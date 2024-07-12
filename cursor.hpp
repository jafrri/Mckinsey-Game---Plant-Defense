#include "gameObject.hpp"

class Cursor : public GameObject
{
    public:
        Cursor(SDL_Renderer* renderer, SDL_Texture* texture);
        void draw();
        void update(SDL_Event& event);
};