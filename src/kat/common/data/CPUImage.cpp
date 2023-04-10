#include "CPUImage.hpp"
#include <stb_image.h>

namespace kat {

    CPUImage::CPUImage(const std::string &path, uint32_t preferredChannels, bool flipVertically, bool unpremultiply) {
        stbi_set_flip_vertically_on_load(flipVertically);
        stbi_set_unpremultiply_on_load(unpremultiply);

        int x, y, noc;

        unsigned char* pixels = stbi_load(path.c_str(), &x, &y, &noc, static_cast<int>(preferredChannels));

        if (preferredChannels == 0) {
            m_Channels = channels_in_file;
        } else {
            m_Channels = preferredChannels;
        }

    }

    const glm::uvec2 &CPUImage::getSize() const {
        return m_Size;
    }

    uint32_t CPUImage::getChannels() const {
        return m_Channels;
    }

    const std::vector<unsigned char> &CPUImage::getPixels() const {
        return m_Pixels;
    }
}

