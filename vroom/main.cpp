#include <Windows.h>

LRESULT CALLBACK
WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
	{
    case WM_PAINT:
    {
      PAINTSTRUCT paint;
      HDC hDC = BeginPaint(window, &paint);

      PatBlt(hDC, paint.rcPaint.left, paint.rcPaint.top,
             paint.rcPaint.right - paint.rcPaint.left,
             paint.rcPaint.bottom - paint.rcPaint.top, BLACKNESS);

      EndPaint(window, &paint);
    }
		case WM_QUIT:
		{
      PostQuitMessage(0);
      return 0;
		}
		default:
		{
			return DefWindowProc(window, message, wParam, lParam);
		}
	}

  return 0;
}

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass = {};
  windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hInstance = hInstance;
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpszClassName = "VroomClassName";
	windowClass.lpfnWndProc = WindowProc;

	if (RegisterClassEx(&windowClass))
	{
    HWND window = CreateWindowEx(WS_EX_APPWINDOW, windowClass.lpszClassName, "Vroom", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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