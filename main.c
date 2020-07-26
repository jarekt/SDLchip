#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "chip.h"
#ifdef __EMSCRIPTEN__
#include "SDL.h"
#include <emscripten.h>
EM_JS(int, getWinHeight, (), {
    return window.innerHeight
});
EM_JS(int, getWinWidth, (), {
    return window.innerWidth
});
#else
#include "SDL/include/SDL.h"
#endif

#ifdef EMBED_TETRIS
#include "tetris.h"//include if you want a standalone chip8 tetris executable,
extern const size_t import_string_size;
extern const char import_string[import_string_size];
#endif

#define COLOR_BLACK 0,0,0,0
#define COLOR_WHITE 255,255,255,0

SDL_Window *win;
SDL_Renderer *ren;
SDL_Event eve;

int clock_speed = 500;
char paused = 0;
char key[16] = {0};//an array for keystate keeping
const char *filename;

#ifdef EMBED_TETRIS
void loadString()//use for intro logo - after loading integrated or for nocart
{
    for (int i = 0; i < import_string_size; i++)
    {

        memory[i+512] = import_string[i];
    }
    
}
#endif

void loadFile(const char *filename)
{
    FILE * fp;
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        perror("err: rom file not found");
        exit(0);
    }
    //open the file
    for (int i = 512; i < 4096; i++)
    {
        memory[i] = fgetc(fp);
    }
    //copy it to memory
    fclose(fp);
}

void quit()
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(0);
}


char getEvents(char b_wait)
{
    if(SDL_PollEvent(&eve) || (b_wait && SDL_WaitEvent(&eve)))
    {
        if(eve.type == SDL_QUIT) {quit();}
        else if(eve.type == SDL_KEYDOWN)
        {
            paused = 0;
            switch (eve.key.keysym.sym)
            {
            case SDLK_x:
                key[0] = 1;
                return 0;
            case SDLK_1:
                key[1] = 1;
                return 1;
            case SDLK_2:
                key[2] = 1;
                return 2;
            case SDLK_3:
                key[3] = 1;
                return 3;
            case SDLK_q:
                key[4] = 1;
                return 4;
            case SDLK_w:
                key[5] = 1;
                return 5;
            case SDLK_e:
                key[6] = 1;
                return 6;
            case SDLK_a:
                key[7] = 1;
                return 7;
            case SDLK_s:
                key[8] = 1;
                return 8;
            case SDLK_d:
                key[9] = 1;
                return 9;
            case SDLK_y:
            case SDLK_z:
                key[10] = 1;
                return 10;
            case SDLK_c:
                key[11] = 1;
                return 11;
            case SDLK_4:
                key[12] = 1;
                return 12;
            case SDLK_r:
                key[13] = 1;
                return 13;
            case SDLK_f:
                key[14] = 1;
                return 14;
            case SDLK_v:
                key[15] = 1;
                return 15;
            case SDLK_ESCAPE:
                quit();
                break;
            case SDLK_p:
                paused = 1;
                break;
            case SDLK_o:
                init();
                #ifdef EMBED_TETRIS
                loadString();
                #else
                loadFile(filename);
                #endif
                break;
            default:
                break;
            }
        }
        else if(eve.type == SDL_KEYUP)
        {
            switch (eve.key.keysym.sym)
            {
            case SDLK_x:
                key[0] = 0;
                break;
            case SDLK_1:
                key[1] = 0;
                break;
            case SDLK_2:
                key[2] = 0;
                break;
            case SDLK_3:
                key[3] = 0;
                break;
            case SDLK_q:
                key[4] = 0;
                break;
            case SDLK_w:
                key[5] = 0;
                break;
            case SDLK_e:
                key[6] = 0;
                break;
            case SDLK_a:
                key[7] = 0;
                break;
            case SDLK_s:
                key[8] = 0;
                break;
            case SDLK_d:
                key[9] = 0;
                break;
            case SDLK_y:
            case SDLK_z:
                key[10] = 0;
                break;
            case SDLK_c:
                key[11] = 0;
                break;
            case SDLK_4:
                key[12] = 0;
                break;
            case SDLK_r:
                key[13] = 0;
                break;
            case SDLK_f:
                key[14] = 0;
                break;
            case SDLK_v:
                key[15] = 0;
                break;
            default:
                break;
            }
        }
    }
    return 16;
}
//keypresses for chip, quit, pause

void displayScreen()
{
    SDL_SetRenderDrawColor(ren, COLOR_BLACK);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, COLOR_WHITE);
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if(readBit(i*64+j))
            {
                SDL_RenderDrawPoint(ren, j, i);
            }
        }
    }
    SDL_RenderPresent(ren);
}
//load from gfx_buf and update - maybe not necessary setting color to black

void initMain()
{
    init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640*2, 320*2, SDL_WINDOW_RESIZABLE, &win, &ren);
    SDL_RenderSetLogicalSize(ren, 64, 32);
    SDL_SetRenderDrawColor(ren, COLOR_BLACK);
    SDL_RenderClear(ren);
}
//inits SDL and the emu

void mainloop()
{
    #ifdef __EMSCRIPTEN__//fix
    if(!paused)
    {
        if(timerS > 0){timerS--;}
        if(timerD > 0){timerD--;}
        for (size_t i = 0; i < 500/60; i++)
        {
            fetch();
            execute();
        }
        SDL_SetWindowSize(win, getWinWidth(), getWinHeight());
        displayScreen();
    }
    getEvents(0);
    #else
    clock_t cycle_timer, sd_timer;
    cycle_timer = clock();
    sd_timer = clock();

    while(1)
    {
        if(!paused)
        {
            if (clock() - cycle_timer >= CLOCKS_PER_SEC/60)//update timers
            {
                if(timerS > 0){timerS--;}
                if(timerD > 0){timerD--;}
                cycle_timer = clock();
                for (size_t i = 0; i < 500/60; i++)
                {
                    if(!fetch()){break;}
                    execute();
                }
                displayScreen();
            }
        }
        getEvents(0);
    }
    #endif
}

int main(int argc, char const *argv[])
{
    #ifndef EMBED_TETRIS
    if(argc < 2 || argc > 3)
    {
        puts("Usage:");
        puts("expecting args - a filename to open and an emulator speed in Hz (optional)");
        puts("hex keypad mapping: ");
        puts("1|2|3|C    1|2|3|4");
        puts("4|5|6|D => Q|W|E|R");
        puts("7|8|9|E    A|S|D|F");
        puts("A|0|B|F    Y|X|C|V");
        puts("misc keys:");
        puts("ESC - quit");
        puts("P - pause");
        puts("O - restart");
        exit(0);
    }
    if(argc == 3){sscanf(argv[2], "%d", &clock_speed);}
    initMain();
    filename = argv[1];
    loadFile(filename);
    #else
    initMain();
    loadString();
    #endif
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 60, 1);
    #else
    mainloop();
    #endif
    quit();
    return 0;
}
