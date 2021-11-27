/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <GaussianUtils/GaussianDistribution.h>
#include <random>

namespace gauss {
class GaussianDistributionSampler {
public:
  GaussianDistributionSampler(const GaussianDistribution &distribution);

  Eigen::VectorXd getSample() const;

private:
  const Eigen::VectorXd traslation;
  const Eigen::MatrixXd rotation;
  mutable std::normal_distribution<double> gauss_iso;
  mutable std::default_random_engine generator;
};
} // namespace gauss
