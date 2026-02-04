#ifndef FX_PLATFORM_BUTTON_HEADER
#define FX_PLATFORM_BUTTON_HEADER

#include "FXNamespaces.h"
#include "FXCoordinates.h"
#include "Windows.h"
#include "tchar.h"
#include "strsafe.h"
#include "FXSize.h"
#include <functional>
#include "FXButtonBase.h"
#include "FXButton.h"
#include <string>
#include "FX_Internal_D2DEngine.h"

//#include 
//	HEX CODE from 1100 to 1199 RESERVED FOR FX PLATFORM BUTTON  

#define FX_ID_BTN_SOLID_COl_BRUSH_GRAY				0x1100
#define FX_ID_BTN_SOLID_COl_BRUSH_LIGHT_GRAY		0x1101
#define FX_ID_BTN_SOLID_COl_BRUSH_DIM_GRAY			0x1102
#define FX_ID_BTN_SOLID_COl_BRUSH_STARC_DIM_GRAY	0x1103
#define FX_ID_BTN_SOLID_COl_BRUSH_RED				0x1104

#define FX_BUTTON_WINDOW_PROC fnfxBtnWinProc
#define FX_BUTTON_ROUND_IGNORANCE 2
namespace FluentX::platform {

	LRESULT CALLBACK FX_BUTTON_WINDOW_PROC(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	class FXPButton {
	public:
		FXPButton(
			std::string& text,
			std::string& subText,
			FluentX::UI::FXCoords& coords,
			bool& enabled,
			FluentX::UI::FXSize& size,
			FluentX::UI::FXButtonStyle& style,
			FluentX::UI::FXButtonState& state,
			std::function<void(FluentX::UI::FXButtonBase& btn)>& onClick,
			std::function<void(FluentX::UI::FXButtonBase& btn)>& onPress,
			std::function<void(FluentX::UI::FXButtonBase& btn)>& onHover,
			std::function<void(FluentX::UI::FXButtonBase& btn)>& onHoverExit,
			HWND hParentWND,
			FX_FLAG flags,
			FluentX::UI::FXButton BtnStruct
		)
			: mPosition(coords),
			mBIsEnabled(enabled),
			mSize(size),
			mFnOnClick(onClick),
			mFnOnPress(onPress),
			mFnOnHover(onHover),
			mFnOnHoverExit(onHoverExit),
			mStrText(text),
			mStrSubText(subText),
			mBtnState(state),
			mBtnStyle(style),
			mHInstance(GetModuleHandle(NULL)),
			mHParentWND(hParentWND),
			mBitFlags(flags),
			mBtnStruct(BtnStruct)
		{
			fnConvUnits();

			mBtnClass.cbClsExtra = 0;
			mBtnClass.cbWndExtra = 0;
			//mBtnClass.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
			mBtnClass.hbrBackground = NULL;
			mBtnClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			mBtnClass.hIcon = NULL;
			mBtnClass.hInstance = mHInstance;
			mBtnClass.lpfnWndProc = FX_BUTTON_WINDOW_PROC;
			mBtnClass.lpszClassName = fnGetClassName();
			mBtnClass.lpszMenuName = NULL;
			mBtnClass.style = CS_VREDRAW | CS_HREDRAW;

			static bool bIsClsBtnRegistered = false;

			if (!bIsClsBtnRegistered) {
				if (!RegisterClass(&mBtnClass)) {
					FX_RESERVE_ERR_CHAR_BUFF[FX_CHAR_BUFFER_QUANTITY_STANDARD_ERR];
					StringCchPrintf(
						FX_ERR_CHAR_BUFF,
						FX_CHAR_BUFFER_QUANTITY_STANDARD_ERR,
						_TEXT("Cannot Register Button Class")
					);
					::MessageBox(
						mHParentWND,
						FX_ERR_CHAR_BUFF,
						_TEXT("ERROR : Cannot Register Button Class"),
						MB_ICONERROR | MB_APPLMODAL
					);
					this->InitFailed = true;
				}
				bIsClsBtnRegistered = true;
			}

			mHWnd = ::CreateWindowEx(
				0,
				fnGetClassName(),
				NULL,
				WS_CHILDWINDOW | WS_VISIBLE,
				mPosition.x,
				mPosition.y,
				mSize.width(),
				mSize.height(),
				mHParentWND,
				NULL,
				(HINSTANCE)::GetWindowLongPtr(mHParentWND, GWLP_HINSTANCE),
				this
			);

			if (!mHWnd) {
				DWORD err = ::GetLastError();
				MessageBox(NULL, L"Button creation failed!", L"ERROR", MB_ICONERROR);
			}

			SetLayeredWindowAttributes(mHWnd, RGB(255, 0, 255), 255, LWA_COLORKEY);
			if (mBtnStyle.cornerRadius > 0) {
				HRGN reigon = ::CreateRoundRectRgn(0, 0, mSize.width(), mSize.height(), mBtnStyle.cornerRadius, mBtnStyle.cornerRadius);
				::SetWindowRgn(mHWnd, reigon, TRUE);
			}


		}
		~FXPButton() {}
		LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
			static int cxClient, cyClient;
			switch (msg)
			{
			case WM_SIZE:
				cxClient = LOWORD(lParam);
				cyClient = HIWORD(lParam);
				mSize.SetWidth(cxClient);
				mSize.SetHeight(cyClient);
				return 1;
			case WM_MOVE: {
				RECT rect;
				GetWindowRect(hWnd, &rect);
				MapWindowPoints(HWND_DESKTOP, mHParentWND, (POINT*)&rect, 2);

				mPosition.x = rect.left;
				mPosition.y = rect.top;
				return 1;
			}
			case WM_LBUTTONDOWN: {
				SetCapture(hWnd);
				if (mBtnState != FluentX::UI::FXButtonState::Pressed) {
					mBtnState = FluentX::UI::FXButtonState::Pressed;
					mFnOnPress(mBtnStruct);
					ReloadValues();
					InvalidateRect(hWnd, NULL, FALSE);
				}
				return 1;
			}case WM_LBUTTONUP: {
				ReleaseCapture();
				if (mBtnState == FluentX::UI::FXButtonState::Pressed) {
					mBtnState = FluentX::UI::FXButtonState::Normal;
					mFnOnClick(mBtnStruct);
					ReloadValues();
					InvalidateRect(hWnd, NULL, FALSE);
				}
				return 1;
			}case WM_MOUSEMOVE: {
				if (
					mBtnState != FluentX::UI::FXButtonState::Hovered &&
					mBtnState != FluentX::UI::FXButtonState::Pressed
					)
				{
					mBtnState = FluentX::UI::FXButtonState::Hovered;
					mFnOnHover(mBtnStruct);
					ReloadValues();
					InvalidateRect(hWnd, NULL, FALSE);
				}
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(TRACKMOUSEEVENT);
				tme.dwFlags = TME_HOVER | TME_LEAVE;
				tme.dwHoverTime = HOVER_DEFAULT;
				tme.hwndTrack = mHWnd;
				TrackMouseEvent(&tme);
				return 1;
			}case WM_MOUSEHOVER: {
				if (
					mBtnState != FluentX::UI::FXButtonState::Hovered &&
					mBtnState != FluentX::UI::FXButtonState::Pressed
					)
				{
					mBtnState = FluentX::UI::FXButtonState::Hovered;
					mFnOnHover(mBtnStruct);
					ReloadValues();
					InvalidateRect(hWnd, NULL, FALSE);
				}
				return 1;
			}case WM_MOUSELEAVE: {
				if (mBtnState != FluentX::UI::FXButtonState::Normal) {
					mBtnState = FluentX::UI::FXButtonState::Normal;
					mFnOnHoverExit(mBtnStruct);
					ReloadValues();
					InvalidateRect(hWnd, NULL, FALSE);
				}
				return 1;
			}
			case WM_PAINT: {
				PAINTSTRUCT ps;
				BeginPaint(hWnd, &ps);
				static FluentX::InternalEngines::FXD2D* eng = &FluentX::InternalEngines::FXD2D::Instance();
				ID2D1HwndRenderTarget* pRend = eng->AcquireTarget(mHWnd);
				eng->BeginPaint(pRend);
				pRend->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
				HandleNormalPaint(eng,pRend);
				eng->EndPaint(pRend);
				EndPaint(hWnd, &ps);
				return 1;
			}
			default:
				break;
			}
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		void HandleNormalPaint(FluentX::InternalEngines::FXD2D* eng, ID2D1HwndRenderTarget* pRend) {
			NormalPaintFloor(eng, pRend);
			if (mBitFlags & FX_FLAG_BTN_VINTAGE) {
				NormalPaintVintageCornerLines(eng, pRend);
			}
		}

		void NormalPaintFloor(FluentX::InternalEngines::FXD2D* eng, ID2D1HwndRenderTarget* pRend) {
			if (mBtnStyle.cornerRadius > 0) { // DEPRECATED ::: ROUNDED BTNS ARE PAINTED BY WINDOW DIRECTLY !!! ------------

				//eng->Clear(pRend, FluentX::UI::FXColorPalette::Solid::gray);
				ID2D1SolidColorBrush* brRed = eng->AcquireSolidColorBrush(pRend, FX_ID_BTN_SOLID_COl_BRUSH_RED, D2D1::ColorF::Red);
				/*RECT rect;
				GetClientRect(mHWnd, &rect);
				D2D1_RECT_F r = D2D1::RectF(
					rect.left + FX_BUTTON_ROUND_IGNORANCE,
					rect.top + FX_BUTTON_ROUND_IGNORANCE,
					rect.right - FX_BUTTON_ROUND_IGNORANCE,
					rect.bottom - FX_BUTTON_ROUND_IGNORANCE
				);
				float radius = mBtnStyle.cornerRadius - FX_BUTTON_ROUND_IGNORANCE;
				radius = std::max(radius, 0.0f);
				D2D1_ROUNDED_RECT rr= D2D1::RoundedRect(
					r,
					mBtnStyle.cornerRadius-FX_BUTTON_ROUND_IGNORANCE,
					mBtnStyle.cornerRadius-FX_BUTTON_ROUND_IGNORANCE
				);
				pRend->DrawRoundedRectangle(rr, brRed);
				pRend->FillRoundedRectangle(rr, brRed);*/
				eng->Clear(pRend, FluentX::UI::FXColorPalette::Solid::red);
			}
			else {
				eng->Clear(pRend, mBtnStyle.colorFor(mBtnState));
			}
		}

		void NormalPaintVintageCornerLines(FluentX::InternalEngines::FXD2D* eng, ID2D1HwndRenderTarget* pRend) {

			if (mBtnStyle.cornerRadius > 0) {
				NormalPaintVintageCornerLinesRounded(eng, pRend);
				return;
			}

			RECT rect;
			GetClientRect(mHWnd, &rect);
			D2D1_POINT_2F pOneLineOne; //LINE ONE - Bottom
			pOneLineOne.x = rect.left;
			pOneLineOne.y = rect.bottom;
			D2D1_POINT_2F pTwoLineOne; 
			pTwoLineOne.x = rect.right;
			pTwoLineOne.y = rect.bottom;
			D2D1_POINT_2F pOneLineTwo; //LINE TWO - RIGHT
			pOneLineTwo.x = rect.right;
			pOneLineTwo.y = rect.bottom;
			D2D1_POINT_2F pTwoLineTwo;
			pTwoLineTwo.x = rect.right;
			pTwoLineTwo.y = rect.top;
			D2D1_POINT_2F pOneLineThree = pOneLineOne; //LINE THREE - TOP
			pOneLineThree.y = rect.top;
			D2D1_POINT_2F pTwoLineThree = pTwoLineOne;
			pTwoLineThree.y = rect.top;
			D2D1_POINT_2F pOneLineFour = pOneLineTwo; //LINE FOUR - Left
			pOneLineFour.x = rect.left;
			D2D1_POINT_2F pTwoLineFour = pTwoLineTwo;
			pTwoLineFour.x = rect.left;

			D2D1_POINT_2F grayShaderPOne;
			D2D1_POINT_2F grayShaderPTwo;
			D2D1_POINT_2F grayShaderPThree;
			D2D1_POINT_2F grayShaderPFour;

			/*D2D1_POINT_2F grayShaderSecondPOne;
			D2D1_POINT_2F grayShaderSecondPTwo;
			D2D1_POINT_2F grayShaderSecondPThree;
			D2D1_POINT_2F grayShaderSecondPFour;*/

			const float grayStroke = 3.0f;
			const float half = grayStroke * 0.5f;
			float fLineWidth = std::clamp(rect.bottom * 0.06f, 1.0f, 8.0f)+3*grayStroke;
			float fLineWidthGrayDim = fLineWidth/2*1.5f;
			float fLGSHWidth = grayStroke*1.5f;

			D2D1_POINT_2F LGSh1;
			D2D1_POINT_2F LGSh2;
			D2D1_POINT_2F LGSh3;
			D2D1_POINT_2F LGSh4;


			if (isPressed()) {
				// TOP shadow
				grayShaderPOne = pOneLineThree;
				grayShaderPTwo = pTwoLineThree;
				grayShaderPOne.y += half;
				grayShaderPTwo.y += half;

				// LEFT shadow
				grayShaderPThree = pOneLineFour;
				grayShaderPFour = pTwoLineFour;
				grayShaderPThree.x += half;
				grayShaderPFour.x += half;

				LGSh1.x = pOneLineThree.x + 2 * (half)+grayStroke;
				LGSh1.y = pOneLineThree.y + 2 * (half)+grayStroke + fLGSHWidth;
				LGSh2.x = pTwoLineThree.x - 2 * (half)-grayStroke;
				LGSh2.y = pTwoLineThree.y + 2 * (half)+grayStroke + fLGSHWidth;

				LGSh3 = LGSh1;
				LGSh3.x += fLGSHWidth;
				LGSh4.x = pOneLineFour.x + 2 * (half)+grayStroke + fLGSHWidth;
				LGSh4.y = pOneLineFour.y - 2 * (half)+grayStroke - fLGSHWidth-grayStroke;
			}
			else {
				// BOTTOM shadow
				grayShaderPOne = pOneLineOne;
				grayShaderPTwo = pTwoLineOne;
				grayShaderPOne.y -= half;
				grayShaderPTwo.y -= half;

				// Right shadow
				grayShaderPThree = pOneLineTwo;
				grayShaderPFour = pTwoLineTwo;
				grayShaderPThree.x -= half;
				grayShaderPFour.x -= half;

				LGSh1.x = pOneLineOne.x + 2 * (half)+grayStroke;
				LGSh1.y = pOneLineOne.y - 2 * (half)-grayStroke - fLGSHWidth;
				LGSh2.x = pTwoLineOne.x - 2 * (half)-grayStroke;
				LGSh2.y = pTwoLineOne.y - 2 * (half)-grayStroke - fLGSHWidth;
				LGSh3 = LGSh2;
				LGSh3.x -= fLGSHWidth;
				LGSh4.x = pTwoLineTwo.x - 2 * (half)-grayStroke-fLGSHWidth;
				LGSh4.y = pTwoLineTwo.y + 2 * (half)-grayStroke + fLGSHWidth+grayStroke;

			}

			ID2D1SolidColorBrush* brLightGray = eng->AcquireSolidColorBrush(pRend, FX_ID_BTN_SOLID_COl_BRUSH_LIGHT_GRAY, D2D1::ColorF::LightGray);
			ID2D1SolidColorBrush* brGray = eng->AcquireSolidColorBrush(pRend, FX_ID_BTN_SOLID_COl_BRUSH_GRAY, D2D1::ColorF::Gray);
			ID2D1SolidColorBrush* brGrayDim = eng->AcquireSolidColorBrush(pRend, FX_ID_BTN_SOLID_COl_BRUSH_DIM_GRAY, D2D1::ColorF::DimGray);
			ID2D1SolidColorBrush* brGrayStarcDim = eng->AcquireSolidColorBrush(pRend, FX_ID_BTN_SOLID_COl_BRUSH_STARC_DIM_GRAY, D2D1::ColorF::LightSlateGray);
			ID2D1SolidColorBrush* brRed = eng->AcquireSolidColorBrush(pRend, FX_ID_BTN_SOLID_COl_BRUSH_RED, D2D1::ColorF::Red);

			auto drawLOne = [&]() {
				pRend->DrawLine(
					pOneLineOne,
					pTwoLineOne,
					this->isPressed() ? brLightGray : brGray,
					this->isPressed() ? fLineWidthGrayDim : fLineWidth
				);
				};
			auto drawLTwo = [&]() {
				pRend->DrawLine(
					pOneLineTwo,
					pTwoLineTwo,
					(this->isPressed()) ? brLightGray : brGray,
					(this->isPressed()) ? fLineWidthGrayDim : fLineWidth
				);
				};
			auto drawLThree = [&]() {
				pRend->DrawLine(
					pOneLineThree,
					pTwoLineThree,
					(this->isPressed()) ? brGray : brLightGray,
					(this->isPressed()) ? fLineWidth : fLineWidthGrayDim
				);
				};
			auto drawLFour = [&]() {
				pRend->DrawLine(
					pOneLineFour,
					pTwoLineFour,
					(this->isPressed()) ? brGray : brLightGray,
					(this->isPressed()) ? fLineWidth : fLineWidthGrayDim
				);
				};

			auto drawLineShaderOuter = [&]() {
				pRend->DrawLine(
					grayShaderPOne,
					grayShaderPTwo,
					brGrayDim,
					grayStroke
				);
				pRend->DrawLine(
					grayShaderPThree,
					grayShaderPFour,
					brGrayDim,
					grayStroke
				);
				};
			auto drawLineShaderInner = [&]() {
				pRend->DrawLine(
					LGSh1,
					LGSh2,
					brGrayStarcDim,
					fLGSHWidth
				);
				pRend->DrawLine(
					LGSh3,
					LGSh4,
					brGrayStarcDim,
					fLGSHWidth
				);
				};

			drawLineShaderInner();
			if (isPressed()) {
				drawLFour();
				drawLThree();
				drawLTwo();
				drawLOne();
			}
			else {
				drawLOne();
				drawLTwo();
				drawLThree();
				drawLFour();
			}
			drawLineShaderOuter();
		}

		void NormalPaintVintageCornerLinesRounded(FluentX::InternalEngines::FXD2D* eng, ID2D1HwndRenderTarget* target) {
			// This Function Id Deprecated and ROUNDED BUTTONS ARE PAINTED BY WINDOW Itself !!!
		}

		void fnConvUnits() {
			if (mSize.height() == FX_USE_DEFAULT) mSize.SetHeight(30);
			if (mSize.width() == FX_USE_DEFAULT) mSize.SetWidth(100);
		}

		TCHAR* fnGetClassName() {
			static TCHAR szFXBTNClassName[] = _TEXT("CLASS_FX_BUTTON");
			return szFXBTNClassName;
		}

		bool isPressed() const {
			return (mBtnState == FluentX::UI::FXButtonState::Pressed);
		}

		HWND getHWND() {
			return mHWnd;
		}

		void ReloadValues() {
			// CURRENTY NOT REQUIRED AS ALL THE VARS ARE REFERENCES 
			// JUST FOR ANY FUTURE USE 
		}

	private:
		bool& mBIsEnabled;
		std::string& mStrText;
		std::string& mStrSubText;
		FluentX::UI::FXCoords& mPosition;
		FluentX::UI::FXSize& mSize;
		FluentX::UI::FXButtonStyle& mBtnStyle;
		FluentX::UI::FXButtonState& mBtnState;
		FluentX::UI::FXButton& mBtnStruct;
		std::function<void(FluentX::UI::FXButtonBase& btn)>& mFnOnClick;
		std::function<void(FluentX::UI::FXButtonBase& btn)>& mFnOnPress;
		std::function<void(FluentX::UI::FXButtonBase& btn)>& mFnOnHover;
		std::function<void(FluentX::UI::FXButtonBase& btn)>& mFnOnHoverExit;

		WNDCLASS mBtnClass = {};
		HWND mHWnd = {};
		HWND mHParentWND = {};
		HINSTANCE mHInstance = {};
		bool InitFailed = false;
		FX_FLAG mBitFlags;
	};

	LRESULT CALLBACK FX_BUTTON_WINDOW_PROC(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
		FXPButton* btn = nullptr;

		if (msg == WM_NCCREATE) {
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			btn = static_cast<FXPButton*>(cs->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)btn);
		}
		else
		{
			btn = reinterpret_cast<FXPButton*>(
				GetWindowLongPtr(hWnd, GWLP_USERDATA)
				);
		}
		if (btn)
			return btn->WndProc(hWnd, msg, wParam, lParam);

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

#endif // !FX_PLATFORM_BUTTON_HEADER
