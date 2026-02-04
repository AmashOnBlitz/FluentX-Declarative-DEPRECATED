#ifndef FX_LIGHT_SORUCE_DECL
#define FX_LIGHT_SORUCE_DECL

#include "FXNamespaces.h"
#include "FXColor.h"
#include "FXCoordinates.h"

namespace FluentX::UI {

	struct FXLightSource {
		FXColor color = FXColorPalette::Solid::whiteSmoke;
		FXCoords position = { 0,0 };
	};

}

#endif // !FX_LIGHT_SORUCE_DECL

