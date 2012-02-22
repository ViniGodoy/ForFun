#pragma once
#include "PixelBuffer.hpp"

namespace fun {
namespace render {
	class SwapChain
	{
		private:
			PixelBuffer* buffer;
			SwapChain(const SwapChain& other);
			SwapChain& operator=(const SwapChain& other);

		public:
			SwapChain(int w, int h, bool fullscreen=true);
			PixelBuffer& getBuffer();
			void swap();
			~SwapChain();
	};
}};

