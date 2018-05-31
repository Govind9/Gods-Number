/*
 * This is Program which tells the moves 
 * to solve cube in least possible moves
 *
 * author -:
 * Amarjeet Singh Kapoor
 */


#include<iostream>
#include"PocketCube.h"

using namespace std;

int main(){
        CubeState cube, cube2, cube1; //make cube
		string  s1 = "URU2RU2R2FRiFiRF2UF2RiFiUR", s2 = "URU2RU2R2FRiFiRF2UF2RiFiUL";
		
		scramble(cube1);
		scramble(cube2);
		int code1 = code_generator(cube1);
		int code2 = code_generator(cube2);
		cube1.printMe();
		cout << code1<< endl << endl;
		cube2.printMe();
		cout << code2 << endl;

		//test_scope(cube);
}
