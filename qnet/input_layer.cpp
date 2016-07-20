#include "input_layer.h"


namespace qnet {
	template<int input_count, int output_count>
	InputLayer::InputLayer()
	{
	}

	template<int input_count, int output_count>
	InputLayer::~InputLayer()
	{
	}

	template<int input_count, int output_count>
	void InputLayer<input_count, output_count>::Update()
	{
	}

	template<int input_count, int output_count>
	void InputLayer<input_count, output_count>::BackPropogate()
	{
	}

	template<int input_count, int output_count>
	void InputLayer<input_count, output_count>::ForwardPass()
	{
	}

	template<int input_count, int output_count>
	std::array<float, input_count> InputLayer<input_count, output_count>::GetNetIn()
	{
		return std::array<float, input_count>();
	}

	template<int input_count, int output_count>
	std::array<float, output_count> InputLayer<input_count, output_count>::GetNetOut()
	{

		return std::array<float, output_count>();
	}
}