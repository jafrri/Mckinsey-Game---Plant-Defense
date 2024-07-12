#pragma once
#include <string>
#include <map>
#include <SDL_mixer.h>
#include "definitions.hpp"

class SoundManager
{
    std::map<std::string, Mix_Chunk*> m_sfxs;
    std::map<std::string, Mix_Music*> m_music;

    public:
        SoundManager();
        ~SoundManager();
    
        bool load(std::string fileName, std::string id, int type);
        void deleteSound(std::string id, int type);
        void playSound(std::string id, int loop);
        void playMusic(std::string id, int loop);
};