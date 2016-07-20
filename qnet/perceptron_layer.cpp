#include "perceptron_layer.h"

namespace qnet {

	template<int input_count, int output_count>
	PerceptronLayer::PerceptronLayer()
	{

	}

	template<int input_count, int output_count>
	PerceptronLayer::~PerceptronLayer()
	{

	}

	template<int input_count, int output_count>
	void PerceptronLayer<input_count, output_count>::Update()
	{

	}

	template<int input_count, int output_count>
	void PerceptronLayer<input_count, output_count>::BackPropogate()
	{
	}

	template<int input_count, int output_count>
	void PerceptronLayer<input_count, output_count>::ForwardPass()
	{
		// itterate over previous layers output
	}

	template<int input_count, int output_count>
	std::array<float, input_count> PerceptronLayer<input_count, output_count>::GetNetIn()
	{
		return net_in_;
	}

	template<int input_count, int output_count>
	std::array<float, output_count> PerceptronLayer<input_count, output_count>::GetNetOut()
	{
		return net_out_;
	}

}