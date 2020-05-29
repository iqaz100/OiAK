//
// Created by piotr on 26.05.2020.
//

#include "calc.h"

void testMet(){

}

void sumSIMD(struct vector a, struct vector b, struct vector *result) {
    asm(
    "movaps %1,%%xmm0;"
    "movaps %2,%%xmm1;"
    "addps %%xmm1, %%xmm0;"
    "movaps %%xmm0,%0;"
    :"=m" (*result)
    :"m" (a), "m" (b));
    //printf("%.6f", result);
}

void subSIMD(struct vector a, struct vector b, struct vector *result) {
    asm(
    "movaps %1,%%xmm0;"
    "movaps %2,%%xmm1;"
    "subps %%xmm1, %%xmm0;"
    "movaps %%xmm0,%0;"
    :"=m" (*result)
    :"m" (a), "m" (b));
}

void mulSIMD(struct vector a, struct vector b, struct vector *result) {
    asm(
    "movaps %1,%%xmm0;"
    "movaps %2,%%xmm1;"
    "mulps %%xmm1, %%xmm0;"
    "movaps %%xmm0,%0;"
    :"=m" (*result)
    :"m" (a), "m" (b));
}

void divSIMD(struct vector a, struct vector b, struct vector *result) {
    asm(
    "movaps %1,%%xmm0;"
    "movaps %2,%%xmm1;"
    "divps %%xmm1, %%xmm0;"
    "movaps %%xmm0,%0;"
    :"=m" (*result)
    :"m" (a), "m" (b));
}

void sumSISD(struct vector a, struct vector b, struct vector *result){
    asm(
    "fld %4;"
    "fadd %8;"
    "fstp %0;"
    "fld %5;"
    "fadd %9;"
    "fstp %1;"
    "fld %6;"
    "fadd %10;"
    "fstp %2;"
    "fld %7;"
    "fadd %11;"
    "fstp %3;"
    :"=m" (result->a),
    "=m" (result->b),
    "=m" (result->c),
    "=m" (result->d)
    :"m"(a.a),"m"(a.b),"m"(a.c),"m"(a.d),
    "m"(b.a),"m"(b.b),"m"(b.c),"m"(b.d));
}

void subSISD(struct vector a, struct vector b, struct vector *result){
    asm(
    "fld %4;"
    "fsub %8;"
    "fstp %0;"
    "fld %5;"
    "fsub %9;"
    "fstp %1;"
    "fld %6;"
    "fsub %10;"
    "fstp %2;"
    "fld %7;"
    "fsub %11;"
    "fstp %3;"
    :"=m" (result->a),
    "=m" (result->b),
    "=m" (result->c),
    "=m" (result->d)
    :"m"(a.a),"m"(a.b),"m"(a.c),"m"(a.d),
    "m"(b.a),"m"(b.b),"m"(b.c),"m"(b.d));
}
void mulSISD(struct vector a, struct vector b, struct vector *result){
    asm(
    "fld %4;"
    "fmul %8;"
    "fstp %0;"
    "fld %5;"
    "fmul %9;"
    "fstp %1;"
    "fld %6;"
    "fmul %10;"
    "fstp %2;"
    "fld %7;"
    "fmul %11;"
    "fstp %3;"
    :"=m" (result->a),
    "=m" (result->b),
    "=m" (result->c),
    "=m" (result->d)
    :"m"(a.a),"m"(a.b),"m"(a.c),"m"(a.d),
    "m"(b.a),"m"(b.b),"m"(b.c),"m"(b.d));
}

void divSISD(struct vector a, struct vector b, struct vector *result){
    asm(
    "fld %4;"
    "fdiv %8;"
    "fstp %0;"
    "fld %5;"
    "fdiv %9;"
    "fstp %1;"
    "fld %6;"
    "fdiv %10;"
    "fstp %2;"
    "fld %7;"
    "fdiv %11;"
    "fstp %3;"
    :"=m" (result->a),
    "=m" (result->b),
    "=m" (result->c),
    "=m" (result->d)
    :"m"(a.a),"m"(a.b),"m"(a.c),"m"(a.d),
    "m"(b.a),"m"(b.b),"m"(b.c),"m"(b.d));
}

