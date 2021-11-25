#pragma once

#include <Distribution.h>
#include <Utils.h>
#include <memory>

namespace gauss {
class GaussianDistributionBase : public Distribution {
protected:
  // throw in case of not valid inputs
  GaussianDistributionBase(const Eigen::VectorXd &mean) : mean(mean){};

  Eigen::VectorXd getMean() const override { return mean; };
  double getAbsDeterminantCovarianceInv() const override;

  const Eigen::VectorXd mean;
  mutable std::unique_ptr<const double> covariance_inv_abs_determinant;
};

class GaussianDistribution : public GaussianDistributionBase {
public:
  // throw in case of not valid inputs
  GaussianDistribution(const Eigen::VectorXd &mean,
                       const Eigen::MatrixXd &covariance);

  template <typename Iterable>
  GaussianDistribution(const Iterable &samples)
      : GaussianDistributionBase(computeMean(samples),
                                 computeCovariance(samples)){};

  Eigen::MatrixXd getCovariance() const override { return covariance; };
  Eigen::MatrixXd getCovarianceInv() const override;

protected:
  const Eigen::MatrixXd covariance;
  mutable std::unique_ptr<const Eigen::MatrixXd> covariance_inv;
};

class GaussianDistributionFromInverseCov : public GaussianDistributionBase {
public:
  // throw in case of not valid inputs
  GaussianDistributionFromInverseCov(const Eigen::VectorXd &mean,
                                     const Eigen::MatrixXd &covariance_inv);

  Eigen::MatrixXd getCovariance() const override;
  Eigen::MatrixXd getCovarianceInv() const override { return covariance_inv; };

protected:
  mutable std::unique_ptr<const Eigen::MatrixXd> covariance;
  const Eigen::MatrixXd covariance_inv;
};

} // namespace gauss
