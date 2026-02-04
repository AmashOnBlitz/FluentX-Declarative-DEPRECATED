#ifndef FX_COORDS_DECL
#define FX_COORDS_DECL

#include "FXNamespaces.h"

namespace FluentX::UI {
	struct FXCoords {
		int x = 0;
		int y = 0;
		FXCoords(int _x, int _y) {
			this->x = _x;
			this->y = _y;
		}
	};
}

#endif // !FX_COORDS_DECL
