/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#include <GaussianUtils/GaussianDistributionSampler.h>
#include <Eigen/Dense>
#include <GaussianUtils/GaussianDistribution.h>
#include <GaussianUtils/Error.h>

namespace gauss {
GaussianDistribution::GaussianDistribution(const Eigen::VectorXd &mean,
                                           const Eigen::MatrixXd &covariance,
                                           bool treat_covariance_as_inv)
    : mean(mean) {
  if (!isSuitableCovarianceMatrix(covariance)) {
    throw Error("Invalid covariance");
  }
  if (treat_covariance_as_inv) {
    this->covariance_inv = std::make_unique<const Eigen::MatrixXd>(covariance);
  } else {
    this->covariance = std::make_unique<const Eigen::MatrixXd>(covariance);
  }
}

GaussianDistribution::GaussianDistribution(const GaussianDistribution& o) {
    *this = o;
}
GaussianDistribution& GaussianDistribution::operator=(const GaussianDistribution& o) {
    this->mean = o.mean;
    if (nullptr != o.covariance) {
        this->covariance = std::make_unique<Eigen::MatrixXd>(*o.covariance);
    }
    if (nullptr != o.covariance_inv) {
        this->covariance_inv = std::make_unique<Eigen::MatrixXd>(*o.covariance_inv);
    }
    if (nullptr != o.covariance_abs_determinant) {
        this->covariance_abs_determinant = std::make_unique<double>(*o.covariance_abs_determinant);
    }
    return *this;
}

GaussianDistribution::GaussianDistribution(GaussianDistribution&& o) {
    *this = std::move(o);
}
GaussianDistribution& GaussianDistribution::operator=(GaussianDistribution&& o) {
    this->mean = o.mean;
    this->covariance = std::move(o.covariance);
    this->covariance_inv = std::move(o.covariance_inv);
    this->covariance_abs_determinant = std::move(o.covariance_abs_determinant);
    return *this;
}

Eigen::MatrixXd
GaussianDistribution::GaussianDistribution::getCovariance() const {
  if (nullptr == covariance) {
    covariance =
        std::make_unique<const Eigen::MatrixXd>(computeCovarianceInvert(*covariance_inv));
  }
  return *covariance;
};
Eigen::MatrixXd GaussianDistribution::getCovarianceInv() const {
  if (nullptr == covariance_inv) {
    covariance_inv =
        std::make_unique<const Eigen::MatrixXd>(computeCovarianceInvert(*covariance));
  }
  return *covariance_inv;
};
double GaussianDistribution::getCovarianceDeterminant() const {
  if (nullptr == covariance) {
    covariance =
        std::make_unique<const Eigen::MatrixXd>(computeCovarianceInvert(*covariance_inv));
  }
  if (nullptr == covariance_abs_determinant) {
    covariance_abs_determinant =
        std::make_unique<double>(covariance->determinant());
  }
  return *covariance_abs_determinant;
};

static const double LOG_2_PI = log(2.0 * PI_GREEK);
double
GaussianDistribution::evaluateLogDensity(const Eigen::VectorXd &point) const {
  double den;
  if (nullptr == covariance_inv) {
    covariance_inv =
        std::make_unique<const Eigen::MatrixXd>(computeCovarianceInvert(*covariance));
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

double GaussianDistribution::evaluateKullbackLeiblerDivergence(
    const GaussianDistribution& other) const {
    double result = log(abs(other.getCovarianceDeterminant())) - log(abs(this->getCovarianceDeterminant()));
    const auto cov_inv = other.getCovarianceInv();
    Eigen::MatrixXd P = cov_inv * this->getCovariance();
    result += P.trace();
    Eigen::VectorXd Delta = this->mean - other.mean;
    result += Delta.transpose() * cov_inv * Delta;
    result -= static_cast<double>(this->mean.size());
    result *= 0.5f;
    return result;
}
} // namespace gauss
