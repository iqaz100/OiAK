//
// Created by piotr on 26.05.2020.
//

#ifndef LAB4_CALC_H
#define LAB4_CALC_H
#include "vectorClass.h"

void sumSIMD(struct vector a, struct vector b, struct vector *result);
void subSIMD(struct vector a, struct vector b, struct vector *result);
void mulSIMD(struct vector a, struct vector b, struct vector *result);
void divSIMD(struct vector a, struct vector b, struct vector *result);

void sumSISD(struct vector a, struct vector b, struct vector *result);
void subSISD(struct vector a, struct vector b, struct vector *result);
void mulSISD(struct vector a, struct vector b, struct vector *result);
void divSISD(struct vector a, struct vector b, struct vector *result);

#endif //LAB4_CALC_H
