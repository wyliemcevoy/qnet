#pragma once
#include "layer.h"

namespace qnet {

	template<int input_count, int output_count>
	class OutputLayer : public Layer
	{
	public:
		OutputLayer();
		~OutputLayer();

		void Update() override;
		void BackPropogate() override;
		void ForwardPass() override;
		std::array<float, input_count> GetNetIn() override;
		std::array<float, output_count> GetNetOut() override;
	};

}