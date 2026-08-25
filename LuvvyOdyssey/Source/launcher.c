typedef void* HINSTANCE;
typedef void* HWND;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef unsigned short WCHAR;
typedef const WCHAR* LPCWSTR;
#define WINAPI __stdcall
#define NULL ((void*)0)
__declspec(dllimport) DWORD WINAPI GetModuleFileNameW(HINSTANCE,WCHAR*,DWORD);
__declspec(dllimport) void WINAPI ExitProcess(UINT);
__declspec(dllimport) HINSTANCE WINAPI ShellExecuteW(HWND,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,int);

static DWORD wlen(const WCHAR* s){DWORD n=0;while(s&&s[n])n++;return n;}
static void append_w(WCHAR* d,DWORD cap,const WCHAR* s){DWORD n=wlen(d),i=0;while(s&&s[i]&&n+i+1<cap){d[n+i]=s[i];i++;}d[n+i]=0;}
void WINAPI LauncherEntry(void){
 WCHAR path[1024]; DWORD n=GetModuleFileNameW(NULL,path,1024);
 if(!n||n>=1024) ExitProcess(2);
 while(n>0&&path[n-1]!=L'\\'&&path[n-1]!=L'/')n--;
 path[n]=0; append_w(path,1024,L"Luvvy Odyssey Launcher.bat");
 HINSTANCE r=ShellExecuteW(NULL,L"open",path,NULL,NULL,1);
 ExitProcess(((unsigned long long)r<=32ULL)?3:0);
}
