#include <stdio.h>
#include <Windows.h>
#include <gl/GL.h>
#include <resource.h>

#define global_file static
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))


LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


global_file int S_W = 1024;
global_file int S_H = 768;
global_file HWND txtVertexShader;
global_file HWND txtFragmentShader;

LRESULT CALLBACK GLWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE prevInst,
		     LPSTR cmdLine, int cmdShowParam)
{

  printf("Initializing application.\n");

  WNDCLASS wcx;
  wcx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wcx.lpfnWndProc = WinProc;
  wcx.cbClsExtra = 0;
  wcx.cbWndExtra = 0;
  wcx.hInstance = hinst;
  wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcx.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
  wcx.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
  wcx.lpszClassName = "MainWClass";


  RegisterClass(&wcx);
  
  wcx.lpszMenuName = NULL;
  wcx.lpszClassName = "GL_WIN_CLASS";
  wcx.hIcon = NULL;
  wcx.lpfnWndProc = GLWinProc;
  
  RegisterClass(&wcx);

  HWND hWnd = CreateWindow(
			   "MainWClass",
			   "BitcoinApp",
			   WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			   CW_USEDEFAULT,
			   CW_USEDEFAULT,
			   S_W,
			   S_H,
			   (HWND) NULL,
			   (HMENU) NULL,
			   hinst,
			   (LPVOID) NULL);

  if (hWnd == NULL)
    {
      printf("error creating window!\n");
      return 1;
    }

  // OpenGL stuff - yay :)
  {
	  
	  
  }
  
  // End of OpenGL stuff
  

  ShowWindow(hWnd, SW_SHOW);
  UpdateWindow(hWnd);

  MSG msg;
			  
  printf("starting up\n");
  while(true) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
    if (msg.message == WM_QUIT) {
		printf("got quit message\n");
		break;
	}
		

    // Run our game loop here
    {
		
    }
	
  }
  
  return 0;
}

void InitGL(HWND hWnd) 
{
	PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
			32,                        //Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                        //Number of bits for the depthbuffer
			8,                        //Number of bits for the stencilbuffer
			0,                        //Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		HDC ourWindowHandleToDeviceContext = GetDC(hWnd);

		int  letWindowsChooseThisPixelFormat;
		letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd); 
		SetPixelFormat(ourWindowHandleToDeviceContext,letWindowsChooseThisPixelFormat, &pfd);

		HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
		wglMakeCurrent (ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);

		
		printf("OPENGL VERSION: %s\n", (char*)glGetString(GL_VERSION) );

}

void CompileShaders(const char* vsCode, const char* fsCode)
{
	// TODO: inlcude glext.h etc. 
	// load the functions dynamically via wglGetProc(...)
	GLuint shaders[2];
	glCreateShader(2, shaders);
	
}

LRESULT CALLBACK GLWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg) 
	{
		
		case WM_PAINT:
			{
				glClearColor(0.75f, 0, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				HDC hdc = GetDC(hwnd);
				SwapBuffers(hdc);
				ReleaseDC(hwnd, hdc);
				break;
			
			}
		default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	
	return 0;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
    {
    case WM_CREATE: 
		{
			txtVertexShader = CreateWindow(
			   "EDIT",
			   "",
			   ES_LEFT | ES_MULTILINE | WS_VISIBLE | WS_CHILDWINDOW |
			   WS_VSCROLL | ES_AUTOVSCROLL,
			   0,
			   20,
			   300,
			   200,
			   (HWND) hwnd,
			   (HMENU) NULL,
			   (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			   NULL);
			   
			txtFragmentShader = CreateWindow(
			   "EDIT",
			   "",
			   ES_LEFT | ES_MULTILINE | WS_VISIBLE | WS_CHILDWINDOW |
			   WS_VSCROLL | ES_AUTOVSCROLL,
			   0,
			   260,
			   300,
			   200,
			   (HWND) hwnd,
			   (HMENU) NULL,
			   (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			   NULL);
			   
			HWND glWin = CreateWindow(
			   "GL_WIN_CLASS",
			   "",
			   WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER,
			   310,
			   20,
			   600,
			   600,
			   (HWND) hwnd,
			   (HMENU) NULL,
			   (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			   NULL);
			   
			InitGL(glWin);
			
		}
		break;
	
    case WM_CLOSE: 
		printf("in WM_CLOSE\n");
		DestroyWindow(hwnd); break;
    case WM_PAINT:
		{
			HDC hdc = GetDC(hwnd);
			
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(200, 200, 200));
			TextOut(hdc, 2, 2, "Vertex Shader: ", 14 );
			TextOut(hdc, 2, 242, "Fragment Shader: ", 20);
			ReleaseDC(hwnd, hdc);
		}
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default: return DefWindowProc(hwnd, msg, wParam, lParam);
    }
  return 0;
}
