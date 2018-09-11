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
    
    buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, DISPLAY_PIXEL_WIDTH, DISPLAY_PIXEL_HEIGHT);
    
    // inital fill white
    memset(pixel_buffer, 255, DISPLAY_PIXEL_WIDTH * DISPLAY_PIXEL_HEIGHT * sizeof(Uint32));
}

Display::~Display()
{
    SDL_DestroyTexture(buffer);
    delete[] pixel_buffer;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::start(std::mutex *dispm)
{
    SDL_Event event;
    
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    while (1)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                return;
            }
        }
        
//        pixel_buffer[i] = 0xff0000;
//        pixel_buffer[i+1] = 0x00ff00;
//        pixel_buffer[i+2] = 0x0000ff;
        //pixel_buffer[i+3] = 0x000000ff;
        
        dispm->lock();
        SDL_UpdateTexture(buffer, NULL, pixel_buffer, DISPLAY_PIXEL_WIDTH * sizeof(Uint32));
        dispm->unlock();
        
        SDL_RenderCopy(renderer, buffer, NULL, NULL);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1000 / 60);
    }
}
