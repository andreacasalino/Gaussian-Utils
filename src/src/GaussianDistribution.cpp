#include <GaussianDistribution.h>
#include <stdexcept>

namespace gauss {
double GaussianDistributionBase::getAbsDeterminantCovarianceInv() const {
  if (!covariance_inv_abs_determinant) {
    covariance_inv_abs_determinant =
        std::make_unique<const double>(abs(getCovarianceInv().determinant()));
  }
  return *covariance_inv_abs_determinant;
}

namespace {
const Eigen::MatrixXd &check_covariance(const Eigen::MatrixXd &covariance) {
  if (!isValidCovariance(covariance)) {
    throw std::runtime_error("Invalid covariance");
  }
  return covariance;
};
} // namespace

GaussianDistribution::GaussianDistribution(const Eigen::VectorXd &mean,
                                           const Eigen::MatrixXd &covariance)
    : GaussianDistributionBase(mean), covariance(check_covariance(covariance)) {
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
      covariance_inv(check_covariance(covarianceInv)) {}

Eigen::MatrixXd GaussianDistributionFromInverseCov::getCovariance() const {
  if (!covariance) {
    covariance =
        std::make_unique<const Eigen::MatrixXd>(getCovarianceInv().inverse());
  }
  return *covariance;
}

} // namespace gauss
