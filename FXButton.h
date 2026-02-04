#ifndef FX_BUTTON_DECL
#define FX_BUTTON_DECL

#include "FXNamespaces.h"
#include "FXColor.h"
#include <functional>
#include <optional>
#include "FXSize.h"
#include "FXColorPalette.h"
#include <memory>
#include "FXButtonBase.h"

namespace FluentX::UI {

	struct FXButton : public FXButtonBase {
	};

	struct FXButtonBuilder : public FXButtonBuilderBase<FXButton,FXButtonBuilder> {
		std::unique_ptr<FXButton> build(FXWidgetID& idVar) {
			auto widget = std::make_unique<FXButton>(std::move(Zinternals_Btn));
			widget->type = FX_TYPE_BUTTON;
			widget->id = FluentX::Registrar::GenerateUniqueId();
			idVar = widget->id;
			FluentX::Registrar::RegisterWidget(widget->id, widget.get());
			return widget;
		}
		std::unique_ptr<FXButton> build() {
			FXWidgetID buff;
			return build(buff);
		}
		FXButton buildVariable() {
			return std::move(Zinternals_Btn);
		}
	};

	inline FXButtonBuilder				FXCreateButton() { return FXButtonBuilder{}; }
	inline std::unique_ptr<FXButton>	FXCreateButton(FXButton& button,FXWidgetID& idVar) {
		auto widget = std::make_unique<FXButton>(std::move(button));
		widget->type = FX_TYPE_BUTTON;
		widget->id = FluentX::Registrar::GenerateUniqueId();
		idVar = widget->id;
		FluentX::Registrar::RegisterWidget(widget->id, widget.get());
		return widget;
	}
	inline std::unique_ptr<FXButton>	FXCreateButton(FXButton& button) {
		FXWidgetID buff;
		return FXCreateButton(button, buff);
	}
}

#endif // !FX_BUTTON_DECL
