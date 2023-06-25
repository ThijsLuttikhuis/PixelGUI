cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PixelGUI)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wnone")
set(CMAKE_CXX_FLAGS "-lstdc++fs")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

include_directories(src)

add_subdirectory(include)
include_directories(include
        include/glfw-3.3.7/include/
        include/glm-0.9.7.1/
        )

add_library(glad src/glad.c)

add_library(utils
        src/utilities/pgu.cpp
        src/utilities/pgu.h
        src/utilities/messageException.cpp
        src/utilities/messageException.h
        src/utilities/DebugPrinter.h
        src/utilities/StringWriter.cpp
        src/utilities/StringWriter.h)

set(LIBS
        ${LIBS}
        glad
        glfw
        utils
        ${OPENGL_LIBRARY}
        ${GLFW_LIBRARIES}
        )

set(INCLUDE_UI
        src/ui/uielement/Button.h
        src/ui/uielement/Button.cpp
        src/ui/uielement/UIElement.h
        src/ui/uielement/UIElement.cpp
        src/ui/uielement/Scene.cpp
        src/ui/uielement/Scene.h
        src/ui/uielement/Callbackable.cpp
        src/ui/uielement/Callbackable.h
        src/ui/uielement/Draggable.cpp
        src/ui/uielement/Draggable.h
        src/ui/uielement/DraggableButton.cpp
        src/ui/uielement/DraggableButton.h
        src/ui/uielement/UIGrid.cpp
        src/ui/uielement/UIGrid.h
        src/ui/uielement/Slider.cpp
        src/ui/uielement/Slider.h
        src/ui/uielement/RootScene.cpp
        src/ui/uielement/RootScene.h
        src/ui/uielement/TextInput.cpp
        src/ui/uielement/TextInput.h
        src/ui/uielement/ButtonOnPress.cpp
        src/ui/uielement/ButtonOnPress.h
        src/ui/uielement/ButtonOnRelease.cpp
        src/ui/uielement/ButtonOnRelease.h
        src/ui/uielement/EditableValue.cpp
        src/ui/uielement/EditableValue.h

        src/ui/sprite/Sprite.h
        src/ui/sprite/Sprite.cpp
        src/ui/sprite/MultiSprite.cpp
        src/ui/sprite/MultiSprite.h
        src/ui/sprite/SpriteComposite.cpp
        src/ui/sprite/SpriteComposite.h
        )

set(INCLUDE_UI_EDITOR
        src/uieditor/UIEditor.cpp
        src/uieditor/UIEditor.h
        src/uieditor/DraggableButtonResizable.cpp
        src/uieditor/DraggableButtonResizable.h
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
        )

target_link_libraries(PixelGUI ${LIBS})

target_link_libraries(PixelGUI stdc++fs)

add_library(PIXELGUI_lib STATIC ${INCLUDE_SOURCE_FILES})

target_link_libraries(PIXELGUI_lib ${LIBS})

add_subdirectory(test)

