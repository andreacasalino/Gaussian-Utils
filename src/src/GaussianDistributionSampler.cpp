/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#include <GaussianUtils/GaussianDistributionSampler.h>
#include <Eigen/Cholesky>

namespace gauss {
namespace {
Eigen::MatrixXd compute_rotation(const GaussianDistribution &distribution) {
  Eigen::LLT<Eigen::MatrixXd> lltOfCov(distribution.getCovariance());
  return lltOfCov.matrixL();
}
} // namespace
GaussianDistributionSampler::GaussianDistributionSampler(
    const GaussianDistribution &distribution)
    : traslation(distribution.getMean()),
      rotation(compute_rotation(distribution)) {}

Eigen::VectorXd GaussianDistributionSampler::getSample() const {
  Eigen::VectorXd sample(traslation.size());
  for (std::size_t k = 0; k < static_cast<std::size_t>(traslation.size());
       ++k) {
    sample(k) = gauss_iso(generator);
  }
  sample = rotation * sample;
  sample += traslation;
  return sample;
}
} // namespace gauss
