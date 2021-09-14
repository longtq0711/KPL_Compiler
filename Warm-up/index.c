#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct line {
	int dong;
	struct line* next;
} line;

typedef struct word {
	char tu[30];
	int solan;
	line *dsdong;
	struct word* next;
} word;

line* initLine(int dong) {
	line *root = malloc(sizeof(line));
	root -> dong = dong;
	root -> next = NULL;
	return root;
}

word* initWord(char *tu, int dong) {
	word *root = malloc(sizeof(word));
	strcpy(root -> tu, tu);
	root -> dsdong = NULL;
	addLine(&root -> dsdong, dong);
	root -> solan = 1;
	root -> next = NULL;
	return root;
}

int searchLine(line *root, int dong) {
	line *current = root;
	while(current != NULL) {
		if(current -> dong == dong) {
			return 0;
		}
		current = current -> next;
	}
	return 1;
}

word* searchWord(word *root, char *tu) {
	word *temp = NULL, *current = root;
	while(current != NULL) {
		if(strcmp(current -> tu, tu) == 0) {
			temp = current;
			break;
		}
		current = current -> next;
	}
	return temp;
}

void addLine(line** root, int dong) {
	if((*root) == NULL) {
		*root = initLine(dong);
	} else {
		line *temp = initLine(dong), *current = *root, *prev = current;
		if(searchLine(*root, dong) == 0)
			return;
		if((*root) -> next == NULL) {
			if((*root) -> dong < dong) {
				(*root) -> next = temp;
			} else if((*root) -> dong > dong){
				temp -> next = *root;
				*root = temp;
			}
			return;
		}
		while(current != NULL) {
			if(current -> dong < dong) {
				prev = current;
				if(current -> next == NULL) {
					prev -> next = temp;
				}
			} else if(current -> dong > dong){
				if(current != (*root)) {
					prev -> next = temp;
					temp -> next = current;
				} else {
					temp -> next = *root;
					*root = temp;
				}
				return;
			}
			current = current -> next;
		}
	}
}

void addWord(word** root, char *tu, int dong) {
	word *search_word;
	if((*root) == NULL) {
		*root = initWord(tu, dong);
	} else {
		word *temp = initWord(tu, dong), *prev, *current = *root;
		if((search_word = searchWord(*root, tu)) != NULL) {
			(search_word -> solan)++;
			addLine(&(search_word -> dsdong), dong);
			return;
		}
		if((*root) -> next == NULL) {
			if(strcmp((*root) -> tu, tu) < 0) {
				(*root) -> next = temp;
			} else if(strcmp((*root) -> tu, tu) > 0){
				temp -> next = *root;
				*root = temp;
			}
			return;
		}
		while(current != NULL) {
			if(strcmp(current -> tu, tu) < 0) {
				prev = current;
				if(current -> next == NULL) {
					prev -> next = temp;
				}
			} else if(strcmp(current -> tu, tu) > 0){
				if(current != (*root)) {
					prev -> next = temp;
					temp -> next = current;
				} else {
				  	temp -> next = *root;
				  	*root = temp;
				}
				return;
			}
			current = current -> next;
		}
	
	}
}

void printWord(word *root) {
	word *current = root;
	while(current != NULL) {
		printf("%-30s", current -> tu);
		printf("%-10d", current -> solan);
		line *add = current -> dsdong;
		while(add != NULL) {
			printf("%d ", add -> dong);
			if(add -> next == NULL) {
			  	printf(" \n");
			}
			add = add -> next;
		}
		current = current -> next;
	}
}

void readFile(word **root, word **stopw, char *tenfile) {
	FILE *fp;
	int c, i = 0, line = 1, flag = 1;
	int check_upper;
	int check_end, check;
	int check_begin = 0;
	if((fp = fopen(tenfile, "r")) == NULL) {
	printf("Khong the mo file\n");
	} else {
		char tu[30];
		while((c = fgetc(fp)) != EOF) {
			if(isalpha(c)) {
				tu[i++] = c;
			} else {
				if(c== '.' || c == '\n' || c == '\r'){
					check_end = 0;
				} else {
					check_end = 1;
				} 
				if(isupper(tu[0])){
					check_upper = 1;
				} else {
					check_upper = 0;
				}
				tu[i] = '\0';
				if(check_upper == 1 && check_begin == 1){
					check = 1;
				} else {
					check = 0;
				}
				if((strlen(tu) >= 1)) {
			  		if(((*stopw) != NULL) && check == 0) {
			  			for(i = 0; i < strlen(tu); i++){
			  				tu[i] = tolower(tu[i]);	
						}
						if(searchWord(*stopw, tu) == NULL) {
							addWord(root, tu, line);
						}
				  	} else if(((*stopw) == NULL) && check == 0){
				    	addWord(root, tu, line);			
				  	}
				  	i = 0;
				}
				check_begin = check_end;
				if(c == '\n')
					line++;
			}
			
		}
		fclose(fp);
	}
}

int main() {
	word *root = NULL;
	word *stopw = NULL;
	word *checkNull = NULL;
	readFile(&stopw, &checkNull, "stopw.txt");
	readFile(&root, &stopw, "vanban.txt");
	printWord(root);
	return 1;
}
