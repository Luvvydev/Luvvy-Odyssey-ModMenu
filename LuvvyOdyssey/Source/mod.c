#include "winmini.h"

#define ARRAY_COUNT(x) (sizeof(x)/sizeof((x)[0]))
#define EXPECTED_TIMESTAMP 0x619829C8UL
#define EXPECTED_IMAGE_SIZE 0x11C75000UL
#define IMAGE_SCN_MEM_EXECUTE 0x20000000UL

typedef struct {
 const WCHAR* name;
 BYTE* target;
 BYTE original[16];
 BYTE enabledBytes[16];
 int length;
 int available;
 int enabled;
 int caveKind;
 BYTE* cave;
} Patch;

static HMODULE gSelf;
static BYTE* gBase;
static int gBuildSupported=0;
static HWND gGameWnd=NULL, gOverlay=NULL;
static unsigned long long gBestWindowArea=0;
static int gMenuOpen=0, gSelected=0;
static int gRunning=1;
static Patch gPatches[7];
static const int gPatchCount=7;

static DWORD slen(const char* s){DWORD n=0;while(s&&s[n])n++;return n;}
static DWORD wlen2(const WCHAR* s){DWORD n=0;while(s&&s[n])n++;return n;}
static void wcopy(WCHAR* d,DWORD cap,const WCHAR* s){DWORD i=0;if(!cap)return;while(s&&s[i]&&i+1<cap){d[i]=s[i];i++;}d[i]=0;}
static void wcat(WCHAR* d,DWORD cap,const WCHAR* s){DWORD n=wlen2(d),i=0;while(s&&s[i]&&n+i+1<cap){d[n+i]=s[i];i++;}d[n+i]=0;}

