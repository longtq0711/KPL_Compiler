#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct nodeInt{
  int line;
  struct nodeInt* next;
} nodeInt;

typedef struct nodeChar {
  char *word;
  int solanlap;
  nodeInt *loop;
  struct nodeChar* next;
} nodeChar;
int empty(nodeInt* root) {
  if(root == NULL) return 1;
  return 0;
}

nodeInt* initNode(int line) {
  nodeInt *root = (nodeInt*)malloc(sizeof(nodeInt));
  root -> line = line;
  root -> next = NULL;
  return root;
}

nodeInt* searchNode(nodeInt *root, int line) {
  nodeInt *node = NULL, *cur = root;
  while(cur != NULL) {
    if(cur-> line == line) {
      node = cur;
      break;
    }
    cur = cur -> next;
  }
  return node;
}
void addListInt(nodeInt** root, int line) {
  if((*root)==NULL) {
    *root = initNode(line);
  } else {
    nodeInt *node = initNode(line), *prev, *cur = *root;
    if(searchNode(*root, line) != NULL)
      return;
    if((*root) -> next == NULL) {
      if((*root) -> line < line) {
        (*root) -> next = node;
      } else if((*root) -> line > line){
        node -> next = *root;
        *root = node;
      }
      return;
    }
    while(cur != NULL) {
      if(cur -> line < line) {
//        prev = cur;
        if(cur -> next == NULL) {
          cur -> next = node;
        }
      } else if(cur -> line > line){
        if(cur != (*root)) {
          cur -> next = node;
          node -> next = cur;
        } else {
          node -> next = *root;
          *root = node;
        }
        return;
      }
      cur = cur -> next;
    }
  }
}

void printListInt(nodeInt *root) {
  nodeInt *cur = root;
  while(cur != NULL) {
    printf("%d ", cur -> line);
    if(cur -> next == NULL) {
      printf(" \n");
    }
    cur = cur -> next;
  }
}


nodeChar* initNodeChar(char *word, int sodong) {
  nodeChar *root = (nodeChar*)malloc(sizeof(nodeChar));
  root -> word = (char*)malloc(sizeof(char) * 30);
  strcpy(root -> word, word);
  root -> loop = NULL;
  addListInt(&root -> loop, sodong);
  root -> solanlap = 1;
  root -> next = NULL;
  return root;
}

nodeChar* searchNodeChar(nodeChar *root, char *word) {
  nodeChar *node = NULL, *cur = root;
  while(cur != NULL) {
    if(strcmp(cur -> word, word) == 0) {
      node = cur;
      break;
    }
    cur = cur -> next;
  }
  return node;
}
void addListChar(nodeChar** root, char *word, int sodong) {
  nodeChar *searchNode;
  if((*root)==NULL) {
    *root = initNodeChar(word, sodong);
  } else {

    nodeChar *node = initNodeChar(word, sodong), *prev, *cur = *root;
    if((searchNode = searchNodeChar(*root, word)) != NULL) {
      (searchNode -> solanlap)++;
      addListInt(&(searchNode -> loop), sodong);
      return;
    }
    if (strcmp((*root)->word,word)>0){
                node->next = *root;
                *root = node;
                
            }
            else{
			     while(cur->next != NULL && strcmp(cur->next->word,word)<0){
                    cur = cur->next;
                }
                node->next = cur->next;
                cur->next = node;
            }
//    if((*root) -> next == NULL) {
//      if(strcmp((*root) -> word, word) < 0) {
//        (*root) -> next = node;
//      } else if(strcmp((*root) -> word, word) > 0){
//        node -> next = *root;
//        *root = node;
//      }
//      return;
//    }
//    while(cur != NULL) {
//      if(strcmp(cur -> word, word) < 0) {
//        prev = cur;
//        if(cur -> next == NULL) {
//          prev -> next = node;
//        }
//      } else if(strcmp(cur -> word, word) > 0){
//        if(cur != (*root)) {
//          prev -> next = node;
//          node -> next = cur;
//        } else {
//          node -> next = *root;
//          *root = node;
//        }
//        return;
//      }
//      cur = cur -> next;
//    }

  }
}

void printListChar(nodeChar *root) {
  nodeChar *cur = root;
  
  while(cur != NULL) {
    printf("%-30s | ", cur -> word);
    printf("%-10d | ", cur -> solanlap);
    printListInt(cur -> loop);
    cur = cur -> next;
  }
}
void readFile(nodeChar **root, nodeChar **check, char *tenfile, char *config) { 
  FILE *file;
  int c, i = 0, line = 1;
  if((file = fopen(tenfile, config)) == NULL) {
    printf("Khong the mo file\n");
  } else {
    char* word = (char*)malloc(sizeof(char) * 30);
    while((c = fgetc(file)) != EOF) {
      if(isalpha(c)) {
     	word[i++] = (char)tolower(c);
      } else {
        word[i] = NULL;
//        printf("%s",word);
        if(strlen(word) >= 1) {
          if((*check) != NULL) {
            if(searchNodeChar(*check, word) == NULL) {
              addListChar(root, word, line);
              printf("%s ", word);
              printf("%d ",line);
            }
          } else {
            addListChar(root, word, line);
          }
          i = 0;
        }
      }
      if(c == '\n')
        line++;
    }
    free(word);
    fclose(file);
  }
}
int main() {
  nodeChar *root = NULL; //node vanban.txt
  nodeChar *check = NULL; //node stop.txt
  nodeChar *nullNode = NULL;
  readFile(&check, &nullNode, "stop.txt", "r");
 
  readFile(&root, &check, "vanban.txt", "r");
  printListChar(root);
  return 1;
}
