// run Windows as fast as possible :-)
#define WIN32_LEAN_AND_MEAN
#define INITGUID

// include these header files
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>

#define  WINDOW_CLASS_NAME L"WIN3DCLASS"

// Globals
HWND main_window_handle = NULL;  // window handle
HINSTANCE main_instance = NULL;
HWND hwnd;						 // main window handle

// windows message handler
// This is how Windows handles messages
LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT msg,
	WPARAM wparam,
	LPARAM lparam)
{
	PAINTSTRUCT	ps;		// paint structure
	HDC			hdc;

	// handle Windows messages
	switch (msg)
	{
		// Do this on creating the window
	case WM_CREATE:
	{

		return (0);
	} break;

	// Do this if the user double-clicks with the left mouse button
	case WM_LBUTTONDBLCLK:
	{

		// Display message box with message
		MessageBox(NULL, L"Cool Huh?", L"WinFirst Program",
			MB_OK | MB_ICONEXCLAMATION);

		return (0);
	} break;


	// Do this to paint in the Window itself
	// Windows will also use this to repaint itself if
	// the window gets covered by another window
	case WM_PAINT:
	{
		// get drawing device & begin painting in window
		hdc = BeginPaint(hwnd, &ps);

		// get rectangle (white part of window)
		RECT rcClient;
		GetClientRect(hwnd, &rcClient);

		// save previous window background
		int nOldBkMode = SetBkMode(hdc, TRANSPARENT);

		// set text colour and store old colour
		COLORREF clrOldTextColor = SetTextColor(hdc, GetSysColor(COLOR_WINDOWTEXT));

		// Output the text
		DrawText(
			hdc,		// drawing device
			_T("This is my first Windows program!"),
			-1,			// zero delimiter for text
			&rcClient,	// window client area
			DT_LEFT);  // left justify text

		// add a new line (need to increase the rectangle)
		rcClient.top = rcClient.top + 15;

		// display more text
		for (int i = 0; i < 10; i++)
		{
			rcClient.top = rcClient.top + 15;

			DrawText(
				hdc,
				_T("Cool or What?!!!!!"),
				-1,
				&rcClient,
				DT_LEFT);

		}

		rcClient.top = rcClient.top + 30;


		DrawText(
			hdc,
			_T("Try Double-Clicking inside this Window"),
			-1,
			&rcClient,
			DT_LEFT);

		// restore original text colour
		SetTextColor(hdc, clrOldTextColor);

		// restore original window background
		SetBkMode(hdc, nOldBkMode);

		// end the window painting
		EndPaint(hwnd, &ps);
		return (0);
	} break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return (0);
	} break;

	default: break;
	} // end switch

	// pass unprocessed messages to windows
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WindowProc function



// Main Windows Function
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hprevinstance,
	LPSTR lpcmdline,
	int ncmdshow)
{

	WNDCLASSEX winclass;
	MSG msg;


	// create window structure
	// This describes some properties that need to be setup
	// to create the window
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC |
		CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = (LPCWSTR) WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window so Windows knows about it
	if (!RegisterClassEx(&winclass))
		return (0);

	// Create the window itself
	if (!(hwnd = CreateWindowEx(
		NULL,
		WINDOW_CLASS_NAME,
		L"Winfirst Program",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		200, 50,  // initial x,y
		500, // window width
		400, // window height
		NULL,
		NULL,
		hinstance,
		NULL)))
		return (0);


	main_window_handle = hwnd;
	main_instance = hinstance;


	// main event loop
	// This is an infinite loop which checks
	// to see if the user has quit by closing the window,
	// otherwise it will check for messages and process
	// requests using the Windowproc() message handler
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	} // end while


	return (msg.wParam);

} // end WinMain


