#include <stdio.h>
#include <Windows.h>
#include <gl/GL.h>
#include <resource.h>

#define global_file static
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))


LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


global_file int S_W = 1024;
global_file int S_H = 768;


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


LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
    {
    case WM_CREATE: break;
    case WM_CLOSE: 
		printf("in WM_CLOSE\n");
		DestroyWindow(hwnd); break;
    case WM_PAINT:
      {
	/*PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	SetTextColor(hdc, 0x00ff0000);
	TextOut(hdc,
		10,
		10,
		"hello world",
		11);
		EndPaint(hwnd, &ps);*/
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default: return DefWindowProc(hwnd, msg, wParam, lParam);
    }
  return 0;
}
