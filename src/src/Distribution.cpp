#include <Distribution.h>
#include <Utils.h>

namespace gauss {
static const double LOG_2_PI = log(2.0 * PI_GREEK);
double Distribution::evalNormalLogDensity(const Eigen::VectorXd &point) const {
  double den;
  const auto &mean = getMean();
  const auto &cov_inv = getCovarianceInv();
  den = (point - mean).transpose() * cov_inv * (point - mean);
  den += point.size() * LOG_2_PI;
  den += log(getAbsDeterminantCovarianceInv());
  den *= -0.5;
  return den;
}
} // namespace gauss