int _fltused=0;
typedef void* HANDLE;
typedef void* HINSTANCE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* HDC;
typedef void* HGDIOBJ;
typedef void* HBRUSH;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef unsigned long DWORD;
typedef unsigned long long ULONG_PTR;
typedef unsigned long long SIZE_T;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef unsigned short WCHAR;
typedef const WCHAR* LPCWSTR;
typedef const char* LPCSTR;
typedef unsigned int UINT;
typedef int BOOL;
typedef long LONG;
typedef long long LONG_PTR;
typedef LONG_PTR LPARAM;
typedef ULONG_PTR WPARAM;
typedef LONG_PTR LRESULT;
typedef unsigned long COLORREF;
#define WINAPI __stdcall
#define CALLBACK __stdcall
#define TRUE 1
#define FALSE 0
#define NULL ((void*)0)
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define MAX_PATH 260
#define TH32CS_SNAPPROCESS 0x00000002UL
#define TH32CS_SNAPMODULE 0x00000008UL
#define TH32CS_SNAPMODULE32 0x00000010UL
#define PROCESS_QUERY_INFORMATION 0x0400UL
#define PROCESS_VM_OPERATION 0x0008UL
#define PROCESS_VM_WRITE 0x0020UL
#define PROCESS_VM_READ 0x0010UL
#define SYNCHRONIZE 0x00100000UL
#define MEM_COMMIT 0x1000UL
#define MEM_RESERVE 0x2000UL
#define PAGE_EXECUTE_READWRITE 0x40UL
#define GENERIC_WRITE 0x40000000UL
#define FILE_SHARE_READ 0x00000001UL
#define OPEN_ALWAYS 4UL
#define FILE_ATTRIBUTE_NORMAL 0x00000080UL
#define FILE_END 2UL
#define STILL_ACTIVE 259UL
#define WS_POPUP 0x80000000UL
#define WS_EX_TOPMOST 0x00000008UL
#define WS_EX_TRANSPARENT 0x00000020UL
#define WS_EX_TOOLWINDOW 0x00000080UL
#define WS_EX_LAYERED 0x00080000UL
#define WS_EX_NOACTIVATE 0x08000000UL
#define SW_HIDE 0
#define SW_SHOWNOACTIVATE 4
#define SWP_NOACTIVATE 0x0010
#define WM_PAINT 0x000F
#define WM_ERASEBKGND 0x0014
#define PM_REMOVE 0x0001
#define LWA_ALPHA 0x00000002UL
#define DT_LEFT 0x00000000UL
#define DT_VCENTER 0x00000004UL
#define DT_SINGLELINE 0x00000020UL
#define DT_NOPREFIX 0x00000800UL
#define TRANSPARENT 1
#define BLACK_BRUSH 4
#define DEFAULT_GUI_FONT 17
#define VK_F10 0x79
#define VK_UP 0x26
#define VK_DOWN 0x28
#define VK_RETURN 0x0D
#define VK_ESCAPE 0x1B
#define HWND_TOPMOST ((HWND)(LONG_PTR)-1)
#define EXPECTED_TIMESTAMP 0x619829C8UL
#define EXPECTED_IMAGE_SIZE 0x11C75000UL

typedef struct tagRECT { LONG left; LONG top; LONG right; LONG bottom; } RECT;
typedef struct tagPOINT { LONG x; LONG y; } POINT;
typedef struct tagPAINTSTRUCT { HDC hdc; BOOL fErase; RECT rcPaint; BOOL fRestore; BOOL fIncUpdate; BYTE rgbReserved[32]; } PAINTSTRUCT;
typedef struct tagMSG { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; DWORD lPrivate; } MSG;
typedef LRESULT (CALLBACK *WNDPROC)(HWND,UINT,WPARAM,LPARAM);
typedef struct tagWNDCLASSEXW {
 UINT cbSize; UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance;
 void* hIcon; void* hCursor; HBRUSH hbrBackground; LPCWSTR lpszMenuName; LPCWSTR lpszClassName; void* hIconSm;
} WNDCLASSEXW;
typedef BOOL (CALLBACK *WNDENUMPROC)(HWND,LPARAM);

typedef struct tagPROCESSENTRY32W {
 DWORD dwSize; DWORD cntUsage; DWORD th32ProcessID; ULONG_PTR th32DefaultHeapID; DWORD th32ModuleID;
 DWORD cntThreads; DWORD th32ParentProcessID; LONG pcPriClassBase; DWORD dwFlags; WCHAR szExeFile[MAX_PATH];
} PROCESSENTRY32W;
typedef struct tagMODULEENTRY32W {
 DWORD dwSize; DWORD th32ModuleID; DWORD th32ProcessID; DWORD GlblcntUsage; DWORD ProccntUsage;
 BYTE* modBaseAddr; DWORD modBaseSize; HMODULE hModule; WCHAR szModule[256]; WCHAR szExePath[MAX_PATH];
} MODULEENTRY32W;

__declspec(dllimport) HANDLE WINAPI CreateToolhelp32Snapshot(DWORD,DWORD);
__declspec(dllimport) BOOL WINAPI Process32FirstW(HANDLE,PROCESSENTRY32W*);
__declspec(dllimport) BOOL WINAPI Process32NextW(HANDLE,PROCESSENTRY32W*);
__declspec(dllimport) BOOL WINAPI Module32FirstW(HANDLE,MODULEENTRY32W*);
__declspec(dllimport) BOOL WINAPI Module32NextW(HANDLE,MODULEENTRY32W*);
__declspec(dllimport) HANDLE WINAPI OpenProcess(DWORD,BOOL,DWORD);
__declspec(dllimport) BOOL WINAPI GetExitCodeProcess(HANDLE,DWORD*);
__declspec(dllimport) BOOL WINAPI ReadProcessMemory(HANDLE,LPCVOID,LPVOID,SIZE_T,SIZE_T*);
__declspec(dllimport) BOOL WINAPI WriteProcessMemory(HANDLE,LPVOID,LPCVOID,SIZE_T,SIZE_T*);
__declspec(dllimport) BOOL WINAPI VirtualProtectEx(HANDLE,LPVOID,SIZE_T,DWORD,DWORD*);
__declspec(dllimport) LPVOID WINAPI VirtualAllocEx(HANDLE,LPVOID,SIZE_T,DWORD,DWORD);
__declspec(dllimport) BOOL WINAPI FlushInstructionCache(HANDLE,LPCVOID,SIZE_T);
__declspec(dllimport) DWORD WINAPI GetModuleFileNameW(HMODULE,WCHAR*,DWORD);
__declspec(dllimport) HMODULE WINAPI GetModuleHandleW(LPCWSTR);
__declspec(dllimport) DWORD WINAPI GetLastError(void);
__declspec(dllimport) void WINAPI Sleep(DWORD);
__declspec(dllimport) BOOL WINAPI CloseHandle(HANDLE);
__declspec(dllimport) void WINAPI ExitProcess(UINT);
__declspec(dllimport) HANDLE WINAPI CreateFileW(LPCWSTR,DWORD,DWORD,void*,DWORD,DWORD,HANDLE);
__declspec(dllimport) BOOL WINAPI WriteFile(HANDLE,LPCVOID,DWORD,DWORD*,void*);
__declspec(dllimport) DWORD WINAPI SetFilePointer(HANDLE,LONG,LONG*,DWORD);
__declspec(dllimport) HINSTANCE WINAPI ShellExecuteW(HWND,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,int);

