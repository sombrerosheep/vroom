#include <Windows.h>

LRESULT CALLBACK
WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_QUIT:
		{
      PostQuitMessage(0);
      return 0;
		}
		default:
		{
			DefWindowProc(window, message, wParam, lParam);
		}
	}
}

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS windowClass = {};
	windowClass.hInstance = hInstance;
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpszClassName = "VroomClassName";
	windowClass.lpfnWndProc = WindowProc;

	if (RegisterClass(&windowClass))
	{
    HWND window = CreateWindow(windowClass.lpszClassName, "Vroom", WS_OVERLAPPED | WS_VISIBLE,
                               CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance, 0);

    if (window == NULL)
    {
      return 1;
    }

    HDC hDC = GetDC(window);
    MSG message;

    while (GetMessage(&message, window, 0, 0))
    {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    ReleaseDC(window, hDC);
    DestroyWindow(window);

    return message.wParam;
	}
}