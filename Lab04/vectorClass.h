//
// Created by piotr on 26.05.2020.
//

#ifndef LAB4_VECTORCLASS_H
#define LAB4_VECTORCLASS_H
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//const int  N = 2000;

typedef struct vector{
    float a;
    float b;
    float c;
    float d;
}vector;

struct times{
    double sumTime;
    double subTime;
    double mulTime;
    double divTime;
};

float generateNumber();

vector createUserVector(float a,float b, float c,float d );

void printVector(vector vec);

vector createVector();
#endif //LAB4_VECTORCLASS_H