__declspec(dllimport) BOOL WINAPI EnumWindows(WNDENUMPROC,LPARAM);
__declspec(dllimport) DWORD WINAPI GetWindowThreadProcessId(HWND,DWORD*);
__declspec(dllimport) BOOL WINAPI IsWindowVisible(HWND);
__declspec(dllimport) BOOL WINAPI GetWindowRect(HWND,RECT*);
__declspec(dllimport) unsigned short WINAPI RegisterClassExW(const WNDCLASSEXW*);
__declspec(dllimport) HWND WINAPI CreateWindowExW(DWORD,LPCWSTR,LPCWSTR,DWORD,int,int,int,int,HWND,void*,HINSTANCE,LPVOID);
__declspec(dllimport) LRESULT WINAPI DefWindowProcW(HWND,UINT,WPARAM,LPARAM);
__declspec(dllimport) BOOL WINAPI ShowWindow(HWND,int);
__declspec(dllimport) BOOL WINAPI SetWindowPos(HWND,HWND,int,int,int,int,UINT);
__declspec(dllimport) short WINAPI GetAsyncKeyState(int);
__declspec(dllimport) BOOL WINAPI InvalidateRect(HWND,const RECT*,BOOL);
__declspec(dllimport) HDC WINAPI BeginPaint(HWND,PAINTSTRUCT*);
__declspec(dllimport) BOOL WINAPI EndPaint(HWND,const PAINTSTRUCT*);
__declspec(dllimport) int WINAPI FillRect(HDC,const RECT*,HBRUSH);
__declspec(dllimport) int WINAPI DrawTextW(HDC,LPCWSTR,int,RECT*,UINT);
__declspec(dllimport) BOOL WINAPI SetLayeredWindowAttributes(HWND,COLORREF,BYTE,DWORD);
__declspec(dllimport) BOOL WINAPI PeekMessageW(MSG*,HWND,UINT,UINT,UINT);
__declspec(dllimport) BOOL WINAPI TranslateMessage(const MSG*);
__declspec(dllimport) LRESULT WINAPI DispatchMessageW(const MSG*);
__declspec(dllimport) BOOL WINAPI DestroyWindow(HWND);
__declspec(dllimport) COLORREF WINAPI SetTextColor(HDC,COLORREF);
__declspec(dllimport) int WINAPI SetBkMode(HDC,int);
__declspec(dllimport) HGDIOBJ WINAPI GetStockObject(int);
__declspec(dllimport) HGDIOBJ WINAPI SelectObject(HDC,HGDIOBJ);

typedef struct {
 const WCHAR* name;
 ULONG_PTR sigRva;
 int sigLen;
 BYTE sig[24];
 char mask[25];
 int add;
 BYTE original[16];
 BYTE enabledBytes[16];
 int length;
 int caveKind;
 ULONG_PTR target;
 ULONG_PTR cave;
 int available;
 int enabled;
} Patch;

static HINSTANCE gSelf;
static HANDLE gProcess=NULL;
static DWORD gPid=0;
static ULONG_PTR gBase=0;
static HWND gGameWnd=NULL,gOverlay=NULL;
static unsigned long long gBestWindowArea=0;
static int gBuildSupported=0,gMenuOpen=0,gSelected=0,gRunning=1;
static Patch gPatches[17];
static const int gPatchCount=17;

static ULONG_PTR gTeleportTarget=0,gTeleportCave=0,gTeleportPlayerPtr=0,gTeleportWaypointXYZ=0,gTeleportCaptureSeq=0;
static BYTE gTeleportOriginal[7]={0x48,0x8B,0x92,0x90,0x00,0x00,0x00};
static int gTeleportAvailable=0,gTeleportInstalled=0,gTeleportHasCapture=0;
static DWORD gTeleportLastSeq=0;

/* Teleport execution is deliberately separate from waypoint capture.
   This target is the same live character transform instruction used by the supplied working CE teleport scripts. */
static ULONG_PTR gTeleportApplyTarget=0,gTeleportApplyCave=0,gTeleportApplyXYZ=0,gTeleportApplyCount=0,gTeleportApplyDone=0;
static BYTE gTeleportApplyOriginal[8]={0x0F,0x28,0x52,0x50,0x49,0x89,0x5B,0x08};
static int gTeleportApplyAvailable=0,gTeleportApplyInstalled=0,gTeleportApplyPending=0,gTeleportApplyPolls=0;

static DWORD alen(const char* s){DWORD n=0;while(s&&s[n])n++;return n;}
static DWORD wlen(const WCHAR* s){DWORD n=0;while(s&&s[n])n++;return n;}
static void wcopy(WCHAR* d,DWORD cap,const WCHAR* s){DWORD i=0;if(!cap)return;while(s&&s[i]&&i+1<cap){d[i]=s[i];i++;}d[i]=0;}
static void wcat(WCHAR* d,DWORD cap,const WCHAR* s){DWORD n=wlen(d),i=0;while(s&&s[i]&&n+i+1<cap){d[n+i]=s[i];i++;}d[n+i]=0;}
static WCHAR lowerw(WCHAR c){return(c>=L'A'&&c<=L'Z')?(WCHAR)(c+32):c;}
static int weq_ci(const WCHAR* a,const WCHAR* b){DWORD i=0;while(a[i]&&b[i]){if(lowerw(a[i])!=lowerw(b[i]))return 0;i++;}return a[i]==0&&b[i]==0;}
static void bytes_copy(BYTE* d,const BYTE* s,int n){for(int i=0;i<n;i++)d[i]=s[i];}
static void bytes_fill(BYTE* d,BYTE v,int n){for(int i=0;i<n;i++)d[i]=v;}
static int bytes_equal(const BYTE* a,const BYTE* b,int n){for(int i=0;i<n;i++)if(a[i]!=b[i])return 0;return 1;}

static void base_dir(WCHAR* out,DWORD cap){DWORD n=GetModuleFileNameW(NULL,out,cap);if(!n||n>=cap){out[0]=0;return;}while(n>0&&out[n-1]!=L'\\'&&out[n-1]!=L'/')n--;out[n]=0;}
static void log_line(const char* s){WCHAR p[1024];base_dir(p,1024);wcat(p,1024,L"LuvvyExternalMenu.log");HANDLE h=CreateFileW(p,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);if(h==INVALID_HANDLE_VALUE)return;SetFilePointer(h,0,NULL,FILE_END);DWORD wr=0,n=alen(s);WriteFile(h,s,n,&wr,NULL);WriteFile(h,"\r\n",2,&wr,NULL);CloseHandle(h);}
static void log_num(const char* prefix,DWORD v){char b[192];DWORD p=0,i=0;while(prefix[p]&&p+1<sizeof(b)){b[p]=prefix[p];p++;}char d[16];if(!v)d[i++]='0';while(v&&i<sizeof(d)){d[i++]=(char)('0'+v%10);v/=10;}while(i&&p+1<sizeof(b))b[p++]=d[--i];b[p]=0;log_line(b);}

static DWORD find_process(void){HANDLE s=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);if(s==INVALID_HANDLE_VALUE)return 0;PROCESSENTRY32W e;e.dwSize=sizeof(e);DWORD pid=0;if(Process32FirstW(s,&e)){do{if(weq_ci(e.szExeFile,L"ACOdyssey.exe")){pid=e.th32ProcessID;break;}e.dwSize=sizeof(e);}while(Process32NextW(s,&e));}CloseHandle(s);return pid;}
static ULONG_PTR remote_module_base(DWORD pid,const WCHAR* name){for(int a=0;a<5;a++){HANDLE s=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32,pid);if(s==INVALID_HANDLE_VALUE){Sleep(50);continue;}MODULEENTRY32W m;m.dwSize=sizeof(m);ULONG_PTR base=0;if(Module32FirstW(s,&m)){do{if(weq_ci(m.szModule,name)){base=(ULONG_PTR)m.modBaseAddr;break;}m.dwSize=sizeof(m);}while(Module32NextW(s,&m));}CloseHandle(s);if(base)return base;Sleep(50);}return 0;}
static int process_alive_handle(void){DWORD code=0;return gProcess&&GetExitCodeProcess(gProcess,&code)&&code==STILL_ACTIVE;}

