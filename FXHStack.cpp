#include "FXHStack.h"
#include "FXElementLayoutTree.h"

void FluentX::UI::FXHStack::layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const
{
    int childCount = children.size();
    if (childCount == 0) return;

    int totalDesiredWidth = 0;
    int flexibleChildCount = 0;

    for (const auto& child : children) {
        if (child->type == UI::FX_TYPE_SPACER) {
            UI::FXSpacer* spacer = static_cast<UI::FXSpacer*>(child.get());
            totalDesiredWidth += (spacer->width > 0) ? spacer->width : 0;
        }
        else if (child->maxSize.width() != FX_USE_DEFAULT) {
            totalDesiredWidth += child->maxSize.width();
        }
        else {
            totalDesiredWidth += child->minSize.width();
            flexibleChildCount++;
        }
    }

    int totalSpacing = spacing * (childCount - 1);
    totalDesiredWidth += totalSpacing;

    // Check if the desired width exceeds the available width.
    if (totalDesiredWidth > availW) {
        // We are in an overflow state. We must scale down to fit.
        float scale = (float)(availW - totalSpacing) / (float)(totalDesiredWidth - totalSpacing);

        int cursorX = x;
        for (const auto& child : children) {
            int desiredChildWidth = 0;
            if (child->type == UI::FX_TYPE_SPACER) {
                UI::FXSpacer* spacer = static_cast<UI::FXSpacer*>(child.get());
                desiredChildWidth = (spacer->width > 0) ? spacer->width : 0;
            }
            else if (child->maxSize.width() != FX_USE_DEFAULT) {
                desiredChildWidth = child->maxSize.width();
            }
            else {
                desiredChildWidth = child->minSize.width();
            }

            // Scale the desired width to get the final layout width.
            int childWidth = (int)(desiredChildWidth * scale);
            if (childWidth < 1) childWidth = 1; // Prevent zero or negative size

            FXRECURSIVELayoutWidgets(
                *child,
                cursorX,
                y,
                childWidth,
                availH,
                tree,
                baseZ
            );

            cursorX += childWidth + spacing;
        }
        return; // Layout is complete for the overflow case.
    }

    // Normal layout when there is enough space.
    int remainingWidth = availW - totalDesiredWidth;
    if (remainingWidth < 0) remainingWidth = 0; // Safeguard

    int eachFlexibleWidth = (flexibleChildCount > 0) ? (remainingWidth / flexibleChildCount) : 0;

    int cursorX = x;
    for (const auto& child : children) {
        int childWidth = 0;
        if (child->type == UI::FX_TYPE_SPACER) {
            UI::FXSpacer* spacer = static_cast<UI::FXSpacer*>(child.get());
            childWidth = (spacer->width > 0) ? spacer->width : remainingWidth;
        }
        else if (child->maxSize.width() != FX_USE_DEFAULT) {
            childWidth = child->maxSize.width();
        }
        else {
            // Flexible child: give it its min width plus a share of the remaining space.
            childWidth = child->minSize.width() + eachFlexibleWidth;
        }

        FXRECURSIVELayoutWidgets(
            *child,
            cursorX,
            y,
            childWidth,
            availH,
            tree,
            baseZ
        );

        cursorX += childWidth + spacing;
    }
}