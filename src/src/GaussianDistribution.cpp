/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#include <Eigen/Dense>
#include <GaussianUtils/Error.h>
#include <GaussianUtils/GaussianDistribution.h>
#include <GaussianUtils/GaussianDistributionSampler.h>

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

GaussianDistribution::GaussianDistribution(const GaussianDistribution &o) {
  *this = o;
}
GaussianDistribution &
GaussianDistribution::operator=(const GaussianDistribution &o) {
  this->mean = o.mean;
  if (nullptr != o.covariance) {
    this->covariance = std::make_unique<Eigen::MatrixXd>(*o.covariance);
  }
  if (nullptr != o.covariance_inv) {
    this->covariance_inv = std::make_unique<Eigen::MatrixXd>(*o.covariance_inv);
  }
  if (nullptr != o.covariance_abs_determinant) {
    this->covariance_abs_determinant =
        std::make_unique<double>(*o.covariance_abs_determinant);
  }
  return *this;
}

GaussianDistribution::GaussianDistribution(GaussianDistribution &&o) {
  *this = std::move(o);
}
GaussianDistribution &
GaussianDistribution::operator=(GaussianDistribution &&o) {
  this->mean = o.mean;
  this->covariance = std::move(o.covariance);
  this->covariance_inv = std::move(o.covariance_inv);
  this->covariance_abs_determinant = std::move(o.covariance_abs_determinant);
  return *this;
}

Eigen::MatrixXd
GaussianDistribution::GaussianDistribution::getCovariance() const {
  if (nullptr == covariance) {
    covariance = std::make_unique<const Eigen::MatrixXd>(
        computeCovarianceInvert(*covariance_inv));
  }
  return *covariance;
};
Eigen::MatrixXd GaussianDistribution::getCovarianceInv() const {
  if (nullptr == covariance_inv) {
    covariance_inv = std::make_unique<const Eigen::MatrixXd>(
        computeCovarianceInvert(*covariance));
  }
  return *covariance_inv;
};
double GaussianDistribution::getCovarianceDeterminant() const {
  if (nullptr == covariance) {
    covariance = std::make_unique<const Eigen::MatrixXd>(
        computeCovarianceInvert(*covariance_inv));
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
    covariance_inv = std::make_unique<const Eigen::MatrixXd>(
        computeCovarianceInvert(*covariance));
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
    const GaussianDistribution &other) const {
  double result = log(abs(other.getCovarianceDeterminant())) -
                  log(abs(this->getCovarianceDeterminant()));
  const auto cov_inv = other.getCovarianceInv();
  Eigen::MatrixXd P = cov_inv * this->getCovariance();
  result += P.trace();
  Eigen::VectorXd Delta = this->mean - other.mean;
  result += Delta.transpose() * cov_inv * Delta;
  result -= static_cast<double>(this->mean.size());
  result *= 0.5f;
  return result;
}

namespace {
Eigen::VectorXd get_portion(const Eigen::VectorXd &subject,
                            const std::set<Eigen::Index> &indices) {
  Eigen::VectorXd result(indices.size());
  Eigen::Index pos = 0;
  for (auto it = indices.begin(); it != indices.end(); ++it, ++pos) {
    result(pos) = subject(*it);
  }
  return result;
}

Eigen::MatrixXd get_portion(const Eigen::MatrixXd &subject,
                            const std::set<Eigen::Index> &rows,
                            const std::set<Eigen::Index> &cols) {
  Eigen::MatrixXd result(rows.size(), cols.size());
  Eigen::Index row = 0;
  for (auto it_row = rows.begin(); it_row != rows.end(); ++it_row, ++row) {
    Eigen::Index col = 0;
    for (auto it_col = cols.begin(); it_col != cols.end(); ++it_col, ++col) {
      result(row, col) = subject(*it_row, *it_col);
    }
  }
  return result;
}
} // namespace

GaussianDistribution GaussianDistribution::getConditioned(
    const std::set<std::size_t> &observations_indices,
    const Eigen::VectorXd &observations) const {
  if (static_cast<std::size_t>(observations.size()) !=
      observations_indices.size()) {
    throw Error("invalid indices");
  }

  std::set<Eigen::Index> remaining, leaving;
  for (std::size_t i = 0; i < getStateSpaceSize(); ++i) {
    if (observations_indices.find(i) == observations_indices.end()) {
      remaining.emplace(static_cast<Eigen::Index>(i));
    } else {
      leaving.emplace(static_cast<Eigen::Index>(i));
    }
  }

  Eigen::VectorXd mean_1 = get_portion(mean, remaining);
  Eigen::VectorXd mean_2 = get_portion(mean, leaving);
  Eigen::MatrixXd cov_11 = get_portion(*covariance, remaining, remaining);
  Eigen::MatrixXd cov_22 = get_portion(*covariance, leaving, leaving);
  Eigen::MatrixXd cov_12 = get_portion(*covariance, remaining, leaving);

  Eigen::MatrixXd temp = cov_12 * computeCovarianceInvert(cov_22);
  return GaussianDistribution(mean_1 + temp * (observations - mean_2),
                              cov_11 - temp * cov_12.transpose());
}

GaussianDistribution
GaussianDistribution::getConditioned(const std::size_t observation_index,
                                     const double observation) const {
  Eigen::VectorXd temp(1);
  temp << observation;
  return getConditioned(std::set<std::size_t>{observation_index}, temp);
}
} // namespace gauss
