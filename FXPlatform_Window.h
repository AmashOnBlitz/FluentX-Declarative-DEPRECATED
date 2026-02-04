#ifndef FX_PLATFORM_WINDOW_HEADER
#define FX_PLATFORM_WINDOW_HEADER

#include "FXNamespaces.h"
#include "FXSize.h"
#include <string>
#include "Windows.h"
#include "tchar.h"
#include "strsafe.h"
#include "FXCoordinates.h"
#include <algorithm>
#include "FXGDIWrapper.h"
#include <filesystem>
#include "FXSize.h"
namespace fs = std::filesystem;


#define FX_MAIN_WINDOW_PROC fnfxMainWinProc

//	HEX CODE from 1000 to 1099 RESERVED FOR FX PLATFORM WINDOW  

namespace FluentX::platform {

	LRESULT CALLBACK FX_MAIN_WINDOW_PROC(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	class FXPWindow {
	public:
		FXPWindow(
			std::string& title,
			fs::path iconPath,
			FluentX::UI::FXCoords& pos,
			FluentX::UI::FXSize& Size,
			FluentX::UI::FXSize& MaxSize,
			FluentX::UI::FXSize& MinSize,
			bool& resizable,
			//bool frameless,
			bool& transparent,
			int& opacity255
		) : mTitle(title),
			mIconPath(iconPath),
			mPosition(pos),
			mSize(Size),
			mMaxSize(MaxSize),
			mMinSize(MinSize),
			mResizable(resizable),
			//mFrameless(frameless),
			mTransparent(transparent),
			mOpacity(opacity255),
			mHInstance(GetModuleHandle(NULL))
		{
			ConvUnits();
			InitIcon();
			mWTitle					= std::wstring(mTitle.begin(), mTitle.end());
			mWndClass.cbClsExtra	= 0;
			mWndClass.cbWndExtra	= sizeof(FXPWindow);
			mWndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			mWndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
			mWndClass.hIcon			= mIcon;
			mWndClass.hInstance		= mHInstance;
			mWndClass.lpfnWndProc	= FX_MAIN_WINDOW_PROC;
			mWndClass.lpszClassName = mWTitle.c_str();
			mWndClass.lpszMenuName	= NULL;
			mWndClass.style			= CS_HREDRAW | CS_VREDRAW;

			if (!RegisterClass(&mWndClass)) {
				FX_RESERVE_ERR_CHAR_BUFF[FX_CHAR_BUFFER_QUANTITY_STANDARD_ERR];
				StringCchPrintf(
					FX_ERR_CHAR_BUFF,
					FX_CHAR_BUFFER_QUANTITY_STANDARD_ERR,
					_TEXT("Cannot Register Window Class Of Class Name \"%s\" \n Window Name : \"%s\""),
					mWndClass.lpszClassName,
					mWTitle.c_str()
				);
				MessageBox(NULL, FX_ERR_CHAR_BUFF, _TEXT("INTERNAL ERROR : Window Class Not Registered!"), MB_ICONERROR | MB_APPLMODAL);
				this->InitFailed = true;
				return;
			}


			mHWnd = ::CreateWindowEx(
				(mTransparent)? WS_EX_LAYERED : 0,
				mWTitle.c_str(),
				mWTitle.c_str(),
				/*(mFrameless) ? WS_POPUP : WS_OVERLAPPEDWINDOW,*/	WS_OVERLAPPEDWINDOW,
				(mPosition.x == FX_USE_DEFAULT)?	CW_USEDEFAULT : mPosition.x,
				(mPosition.y == FX_USE_DEFAULT)?	CW_USEDEFAULT : mPosition.y,
				(mSize.width() == FX_USE_DEFAULT)?	CW_USEDEFAULT : mSize.width(),
				(mSize.height() == FX_USE_DEFAULT)?	CW_USEDEFAULT : mSize.height(),
				NULL,
				NULL,
				mHInstance,
				this
			);

		}

		void ShowWindow(){
			if (InitFailed) return;
			if (mTransparent)
				::SetLayeredWindowAttributes(mHWnd, RGB(0, 0, 0), mOpacity, LWA_COLORKEY | LWA_ALPHA);
			::ShowWindow(mHWnd, getCMDShow());
			::UpdateWindow(mHWnd);
		}

		int MessageLoop() {

			if (InitFailed) return 0;

			if (mMinSize.width() > mMaxSize.width() || mMinSize.height() > mMaxSize.height()) {
				FX_RESERVE_ERR_CHAR_BUFF[FX_CHAR_BUFFER_QUANTITY_STANDARD_ERR];
				StringCchPrintf(
					FX_ERR_CHAR_BUFF,
					FX_CHAR_BUFFER_QUANTITY_STANDARD_ERR,
					_TEXT("MIN SIZE cannot be more than MAX SIZE \n Exception in Window Named \"%s\""),
					mWTitle.c_str()
				);
				MessageBox(mHWnd, FX_ERR_CHAR_BUFF, _TEXT("ERROR : Invalid Values!"), MB_ICONERROR | MB_APPLMODAL);
				return 0;
			}
			if (mResizable) {
				mSize.SetWidth(std::clamp<LONG>(mSize.width(), mMinSize.width(), mMaxSize.width()));
				mSize.SetHeight(std::clamp<LONG>(mSize.height(), mMinSize.height(), mMaxSize.height()));
			}

			::SetWindowPos(mHWnd, NULL, mPosition.x, mPosition.y, mSize.width(), mSize.height(), SWP_NOZORDER);

			if (!mResizable) {
				::SetWindowLong(mHWnd, GWL_STYLE, GetWindowLong(mHWnd, GWL_STYLE) & ~(WS_THICKFRAME | WS_MAXIMIZEBOX));
			}

			while (GetMessage(&msg, NULL, 0, 0))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			return 1;
		}


		void SetTitle(const std::string& title) {
			mTitle = title;
			mWTitle = std::wstring(mTitle.begin(), mTitle.end());
		}
		void SetSize(const FluentX::UI::FXSize& size)		{ mSize = size; }
		void SetPosition(const FluentX::UI::FXCoords& pos)	{ mPosition = pos; }
		void SetMaxSize(const FluentX::UI::FXSize& maxSize) { mMaxSize = maxSize; }
		void SetMinSize(const FluentX::UI::FXSize& minSize) { mMinSize = minSize; }
		void SetResizable(bool resizable)					{ mResizable = resizable; }
		//void SetFrameless(bool frameless)					{ mFrameless = frameless; }
		void SetTransparent(bool transparent)				{ mTransparent = transparent; }
		void SetOpacity(int value255)						{ mOpacity = value255; }

		int getCMDShow() {
			STARTUPINFO si{};
			si.cb = sizeof(STARTUPINFO);
			::GetStartupInfo(&si);
			if (si.dwFlags & STARTF_USESHOWWINDOW)
				return si.wShowWindow;
			return SW_SHOWNORMAL;
		}

		void ConvUnits() {
			if (mMaxSize.width() == FX_USE_DEFAULT) { mMaxSize.SetWidth(9999); }
			if (mMaxSize.height() == FX_USE_DEFAULT) { mMaxSize.SetHeight(9999); }
			if (mMinSize.width() == FX_USE_DEFAULT) { mMinSize.SetWidth(0); }
			if (mMinSize.height() == FX_USE_DEFAULT) { mMinSize.SetHeight(0); }
		}

		FluentX::UI::FXSize GetClientSize() const
		{
			RECT windowRect, clientRect;

			GetWindowRect(mHWnd, &windowRect);
			GetClientRect(mHWnd, &clientRect);

			int borderWidth = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left);
			int borderHeight = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top);

			return {
				mSize.width() - borderWidth,
				mSize.height() - borderHeight
			};
		}


