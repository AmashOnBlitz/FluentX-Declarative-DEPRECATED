#ifndef FX_IMAGE_WIDGET_DECL
#define FX_IMAGE_WIDGET_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include <string>
#include <memory>
#include "FXCoordinates.h"
#include "FXRegistrar.h"

namespace FluentX::UI {

	enum IMAGESTYLE {
		IMAGESTYLE_FIT,
		IMAGESTYLE_STRECHTOFILL
	};

	struct FXImage : public FXWidgetBase {
	public:
		std::string sourceFile = "none";
		IMAGESTYLE style = IMAGESTYLE_STRECHTOFILL;
		FXSize size = FXSize(200, 60); 
		FXCoords position = { 0,0 };
	};

	struct FXImageBuilder {
	private:
		FXImage zInternals_img;
	public:
		FXImageBuilder& sourceFile(std::string filePath) {
			zInternals_img.sourceFile = filePath;
			return *this;
		}
		FXImageBuilder& style(IMAGESTYLE imageStyle) {
			zInternals_img.style = imageStyle;
			return *this;
		}
		FXImageBuilder& position(int x, int y) {
			zInternals_img.position.x = x;
			zInternals_img.position.y = y;
			return *this;
		}
		FXImageBuilder& position(FXCoords pos) {
			zInternals_img.position = pos;
			return *this;
		}
		FXImageBuilder& size(FXSize val) {
			zInternals_img.size = val;
			return *this;
		}
		std::unique_ptr<FXImage> build(FXWidgetID& idVar) {
			auto widget = std::make_unique<FXImage>(std::move(zInternals_img));
			widget->type = FX_TYPE_IMAGE;
			widget->id = FluentX::Registrar::GenerateUniqueId();
			idVar = widget->id;
			FluentX::Registrar::RegisterWidget(widget->id, widget.get());
			return widget;
		}
		std::unique_ptr<FXImage> build() {
			FXWidgetID buff;
			return build(buff);
		}
		FXImage buildVariable() {
			return std::move(zInternals_img);
		}
	};

	inline FXImageBuilder FXCreateImage() {return FXImageBuilder{};}
	inline std::unique_ptr<FXImage> FXCreateImage(FXImage& image, FXWidgetID& idVar) {
		auto widget = std::make_unique<FXImage>(std::move(image));
		widget->type = FX_TYPE_IMAGE;
		widget->id = FluentX::Registrar::GenerateUniqueId();
		idVar = widget->id;
		FluentX::Registrar::RegisterWidget(widget->id, widget.get());
		return widget;
	}
	inline std::unique_ptr<FXImage> FXCreateImage(FXImage& image) {
		FXWidgetID buff;
		return FXCreateImage(image, buff);
	}
}

#endif // !FX_IMAGE_WIDGET_DECl
