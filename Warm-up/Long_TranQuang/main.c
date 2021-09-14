#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct dong{
  int line;
  struct dong * next;
} dong;

typedef struct tu {
  char *word;
  int solanxh;
  dong *loop;
  struct tu* next;
} tu;
int empty(dong* root) {
  if(root == NULL) return 1;
  return 0;
}

dong* initNode(int line) {
  dong *root = (dong*)malloc(sizeof(dong));
  root -> line = line;
  root -> next = NULL;
  return root;
}

int search(dong *root, int line) {
  dong *node = NULL, *cur = root;
  if(root == NULL) return 0;
  while(cur->line != line) {
    if(cur-> next == NULL) return 0;
    else cur = cur->next;
    }
  return 1;
  }
void addListInt(dong** root, int line) {
  if((*root)==NULL) {
    *root = initNode(line);
  } else {
    dong *node = initNode(line), *cur = *root;
    if(search(*root, line) == 1)
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
    	if(cur -> line > line){
        if(cur != (*root)) {
          cur -> next = node;
          node -> next = cur;
        } else {
          node -> next = *root;
          *root = node;
        }
        return;
      }
      else if(cur -> line < line) {
        if(cur -> next == NULL) {
          cur -> next = node;
        }
        }
      cur = cur -> next;
    }
  }
}

void printListInt(dong *root) {
  dong *cur = root;
  while(cur != NULL) {
    printf("%d ", cur -> line);
    if(cur -> next == NULL) {
      printf(" \n");
    }
    cur = cur -> next;
  }
}
tu* initTu(char *word, int line) {
  tu *root = (tu*)malloc(sizeof(tu));
  root -> word = (char*)malloc(sizeof(char) * 30);
  strcpy(root -> word, word);
  root -> loop = NULL;
  addListInt(&root -> loop, line);
  root -> solanxh = 1;
  root -> next = NULL;
  return root;
}

tu* wordSearch(tu *root, char *word) {
  tu *cur = root;
  if(root == NULL) return NULL;
  while(strcmp(cur -> word, word) != 0) {
    if(cur->next == NULL) return NULL;
	else cur = cur->next;
    }
  return cur;
}
void addListChar(tu** root, char *word, int line) {
  tu *search;
  if((*root)==NULL) {
    *root = initTu(word, line);
  } else {
    tu *node = initTu(word, line), *prev, *cur = *root;
    if((search = wordSearch(*root, word)) != NULL) {
      (search -> solanxh)++;
      addListInt(&(search -> loop), line);
      return;
    }
    if (strcmp((*root)->word,word)>0){
                node->next = *root;
                *root = node;
            }
            else{
			     while(cur->next != NULL && strcmp(cur->next->word,word) < 0){
                    cur = cur->next;
                }
                node->next = cur->next;
                cur->next = node;
            }
  }
}

void printListChar(tu *node)
 {
tu *cur = node;
  while(cur != NULL) {
    printf("%s %d ", cur-> word, cur-> solanxh);
    printListInt(cur -> loop);
    cur = cur -> next;
  }
}
void readFile(tu **root, tu **check, char *tenfile) { 
  FILE *fp;
  int c, i = 0, line = 1;
  if((fp = fopen(tenfile, "r")) == NULL) {
    printf("Error opening file\n");
  } else {
    char word[MAX];
    while((c = fgetc(fp)) != EOF) {
      if(isalpha(c)) {
     	word[i++] = (char)tolower(c);
      } else {
        word[i] = '\0';
        if(strlen(word) >= 1) {
          if((*check) != NULL) {
            if(wordSearch(*check, word) == NULL) {
              addListChar(root, word, line);
            }
          } else {
            addListChar(root, word, line);
          }
          i = 0;
        }
      }
      if(c == '\n') line++;
    }
    fclose(fp);
  }
}
int main() {
  tu *root = NULL;
  tu *check = NULL; 
  tu *nullNode = NULL;
  readFile(&check, &nullNode, "stopw.txt");
  readFile(&root, &check, "vanban.txt");
  printListChar(root);
//  return 1;
  char str[100];
	int i;
	for(i=0;i<100;i++){
		str[i++] = (char)(0);
	}
	printf("%d", '\0');
}
