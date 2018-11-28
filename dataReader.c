#include "dataReader.h"
#include "entry.h"
#include "lineQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int compare(const void* a, const void* b){
    entry *A = (entry*) a;
    entry *B = (entry*) b;
    return (A->Database_Index-B->Database_Index);
}

entry *CreateEntry(char* lineTo){
    entry* retEnt = (entry*)malloc(sizeof(entry));
    int index = 0;
    int start = 0;
    int on = 0;
    char* tmp;
    while(on < 5){
        while(lineTo[index]!=',' && lineTo[index]!='\n' && lineTo[index]!='\0')
            index++;
        tmp = malloc(index-start+1);
        for(int i=start; i<index; i++){
            tmp[i-start] = lineTo[i];
        }
        tmp[index-start]='\0';
        start = ++index;        
        if(on == 0){
            retEnt->Username = tmp;
        }
        if(on == 1){
            retEnt->Password = tmp;
        }
        if(on == 2){
            retEnt->Blood_Type = tmp;
        }
        if(on == 3){
            retEnt->Domain_Name = tmp;
        }
        if(on == 4){
            retEnt->Database_Index = atoi(tmp);
            free(tmp);
            tmp = NULL;
        }
        on++;
    }
    return retEnt;
}
/**
 * reads in file from pathToFile and puts it into an sorted array of entryStuct
 **/
int readInFile(char* pathToFile ,entry** enteries){
    entry* sortedEntries;
    queue* lineQueue = (queue*)malloc(sizeof(queue));
    FILE* smallFile = fopen(pathToFile,"r+");
    initQueue(lineQueue);
    char line[1024];
    int length;
    while(fgets(line,1024,smallFile)!=NULL){
        char* tmp = malloc(strlen(line)+1);
        strcpy(tmp,line);
        enqueue(lineQueue,tmp);
    }
    fclose(smallFile);
    length = lineQueue->length;
    
    sortedEntries = (entry*)malloc(sizeof(entry)*length);
    
    entry* tmp;
    
    for(size_t i = 0; i < length; i++)
    {
        tmp = CreateEntry(dequeue(lineQueue));
        sortedEntries[i] = *tmp;
        free(tmp);
    }
    
    closeQueue(lineQueue);
    qsort(sortedEntries,length,sizeof(entry),compare);

    *enteries = sortedEntries;
    return length;
}