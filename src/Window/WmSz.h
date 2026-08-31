#pragma once

#include "fixWin32Compat.h"
#include <raylib.h>

class WmSz
{
private:
	static inline float s_aspectRatio{ 0.0f };
	static inline RECT s_prevRect{ 0, 0, 0, 0 };
	static inline HWND s_hWnd{ nullptr };
	static inline WNDPROC s_originalWndProc{ nullptr };
	static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
	static void AdjustRect(RECT*, WPARAM);

public:
	static void Init(HWND hWnd);
	static void Exit();
};
