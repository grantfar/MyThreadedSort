#include "merge.h"
#include "dataReader.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "entry.h"
#include <dirent.h>
#include "lineQueue.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mergeQueue.h"
/**
 * Struct to pass at creation of thread;
 **/
typedef struct readParam{
    char* path;
    int length;
    entry** out;
} readParam;

/**
 * Function called at creating of thread
 **/
void *ThreadHandeler(void*p){
    readParam* params = (readParam*)p;
    params->out = malloc(sizeof(entry*));
    params->length = readInFile(params->path,params->out);
}

int main(int argc, char const *argv[])
{
    DIR *d;
    struct dirent *fi;
    char* baseDir;
    int dirLen = strlen(argv[1]);
    const long PathMax = pathconf("/",_PC_PATH_MAX);
    char *CWD = malloc(PathMax+1);
    
    getcwd(CWD,PathMax+1);
    if(argv[1][0] == '/'){
        baseDir = malloc(dirLen+1);
        strcpy(baseDir,argv[1]);
    }
    else{
        dirLen = strlen(CWD)+dirLen+1;
        baseDir = malloc(dirLen+1);
        strcpy(baseDir,CWD);
        strcat(baseDir,"/");
        strcat(baseDir,argv[1]);
    }
    if(baseDir[dirLen-1]=='/'){
        baseDir[dirLen-1]='\0';
        dirLen--;
    }
    d = opendir(baseDir);
    queue *files = malloc(sizeof(queue));
    initQueue(files);
    
    while((fi = readdir(d)) != NULL){
        enqueue(files,fi->d_name);
    }
    

    char* fileName;
    char* AbsFile;
    queue* normFiles = malloc(sizeof(queue));
    struct stat fileStat;
    initQueue(normFiles);
    while(files->length>0){
        fileName = dequeue(files);
        AbsFile = malloc(dirLen + strlen(fileName)+2);
        strcpy(AbsFile,baseDir);
        strcat(AbsFile,"/");
        strcat(AbsFile,fileName);
        lstat(AbsFile,&fileStat);
        if(S_ISREG(fileStat.st_mode)){
            enqueue(normFiles,AbsFile);
        }
    }

    closeQueue(files);
    int length = normFiles->length;

    pthread_t* threads = malloc(length*sizeof(pthread_t));
    readParam* params = malloc(sizeof(readParam)*length);

    

    

    for(int i=0; i < length;i++){
        AbsFile = dequeue(normFiles);
        params[i].path= AbsFile;
    }
    
    for(int i=0; i < length;i++){
        pthread_create(threads+i, NULL, ThreadHandeler, (void*)(params+i));
    }

    for(int i=0; i < length;i++){
        pthread_join(threads[i],NULL);
    }
    free(threads);
    
    mergeQueue mergesLeft;
    mInitQueue(&mergesLeft);
    entryArray* hold;
    for(int i=0; i<length;i++){
        hold= malloc(sizeof(entryArray));
        hold->data = *(params[i].out);
        hold->length = params[i].length;
        mEnqueue(&mergesLeft,hold);
        free(params[i].out);
    }
    free(params);

    entryArray *merge1, *merge2;
    entry **mergedOut = malloc(sizeof(entry*));
    
    /**
     * Loop merges sorted arrays
     **/
    while(mergesLeft.length > 1){
        merge1 = mDequeue(&mergesLeft);
        merge2 = mDequeue(&mergesLeft);
        hold = malloc(sizeof(entryArray));
        hold->length = merge(merge1->data,merge1->length,merge2->data,merge2->length,mergedOut);
        hold->data = *mergedOut;
        free(merge1);
        free(merge2);
        mEnqueue(&mergesLeft,hold);
    }
    entryArray *sorted =  mDequeue(&mergesLeft);
    FILE* yay = fopen("sorted.yay","w");
    
    for(size_t i = 0; i < sorted->length; i++)
    {
        entry temp = sorted->data[i];
        fprintf(yay,"%s,%s,%s,%s,%i\n",temp.Username,temp.Password,temp.Blood_Type,temp.Domain_Name,temp.Database_Index);
    }
    
    fclose(yay);
}
