/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#include <Eigen/Eigenvalues>
#include <GaussianUtils/Utils.h>

namespace gauss {
Eigen::MatrixXd computeCovarianceInvert(const Eigen::MatrixXd &sigma) {
    Eigen::EigenSolver<Eigen::MatrixXd> eig_solv(sigma);
    auto eig_vals = eig_solv.eigenvalues();
    auto eig_vecs_complex = eig_solv.eigenvectors();
    Eigen::MatrixXd eig_vecs(eig_vecs_complex.rows(), eig_vecs_complex.cols());
    for (Eigen::Index r = 0; r < eig_vecs_complex.rows(); ++r) {
        for (Eigen::Index c = 0; c < eig_vecs_complex.cols(); ++c) {
            eig_vecs(r, c) = eig_vecs_complex(r,c).real();
        }
    }

    Eigen::MatrixXd sigma_inverse (sigma.rows(), sigma.cols());
    sigma_inverse.setZero();
    for (Eigen::Index k = 0; k < sigma.rows(); ++k) {
        sigma_inverse(k, k) = 1.0 / eig_vals(k).real();
    }
    return eig_vecs * sigma_inverse * eig_vecs.transpose();
}

constexpr double TOLLERANCE = 1e-5;
bool isSuitableCovarianceMatrix(const Eigen::MatrixXd &sigma) {
  if (sigma.rows() != sigma.cols()) {
    return false;
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
