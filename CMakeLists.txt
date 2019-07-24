cmake_minimum_required(VERSION 3.14.5)

project(SDL_demo LANGUAGES C VERSION 9.0)


add_executable(SDLchip main.c chip.c)

add_subdirectory(SDL)


target_link_libraries(SDLchip SDL2main SDL2-static)