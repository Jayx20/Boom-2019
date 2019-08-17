#include <iostream>
#include <vector>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "object.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
extern const int NUM_SPRITES = 2;

//Function for initializing the Window
bool init(SDL_Window *&window, SDL_Surface *&surface);

//REMOVED Function for loading a bitmap and assigning it to a surface
//bool LoadMedia(SDL_Surface *&surface, const char* path);

//New function to load a surface to use as a sprite
SDL_Surface* LoadSurface(const char*  path, SDL_Surface *&surface);


//Function to make an SDL_Rect
SDL_Rect MakeRect(float x, float y, float w, float h);

std::shared_ptr<Object> NewObjectPtr(int id, int x, int y);
//These are only function prototypes, scroll down to the buttom for the actual functions that is just a C++ thing to make it easier to read

enum class SpriteEnum {null=0, dirt};



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

    //Loading all the images into our spriteArray
    SDL_Surface* nullSprite = NULL;
    SDL_Surface* dirtSprite = NULL;
    dirtSprite = LoadSurface("assets/dirt.png",gameSurface);
    //LoadMedia(dirtSprite, "assets/dirt.bmp");

    //SDL_Surface* testSurface = NULL;
    //testSurface = SDL_LoadBMP("assets/dirt.bmp");

    //
    SDL_Surface* spriteArray[NUM_SPRITES] = {nullSprite, dirtSprite};
    // 0 = Null, 1 = Dirt

    std::vector<std::shared_ptr<Object>> objectsVector;
    objectsVector.push_back(NewObjectPtr(1,32,32));
    objectsVector.push_back(NewObjectPtr(1,64,32));
    objectsVector.push_back(NewObjectPtr(1,64,64));
    
    //SDL_Surface* testSurface = IMG_Load("assets/dirt.png");
    //SDL_Surface* finalTestSurface = SDL_ConvertSurface(testSurface, gameSurface->format, 0);

    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {
            //User wants to quit the program
            if (e.type == SDL_QUIT ) {
                quit=true;
            }
        }

        //SDL_FillRect can be used to set a background color
        SDL_FillRect(gameSurface, NULL, SDL_MapRGB(gameSurface->format, 0xFF, 0xFF, 0xFF) ); //white background
        
        //Puts the image of dirt on the screen
        //SDL_BlitSurface(image, NULL, gameSurface, NULL );

        //
        for(std::shared_ptr<Object> object : objectsVector) {
            SDL_Rect objRect = MakeRect(object->x,object->y,32,32);

            SDL_BlitSurface(spriteArray[object->spriteId], NULL, gameSurface, &objRect);
            

            //SDL_BlitSurface(spriteArray[object.spriteId], NULL, gameSurface, NULL);
        }
        //SDL_BlitSurface(finalTestSurface,NULL,gameSurface,NULL);

        //Updates the screen
        SDL_UpdateWindowSurface(gameWindow);
        
        //Delay so I dont render like 1000000 frames per second and destroy my CPU setting a framerate will be done soon
        SDL_Delay(10);
        
    }

    //Freeing memory of everything and quitting the game
    for (SDL_Surface* spriteSurface : spriteArray) {
        SDL_FreeSurface(spriteSurface);
    }
    
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
        
        if (window == NULL) {
            printf("Window creation failed! SDL_Error:%s\n", SDL_GetError() ); success = false;
        }
        else {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init(imgFlags) & imgFlags )) {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ); success = false;
            }
            else {
                surface = SDL_GetWindowSurface(window);
            }
        }
    }
    return success;
}

/*bool LoadMedia(SDL_Surface *&surface, const char* path) {
    bool success = true;

    surface = SDL_LoadBMP(path);

    if(surface == NULL) {success = false; printf("Failed to Load Image. SDL_Error: %s\n", SDL_GetError());}

    return success;
}*/

SDL_Surface* LoadSurface(const char* path, SDL_Surface *&surface) {
    SDL_Surface* finalSurface = NULL;

    //Load image
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface = NULL) {
        printf("Failed to load surface at %s. Error: %s",path,IMG_GetError());
    }
    else {
        finalSurface = SDL_ConvertSurface(loadedSurface, surface->format, 0);
        if (finalSurface = NULL) {
            printf("Failed to optimize surface from %s. Error: %s",path,IMG_GetError());
        }

        SDL_FreeSurface(loadedSurface);
    }
    return finalSurface;
}

SDL_Rect MakeRect(float x, float y, float w, float h) {
    SDL_Rect madeRect; //stupid name for the new rect we are making
    madeRect.x = x;
    madeRect.y = y;
    madeRect.w = w;
    madeRect.h = h;
    return madeRect;
}

std::shared_ptr<Object> NewObjectPtr(int id, int x, int y) {
    Object* ptr = new Object(id, x, y);
    std::shared_ptr<Object> sharedPtr(ptr);
    return sharedPtr;
}