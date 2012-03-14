#pragma once

namespace key {

	class RenderItemBase {
	public:
		RenderItemBase() {};
		virtual ~RenderItemBase() {};
		virtual void process() = 0;
	};

}