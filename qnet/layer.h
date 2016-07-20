#pragma once

namespace qnet
{
	class Layer
	{
	public:
		virtual ~Layer();
		virtual void ForwardPass() = 0;
		virtual void BackPropogate() = 0;
	};


	Layer::~Layer() {}
}
