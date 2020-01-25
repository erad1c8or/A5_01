#pragma once																//guards per C++11???

/*dependencies*/
//#include <iostream>															//includes the C++ library named iostream

#include "!globals.hpp"
//#include "+App.hpp"

//#include "02_gamecode_01.hpp"
//#include "+Sprite.hpp"


//Before trying to learn how to use global pointers, this was kind of working...
//See inside of 02_gamecode_01.hpp/02_gamecode01.cpp for actual implementation

//extern Sprite invaderglob;												//Fwd Declaration

//The only problem with this is that the compiler creates invaderglob first and before main()...
//And when the app is closed, it is destroyed last, and the destructor fails because...
//It only gets called, after the Allegro systems have been unloaded, but the constructor needs these:(


//std::vector<Sprite> invader_glob_vector;													//now defining in main()



int main();




void arraytest2(std::vector <int> input_vect);
