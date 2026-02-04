#ifndef FX_PADDING_WIDGET_DECL
#define FX_PADDING_WIDGET_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include "FXPadding.h"
#include <memory>
#include "FXRegistrar.h"

namespace FluentX::UI {

	struct FXPaddingWidget : public FXWidgetBase {
	public:
		FXPadding padding = {20,20,20,20};
		std::unique_ptr<FXWidgetBase> child;
		bool isContainer() const override { return true; }
		void layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const override;
	};

	struct FXPaddingWidgetBuilder {
	private:
		FXPaddingWidget zInternals_padding;

	public:
		FXPaddingWidgetBuilder& padding(const FXPadding& p) {
			zInternals_padding.padding = p;
			return *this;
		}

		FXPaddingWidgetBuilder& child(std::unique_ptr<FXWidgetBase> c) {
			zInternals_padding.child = std::move(c);
			return *this;
		}

		std::unique_ptr<FXPaddingWidget> build(FXWidgetID& idVar) {
			auto widget = std::make_unique<FXPaddingWidget>(std::move(zInternals_padding));
			widget->type = FX_TYPE_PADDING;
			widget->id = FluentX::Registrar::GenerateUniqueId();
			idVar = widget->id;
			FluentX::Registrar::RegisterWidget(widget->id, widget.get());
			return widget;
		}

		std::unique_ptr<FXPaddingWidget> build() {
			FXWidgetID dummy;
			return build(dummy);
		}

		FXPaddingWidget buildVariable() {
			return std::move(zInternals_padding);
		}
	};

	inline FXPaddingWidgetBuilder FXCreatePaddingWidget() {
		return FXPaddingWidgetBuilder{};
	}

	inline std::unique_ptr<FXPaddingWidget> FXCreatePaddingWidget(
		FXPaddingWidget& paddingWidget,
		FXWidgetID& idVar
	) {
		auto widget = std::make_unique<FXPaddingWidget>(std::move(paddingWidget));
		widget->type = FX_TYPE_PADDING;
		widget->id = FluentX::Registrar::GenerateUniqueId();
		idVar = widget->id;
		FluentX::Registrar::RegisterWidget(widget->id, widget.get());
		return widget;
	}

	inline std::unique_ptr<FXPaddingWidget> FXCreatePaddingWidget(FXPaddingWidget& paddingWidget) {
		FXWidgetID buff;
		return FXCreatePaddingWidget(paddingWidget, buff);
	}

}

#endif // !FX_PADDING_WIDGET_DECL
