/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <memory>

namespace gauss {
template <typename ModelT> class RandomModelFactory {
public:
  virtual ~RandomModelFactory() = default;

  virtual std::unique_ptr<ModelT> makeRandomModel() const = 0;

protected:
  RandomModelFactory() = default;
};

} // namespace gauss
