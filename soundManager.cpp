#include "soundManager.hpp"
#include <iostream>

SoundManager::SoundManager()
{
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);

    // Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
}

bool SoundManager::load(std::string fileName, std::string id, int type)
{
    if(type == SOUND_MUSIC)
    {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if(pMusic == 0)
        {
            std::cout << "Could not load music: ERROR - "
            << Mix_GetError() << std::endl;
            return false;
        }
        m_music[id] = pMusic;
        return true;
    }
    else if(type == SOUND_SFX)
    {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if(pChunk == 0)
        {
            std::cout << "Could not load SFX: ERROR - "
            << Mix_GetError() << std::endl;
            return false;
        }
        m_sfxs[id] = pChunk;
        return true;
    }
    return false;
}

void SoundManager::playMusic(std::string id, int loop)
{
    Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(std::string id, int loop)
{
    Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void SoundManager::deleteSound(std::string id, int type)
{
    if(type == SOUND_MUSIC)
        Mix_FreeMusic(m_music[id]);
    else if (type == SOUND_SFX)
        Mix_FreeChunk(m_sfxs[id]);
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}