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

    int loop=1;
    while(loop!=0){
        CubeState cube; //make cube
        if(scramble(cube)!=-1) //check if cube is scrambled
            cube_solving(cube); //solve the cube
        cout<<"enter 0 to exit";
    }
}
