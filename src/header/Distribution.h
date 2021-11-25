#pragma once

#include <CoviarianceAware.h>
#include <MeanAware.h>

namespace gauss {
class Distribution : public CovarianceAware, public MeanAware {
public:
  double evalNormalLogDensity(const Eigen::VectorXd &point) const;

protected:
  Distribution() = default;
};
} // namespace gauss
