#ifndef METADATA_HPP
#define METADATA_HPP

#include <string>
#include <vector>

struct TrackInfo {
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    int duration;
    std::vector<unsigned char> albumArt;
};

class MetadataReader {
public:
    static TrackInfo readMetadata(const std::string& filename);
};

#endif
