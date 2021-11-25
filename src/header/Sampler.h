#pragma once

#include <Distribution.h>
#include <random>

namespace gauss {
class Sampler {
public:
  Sampler(const Distribution &distribution);

  Eigen::VectorXd getSample() const;

private:
  const Eigen::VectorXd traslation;
  const Eigen::MatrixXd rotation;
  mutable std::normal_distribution<double> gauss_iso;
  mutable std::default_random_engine generator;
};
} // namespace gauss
