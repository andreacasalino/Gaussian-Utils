/**
 * Author:    Andrea Casalino
 * Created:   26.11.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <Eigen/Core>
#include <GaussianUtils/Error.h>

namespace gauss {
	class TrainSet {
	public:
		TrainSet(const TrainSet& o) = default;
		TrainSet& operator=(const TrainSet& o) = default;

		TrainSet(TrainSet&& o) = default;
		TrainSet& operator=(TrainSet&& o) = default;

		/** @brief Import the training set from a textual file.
		 * Every line of the file is a sample. Clearly, all the rows must have the same number of elements
		 * @param The location of the file to import (it can be a relative or an absolute path)
		 */
		TrainSet(const std::string& file_to_read);

		/** @brief Build a training set by cloning the samples passed as input.
		 * Container is in iterable container of vectors, having all the same size
		 * @param The iterable collection of samples characterizing the training set to build
		 */
		template<typename Collection>
		TrainSet(const Collection& samples) 
			: TrainSet(samples.front()) {
			if (samples.empty()) throw gauss::Error("training set can't be empty");
			auto it = samples.begin();
			++it;
			this->addSamples(it, samples.end());
		};

		/** @brief Append the samples of another set into this set.
		 */
		inline void operator+=(const TrainSet& o) { this->addSamples(o.samples.begin(), o.samples.end()); };

		/** @brief Get the list of samples of this set.
		 */
		const std::vector<Eigen::VectorXd>& GetSamples() const { return samples; };

	private:
		TrainSet(const Eigen::VectorXd& initialSample);

		template<typename CollectionIter>
		void addSamples(const CollectionIter& samplesBegin, const CollectionIter& samplesEnd) {
			std::size_t to_add = 0;
			{
				for (auto it = samplesBegin; it != samplesEnd; ++it) {
					++to_add;
				}
			}
			samples.reserve(samples.size() + to_add);
			std::size_t pos = 0;
			for (auto it = samplesBegin; it != samplesEnd; ++it) {
				if (samples.front().size() != it->size()) {
					throw gauss::Error("found invalid size for sample " + pos);
				}
				samples.push_back(*it);
				++pos;
			}
		};

		std::vector<Eigen::VectorXd> samples;
	};
}
