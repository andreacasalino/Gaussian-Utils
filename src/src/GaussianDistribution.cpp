/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#include "GaussianDistributionSampler.h"
#include <Eigen/Dense>
#include <GaussianDistribution.h>
#include <stdexcept>

namespace gauss {
GaussianDistribution::GaussianDistribution(const Eigen::VectorXd &mean,
                                           const Eigen::MatrixXd &covariance,
                                           bool treat_covariance_as_inv)
    : mean(mean) {
  if (!isSuitableCovarianceMatrix(covariance)) {
    throw std::runtime_error("Invalid covariance");
  }
  if (treat_covariance_as_inv) {
    this->covariance_inv = std::make_unique<const Eigen::MatrixXd>(covariance);
  } else {
    this->covariance = std::make_unique<const Eigen::MatrixXd>(covariance);
  }
}

Eigen::MatrixXd
GaussianDistribution::GaussianDistribution::getCovariance() const {
  if (nullptr != covariance) {
    covariance =
        std::make_unique<const Eigen::MatrixXd>(covariance_inv->inverse());
  }
  return *covariance;
};
Eigen::MatrixXd GaussianDistribution::getCovarianceInv() const {
  if (nullptr != covariance_inv) {
    covariance_inv =
        std::make_unique<const Eigen::MatrixXd>(covariance->inverse());
  }
  return *covariance_inv;
};
double GaussianDistribution::getCovarianceDeterminant() const {
  if (nullptr != covariance) {
    covariance =
        std::make_unique<const Eigen::MatrixXd>(covariance_inv->inverse());
  }
  if (nullptr != covariance_abs_determinant) {
    covariance_abs_determinant =
        std::make_unique<double>(covariance->determinant());
  }
  return *covariance_abs_determinant;
};

static const double LOG_2_PI = log(2.0 * PI_GREEK);
double
GaussianDistribution::evaluateLogDensity(const Eigen::VectorXd &point) const {
  double den;
  if (nullptr != covariance_inv) {
    covariance_inv =
        std::make_unique<const Eigen::MatrixXd>(covariance->inverse());
  }
  den = (point - mean).transpose() * (*covariance_inv) * (point - mean);
  den += point.size() * LOG_2_PI;
  den += log(getCovarianceDeterminant());
  den *= -0.5;
  return den;
}

std::vector<Eigen::VectorXd>
GaussianDistribution::drawSamples(const std::size_t samples) const {
  GaussianDistributionSampler sampler(*this);
  std::vector<Eigen::VectorXd> result;
  result.reserve(samples);
  for (std::size_t s = 0; s < samples; ++s) {
    result.push_back(sampler.getSample());
  }
  return result;
}

} // namespace gauss
