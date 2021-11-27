/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <Eigen/Core>

namespace gauss {
class LogDensityAware {
public:
  virtual ~LogDensityAware() = default;

  virtual double evaluateLogDensity(const Eigen::VectorXd &point) const = 0;

protected:
  LogDensityAware() = default;
};

} // namespace gauss
