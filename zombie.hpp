#pragma once
#include "Protector.hpp"
#include "score.hpp"

// The class zombie is defined which is inherited from protector class.
class Zombie: public Protector{
    int damage=30;  // The damage of zombie is set to 30.
    SDL_Rect shadeRect;
    Score* display; // The score ponter is used to show the quantity of zombie above zombie on the panel.

    public:
        static int count; // The static variable is used to count the  number of zobie objects constructed.
        static void set_count(int num); // The static function is used to set the value of count to what is passed it in arguement. 
        static int maxZombies; // The max number of max zombies set as static int.
        Zombie(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect movRect);
        void draw();
        void draw(Grid* &grid);
        void attack(Grid* &grid);
        void highlight(Grid* &grid);
        ~Zombie();
};