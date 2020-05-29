#include <stdio.h>
#include "calc.h"
#include <string.h>

#define N 8192

const int Na = 2048;

int repeats = 10;

struct vector vec[N];
struct vector vec2[N];
struct vector resultSum[N];
struct vector resultSub[N];
struct vector resultMul[N];
struct vector resultDiv[N];

struct times tSIMD;
struct times tSISD;

void fillVectorArray(){
    for(int i=0;i<N;i++){
        vec[i] = createVector();
        vec2[i] = createVector();
    }
}

void saveToFile(char type[], struct times t){
    FILE *file;
    char fileName[15];
    char fileExt[10] = {".txt"};
    strcat(fileName,type);
    strcat(fileName, fileExt);

    file = fopen(fileName,"w");
    fprintf(file,"Typ obliczen: %s\n Liczba liczb: %d \nSredni czas: \n+ %f \n- %f \n* %f \n/ %f \n",
            type,N,t.sumTime,t.subTime,t.mulTime,t.divTime );
}

void testSIMD(){
    double startTime;
    for(int i=0; i<repeats;i++){
        startTime = clock();
        for(int j=0;j<N;j++){
            sumSIMD(vec[j],vec2[j],&resultSum[j]);
        }
        tSIMD.sumTime +=((double) clock() - startTime);

        startTime = clock();
        for(int j=0;j<N;j++){
            subSIMD(vec[j],vec2[j],&resultSub[j]);
        }
        tSIMD.subTime +=((double) clock() - startTime);

        startTime = clock();
        for(int j=0;j<N;j++){
            mulSIMD(vec[j],vec2[j],&resultMul[j]);
        }
        tSIMD.mulTime +=((double) clock() - startTime);

        startTime = clock();
        for(int j=0;j<N;j++){
            divSIMD(vec[j],vec2[j],&resultDiv[j]);
        }
        tSIMD.divTime +=((double) clock() - startTime);

        tSIMD.sumTime = tSIMD.sumTime/repeats/N;
        tSIMD.subTime = tSIMD.subTime/repeats/N;
        tSIMD.mulTime = tSIMD.mulTime/repeats/N;
        tSIMD.divTime = tSIMD.divTime/repeats/N;

    }
    saveToFile("SIMD8192", tSIMD);
}


void testSISD(){
    double startTime;
    for(int i=0; i<repeats;i++){
        startTime = clock();
        for(int j=0;j<N;j++){
            sumSISD(vec[j],vec2[j],&resultSum);
            //printf("%u", j);
        }
        tSISD.sumTime +=((double) clock() - startTime);

        startTime = clock();
        for(int j=0;j<N;j++){
            subSISD(vec[j],vec2[j],&resultSub);
        }
        tSISD.subTime +=((double) clock() - startTime);

        startTime = clock();
        for(int j=0;j<N;j++){
            mulSISD(vec[j],vec2[j],&resultMul);
        }
        tSISD.mulTime +=((double) clock() - startTime);

        startTime = clock();
        for(int j=0;j<N;j++){
            divSISD(vec[j],vec2[j],&resultDiv);
        }
        tSISD.divTime +=((double) clock() - startTime);

        tSISD.sumTime = tSISD.sumTime/repeats/N;
        tSISD.subTime = tSISD.subTime/repeats/N;
        tSISD.mulTime = tSISD.mulTime/repeats/N;
        tSISD.divTime = tSISD.divTime/repeats/N;

    }
    saveToFile("SISD8192",tSISD);
}

int main() {
    fillVectorArray();
    testSIMD();
    //testSISD();
    return 0;
}