static BOOL CALLBACK enum_game_cb(HWND h,LPARAM lp){(void)lp;DWORD pid=0;if(h==gOverlay||!IsWindowVisible(h))return TRUE;GetWindowThreadProcessId(h,&pid);if(pid!=gPid)return TRUE;RECT r;if(!GetWindowRect(h,&r))return TRUE;LONG w=r.right-r.left,ht=r.bottom-r.top;if(w<=0||ht<=0)return TRUE;unsigned long long area=(unsigned long long)(unsigned long)w*(unsigned long long)(unsigned long)ht;if(area>gBestWindowArea){gBestWindowArea=area;gGameWnd=h;}return TRUE;}
static HWND find_game_window(void){gGameWnd=NULL;gBestWindowArea=0;EnumWindows(enum_game_cb,0);return gGameWnd;}
static int has_large_game_window(DWORD pid){gPid=pid;find_game_window();if(!gGameWnd)return 0;RECT r;if(!GetWindowRect(gGameWnd,&r))return 0;return (r.right-r.left)>=640&&(r.bottom-r.top)>=360;}

static int remote_read(ULONG_PTR at,BYTE* out,SIZE_T n){SIZE_T got=0;return ReadProcessMemory(gProcess,(LPCVOID)at,out,n,&got)&&got==n;}
static int remote_equal(ULONG_PTR at,const BYTE* expected,int n){BYTE b[32];if(n>(int)sizeof(b)||!remote_read(at,b,(SIZE_T)n))return 0;return bytes_equal(b,expected,n);}
static int remote_sig_equal(Patch* p){BYTE b[32];if(p->sigLen>(int)sizeof(b)||!remote_read(gBase+p->sigRva,b,(SIZE_T)p->sigLen))return 0;for(int i=0;i<p->sigLen;i++)if(p->mask[i]=='x'&&b[i]!=p->sig[i])return 0;return 1;}
static int remote_write(ULONG_PTR at,const BYTE* src,int n){DWORD old=0,tmp=0;SIZE_T wrote=0;if(!VirtualProtectEx(gProcess,(LPVOID)at,(SIZE_T)n,PAGE_EXECUTE_READWRITE,&old))return 0;BOOL ok=WriteProcessMemory(gProcess,(LPVOID)at,src,(SIZE_T)n,&wrote)&&wrote==(SIZE_T)n;FlushInstructionCache(gProcess,(LPCVOID)at,(SIZE_T)n);VirtualProtectEx(gProcess,(LPVOID)at,(SIZE_T)n,old,&tmp);return ok;}
static ULONG_PTR alloc_near(ULONG_PTR target,SIZE_T size){ULONG_PTR gran=0x10000ULL,base=target&~(gran-1),maxDelta=0x70000000ULL;for(ULONG_PTR d=gran;d<maxDelta;d+=gran){ULONG_PTR hi=base+d;if(hi>base){LPVOID p=VirtualAllocEx(gProcess,(LPVOID)hi,size,MEM_RESERVE|MEM_COMMIT,PAGE_EXECUTE_READWRITE);if(p)return(ULONG_PTR)p;}if(base>d){ULONG_PTR lo=base-d;LPVOID p=VirtualAllocEx(gProcess,(LPVOID)lo,size,MEM_RESERVE|MEM_COMMIT,PAGE_EXECUTE_READWRITE);if(p)return(ULONG_PTR)p;}}return 0;}
static int make_rel_jmp(BYTE* out,ULONG_PTR at,ULONG_PTR to,int overwrite){long long rel=(long long)to-(long long)(at+5);if(rel<-2147483648LL||rel>2147483647LL||overwrite<5||overwrite>16)return 0;out[0]=0xE9;*(int*)(out+1)=(int)rel;for(int i=5;i<overwrite;i++)out[i]=0x90;return 1;}
static int append_rel_jmp(BYTE* out,ULONG_PTR at,ULONG_PTR to){long long rel=(long long)to-(long long)(at+5);if(rel<-2147483648LL||rel>2147483647LL)return 0;out[0]=0xE9;*(int*)(out+1)=(int)rel;return 1;}
static int append_rel_jcc(BYTE* out,ULONG_PTR at,ULONG_PTR to,BYTE cc){long long rel=(long long)to-(long long)(at+6);if(rel<-2147483648LL||rel>2147483647LL)return 0;out[0]=0x0F;out[1]=cc;*(int*)(out+2)=(int)rel;return 1;}
static int append_rip_disp(BYTE* out,ULONG_PTR next,ULONG_PTR to){long long rel=(long long)to-(long long)next;if(rel<-2147483648LL||rel>2147483647LL)return 0;*(int*)out=(int)rel;return 1;}

