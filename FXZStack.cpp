#include "FXZStack.h"
#include "FXElementLayoutTree.h"

void FluentX::UI::FXZStack::layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const {
    
    int localZ = 0;
    for (const auto& zChild : children) {
        const auto& child = zChild.widget;
        
        if (!child || !child->visible) {
            continue;
        }
        int childWidth = availW;
        int childHeight = availH;

        if (childWidth < child->minSize.width()) {
            childWidth = child->minSize.width();
        }
        if (childHeight < child->minSize.height()) {
            childHeight = child->minSize.height();
        }
        
        if (child->maxSize.width() != FX_USE_DEFAULT && childWidth > child->maxSize.width()) {
            childWidth = child->maxSize.width();
        }
        if (child->maxSize.height() != FX_USE_DEFAULT && childHeight > child->maxSize.height()) {
            childHeight = child->maxSize.height();
        }
        
        int childX = x;
        int childY = y;
        
        if (childWidth < availW) {
            childX = x + (availW - childWidth) / 2;
        }
        if (childHeight < availH) {
            childY = y + (availH - childHeight) / 2;
        }
        FXRECURSIVELayoutWidgets(
            *child,
            childX,
            childY,
            childWidth,
            childHeight,
            tree,
            baseZ + zChild.zIndex
        );
    }
}