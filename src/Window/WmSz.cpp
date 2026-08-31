#include <print>
#include "WmSz.h"

LRESULT CALLBACK WmSz::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	switch (uMsg)
	{
	case WM_SIZING:
		AdjustRect((RECT*)lParam, wParam);
		s_prevRect = *reinterpret_cast<RECT*>(lParam);
		return TRUE;
	}

	return CallWindowProc(s_originalWndProc, hWnd, uMsg, wParam, lParam);
#else
	return 0;
#endif
}

void WmSz::Init(HWND hWnd)
{
#ifdef _WIN32
	s_hWnd = hWnd;
	GetWindowRect(s_hWnd, &s_prevRect);
	s_aspectRatio = static_cast<float>(s_prevRect.right - s_prevRect.left) / static_cast<float>(s_prevRect.bottom - s_prevRect.top);
	if (!s_hWnd) {
		std::println("WmSz: Failed to get window handle.");
		return;
	}
	s_originalWndProc = (WNDPROC)SetWindowLongPtr(s_hWnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);
	if (!s_originalWndProc) {
		std::println("WmSz: Failed to subclass window. Error: %lu", GetLastError());
		s_hWnd = nullptr;
	}
#endif
}

void WmSz::AdjustRect(RECT* rect, WPARAM wParam)
{
	// For sides
	int width = rect->right - rect->left;
	int height = rect->bottom - rect->top;
	auto newWidth = static_cast<int>(height * s_aspectRatio);
	auto newHeight = static_cast<int>(width / s_aspectRatio);

	switch (wParam)
	{
	case WMSZ_LEFT:
	case WMSZ_RIGHT: {
		auto difference = newHeight - height;
		rect->top -= difference / 2;
		rect->bottom += difference / 2;
	} break;
	case WMSZ_TOP:
	case WMSZ_BOTTOM: {
		auto difference = newWidth - width;
		rect->left -= difference / 2;
		rect->right += difference / 2;
	} break;
	case WMSZ_TOPLEFT:
	case WMSZ_TOPRIGHT:
		rect->top = rect->bottom - newHeight;
		break;
	case WMSZ_BOTTOMLEFT:
	case WMSZ_BOTTOMRIGHT: 
		rect->bottom = rect->top + newHeight;
		break;
	}
}

void WmSz::Exit()
{
#ifdef _WIN32
	if (s_hWnd && s_originalWndProc)
	{
		SetWindowLongPtr(s_hWnd, GWLP_WNDPROC, (LONG_PTR)s_originalWndProc);
		s_originalWndProc = nullptr;
		s_hWnd = nullptr;
	}
#endif
}
