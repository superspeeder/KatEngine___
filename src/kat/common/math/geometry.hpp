#pragma once

#include "kat/utils.hpp"

namespace kat {
    namespace math {

        template<kat::numeric T>
        struct Rect {
            T left, top, right, bottom;
        };
    }
}