static void setup_patch(Patch* p,const WCHAR* name,ULONG_PTR sigRva,const BYTE* sig,const char* mask,int sigLen,int add,const BYTE* orig,int len,const BYTE* on,int caveKind){p->name=name;p->sigRva=sigRva;p->sigLen=sigLen;p->add=add;p->length=len;p->caveKind=caveKind;p->target=gBase+sigRva+(ULONG_PTR)add;p->cave=0;p->enabled=0;p->available=0;bytes_copy(p->sig,sig,sigLen);for(int i=0;i<sigLen;i++)p->mask[i]=mask[i];p->mask[sigLen]=0;bytes_copy(p->original,orig,len);if(on)bytes_copy(p->enabledBytes,on,len);if(remote_sig_equal(p)&&remote_equal(p->target,p->original,p->length))p->available=1;}
static void resolve_patches(void){
 BYTE p0[]={0x8B,0xB7,0x30,0x01,0x00,0x00,0x75,0x2B,0x85,0xF6,0x78,0x27};
 BYTE p1[]={0xCF,0x00,0x33,0xD2,0x89,0xBB,0xA8,0x02,0x00,0x00};
 BYTE p2[]={0xF3,0x0F,0x11,0x89,0xF0,0x05,0x00,0x00,0x48,0x8B,0x43};
 BYTE p3[]={0xF6,0x43,0x78,0x78,0x74,0x06,0x83,0x63,0x7C,0xF7,0xEB,0x04};
 BYTE p4[]={0x8B,0x41,0x10,0x8B,0x51,0x14,0x3B,0xC2,0x73,0x03,0x33,0xC0,0xC3,0x2B,0xC2,0xC3};
 BYTE p5[]={0x48,0x3B,0xDD,0x0F,0x84,0,0,0,0,0x66,0x0F,0x1F,0x84,0x00,0x00,0x00,0x00,0x00,0x0F,0x10,0x03};
 BYTE p6[]={0x89,0x02,0x33,0xC0,0xC3,0xCC,0xCC,0xCC,0xCC,0xCC,0x8B,0x81,0x90};
 BYTE p7[]={0xE8,0x44,0x4C,0x26,0xFF,0x48,0x8D,0x4C,0x24,0x20,0x0F,0xB6,0xD8,0xE8,0x27,0x80};
 BYTE p8[]={0x44,0x89,0x03,0x75,0x0B,0x8B,0xD7,0x49,0x8D,0x4E,0x2C,0xE8,0xCC,0x10,0x00,0x00};
 BYTE p9[]={0xF3,0x44,0x0F,0x11,0x49,0x28,0xB0,0x01,0x0F,0x2E,0x71,0x2C,0x74,0x07,0xF3,0x0F};
 BYTE p10[]={0x8B,0x81,0xFC,0x01,0x00,0x00,0x39,0x42,0x10,0x0F,0x97,0xC0,0x84,0xC0,0x0F,0x84};
 BYTE p11[]={0x66,0x41,0x0F,0x6E,0x0E,0x66,0x0F,0x6E,0xC0,0x0F,0x5B,0xC9,0x0F,0x5B,0xC0,0xF3};
 BYTE p12[]={0x0F,0x2F,0x40,0x50,0x72,0xC4,0x48,0x8B,0x0B,0x48,0x8B,0x01,0xFF,0x50,0x68,0xF3};
 BYTE p13[]={0xE8,0x28,0x9D,0xCE,0xF5,0xB8,0x01,0x00,0x00,0x00,0x48,0x83,0xC4,0x28,0xC3,0xCC};
 BYTE p14[]={0x41,0x8B,0x82,0xC4,0x03,0x00,0x00,0x89,0x42,0x24,0x41,0x8B,0x82,0xCC,0x03,0x00};
 BYTE p15[]={0xE8,0x89,0x8E,0xFF,0xFF,0x0F,0xB6,0xF8,0x84,0xC0,0x75,0x0E,0x48,0x8B,0xCE,0xE8,0x1A,0xD0,0x40,0xFD};
 BYTE p16[]={0x44,0x8B,0x87,0xB8,0x00,0x00,0x00,0x48,0x81,0xC1,0x08,0x01,0x00,0x00,0x89,0x44};

 BYTE o0[]={0x8B,0xB7,0x30,0x01,0x00,0x00};
 BYTE o1[]={0x89,0xBB,0xA8,0x02,0x00,0x00};
 BYTE o2[]={0xF3,0x0F,0x11,0x89,0xF0,0x05,0x00,0x00};
 BYTE o3[]={0x78},n3[]={0x01};
 BYTE o4[]={0x73,0x03},n4[]={0xEB,0x03};
 BYTE o5[]={0x48,0x3B,0xDD},n5[]={0x48,0x31,0xC0};
 BYTE o6[]={0x89,0x02,0x33,0xC0,0xC3};
 BYTE o7[]={0xE8,0x44,0x4C,0x26,0xFF},n7[]={0x90,0x90,0x90,0x90,0x90};
 BYTE o8[]={0x44,0x89,0x03,0x75,0x0B};
 BYTE o9[]={0xF3,0x44,0x0F,0x11,0x49,0x28};
 BYTE o10[]={0x8B,0x81,0xFC,0x01,0x00,0x00};
 BYTE o11[]={0x66,0x41,0x0F,0x6E,0x0E};
 BYTE o12[]={0x0F,0x2F,0x40,0x50,0x72,0xC4};
 BYTE o13[]={0xE8,0x28,0x9D,0xCE,0xF5},n13[]={0x90,0x90,0x90,0x90,0x90};
 BYTE o14[]={0x41,0x8B,0x82,0xC4,0x03,0x00,0x00};
 BYTE o15[]={0xE8,0x89,0x8E,0xFF,0xFF},n15[]={0x90,0x90,0x90,0x90,0x90};
 BYTE o16[]={0x44,0x8B,0x87,0xB8,0x00,0x00,0x00};

 setup_patch(&gPatches[0],L"God Mode  [EXPERIMENTAL]",0x22E0FEEULL,p0,"xxxxxxxxxxxx",12,0,o0,6,NULL,1);
 setup_patch(&gPatches[1],L"Infinite Adrenaline",0x22D7595ULL,p1,"xxxxxxxxxx",10,4,o1,6,NULL,2);
 setup_patch(&gPatches[2],L"Infinite Oxygen",0x35A958AULL,p2,"xxxxxxxxxxx",11,0,o2,8,NULL,3);
 setup_patch(&gPatches[3],L"No Ability Cooldown  [v2]",0x20224A5ULL,p3,"xxxxxxxxxxxx",12,3,o3,1,n3,0);
 setup_patch(&gPatches[4],L"Infinite Ability Points  [v2]",0x24337E0ULL,p4,"xxxxxxxxxxxxxxxx",16,8,o4,2,n4,5);
 setup_patch(&gPatches[5],L"Remove Horse Speed Limit",0x2973BCEULL,p5,"xxxxx????xxxxxxxxxxxx",22,0,o5,3,n5,0);
 setup_patch(&gPatches[6],L"One Hit Kill",0x22981D6ULL,p6,"xxxxxxxxxxxxx",13,0,o6,5,NULL,4);
 setup_patch(&gPatches[7],L"Stealth / Undetected",0x28CC9D7ULL,p7,"xxxxxxxxxxxxxxxx",16,0,o7,5,n7,0);
 setup_patch(&gPatches[8],L"Infinite Materials + Drachmae + Arrows",0x2617F94ULL,p8,"xxxxxxxxxxxxxxxx",16,0,o8,5,NULL,6);
 setup_patch(&gPatches[9],L"No Bounty",0x25493EFULL,p9,"xxxxxxxxxxxxxxxx",16,0,o9,6,NULL,7);
 setup_patch(&gPatches[10],L"Inventory Capacity 1000",0x28D220BULL,p10,"xxxxxxxxxxxxxxxx",16,0,o10,6,NULL,8);
 setup_patch(&gPatches[11],L"Ship God Mode + Enemy Ship One Hit Kill",0x30E36F0ULL,p11,"xxxxxxxxxxxxxxxx",16,0,o11,5,NULL,9);
 setup_patch(&gPatches[12],L"Infinite Ship Stamina  [EXPERIMENTAL]",0x310F49CULL,p12,"xxxxxxxxxxxxxxxx",16,0,o12,6,NULL,10);
 setup_patch(&gPatches[13],L"Infinite Felucca HP",0xAD77483ULL,p13,"xxxxxxxxxxxxxxxx",16,0,o13,5,n13,0);
 setup_patch(&gPatches[14],L"Maximum Phobos Speed",0x1F120F4ULL,p14,"xxxxxxxxxxxxxxxx",16,0,o14,7,NULL,11);
 setup_patch(&gPatches[15],L"Auto Climb  [EXPERIMENTAL]",0x3559172ULL,p15,"xxxxxxxxxxxxxxxxxxxx",20,0,o15,5,n15,0);
 setup_patch(&gPatches[16],L"XP Boost +8000  [EXPERIMENTAL]",0x2922715ULL,p16,"xxxxxxxxxxxxxxxx",16,0,o16,7,NULL,12);

 if(gPatches[4].available){
  BYTE abilityChild[]={0x2B,0xC2};
  if(!remote_equal(gBase+0x24337EDULL,abilityChild,2))gPatches[4].available=0;
 }

 for(int i=0;i<gPatchCount;i++)log_line(gPatches[i].available?"[patch] signature and original bytes verified":"[patch] BLOCKED: signature/original bytes mismatch");

 gTeleportTarget=gBase+0x2F30043ULL;
 BYTE teleSig[]={0x48,0x8B,0x92,0x90,0x00,0x00,0x00,0x48,0x85,0xD2,0x74,0x1A,0x48,0x8D,0x4C,0x24,0x40,0xE8,0xA7,0xCD,0x1B,0xFF,0x0F,0x28};
 gTeleportAvailable=remote_equal(gTeleportTarget,teleSig,24);
 log_line(gTeleportAvailable?"[teleport] waypoint capture signature verified":"[teleport] BLOCKED: waypoint capture signature mismatch");

 gTeleportApplyTarget=gBase+0x183D20BULL;
 BYTE teleApplySig[]={0x0F,0x28,0x52,0x50,0x49,0x89,0x5B,0x08,0x41,0x0F,0x29,0x73,0xD8};
 gTeleportApplyAvailable=remote_equal(gTeleportApplyTarget,teleApplySig,13);
 log_line(gTeleportApplyAvailable?"[teleport] live character transform signature verified":"[teleport] BLOCKED: live character transform signature mismatch");
}

