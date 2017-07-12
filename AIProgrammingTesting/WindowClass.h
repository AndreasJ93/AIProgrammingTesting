#pragma once
#include <Windows.h>
#include <windowsx.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Window
{
public:
	Window(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow,
		int height = WINDOW_HEIGHT,
		int width = WINDOW_WIDTH);

	bool run();
	HWND& getHWND();
private:
	int height;
	int width;
	HWND hWnd;
	MSG msg;
	static LRESULT CALLBACK WindowProc(HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam);
};
