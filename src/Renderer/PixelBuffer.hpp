#if !defined(__PixelBuffer_HPP__)
#define __PixelBuffer_HPP__

struct SDL_Surface;

namespace fun {
namespace render {
	class SwapChain;

	class PixelBuffer
	{
		private:
			SDL_Surface* surface;
			PixelBuffer(SDL_Surface* _surface);

		public:		
			friend class SwapChain;

			PixelBuffer(int w, int h);
			PixelBuffer(const PixelBuffer& other);

			void lock();
			void unlock();

			const unsigned int& operator() (int x, int y) const;
			unsigned int& operator() (int x, int y);
			PixelBuffer& operator =(const PixelBuffer& other);

			~PixelBuffer();
	};
}}

#endif