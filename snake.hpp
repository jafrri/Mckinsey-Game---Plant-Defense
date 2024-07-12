#pragma once
#include "Protector.hpp"
#include "score.hpp"

class Snake: public Protector{
    int damage=50; // The damage that the snake infilicts.
    SDL_Rect shadeRect;
    Score* display;//pointer to the score class object and its function is to display the quantity of the protector above the protector on panel.
    
    public:
        int static count;// The static variable is used to count the  number of snake objects constructed. 
        static void set_count(int num);// The static function is used to set the value of count of what is passed it in argument.
        static int maxSnakes;// The number of max Snakes is set from here as a static integer.
        Snake(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect movRect);
        void draw();
        void draw(Grid* &grid);
        void attack(Grid* &grid);
        void highlight(Grid* &grid);
        ~Snake();
};