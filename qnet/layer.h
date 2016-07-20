#pragma once

namespace qnet
{

	template<int input_count, int output_count>
	class Layer
	{
	public:
		virtual ~Layer();
		virtual void ForwardPass() = 0;
		virtual void BackPropogate() = 0;
		virtual void Update() = 0;

		virtual std::array<float, input_count> GetNetIn() = 0;
		virtual std::array<float, output_count> GetNetOut() = 0;
	};

	template<int input_count, int output_count>
	Layer::~Layer() {}
}
