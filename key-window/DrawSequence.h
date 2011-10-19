#pragma once

#include <bullet/LinearMath/btMatrix3x3.h>

namespace key
{
	class DrawTree;

	class DrawSequence
	{
	private:

	public:
		DrawSequence();
		virtual ~DrawSequence();

		virtual void rebuild(DrawTree * drawTree) = 0;
		virtual void run() = 0;
	};

}