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
  GaussianDistributionFactory(const std::size_t model_size);

  std::unique_ptr<GaussianDistribution> makeRandomModel() const override;

  void setMeanCenter(const Eigen::VectorXd& center);
  void setMeanScale(const Eigen::VectorXd& scale);
  void setEigenValues(const Eigen::VectorXd& eigs);

private:
  Eigen::VectorXd mean_center;
  Eigen::VectorXd mean_scale;
  Eigen::VectorXd covariance_eigenvalues;
};

Eigen::MatrixXd make_random_covariance(const Eigen::VectorXd& eig_vals);
} // namespace gauss
