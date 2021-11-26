/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

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
bool isSuitableCovarianceMatrix(const Eigen::MatrixXd &sigma) {
  if (sigma.rows() != sigma.cols()) {
    throw std::runtime_error("Invalid covariance");
  }
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

  // check all values are positive
  for (std::size_t k = 0; k < K; ++k) {
    if (eigs(k).real() < -TOLLERANCE) {
      return false;
    }
  }
  return true;
}
} // namespace gauss
