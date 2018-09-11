//
//  Display.hpp
//  ttvm
//
//  Created by Mario Döring on 10.09.18.
//

#ifndef Display_hpp
#define Display_hpp

#include <SDL.h>

#define DISPLAY_WIDHT 800
#define DISPLAY_HEIGHT 600
#define DISPLAY_PIXEL_WIDTH 80
#define DISPLAY_PIXEL_HEIGHT 60

class Display
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *buffer;
    
    void* buffer_data = NULL;
    int buffer_pitch = 0;
    
public:
    Uint32 *pixel_buffer = new Uint32[DISPLAY_PIXEL_HEIGHT * DISPLAY_PIXEL_WIDTH];
    
    Display();
    ~Display();
    
    void start();
};

#endif /* Display_hpp */
