#include <iostream>
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Function for initializing the Window
bool init(SDL_Window *&window, SDL_Surface *&surface);

//Function for loading a bitmap and assigning it to a surface
bool LoadMedia(SDL_Surface *&surface, const char* path);

//These are only function prototypes, scroll down to the buttom for the actual functions that is just a C++ thing to make it easier to read

int main( int argc, char* args[] ) {

    //Game window
    SDL_Window* gameWindow = NULL;

    //Game surface
    SDL_Surface* gameSurface = NULL;

    //Initialization of SDL, actually making the gameWindow and gameSurface pointers point to stuff
    if(!init(gameWindow, gameSurface)) {printf("Init machine broke\n");}

    //Making a bool called quit that if it gets set to 1 will quit the game
    bool quit = 0;
    //setting up the SDL Event Manager
    SDL_Event e;

    //Placeholder code for loading an image of dirt so we can test that it works
    SDL_Surface* image = NULL;
    LoadMedia(image, "assets/dirt.bmp");

    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {
            //User wants to quit the program
            if (e.type == SDL_QUIT ) {
                quit=true;
            }
        }

        //SDL_FillRect can be used to set a background color
        //SDL_FillRect(gameSurface, NULL, SDL_MapRGB(gameSurface->format, 0x00, 0xFF, 0x00) );
        
        //Puts the image of dirt on the screen
        SDL_BlitSurface(image, NULL, gameSurface, NULL );

        //Updates the screen
        SDL_UpdateWindowSurface(gameWindow);
        
        //Delay so I dont render like 1000000 frames per second and destroy my CPU setting a framerate will be done soon
        SDL_Delay(10);
        
    }

    SDL_FreeSurface(image);
    //Freeing memory of everything and quitting the game
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();

    return 0;
}

bool init(SDL_Window *&window, SDL_Surface *&surface) {
    bool success = true;
    //Initialization of SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed to initialize. SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //actually creating the game window
        window = SDL_CreateWindow("Boom 2019", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (window == NULL) { printf("Window creation failed! SDL_Error:%s\n", SDL_GetError() ); success = false; }
        else {
            surface = SDL_GetWindowSurface(window);
        }

    }
    return success;
}

bool LoadMedia(SDL_Surface *&surface, const char* path) {
    bool success = true;

    surface = SDL_LoadBMP(path);

    if(surface == NULL) {success = false; printf("Failed to Load Image. SDL_Error: %s\n", SDL_GetError());}

    return success;
}