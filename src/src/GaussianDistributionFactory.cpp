/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#include <GaussianUtils/GaussianDistributionFactory.h>
#include <GaussianUtils/Error.h>

namespace gauss {
	GaussianDistributionFactory::GaussianDistributionFactory(const std::size_t model_size)
		: mean_center(model_size)
		, mean_scale(model_size)
		, covariance_eigenvalues(model_size) {
		if (0 == model_size) {
			throw Error("Invalid model size");
		}
		mean_center.setZero();
		mean_scale.setOnes();
		covariance_eigenvalues.setOnes();
	}

	namespace {
		Eigen::VectorXd make_random_mean(const Eigen::VectorXd& mean_center, const Eigen::VectorXd& mean_scale) {
			Eigen::VectorXd sample(mean_center.size());
			sample.setRandom();
			for (Eigen::Index k = 0; k < mean_center.size(); ++k) {
				sample(k) *= mean_scale(k);
			}
			sample += mean_center;
			return sample;
		}

		void make_orthogonal(Eigen::VectorXd& vector,
			const Eigen::VectorXd& direction) {
			vector -= (vector.dot(direction)) * direction;
		}
		Eigen::MatrixXd sample_rotation(const std::size_t size) {
			Eigen::MatrixXd rotation(size, size);
			for (std::size_t k = 0; k < size; ++k) {
				Eigen::VectorXd col(size);
				col.setRandom();
				for (std::size_t k2 = 0; k2 < k; ++k2) {
					make_orthogonal(col, rotation.col(k2));
				}
				col *= 1.0 / col.norm();
				rotation.col(static_cast<Eigen::Index>(k)) = col;
			}
			return rotation;
		}
	}
	Eigen::MatrixXd make_random_covariance(const Eigen::VectorXd& eig_vals) {
		Eigen::MatrixXd covariance(eig_vals.size(), eig_vals.size());
		covariance.setZero();
		for (Eigen::Index k = 0; k < eig_vals.size(); ++k) {
			covariance(k, k) = eig_vals(k);
		}

		Eigen::MatrixXd rotation = sample_rotation(eig_vals.size());

		return rotation * covariance * rotation.transpose();
	}

	std::unique_ptr<GaussianDistribution> GaussianDistributionFactory::makeRandomModel() const {

		return std::make_unique<GaussianDistribution>(make_random_mean(mean_center, mean_scale), make_random_covariance(covariance_eigenvalues));
	}

	void GaussianDistributionFactory::setMeanCenter(const Eigen::VectorXd& center) {
		if (mean_center.size() != center.size()) {
			throw Error("Invalid mean center");
		}
		mean_center = center;
	}

	void GaussianDistributionFactory::setMeanScale(const Eigen::VectorXd& scale) {
		if (mean_scale.size() != scale.size()) {
			throw Error("Invalid mean scale");
		}
		mean_scale = scale;
	}

	void GaussianDistributionFactory::setEigenValues(const Eigen::VectorXd& eigs) {
		if (covariance_eigenvalues.size() != eigs.size()) {
			throw Error("Invalid eigenvalues");
		}
		for (Eigen::Index i = 0; i < eigs.size(); ++i) {
			if (eigs(i) < 0.000001) {
				throw Error("Invalid eigenvalues: at least one negative value");
			}
		}
		covariance_eigenvalues = eigs;
	}
}
