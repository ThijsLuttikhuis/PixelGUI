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

set(INCLUDE_UI
        src/ui/UIElement.h
        src/ui/UIElement.cpp
        )

set(INCLUDE_GAME_OBJECT
        src/game/GameObject.h
        src/game/GameObject.cpp
        src/game/Game.h
        src/game/Game.cpp
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
        )

set(INCLUDE_SOURCE_FILES
        src/glad.c
        src/stb_image.h
        ${INCLUDE_GAME_OBJECT}
        ${INCLUDE_WINDOW}
        ${INCLUDE_UI}
        )

add_executable(PixelGUI
        main.cpp
        ${INCLUDE_SOURCE_FILES}
        src/window_callback.cpp)

target_link_libraries(PixelGUI ${LIBS})

target_link_libraries(PixelGUI stdc++fs)

add_library(PIXELGUI_lib STATIC ${INCLUDE_SOURCE_FILES})

target_link_libraries(PIXELGUI_lib ${LIBS})

add_subdirectory(test)

