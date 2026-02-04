#include "FXVStack.h"
#include "FXElementLayoutTree.h"

void FluentX::UI::FXVStack::layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const
{
    int childCount = children.size();
    if (childCount == 0) return;

    int totalDesiredHeight = 0;
    int flexibleChildCount = 0;

    // First pass: Calculate the total height the children *want* to take.
    for (const auto& child : children) {
        if (child->type == UI::FX_TYPE_SPACER) {
            UI::FXSpacer* spacer = static_cast<UI::FXSpacer*>(child.get());
            totalDesiredHeight += (spacer->height > 0) ? spacer->height : 0;
        }
        else if (child->maxSize.height() != FX_USE_DEFAULT) {
            // This child wants to be its max height.
            totalDesiredHeight += child->maxSize.height();
        }
        else {
            // This is a flexible child. Its "desired" height for this calculation is its min height.
            totalDesiredHeight += child->minSize.height();
            flexibleChildCount++;
        }
    }

    int totalSpacing = spacing * (childCount - 1);
    totalDesiredHeight += totalSpacing;

    // Check if the desired height exceeds the available height.
    if (totalDesiredHeight > availH) {
        // We are in an overflow state. We must scale down to fit.
        // The scale factor is based on the available space vs. the desired space.
        float scale = (float)(availH - totalSpacing) / (float)(totalDesiredHeight - totalSpacing);

        int cursorY = y;
        for (const auto& child : children) {
            int desiredChildHeight = 0;
            if (child->type == UI::FX_TYPE_SPACER) {
                UI::FXSpacer* spacer = static_cast<UI::FXSpacer*>(child.get());
                desiredChildHeight = (spacer->height > 0) ? spacer->height : 0;
            }
            else if (child->maxSize.height() != FX_USE_DEFAULT) {
                desiredChildHeight = child->maxSize.height();
            }
            else {
                desiredChildHeight = child->minSize.height();
            }

            // Scale the desired height to get the final layout height.
            // We do NOT clamp to minSize here, as that would re-introduce the overflow.
            int childHeight = (int)(desiredChildHeight * scale);
            if (childHeight < 1) childHeight = 1; // Prevent zero or negative size

            FXRECURSIVELayoutWidgets(
                *child,
                x,
                cursorY,
                availW,
                childHeight,
                tree,
                baseZ
            );

            cursorY += childHeight + spacing;
        }
        return; // Layout is complete for the overflow case.
    }

    // Normal layout when there is enough space.
    int remainingHeight = availH - totalDesiredHeight;
    if (remainingHeight < 0) remainingHeight = 0; // Should not happen, but as a safeguard

    int eachFlexibleHeight = (flexibleChildCount > 0) ? (remainingHeight / flexibleChildCount) : 0;

    int cursorY = y;
    for (const auto& child : children) {
        int childHeight = 0;
        if (child->type == UI::FX_TYPE_SPACER) {
            UI::FXSpacer* spacer = static_cast<UI::FXSpacer*>(child.get());
            childHeight = (spacer->height > 0) ? spacer->height : remainingHeight;
        }
        else if (child->maxSize.height() != FX_USE_DEFAULT) {
            childHeight = child->maxSize.height();
        }
        else {
            // Flexible child: give it its min height plus a share of the remaining space.
            childHeight = child->minSize.height() + eachFlexibleHeight;
        }

        FXRECURSIVELayoutWidgets(
            *child,
            x,
            cursorY,
            availW,
            childHeight,
            tree,
            baseZ
        );

        cursorY += childHeight + spacing;
    }
}