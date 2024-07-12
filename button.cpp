#include "button.hpp"

Button::Button(SDL_Renderer* renderer, SDL_Texture* texture, int* pMouseX, int* pMouseY, int s1x, int s1y, int s2x, int s2y, int posx, int posy, int width, int height)
       : pRenderer(renderer), pButtonTexture(texture), pMouseX(pMouseX), pMouseY(pMouseY)
{
    //srcrect and moverrect for the button
    srcRect1 = {s1x, s1y, width, height};
    srcRect2 = {s2x, s2y, width, height};
    movRect = {posx, posy, width, height};
}

void Button::check()//this checks whetehr the cursor is hovering on the button or not.
{
    if(*pMouseX >= movRect.x && *pMouseX <= (movRect.x + movRect.w) && *pMouseY >= movRect.y && *pMouseY <= (movRect.y + movRect.h))
        pointed = true;
    else 
        pointed = false;
}

void Button::draw()//draws button using two different srcrect depending upon the value of the bool pointed.
{
    check();
    if (pointed)
        SDL_RenderCopy(pRenderer, pButtonTexture, &srcRect2, &movRect);
    else
        SDL_RenderCopy(pRenderer, pButtonTexture, &srcRect1, &movRect);
}

bool Button::hover()
{
    return pointed;
}