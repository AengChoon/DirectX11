#include "pch.h"
#include "DirectX11.h"
#include "framework.h"
#include "Game.h"

HINSTANCE GInstanceHandle;
HWND GWindowHandle;

ATOM MyRegisterClass(HINSTANCE InstanceHandle);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    /** 1) 윈도우 창 정보 등록 */
    MyRegisterClass(hInstance);

    /** 2) 윈도우 창 생성 */
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    CGame Game;
    Game.Init(GWindowHandle);

    MSG Msg {};
    while (Msg.message != WM_QUIT)
    {
        if (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
        {
	        TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
        else
        {
	        Game.Update();
            Game.Render();
        }
    }

    return static_cast<int>(Msg.wParam);
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE InstanceHandle)
{
    WNDCLASSEXW Wcex;

    Wcex.cbSize = sizeof(WNDCLASSEX);
    Wcex.style          = CS_HREDRAW | CS_VREDRAW;
    Wcex.lpfnWndProc    = WndProc;
    Wcex.cbClsExtra     = 0;
    Wcex.cbWndExtra     = 0;
    Wcex.hInstance      = InstanceHandle;
    Wcex.hIcon          = LoadIcon(InstanceHandle, MAKEINTRESOURCE(IDI_DIRECTX11));
    Wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    Wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    Wcex.lpszMenuName   = nullptr;
    Wcex.lpszClassName  = L"DirectX11";
    Wcex.hIconSm        = LoadIcon(Wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&Wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	GInstanceHandle = hInstance; // Store instance handle in our global variable

    RECT WindowRect {0, 0, GWindowSizeX, GWindowSizeY};
    ::AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, false);

	GWindowHandle = CreateWindowW
	(
        L"DirectX11",
        L"Client",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        0,
        WindowRect.right - WindowRect.left,
        WindowRect.bottom - WindowRect.top,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

	if (!GWindowHandle)
    {
		return FALSE;
    }

	::ShowWindow(GWindowHandle, nCmdShow);
	::UpdateWindow(GWindowHandle);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
            // TODO: Add any drawing code that uses hdc here...
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