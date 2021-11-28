/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <GaussianUtils/GaussianDistribution.h>
#include <GaussianUtils/components/RandomModelFactory.h>

namespace gauss {
class GaussianDistributionFactory
    : public RandomModelFactory<GaussianDistribution>
    , public StateSpaceSizeAware {
public:
  GaussianDistributionFactory(const std::size_t model_size);

  std::size_t getStateSpaceSize() const override { return mean_center.size(); }

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
