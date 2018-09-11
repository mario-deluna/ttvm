//
//  Display.hpp
//  ttvm
//
//  Created by Mario Döring on 10.09.18.
//

#ifndef Display_hpp
#define Display_hpp

#include <SDL.h>
#include <mutex>

#define DISPLAY_WIDHT 800
#define DISPLAY_HEIGHT 600
#define DISPLAY_PIXEL_WIDTH 80
#define DISPLAY_PIXEL_HEIGHT 60

class Display
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *buffer;
    
public:
    Uint32 *pixel_buffer = new Uint32[DISPLAY_PIXEL_HEIGHT * DISPLAY_PIXEL_WIDTH];
    
    Display();
    ~Display();
    
    void start(std::mutex *dispm);
};

#endif /* Display_hpp */
