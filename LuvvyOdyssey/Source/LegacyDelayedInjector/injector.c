typedef void* HANDLE;
typedef void* HINSTANCE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef unsigned long DWORD;
typedef unsigned long long ULONG_PTR;
typedef unsigned long long SIZE_T;
typedef unsigned short WORD;
typedef unsigned short WCHAR;
typedef const WCHAR* LPCWSTR;
typedef const char* LPCSTR;
typedef unsigned int UINT;
typedef int BOOL;
typedef long LONG;
typedef long long LONG_PTR;
typedef LONG_PTR LPARAM;
typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE)(LPVOID);
typedef BOOL (__stdcall *WNDENUMPROC)(HWND,LPARAM);
typedef struct tagRECT { LONG left; LONG top; LONG right; LONG bottom; } RECT;
#define WINAPI __stdcall
#define TRUE 1
#define FALSE 0
#define NULL ((void*)0)
#define INVALID_HANDLE_VALUE ((HANDLE)(long long)-1)
#define MAX_PATH 260
#define TH32CS_SNAPPROCESS 0x00000002UL
#define TH32CS_SNAPMODULE 0x00000008UL
#define TH32CS_SNAPMODULE32 0x00000010UL
#define PROCESS_CREATE_THREAD 0x0002UL
#define PROCESS_QUERY_INFORMATION 0x0400UL
#define PROCESS_VM_OPERATION 0x0008UL
#define PROCESS_VM_WRITE 0x0020UL
#define PROCESS_VM_READ 0x0010UL
#define SYNCHRONIZE 0x00100000UL
#define MEM_COMMIT 0x1000UL
#define MEM_RESERVE 0x2000UL
#define MEM_RELEASE 0x8000UL
#define PAGE_READWRITE 0x04UL
#define WAIT_OBJECT_0 0x00000000UL
#define WAIT_TIMEOUT 0x00000102UL
#define STILL_ACTIVE 259UL
#define GENERIC_WRITE 0x40000000UL
#define FILE_SHARE_READ 0x00000001UL
#define OPEN_ALWAYS 4UL
#define FILE_ATTRIBUTE_NORMAL 0x00000080UL
#define FILE_END 2UL

typedef struct tagPROCESSENTRY32W {
 DWORD dwSize;
 DWORD cntUsage;
 DWORD th32ProcessID;
 ULONG_PTR th32DefaultHeapID;
 DWORD th32ModuleID;
 DWORD cntThreads;
 DWORD th32ParentProcessID;
 LONG pcPriClassBase;
 DWORD dwFlags;
 WCHAR szExeFile[MAX_PATH];
} PROCESSENTRY32W;

typedef struct tagMODULEENTRY32W {
 DWORD dwSize;
 DWORD th32ModuleID;
 DWORD th32ProcessID;
 DWORD GlblcntUsage;
 DWORD ProccntUsage;
 unsigned char* modBaseAddr;
 DWORD modBaseSize;
 HMODULE hModule;
 WCHAR szModule[256];
 WCHAR szExePath[MAX_PATH];
} MODULEENTRY32W;

__declspec(dllimport) HANDLE WINAPI CreateToolhelp32Snapshot(DWORD,DWORD);
__declspec(dllimport) BOOL WINAPI Process32FirstW(HANDLE,PROCESSENTRY32W*);
__declspec(dllimport) BOOL WINAPI Process32NextW(HANDLE,PROCESSENTRY32W*);
__declspec(dllimport) BOOL WINAPI Module32FirstW(HANDLE,MODULEENTRY32W*);
__declspec(dllimport) BOOL WINAPI Module32NextW(HANDLE,MODULEENTRY32W*);
__declspec(dllimport) HANDLE WINAPI OpenProcess(DWORD,BOOL,DWORD);
__declspec(dllimport) BOOL WINAPI GetExitCodeProcess(HANDLE,DWORD*);
__declspec(dllimport) LPVOID WINAPI VirtualAllocEx(HANDLE,LPVOID,SIZE_T,DWORD,DWORD);
__declspec(dllimport) BOOL WINAPI VirtualFreeEx(HANDLE,LPVOID,SIZE_T,DWORD);
__declspec(dllimport) BOOL WINAPI WriteProcessMemory(HANDLE,LPVOID,LPCVOID,SIZE_T,SIZE_T*);
__declspec(dllimport) HANDLE WINAPI CreateRemoteThread(HANDLE,void*,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,DWORD*);
__declspec(dllimport) DWORD WINAPI WaitForSingleObject(HANDLE,DWORD);
__declspec(dllimport) HMODULE WINAPI GetModuleHandleW(LPCWSTR);
__declspec(dllimport) LPVOID WINAPI GetProcAddress(HMODULE,LPCSTR);
__declspec(dllimport) DWORD WINAPI GetModuleFileNameW(HMODULE,WCHAR*,DWORD);
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

