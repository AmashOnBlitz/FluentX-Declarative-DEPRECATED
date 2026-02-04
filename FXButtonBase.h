#ifndef FX_BUTTON_BASE_DECL
#define FX_BUTTON_BASE_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include "FXColor.h"
#include "FXColorPalette.h"
#include "FXHStack.h"
#include "FXCoordinates.h"
#include <functional>
#include <optional>
#include <memory>
#include "FXLightSource.h"

namespace FluentX::UI {

	enum class FXButtonState {
		Normal,
		Hovered,
		Pressed,
		Disabled
	};

	enum FXButtonVariant {
		FXBUTTONVARIANT_Normal,
		FXBUTTONVARIANT_Vintage,
		FXBUTTONVARIANT_Modern,
	};

	struct FXButtonStyle {
		int cornerRadius = FX_USE_DEFAULT; //equates to no corner radius

		FXColor baseColor = FXColorPalette::Fluent::primary;
		FXColor hoverColor = FXColorPalette::Fluent::accent;
		FXColor pressedColor = FXColorPalette::Fluent::pressedAccent;
		FXColor disabledColor = FXColorPalette::Fluent::backgroundSoft;

		FXButtonVariant variant = FXBUTTONVARIANT_Normal;

		FXColor textColor = FXColor(255, 255, 255, 255);
		FXColor subTextColor = FXColor(220, 230, 240, 255);   

		bool reflectionPhysics = false;
		std::optional<FXLightSource> lightSource;

		const FXColor& colorFor(FXButtonState state) const {
			switch (state) {
			case FXButtonState::Hovered:  return hoverColor;
			case FXButtonState::Pressed:  return pressedColor;
			case FXButtonState::Disabled: return disabledColor;
			default:                      return baseColor;
			}
		}
	};

	struct FXButtonStyleBuilder {
	private:
		FXButtonStyle style;

	public:
		FXButtonStyleBuilder& rounded(int radius) {
			style.cornerRadius = radius;
			return *this;
		}

		FXButtonStyleBuilder& base(const FXColor& c) {
			style.baseColor = c;
			return *this;
		}

		FXButtonStyleBuilder& hover(const FXColor& c) {
			style.hoverColor = c;
			return *this;
		}

		FXButtonStyleBuilder& pressed(const FXColor& c) {
			style.pressedColor = c;
			return *this;
		}

		FXButtonStyleBuilder& disabled(const FXColor& c) {
			style.disabledColor = c;
			return *this;
		}

		FXButtonStyleBuilder& text(const FXColor& c) {
			style.textColor = c;
			return *this;
		}
		FXButtonStyleBuilder& variant(FXButtonVariant FXBUTTONVARIANT) {
			style.variant = FXBUTTONVARIANT;
			return *this;
		}

		FXButtonStyleBuilder& reflection(bool enabled) {
			style.reflectionPhysics = enabled;
			return *this;
		}

		FXButtonStyleBuilder& light(const FXLightSource& src) {
			style.lightSource = src;
			return *this;
		}

		FXButtonStyle build() {
			return style;
		}
	};

	inline FXButtonStyleBuilder FXCreateButtonStyle() {
		return FXButtonStyleBuilder{};
	}

	struct FXButtonBase : FXWidgetBase {
	public:
		FXCoords position = { 0,0 };
		FXSize   size = FXSize(FX_USE_DEFAULT, FX_USE_DEFAULT);
		bool     enabled = true;

		std::string text;
		std::string subText;

		FXButtonStyle style;
		FXButtonState state = FXButtonState::Normal;

		std::function<void(FXButtonBase&)> onClick = [](FXButtonBase&) {};
		std::function<void(FXButtonBase&)> onPress = [](FXButtonBase&) {};
		std::function<void(FXButtonBase&)> onHover = [](FXButtonBase&) {};
		std::function<void(FXButtonBase&)> onHoverExit = [](FXButtonBase&) {};

		FXButtonBase() {
			minSize = FXSize(80, 32);
			maxSize = FXSize(FX_USE_DEFAULT, FX_USE_DEFAULT);
		}

		bool isContainer() const override { return false; }
	};

	template <typename ButtonType,typename BuilderType>
	struct FXButtonBuilderBase {
	protected:
		ButtonType Zinternals_Btn;
		BuilderType& zSelf() {
			return (BuilderType&)(*this);
		}
	public:
		BuilderType& size(const FXSize& size) {
			Zinternals_Btn.size = size;
			return zSelf();
		}
		BuilderType& position(int x, int y) {
			Zinternals_Btn.position.x = x;
			Zinternals_Btn.position.y = y;
			return zSelf();
		}
		BuilderType& position(FXCoords pos) {
			Zinternals_Btn.position = pos;
			return zSelf();
		}
		BuilderType& enabled(bool value) {
			Zinternals_Btn.enabled = value;
			return zSelf();
		}
		BuilderType& onClick(std::function<void(ButtonType& btn)> VoidCallback) {
			Zinternals_Btn.onClick = [VoidCallback](FXButtonBase& baseBtn) {
				if (auto derived = dynamic_cast<ButtonType*>(&baseBtn)) {
					VoidCallback(*derived);
				}
				};
			return zSelf();
		}

		BuilderType& onPress(std::function<void(ButtonType& btn)> VoidCallback) {
			Zinternals_Btn.onPress = [VoidCallback](FXButtonBase& baseBtn) {
				if (auto derived = dynamic_cast<ButtonType*>(&baseBtn)) {
					VoidCallback(*derived);
				}
				};
			return zSelf();
		}

		BuilderType& onHover(std::function<void(ButtonType& btn)> VoidCallback) {
			Zinternals_Btn.onHover = [VoidCallback](FXButtonBase& baseBtn) {
				if (auto derived = dynamic_cast<ButtonType*>(&baseBtn)) {
					VoidCallback(*derived);
				}
				};
			return zSelf();
		}

		BuilderType& onHoverExit(std::function<void(ButtonType& btn)> VoidCallback) {
			Zinternals_Btn.onHoverExit = [VoidCallback](FXButtonBase& baseBtn) {
				if (auto derived = dynamic_cast<ButtonType*>(&baseBtn)) {
					VoidCallback(*derived);
				}
				};
			return zSelf();
		}

		BuilderType& style(const FXButtonStyle& style) {
			Zinternals_Btn.style = style;
			return zSelf();
		}

		BuilderType& text(const std::string& t) {
			Zinternals_Btn.text = t;
			return zSelf();
		}

		BuilderType& subText(const std::string& t) {
			Zinternals_Btn.subText = t;
			return zSelf();
		}
		BuilderType& minSize(const FXSize& s) {
			Zinternals_Btn.minSize = s;
			return zSelf();
		}

		BuilderType& maxSize(const FXSize& s) {
			Zinternals_Btn.maxSize = s;
			return zSelf();
		}
		std::unique_ptr<ButtonType> build() {
			Zinternals_Btn.type = FX_TYPE_BUTTON;
			return std::make_unique<ButtonType>(std::move(Zinternals_Btn));
		}
	};
}

#endif // !FX_BUTTON_BASE_DECL
