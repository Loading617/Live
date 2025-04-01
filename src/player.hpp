#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "miniaudio.h"

class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();
    
    bool load(const std::string& filename);
    void play();
    void pause();
    void stop();
    void setVolume(float volume);
    
private:
    ma_engine engine;
    ma_sound sound;
    bool loaded;
};

#endif
