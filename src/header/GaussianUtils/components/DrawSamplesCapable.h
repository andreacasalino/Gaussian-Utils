/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <Eigen/Core>
#include <vector>

namespace gauss {
class DrawSamplesCapable {
public:
  virtual ~DrawSamplesCapable() = default;

  virtual std::vector<Eigen::VectorXd>
  drawSamples(const std::size_t samples) const = 0;

protected:
  DrawSamplesCapable() = default;
};

} // namespace gauss
