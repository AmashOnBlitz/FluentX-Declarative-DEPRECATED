#ifndef FX_COLOR_DECl
#define FX_COLOR_DECl

#include <d2d1.h>
#include "FXNamespaces.h"

namespace FluentX::UI {

	struct FXColor {
		int r;
		int g;
		int b;
		int a;
	};

	struct ColorBuilder {
	private:
		FXColor Zinternals_Color;
	public:
		ColorBuilder& r(const int& value) { Zinternals_Color.r = value; return *this; }
		ColorBuilder& g(const int& value) { Zinternals_Color.g = value; return *this; }
		ColorBuilder& b(const int& value) { Zinternals_Color.b = value; return *this; }
		ColorBuilder& a(const int& value) { Zinternals_Color.a = value; return *this; }
		FXColor build() const { return Zinternals_Color; }
	};

	inline ColorBuilder FXCreateColor() {
		return ColorBuilder{};
	}
} // namespace FluentX::UI

#endif // !FX_COLOR_DECl