		void InitIcon() {
			mIcon = nullptr;

			if (mIconPath.string() == FX_STR_NOT_DEFINED || mIconPath.empty()) {
				mIcon = ::LoadIcon(NULL, IDI_APPLICATION);
				return;
			}


			if (!fs::exists(mIconPath)) {
				InitFailed = true;
				MessageBox(nullptr, L"Icon file does not exist", L"Error", MB_ICONERROR);
				return;
			}

			auto ext = mIconPath.extension().wstring();
			std::transform(ext.begin(), ext.end(), ext.begin(), ::towlower);

			if (ext == L".ico" || ext == L".bmp") {
				mIcon = (HICON)LoadImageW(
					mHInstance,
					mIconPath.c_str(),
					IMAGE_ICON,
					0, 0,
					LR_LOADFROMFILE
				);
			}
			else if (ext == L".png" || ext == L".jpg" || ext == L".jpeg") {
				mIcon = (HICON)GDIPLoadPNG(mIconPath.c_str());
			}
			else {
				InitFailed = true;
				MessageBox(
					mHWnd,
					L"Unsupported icon format",
					L"Icon Error",
					MB_ICONERROR
				);
			}
		}

		TCHAR* getClassName() {
			static TCHAR szWNDClassName[] = _TEXT("CLASS_FX_MAIN_WINDOW");
			return szWNDClassName;
		}

		LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
			static int cxClient, cyClient;
			switch (msg)
			{
			case WM_SIZE:
				if (mResizable) {
					cxClient = LOWORD(lParam);
					cyClient = HIWORD(lParam);
					mSize.SetWidth(cxClient);
					mSize.SetHeight(cyClient);
				}
				return 1;
			case WM_GETMINMAXINFO: {
				MINMAXINFO* mmInfo = (MINMAXINFO*)lParam;
				if (!mmInfo) return 0;
				if (mResizable) {
					mmInfo->ptMaxTrackSize = { mMaxSize.width(), mMaxSize.height() };
					mmInfo->ptMinTrackSize = { mMinSize.width(), mMinSize.height() };
				}
				else {
					mmInfo->ptMaxTrackSize = { mMaxSize.width(), mMaxSize.height() };
					mmInfo->ptMinTrackSize = { mMaxSize.width(), mMaxSize.height() };
				}
				return 1;
			}
			case WM_MOVE: {
				RECT rect;
				if (::GetWindowRect(hWnd, &rect)) {
					MapWindowPoints(HWND_DESKTOP, NULL, (POINT*)&rect, 2);

					mPosition.x = rect.left;
					mPosition.y = rect.top;
				}
				return 1;
			}
			case WM_DESTROY:
				::PostQuitMessage(0);
				return 1;
			default:
				break;
			}
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}


	public:
		std::string& mTitle;
		fs::path& mIconPath;
		std::wstring mWTitle;
		FluentX::UI::FXSize& mSize;
		FluentX::UI::FXSize& mMaxSize;
		FluentX::UI::FXSize& mMinSize;
		FluentX::UI::FXCoords& mPosition;
		bool& mResizable;
		//bool mFrameless;
		bool& mTransparent;
		bool InitFailed = false;
		int& mOpacity;
		HWND mHWnd{};
		WNDCLASS mWndClass{};
		HINSTANCE mHInstance{};
		HICON mIcon;
		MSG msg {};
	};

	inline LRESULT CALLBACK FX_MAIN_WINDOW_PROC(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		FXPWindow* window = nullptr;

		if (msg == WM_NCCREATE){
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			window = static_cast<FXPWindow*>(cs->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
		}
		else
		{
			window = reinterpret_cast<FXPWindow*>(
				GetWindowLongPtr(hWnd, GWLP_USERDATA)
				);
		} 
		if (window)
			return window->WndProc(hWnd, msg, wParam, lParam);

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

#endif // !FX_PLATOFORM_WINDOW_HEADER
