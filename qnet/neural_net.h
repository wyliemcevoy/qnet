#pragma once

#include <vector>
#include "layer.h"

namespace qnet
{
	class NeuralNet
	{
	public:
		NeuralNet();
		~NeuralNet();

	private:
		std::vector<Layer> layers_;
	};
}