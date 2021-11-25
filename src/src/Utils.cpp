#include <GaussianUtils.h>

namespace gauss {
	double evalNormalLogDensity(const Distribution& distribution, const Eigen::VectorXd& point) {
		double den;
		const auto& mean = distribution.getMean();
		const auto& cov_inv = distribution.getCovarianceInv();
		den = (point - mean).transpose() * cov_inv * (point - mean);
		den += point.size() * LOG_2_PI;
		den += log(distr.Abs_Deter_Cov);
		den *= -0.5;
		return den;
	}
}
