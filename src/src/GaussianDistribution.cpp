/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#include <Eigen/Dense>
#include <GaussianDistribution.h>
#include <stdexcept>

namespace gauss {
double GaussianDistributionBase::getDeterminantCovariance() const {
  if (!covariance_abs_determinant) {
    covariance_abs_determinant =
        std::make_unique<const double>(abs(getCovariance().determinant()));
  }
  return *covariance_abs_determinant;
}
namespace {
const Eigen::MatrixXd &check_covariance(const Eigen::MatrixXd &covariance) {
  if (!isSymmetricPositive(covariance)) {
    throw std::runtime_error("Invalid covariance");
  }
  return covariance;
};
} // namespace

GaussianDistribution::GaussianDistribution(const Eigen::VectorXd &mean,
                                           const Eigen::MatrixXd &covariance)
    : GaussianDistributionBase(mean), covariance(check_covariance(covariance)) {
  if (mean.size() != covariance.cols()) {
    throw std::runtime_error("Inconsistent mean-covariance pair");
  }
}

Eigen::MatrixXd GaussianDistribution::getCovarianceInv() const {
  if (!covariance_inv) {
    covariance_inv =
        std::make_unique<const Eigen::MatrixXd>(getCovariance().inverse());
  }
  return *covariance_inv;
}

GaussianDistributionFromInverseCov::GaussianDistributionFromInverseCov(
    const Eigen::VectorXd &mean, const Eigen::MatrixXd &covarianceInv)
    : GaussianDistributionBase(mean),
      covariance_inv(check_covariance(covarianceInv)) {
  if (mean.size() != covarianceInv.cols()) {
    throw std::runtime_error("Inconsistent mean-covariance pair");
  }
}

Eigen::MatrixXd GaussianDistributionFromInverseCov::getCovariance() const {
  if (!covariance) {
    covariance =
        std::make_unique<const Eigen::MatrixXd>(getCovarianceInv().inverse());
  }
  return *covariance;
}

} // namespace gauss
