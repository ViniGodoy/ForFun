/******************************************************************************
*
* COPYRIGHT Vin�cius G. Mendon�a ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vin�cius G.Mendon�a prior authorization.
*
* This file was made available on https://github.com/ViniGodoy/ForFun and it 
* is free to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autoriza��o 
* a priori de Vin�cius G. Mendon�a
*
* Este arquivo foi disponibilizado no site https://github.com/ViniGodoy/ForFun 
* e esta livre para distribui��o seguindo a licen�a Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/

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
			PixelBuffer& backBuffer();
			void swap();
			~SwapChain();
	};
}};

