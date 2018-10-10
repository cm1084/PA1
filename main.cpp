#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAXSIZE 1024
int number=0;//This is for counting how may word in the linked list
typedef struct node{
    int count;
    char s[MAXSIZE];
    struct node *next;
}list,*linkP;
typedef struct array_node{
    int count;
    char s[MAXSIZE];
    
}array_node,*arr;


FILE *fp;
linkP L;
linkP deal(char temp[],char line[]);
linkP search(char temp[],linkP L);
void PrintList(linkP L);
linkP sort(linkP L);

void copy(arr array,linkP L);//This funciton copy the sorted word to an array

int main(void){
    L= (linkP)malloc(sizeof(struct node));
    fp = fopen("test.txt","r");
    L->next = NULL;
    char line[MAXSIZE];
    char temp[MAXSIZE];
    memset(temp,0,MAXSIZE);
    while(fgets(line,1024,fp)!=NULL){
        L = deal(temp,line);
    }
    L = sort(L);
    PrintList(L);
    //printf("\n %d",number);
    
    arr array = (arr)malloc(sizeof(array_node)*number);
    copy(array, L);
    
    //This part is for checking whether the linked list has been copy to the string
    for (int i=0; i<number; i++) {
         printf("%s  %d\n",array[i].s,array[i].count);
    }
    
    return 0;
}

void copy(arr array,linkP L)
{
    linkP p;
    int i=0;
    p = L->next;
    while(p){
        strcpy(array[i].s,p->s);
        array[i].count=p->count;
        i++;
        p = p->next;
    }
    
}
linkP deal(char temp[],char line[]){
    int i,k=0;
    char ch;
    for(i=0;i<strlen(line);i++){
        ch = tolower(line[i]);
        if(((ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')||(ch=='('))&&((ch!='.')&&(ch!=',')&&(ch!=';')&&(ch!=':')&&(ch!='!'))){
            temp[k] = ch;
            k++;
        }
        else{
            if(temp[0]==0){
                continue;
            }
            else{
                L = search(temp,L);
                memset(temp,0,MAXSIZE);
                k = 0;
                continue;
            }
        }
    }
    return L;
}

linkP search(char temp[],linkP L){
    linkP p,q;
    int flag = 0;
    p = L;
    while(p){
        if(strcmp(temp,p->s)==0){
            p->count++;
            flag = 1;
            break;
        }
        p = p->next;
    }
    if(flag==0){
        p = L;
        while(p->next){
            p = p->next;
        }
        q = (linkP)malloc(sizeof(list));
        strcpy(q->s,temp);
        q->next = NULL;
        q->count = 1;
        p->next = q;
        p = q;
    }
    return L;
}

void PrintList(linkP L){
    linkP p;
    p = L->next;
    while(p){
        number++;
        
        p = p->next;
    }
}


linkP sort(linkP L){
    linkP p,q;
    char s[MAXSIZE];
    int temp;
    for(p=L;p;p=p->next){
        for(q=p;q;q=q->next){
            if(strcmp(p->s,q->s)>0){
                strcpy(s,p->s);
                strcpy(p->s,q->s);
                strcpy(q->s,s);
                temp = p->count;
                p->count = q->count;
                q->count = temp;
            }
        }
    }
    return L;
}
