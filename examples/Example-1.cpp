///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2013 Jimmie Bergmann - jimmiebergmann@gmail.com
//
// This software is provided 'as-is', without any express or
// implied warranty. In no event will the authors be held
// liable for any damages arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute
// it freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but
//    is not required.
// 
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any
//    source distribution.
// 
///////////////////////////////////////////////////////////////////////////////////

#include <RSA.hpp>
#include <time.h>
#include <cmath>
#include <iostream>

int main( )
{

	// Test the large integer Sqrt function

	const unsigned int number = 1234567;
	
	LargeInteger a( 2, 0, 0 );
	// Set the a's components
	a.SetComponent( 0, number & 0xFFFF );
	a.SetComponent( 1, (number & 0xFFFF0000) >> 16 );

	//std::cout << a.Sqrt( );

	std::cout << number	<< "   " << (unsigned int)(sqrt( (double)number ) ) << std::endl;
	std::cout << a		<< "   " << a.Sqrt( ) << std::endl;


/*
	// Let's seed the rand function by using the time.
	// Might be useful later on.
	srand( time( NULL ) );


	// Create a 16 bit RSA class
	RSA rsa( 16 / 16 );

	// Randomize keys
	rsa.RandomizeKeys( 0 );

	*/

	// Wait for any input in order to close the program.
	std::cin.get( );
	return 0;
}