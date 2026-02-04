#include "FXPaddingWidget.h"
#include "FXElementLayoutTree.h"
#include <iostream>

void FluentX::UI::FXPaddingWidget::layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const
{
    if (!child) return;

    std::cout << "PaddingWidget Layout -> x:" << x << " y:" << y
        << " availW:" << availW << " availH:" << availH << "\n";

    FXRECURSIVELayoutWidgets(
        *child,
        x + padding.left,
        y + padding.top,
        availW - (padding.left + padding.right),
        availH - (padding.top + padding.bottom),
        tree,
        baseZ
    );
}

