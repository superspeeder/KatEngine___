#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace kat {
    class CPUImage {
    public:
        static constexpr uint32_t channels_in_file = 0;

        /**
         * For images that will be transferred to the GPU, no settings have to be made (other than insuring that the channel count is correct).
         * For images that will be used as window icons, you *must* use a channel count of 4, the images *must* not be flipped on load, and the colors *must* be unpremultiplied.
         *      It is undefined behavior to not unpremultiply (ensure that the flag is set to true).
         *      Your icons will be vertically flipped if you do not set the flag correctly (should be false)
         *      Your icon will get ignored when being set if it does not have the correct number of channels.
         *
         * @param path
         * @param preferredChannels
         * @param flipVertically
         * @param unpremultiply Generally you shouldn't have to change this, however when we are loading window icons this must be true.
         */
        explicit CPUImage(const std::string& path, uint32_t preferredChannels = 4, bool flipVertically = true, bool unpremultiply = false);

        [[nodiscard]] const glm::uvec2 &getSize() const;

        [[nodiscard]] uint32_t getChannels() const;

        [[nodiscard]] const std::vector<unsigned char> &getPixels() const;

    private:

        glm::uvec2 m_Size;
        uint32_t m_Channels;
        std::vector<unsigned char> m_Pixels;
    };
}