#ifndef FX_RECTANGLE_DECL
#define FX_RECTANGLE_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include "FXColor.h"
#include "FXCoordinates.h"
#include "FXColorPalette.h"
#include "FXRegistrar.h"
#include <memory>

namespace FluentX::UI {

	struct FXRectangle : FXWidgetBase {
	public:
		FXColor color = FXColorPalette::IceCream::babyBlue;
		FXCoords position = { 0,0 };
		FXSize size = FXSize(100, 30);
		int cornerRadius = 4;
		bool cornerRounded = false;
		std::unique_ptr<FXWidgetBase> child;
		bool isContainer() const override { return true; }
		void layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const override;
	};

	struct FXRectangleBuilder {
	private:
		FXRectangle zInternals_rect;
		FXRectangleBuilder& zself() {
			return (*this);
		}
	public:
		FXRectangleBuilder& color(FXColor col) {
			zInternals_rect.color = col;
			return zself();
		}
		FXRectangleBuilder& position(FXCoords coordinates) {
			zInternals_rect.position = coordinates;
			return zself();
		}
		FXRectangleBuilder& size(FXSize size) {
			zInternals_rect.size = size;
			return zself();
		}
		FXRectangleBuilder& size(int width, int height) {
			zInternals_rect.size = FXSize(width, height);
			return zself();
		}
		FXRectangleBuilder& cornerRadius(int val) {
			zInternals_rect.cornerRadius = val;
			return zself();
		}
		FXRectangleBuilder& cornerRounded(bool b) {
			zInternals_rect.cornerRounded = b;
			return zself();
		}
		FXRectangleBuilder& child(std::unique_ptr<FXWidgetBase> child) {
			zInternals_rect.child = std::move(child);
			return zself();
		}
		std::unique_ptr<FXRectangle> build(FXWidgetID& idVar) {
			auto widget		= std::make_unique<FXRectangle>(std::move(zInternals_rect));
			widget->type	= FX_TYPE_RECTANGLE;
			widget->id = FluentX::Registrar::GenerateUniqueId();
			idVar = widget->id;
			FluentX::Registrar::RegisterWidget(widget->id, widget.get());
			return widget;
		}
		std::unique_ptr<FXRectangle> build() {
			FXWidgetID buff;
			return build(buff);
		}
		FXRectangle buildVariable() {
			return std::move(zInternals_rect);
		}
	};

	inline FXRectangleBuilder			FXCreateRectangle() { return FXRectangleBuilder{}; }
	inline std::unique_ptr<FXRectangle> FXCreateRectangle(FXRectangle& rect, FXWidgetID& idVar) {
		auto widget = std::make_unique<FXRectangle>(std::move(rect));
		widget->type = FX_TYPE_RECTANGLE;
		widget->id = FluentX::Registrar::GenerateUniqueId();
		idVar = widget->id;
		FluentX::Registrar::RegisterWidget(widget->id, widget.get());
		return widget;
	}
	inline std::unique_ptr<FXRectangle> FXCreateRectangle(FXRectangle& rect) {
		FXWidgetID buff;
		return FXCreateRectangle(rect, buff);
	}
}
#endif // !FX_RECTANGLE_DECL
