#pragma once

#include <CoviarianceAware.h>
#include <MeanAware.h>
#include <vector>

namespace gauss {
class GaussianDistribution;
class Distribution : public CovarianceAware, public MeanAware {
public:
  double evalNormalLogDensity(const Eigen::VectorXd &point) const;

  GaussianDistribution getConditioned(const Eigen::VectorXd& point, const std::vector<std::size_t>& point_indices) const;

protected:
  Distribution() = default;
};
} // namespace gauss
