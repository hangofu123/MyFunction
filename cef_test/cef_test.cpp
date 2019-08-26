// cef_test.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "resource.h"
#include "SimpleApp.h"
#include "SimpleHandler.h"
#include "plugin.h"
#define MAX_LOADSTRING 100

#define IDM_FILE_NEW  40001

#define IDM_FILE_OPEN 40002

#define IDM_EDIT_COPY 40003

#define IDM_EDIT_CUT  40004
#pragma comment(lib,"libcef.lib")
#pragma comment(lib,"libcef_dll_wrapper.lib")
#pragma comment(lib,"plugin.lib")
// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
#define APP_NAME	TEXT("Hanog")
// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	CefEnableHighDPISupport();
	void* sandbox_info = NULL;

	HWND hWnd;
	MSG msg;
	WNDCLASS wc = { 0 };
	wc.style = NULL;
	wc.hIcon = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = MAKEINTRESOURCE(IDC_CEF_TEST);
	wc.lpszClassName = APP_NAME;
	wc.hCursor = NULL;
//	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_MAIN));

	if (!RegisterClass(&wc)) return 0;
	HMENU    hMenu;
	HMENU	  hMenuPop;

	//// Menu Append
	//hMenu = CreateMenu();		//主菜单,水平
	//hMenuPop = CreateMenu();	//下拉的菜单,垂直

	//AppendMenu(hMenuPop, MF_STRING, IDM_FILE_NEW, TEXT("New"));
	//AppendMenu(hMenuPop, MF_STRING, IDM_FILE_OPEN, TEXT("Open"));
	//AppendMenu(hMenu, MF_POPUP, (unsigned int)hMenuPop, TEXT("File"));

	//hMenuPop = CreateMenu();

	//AppendMenu(hMenuPop, MF_STRING, IDM_EDIT_COPY, TEXT("Copy"));
	//AppendMenu(hMenuPop, MF_SEPARATOR, 0, NULL);
	//AppendMenu(hMenuPop, MF_STRING, IDM_EDIT_CUT, TEXT("Cut"));
	//AppendMenu(hMenu, MF_POPUP, (unsigned int)hMenuPop, TEXT("Edit"));// Menu Insert
	//InsertMenu(hMenu, 0, MF_BYPOSITION | MF_POPUP, IDM_EDIT_CUT + 7, TEXT("NewAdd"));
	hInst = hInstance;
//	HMENU hMenu;  //菜单句柄 
	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_CEF_TEST));

	hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, APP_NAME, APP_NAME, WS_POPUP, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, hMenu, hInstance, NULL);

	

	//SetMenu(hWnd, hMenu);
	//ShowWindow(hWnd, nCmdShow);
	//UpdateWindow(hWnd);

#if defined(CEF_USE_SANDBOX)
	// Manage the life span of the sandbox information object. This is necessary
	// for sandbox support on Windows. See cef_sandbox_win.h for complete details.
	CefScopedSandboxInfo scoped_sandbox;
	sandbox_info = scoped_sandbox.sandbox_info();
#endif

	// Provide CEF with command-line arguments.
	//HINSTANCE hInstance = GetModuleHandle(0);
	CefMainArgs main_args(hInstance);

	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.

	// Specify CEF global settings here.
	CefSettings settings;
	//settings.single_process = false;
	//CefString(&settings.log_file).FromString("cef.log");
	settings.log_severity = LOGSEVERITY_DISABLE;
	settings.multi_threaded_message_loop = true;
	settings.single_process= true;
	//settings.remote_debugging_port = 8083;
	CefString(&settings.user_agent).FromString("WDF");
	settings.no_sandbox = true;
	CefRefPtr<SimpleApp> app(new SimpleApp);

	// WDFApp implements application-level callbacks for the browser process.
	// It will create the first browser instance in OnContextInitialized() after
	// CEF has initialized.
	int exit_code = CefExecuteProcess(main_args, app, sandbox_info);
	if (exit_code >= 0) {
		// The sub-process has completed so return here.
		return exit_code;
	}

	//启动插件框架
	plugin::PluginManager::SetupAsync();

	// Initialize CEF.
	CefInitialize(main_args, settings, app, sandbox_info);

	// Run the CEF message loop. This will block until CefQuitMessageLoop() is called.
	//CefRunMessageLoop();
	// Shut down CEF.
	//CefShutdown();
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CefShutdown();
	//关闭插件框架
	plugin::PluginManager::Shutdown();
	return 0;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//


//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
		  switch (wmId)
		  {
			case IDM_FILE_OPEN:
				//Mess(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				MessageBox(NULL,TEXT( "hango"), NULL, NULL);
				break;
			case IDM_FILE_NEW:
				//DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

