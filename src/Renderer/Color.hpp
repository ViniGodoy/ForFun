/******************************************************************************
*
* COPYRIGHT Vinícius G. Mendonça ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vinícius G.Mendonça prior authorization.
*
* This file was made available on https://github.com/ViniGodoy/ForFun and it 
* is free to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autorização 
* a priori de Vinícius G. Mendonça
*
* Este arquivo foi disponibilizado no site https://github.com/ViniGodoy/ForFun 
* e esta livre para distribuição seguindo a licença Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/

#if !defined(__COLOR_HPP__)
#define __COLOR_HPP__

#include "../Math/Vector4.hpp"

namespace fun {
namespace render {
	static const math::Vector4 BLACK(0,0,0);
	static const math::Vector4 BLUE(0,0,1);
	static const math::Vector4 GREEN(0,1,0);
	static const math::Vector4 CYAN(0,1,1);
	static const math::Vector4 RED(1,0,0);
	static const math::Vector4 MAGENTA(1,0,1);
	static const math::Vector4 YELLOW(1,1,0);
	static const math::Vector4 WHITE(1,1,1);

	static const math::Vector4 PURE_COLORS[8] = {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE};
}
}
#endif