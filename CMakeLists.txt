cmake_minimum_required(VERSION 3.14.5)
project(SDL_demo LANGUAGES C VERSION 1.1)

set(SDLCHIP_SOURCES main.c chip.c chip.h)

if(EMSCRIPTEN)
    add_compile_options("SHELL:-s WASM=1")
    add_compile_options("SHELL:-s USE_SDL=2")
    include_directories("${EMSCRIPTEN_ROOT_PATH}/cache/wasm/include/SDL2")
    if(EXISTS "${EMSCRIPTEN_ROOT_PATH}/cache/wasm/ports-builds/sdl2/libSDL2.a")
        set(SDL2_LIBRARIES "${EMSCRIPTEN_ROOT_PATH}/cache/wasm/ports-builds/sdl2/libSDL2.a")#myb not necessary but it didnt work for me without it
    else()
        message(FATAL_ERROR "SDL2 library not found, run: embuilder build sdl2")
    endif()
else()
    add_subdirectory(SDL)
    set(SDL2_LIBRARIES SDL2main SDL2-static)
endif()

option(EMBED_TETRIS "on to embed the tetris rom" ON)
if(EMBED_TETRIS)
    add_compile_definitions(EMBED_TETRIS)
    list(APPEND SDLCHIP_SOURCES tetris.h)
endif()

add_executable(SDLchip ${SDLCHIP_SOURCES})
target_link_libraries(SDLchip ${SDL2_LIBRARIES})