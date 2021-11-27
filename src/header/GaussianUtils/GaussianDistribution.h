/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <GaussianUtils/Utils.h>
#include <GaussianUtils/components/CoviarianceAware.h>
#include <GaussianUtils/components/DivergenceAware.h>
#include <GaussianUtils/components/DrawSamplesCapable.h>
#include <GaussianUtils/components/LogDensityAware.h>
#include <GaussianUtils/components/MeanAware.h>
#include <memory>

namespace gauss {
class GaussianDistribution : public CovarianceAware,
                             public DivergenceAware<GaussianDistribution>,
                             public DrawSamplesCapable,
                             public LogDensityAware,
                             public MeanAware {
public:
  // throw in case of not valid inputs
  GaussianDistribution(const Eigen::VectorXd &mean,
                       const Eigen::MatrixXd &covariance,
                       bool treat_covariance_as_inv = false);

  template <typename Iterable>
  GaussianDistribution(const Iterable &samples)
      : GaussianDistribution(computeMean(samples),
                             computeCovariance(samples)){};

  GaussianDistribution(const GaussianDistribution &o);
  GaussianDistribution &operator=(const GaussianDistribution &o);

  GaussianDistribution(GaussianDistribution &&o) = delete;
  GaussianDistribution &operator=(GaussianDistribution &&o) = delete;

  Eigen::VectorXd getMean() const override { return mean; }

  Eigen::MatrixXd getCovariance() const override;
  Eigen::MatrixXd getCovarianceInv() const override;
  double getCovarianceDeterminant() const override;

  std::vector<Eigen::VectorXd>
  drawSamples(const std::size_t samples) const override;

  double evaluateLogDensity(const Eigen::VectorXd &point) const override;

  double evaluateKullbackLeiblerDivergence(
      const GaussianDistribution& other) const override;

protected:
  Eigen::VectorXd mean;
  mutable std::unique_ptr<const Eigen::MatrixXd> covariance;
  mutable std::unique_ptr<const Eigen::MatrixXd> covariance_inv;
  mutable std::unique_ptr<const double> covariance_abs_determinant;
};

} // namespace gauss
