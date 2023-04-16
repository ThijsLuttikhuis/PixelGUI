//
// Created by thijs on 11-12-22.
//

#include "src/uieditor/UIEditor.h"

int main() {

    auto UIEditor = std::make_shared<PG::UIEditor>();
    UIEditor->initialize();
    UIEditor->run();

    return 0;
}
