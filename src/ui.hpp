#ifndef UI_HPP
#define UI_HPP

#include <elements.hpp>
#include "player.hpp"
#include "metadata.hpp"
#include <vector>

class LiveApp {
public:
    LiveApp();
    void run();

private:
    cycfi::elements::app _app;
    cycfi::elements::window _window;
    AudioPlayer _player;
    TrackInfo _trackInfo;

    std::vector<RadioStation> _stations;

    cycfi::elements::static_text _title_text;
    cycfi::elements::static_text _artist_text;
    cycfi::elements::static_text _album_text;
    cycfi::elements::image _album_image;

    cycfi::elements::basic_text_box _name_input;
    cycfi::elements::basic_text_box _path_input;

    void loadStation(const std::string& filename);
    void saveStation();
    void deleteStation(const std::string& stationName);
    void updateMetadata();
    void createStationButtons();
};

#endif
