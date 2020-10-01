#include "Menu.h"

void Menu(FILE* hardDisk){

  Cache* cacheL1 = NULL;
  Cache* cacheL2 = NULL;
  Cache* cacheL3 = NULL;
  Cache* RAM_memory = NULL;
  do{
    cacheL1=createCache(1);
      if(getSizeCache(cacheL1)<2){
        deleteCache(cacheL1);
        printf("Tamanho inválido\n");
        continue;
      }
      else{
          do{
              cacheL2 = createCache(2);
              if(getSizeCache(cacheL2)<=getSizeCache(cacheL1)){
                  deleteCache(cacheL2);
                  printf("Tamanho inválido\n");
                  continue;
              }
              else{
                  do{
                      cacheL3 = createCache(3);
                      if(getSizeCache(cacheL3)<=getSizeCache(cacheL2)){
                          deleteCache(cacheL3);
                          printf("Tamanho inválido\n");
                          continue;
                      }
                      else{
                          //Criação da memória RAM(TP3)
                          do{
                            RAM_memory = createCache(4);
                            if(getSizeCache(RAM_memory)<=getSizeCache(cacheL3)){
                              deleteCache(RAM_memory);
                              printf("Tamanho invalido\n");
                              continue;
                            }
                          }while(getSizeCache(RAM_memory)<=getSizeCache(cacheL3));
                      }
                  }while(getSizeCache(cacheL3)<=getSizeCache(cacheL2));
              }
          }while(getSizeCache(cacheL2)<=getSizeCache(cacheL1));
      }
    }while(getSizeCache(cacheL1)<1);

    clock_t temp;
    temp=clock();

    int ARITMETIC_size=11;

    int* ARITMETIC_memory=criaAritmetica(ARITMETIC_size);

    int* inst = malloc(sizeof(int));

    int** instructions=starta_instrucoes(inst, getSizeCache(cacheL1));

    int interruption;
    int* hardD = malloc(sizeof(int));
    *hardD=0;

    printf("------------------------------------------------------------------------------------------\n");
    printf("DADOS:\n");
    printf("------------------------------------------------------------------------------------------\n\n");

    interruption=CPU(hardDisk, RAM_memory, cacheL1, cacheL2, cacheL3, ARITMETIC_memory, instructions, hardD);

    temp=clock()-temp;
    double* exec_time=malloc(sizeof(double));
    *exec_time=temp/(CLOCKS_PER_SEC/1000.0);
    printf("\n\n");

    cache_show_statistic(cacheL1, cacheL2, cacheL3, RAM_memory, exec_time, interruption, *inst, *hardD);
    printf("\n\n");

    deleteCache(cacheL3);
    deleteCache(cacheL2);
    deleteCache(cacheL1);
    deleteCache(RAM_memory);
    liberaAritmetica(ARITMETIC_memory);
    free(exec_time);
    free(inst);
}
