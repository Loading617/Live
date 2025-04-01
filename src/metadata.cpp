#include "metadata.hpp"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/apicframe.h>
#include <iostream>

TrackInfo MetadataReader::readMetadata(const std::string& filename) {
    TrackInfo info;

    TagLib::FileRef file(filename.c_str());
    if (!file.isNull() && file.tag()) {
        TagLib::Tag* tag = file.tag();
        info.title = tag->title().toCString(true);
        info.artist = tag->artist().toCString(true);
        info.album = tag->album().toCString(true);
        info.genre = tag->genre().toCString(true);
        info.duration = file.audioProperties() ? file.audioProperties()->length() : 0;
    }

    TagLib::MPEG::File mpegFile(filename.c_str());
    if (mpegFile.isValid() && mpegFile.ID3v2Tag()) {
        TagLib::ID3v2::Tag* id3v2tag = mpegFile.ID3v2Tag();
        TagLib::ID3v2::FrameList frames = id3v2tag->frameList("APIC");

        if (!frames.isEmpty()) {
            auto* apic = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(frames.front());
            if (apic) {
                info.albumArt.assign(apic->picture().data(), apic->picture().data() + apic->picture().size());
            }
        }
    }

    return info;
}
