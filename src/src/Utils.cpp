#include <Eigen/Eigenvalues>
#include <Utils.h>

namespace gauss {
void computeCovarianceInvert(Eigen::MatrixXd &sigma_inverse,
                             const Eigen::MatrixXd &sigma) {
  // LLT<MatrixXf> lltOfCov(Sigma);
  // MatrixXf L(lltOfCov.matrixL());
  //*Sigma_inverse = L * L.transpose();

  sigma_inverse = sigma.inverse();
}

constexpr double TOLLERANCE = 1e-5;
bool isSymmetricPositive(const Eigen::MatrixXd &sigma) {
  std::size_t K = (std::size_t)sigma.cols();
  std::size_t c;
  for (std::size_t r = 0; r < K; ++r) {
    for (c = (r + 1); c < K; ++c) {
      if (abs(sigma(r, c) - sigma(c, r)) > TOLLERANCE)
        return false;
    }
  }

  Eigen::EigenSolver<Eigen::MatrixXd> eig_solv(sigma);
  auto eigs = eig_solv.eigenvalues();

  // check all values are sufficient high
  for (std::size_t k = 0; k < K; ++k) {
    if (abs(eigs(k).real()) < TOLLERANCE)
      return false;
  }
  return true;
}

double evalNormalLogDensity(const Distribution &distribution,
                            const Eigen::VectorXd &point) {
  double den;
  const auto &mean = distribution.getMean();
  const auto &cov_inv = distribution.getCovarianceInv();
  den = (point - mean).transpose() * cov_inv * (point - mean);
  den += point.size() * LOG_2_PI;
  den += log(distribution.getAbsDeterminantCovarianceInv());
  den *= -0.5;
  return den;
}
} // namespace gauss
