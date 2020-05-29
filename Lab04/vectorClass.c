//
// Created by piotr on 26.05.2020.
//

#include "vectorClass.h"

float generateNumber(){
    float x = (float)rand()/(float)(RAND_MAX);
    return x;
}

vector createUserVector(float a, float b, float c, float d){
    vector vec;
    vec.a = a;
    vec.b = b;
    vec.c = c;
    vec.d = d;
    return vec;
}

void printVector(vector vec){
    printf("%.6f", vec.a);
    printf("%.6f", vec.b);
    printf("%.6f", vec.c);
    printf("%.6f", vec.d);
}

vector createVector(){
    vector vec;
    vec.a = generateNumber();
    vec.b = generateNumber();
    vec.c = generateNumber();
    vec.d = generateNumber();
    return vec;
}