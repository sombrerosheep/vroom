#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

void
DrawTriangle()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2i(0, 1);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex2i(-1, -1);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex2i(1, -1);
  glEnd();
  glFlush();
}

LRESULT CALLBACK
WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
	{
    case WM_PAINT:
    {
      PAINTSTRUCT paint;
      DrawTriangle();
      BeginPaint(window, &paint);
      EndPaint(window, &paint);
    }
    case WM_DESTROY:
		case WM_CLOSE:
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
  HWND window;
  HDC deviceContext;
  MSG message;
  int pixelFormat;
  PIXELFORMATDESCRIPTOR pfd = {};

  windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hInstance = hInstance;
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpszClassName = "VroomClassName";
	windowClass.lpfnWndProc = WindowProc;

  if (!RegisterClassEx(&windowClass))
  {
    MessageBoxEx(NULL, "ERROR!", "Failed to Register Class", MB_OK, 0);
    return -1;
  }

  window = CreateWindowEx(WS_EX_APPWINDOW, windowClass.lpszClassName, "Vroom", WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance, 0);

  if (window == NULL)
  {
    MessageBoxEx(NULL, "ERROR!", "Failed to create window", MB_OK, 0);
    return 1;
  }

  deviceContext = GetDC(window);

  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;

  pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
  if (pixelFormat == 0)
  {
    MessageBoxEx(window, "ERROR!", "Failed calling ChoosePixelFormat()", MB_OK, 0);
    return 1;
  }

  if (!SetPixelFormat(deviceContext, pixelFormat, &pfd))
  {
    MessageBoxEx(window, "ERROR!", "Failed to set Pixel Format", MB_OK, 0);
    return 1;
  }

  DescribePixelFormat(deviceContext, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

  HGLRC glRC = wglCreateContext(deviceContext);
  wglMakeCurrent(deviceContext, glRC);

  ShowWindow(window, nCmdShow);
    
  while (GetMessage(&message, window, 0, 0))
  {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  wglMakeCurrent(NULL, NULL);
  ReleaseDC(window, deviceContext);
  wglDeleteContext(glRC);
  DestroyWindow(window);

  return message.wParam;
}