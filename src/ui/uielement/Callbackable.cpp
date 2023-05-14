//
// Created by Thijs on 07/05/2023.
//

#include "Callbackable.h"

namespace PG {

void Callbackable::setCallbackFunction(void (* func)(const std::shared_ptr<UIElement> &)) {
    callbackFunc = func;
}

}
