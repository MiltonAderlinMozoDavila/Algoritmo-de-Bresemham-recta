#include <iostream>
using namespace std;

void NormalizarVector(float * vector, int Tamaño, float factor){
    for (int  i = 0; i < Tamaño; i++)
    {
        vector[i] = vector[i] / factor;
        
    }
    
}