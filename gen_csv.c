// Function to help generation of CSV files for different workloads
// and different policies
#include "definitions.h"

/*
    void create_csv(char* policy_type, char* type, struct workload* work_load, int cacheSize): 
    Creates CSV files for the given input configuration by invoking the required policy
    Writes the cache_size and the return hit rate from the policy invoked on the input workload
        
*/ 
void create_csv(char* policy_type, char* type, struct workload* work_load, int cacheSize){
    // setting the path name according to the policy type and work load type
    char path[1024] = ""; 
    strcat(path , "./data/");
    strcat(path,type);
    strcat(path,"_");
    strcat(path,policy_type);
    strcat(path,".csv"); 
    // Opening the CSV file for writing data
    FILE * f = fopen(path, "w"); 
    if(f == NULL){
        printf("Could not create the CSV file %s\n", type);
        return ;
    }
    int pages = work_load->pages ;
    int cache_size;
    // Depending on the policy type, enter data by running workload on the policy
    if(policy_type == "FIFO"){
        for(cache_size = 1;cache_size<=cacheSize; cache_size ++ ){
            fprintf(f,"%d,%f\n",cache_size, policy_FIFO(work_load,cache_size)*100);
        }
    }
    else if(policy_type == "LRU"){
        for(cache_size = 1;cache_size<=cacheSize; cache_size ++ ){
            fprintf(f,"%d,%f\n",cache_size, policy_LRU(work_load,cache_size)*100);
        }
    }
    else if(policy_type == "LRUAppr"){
        for(cache_size = 1;cache_size<=cacheSize; cache_size ++ ){
            fprintf(f,"%d,%f\n",cache_size, policy_LRUapprox(work_load,cache_size)*100);
        }
    }
    else if(policy_type == "RANDOM"){
        for(cache_size = 1;cache_size<=cacheSize; cache_size ++ ){
            fprintf(f,"%d,%f\n",cache_size, policy_RANDOM(work_load,cache_size)*100);
        }
    }
    fclose(f); 
}

// Functions for creating all combinations of workload
// and policy
void loop_csv(struct workload* work_load, int cache_size){
    create_csv("FIFO","LOOP",  work_load, cache_size); 
    create_csv("LRU", "LOOP",work_load, cache_size); 
    create_csv("LRUAppr","LOOP", work_load, cache_size); 
    create_csv("RANDOM", "LOOP",work_load, cache_size); 
}

void random_csv(struct workload* work_load, int cache_size){
    create_csv("FIFO","RANDOM", work_load, cache_size); 
    create_csv("LRU", "RANDOM", work_load, cache_size); 
    create_csv("LRUAppr", "RANDOM", work_load, cache_size); 
    create_csv("RANDOM", "RANDOM", work_load, cache_size); 
}

void local_csv(struct workload* work_load, int cache_size){
    create_csv("FIFO","LOCAL", work_load, cache_size); 
    create_csv("LRU","LOCAL", work_load, cache_size); 
    create_csv("LRUAppr", "LOCAL",work_load, cache_size); 
    create_csv("RANDOM", "LOCAL",work_load, cache_size); 
}