static int enable_ability_points(Patch* p){
 BYTE childOrig[]={0x2B,0xC2},childOn[]={0x03,0xC2};
 ULONG_PTR child=gBase+0x24337EDULL;
 if(!p->available||p->enabled)return p->enabled;
 if(!remote_equal(p->target,p->original,p->length)||!remote_equal(child,childOrig,2)){p->available=0;log_line("[patch] Infinite Ability Points BLOCKED: parent/child bytes changed");return 0;}
 if(!remote_write(child,childOn,2)){log_line("[patch] Infinite Ability Points ERROR: child patch failed");return 0;}
 if(!remote_write(p->target,p->enabledBytes,p->length)){remote_write(child,childOrig,2);log_line("[patch] Infinite Ability Points ERROR: parent patch failed");return 0;}
 p->enabled=1;log_line("[patch] Infinite Ability Points v2 enabled: parent and hidden child patch applied");return 1;
}

static int enable_cave(Patch* p){
 if(!p->available||p->enabled)return p->enabled;
 if(!remote_equal(p->target,p->original,p->length)){p->available=0;log_line("[patch] BLOCKED: original bytes changed before cave apply");return 0;}
 if(!p->cave){
  p->cave=alloc_near(p->target,0x1000);
  if(!p->cave){log_line("[patch] ERROR: VirtualAllocEx near target failed");return 0;}
  BYTE c[256];int n=0;
  if(p->caveKind==1){
   BYTE a[]={0x8B,0xB7,0x30,0x01,0x00,0x00};
   BYTE b[]={0xC7,0x87,0x30,0x01,0x00,0x00,0x40,0x42,0x0F,0x00};
   bytes_copy(c+n,a,6);n+=6;bytes_copy(c+n,b,10);n+=10;
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else if(p->caveKind==2){
   BYTE a[]={0xC7,0x83,0xA8,0x02,0x00,0x00,0x20,0x03,0x00,0x00};
   bytes_copy(c+n,a,10);n+=10;
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else if(p->caveKind==3){
   BYTE a[]={0xC7,0x81,0xF0,0x05,0x00,0x00,0x00,0x00,0xC8,0x42};
   bytes_copy(c+n,a,10);n+=10;
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else if(p->caveKind==4){
   BYTE a[]={0xC7,0x02,0x00,0x00,0x00,0x00,0x33,0xC0,0xC3};
   bytes_copy(c+n,a,9);n+=9;
  }else if(p->caveKind==6){
   BYTE a[]={0x41,0xB8,0x3F,0x42,0x0F,0x00,0x44,0x89,0x03};
   bytes_copy(c+n,a,9);n+=9;
   if(!append_rel_jcc(c+n,p->cave+n,p->target+0x10,0x85))return 0;n+=6;
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else if(p->caveKind==7){
   BYTE a[]={0xF3,0x44,0x0F,0x11,0x49,0x28,0xC7,0x41,0x28,0x00,0x00,0x00,0x00};
   bytes_copy(c+n,a,13);n+=13;
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else if(p->caveKind==8){
   BYTE a[]={0xB8,0xE8,0x03,0x00,0x00};
   bytes_copy(c+n,a,5);n+=5;
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else if(p->caveKind==9){
   BYTE cmpPlayer[]={0x41,0x83,0xBE,0x0C,0x01,0x00,0x00,0x01};
   bytes_copy(c+n,cmpPlayer,8);n+=8;
   int jnePlayer=n;c[n++]=0x75;c[n++]=0;
   BYTE setPlayer[]={0x41,0xC7,0x06,0x3F,0x42,0x0F,0x00};
   bytes_copy(c+n,setPlayer,7);n+=7;
   int jmpLoad=n;c[n++]=0xEB;c[n++]=0;
   int enemyLabel=n;
   BYTE cmpEnemy[]={0x41,0x83,0xBE,0x0C,0x01,0x00,0x00,0x00};
   bytes_copy(c+n,cmpEnemy,8);n+=8;
   int jneEnemy=n;c[n++]=0x75;c[n++]=0;
   BYTE setEnemy[]={0x41,0xC7,0x06,0x00,0x00,0x00,0x00};
   bytes_copy(c+n,setEnemy,7);n+=7;
   int loadLabel=n;
   BYTE load[]={0x66,0x41,0x0F,0x6E,0x0E};
   bytes_copy(c+n,load,5);n+=5;
   c[jnePlayer+1]=(BYTE)(enemyLabel-(jnePlayer+2));
   c[jmpLoad+1]=(BYTE)(loadLabel-(jmpLoad+2));
   c[jneEnemy+1]=(BYTE)(loadLabel-(jneEnemy+2));
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else if(p->caveKind==10){
   BYTE a[]={0x0F,0x2F,0x40,0x50,0xC7,0x40,0x50,0x00,0x00,0x7A,0x44};
   bytes_copy(c+n,a,11);n+=11;
   if(!append_rel_jcc(c+n,p->cave+n,p->target-0x36,0x82))return 0;n+=6;
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else if(p->caveKind==11){
   BYTE a[]={0xB8,0x61,0x79,0xFE,0xFF};
   bytes_copy(c+n,a,5);n+=5;
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else if(p->caveKind==12){
   BYTE a[]={0x41,0x81,0xC0,0x40,0x1F,0x00,0x00,0x44,0x89,0x87,0xB8,0x00,0x00,0x00};
   bytes_copy(c+n,a,14);n+=14;
   if(!append_rel_jmp(c+n,p->cave+n,p->target+p->length))return 0;n+=5;
  }else return 0;
  SIZE_T wrote=0;
  if(!WriteProcessMemory(gProcess,(LPVOID)p->cave,c,(SIZE_T)n,&wrote)||wrote!=(SIZE_T)n){log_line("[patch] ERROR: cave WriteProcessMemory failed");return 0;}
  FlushInstructionCache(gProcess,(LPCVOID)p->cave,(SIZE_T)n);
 }
 BYTE j[16];
 if(!make_rel_jmp(j,p->target,p->cave,p->length))return 0;
 if(!remote_write(p->target,j,p->length))return 0;
 p->enabled=1;log_line("[patch] cave feature enabled");return 1;
}

static int disable_patch(Patch* p){
 if(!p->enabled)return 1;
 if(!process_alive_handle())return 0;
 if(p->caveKind==5){
  BYTE childOrig[]={0x2B,0xC2};
  ULONG_PTR child=gBase+0x24337EDULL;
  if(!remote_write(p->target,p->original,p->length)){log_line("[patch] Infinite Ability Points ERROR: parent restore failed");return 0;}
  if(!remote_write(child,childOrig,2)){log_line("[patch] Infinite Ability Points ERROR: child restore failed");return 0;}
  p->enabled=0;log_line("[patch] Infinite Ability Points restored parent and child bytes");return 1;
 }
 if(!remote_write(p->target,p->original,p->length)){log_line("[patch] ERROR: restore failed");return 0;}
 p->enabled=0;log_line("[patch] restored original bytes");return 1;
}

static int toggle_patch(Patch* p){
 if(!p->available)return 0;
 if(p->enabled)return disable_patch(p);
 if(p->caveKind==5)return enable_ability_points(p);
 if(p->caveKind)return enable_cave(p);
 if(!remote_equal(p->target,p->original,p->length)){p->available=0;log_line("[patch] BLOCKED: original bytes changed before apply");return 0;}
 if(remote_write(p->target,p->enabledBytes,p->length)){p->enabled=1;log_line("[patch] byte patch enabled");return 1;}
 log_line("[patch] ERROR: byte patch write failed");return 0;
}

static void restore_teleport_apply_hook(void){
 if(gTeleportApplyInstalled&&process_alive_handle()){
  if(remote_write(gTeleportApplyTarget,gTeleportApplyOriginal,8))log_line("[teleport] live character transform hook restored original bytes");
  else log_line("[teleport] ERROR: live character transform hook restore failed");
 }
 gTeleportApplyInstalled=0;gTeleportApplyPending=0;gTeleportApplyPolls=0;
}

static int build_teleport_apply_cave(void){
 if(gTeleportApplyCave)return 1;
 gTeleportApplyCave=alloc_near(gTeleportApplyTarget,0x1000);
 if(!gTeleportApplyCave){log_line("[teleport] ERROR: character transform near cave allocation failed");return 0;}
 gTeleportApplyXYZ=gTeleportApplyCave+0x300;
 gTeleportApplyCount=gTeleportApplyCave+0x30C;
 gTeleportApplyDone=gTeleportApplyCave+0x310;

 BYTE c[256];int n=0;
 BYTE orig1[]={0x0F,0x28,0x52,0x50};
 bytes_copy(c+n,orig1,4);n+=4;
 c[n++]=0x50; /* push rax */

 BYTE cmpCount[]={0x83,0x3D,0,0,0,0,0x00};
 bytes_copy(c+n,cmpCount,7);
 if(!append_rip_disp(c+n+2,gTeleportApplyCave+n+7,gTeleportApplyCount))return 0;
 n+=7;
 int jeSkip=n;c[n++]=0x74;c[n++]=0;

 BYTE loadX[]={0x8B,0x05,0,0,0,0};bytes_copy(c+n,loadX,6);
 if(!append_rip_disp(c+n+2,gTeleportApplyCave+n+6,gTeleportApplyXYZ))return 0;n+=6;
 BYTE saveX[]={0x89,0x42,0x50};bytes_copy(c+n,saveX,3);n+=3;
 BYTE loadY[]={0x8B,0x05,0,0,0,0};bytes_copy(c+n,loadY,6);
 if(!append_rip_disp(c+n+2,gTeleportApplyCave+n+6,gTeleportApplyXYZ+4))return 0;n+=6;
 BYTE saveY[]={0x89,0x42,0x54};bytes_copy(c+n,saveY,3);n+=3;
 BYTE loadZ[]={0x8B,0x05,0,0,0,0};bytes_copy(c+n,loadZ,6);
 if(!append_rip_disp(c+n+2,gTeleportApplyCave+n+6,gTeleportApplyXYZ+8))return 0;n+=6;
 BYTE saveZ[]={0x89,0x42,0x58};bytes_copy(c+n,saveZ,3);n+=3;

 BYTE decCount[]={0xFF,0x0D,0,0,0,0};bytes_copy(c+n,decCount,6);
 if(!append_rip_disp(c+n+2,gTeleportApplyCave+n+6,gTeleportApplyCount))return 0;n+=6;
 int jneSkip=n;c[n++]=0x75;c[n++]=0;
 BYTE setDone[]={0xC7,0x05,0,0,0,0,0x01,0x00,0x00,0x00};bytes_copy(c+n,setDone,10);
 if(!append_rip_disp(c+n+2,gTeleportApplyCave+n+10,gTeleportApplyDone))return 0;n+=10;

 int skipLabel=n;
 c[jeSkip+1]=(BYTE)(skipLabel-(jeSkip+2));
 c[jneSkip+1]=(BYTE)(skipLabel-(jneSkip+2));
 c[n++]=0x58; /* pop rax */
 BYTE orig2[]={0x49,0x89,0x5B,0x08};bytes_copy(c+n,orig2,4);n+=4;
 if(!append_rel_jmp(c+n,gTeleportApplyCave+n,gTeleportApplyTarget+8))return 0;n+=5;

 SIZE_T wrote=0;
 if(!WriteProcessMemory(gProcess,(LPVOID)gTeleportApplyCave,c,(SIZE_T)n,&wrote)||wrote!=(SIZE_T)n){log_line("[teleport] ERROR: character transform cave write failed");return 0;}
 BYTE zero[32];bytes_fill(zero,0,sizeof(zero));
 if(!WriteProcessMemory(gProcess,(LPVOID)gTeleportApplyXYZ,zero,sizeof(zero),&wrote)||wrote!=sizeof(zero)){log_line("[teleport] ERROR: character transform state init failed");return 0;}
 FlushInstructionCache(gProcess,(LPCVOID)gTeleportApplyCave,(SIZE_T)n);
 return 1;
}

static int arm_teleport_apply(const DWORD xyz[3]){
 if(!gBuildSupported||!gTeleportApplyAvailable)return 0;
 if(!build_teleport_apply_cave())return 0;
 if(!gTeleportApplyInstalled&& !remote_equal(gTeleportApplyTarget,gTeleportApplyOriginal,8)){
  gTeleportApplyAvailable=0;log_line("[teleport] BLOCKED: live character transform bytes changed before hook install");return 0;
 }
 SIZE_T wrote=0;
 if(!WriteProcessMemory(gProcess,(LPVOID)gTeleportApplyXYZ,xyz,12,&wrote)||wrote!=12){log_num("[teleport] ERROR: target coordinate state write failed, Windows error ",GetLastError());return 0;}
 DWORD count=30,done=0;
 if(!WriteProcessMemory(gProcess,(LPVOID)gTeleportApplyCount,&count,4,&wrote)||wrote!=4)return 0;
 if(!WriteProcessMemory(gProcess,(LPVOID)gTeleportApplyDone,&done,4,&wrote)||wrote!=4)return 0;
 if(!gTeleportApplyInstalled){
  BYTE j[16];if(!make_rel_jmp(j,gTeleportApplyTarget,gTeleportApplyCave,8))return 0;
  if(!remote_write(gTeleportApplyTarget,j,8)){log_line("[teleport] ERROR: live character transform hook install failed");return 0;}
  gTeleportApplyInstalled=1;
 }
 gTeleportApplyPending=1;gTeleportApplyPolls=0;
 log_line("[teleport] teleport armed through verified live character transform; forcing target for 30 transform updates");
 return 1;
}

static void restore_teleport_hook(void){
 if(gTeleportInstalled&&process_alive_handle()){
  if(remote_write(gTeleportTarget,gTeleportOriginal,7))log_line("[teleport] waypoint observer restored original bytes");
  else log_line("[teleport] ERROR: waypoint observer restore failed");
 }
 gTeleportInstalled=0;gTeleportHasCapture=0;gTeleportLastSeq=0;
}

static int build_teleport_observer(void){
 if(gTeleportCave)return 1;
 gTeleportCave=alloc_near(gTeleportTarget,0x1000);
 if(!gTeleportCave){log_line("[teleport] ERROR: near cave allocation failed");return 0;}
 gTeleportPlayerPtr=gTeleportCave+0x300;
 gTeleportWaypointXYZ=gTeleportCave+0x308;
 gTeleportCaptureSeq=gTeleportCave+0x318;

 BYTE c[256];int n=0;
 BYTE orig[]={0x48,0x8B,0x92,0x90,0x00,0x00,0x00};
 bytes_copy(c+n,orig,7);n+=7;
 BYTE testRdx[]={0x48,0x85,0xD2};
 bytes_copy(c+n,testRdx,3);n+=3;
 int jeReturn=n;c[n++]=0x0F;c[n++]=0x84;int jeDisp=n;n+=4;

 c[n++]=0x50; /* push rax: preserve game state while capturing */
 BYTE leaPlayer[]={0x48,0x8D,0x82,0xF4,0x00,0x00,0x00};
 bytes_copy(c+n,leaPlayer,7);n+=7;
 BYTE savePlayer[]={0x48,0x89,0x05,0,0,0,0};
 bytes_copy(c+n,savePlayer,7);
 if(!append_rip_disp(c+n+3,gTeleportCave+n+7,gTeleportPlayerPtr))return 0;
 n+=7;

 /* After push rax, original rsp+30/34/38 lives at rsp+38/3c/40. */
 BYTE loadX[]={0x8B,0x44,0x24,0x38};bytes_copy(c+n,loadX,4);n+=4;
 BYTE saveX[]={0x89,0x05,0,0,0,0};bytes_copy(c+n,saveX,6);
 if(!append_rip_disp(c+n+2,gTeleportCave+n+6,gTeleportWaypointXYZ))return 0;n+=6;
 BYTE loadY[]={0x8B,0x44,0x24,0x3C};bytes_copy(c+n,loadY,4);n+=4;
 BYTE saveY[]={0x89,0x05,0,0,0,0};bytes_copy(c+n,saveY,6);
 if(!append_rip_disp(c+n+2,gTeleportCave+n+6,gTeleportWaypointXYZ+4))return 0;n+=6;
 BYTE loadZ[]={0x8B,0x44,0x24,0x40};bytes_copy(c+n,loadZ,4);n+=4;
 BYTE saveZ[]={0x89,0x05,0,0,0,0};bytes_copy(c+n,saveZ,6);
 if(!append_rip_disp(c+n+2,gTeleportCave+n+6,gTeleportWaypointXYZ+8))return 0;n+=6;
 BYTE incSeq[]={0xFF,0x05,0,0,0,0};bytes_copy(c+n,incSeq,6);
 if(!append_rip_disp(c+n+2,gTeleportCave+n+6,gTeleportCaptureSeq))return 0;n+=6;
 c[n++]=0x58; /* pop rax */

 int returnLabel=n;
 if(!append_rel_jmp(c+n,gTeleportCave+n,gTeleportTarget+7))return 0;n+=5;
 *(int*)(c+jeDisp)=(int)((long long)(gTeleportCave+returnLabel)-(long long)(gTeleportCave+jeReturn+6));

 SIZE_T wrote=0;
 if(!WriteProcessMemory(gProcess,(LPVOID)gTeleportCave,c,(SIZE_T)n,&wrote)||wrote!=(SIZE_T)n){log_line("[teleport] ERROR: observer cave write failed");return 0;}
 BYTE zero[32];bytes_fill(zero,0,sizeof(zero));
 if(!WriteProcessMemory(gProcess,(LPVOID)gTeleportPlayerPtr,zero,sizeof(zero),&wrote)||wrote!=sizeof(zero)){log_line("[teleport] ERROR: observer state init failed");return 0;}
 FlushInstructionCache(gProcess,(LPCVOID)gTeleportCave,(SIZE_T)n);
 return 1;
}

static int install_teleport_observer(void){
 if(gTeleportInstalled)return 1;
 if(!gBuildSupported||!gTeleportAvailable)return 0;
 if(!remote_equal(gTeleportTarget,gTeleportOriginal,7)){gTeleportAvailable=0;log_line("[teleport] BLOCKED: original waypoint bytes changed before observer install");return 0;}
 if(!build_teleport_observer())return 0;
 BYTE zeroState[32];bytes_fill(zeroState,0,sizeof(zeroState));SIZE_T resetWrote=0;
 if(!WriteProcessMemory(gProcess,(LPVOID)gTeleportPlayerPtr,zeroState,sizeof(zeroState),&resetWrote)||resetWrote!=sizeof(zeroState)){log_line("[teleport] ERROR: observer state reset failed");return 0;}
 gTeleportHasCapture=0;gTeleportLastSeq=0;
 BYTE j[16];
 if(!make_rel_jmp(j,gTeleportTarget,gTeleportCave,7))return 0;
 if(!remote_write(gTeleportTarget,j,7)){log_line("[teleport] ERROR: waypoint observer install failed");return 0;}
 gTeleportInstalled=1;
 log_line("[teleport] persistent waypoint observer installed; waiting to capture map waypoint data");
 return 1;
}

static int sane_float_bits(DWORD u){return (u&0x7F800000UL)!=0x7F800000UL;}

static int read_captured_waypoint(ULONG_PTR* player,DWORD xyz[3],DWORD* seqOut){
 if(!gTeleportInstalled||!gTeleportCave)return 0;
 for(int tries=0;tries<4;tries++){
  DWORD a=0,b=0;ULONG_PTR p=0;DWORD v[3];
  if(!remote_read(gTeleportCaptureSeq,(BYTE*)&a,4)||a==0)return 0;
  if(!remote_read(gTeleportPlayerPtr,(BYTE*)&p,sizeof(p)))return 0;
  if(!remote_read(gTeleportWaypointXYZ,(BYTE*)v,12))return 0;
  if(!remote_read(gTeleportCaptureSeq,(BYTE*)&b,4))return 0;
  if(a!=b)continue;
  if(p<0x10000ULL||!sane_float_bits(v[0])||!sane_float_bits(v[1])||!sane_float_bits(v[2]))return 0;
  *player=p;xyz[0]=v[0];xyz[1]=v[1];xyz[2]=v[2];*seqOut=b;return 1;
 }
 return 0;
}

static int trigger_waypoint_teleport(void){
 if(!gBuildSupported||!gTeleportAvailable||!gTeleportApplyAvailable)return 0;
 if(!gTeleportInstalled){
  if(!install_teleport_observer())return 0;
  log_line("[teleport] observer was off; open the map, place/move a custom waypoint, then trigger Teleport again");
  return 0;
 }
 ULONG_PTR ignoredPlayer=0;DWORD xyz[3],seq=0;
 if(!read_captured_waypoint(&ignoredPlayer,xyz,&seq)){
  gTeleportHasCapture=0;
  log_line("[teleport] NO WAYPOINT CAPTURED: open the map and place or move a custom waypoint, then try again");
  return 0;
 }
 union {DWORD u;float f;} z;z.u=xyz[2];z.f+=5.0f;xyz[2]=z.u;
 if(!arm_teleport_apply(xyz))return 0;
 gTeleportHasCapture=1;gTeleportLastSeq=seq;
 if(gOverlay)InvalidateRect(gOverlay,NULL,TRUE);
 return 1;
}

static void poll_waypoint_teleport(void){
 if(gTeleportInstalled){
  DWORD seq=0;
  if(remote_read(gTeleportCaptureSeq,(BYTE*)&seq,4)){
   if(seq&&!gTeleportHasCapture){gTeleportHasCapture=1;if(gOverlay)InvalidateRect(gOverlay,NULL,TRUE);}
   if(seq)gTeleportLastSeq=seq;
  }
 }
 if(gTeleportApplyInstalled&&gTeleportApplyPending){
  DWORD done=0;
  if(remote_read(gTeleportApplyDone,(BYTE*)&done,4)&&done){
   gTeleportApplyPending=0;
   log_line("[teleport] TELEPORTED through live character transform (+5 Z safety offset); restoring one-shot transform hook");
   restore_teleport_apply_hook();
   if(gOverlay)InvalidateRect(gOverlay,NULL,TRUE);
  }else if(++gTeleportApplyPolls>=200){
   log_line("[teleport] ERROR: live character transform did not consume teleport within 5 seconds; restoring hook");
   restore_teleport_apply_hook();
   if(gOverlay)InvalidateRect(gOverlay,NULL,TRUE);
  }
 }
}

static void disable_all(void){
 for(int i=0;i<gPatchCount;i++)disable_patch(&gPatches[i]);
 restore_teleport_apply_hook();
 restore_teleport_hook();
}

static int verify_remote_build(void){BYTE dos[64];if(!remote_read(gBase,dos,sizeof(dos))||dos[0]!='M'||dos[1]!='Z')return 0;DWORD peoff=*(DWORD*)(dos+0x3c);BYTE nt[96];if(!remote_read(gBase+peoff,nt,sizeof(nt)))return 0;if(*(DWORD*)nt!=0x00004550UL)return 0;DWORD stamp=*(DWORD*)(nt+8);BYTE* opt=nt+24;DWORD size=*(DWORD*)(opt+56);return stamp==EXPECTED_TIMESTAMP&&size==EXPECTED_IMAGE_SIZE;}

static void make_line(WCHAR* out,DWORD cap,const WCHAR* name,const WCHAR* status){wcopy(out,cap,name);wcat(out,cap,L"   ");wcat(out,cap,status);}
static LRESULT CALLBACK OverlayProc(HWND h,UINT m,WPARAM w,LPARAM l){
 (void)w;(void)l;
 if(m==WM_ERASEBKGND)return 1;
 if(m==WM_PAINT){
  PAINTSTRUCT ps;HDC dc=BeginPaint(h,&ps);
  RECT bg={0,0,720,650};FillRect(dc,&bg,(HBRUSH)GetStockObject(BLACK_BRUSH));
  SetBkMode(dc,TRANSPARENT);SelectObject(dc,GetStockObject(DEFAULT_GUI_FONT));
  RECT r={18,12,700,36};SetTextColor(dc,0x00FFFFFF);
  DrawTextW(dc,L"Luvvy Odyssey External Mod Menu v4.2.2  |  F10 close",-1,&r,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  RECT b={18,38,700,60};SetTextColor(dc,gBuildSupported?0x008CFF78:0x006060FF);
  DrawTextW(dc,gBuildSupported?L"EXACT BUILD VERIFIED | EXTERNAL ONLY | NO DLL INJECTION":L"BLOCKED: unsupported runtime build",-1,&b,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);

  for(int i=0;i<gPatchCount+2;i++){
   WCHAR line[220];const WCHAR* name;const WCHAR* st=L"";
   if(i<gPatchCount){
    name=gPatches[i].name;
    if(!gBuildSupported||!gPatches[i].available)st=L"[BLOCKED]";
    else st=gPatches[i].enabled?L"[ON]":L"[OFF]";
   }else if(i==gPatchCount){
    name=L"Teleport to Custom Map Waypoint  [ACTION]";
    if(!gBuildSupported||!gTeleportAvailable||!gTeleportApplyAvailable)st=L"[BLOCKED]";
    else if(gTeleportApplyPending)st=L"[TELEPORTING]";
    else if(!gTeleportInstalled)st=L"[ARM CAPTURE]";
    else st=gTeleportHasCapture?L"[WAYPOINT CAPTURED]":L"[WAITING FOR WAYPOINT]";
   }else{
    name=L"Disable All";
   }
   make_line(line,220,name,st);
   RECT rr={28,70+i*27,700,95+i*27};
   SetTextColor(dc,i==gSelected?0x008CFF78:0x00FFFFFF);
   DrawTextW(dc,line,-1,&rr,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  }
  RECT f={18,610,700,638};SetTextColor(dc,0x00C0C0C0);
  DrawTextW(dc,L"Up/Down select   Enter toggle/action   F10 hide   |   Teleport: Enter once to arm capture",-1,&f,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  EndPaint(h,&ps);return 0;
 }
 return DefWindowProcW(h,m,w,l);
}
static int create_overlay(void){
 WNDCLASSEXW wc;bytes_fill((BYTE*)&wc,0,sizeof(wc));wc.cbSize=sizeof(wc);wc.lpfnWndProc=OverlayProc;wc.hInstance=gSelf;wc.lpszClassName=L"LuvvyOdysseyExternalOverlay";RegisterClassExW(&wc);
 gOverlay=CreateWindowExW(WS_EX_TOPMOST|WS_EX_TOOLWINDOW|WS_EX_LAYERED|WS_EX_NOACTIVATE|WS_EX_TRANSPARENT,L"LuvvyOdysseyExternalOverlay",L"Luvvy Odyssey External",WS_POPUP,40,40,720,650,NULL,NULL,gSelf,NULL);
 if(!gOverlay)return 0;SetLayeredWindowAttributes(gOverlay,0,220,LWA_ALPHA);return 1;
}
static void reposition(void){
 if(!gOverlay)return;if(!gGameWnd||!IsWindowVisible(gGameWnd))find_game_window();if(!gGameWnd)return;
 RECT r;if(!GetWindowRect(gGameWnd,&r))return;
 SetWindowPos(gOverlay,HWND_TOPMOST,r.left+35,r.top+35,720,650,SWP_NOACTIVATE);
}
static void toggle_selected(void){
 if(gSelected<gPatchCount){
  if(gBuildSupported)toggle_patch(&gPatches[gSelected]);
 }else if(gSelected==gPatchCount){
  if(gBuildSupported)trigger_waypoint_teleport();
 }else{
  disable_all();
 }
 if(gOverlay)InvalidateRect(gOverlay,NULL,TRUE);
}

void WINAPI ExternalMenuEntry(void){
 gSelf=(HINSTANCE)0;WCHAR selfPath[1024];GetModuleFileNameW(NULL,selfPath,1024);gSelf=(HINSTANCE)GetModuleHandleW(NULL);
 log_line("[external] v4.2.2 external menu started; startup is read-only until user explicitly enables a feature");HINSTANCE r=ShellExecuteW(NULL,L"open",L"steam://rungameid/812140",NULL,NULL,1);if((ULONG_PTR)r<=32ULL){log_line("[external] ERROR: Steam protocol launch failed");ExitProcess(3);}log_line("[external] Steam launch requested; waiting for final stable game process");
 DWORD candidate=0,stable=0;for(DWORD t=0;t<1800;t++){DWORD pid=find_process();if(!pid){candidate=0;stable=0;Sleep(1000);continue;}if(pid!=candidate){candidate=pid;stable=0;log_num("[external] candidate ACOdyssey PID ",pid);}ULONG_PTR up=remote_module_base(pid,L"uplay_r1_loader64.dll");if(!up||!has_large_game_window(pid)){stable=0;Sleep(1000);continue;}stable++;if(stable==1)log_line("[external] Ubisoft loader and visible game window present; beginning 20s stability timer");if(stable<20){Sleep(1000);continue;}gPid=pid;gBase=remote_module_base(pid,L"ACOdyssey.exe");if(!gBase){stable=0;Sleep(1000);continue;}gProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ|SYNCHRONIZE,FALSE,pid);if(!gProcess){log_num("[external] OpenProcess failed for candidate, Windows error ",GetLastError());candidate=0;stable=0;Sleep(1000);continue;}break;}
 if(!gProcess){log_line("[external] ERROR: timed out waiting for stable ACOdyssey.exe");ExitProcess(5);}log_line("[external] attached to stable game process after Ubisoft startup handoff");gBuildSupported=verify_remote_build();log_line(gBuildSupported?"[external] runtime build marker verified":"[external] BLOCKED: runtime build marker mismatch");if(gBuildSupported)resolve_patches();
 if(!create_overlay()){log_line("[overlay] ERROR: external CreateWindowExW failed");CloseHandle(gProcess);ExitProcess(6);}log_line("[overlay] external F10 overlay initialized; game process has not been modified");
 DWORD ticks=0;MSG msg;while(gRunning&&process_alive_handle()){while(PeekMessageW(&msg,NULL,0,0,PM_REMOVE)){TranslateMessage(&msg);DispatchMessageW(&msg);}poll_waypoint_teleport();if(GetAsyncKeyState(VK_F10)&1){gMenuOpen=!gMenuOpen;ShowWindow(gOverlay,gMenuOpen?SW_SHOWNOACTIVATE:SW_HIDE);if(gMenuOpen){reposition();InvalidateRect(gOverlay,NULL,TRUE);}}if(gMenuOpen){if(GetAsyncKeyState(VK_UP)&1){gSelected--;if(gSelected<0)gSelected=gPatchCount+1;InvalidateRect(gOverlay,NULL,TRUE);}if(GetAsyncKeyState(VK_DOWN)&1){gSelected++;if(gSelected>gPatchCount+1)gSelected=0;InvalidateRect(gOverlay,NULL,TRUE);}if(GetAsyncKeyState(VK_RETURN)&1)toggle_selected();if(GetAsyncKeyState(VK_ESCAPE)&1){gMenuOpen=0;ShowWindow(gOverlay,SW_HIDE);}if((ticks++%20)==0)reposition();}Sleep(25);}if(process_alive_handle())disable_all();if(gOverlay)DestroyWindow(gOverlay);if(gProcess)CloseHandle(gProcess);log_line("[external] game process ended; external menu exiting");ExitProcess(0);
}
