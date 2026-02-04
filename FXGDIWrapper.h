#ifndef FX_GDI_WRAPPER_HEADER

#include "FXNamespaces.h"
#include "Windows.h"
#include <gdiplus.h>
#include <string>
#pragma comment(lib, "gdiplus.lib")

namespace FluentX::platform {
	
	inline static ULONG_PTR gdiStartupToken = 0;

	inline void InitGDI() {
		if (!gdiStartupToken) {
			Gdiplus::GdiplusStartupInput GPSInput;
			Gdiplus::GdiplusStartup(&gdiStartupToken, &GPSInput, nullptr);
		}
	}

	inline HICON GDIPLoadPNG(std::wstring path) {
		InitGDI();
		Gdiplus::Bitmap bmp(path.c_str());
		HICON hIcon;
		bmp.GetHICON(&hIcon);
		return hIcon;
	}

}

#endif // !FX_GDI_WRAPPER_HEADER
