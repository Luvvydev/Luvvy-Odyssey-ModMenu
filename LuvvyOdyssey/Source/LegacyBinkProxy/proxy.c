#include "winmini.h"

static HMODULE gSelf;

static DWORD wlen(const WCHAR* s){ DWORD n=0; while(s && s[n]) n++; return n; }
static void append_w(WCHAR* out,DWORD cap,const WCHAR* s){
 DWORD n=wlen(out),i=0; while(s && s[i] && n+i+1<cap){out[n+i]=s[i];i++;} out[n+i]=0;
}
static void build_sibling_path(WCHAR* out,DWORD cap,const WCHAR* name){
 DWORD n=GetModuleFileNameW(gSelf,out,cap);
 if(!n || n>=cap){out[0]=0;return;}
 while(n>0 && out[n-1]!=L'\\' && out[n-1]!=L'/') n--;
 out[n]=0; append_w(out,cap,name);
}
static void build_log_path(WCHAR* out, DWORD cap){ build_sibling_path(out,cap,L"LuvvyProxy.log"); }
static void log_line(const char* s){
 WCHAR path[1024]; path[0]=0; build_log_path(path,1024);
 HANDLE h=CreateFileW(path,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
 if(h==INVALID_HANDLE_VALUE) return;
 SetFilePointer(h,0,NULL,FILE_END);
 DWORD n=0; while(s[n]) n++;
 DWORD wr=0; WriteFile(h,s,n,&wr,NULL); WriteFile(h,"\r\n",2,&wr,NULL); CloseHandle(h);
}
static void log_winerr(const char* prefix,DWORD e){
 char b[160]; DWORD p=0,i=0; while(prefix[p] && p+1<sizeof(b)){b[p]=prefix[p];p++;}
 char d[16]; if(e==0)d[i++]='0'; while(e && i<sizeof(d)){d[i++]=(char)('0'+(e%10));e/=10;}
 while(i && p+1<sizeof(b)) b[p++]=d[--i]; b[p]=0; log_line(b);
}
static DWORD WINAPI LoaderThread(LPVOID p){
 (void)p;
 log_line("[proxy] process attach: bink proxy loaded");
 log_line("[proxy] waiting for Ubisoft session loader before loading mod");
 int seen=0;
 for(int i=0;i<300;i++){
  if(GetModuleHandleW(L"uplay_r1_loader64.dll")){seen=1;break;}
  Sleep(100);
 }
 if(seen) log_line("[proxy] Ubisoft session loader detected");
 else log_line("[proxy] WARNING: Ubisoft session loader not detected after 30s; continuing");

 /* Do not inject our UI during the launcher's/anti-tamper bootstrap window. */
 Sleep(5000);

 WCHAR modPath[1024]; modPath[0]=0; build_sibling_path(modPath,1024,L"LuvvyOdysseyMod.dll");
 if(!modPath[0]){log_line("[proxy] ERROR: could not build absolute mod DLL path");return 0;}
 HMODULE m=LoadLibraryW(modPath);
 if(m) log_line("[proxy] mod DLL loaded from absolute game path");
 else log_winerr("[proxy] ERROR: LuvvyOdysseyMod.dll LoadLibraryW failed, Windows error ",GetLastError());
 return 0;
}
BOOL WINAPI DllMain(HINSTANCE h,DWORD reason,LPVOID reserved){
 (void)reserved;
 if(reason==DLL_PROCESS_ATTACH){
  gSelf=(HMODULE)h;
  DisableThreadLibraryCalls((HMODULE)h);
  HANDLE t=CreateThread(NULL,0,LoaderThread,NULL,0,NULL);
  if(t) CloseHandle(t);
 }
 return TRUE;
}
