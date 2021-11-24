#pragma once

#include <Eigen/Core>

namespace gauss {
	class CovarianceAware {
	public:
		virtual ~CovarianceAware() = default;

		virtual Eigen::MatrixXd getCovariance() = 0;
		virtual Eigen::MatrixXd getCovarianceInv() = 0;

	protected:
		CovarianceAware() = default;
	};

	class Distribution
		: public CovarianceAware {
	public:

		const Eigen::VectorXd& getMean() const { return mean; }

	protected:
		Eigen::VectorXd mean;
	};

	class DistributionBasic {
		// throw in case of not valid inputs
		Distribution(const Eigen::VectorXd& mean, const Eigen::MatrixXd& covarianceInverse);

		template<typename Iterable>
		Distribution(const Iterable& samples);
	};
}
