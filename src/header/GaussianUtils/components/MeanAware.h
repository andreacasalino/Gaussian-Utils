/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <Eigen/Core>

namespace gauss {
class MeanAware {
public:
  virtual ~MeanAware() = default;

  virtual Eigen::VectorXd getMean() const = 0;

protected:
  MeanAware() = default;
};

} // namespace gauss
