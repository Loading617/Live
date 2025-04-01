#include "player.hpp"
#include <iostream>

AudioPlayer::AudioPlayer() : loaded(false) {
    ma_engine_init(NULL, &engine);
}

AudioPlayer::~AudioPlayer() {
    if (loaded) {
        ma_sound_uninit(&sound);
    }
    ma_engine_uninit(&engine);
}

bool AudioPlayer::load(const std::string& filename) {
    if (loaded) {
        ma_sound_uninit(&sound);
    }
    
    if (ma_sound_init_from_file(&engine, filename.c_str(), 0, NULL, NULL, &sound) != MA_SUCCESS) {
        std::cerr << "Failed to load file: " << filename << std::endl;
        return false;
    }
    
    loaded = true;
    return true;
}

void AudioPlayer::play() {
    if (loaded) ma_sound_start(&sound);
}

void AudioPlayer::pause() {
    if (loaded) ma_sound_stop(&sound);
}

void AudioPlayer::stop() {
    if (loaded) ma_sound_stop(&sound);
}

void AudioPlayer::setVolume(float volume) {
    if (loaded) ma_sound_set_volume(&sound, volume);
}
