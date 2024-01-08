#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>


//   *(IN THE NAME OF GOD)*
//**  AMIRMAHDI TAHMASEBI   **

//portotypes
char* connectTwoString(char*, char*);
//End of portotypes

//Helpful additinal functions:
char equalStrings(char* a, char* b){
    if(!strcmp(a,b))
        return 1;
    return 0;
}
char strcheck(char* string, char ch){ //salam , a -> 1 // salam , i -> 0
    int i = 0;
    while(string[i] != 0){
        if(string[i] == ch){
            return 1;
        }
        i++;
    }
    return 0;
}
int ___findLen (char* str){ //only for deleting spaces
    int i = 0;
    while(*(str + i) != ' ' && *(str + i) != '\t' && *(str + i) != '\0')
        i++;
    return i;
}
char* ___find (char* str, int* p){ //only for deleting spaces
    if(*(str + *p) == '\0')
        return NULL;
    while(*(str + *p) == ' ' || *(str + *p) == '\t')
        (*p) ++;
    return (str + *p);
}
void ___print(char* str, int len, char** final){ //only for deleting spaces
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
int getLevelofAddress(char* address){
    int i = 0;
    for(int k = 0; address[k] != 0; k++){
        if(address[k] == '\\'){
            i++;
        }
    }
    return i;
}
int gitFoldeerCheck(char* foldername, int nowLevel, int finalLevel){
    DIR* neogit = opendir(foldername);
    if (neogit) {
        closedir(neogit);
        return 0;
    } 
    else {
        if(nowLevel == finalLevel){
            printf("not a neogit repository (or any of the parent directories): .neogit");
            exit(-1);
        }
        return 1 + gitFoldeerCheck(connectTwoString("..//", foldername), nowLevel+1, finalLevel);
    }
}
//End of additional functions

//other functions
char* GetAddressHere(){
    char* address = (char*)calloc(2000,1);
    if(!system("cd > .____neogit_temp")){
        FILE* f = fopen(".____neogit_temp", "r");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        fscanf(f, "%s", address);
        fclose(f);
        remove(".____neogit_temp");
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);   
    }
    return address;
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
    /* how to use:
    int index = 0;
    while(*(finaladdress + index)){
        printf("%s ", *(finaladdress + index));
        index++;
    }
    */
    return finaladdress;
}
char * connectTwoString(char* a, char* b){
    char* str3 = (char*)calloc(2000,1);
    int i = 0, j = 0;   
    while (a[i] != '\0') {
        str3[j] = a[i];
        i++;
        j++;
    }
    i = 0;
    while (b[i] != '\0') {
        str3[j] = b[i];
        i++;
        j++;
    }
    str3[j] = '\0';
   return str3;
}
char* gitFolder(){
    int k = gitFoldeerCheck(".neogit", 0, getLevelofAddress(GetAddressHere()));
    char* address = (char*)calloc(2000,1);
    for(int i = 0; i < k; i++){
        address = connectTwoString("..//", address);
    }
    address = connectTwoString(address,".neogit");
    return address;
}
char ** tokenizeInput(int* len, char** argv){
    if(*len > 95){
        printf("Too many arguments!\n");
        exit(-1);
    }
    char** input = (char**)calloc(110, sizeof(char*));
    int i;
    for(i = 0; i < *len; i++)
        *(input + i) = argv[i];
    for(; i< 100; i++)
        *(input + i) = (char *)calloc(2,sizeof(char));
    return input;
}
//end of other functions


//main functions
void changeNameGlobal(char* name){
    if(strlen(name) > 70){
        printf("Your name is too long!\n");
        exit(-1);
    }
    if(strcheck(name, '\"')){
        printf("Your name is invalid!\n");
        exit(-1);
    }
    FILE * f = fopen("d://SETTINGS//config//name", "w");
    if(f == NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    fprintf(f, name);
    fclose(f);
    printf("global name changed successfully\n");
}
void changeName(char* name){
    if(strlen(name) > 70){
        printf("Your name is too long!\n");
        exit(-1);
    }
    if(strcheck(name, '\"')){
        printf("Your name is invalid!\n");
        exit(-1);
    }
    char * address =  gitFolder();
    DIR* dir = opendir(connectTwoString(address, "//config"));
    if(dir) {
        FILE *f = fopen(connectTwoString(address,"//config//name"), "w");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        fprintf(f, name);
        fclose(f);
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address, "//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//name"), "w");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fprintf(f, name);
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    printf("local name changed successfully\n");
}
void changeEmailGlobal(char* email){
    if(strlen(email) > 150){
        printf("Your email is too long!\n");
        exit(-1);
    }
    if(strcheck(email, '\"')){
        printf("Your email is invalid!\n");
        exit(-1);
    }
    FILE * f = fopen("d://SETTINGS//config//email", "w");
    if(f == NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    fprintf(f, email);
    fclose(f);
    printf("global email changed successfully\n");
}
void changeEmail(char* email){
    if(strlen(email) > 150){
        printf("Your email is too long!\n");
        exit(-1);
    }
    if(strcheck(email, '\"')){
        printf("Your name is invalid!\n");
        exit(-1);
    }
    char* address = gitFolder();
    DIR* dir = opendir(connectTwoString(address,"//config"));
    if(dir) {
        FILE *f = fopen(connectTwoString(address,"//config//email"), "w");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        fprintf(f, email);
        fclose(f);
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address,"//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//email"), "w");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fprintf(f, email);
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    printf("local email changed successfully\n");
}
void alias(char* newName, char** command){

}

//End of main functions

int main(int argc, char* argv[]){
    //get inputs        #############################
    int len = argc;
    char** input = tokenizeInput(&len, argv);
    //end of getting    #############################

    // neogit config -global user.name
    if(equalStrings(input[1], "config") && equalStrings(input[2], "-global") && equalStrings(input[3], "user.name") && strcasecmp(input[4], "") && equalStrings(input[5], "") && len == 5)
        changeNameGlobal(input[4]);
    // neogit config -global user.email
    if(equalStrings(input[1], "config") && equalStrings(input[2], "-global") && equalStrings(input[3], "user.email") && strcasecmp(input[4], "") && equalStrings(input[5], "") && len == 5)
        changeEmailGlobal(input[4]);
    // neogit config user.name
    if(equalStrings(input[1], "config") && equalStrings(input[2], "user.name") && strcasecmp(input[3], "") && equalStrings(input[4], "") && len == 4)
        changeName(input[3]);
    // neogit config user.email
    if(equalStrings(input[1], "config") && equalStrings(input[2], "user.email") && strcasecmp(input[3], "") && equalStrings(input[4], "") && len == 4)
        changeEmail(input[3]);
    //neogit config -gelobal alias.name "command"
    if(equalStrings(input[1], "config") && equalStrings(input[2], "-gelobal") && (input[3][0] == 'a' && input[3][1] == 'l' && input[3][2] == 'i' && input[3][3] == 'a' && input[3][4] == 's' && input[3][5] == '.' && strlen(input[3]) > 6) && strcasecmp(input[4], "") && equalStrings(input[5], "") && len == 5){       
        if(strlen(input[4]) > 250){
            printf("Your command is too long!\n");
            exit(-1);
        }
        if(strcheck(input[4], '\"')){
            printf("Your command is invalid!\n");
            exit(-1);
        }
        alias(input[3]+6, delete_spaces(input[4]));
    }
    return 0;
}