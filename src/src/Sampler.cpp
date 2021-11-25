#include <Eigen/Cholesky>
#include <Sampler.h>

namespace gauss {
namespace {
Eigen::MatrixXd compute_rotation(const Distribution &distribution) {
  Eigen::LLT<Eigen::MatrixXd> lltOfCov(distribution.getCovariance());
  return lltOfCov.matrixL();
}
} // namespace
Sampler::Sampler(const Distribution &distribution)
    : traslation(distribution.getMean()),
      rotation(compute_rotation(distribution)) {}

Eigen::VectorXd Sampler::getSample() const {
  Eigen::VectorXd sample(traslation.size());
  for (std::size_t k = 0; k < static_cast<std::size_t>(traslation.size()); ++k) {
      sample(k) = gauss_iso(generator);
  }
  sample = rotation * sample;
  sample += traslation;
  return sample;
}
} // namespace gauss
