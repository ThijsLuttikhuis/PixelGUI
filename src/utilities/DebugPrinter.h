//
// Created by Thijs on 30/03/2023.
//

#ifndef PIXELGUI_DEBUGPRINTER_H
#define PIXELGUI_DEBUGPRINTER_H

#include <initializer_list>
#include <iostream>

namespace PG {

class DebugPrinter {
public:
    enum verboseLevel : int {
        NONE = 0,
        ESSENTIAL_ONLY = 1,
        VERBOSE = 3,
        ALL = 5
    };

    enum verboseSpecifics : unsigned long {
        DEBUG_MOUSE_POSITION_ALWAYS = 1,
        DEBUG_MOUSE_BUTTON_ALWAYS = 2,
        DEBUG_MOUSE_POSITION_UIELEMENT = 4,
        DEBUG_MOUSE_BUTTON_UIELEMENT = 8,
        DEBUG_KEYBOARD_KEYS = 16,
        DEBUG_RENDER_GENERAL = 256,
        DEBUG_RENDER_ERRORS = 512,
    };

private:
    static const verboseLevel verbosity = ALL;

    static const unsigned long verboseSpecifics = DEBUG_MOUSE_POSITION_ALWAYS * true
                                                  + DEBUG_MOUSE_BUTTON_ALWAYS * true
                                                  + DEBUG_MOUSE_POSITION_UIELEMENT * false
                                                  + DEBUG_MOUSE_BUTTON_UIELEMENT * true
                                                  + DEBUG_KEYBOARD_KEYS * true
                                                  + DEBUG_RENDER_GENERAL * true
                                                  + DEBUG_RENDER_ERRORS * true;


public:
    template<typename T>
    static void print(enum verboseLevel verboseLevel, T t) {
        if (verbosity > verboseLevel) {
            std::cout << t << std::endl;
        }
    }

    template<typename T, typename... Args>
    static void print(enum verboseLevel verboseLevel, T t, Args... args) {
        if (verbosity > verboseLevel) {
            std::cout << t;

            print(verboseLevel, args...);
        }
    }

    template<typename T>
    static void print(enum verboseSpecifics verboseSpecific, T t) {
        if (verboseSpecifics & verboseSpecific) {
            std::cout << t << std::endl;
        }
    }

    template<typename T, typename... Args>
    static void print(enum verboseSpecifics verboseSpecific, T t, Args... args) {
        if (verboseSpecifics & verboseSpecific) {
            std::cout << t;

            print(verboseSpecific, args...);
        }
    }
};

}

#endif //PIXELGUI_DEBUGPRINTER_H
