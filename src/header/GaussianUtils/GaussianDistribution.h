/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <GaussianUtils/TrainSet.h>
#include <GaussianUtils/Utils.h>
#include <GaussianUtils/components/CoviarianceAware.h>
#include <GaussianUtils/components/DivergenceAware.h>
#include <GaussianUtils/components/DrawSamplesCapable.h>
#include <GaussianUtils/components/LogDensityAware.h>
#include <GaussianUtils/components/MeanAware.h>
#include <GaussianUtils/components/StateSpaceSizeAware.h>
#include <memory>
#include <set>

namespace gauss {
class GaussianDistribution : public CovarianceAware,
                             public DivergenceAware<GaussianDistribution>,
                             public DrawSamplesCapable,
                             public LogDensityAware,
                             public MeanAware,
                             public StateSpaceSizeAware {
public:
  // throw in case of not valid inputs
  GaussianDistribution(const Eigen::VectorXd &mean,
                       const Eigen::MatrixXd &covariance,
                       bool treat_covariance_as_inv = false);

  GaussianDistribution(const TrainSet &samples)
      : GaussianDistribution(
            computeMean(samples.GetSamples(),
                        [](const auto &sample) { return sample; }),
            computeCovariance(samples.GetSamples(),
                              [](const auto &sample) { return sample; })){};

  GaussianDistribution(const GaussianDistribution &o);
  GaussianDistribution &operator=(const GaussianDistribution &o);

  GaussianDistribution(GaussianDistribution &&o);
  GaussianDistribution &operator=(GaussianDistribution &&o);

  std::size_t getStateSpaceSize() const override { return mean.size(); }

  Eigen::VectorXd getMean() const override { return mean; }

  Eigen::MatrixXd getCovariance() const override;
  Eigen::MatrixXd getCovarianceInv() const override;
  double getCovarianceDeterminant() const override;

  std::vector<Eigen::VectorXd>
  drawSamples(const std::size_t samples) const override;

  double evaluateLogDensity(const Eigen::VectorXd &point) const override;

  double evaluateKullbackLeiblerDivergence(
      const GaussianDistribution &other) const override;

  GaussianDistribution getConditioned(const std::size_t observation_index,
                                      const double observation) const;
  GaussianDistribution
  getConditioned(const std::set<std::size_t> &observations_indices,
                 const Eigen::VectorXd &observations) const;

protected:
  Eigen::VectorXd mean;
  mutable std::unique_ptr<const Eigen::MatrixXd> covariance;
  mutable std::unique_ptr<const Eigen::MatrixXd> covariance_inv;
  mutable std::unique_ptr<const double> covariance_abs_determinant;
};

} // namespace gauss
