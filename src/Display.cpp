//
//  Display.cpp
//  ttvm
//
//  Created by Mario Döring on 10.09.18.
//

#include "Display.hpp"



Display::Display()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("TTVM", NULL, NULL, DISPLAY_WIDHT, DISPLAY_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_SetWindowInputFocus(window);
    SDL_RaiseWindow(window);
    
    buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_STATIC, DISPLAY_PIXEL_WIDTH, DISPLAY_PIXEL_HEIGHT);
}

Display::~Display()
{
    SDL_DestroyTexture(buffer);
    buffer_data = NULL;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::start()
{
    SDL_Event event;
    
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
   
    SDL_LockTexture(buffer, NULL, &buffer_data, &buffer_pitch);
    
    Uint32 format = SDL_GetWindowPixelFormat(window);
    SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);
    
    //Uint32* pixels = (Uint32*)buffer_data;
    //int pixelCount = (buffer_pitch / 4) * DISPLAY_PIXEL_HEIGHT;
    
    int i = 0;
//
//    pixels[0] = SDL_MapRGB(mappingFormat, 0xff, 0xFF, 0xFF);
//    pixels[2] = SDL_MapRGB(mappingFormat, 0xff, 0xFF, 0xFF);
//    pixels[344] = SDL_MapRGB(mappingFormat, 0xff, 0xFF, 0xFF);
//    pixels[3453] = SDL_MapRGB(mappingFormat, 0xff, 0xFF, 0xFF);
    
    SDL_UnlockTexture(buffer);
    //SDL_FreeFormat(mappingFormat);
    
    while (1)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                return;
            }
        }
        
        SDL_LockTexture(buffer, NULL, &buffer_data, &buffer_pitch);
        Uint32 *pixels = (Uint32*)buffer_data;
        
        pixel_buffer[i] = SDL_MapRGB(mappingFormat, 0xff, 0xFF, 0xFF);
        
        // apply the pixel buffer
        pixels = pixel_buffer;
        
        SDL_UnlockTexture(buffer);
        
        SDL_RenderCopy(renderer, buffer, NULL, NULL);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1000 / 60);
        i++;
    }
}
