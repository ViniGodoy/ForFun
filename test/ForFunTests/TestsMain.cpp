/******************************************************************************
*
* COPYRIGHT Vin�cius G. Mendon�a ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vin�cius G.Mendon�a prior authorization.
*
* This file was made available on http://www.pontov.com.br and it is free 
* to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autoriza��o 
* a priori de Vin�cius G. Mendon�a
*
* Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta 
* livre para distribui��o seguindo a licen�a Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/
#include <iostream>
#include "Vector2Test.hpp"
#include "Vector3Test.hpp"
#include "Vector4Test.hpp"
#include "Matrix3Test.hpp"
#include "Matrix4Test.hpp"

int main(int argc, char* argv[])
{	
	testVector2();
	testVector3();	
	testVector4();
	testMatrix3();
	testMatrix4();
	testAffineTransform();
	std::cout << "All tests passed!" << std::endl;
	system("pause");
}