#include "WindowClass.h"

#include <d2d1.h>

Window::Window(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow, int height, int width)
{
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW);
	wc.lpszClassName = L"WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	HWND hWnd = CreateWindowEx(NULL,
		L"WindowClass1", // name of the window class
		L"AI with Direct2D", // title of the window
		WS_OVERLAPPEDWINDOW, // window style
		GetSystemMetrics(SM_CXFULLSCREEN) / 2 - WINDOW_WIDTH / 2, // x-position of the window
		GetSystemMetrics(SM_CYFULLSCREEN) / 2 - WINDOW_HEIGHT / 2, // y-position of the window
		width, // width of the window
		height, // height of the window
		nullptr, // we have no parent window, NULL
		nullptr, // we aren't using menus, NULL
		hInstance, // application handle
		this); // used with multiple windows, NULL

// display the window on the screen
	ShowWindow(hWnd, nCmdShow);
}

bool Window::run()
{
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		// Translate the message and dispatch it to WindowProc()
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// If the message is WM_QUIT, exit the while loop
	if (msg.message == WM_QUIT)
		return false;

	return true;
}

HWND& Window::getHWND()
{
	return hWnd;
}

LRESULT Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		}
		default:
			break;
		}
	}
	default:
		break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}