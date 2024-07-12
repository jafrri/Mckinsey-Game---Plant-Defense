#include "score.hpp"
#include <iostream>

Score::Score(SDL_Renderer* renderer)
: m_pRenderer(renderer)
{
    font = TTF_OpenFont("Assets/Roboto-Black.ttf", 24);
}

void Score::draw(SDL_Rect* movRect, int number){
    std::string turn_text = "Turns: " + std::to_string(number);
    const char* score_text = turn_text.c_str();
    SDL_Color color = {220, 220, 220};
    SDL_Surface* pTempSurface = TTF_RenderUTF8_Solid(font, score_text, color); // Make text into a surface.

    if(!pTempSurface)
        std::cout << "Surface not created!\n";

    m_pTextTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface); // Turn the surface into a texture.
    // fontRect = {(COLUMNS/2 + 3) * tileWidth, 0, tileWidth * 3, tileHeight};
    
    SDL_RenderCopy(m_pRenderer, m_pTextTexture, NULL, movRect);

    SDL_FreeSurface(pTempSurface);
    SDL_DestroyTexture(m_pTextTexture);
}

void Score::draw(SDL_Rect* movRect, int number, int dummy){
    std::string turn_text = std::to_string(number);
    const char* score_text = turn_text.c_str();
    SDL_Color color = {0, 0, 0};
    SDL_Surface* pTempSurface = TTF_RenderUTF8_Solid(font, score_text, color); // Make text into a surface.

    if(!pTempSurface)
        std::cout << "Surface not created!\n";

    m_pTextTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface); // Turn the surface into a texture.
    // fontRect = {(COLUMNS/2 + 3) * tileWidth, 0, tileWidth * 3, tileHeight};
    
    SDL_RenderCopy(m_pRenderer, m_pTextTexture, NULL, movRect);

    SDL_FreeSurface(pTempSurface);
    SDL_DestroyTexture(m_pTextTexture);
}

Score::~Score()
{
    TTF_CloseFont(font);
}