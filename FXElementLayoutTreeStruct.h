#ifndef FX_ELEMENT_TREE_STRUCT_DECL
#define FX_ELEMENT_TREE_STRUCT_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include <vector>

namespace FluentX::layout {

	struct FXElementPlacementProperties {
		int x = 0;
		int y = 0;
		int z = 0;
		int width = 0;
		int height = 0;
		bool worthyToRender = true;
	};

	struct FXElementLayoutTree {
		std::vector<std::pair<FXElementPlacementProperties, UI::FXWidgetBase*>> elements;
	};

}

#endif // !FX_ELEMENT_TREE_STRUCT_DECL
