#ifndef FX_ROUNDED_BUTTONS_DECL
#define FX_ROUNDED_BUTTONS_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include "FXColor.h"
#include "FXColorPalette.h"
#include <functional>
#include <optional>

namespace FluentX::UI {

	struct FXButtonRounded : public FXButton {
	public:
		int CornerRadius  = 10;
	};

	struct RoundedButtonBuilder : public FXButtonBuilderBase<FXButtonRounded,RoundedButtonBuilder>{
		
		RoundedButtonBuilder& cornerRadius(int value) {
			Zinternals_Btn.CornerRadius = value;
			return *this;
		}

		std::unique_ptr<FXButtonRounded> build(FXWidgetID& idVar) {
			auto widget = std::make_unique<FXButtonRounded>(std::move(Zinternals_Btn));
			widget->type = FX_TYPE_BUTTON_ROUNDED;
			widget->id = FluentX::Registrar::GenerateUniqueId();
			idVar = widget->id;
			FluentX::Registrar::RegisterWidget(widget->id, widget.get());
			return widget;
		}
		std::unique_ptr<FXButtonRounded> build() {
			FXWidgetID buff;
			return build(buff);
		}
		FXButtonRounded buildVariable() {
			return std::move(Zinternals_Btn);
		}
	};

	inline RoundedButtonBuilder				FXCreateButtonRounded() { return RoundedButtonBuilder{}; }
	inline std::unique_ptr<FXButtonRounded> FXCreateButtonRounded(FXButtonRounded& roundedButton, FXWidgetID& idVar) {
		auto widget = std::make_unique<FXButtonRounded>(std::move(roundedButton));
		widget->type = FX_TYPE_BUTTON_ROUNDED;
		widget->id = FluentX::Registrar::GenerateUniqueId();
		idVar = widget->id;
		FluentX::Registrar::RegisterWidget(widget->id, widget.get());
		return widget;
	}
	inline std::unique_ptr<FXButtonRounded> FXCreateButtonRounded(FXButtonRounded& roundedButton) {
		FXWidgetID buff;
		return FXCreateButtonRounded(roundedButton, buff);
	}

}

#endif // !FX_ROUNDED_BUTTONS_DECL
