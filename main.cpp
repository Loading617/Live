#include <CtrlLib/CtrlLib.h>
#include <vlc/vlc.h>

using namespace Upp;

#define LAYOUTFILE <OfflineRadioApp/OfflineRadioApp.lay>
#include <CtrlCore/lay.h>

class LiveApp : public WithOfflineRadioAppLayout<TopWindow> {
private:
    libvlc_instance_t *vlcInstance;
    libvlc_media_player_t *player;

public:
    LiveApp() {
        CtrlLayout(*this, "Live");

        vlcInstance = libvlc_new(0, nullptr);
        player = nullptr;

        playBtn << [=] { PlaySelected(); };
        pauseBtn << [=] { Pause(); };
        stopBtn << [=] { Stop(); };
        volumeSlider.WhenAction = [=] { SetVolume(); };

        LoadPlaylist();
    }

    ~LiveApp() {
        if (player)
            libvlc_media_player_release(player);
        libvlc_release(vlcInstance);
    }

    void LoadPlaylist() {
        playlist.Add("radio1.mp3");
        playlist.Add("radio2.mp3");
        playlist.Add("radio3.mp3");
    }

    void PlaySelected() {
        if (player)
            libvlc_media_player_stop(player);

        String file = playlist.GetCurrentName();
        libvlc_media_t *media = libvlc_media_new_path(vlcInstance, file.ToStd());
        player = libvlc_media_player_new_from_media(media);
        libvlc_media_release(media);
        libvlc_media_player_play(player);
        SetVolume();
    }

    void Pause() {
        if (player)
            libvlc_media_player_set_pause(player, 1);
    }

    void Stop() {
        if (player)
            libvlc_media_player_stop(player);
    }

    void SetVolume() {
        if (player) {
            int volume = volumeSlider.GetPos();
            libvlc_audio_set_volume(player, volume);
        }
    }
};

GUI_APP_MAIN {
    LiveApp().Run();
}

