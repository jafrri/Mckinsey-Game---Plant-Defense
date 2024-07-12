#pragma once
#include "Protector.hpp"
#include "score.hpp"
#include<iostream>

class Eagle: public Protector{
    int damage=40;
    SDL_Rect shadeRect;
    Score* display;//pointer to the score class object and its function is to display the quantity of the protector above the protector on panel.

    public:
        static int count;// The static variable is used to count the  number of eagle objects constructed.
        static void set_count(int num);// The static function is used to set the value of count of what is passed it in argument.
        static int maxEagles;// The number of max eagles is set from here as a static integer.
        Eagle(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect movRect);
        void draw();
        void draw(Grid* &grid);
        void attack(Grid* &grid);
        void highlight(Grid* &grid);
        ~Eagle();
};