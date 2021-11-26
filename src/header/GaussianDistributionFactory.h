/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <GaussianDistribution.h>
#include <components/RandomModelFactory.h>

namespace gauss {
class GaussianDistributionFactory
    : public RandomModelFactory<GaussianDistribution> {
public:
  GaussianDistributionFactory();

  std::unique_ptr<GaussianDistribution> makeRandomModel() const override;

private:
  Eigen::VectorXd mean_lower_corner_box;
  Eigen::VectorXd mean_upper_corner_box;
  Eigen::VectorXd covariance_eigenvalues;
};
} // namespace gauss
