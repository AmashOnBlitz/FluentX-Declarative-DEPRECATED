#ifndef FX_ELEMENT_LAYOUT_TREE_HEADER
#define FX_ELEMENT_LAYOUT_TREE_HEADER

#include "FXNamespaces.h"
#include <vector>
#include "FXWidget.h"
#include <string>
#include "FXElementLayoutTreeStruct.h"
#include "FXSpacer.h"
#include "FXZStack.h"

#undef min
#undef max

using namespace FluentX;

namespace FluentX::layout {

    inline void FXRECURSIVELayoutWidgets(
        UI::FXWidgetBase& widget,
        int x, int y,
        int availW, int availH,
        FXElementLayoutTree& tree,
        int baseZ
    ) {
        FXElementPlacementProperties placement;
        placement.x = x;
        placement.y = y;
        placement.z = baseZ;
        if (widget.type == UI::FX_TYPE_SPACER) {
            UI::FXSpacer* spacer = static_cast<UI::FXSpacer*>(&widget);
            placement.width = (spacer->width > 0) ? spacer->width : availW;
            placement.height = (spacer->height > 0) ? spacer->height : availH;
        }
        else{

            if (widget.type == UI::FX_TYPE_ZSTACK) {
                UI::FXZStack* zStack = static_cast<UI::FXZStack*>(&widget);
                zStack->sortChildrenByZIndex();
            }

            int w = availW;
            int h = availH;

            if (w >= widget.minSize.width()) {
                w = std::max(w, widget.minSize.width());
            }

            if (h >= widget.minSize.height()) {
                h = std::max(h, widget.minSize.height());
            }

            if (widget.maxSize.width() != FX_USE_DEFAULT)
                w = std::min(w, widget.maxSize.width());

            if (widget.maxSize.height() != FX_USE_DEFAULT)
                h = std::min(h, widget.maxSize.height());

            placement.width = w;
            placement.height = h;
        }

        tree.elements.push_back({ placement, &widget });
        if (widget.isContainer()) {
            widget.layoutChildren(x, y, placement.width, placement.height, tree, baseZ);
        }
    }


    inline FXElementLayoutTree FXMakeElementLayoutTree(UI::FXWidgetBase& rootChild, const UI::FXSize& WindowSize) {
        FXElementLayoutTree tree;
        FXRECURSIVELayoutWidgets(
            rootChild,
            0,
            0,
            (WindowSize.width()),
            (WindowSize.height()),
            tree,
            0
        );
        return tree;
    }

}

#endif // !FX_ELEMENT_LAYOUT_TREE_HEADER