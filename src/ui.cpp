#include "ui.hpp"
#include <iostream>
#include <fstream>
#include <elements.hpp>

using namespace cycfi::elements;

LiveApp::LiveApp()
    : _app(400, 400, "Live"), _window(_app.name()) {}

    void LiveApp::run() {
        auto play_button = button("Play");
        auto pause_button = button("Pause");
        auto stop_button = button("Stop");
    
        play_button.on_click = [this] { _player.play(); };
        pause_button.on_click = [this] { _player.pause(); };
        stop_button.on_click = [this] { _player.stop(); };
    
        _title_text = static_text("Title: ");
        _artist_text = static_text("Artist: ");
        _album_text = static_text("Album: ");
        _album_image = image("assets/default.png");
    
        _name_input = basic_text_box("Station Name");
        _path_input = basic_text_box("File Path");
    
        auto save_button = button("Save Station");
        save_button.on_click = [this] { saveStation(); };
    
        auto station_buttons = vtile();
        for (auto& station : _stations) {
            auto station_button = button(station.name);
            station_button.on_click = [this, station] { loadStation(station.filePath); };
    
            auto delete_button = button("❌");
            delete_button.on_click = [this, station] { deleteStation(station.name); };
    
            station_buttons.push_back(htile(station_button, delete_button));
        }
    
        auto controls = vtile(
            _title_text,
            _artist_text,
            _album_text,
            margin({ 10, 10, 10, 10 }, _album_image),
            htile(play_button, pause_button, stop_button),
            vscroll(station_buttons),
            _name_input,
            _path_input,
            save_button
        );
    
        _window.content(controls);
        _app.run();
    }
    
    void LiveApp::deleteStation(const std::string& stationName) {
        auto it = std::remove_if(_stations.begin(), _stations.end(), [&](const RadioStation& station) {
            return station.name == stationName;
        });
    
        if (it != _stations.end()) {
            _stations.erase(it, _stations.end());
            PresetManager::savePresets(_stations);
            _window.refresh();
        }
    }
    
