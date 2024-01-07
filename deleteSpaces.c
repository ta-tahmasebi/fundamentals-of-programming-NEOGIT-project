#include <stdio.h>
#include <stdlib.h>


int ___findLen (char* str){
    int i = 0;
    while(*(str + i) != ' ' && *(str + i) != '\t' && *(str + i) != '\0')
        i++;
    return i;
}

char* ___find (char* str, int* p){
    if(*(str + *p) == '\0')
        return NULL;
    while(*(str + *p) == ' ' || *(str + *p) == '\t')
        (*p) ++;
    return (str + *p);
}

void ___print(char* str, int len, char** final){
    if (!len) return;
    int index = 0;
    while(*(final + index))
        index++;
    char* a = (char*)calloc(300, sizeof(char));
    for(int i = 0; i < len; i++)
        a[i] = *(str + i);
    a[len] = '\0';
    *(final + index) = a;
}

char** delete_spaces (char* string){
    char ** finaladdress = (char**)calloc(300,sizeof(char*));
    int p = 0;
    while(1){
        char* address = ___find(string, &p);
        if(!address) break;
        int len = ___findLen(address);
        p+= len;
        ___print(address, len, finaladdress);
    }
    /*
    int index = 0;
    while(*(finaladdress + index)){
        printf("%s ", *(finaladdress + index));
        index++;
    }
    */
    return finaladdress;
}
int main(){
    
}