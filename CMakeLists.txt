cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PixelGUI)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wnone")
set(CMAKE_CXX_FLAGS "-lstdc++fs")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

include_directories(src)

add_subdirectory(include)
include_directories(include
        include/glfw-3.3.7/include/
        include/glm-0.9.7.1/)

add_library(GLAD "src/glad.c")
set(LIBS
        ${LIBS}
        GLAD
        ${OPENGL_LIBRARY}
        glfw
        ${GLFW_LIBRARIES}
        )

set(INCLUDE_UTILITIES
        src/utilities/DebugPrinter.h
        )

set(INCLUDE_UI
        src/ui/uielement/Button.h
        src/ui/uielement/Button.cpp
        src/ui/uielement/UIElement.h
        src/ui/uielement/UIElement.cpp
        src/ui/uielement/Scene.cpp
        src/ui/uielement/Scene.h
        src/ui/uielement/Draggable.cpp
        src/ui/uielement/Draggable.h
        src/ui/uielement/DraggableButton.cpp
        src/ui/uielement/DraggableButton.h

        src/ui/sprite/Sprite.h
        src/ui/sprite/Sprite.cpp
        )

set(INCLUDE_UI_EDITOR
        src/uieditor/UIEditor.cpp src/uieditor/UIEditor.h
        )

set(INCLUDE_WINDOW
        src/window/Window.h
        src/window/Window.cpp
        src/window_callback.cpp

        src/window/render/Shader.h
        src/window/render/Shader.cpp
        src/window/render/Texture2D.h
        src/window/render/Texture2D.cpp
        src/window/render/SpriteRenderer.h
        src/window/render/SpriteRenderer.cpp
        src/window/render/TextRenderer.h
        src/window/render/TextRenderer.cpp
        )

set(INCLUDE_SOURCE_FILES
        src/glad.c
        src/stb_image.h
        src/window_callback.cpp
        ${INCLUDE_UI_EDITOR}
        ${INCLUDE_WINDOW}
        ${INCLUDE_UI}
        )

add_executable(PixelGUI
        main.cpp
        ${INCLUDE_SOURCE_FILES}
        src/ui/sprite/MultiSprite.cpp src/ui/sprite/MultiSprite.h src/ui/sprite/SpriteComposite.cpp src/ui/sprite/SpriteComposite.h src/ui/uielement/UIGrid.cpp src/ui/uielement/UIGrid.h)

target_link_libraries(PixelGUI ${LIBS})

target_link_libraries(PixelGUI stdc++fs)

add_library(PIXELGUI_lib STATIC ${INCLUDE_SOURCE_FILES})

target_link_libraries(PIXELGUI_lib ${LIBS})

if(EXISTS src/test/lib/googletest/CMakelists.txt)
    add_subdirectory(test)
endif()
