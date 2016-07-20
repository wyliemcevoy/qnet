#pragma once
#include "layer.h"

namespace qnet {

	template<int input_count, int output_count>
	class PerceptronLayer : public Layer
	{
	public:
		PerceptronLayer();
		~PerceptronLayer();
		void Update() override;
		void BackPropogate() override;
		void ForwardPass() override;
		std::array<float, input_count> GetNetIn() override;
		std::array<float, output_count> GetNetOut() override;

	private:
		std::array<float, input_count> net_in_;
		std::array<float, output_count> net_out_;
		
		/*** /brief Matrix representing the weights of the edges
		* weights_[i][j] represents node i's j'th imput edge weight. */
		std::array<std::array<float, input_count>, output_count> weights_;

		/*** /brief Matrix representing the calculated deltas to the edge weights
		* Weight can be updated after each back propogation or can be done in batch
		* after a set number of instances have been run.
		* @see Update() 	*/
		std::array<std::array<float, input_count>, output_count> weight_updates_;
	};
}
