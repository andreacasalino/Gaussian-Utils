#pragma once

#include <Eigen/Core>

namespace gauss {
	class Distribution {
	public:
		// throw in case of not valid inputs
		Distribution(const Eigen::VectorXd& mean, const Eigen::MatrixXd& covarianceInverse);

		// throw in case of not valid inputs
		template<typename Iterable>
		Distribution(const Iterable& samples);

	protected:
		Eigen::VectorXd mean;
		Eigen::MatrixXd covarianceInverse;
	};
}
