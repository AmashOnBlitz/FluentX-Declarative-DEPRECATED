#ifndef FX_PLATFORM_UI_SERVICE_HEADER
#define FX_PLATFORM_UI_SERVICE_HEADER

#include "FXNamespaces.h"
#include "FXPlatform_Button.h"
#include "FXPlatform_Window.h"
#include "FXElementLayoutTree.h"
#include "FXButton.h"

namespace FluentX::platform {

	struct FXPlatformWidgetEntry {
		HWND hwnd;
		int z;
		FluentX::UI::FXWidgetBase* widget;
	};

	class FXUIService {
	public:
		FXUIService(FXPWindow& parentWnd, FluentX::layout::FXElementLayoutTree& layoutTree)
			: mParentWnd(parentWnd),
			mLayoutTree(layoutTree)
		{

		}
		void UIStartService() {
			auto& elements = mLayoutTree.elements;

			std::sort(elements.begin(), elements.end(),
					  [](const auto& a, const auto& b) {
						  return a.first.z < b.first.z;
					  });
			for (auto& widget : elements) {
				if (widget.second->type == FluentX::UI::FX_TYPE_BUTTON) {
					FluentX::UI::FXButton* BtnWidget = static_cast<FluentX::UI::FXButton*>(widget.second);
					BtnWidget->position = { widget.first.x, widget.first.y };
					BtnWidget->size.SetWidth(widget.first.width);
					BtnWidget->size.SetHeight(widget.first.height);
					if (BtnWidget->style.cornerRadius > 0) {

					}
					FX_FLAG flags = 0;
					if (BtnWidget->style.variant == FluentX::UI::FXBUTTONVARIANT_Normal) {
						flags |= FX_FLAG_BTN_NORMAL;
					}
					else if (BtnWidget->style.variant == FluentX::UI::FXBUTTONVARIANT_Vintage) {
						flags |= FX_FLAG_BTN_VINTAGE;
					}
					FXPButton* btn = new FXPButton(
						BtnWidget->text,
						BtnWidget->subText,
						BtnWidget->position,
						BtnWidget->enabled,
						BtnWidget->size,
						BtnWidget->style,
						BtnWidget->state,
						BtnWidget->onClick,
						BtnWidget->onPress,
						BtnWidget->onHover,
						BtnWidget->onHoverExit,
						mParentWnd.mHWnd,
						flags,
						*BtnWidget
					);
					vectWidgets.push_back({
						btn->getHWND(),     
						widget.first.z,     
						widget.second       
										  });
				}
			}
			SortWidgetsByZOrder();
			enforceZLayer();
		}

		void SortWidgetsByZOrder() {
			std::sort(vectWidgets.begin(), vectWidgets.end(),
					  [](const FXPlatformWidgetEntry& a,
						 const FXPlatformWidgetEntry& b) {
							 return a.z < b.z;
					  });
		}

		void enforceZLayer() {
			for (size_t i = 0; i < vectWidgets.size(); ++i) {
				SetWindowPos(
					vectWidgets[i].hwnd,
					(i == 0) ? HWND_BOTTOM : vectWidgets[i - 1].hwnd,
					0, 0, 0, 0,
					SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE
				);
			}
		}

	public:
		FXPWindow& mParentWnd;
		FluentX::layout::FXElementLayoutTree& mLayoutTree;
		//std::vector <std::pair<HWND, FluentX::UI::FXWidgetBase&>> vectWidgets
		std::vector<FXPlatformWidgetEntry> vectWidgets;
	};

}

#endif // !FX_PLATFORM_UI_SERVICE_HEADER
