#ifndef WINMINI_H
#define WINMINI_H

typedef void* HANDLE;
typedef void* HINSTANCE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* HDC;
typedef void* HGDIOBJ;
typedef void* HBRUSH;
typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned int UINT;
typedef unsigned long long ULONG_PTR;
typedef long long LONG_PTR;
typedef unsigned long long SIZE_T;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef unsigned short WCHAR;
typedef const WCHAR* LPCWSTR;
typedef WCHAR* LPWSTR;
typedef const char* LPCSTR;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef LONG_PTR LRESULT;
typedef ULONG_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef unsigned long COLORREF;

#define WINAPI __stdcall
#define CALLBACK __stdcall
#define TRUE 1
#define FALSE 0
#define NULL ((void*)0)
#define DLL_PROCESS_DETACH 0
#define DLL_PROCESS_ATTACH 1
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define GENERIC_WRITE 0x40000000UL
#define FILE_SHARE_READ 0x00000001UL
#define CREATE_ALWAYS 2UL
#define OPEN_ALWAYS 4UL
#define FILE_ATTRIBUTE_NORMAL 0x00000080UL
#define FILE_END 2UL
#define MEM_COMMIT 0x1000UL
#define MEM_RESERVE 0x2000UL
#define MEM_RELEASE 0x8000UL
#define PAGE_EXECUTE_READWRITE 0x40UL
#define PAGE_EXECUTE_READ 0x20UL
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

typedef struct tagRECT { long left; long top; long right; long bottom; } RECT;
typedef struct tagPAINTSTRUCT { HDC hdc; BOOL fErase; RECT rcPaint; BOOL fRestore; BOOL fIncUpdate; BYTE rgbReserved[32]; } PAINTSTRUCT;
typedef struct tagPOINT { long x; long y; } POINT;
typedef struct tagMSG { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; DWORD lPrivate; } MSG;
typedef LRESULT (CALLBACK *WNDPROC)(HWND,UINT,WPARAM,LPARAM);
typedef struct tagWNDCLASSEXW {
 UINT cbSize; UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance;
 void* hIcon; void* hCursor; HBRUSH hbrBackground; LPCWSTR lpszMenuName; LPCWSTR lpszClassName; void* hIconSm;
} WNDCLASSEXW;
typedef BOOL (CALLBACK *WNDENUMPROC)(HWND, LPARAM);
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID);

__declspec(dllimport) HANDLE WINAPI CreateThread(void*,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,DWORD*);
__declspec(dllimport) HMODULE WINAPI LoadLibraryW(LPCWSTR);
__declspec(dllimport) BOOL WINAPI DisableThreadLibraryCalls(HMODULE);
__declspec(dllimport) DWORD WINAPI GetLastError(void);
__declspec(dllimport) HANDLE WINAPI CreateFileW(LPCWSTR,DWORD,DWORD,void*,DWORD,DWORD,HANDLE);
__declspec(dllimport) BOOL WINAPI WriteFile(HANDLE,LPCVOID,DWORD,DWORD*,void*);
__declspec(dllimport) BOOL WINAPI CloseHandle(HANDLE);
__declspec(dllimport) DWORD WINAPI SetFilePointer(HANDLE,long,long*,DWORD);
__declspec(dllimport) DWORD WINAPI GetModuleFileNameW(HMODULE,LPWSTR,DWORD);
__declspec(dllimport) HMODULE WINAPI GetModuleHandleW(LPCWSTR);
__declspec(dllimport) DWORD WINAPI GetCurrentProcessId(void);
__declspec(dllimport) HANDLE WINAPI GetCurrentProcess(void);
__declspec(dllimport) void WINAPI Sleep(DWORD);
__declspec(dllimport) BOOL WINAPI VirtualProtect(LPVOID,SIZE_T,DWORD,DWORD*);
__declspec(dllimport) LPVOID WINAPI VirtualAlloc(LPVOID,SIZE_T,DWORD,DWORD);
__declspec(dllimport) BOOL WINAPI VirtualFree(LPVOID,SIZE_T,DWORD);
__declspec(dllimport) BOOL WINAPI FlushInstructionCache(HANDLE,LPCVOID,SIZE_T);

__declspec(dllimport) BOOL WINAPI EnumWindows(WNDENUMPROC,LPARAM);
__declspec(dllimport) DWORD WINAPI GetWindowThreadProcessId(HWND,DWORD*);
__declspec(dllimport) BOOL WINAPI IsWindowVisible(HWND);
__declspec(dllimport) BOOL WINAPI GetWindowRect(HWND,RECT*);
__declspec(dllimport) unsigned short WINAPI RegisterClassExW(const WNDCLASSEXW*);
__declspec(dllimport) HWND WINAPI CreateWindowExW(DWORD,LPCWSTR,LPCWSTR,DWORD,int,int,int,int,HWND,void*,HINSTANCE,LPVOID);
__declspec(dllimport) LRESULT WINAPI DefWindowProcW(HWND,UINT,WPARAM,LPARAM);
__declspec(dllimport) BOOL WINAPI ShowWindow(HWND,int);
__declspec(dllimport) BOOL WINAPI UpdateWindow(HWND);
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

#endif
