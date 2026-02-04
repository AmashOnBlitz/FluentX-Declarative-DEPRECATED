#ifndef FX_PADDING_DECL
#define FX_PADDING_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"

namespace FluentX::UI {

	struct FXPadding {
		int top = 0;
		int bottom = 0;
		int right = 0;
		int left = 0;
	};
	struct FXPaddingBuilder {
	private:
		FXPadding zInternals_p;
	public:
		FXPaddingBuilder& top(int val) {
			zInternals_p.top = val;
			return *this;
		}
		FXPaddingBuilder& bottom(int val) {
			zInternals_p.bottom = val;
			return *this;
		}
		FXPaddingBuilder& right(int val) {
			zInternals_p.right = val;
			return *this;
		}
		FXPaddingBuilder& left(int val) {
			zInternals_p.left = val;
			return *this;
		}
		FXPadding build() { return zInternals_p; }
	};
	inline FXPaddingBuilder FXCreatePadding() { return FXPaddingBuilder{}; }

}

#endif // !FX_PADDING_DECL
