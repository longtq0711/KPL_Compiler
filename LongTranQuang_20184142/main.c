/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reader.h"
#include "parser.h"
#include "codegen.h"


int dumpCode = 1;

void printUsage(void) {
  printf("Usage: kplc input [-dump]\n");
  printf("   input: input kpl program\n");
  printf("   -dump: code dump\n");
}

int analyseParam(char* param) {
  if (strcmp(param, "-dump") == 0) {
    dumpCode = 1;
    return 1;
  } 
  return 0;
}


/******************************************************************/

int main(int argc, char *argv[]) {
  int i; 
  char outFile[20]={}; 

  if (argc <= 1) {
    printf("kplc: no input file.\n");
    printUsage();
    return -1;
  }

  for ( i = 2; i < argc; i ++) 
    analyseParam(argv[i]);

  initCodeBuffer();

  if (compile(argv[1]) == IO_ERROR) {
    printf("Can\'t read input file!\n");
    return -1;
  }

  strncpy(outFile, argv[1], strchr(argv[1],'.') - argv[1]);
  if (serialize(strcat(outFile,".out")) == IO_ERROR) {
    printf("Can\'t write output file!\n");
    return -1;
  }

  if (dumpCode) printCodeBuffer();
    
  cleanCodeBuffer();

  return 0;
}
