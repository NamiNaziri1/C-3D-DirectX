#include <windows.h>
#include <iostream>
#include <sstream>

LRESULT CALLBACK WndProC(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
			PostQuitMessage( 69 );
			break;

		case WM_KEYDOWN:
			if (wParam == 'F') 
			{
				SetWindowText(hWnd, "Respect");
			}
			break;
		case WM_KEYUP:
			if (wParam == 'F')
			{
				SetWindowText(hWnd, "Not Respect");
			}
			break;
		case WM_CHAR :
			{
				static std::string title;
				title.push_back((char)wParam);
				SetWindowText(hWnd, title.c_str());
			}
			break;
		case WM_LBUTTONDOWN:
			{
				const POINTS point = MAKEPOINTS(lParam);
				std::ostringstream oss;
				oss << "(" << point.x << "." << point.y << ")";
				SetWindowText(hWnd, oss.str().c_str());
				
			}
			break;
			
		default:
			break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	const auto pClassName = "hw3d";
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(
		0,
		pClassName,
		"Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);
	ShowWindow(hWnd, SW_SHOW);

	MSG msg;
	BOOL gResult;
	while (gResult = GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}


		
		
		
	return 0;
}