#ifndef FX_SPACER_DECL
#define FX_SPACER_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include <memory>

namespace FluentX::UI{
	struct FXSpacer : public FXWidgetBase {
	public:
		int width = FX_USE_DEFAULT;
		int height = FX_USE_DEFAULT;
		void layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const override {
			if (!tree.elements.empty()) {
				auto& lastElement = tree.elements.back();

				if (lastElement.second == this) {
					int finalWidth = (width > 0) ? width : availW;
					int finalHeight = (height > 0) ? height : availH;

					lastElement.first.width = finalWidth;
					lastElement.first.height = finalHeight;
				}
			}
		}
	};
	struct FXSpacerBuilder {
	private:
		FXSpacer zInternals_sp;
	public:
		FXSpacerBuilder& width(const int val) {
			zInternals_sp.width = val;
			return *this;
		}
		FXSpacerBuilder& height(const int val) {
			zInternals_sp.height = val;
			return *this;
		}
		std::unique_ptr<FXSpacer> build(FXWidgetID& idVar) {
			auto widget = std::make_unique<FXSpacer>(std::move(zInternals_sp));
			widget->type = FX_TYPE_SPACER;
			widget->id = FluentX::Registrar::GenerateUniqueId();
			idVar = widget->id;
			FluentX::Registrar::RegisterWidget(widget->id, widget.get());
			return widget;
		};
		std::unique_ptr<FXSpacer> build() {
			FXWidgetID dummy;
			return build(dummy);
		}
		FXSpacer buildVariable(){
			return std::move(zInternals_sp);
		}
	};
	inline FXSpacerBuilder				FXCreateSpacer() { return FXSpacerBuilder{}; }
	inline std::unique_ptr<FXSpacer>	FXCreateSpacer(FXSpacer& spacer, FXWidgetID& idVar) {
		auto widget =  std::make_unique<FXSpacer>(std::move(spacer));
		widget->type = FX_TYPE_SPACER;
		widget->id = FluentX::Registrar::GenerateUniqueId();
		idVar = widget->id;
		FluentX::Registrar::RegisterWidget(widget->id, widget.get());
		return widget;
	}
	inline std::unique_ptr<FXSpacer>	FXCreateSpacer(FXSpacer& spacer){
		FXWidgetID buff;
		return FXCreateSpacer(spacer, buff);
	}
}

#endif // !FX_SPACER_DECL
