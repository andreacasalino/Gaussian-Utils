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
