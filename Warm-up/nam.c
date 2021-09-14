#include<stdio.h>
// #include"llist.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 100
typedef struct _LIST_ELEM LIST_ELEM, *LLIST;
typedef struct _LIST_LINE LIST_LINE, *LISTL;
typedef struct _LIST_SW LIST_SW, *LISTSW;
struct _LIST_LINE{
    int line;
    LIST_LINE *next;
};
struct _LIST_ELEM {
	char data[MAX];
    int count;
    LIST_LINE *lline;
	LIST_ELEM *next;
};
struct _LIST_SW{
    char word[MAX];
    LIST_SW *next;
};
void InsertSW(LISTSW* lsw, char data[MAX]) {
    LIST_SW* e = (LIST_SW*)malloc(sizeof(LIST_SW));
	strcpy(e->word,data);
	e->next = *lsw;
	*lsw = (LISTSW)e;
}
void readFileStopWord(LISTSW* lsw, char *filename){
    int num;
    FILE *file;
    char buff[MAX];
    if((file = fopen(filename,"r"))==NULL){
        printf("Can not open file.\n");
    } else{
    while (fscanf(file, "%s", buff) != EOF) {
        InsertSW(lsw,buff); 
        }
    }
}
int searchStopWord(LISTSW *lsw, char *word){
    LIST_SW* tmp;
    tmp = *lsw;
    while(tmp != NULL){
        if(strcmp(word,tmp->word)==0){
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}
LIST_LINE *InitLineList(int line){
    LIST_LINE *root = malloc(sizeof(LIST_LINE));
    root->line = line;
    // root->next = NULL;
    return root;
};
LIST_LINE* searchLineList(LIST_LINE *list,int line) {
    LIST_LINE *node = NULL;
    LIST_LINE *tmp = list;
    while(tmp != NULL) {
        if(tmp->line == line){
        node = tmp;
        break;
        }
        tmp = tmp->next;
    }
    return node;
}
void InsertLineList(LISTL *ll, int line){
    LIST_LINE *new_node = InitLineList(line);
    if(*ll == NULL || (*ll)->line > line){
        // printf("lline :%d",(*ll)->line);
        new_node->next = *ll;
        *ll = new_node;
    } else {
        LIST_LINE *cur = *ll;
        while(cur->next != NULL && cur->next->line < line){
            cur = cur->next;
        }
        new_node->next = cur->next;
        cur->next = new_node;
    }
   
}
LIST_ELEM *searchList(LIST_ELEM *list, char *word){
    LIST_ELEM *node = NULL;
    LIST_ELEM *tmp = list;
    while(tmp != NULL) {
        if(strcmp(tmp->data,word)==0){
        node = tmp;
        break;
        }
        tmp = tmp->next;
    }
    return node;
}
LIST_ELEM *InitList(char *word,int line){
    LIST_ELEM *root = malloc(sizeof(LIST_ELEM));
    strcpy(root->data,word);
    InsertLineList(&(root->lline),line);
    root->count = 1;
    root->next = NULL;
    return root;
};
void TraverseLine(LIST_LINE *l){
    LIST_LINE *p = l;
    while(p != NULL){
        printf(" %d",p->line);
        p = p->next;
    }
}
void TraverseLink(LLIST* l){
    LIST_ELEM* p;
    p = *l;
    while(p != NULL){
        printf("%s %d",p->data,p->count);
        LIST_LINE *tmp;
        tmp = p->lline;
        TraverseLine(tmp);
        printf("\n");
        p = p->next;
    }
	
}
void InsertList(LLIST *l, char *word, int line){

        LIST_ELEM *result;
        if((result = searchList(*l,word))!=NULL){
            result->count++;
            LIST_LINE *check = searchLineList(result->lline,line);
            if (check == NULL){
            InsertLineList(&(result->lline),line);
            }
        }else {
            // printf("line:%d",line);
            LIST_ELEM *new_node = InitList(word,line);
            // printf("test: %d\n",new_node->lline->line);
            if(*l == NULL){
               *l = new_node;
            } else if (strcmp((*l)->data,word)>0){
                new_node->next = *l;
                *l = new_node;
            }
            else{
                LIST_ELEM *cur = *l;
                while(cur->next != NULL && strcmp(cur->next->data,word)<0){
                    cur = cur->next;
                }
                new_node->next = cur->next;
                cur->next = new_node;
        
            }
    }
}
void readFile(LLIST* l,LISTSW *lsw, LISTL *ll,char *filename){
    FILE *file;
    int c;
    int flag_1;
    int flag_2;
    int flag_3 = 1;
    int flag_4;
    int i = 0, line = 1;
      int j;
    if((file = fopen(filename,"r"))==NULL){
        printf("Can not open file.\n");
    } else{
            char word[MAX];
            while((c = fgetc(file)) != EOF) {
                if(!isalpha(c)){
                        if(c == '.' || c == '\n'){
                            flag_1 = 1;
                        } else flag_1 = 0;
                        if(isupper(word[0])){
                            flag_2 = 1;
                        } else flag_2 = 0;
                        if(flag_2 == 1 && flag_3 == 0){
                            flag_4 = 1;
                            // printf("danh tu rieng: %s\n",word);
                        } else flag_4 = 0;
                        word[i] = '\0';
                        if(flag_4 == 0 && searchStopWord(lsw,word)!=0 && strlen(word)>1 ){
                          
							for( j=0; j<strlen(word); j++){
                                word[j] = tolower(word[j]);
                            }
                            // printf("line: %d \n",line);
                            InsertList(l,word,line);
                        } 
                        if(c == '\n'){
                            line++;
                        }
                         flag_3 = flag_1;
                        i = 0;
                        // }
                
            }
             else {
                    word[i] = c;
                    i++;
                }
        }
    }
}

int main(int argc, char* argv[]) {
    LISTSW lsw = NULL;
    LLIST l = NULL;
    LISTL ll = NULL;
    readFileStopWord(&lsw,"stop.txt");
    readFile(&l,&lsw,&ll,"vanban.txt");
    TraverseLink(&l);
    return 1;
}

