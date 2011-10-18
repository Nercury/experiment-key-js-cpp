#pragma once

namespace key
{
	class DrawList;

	class DrawLoop
	{
	private:

	public:
		DrawLoop();
		virtual ~DrawLoop();

		virtual void rebuild(DrawList * drawList) = 0;
		virtual void run() = 0;
	};

}