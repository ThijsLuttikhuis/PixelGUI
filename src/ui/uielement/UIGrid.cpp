//
// Created by Thijs on 15/04/2023.
//

#include "UIGrid.h"
#include "utilities/DebugPrinter.h"

namespace PG {

void UIGrid::addUIElement(const std::shared_ptr<UIElement> &uiElement) {
    (void) uiElement;

//    (void) uiElement;
//    DebugPrinter::print(DebugPrinter::ESSENTIAL_ONLY,
//                        "UIGrid::addUIElement: please use setUIElement instead");
}

void UIGrid::setUIElement(const std::shared_ptr<UIElement> &uiElement, int x, int y) {
    (void) uiElement;
    (void) x;
    (void) y;

//    if (x < 0 || x >= nHorizontal || y < 0 || y >= nVertical) {
//        DebugPrinter::print(DebugPrinter::ESSENTIAL_ONLY,
//                            "UIGrid::setUIElement: trying to set element outside of the Grid");
//    }
//    int childIndex = getChildIndex(uiElement);
//    if (childIndex >= 0) {
//        removeUIElement(childIndex);
//    }
//
//    children[x + y * nHorizontal] = uiElement;
}

}
