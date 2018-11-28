#include "merge.h"
#include <stdlib.h>
#include <string.h>
#include "entry.h"
int merge(entry* sorted1, int length1, entry* sorted2, int length2, entry** out){
    int length = length1 + length2;
    entry* merged = *out = (entry*)malloc(sizeof(entry)*length);
    int index1 = 0;
    int index2 = 0;
    while(index1 < length1 && index2 < length2){
        if(sorted1[index1].Database_Index>sorted2[index2].Database_Index){
            merged[index1+index2] = sorted2[index2];
            index2++;
        }
        else{
            merged[index1+index2] = sorted1[index1];
            index1++;
        }
    }
    while(index1 < length1){
        merged[index1+index2] = sorted1[index1];
        index1++;
    }
    while(index2 < length2){
        merged[index1+index2] = sorted2[index2];
        index2++;
    }
    free(sorted1);
    free(sorted2);
    return length;
}