static void log_path(WCHAR* out,DWORD cap){
 DWORD n=GetModuleFileNameW(NULL,out,cap); if(!n||n>=cap){out[0]=0;return;}
 while(n>0&&out[n-1]!=L'\\'&&out[n-1]!=L'/') n--;
 const WCHAR name[]=L"LuvvyModMenu.log"; DWORD i=0; while(name[i]&&n+i+1<cap){out[n+i]=name[i];i++;} out[n+i]=0;
}
static void log_line(const char* s){
 WCHAR path[1024];log_path(path,1024); HANDLE h=CreateFileW(path,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
 if(h==INVALID_HANDLE_VALUE)return; SetFilePointer(h,0,NULL,FILE_END); DWORD wr=0,n=slen(s);WriteFile(h,s,n,&wr,NULL);WriteFile(h,"\r\n",2,&wr,NULL);CloseHandle(h);
}

static int bytes_equal(const BYTE* a,const BYTE* b,int n){int i;for(i=0;i<n;i++)if(a[i]!=b[i])return 0;return 1;}
static void bytes_copy(BYTE* d,const BYTE* s,int n){int i;for(i=0;i<n;i++)d[i]=s[i];}
static void bytes_fill(BYTE* d,BYTE v,int n){int i;for(i=0;i<n;i++)d[i]=v;}

static int protect_write(BYTE* dst,const BYTE* src,int n){
 DWORD old=0,tmp=0; if(!VirtualProtect(dst,(SIZE_T)n,PAGE_EXECUTE_READWRITE,&old)) return 0;
 bytes_copy(dst,src,n); FlushInstructionCache(GetCurrentProcess(),dst,(SIZE_T)n); VirtualProtect(dst,(SIZE_T)n,old,&tmp); return 1;
}

static BYTE* alloc_near(BYTE* target,SIZE_T size){
 ULONG_PTR t=(ULONG_PTR)target; ULONG_PTR gran=0x10000ULL; ULONG_PTR base=t & ~(gran-1); ULONG_PTR maxDelta=0x70000000ULL;
 ULONG_PTR d;
 for(d=gran; d<maxDelta; d+=gran){
  ULONG_PTR hi=base+d; if(hi>base){ LPVOID p=VirtualAlloc((LPVOID)hi,size,MEM_RESERVE|MEM_COMMIT,PAGE_EXECUTE_READWRITE); if(p) return (BYTE*)p; }
  if(base>d){ ULONG_PTR lo=base-d; LPVOID p=VirtualAlloc((LPVOID)lo,size,MEM_RESERVE|MEM_COMMIT,PAGE_EXECUTE_READWRITE); if(p) return (BYTE*)p; }
 }
 return NULL;
}
static int write_rel_jmp(BYTE* at,BYTE* to,int overwrite){
 long long rel=(long long)(to-(at+5)); if(rel < -2147483648LL || rel > 2147483647LL) return 0;
 BYTE b[16]; if(overwrite>16||overwrite<5)return 0; b[0]=0xE9; *(int*)(b+1)=(int)rel; for(int i=5;i<overwrite;i++)b[i]=0x90; return protect_write(at,b,overwrite);
}
static int append_rel_jmp(BYTE* at,BYTE* to){
 long long rel=(long long)(to-(at+5)); if(rel < -2147483648LL || rel > 2147483647LL) return 0;
 at[0]=0xE9; *(int*)(at+1)=(int)rel; return 1;
}

static int enable_cave(Patch* p){
 if(!p->available||p->enabled)return p->enabled;
 if(p->cave){
  if(!bytes_equal(p->target,p->original,p->length)){p->available=0;log_line("[patch] BLOCKED: original bytes changed before cave reapply");return 0;}
  if(write_rel_jmp(p->target,p->cave,p->length)){p->enabled=1;return 1;}
  return 0;
 }
 BYTE* cave=alloc_near(p->target,0x1000); if(!cave){log_line("[patch] ERROR: near cave allocation failed");return 0;}
 int n=0;
 if(p->caveKind==1){
  BYTE a[]={0x8B,0xB7,0x30,0x01,0x00,0x00}; bytes_copy(cave+n,a,6);n+=6;
  BYTE b[]={0xC7,0x87,0x30,0x01,0x00,0x00,0x40,0x42,0x0F,0x00}; bytes_copy(cave+n,b,10);n+=10;
  if(!append_rel_jmp(cave+n,p->target+p->length)){VirtualFree(cave,0,MEM_RELEASE);return 0;} n+=5;
 } else if(p->caveKind==2){
  BYTE a[]={0xC7,0x83,0xA8,0x02,0x00,0x00,0x20,0x03,0x00,0x00};bytes_copy(cave+n,a,10);n+=10;
  if(!append_rel_jmp(cave+n,p->target+p->length)){VirtualFree(cave,0,MEM_RELEASE);return 0;}n+=5;
 } else if(p->caveKind==3){
  BYTE a[]={0xC7,0x81,0xF0,0x05,0x00,0x00,0x00,0x00,0xC8,0x42};bytes_copy(cave+n,a,10);n+=10;
  if(!append_rel_jmp(cave+n,p->target+p->length)){VirtualFree(cave,0,MEM_RELEASE);return 0;}n+=5;
 } else if(p->caveKind==4){
  BYTE a[]={0x2D,0x10,0x27,0x00,0x00,0x89,0x02,0x33,0xC0,0xC3};bytes_copy(cave+n,a,10);n+=10;
 } else {VirtualFree(cave,0,MEM_RELEASE);return 0;}
 FlushInstructionCache(GetCurrentProcess(),cave,(SIZE_T)n);
 if(!bytes_equal(p->target,p->original,p->length)){VirtualFree(cave,0,MEM_RELEASE);p->available=0;log_line("[patch] BLOCKED: original bytes changed before cave install");return 0;}
 if(!write_rel_jmp(p->target,cave,p->length)){VirtualFree(cave,0,MEM_RELEASE);return 0;}
 p->cave=cave;p->enabled=1;return 1;
}
static int disable_patch(Patch* p){
 if(!p->enabled)return 1;
 if(!protect_write(p->target,p->original,p->length))return 0;
 p->enabled=0;
 /* Keep cave memory allocated. An in-flight game thread may still be returning through it. */
 return 1;
}
static int toggle_patch(Patch* p){
 if(!p->available)return 0;
 if(p->enabled)return disable_patch(p);
 if(p->caveKind)return enable_cave(p);
 if(!bytes_equal(p->target,p->original,p->length)){p->available=0;log_line("[patch] BLOCKED: original bytes changed before apply");return 0;}
 if(protect_write(p->target,p->enabledBytes,p->length)){p->enabled=1;return 1;}return 0;
}
static void disable_all(void){for(int i=0;i<gPatchCount;i++)disable_patch(&gPatches[i]);}

static BYTE* scan_unique(const BYTE* pat,const char* mask,int len,int add){
 if(!gBase)return NULL;
 BYTE* dos=gBase; if(dos[0]!='M'||dos[1]!='Z')return NULL; DWORD peoff=*(DWORD*)(dos+0x3c); BYTE* nt=dos+peoff; if(*(DWORD*)nt!=0x00004550UL)return NULL;
 WORD nsec=*(WORD*)(nt+6); WORD opt=*(WORD*)(nt+20); BYTE* sec=nt+24+opt; BYTE* found=NULL;int hits=0;
 for(int s=0;s<nsec;s++){
  BYTE* sh=sec+s*40; DWORD vs=*(DWORD*)(sh+8),va=*(DWORD*)(sh+12),ch=*(DWORD*)(sh+36);
  if(!(ch&IMAGE_SCN_MEM_EXECUTE))continue;
  if(!(sh[0]=='.'&&sh[1]=='s'&&sh[2]=='b'&&sh[3]=='s'&&sh[4]=='s'))continue;
  BYTE* start=gBase+va; DWORD size=vs; if(size<(DWORD)len)continue;
  for(DWORD i=0;i<=size-(DWORD)len;i++){
   int ok=1; for(int j=0;j<len;j++){if(mask[j]=='x'&&start[i+j]!=pat[j]){ok=0;break;}}
   if(ok){found=start+i+add;hits++;if(hits>1)return NULL;}
  }
 }
 return hits==1?found:NULL;
}
static void init_patch(Patch* p,const WCHAR* name,BYTE* target,const BYTE* orig,int len,const BYTE* on,int caveKind){
 p->name=name;p->target=target;p->length=len;p->available=0;p->enabled=0;p->caveKind=caveKind;p->cave=NULL;
 bytes_copy(p->original,orig,len);if(on)bytes_copy(p->enabledBytes,on,len);
 if(target&&bytes_equal(target,orig,len))p->available=1;
}
static void resolve_patches(void){
 BYTE p0[]={0x8B,0xB7,0x30,0x01,0x00,0x00,0x75,0x2B,0x85,0xF6,0x78,0x27};
 BYTE p1[]={0xCF,0x00,0x33,0xD2,0x89,0xBB,0xA8,0x02,0x00,0x00};
 BYTE p2[]={0xF3,0x0F,0x11,0x89,0xF0,0x05,0x00,0x00,0x48,0x8B,0x43};
 BYTE p3[]={0x74,0x10,0xF6,0x43,0x78,0x78};
 BYTE p4[]={0x8B,0x41,0x10,0x8B,0x51,0x14,0x3B,0xC2,0x73,0x03,0x33,0xC0,0xC3};
 BYTE p5[]={0x48,0x3B,0xDD,0x0F,0x84,0,0,0,0,0x66,0x0F,0x1F,0x84,0x00,0x00,0x00,0x00,0x00,0x0F,0x10,0x03};
 BYTE p6[]={0x89,0x02,0x33,0xC0,0xC3,0xCC,0xCC,0xCC,0xCC,0xCC,0x8B,0x81,0x90};
 BYTE o0[]={0x8B,0xB7,0x30,0x01,0x00,0x00};
 BYTE o1[]={0x89,0xBB,0xA8,0x02,0x00,0x00};
 BYTE o2[]={0xF3,0x0F,0x11,0x89,0xF0,0x05,0x00,0x00};
 BYTE o3[]={0x74,0x10},n3[]={0xEB,0x10};
 BYTE o4[]={0x73,0x03},n4[]={0xEB,0x03};
 BYTE o5[]={0x48,0x3B,0xDD},n5[]={0x48,0x31,0xC0};
 BYTE o6[]={0x89,0x02,0x33,0xC0,0xC3};
 init_patch(&gPatches[0],L"God Mode  [EXPERIMENTAL]",scan_unique(p0,"xxxxxxxxxxxx",12,0),o0,6,NULL,1);
 init_patch(&gPatches[1],L"Infinite Adrenaline",scan_unique(p1,"xxxxxxxxxx",10,4),o1,6,NULL,2);
 init_patch(&gPatches[2],L"Infinite Oxygen",scan_unique(p2,"xxxxxxxxxxx",11,0),o2,8,NULL,3);
 init_patch(&gPatches[3],L"No Ability Cooldown",scan_unique(p3,"xxxxxx",6,0),o3,2,n3,0);
 init_patch(&gPatches[4],L"Infinite Ability Points",scan_unique(p4,"xxxxxxxxxxxxx",13,8),o4,2,n4,0);
 init_patch(&gPatches[5],L"Remove Horse Speed Limit",scan_unique(p5,"xxxxx????xxxxxxxxxxxx",22,0),o5,3,n5,0);
 init_patch(&gPatches[6],L"Massive Damage  [EXPERIMENTAL]",scan_unique(p6,"xxxxxxxxxxxxx",13,0),o6,5,NULL,4);
 for(int i=0;i<gPatchCount;i++) log_line(gPatches[i].available?"[patch] signature verified":"[patch] BLOCKED: signature missing or non-unique");
}

static BOOL CALLBACK enum_cb(HWND h,LPARAM lp){
 DWORD pid=0;(void)lp;
 if(h==gOverlay||!IsWindowVisible(h))return TRUE;
 GetWindowThreadProcessId(h,&pid);if(pid!=GetCurrentProcessId())return TRUE;
 RECT r;if(!GetWindowRect(h,&r))return TRUE;
 long w=r.right-r.left,hgt=r.bottom-r.top;if(w<=0||hgt<=0)return TRUE;
 unsigned long long area=(unsigned long long)(unsigned long)w*(unsigned long long)(unsigned long)hgt;
 if(area>gBestWindowArea){gBestWindowArea=area;gGameWnd=h;}
 return TRUE;
}
static HWND find_game_window(void){gGameWnd=NULL;gBestWindowArea=0;EnumWindows(enum_cb,0);return gGameWnd;}

static void make_line(WCHAR* out,DWORD cap,const WCHAR* name,const WCHAR* status){wcopy(out,cap,name);wcat(out,cap,L"   ");wcat(out,cap,status);}
static LRESULT CALLBACK OverlayProc(HWND h,UINT m,WPARAM w,LPARAM l){
 (void)w;(void)l;
 if(m==WM_ERASEBKGND)return 1;
 if(m==WM_PAINT){
  PAINTSTRUCT ps;HDC dc=BeginPaint(h,&ps);RECT bg={0,0,520,370};FillRect(dc,&bg,(HBRUSH)GetStockObject(BLACK_BRUSH));SetBkMode(dc,TRANSPARENT);SelectObject(dc,GetStockObject(DEFAULT_GUI_FONT));
  RECT r={18,12,500,36};SetTextColor(dc,0x00FFFFFF);DrawTextW(dc,L"Luvvy Odyssey Mod Menu  |  F10 close",-1,&r,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  RECT b={18,38,500,60};SetTextColor(dc,gBuildSupported?0x008CFF78:0x006060FF);DrawTextW(dc,gBuildSupported?L"EXACT BUILD VERIFIED":L"BLOCKED: unsupported executable build",-1,&b,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  for(int i=0;i<gPatchCount+1;i++){
   WCHAR line[160];const WCHAR* name;const WCHAR* st=L"";
   if(i<gPatchCount){name=gPatches[i].name; if(!gBuildSupported||!gPatches[i].available)st=L"[BLOCKED]";else st=gPatches[i].enabled?L"[ON]":L"[OFF]";}
   else {name=L"Disable All";st=L"";}
   make_line(line,160,name,st); RECT rr={28,72+i*30,500,98+i*30}; SetTextColor(dc,i==gSelected?0x008CFF78:0x00FFFFFF); DrawTextW(dc,line,-1,&rr,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  }
  RECT f={18,330,500,355};SetTextColor(dc,0x00C0C0C0);DrawTextW(dc,L"Up/Down select   Enter toggle   F10 hide",-1,&f,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  EndPaint(h,&ps);return 0;
 }
 return DefWindowProcW(h,m,w,l);
}
static int create_overlay(void){
 WNDCLASSEXW wc; bytes_fill((BYTE*)&wc,0,sizeof(wc));wc.cbSize=sizeof(wc);wc.lpfnWndProc=OverlayProc;wc.hInstance=(HINSTANCE)gSelf;wc.lpszClassName=L"LuvvyOdysseyOverlay";RegisterClassExW(&wc);
 gOverlay=CreateWindowExW(WS_EX_TOPMOST|WS_EX_TOOLWINDOW|WS_EX_LAYERED|WS_EX_NOACTIVATE|WS_EX_TRANSPARENT,L"LuvvyOdysseyOverlay",L"Luvvy Odyssey",WS_POPUP,40,40,520,370,NULL,NULL,(HINSTANCE)gSelf,NULL);
 if(!gOverlay)return 0;SetLayeredWindowAttributes(gOverlay,0,220,LWA_ALPHA);return 1;
}
static void reposition(void){
 if(!gOverlay)return;if(!gGameWnd||!IsWindowVisible(gGameWnd))find_game_window();if(!gGameWnd)return;RECT r;if(!GetWindowRect(gGameWnd,&r))return;SetWindowPos(gOverlay,HWND_TOPMOST,r.left+35,r.top+35,520,370,SWP_NOACTIVATE);
}
static void toggle_selected(void){
 if(gSelected<gPatchCount){if(gBuildSupported)toggle_patch(&gPatches[gSelected]);}
 else disable_all();if(gOverlay)InvalidateRect(gOverlay,NULL,TRUE);
}
static DWORD WINAPI MainThread(LPVOID p){
 (void)p;log_line("[mod] LuvvyOdysseyMod loaded");gBase=(BYTE*)GetModuleHandleW(L"ACOdyssey.exe");
 if(!gBase){log_line("[mod] ERROR: ACOdyssey.exe module not found");return 0;}
 DWORD peoff=*(DWORD*)(gBase+0x3c);BYTE* nt=gBase+peoff;DWORD stamp=*(DWORD*)(nt+8);BYTE* opt=nt+24;DWORD size=*(DWORD*)(opt+56);
 gBuildSupported=(stamp==EXPECTED_TIMESTAMP&&size==EXPECTED_IMAGE_SIZE);log_line(gBuildSupported?"[mod] build marker verified":"[mod] BLOCKED: build marker mismatch");
 if(gBuildSupported)resolve_patches();else{for(int i=0;i<gPatchCount;i++)gPatches[i].available=0;}
 if(!create_overlay()){log_line("[overlay] ERROR: CreateWindowExW failed");return 0;}log_line("[overlay] initialized; F10 input initialized");
 DWORD ticks=0;MSG msg;
 while(gRunning){
  while(PeekMessageW(&msg,NULL,0,0,PM_REMOVE)){TranslateMessage(&msg);DispatchMessageW(&msg);}
  if(GetAsyncKeyState(VK_F10)&1){gMenuOpen=!gMenuOpen;ShowWindow(gOverlay,gMenuOpen?SW_SHOWNOACTIVATE:SW_HIDE);if(gMenuOpen){reposition();InvalidateRect(gOverlay,NULL,TRUE);}}
  if(gMenuOpen){
   if(GetAsyncKeyState(VK_UP)&1){gSelected--;if(gSelected<0)gSelected=gPatchCount;InvalidateRect(gOverlay,NULL,TRUE);}
   if(GetAsyncKeyState(VK_DOWN)&1){gSelected++;if(gSelected>gPatchCount)gSelected=0;InvalidateRect(gOverlay,NULL,TRUE);}
   if(GetAsyncKeyState(VK_RETURN)&1)toggle_selected();
   if(GetAsyncKeyState(VK_ESCAPE)&1){gMenuOpen=0;ShowWindow(gOverlay,SW_HIDE);}
   if((ticks++%20)==0)reposition();
  }
  Sleep(25);
 }
 disable_all();if(gOverlay)DestroyWindow(gOverlay);return 0;
}

BOOL WINAPI DllMain(HINSTANCE h,DWORD reason,LPVOID reserved){
 (void)reserved;
 if(reason==DLL_PROCESS_ATTACH){gSelf=(HMODULE)h;DisableThreadLibraryCalls((HMODULE)h);HANDLE t=CreateThread(NULL,0,MainThread,NULL,0,NULL);if(t)CloseHandle(t);}
 else if(reason==DLL_PROCESS_DETACH){gRunning=0;}
 return TRUE;
}
