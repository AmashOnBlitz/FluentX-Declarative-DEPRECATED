#ifndef TEXT_EDIT_DECL_HEADER
#define TEXT_EDIT_DECL_HEADER

#include "FXNamespaces.h"
#include "FXWidget.h"
#include <string>
#include <functional>
#include <memory>
#include "FXLightSource.h"

namespace FluentX::UI {

	struct FXTextEditStyle {

		FXColor colorBackground = FXColor{ 255, 255, 255, 255 };
		FXColor colorText = FXColor{ 0, 0, 0, 255 };
		FXColor colorBorder = FXColor{ 200, 200, 200, 255 };
		FXColor colorHover = FXColor{ 220, 220, 220, 255 };
		FXColor colorFocus = FXColor{ 180, 200, 255, 255 };
		FXColor colorDisabled = FXColor{ 240, 240, 240, 255 };

		int cornerRadius = 4;
		bool cornerRounded = false;

		bool copyEnabled = true;
		bool pasteEnabled = true;
		bool selectEnabled = true;
		bool undoRedoEnabled = true;
		bool multiLine = false;
		bool passwordMode = false;

		int paddingTop = 4;
		int paddingBottom = 4;
		int paddingLeft = 4;
		int paddingRight = 4;

		int fontSize = 14;
		bool bold = false;
		bool italic = false;
		bool underline = false;

		bool reflectionPhysics = false;
		FXLightSource lightSource;
	};

	struct FXTextEditStyleBuilder {
	private:
		FXTextEditStyle zInternals_Style;
	public:
		FXTextEditStyleBuilder& colorBackground(const FXColor& c) { zInternals_Style.colorBackground = c; return *this; }
		FXTextEditStyleBuilder& colorText(const FXColor& c) { zInternals_Style.colorText = c; return *this; }
		FXTextEditStyleBuilder& colorBorder(const FXColor& c) { zInternals_Style.colorBorder = c; return *this; }
		FXTextEditStyleBuilder& colorHover(const FXColor& c) { zInternals_Style.colorHover = c; return *this; }
		FXTextEditStyleBuilder& colorFocus(const FXColor& c) { zInternals_Style.colorFocus = c; return *this; }
		FXTextEditStyleBuilder& colorDisabled(const FXColor& c) { zInternals_Style.colorDisabled = c; return *this; }

		FXTextEditStyleBuilder& cornerRadius(int r) { zInternals_Style.cornerRadius = r; return *this; }
		FXTextEditStyleBuilder& cornerRounded(bool enable = true) { zInternals_Style.cornerRounded = enable; return *this; }

		FXTextEditStyleBuilder& copyEnabled(bool enable = true) { zInternals_Style.copyEnabled = enable; return *this; }
		FXTextEditStyleBuilder& pasteEnabled(bool enable = true) { zInternals_Style.pasteEnabled = enable; return *this; }
		FXTextEditStyleBuilder& selectEnabled(bool enable = true) { zInternals_Style.selectEnabled = enable; return *this; }
		FXTextEditStyleBuilder& undoRedoEnabled(bool enable = true) { zInternals_Style.undoRedoEnabled = enable; return *this; }
		FXTextEditStyleBuilder& multiLine(bool enable = true) { zInternals_Style.multiLine = enable; return *this; }
		FXTextEditStyleBuilder& passwordMode(bool enable = true) { zInternals_Style.passwordMode = enable; return *this; }

		FXTextEditStyleBuilder& paddingTop(int val) { zInternals_Style.paddingTop = val; return *this; }
		FXTextEditStyleBuilder& paddingBottom(int val) { zInternals_Style.paddingBottom = val; return *this; }
		FXTextEditStyleBuilder& paddingLeft(int val) { zInternals_Style.paddingLeft = val; return *this; }
		FXTextEditStyleBuilder& paddingRight(int val) { zInternals_Style.paddingRight = val; return *this; }

		FXTextEditStyleBuilder& fontSize(int val) { zInternals_Style.fontSize = val; return *this; }
		FXTextEditStyleBuilder& bold(bool enable = true) { zInternals_Style.bold = enable; return *this; }
		FXTextEditStyleBuilder& italic(bool enable = true) { zInternals_Style.italic = enable; return *this; }
		FXTextEditStyleBuilder& underline(bool enable = true) { zInternals_Style.underline = enable; return *this; }

		FXTextEditStyleBuilder& reflectionPhysics(bool enable, FXLightSource lightSrc) {
			zInternals_Style.lightSource = lightSrc;
			zInternals_Style.reflectionPhysics = enable;
			return *this; 
		}
		FXTextEditStyleBuilder& lightSource(FXLightSource lightSrc) { zInternals_Style.lightSource = lightSrc; return *this; }

		// Build
		FXTextEditStyle build() {
			return zInternals_Style;
		}
	};


	inline FXTextEditStyleBuilder FXCreateTextEditStyle() {
		return FXTextEditStyleBuilder{};
	}

	struct FXTextEditBase : public FXWidgetBase {
	public:
		std::string text;
		bool enabled = true;
		FXCoords position = { 0,0 };
		FXTextEditStyle style = FXCreateTextEditStyle().build();
		std::function<void(FXTextEditBase&)> onTextChanged = [](FXTextEditBase&) {};
		std::function<void(FXTextEditBase&)> onFocusGain = [](FXTextEditBase&) {};
		std::function<void(FXTextEditBase&)> onFocusLost = [](FXTextEditBase&) {};
	};

	template <typename TextEditType, typename TextEditBuilderType>
	struct FXLineEditBuilderBase {
	protected:
		TextEditType zInternals_edit;
		TextEditBuilderType& zSelf() {
			return (TextEditBuilderType&)(*this);
		}
	public:
		TextEditBuilderType& text(const std::string txt) {
			zInternals_edit.text = txt;
			return zSelf();
		}
		TextEditBuilderType& style(FXTextEditStyle Style) {
			zInternals_edit.style = Style;
		}
		TextEditBuilderType& position(int x, int y) {
			zInternals_edit.position.x = x;
			zInternals_edit.position.y = y;
			return zSelf();
		}
		TextEditBuilderType& position(FXCoords pos) {
			zInternals_edit.position = pos;
			return zSelf();
		}
		TextEditBuilderType& enabled(bool val) {
			zInternals_edit.enabled = val;
			return zSelf();
		}
		std::unique_ptr <TextEditType> build() {
			zInternals_edit.type = FX_TYPE_BUTTON;
			return std::make_unique<TextEditType>(std::move(zInternals_edit));
		}
	};

}

#endif // !TEXT_EDIT_DECL_HEADER