static DWORD wlen(const WCHAR* s){DWORD n=0;while(s&&s[n])n++;return n;}
static DWORD alen(const char* s){DWORD n=0;while(s&&s[n])n++;return n;}
static void wcopy(WCHAR* d,DWORD cap,const WCHAR* s){DWORD i=0;if(!cap)return;while(s&&s[i]&&i+1<cap){d[i]=s[i];i++;}d[i]=0;}
static void wcat(WCHAR* d,DWORD cap,const WCHAR* s){DWORD n=wlen(d),i=0;while(s&&s[i]&&n+i+1<cap){d[n+i]=s[i];i++;}d[n+i]=0;}
static WCHAR lowerw(WCHAR c){return (c>=L'A'&&c<=L'Z')?(WCHAR)(c+32):c;}
static int weq_ci(const WCHAR* a,const WCHAR* b){DWORD i=0;while(a[i]&&b[i]){if(lowerw(a[i])!=lowerw(b[i]))return 0;i++;}return a[i]==0&&b[i]==0;}

static void base_dir(WCHAR* out,DWORD cap){
 DWORD n=GetModuleFileNameW(NULL,out,cap);if(!n||n>=cap){out[0]=0;return;}
 while(n>0&&out[n-1]!=L'\\'&&out[n-1]!=L'/')n--;out[n]=0;
}
static void log_line(const char* s){
 WCHAR p[1024];base_dir(p,1024);wcat(p,1024,L"LuvvyInjector.log");
 HANDLE h=CreateFileW(p,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);if(h==INVALID_HANDLE_VALUE)return;
 SetFilePointer(h,0,NULL,FILE_END);DWORD wr=0,n=alen(s);WriteFile(h,s,n,&wr,NULL);WriteFile(h,"\r\n",2,&wr,NULL);CloseHandle(h);
}
static void log_num(const char* prefix,DWORD v){
 char b[192];DWORD p=0,i=0;while(prefix[p]&&p+1<sizeof(b)){b[p]=prefix[p];p++;}
 char d[16];if(v==0)d[i++]='0';while(v&&i<sizeof(d)){d[i++]=(char)('0'+(v%10));v/=10;}
 while(i&&p+1<sizeof(b))b[p++]=d[--i];b[p]=0;log_line(b);
}
static DWORD find_process(void){
 HANDLE s=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);if(s==INVALID_HANDLE_VALUE)return 0;
 PROCESSENTRY32W e;e.dwSize=sizeof(e);DWORD pid=0;
 if(Process32FirstW(s,&e)){do{if(weq_ci(e.szExeFile,L"ACOdyssey.exe")){pid=e.th32ProcessID;break;}e.dwSize=sizeof(e);}while(Process32NextW(s,&e));}
 CloseHandle(s);return pid;
}
static int process_alive(DWORD pid){
 HANDLE h=OpenProcess(SYNCHRONIZE|PROCESS_QUERY_INFORMATION,FALSE,pid);if(!h)return 0;DWORD code=0;BOOL ok=GetExitCodeProcess(h,&code);CloseHandle(h);return ok&&code==STILL_ACTIVE;
}
static ULONG_PTR remote_module_base(DWORD pid,const WCHAR* name){
 for(int attempt=0;attempt<5;attempt++){
  HANDLE s=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32,pid);if(s==INVALID_HANDLE_VALUE){Sleep(50);continue;}
  MODULEENTRY32W m;m.dwSize=sizeof(m);ULONG_PTR base=0;
  if(Module32FirstW(s,&m)){do{if(weq_ci(m.szModule,name)){base=(ULONG_PTR)m.modBaseAddr;break;}m.dwSize=sizeof(m);}while(Module32NextW(s,&m));}
  CloseHandle(s);if(base)return base;Sleep(50);
 }
 return 0;
}
static DWORD gWindowPid=0;static int gWindowFound=0;
static BOOL WINAPI enum_window_cb(HWND h,LPARAM l){
 (void)l;DWORD pid=0;if(!IsWindowVisible(h))return TRUE;GetWindowThreadProcessId(h,&pid);if(pid!=gWindowPid)return TRUE;
 RECT r;if(!GetWindowRect(h,&r))return TRUE;LONG w=r.right-r.left,ht=r.bottom-r.top;if(w>=640&&ht>=360){gWindowFound=1;return FALSE;}return TRUE;
}
static int has_game_window(DWORD pid){gWindowPid=pid;gWindowFound=0;EnumWindows(enum_window_cb,0);return gWindowFound;}
static int inject_into(DWORD pid,const WCHAR* dllPath){
 HANDLE p=OpenProcess(PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ|SYNCHRONIZE,FALSE,pid);
 if(!p){log_num("[injector] ERROR: OpenProcess failed, Windows error ",GetLastError());return 0;}
 HMODULE localKB=GetModuleHandleW(L"kernelbase.dll");if(!localKB){log_line("[injector] ERROR: local kernelbase.dll not found");CloseHandle(p);return 0;}
 LPVOID localLL=GetProcAddress(localKB,"LoadLibraryW");if(!localLL){log_line("[injector] ERROR: local LoadLibraryW not found");CloseHandle(p);return 0;}
 ULONG_PTR remoteKB=remote_module_base(pid,L"kernelbase.dll");if(!remoteKB){log_line("[injector] ERROR: remote kernelbase.dll not found");CloseHandle(p);return 0;}
 ULONG_PTR loadRva=(ULONG_PTR)localLL-(ULONG_PTR)localKB;
 LPTHREAD_START_ROUTINE remoteLL=(LPTHREAD_START_ROUTINE)(remoteKB+loadRva);
 SIZE_T bytes=((SIZE_T)wlen(dllPath)+1)*sizeof(WCHAR);
 LPVOID remoteBuf=VirtualAllocEx(p,NULL,bytes,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
 if(!remoteBuf){log_num("[injector] ERROR: VirtualAllocEx failed, Windows error ",GetLastError());CloseHandle(p);return 0;}
 SIZE_T wrote=0;if(!WriteProcessMemory(p,remoteBuf,dllPath,bytes,&wrote)||wrote!=bytes){log_num("[injector] ERROR: WriteProcessMemory failed, Windows error ",GetLastError());VirtualFreeEx(p,remoteBuf,0,MEM_RELEASE);CloseHandle(p);return 0;}
 HANDLE t=CreateRemoteThread(p,NULL,0,remoteLL,remoteBuf,0,NULL);
 if(!t){log_num("[injector] ERROR: CreateRemoteThread failed, Windows error ",GetLastError());VirtualFreeEx(p,remoteBuf,0,MEM_RELEASE);CloseHandle(p);return 0;}
 DWORD wr=WaitForSingleObject(t,15000);if(wr!=WAIT_OBJECT_0){log_line("[injector] ERROR: remote LoadLibraryW did not finish within 15s");CloseHandle(t);VirtualFreeEx(p,remoteBuf,0,MEM_RELEASE);CloseHandle(p);return 0;}
 CloseHandle(t);VirtualFreeEx(p,remoteBuf,0,MEM_RELEASE);CloseHandle(p);log_line("[injector] remote LoadLibraryW completed");return 1;
}

void WINAPI InjectorEntry(void){
 WCHAR root[1024];base_dir(root,1024);if(!root[0])ExitProcess(2);
 WCHAR dllPath[1024];wcopy(dllPath,1024,root);wcat(dllPath,1024,L"LuvvyOdysseyMod.dll");
 log_line("[injector] v3 external injector started");
 HINSTANCE r=ShellExecuteW(NULL,L"open",L"steam://rungameid/812140",NULL,NULL,1);
 if((ULONG_PTR)r<=32ULL){log_line("[injector] ERROR: Steam protocol launch failed");ExitProcess(3);}
 log_line("[injector] Steam launch requested; waiting for final stable ACOdyssey.exe");
 DWORD candidate=0;DWORD stableTicks=0;
 for(DWORD total=0;total<1800;total++){
  DWORD pid=find_process();
  if(!pid){candidate=0;stableTicks=0;Sleep(1000);continue;}
  if(pid!=candidate){candidate=pid;stableTicks=0;log_num("[injector] candidate ACOdyssey PID ",pid);}
  if(!process_alive(pid)){candidate=0;stableTicks=0;Sleep(1000);continue;}
  ULONG_PTR up=remote_module_base(pid,L"uplay_r1_loader64.dll");
  if(!up){stableTicks=0;Sleep(1000);continue;}
  if(!has_game_window(pid)){stableTicks=0;Sleep(1000);continue;}
  stableTicks++;
  if(stableTicks==1)log_line("[injector] Ubisoft session loader and visible game window present; beginning stability timer");
  if(stableTicks<20){Sleep(1000);continue;}
  if(!process_alive(pid)){candidate=0;stableTicks=0;continue;}
  log_line("[injector] final game process remained stable with a visible window for 20s; injecting mod DLL now");
  if(inject_into(pid,dllPath)){log_line("[injector] SUCCESS: mod DLL injection requested after Ubisoft startup handoff");ExitProcess(0);}
  log_line("[injector] injection failed; stopping instead of retrying into the same process");ExitProcess(4);
 }
 log_line("[injector] ERROR: timed out waiting for a stable ACOdyssey.exe");ExitProcess(5);
}
