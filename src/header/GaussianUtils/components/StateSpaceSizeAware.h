/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <cstdlib>

namespace gauss {
    class StateSpaceSizeAware {
    public:
        virtual ~StateSpaceSizeAware() = default;

        virtual std::size_t getStateSpaceSize() const = 0;

    protected:
        StateSpaceSizeAware() = default;
    };

} // namespace gauss
