#include "FXRectangle.h"
#include "FXElementLayoutTree.h"

void FluentX::UI::FXRectangle::layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const
{
	if (!child) return;
	FXRECURSIVELayoutWidgets(
		*child,
		x,
		y,
		availW,
		availH,
		tree,
		baseZ
	);
}
