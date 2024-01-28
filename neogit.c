#include <stdio.h>
#include <stdlib.h>
//#include <sys/stat.h>
//#include <unistd.h>
#include <string.h>
#include <dirent.h>
//#include <errno.h>
#include <time.h>


//   *(IN THE NAME OF THE GOD)*
//   ** AMIRMAHDI TAHMASEBI  **

//portotypes
char* connectTwoString(char*, char*);
//End of portotypes

//structs
struct address__{
    char** address_given;
    int size_address_given;
    char** address_cmd;
    int size_address_cmd;
    char** address_neogit;
    int size_address_neogit;
    char* adress_stage_file;
};
struct count_directory_file{
    int directory;
    int file;
};
typedef struct folder__{
    char name[20];
    unsigned long long time;
    int parent;
    char user_name[200];
    char email[200];
    char massage[100];
    int count_file;
    int count_folder;
    char banch[100];
    struct folder__* next;
    struct folder__* perv;
} folder;
//end of structs

//unions
typedef union parametrs__ {
    char string[100];
    char** list;
    int number_int;
    unsigned long long number_llu;
}parametrs;

//end of unions

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
char** ___split(char* name){ //c:/users\j -> c:   users    j
    char *k = calloc(1000, sizeof(char));
    strcpy(k, name);
    char** a = (char**)calloc(10000, sizeof(char*));
    int i = 0;
    char * u = strtok(k, "\\/");
    while(u){
        a[i] = u;
        u = strtok(NULL, "\\/");
        i++;
    }
    return a;
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
            printf("not a neogit repository (or any of the parent directories): .neogit\n");
            exit(-1);
        }
        return 1 + gitFoldeerCheck(connectTwoString("..//", foldername), nowLevel+1, finalLevel);
    }
}
int initgitFoldeerCheck(char* foldername, int nowLevel, int finalLevel){
    DIR* neogit = opendir(foldername);
    if (neogit) {
        closedir(neogit);
        return 0;
    } 
    else {
        if(nowLevel == finalLevel){
            return -1000000;
        }
        return 1 + initgitFoldeerCheck(connectTwoString("..//", foldername), nowLevel+1, finalLevel);
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
        fscanf(f, "%[^\n]s", address);
        fclose(f);
        remove(".____neogit_temp");
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);   
    }
    return address;
}
char ** getAddressOfHere_tokenized(){
    FILE* f = fopen(".__E__neogit_temp.bat", "w");
    if(f == NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    fprintf(f, "%s\n%s\n%s%s\n%s\n%s\n", "@ECHO OFF", "call set PARENT_DIR=%CD%","set PARENT_DIR=%PARENT_DIR:", " =+%", "set PARENT_DIR=%PARENT_DIR:\\= %", "FOR %%i IN (%PARENT_DIR%) DO (echo %%i>> .____neogit_temp)");
    fclose(f);
    if(!system(".__E__neogit_temp.bat")){
        remove(".__E__neogit_temp.bat");
        f = fopen(".____neogit_temp", "r");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        char** text = (char **)calloc(100, sizeof(char*));
        int i = 0;
        char line[1000];
        while(fgets(line, 990, f) != NULL && line[0] != '\n'){
            for(int u = 0; line[u] != 0; u++)
                if(line[u] == '+')
                    line[u] = ' ';
            *(text + i) = (char*)calloc(1000, sizeof(char));
            strcpy(text[i], line);
            text[i][strlen(text[i]) - 1] = 0;
            i++;
        }
        fclose(f);
        remove(".____neogit_temp");
        return text;
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);
    }
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
    char* str3 = (char*)calloc(strlen(a) + strlen(b) + 10 ,1);
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
char* gitFolder(){ // return address ..//..//..//.neogit //type no if no git folder
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
char checkIfACommandIsOk(char** command){ //return 1 for accept. //********* for alias
    return 1;
}
char checkIfANameRezerved(char* name){ //return 1 for is rezerved. //******** for alias
    return 0;
}
char initgitFolder(){ //1 -> there is a neogit folder. 0-> there is no neo git folder
    int k = initgitFoldeerCheck(".neogit", 0, getLevelofAddress(GetAddressHere()));
    if(k>=0){
        return 1;
    }
    return 0;
}
//end of other functions

//log function
char beInList_normal (folder a, parametrs b){
    if(sizeof(b.number_int) == 4) //unuseful condition just for turnning of gcc warning;
        return 1;
    if(a.time > 0)
        return 1;
    return 0;
}
char timeUpToDown(folder* a, folder* b){
    if(a->time > b->time){
        return 1;
    }
    return 0;
}
char beInList_InBranch(folder a, parametrs b){
    if(!strcmp(a.banch, b.string)){
        return 1;
    }
    return 0;
}
char beInList_InAuthor(folder a, parametrs b){
    if(!strcmp(a.user_name, b.string)){
        return 1;
    }
    return 0;
}
char beInList_since(folder a, parametrs b){
    if(a.time >= b.number_llu){
        return 1;
    }
    return 0;
}
char beInList_before(folder a, parametrs b){
    if(a.time <= b.number_llu){
        return 1;
    }
    return 0;
}
char beInList_search(folder a, parametrs b){
    int i = 0;
    while(b.list[i] != NULL){
        if(strstr(a.massage, b.list[i])){
            return 1;
        } 
        i++;
    }  
    return 0;
}
void print_time(unsigned long long number){
    printf("%04llu", number / 4000000000llu);
    number -= number / 4000000000llu * 4000000000llu;
    printf("/%02llu", number / 4000000llu);
    number -= number / 4000000llu * 4000000llu;
    printf("/%02llu-", number / (60*60*24));
    number -= number / (60*60*24) * (60*60*24);
    printf("%02llu:", number / (60*60));
    number -= number / (60*60) * 60 * 60;
    printf("%02llu:", number / (60));
    number -= number / 60 * 60;
    printf("%02llu", number);
}
//end of log

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
    fprintf(f, "%s", name);
    fclose(f);
    FILE* ff = fopen("d://SETTINGS//config//nameCount", "a");
    fclose(ff);
    long long global = -1, MAX = -1;
    ff = fopen("d://SETTINGS//config//nameCount", "r");
    fscanf(ff, "%lld", &global);
    fclose(ff);
    ff= fopen("d://SETTINGS//config//MAXnameCount", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXnameCount", "r");
    fscanf(ff, "%lld", &MAX);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXnameCount", "w");
    fprintf(ff, "%lld", (MAX > global)? MAX + 1: global + 1);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//nameCount", "w");
    fprintf(ff, "%lld", (MAX > global)? MAX + 1: global + 1);
    fclose(ff);
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
        fprintf(f, "%s", name);
        fclose(f);
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address, "//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//name"), "w");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fprintf(f, "%s", name);
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    FILE* ff = fopen(connectTwoString(address,"//config//nameCount"), "a");
    fclose(ff);
    ff = fopen(connectTwoString(address,"//config//nameCount"), "r");
    long long countlocal = -1, countGlobal = -1, MAX = -1;
    fscanf(ff, "%lld", &countlocal);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//nameCount", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//nameCount", "r");
    fscanf(ff, "%lld", &countGlobal);
    fclose(ff);
    ff = fopen(connectTwoString(address,"//config//nameCount"), "w");
    fprintf(ff, "%lld", (countlocal > countGlobal)? countlocal + 1 : countGlobal + 1);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXnameCount", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXnameCount", "r");
    fscanf(ff, "%lld", &MAX);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXnameCount", "w");
    fprintf(ff, "%lld", (MAX > ((countlocal > countGlobal)? countlocal + 1 : countGlobal + 1))? MAX : ((countlocal > countGlobal)? countlocal + 1 : countGlobal + 1));
    fclose(ff);
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
    fprintf(f,"%s", email);
    fclose(f);
    FILE* ff = fopen("d://SETTINGS//config//emailCount", "a");
    fclose(ff);
    long long global = -1, MAX = -1;
    ff = fopen("d://SETTINGS//config//emailCount", "r");
    fscanf(ff, "%lld", &global);
    fclose(ff);
    ff= fopen("d://SETTINGS//config//MAXemailCount", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXemailCount", "r");
    fscanf(ff, "%lld", &MAX);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXemailCount", "w");
    fprintf(ff, "%lld", (MAX > global)? MAX + 1: global + 1);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//emailCount", "w");
    fprintf(ff, "%lld", (MAX > global)? MAX + 1: global + 1);
    fclose(ff);
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
        fprintf(f, "%s", email);
        fclose(f);
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address,"//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//email"), "w");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fprintf(f, "%s", email);
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    FILE* ff = fopen(connectTwoString(address,"//config//emailCount"), "a");
    fclose(ff);
    ff = fopen(connectTwoString(address,"//config//emailCount"), "r");
    long long countlocal = -1, countGlobal = -1, MAX = -1;
    fscanf(ff, "%lld", &countlocal);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//emailCount", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//emailCount", "r");
    fscanf(ff, "%lld", &countGlobal);
    fclose(ff);
    ff = fopen(connectTwoString(address,"//config//emailCount"), "w");
    fprintf(ff, "%lld", (countlocal > countGlobal)? countlocal + 1 : countGlobal + 1);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXemailCount", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXemailCount", "r");
    fscanf(ff, "%lld", &MAX);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXemailCount", "w");
    fprintf(ff, "%lld", (MAX > ((countlocal > countGlobal)? countlocal + 1 : countGlobal + 1))? MAX : ((countlocal > countGlobal)? countlocal + 1 : countGlobal + 1));
    fclose(ff);
    printf("local email changed successfully\n");
}
char* current_name(){
    char * address =  gitFolder();
    DIR* dir = opendir(connectTwoString(address, "//config"));
    if(dir) {
        FILE *f = fopen(connectTwoString(address,"//config//name"), "a");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        fclose(f);
        f = fopen(connectTwoString(address,"//config//nameCount"), "a");
            if(f == NULL){
                printf("an unkown problem!\n");
                exit(-1);
            }
        fclose(f);
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address, "//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//name"), "a");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fclose(f);
            f = fopen(connectTwoString(address,"//config//nameCount"), "a");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    FILE* ff = fopen("d://SETTINGS//config//name", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//nameCount", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXnameCount", "a");
    fclose(ff);
    char *name = calloc(200, sizeof(char));
    long long local = -1, global = -1;
    ff = fopen(connectTwoString(address,"//config//nameCount"), "r");
    fscanf(ff, "%lld", &local);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//nameCount", "r");
    fscanf(ff, "%lld", &global);
    fclose(ff);
    if(global >= local){
        ff = fopen("d://SETTINGS//config//name", "r");
        fscanf(ff, "%[^\n]s", name);
        fclose(ff);
        if(name[0] == 0){
            strcpy(name, "NULL");
        }
        return name;
    }
    ff = fopen(connectTwoString(address,"//config//name"), "r");
    fscanf(ff, "%[^\n]s", name);
    fclose(ff);
    return name;
}
char* current_email(){
    char * address =  gitFolder();
    DIR* dir = opendir(connectTwoString(address, "//config"));
    if(dir) {
        FILE *f = fopen(connectTwoString(address,"//config//email"), "a");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        fclose(f);
        f = fopen(connectTwoString(address,"//config//emailCount"), "a");
            if(f == NULL){
                printf("an unkown problem!\n");
                exit(-1);
            }
        fclose(f);
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address, "//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//email"), "a");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fclose(f);
            f = fopen(connectTwoString(address,"//config//emailCount"), "a");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    FILE* ff = fopen("d://SETTINGS//config//email", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//emailCount", "a");
    fclose(ff);
    ff = fopen("d://SETTINGS//config//MAXemailCount", "a");
    fclose(ff);
    char *email = calloc(200, sizeof(char));
    long long local = -1, global = -1;
    ff = fopen(connectTwoString(address,"//config//emailCount"), "r");
    fscanf(ff, "%lld", &local);
    fclose(ff);
    ff = fopen("d://SETTINGS//config//emailCount", "r");
    fscanf(ff, "%lld", &global);
    fclose(ff);
    if(global >= local){
        ff = fopen("d://SETTINGS//config//email", "r");
        fscanf(ff, "%[^\n]s", email);
        fclose(ff);
        if(email[0] == 0){
            strcpy(email, "NULL");
        }
        return email;
    }
    ff = fopen(connectTwoString(address,"//config//email"), "r");
    fscanf(ff, "%[^\n]s", email);
    fclose(ff);
    return email;
}
int current_id(){
    FILE* f = fopen("d://SETTINGS//config//idCount", "a");
    fclose(f);
    f = fopen("d://SETTINGS//config//idCount", "r");
    int number = -1;
    fscanf(f, "%d", &number);
    number++;
    fclose(f);
    f = fopen("d://SETTINGS//config//IDs", "r");
    int list;
    char line[10];
    for(int i = 0; i <= number; i++){
        fgets(line, 9, f);
        for(int j = 0; j < 10; j++){
            if(line[j] == '\n')
                line[j] = 0;
        }
        list = atoi(line);
    }
    fclose(f);
    f = fopen("d://SETTINGS//config//idCount", "w");
    fprintf(f, "%d", number);
    fclose(f);
    return list;
}
char ** current_dateTime(){
    char ** dateTime = (char**)calloc(6,sizeof(char*));
    time_t t = time(NULL);
    struct tm tmm = *localtime(&t);
    for(int i = 0; i < 6; i++)
        dateTime[i] = (char*)calloc(6, sizeof(char));
    sprintf(dateTime[0], "%04d", tmm.tm_year + 1900);
    sprintf(dateTime[1], "%02d", tmm.tm_mon + 1);
    sprintf(dateTime[2], "%02d", tmm.tm_mday);
    sprintf(dateTime[3], "%02d", tmm.tm_hour);
    sprintf(dateTime[4], "%02d", tmm.tm_min);
    sprintf(dateTime[5], "%02d", tmm.tm_sec);
    return dateTime;
}
void GlobalAlias(char* newName, char** command){
    if(checkIfANameRezerved(newName)){
        printf("The new name is invalid! (alias.*)\n");
        exit(-1);
    }
    if(!checkIfACommandIsOk(command)){
        printf("The command is invalid!\n");
        exit(-1);
    }
    FILE * f = fopen("d://SETTINGS//config//alias", "a");
    if(f == NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    fprintf(f, "%s\n", newName);
    int index = 0;
    while(*(command + index)){
        fprintf(f, "%s ", *(command + index));
        index++;
    }
    fprintf(f, "\n");
    fclose(f);
    printf("global alias updated successfully\n");
}
void Alias(char* newName, char** command){
    if(checkIfANameRezerved(newName)){
        printf("The new name is invalid! (alias.*)\n");
        exit(-1);
    }
    if(!checkIfACommandIsOk(command)){
        printf("The command is invalid!\n");
        exit(-1);
    }
    char * address =  gitFolder();
    DIR* dir = opendir(connectTwoString(address, "//config"));
    if(dir) {
        FILE *f = fopen(connectTwoString(address,"//config//alias"), "a");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        fprintf(f, "%s\n", newName);
        int index = 0;
        while(*(command + index)){
            fprintf(f, "%s ", *(command + index));
            index++;
        }
        fprintf(f, "\n");
        fclose(f);
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address, "//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//alias"), "a");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fprintf(f, "%s\n", newName);
            int index = 0;
            while(*(command + index)){
                fprintf(f, "%s ", *(command + index));
                index++;
            }
            fprintf(f, "\n");
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    printf("local alias updated successfully\n");
}
void init(){
    if(initgitFolder()){
        printf("a neoit repository is existed!\n");
        exit(-1);
    }
    if (!mkdir(".neogit")){
        system("attrib +h .neogit");
        mkdir(".neogit\\stage");
        mkdir(".neogit\\config");
        FILE* f = fopen(".neogit\\config\\undo", "w"); fclose(f);
        f = fopen(".neogit\\config\\alias", "w"); fclose(f);
        f = fopen(".neogit\\config\\email", "w"); fclose(f);
        f = fopen(".neogit\\config\\emailCount", "w"); fclose(f);
        f = fopen(".neogit\\config\\name", "w"); fclose(f);
        f = fopen(".neogit\\config\\shortcut", "w"); fclose(f);
        f = fopen(".neogit\\config\\nameCount", "w"); fclose(f);
        mkdir(".neogit\\config\\branch");
        f = fopen(".neogit\\config\\branch\\current", "w"); fprintf(f, "%s", "master"); fclose(f);
        f = fopen(".neogit\\config\\branch\\list", "w"); fprintf(f, "%s\n%s", "master", "NULL"); fclose(f);
        printf("Initialized empty neogit repository\n");
        mkdir(".neogit\\commits");
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);
    }
}
char check_type(char* name){ // 1 -> folder 0-> not found  -1->file
    if(!system("echo A > .____neogit_temp")){
        if(!system(connectTwoString("if exist \"", connectTwoString(name, "\\*\" echo Q > .____neogit_temp")))){
            char check = 0;
            FILE* f = fopen(".____neogit_temp", "r");
            fscanf(f, "%c", &check);
            fclose(f);
            if(check == 'Q'){ // it is a folder;
                remove(".____neogit_temp");
                return 1;
            }
            else{ // it is not a folder
                if(!system(connectTwoString("if exist \"", connectTwoString(name, "\" echo W > .____neogit_temp")))){
                    f = fopen(".____neogit_temp", "r");
                    if(f == NULL){
                        printf("an unkown problem!\n");
                        exit(-1);
                    }
                    fscanf(f, "%c", &check);
                    fclose(f);
                    remove(".____neogit_temp");
                    if(check == 'W'){ // it is a file
                        return -1;
                    }
                    else{ //not found
                        return 0;
                    }
                }
            }
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);   
        }
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);   
    }
    return 0;
}
struct address__ Help_ADD(char* name){
    char * address_stage = gitFolder();
    DIR* dir = opendir(connectTwoString(address_stage, "//stage"));
    if(dir) {
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address_stage, "//stage"))){
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    char ** address_file = getAddressOfHere_tokenized();
    char ** address_neogit = getAddressOfHere_tokenized();
    FILE* f = fopen(".__E__neogit_temp.bat", "w");
    if(f == NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    fprintf(f, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "@ECHO OFF", "call set PARENT_DIR=%%CD%%" , "set /A j = 0" , ":while", "if  not exist \".neogit/*\" (", "	set /a j += 1" , "	cd ..", "	goto :while" , ")", "cd %PARENT_DIR%", "echo %j% > .____neogit_temp");
    fclose(f);
    int ch = 0;;
    if(!system(".__E__neogit_temp.bat")){
        remove(".__E__neogit_temp.bat");
        f = fopen(".____neogit_temp", "r");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        fscanf(f, "%d", &ch);
        fclose(f);
        remove(".____neogit_temp");
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);
    }
    int a = 0;
    while(address_neogit[a]){
        a++;
    }
    a--;
    for(int m = 0; m < ch; m++){
        address_neogit[a] = NULL;
        a--;
    }
    char** address_given = ___split(name);
    int size_address_file = 0;
    while(address_file[size_address_file]){
        size_address_file++;
    }
    int size_address_neogit = 0;
    while(address_neogit[size_address_neogit]){
        size_address_neogit++;
    }
    int size_address_given = 0;
    while(address_given[size_address_given]){
        size_address_given++;
    }
    char * dis = (char*)calloc(10000, sizeof(char));
    for(int i = 0; i < size_address_neogit; i++){
        dis = connectTwoString(dis, address_neogit[i]);
        dis = connectTwoString(dis, "\\");
    }
    dis = connectTwoString(dis, ".neogit\\stage\\");
    for(int i = size_address_neogit; i < size_address_file; i++){
        dis = connectTwoString(dis, address_file[i]);
        dis = connectTwoString(dis, "\\");
    }

    for(int i = 0; i < size_address_given-1; i++){
        dis = connectTwoString(dis, address_given[i]);
        dis = connectTwoString(dis, "\\");
    }
    struct address__ tt;
    tt.address_cmd = address_file;
    tt.address_given = address_given;
    tt.address_neogit = address_neogit;
    tt.size_address_cmd = size_address_file;
    tt.size_address_given = size_address_given;
    tt.size_address_neogit = size_address_neogit;
    tt.adress_stage_file = dis;
    return tt;
}
void addToUndo(char* name_file, char mode, char* address_undo){
    FILE* f = fopen(address_undo, "r");
    if(f==NULL){
        char * gitfolder = gitFolder();
        gitfolder = connectTwoString(gitfolder, "//config");
        mkdir(gitfolder);
        char oo[1000];
        sprintf(oo, "echo.> %s", address_undo);
        if(system(oo)){
            printf("an unkown problem!\n");
            exit(-1);
        }
        f = fopen(address_undo, "r");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    char line[30][400];
    int count = 0;
    while(fgets(line[count], 399, f)){
        count++;
    }
    fclose(f);
    FILE* ff = fopen(address_undo, "w");
    if(ff == NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    if(count == 1){
        char* temp = (char*)calloc(10, sizeof(char));
        fprintf(ff, "%s",temp);
        addToUndo(name_file, mode, address_undo);
        count = 0;
    }
    if(count <= 18){
        for(int i = 0;i<count; i++){
            fprintf(ff, "%s", line[i]);
        }
    }
    else{
        for(int i = 2;i<count; i++){
            fprintf(ff, "%s", line[i]);
        }
    }
    fprintf(ff, "%s\n", name_file);
    fprintf(ff,"%d\n", mode);
    fclose(ff);
}
void Undo(){
    char * address_undo = gitFolder();
    address_undo = connectTwoString(address_undo, "//config//undo");
    FILE * f = fopen(address_undo, "r");
    if(f==NULL){
        char * gitfolder = gitFolder();
        gitfolder = connectTwoString(gitfolder, "//config");
        mkdir(gitfolder);
        char oo[1000];
        sprintf(oo, "echo.> %s", address_undo);
        if(system(oo)){
            printf("an unkown problem!\n");
            exit(-1);
        }
        f = fopen(address_undo, "r");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }

    }
    char line[30][400];
    int count = 0;
    while(fgets(line[count], 399, f)){
        count++;
    }
    fclose(f);
    FILE* ff = fopen(address_undo, "w");
    if(ff == NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    for(int i = 0; i < count-2; i++){
        fprintf(ff, "%s", line[i]);
    }
    fclose(ff);
    if(count == 0){
        printf("There is no history of adding files!\n");
        exit(-1);
    }
    if(count == 1){
        printf("There is no history of adding files!\n");
        char temp[] = "";
        fprintf(ff, "%s",temp);
        exit(-1);
    }
    int mode;
    char* address = (char*)calloc(400, sizeof(char));
    sscanf(line[count - 1], "%d", &mode);
    sscanf(line[count - 2], "%[^\n]s", address);
    char command[1000];
    if(mode == -1){
        char oo[400];
        sprintf(oo, "if exist \"%s\" echo. > ____T____.neogit", address);
        system(oo);
        FILE* ooo = fopen("____T____.neogit", "r");
        if(ooo == NULL){
            char temp[] = ".neogit\\stage\\";
            for(int i = 0; i < (int)strlen(address) - (int)strlen(temp) - 1; i++){
                int flag = 1;
                int j;
                for(j = 0; j < (int)strlen(temp); j++){
                    if (address[i+j] != temp[j]){
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    address = (address+i+j);
                    break;
                }
            }
            printf("%s is unstage now!\n", address);
            exit(-1);
        }
        fclose(ooo);
        remove("____T____.neogit");
        sprintf(command, "del /f /q \"%s\"", address);
        if(!system(command)){
            char temp[] = ".neogit\\stage\\";
            for(int i = 0; i < (int)strlen(address) - (int)strlen(temp) - 1; i++){
                int flag = 1;
                int j;
                for(j = 0; j < (int)strlen(temp); j++){
                    if (address[i+j] != temp[j]){
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    address = (address+i+j);
                    break;
                }
            }
            printf("%s unstaged successfully\n", address);
            exit(0);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    else if(mode == 1){
        char oo[400];
        sprintf(oo, "if exist \"%s*\" echo. > ____T____.neogit", address);
        system(oo);
        FILE* ooo = fopen("____T____.neogit", "r");
        if(ooo == NULL){
            char temp[] = ".neogit\\stage\\";
            for(int i = 0; i < (int)strlen(address) - (int)strlen(temp) - 1; i++){
                int flag = 1;
                int j;
                for(j = 0; j < (int)strlen(temp); j++){
                    if (address[i+j] != temp[j]){
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    address = (address+i+j);
                    break;
                }
            }
            printf("%s is unstage now!\n", address);
            exit(-1);
        }
        fclose(ooo);
        remove("____T____.neogit");
        sprintf(command, "rmdir /s /q \"%s\"", address);
        if(!system(command)){
            char temp[] = ".neogit\\stage\\";
            for(int i = 0; i < (int)strlen(address) - (int)strlen(temp) - 1; i++){
                int flag = 1;
                int j;
                for(j = 0; j < (int)strlen(temp); j++){
                    if (address[i+j] != temp[j]){
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    address = (address+i+j);
                    break;
                }
            }
            printf("%s unstaged successfully\n", address);
            exit(0);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);
    }
}
void add(char *name){
    char * address_stage = gitFolder();
    char mode = check_type(name);
    if(!mode){
        printf("<%s> not found!\n", name);
        exit(-1);
    }
    DIR* dir = opendir(connectTwoString(address_stage, "//stage"));
    if(dir) {
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address_stage, "//stage"))){
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    char ** address_file = getAddressOfHere_tokenized();
    char ** address_neogit = getAddressOfHere_tokenized();
    FILE* f = fopen(".__E__neogit_temp.bat", "w");
    if(f == NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    fprintf(f, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "@ECHO OFF", "call set PARENT_DIR=%%CD%%" , "set /A j = 0" , ":while", "if  not exist \".neogit/*\" (", "	set /a j += 1" , "	cd ..", "	goto :while" , ")", "cd %PARENT_DIR%", "echo %j% > .____neogit_temp");
    fclose(f);
    int ch = 0;;
    if(!system(".__E__neogit_temp.bat")){
        remove(".__E__neogit_temp.bat");
        f = fopen(".____neogit_temp", "r");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        fscanf(f, "%d", &ch);
        fclose(f);
        remove(".____neogit_temp");
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);
    }
    int a = 0;
    while(address_neogit[a]){
        a++;
    }
    a--;
    for(int m = 0; m < ch; m++){
        address_neogit[a] = NULL;
        a--;
    }
    char** address_given = ___split(name);
    int size_address_file = 0;
    while(address_file[size_address_file]){
        size_address_file++;
    }
    int size_address_neogit = 0;
    while(address_neogit[size_address_neogit]){
        size_address_neogit++;
    }
    int size_address_given = 0;
    while(address_given[size_address_given]){
        size_address_given++;
    }
    char * dis = (char*)calloc(10000, sizeof(char));
    for(int i = 0; i < size_address_neogit; i++){
        dis = connectTwoString(dis, address_neogit[i]);
        dis = connectTwoString(dis, "\\");
    }
    char* address_undo = connectTwoString(dis, ".neogit\\config\\undo");
    dis = connectTwoString(dis, ".neogit\\stage\\");
    for(int i = size_address_neogit; i < size_address_file; i++){
        dis = connectTwoString(dis, address_file[i]);
        dis = connectTwoString(dis, "\\");
    }

    for(int i = 0; i < size_address_given-1; i++){
        dis = connectTwoString(dis, address_given[i]);
        dis = connectTwoString(dis, "\\");
    }
    if(mode == -1){
        char* command = (char*)calloc(10000,sizeof(char));
        sprintf(command, "if not exist \"%s\\*\" mkdir \"%s\"", dis, dis);
        if(!system(command)){
            f = fopen(".__E__neogit_temp.bat", "w");
            if(f == NULL){
                printf("an unkown problem!\n");
                exit(-1);
            }
            fprintf(f, "@ECHO OFF\ncopy \"%s\" \"%s\" > NUL", name, dis);
            fclose(f);
            if(!system(".__E__neogit_temp.bat")){
                remove(".__E__neogit_temp.bat");
                for(int i = 0; i < size_address_given-1; i++)
                    printf("%s\\", address_given[i]);
                addToUndo(connectTwoString(dis,address_given[size_address_given - 1]), -1, address_undo);
                printf("%s added successfully\n", address_given[size_address_given - 1]);
                exit(0);
            }
            else{
                remove(".__E__neogit_temp.bat");
                printf("an unkown problem!\n");
                exit(-1); 
            }
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    
    if(mode == 1){
        dis = connectTwoString(dis, address_given[size_address_given - 1]);
        dis = connectTwoString(dis, "\\");
        char* command = (char*)calloc(10000,sizeof(char));
        sprintf(command, "if not exist \"%s\\*\" mkdir \"%s\\\"", dis, dis);
        if(!system(command)){
            f = fopen(".__E__neogit_temp.bat", "w");
            if(f == NULL){
                printf("an unkown problem!\n");
                exit(-1);
            }
            fprintf(f, "@ECHO OFF\nxcopy \"%s\\*\" \"%s\\*\" /e/h/c/i/y > NUL", name, dis);
            fclose(f);
            if(!system(".__E__neogit_temp.bat")){
                remove(".__E__neogit_temp.bat");
                for(int i = 0; i < size_address_given-1; i++)
                    printf("%s\\", address_given[i]);
                addToUndo(dis, 1, address_undo);
                printf("%s\\ added successfully\n", address_given[size_address_given - 1]);
                exit(0);
            }
            else{
                remove(".__E__neogit_temp.bat");
                printf("an unkown problem!\n");
                exit(-1); 
            }
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
}
void rest(char * name){
    struct address__ adress = Help_ADD(name);
    adress.adress_stage_file = connectTwoString(adress.adress_stage_file, adress.address_given[adress.size_address_given - 1]);
    char mode = check_type(adress.adress_stage_file);
    if(!mode){
        printf("<%s> is not in stage now!\n", name);
        exit(-1);
    }
    if(mode == -1){
        char dastoor[1000];
        sprintf(dastoor, "del /f/q \"%s\"", adress.adress_stage_file);
        if(!system(dastoor)){
            printf("%s unstaged successfully\n", name);
            exit(0);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
    if(mode == 1){
        char dastoor[1000];
        sprintf(dastoor, "RMDIR /s/q \"%s\"", adress.adress_stage_file);
        if(!system(dastoor)){
            printf("%s\\ unstaged successfully\n", name);
            exit(0);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }

}
void checkFileInStage(char* name, int mode){
    struct address__ address = Help_ADD(name);
    address.adress_stage_file = connectTwoString(address.adress_stage_file,address.address_given[address.size_address_given - 1]);
    char command[400];
    if(mode == 1){
        sprintf(command, "if exist \"%s\\*\" echo. > ___T____.neogit", address.adress_stage_file);
        system(command);
        FILE* f = fopen("___T____.neogit","r");
        if(f == NULL){
            printf("%s\\ is not in stage area.\n", name);
            exit(0);
        }
        fclose(f);
        remove("___T____.neogit");
        printf("%s\\ is in stage area.\n", name);
        exit(0);
    }
    if(mode == -1){
        sprintf(command, "if exist \"%s\" echo. > ___T____.neogit", address.adress_stage_file);
        system(command);
        FILE* f = fopen("___T____.neogit","r");
        if(f == NULL){
            printf("%s is not in stage area\n", name);
            exit(0);
        }
        fclose(f);
        remove("___T____.neogit");
        printf("%s is in stage area\n", name);
        exit(0);
    }
}
void addNDeath(char* address, int death){
    gitFolder();
    char directiries[100][400];
    int numberdir = 0;
    char files[100][400];
    int numberfile = 0;
    char* address_free;
    if(death == 0){
        return;
    }
    DIR* dir;
    dir = opendir(address);
    struct dirent* entry;
    if(dir == NULL){
        printf("unable to open %s directory\n", address);
        return;
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free = connectTwoString(address, "");
            char isDir;
            address_free = connectTwoString(address_free, connectTwoString("\\", entry->d_name));
            address_free = address_free + 2;
            isDir = check_type(address_free);
            if(isDir == 1){
                strcpy(directiries[numberdir], address_free);
                numberdir++;
            }
            else{
                strcpy(files[numberfile], address_free);
                numberfile++;
            }
        }
    }
    closedir(dir);
    for(int i = 0; i < numberfile; i++){
        char oo[500];
        sprintf(oo, "neogit ___check_if_a_file_is_in_stage__ \"%s\" -1", files[i]);
        system(oo);
    }
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        char oo[500];
        sprintf(oo, "neogit ___check_if_a_file_is_in_stage__ \"%s\" 1", directiries[i]);
        system(oo);
        addNDeath(connectTwoString(".\\", directiries[i]), death - 1);
    }
}
char* absolute_address_neogit(){
    char* address = (char*)calloc(400, sizeof(char));
    struct address__ ab = Help_ADD("a");
    for(int i = 0; i < ab.size_address_neogit; i++)
        address = connectTwoString(address, connectTwoString(ab.address_neogit[i], "\\"));
    address = connectTwoString(address, ".neogit");
    return address;
}
int* Help_current_countOfStageFiles(char* address){
    if(address[0] == 0){
        address = absolute_address_neogit();
        address = connectTwoString(address, "\\stage");
    }
    char directiries[100][400];
    int numberdir = 0;
    int numberfile = 0;
    char* address_free;
    DIR* dir;
    dir = opendir(address);
    struct dirent* entry;
    if(dir == NULL){
        printf("unable to open %s directory\n", address);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free = connectTwoString(address, "");
            char isDir;
            address_free = connectTwoString(address_free, connectTwoString("\\", entry->d_name));
            isDir = check_type(address_free);
            if(isDir == 1){
                strcpy(directiries[numberdir], address_free);
                numberdir++;
            }
            else{
                numberfile++;
            }
        }
    }
    closedir(dir);
    int* count = (int*)calloc(2, sizeof(int));
    count[1] += numberfile;
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        count[0] += 1;
        int* temp = Help_current_countOfStageFiles(directiries[i]);
        count[0] += temp[0];
        count[1] += temp[1];
    }
    return count;
}
struct count_directory_file current_countOfStageFiles(){
    int* a = Help_current_countOfStageFiles("");
    struct count_directory_file b;
    b.file = a[1];
    b.directory = a[0];
    return b;
}
char* get_current_brach(){
    char* address = gitFolder();
    address = connectTwoString(address, "//config//branch//current");
    FILE* f = fopen(address, "r");
    char* line = (char*)calloc(100, sizeof(char));
    fscanf(f,"%[^\n]s", line);
    fclose(f);
    return line;
}
int get_last_hash(char mode){ // mode c = commit - exit if we are not in a branch
    char* branch = get_current_brach();
    if(branch[0] <= '9' && branch[0] >= '0'){
        int hash = atoi(branch);
        if(mode == 'c'){
            printf("Head is not on a branch. so you can't commit.\n");
            exit(0);
        }
        return hash;
    }
    char* address = gitFolder();
    address = connectTwoString(address, "//config//branch//list");
    FILE* f = fopen(address, "r");
    char line[100];
    while(fgets(line, 99, f) != NULL){
        if(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r')
            line[strlen(line) - 1] = 0;
        if(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r')
            line[strlen(line) - 1] = 0;
        if(!strcmp(line, branch)){
            fgets(line, 99, f);
            if(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r')
                line[strlen(line) - 1] = 0;
            if(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r')
                line[strlen(line) - 1] = 0;
            if (line[0] == 'N') return 0;
            int number = 0;
            number = atoi(line);
            return number;
        }
    }
    printf("an unknown problem!\n");
    exit(-1);
    return 0;
}
void change_last_commit_id(char* branch, int id){
    char* address = gitFolder();
    address = connectTwoString(address, "//config//branch//list");
    FILE* f = fopen(address, "r");
    char line[1000][100];
    int i = 0;
    while(fgets(line[i], 99, f) != NULL){
        if(line[i][strlen(line[i]) - 1] == '\n' || line[i][strlen(line[i]) - 1] == '\r')
            line[i][strlen(line[i]) - 1] = 0;
        if(line[i][strlen(line[i]) - 1] == '\n' || line[i][strlen(line[i]) - 1] == '\r')
            line[i][strlen(line[i]) - 1] = 0;
        if(!strcmp(line[i], branch)){
            i++;
            char temp[100];
            fgets(temp, 99, f);
            sprintf(line[i], "%d", id);
        }
        i++;
    }
    fclose(f);
    f = fopen(address, "w");
    for(int j = 0; j < i; j++){
        fprintf(f, "%s\n", line[j]);
    }
    fclose(f);
}
void commit(char* massage){
    char* branch = get_current_brach();
    char* name = current_name();
    char* email = current_email();
    int id = current_id();
    char** date = current_dateTime();
    struct count_directory_file count = current_countOfStageFiles();
    int last_id = get_last_hash('c');
    if(count.directory == 0 && count.file == 0){
        printf("There is nothing in stage area.\n");
        exit(0);
    }
    change_last_commit_id(branch, id);
    char* address = gitFolder();
    char temp[100];
    sprintf(temp, "%d", id);
    char* address_commit = connectTwoString(address, connectTwoString("//commits//", temp));
    sprintf(temp, "%d_info", id);
    char* address_commit_info = connectTwoString(address, connectTwoString("//commits//", temp));
    if(!mkdir(address_commit) && !mkdir(address_commit_info)){
        FILE* f = fopen(connectTwoString(address_commit_info, "//name"), "w");
        fprintf(f, "%s", name);
        fclose(f);
        f = fopen(connectTwoString(address_commit_info, "//email"), "w");
        fprintf(f, "%s", email);
        fclose(f);
        f = fopen(connectTwoString(address_commit_info, "//count"), "w");
        fprintf(f, "%d %d", count.directory, count.file);
        fclose(f);
        f = fopen(connectTwoString(address_commit_info, "//branch"), "w");
        fprintf(f, "%s", branch);
        fclose(f);
        f = fopen(connectTwoString(address_commit_info, "//parent"), "w");
        fprintf(f, "%d", last_id);
        fclose(f);
        f = fopen(connectTwoString(address_commit_info, "//date"), "w");
        fprintf(f, "%s %s %s %s %s %s", date[0], date[1], date[2], date[3], date[4], date[5]);
        fclose(f);
        f = fopen(connectTwoString(address_commit_info, "//massage"), "w");
        fprintf(f, "%s", massage);
        fclose(f);
        char* address_neogit = absolute_address_neogit();
        address_neogit = connectTwoString(address_neogit, "\\stage");
        ///////////////////// commiting
        DIR* dir;
        dir = opendir(address_neogit);
        struct dirent* entry;
        if(dir == NULL){
            printf("unable to open %s directory\n", address_neogit);
            exit(-1);
        }
        char* address_free;
        sprintf(temp, "%d", id);
        char* address_commit_absolut = connectTwoString(absolute_address_neogit(), connectTwoString("\\commits\\", temp));
        char command[400];
        sprintf(command, "xcopy \"%s\\*\" \"%s\" /e/h/c/i/y > NUL", address_neogit, address_commit_absolut);
        if(system(command)){
            printf("an unknown problem!\n");
            exit(-1);
        }
        while ((entry = readdir(dir)) != NULL){
            if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
                address_free = connectTwoString(address_neogit, "");
                char isDir;
                address_free = connectTwoString(address_free, connectTwoString("\\", entry->d_name));
                isDir = check_type(address_free);
                if(isDir == 1){
                    sprintf(command, "rmdir /s /q \"%s\"", address_free);
                    if(system(command)){
                        printf("an unknown problem!\n");
                        continue;
                    }
                }
                else{
                    sprintf(command, "del /f /q \"%s\"", address_free);
                    if(system(command)){
                        printf("an unknown problem!\n");
                        continue;
                    }
                }
            }
        }
        closedir(dir);
    /////////////////////
        printf("%d directory(s) and %d file(s) commited by ID %d  at %s/%s/%s-%s:%s:%s on branch %s\n", count.directory, count.file, id, date[0],date[1],date[2],date[3],date[4],date[5], branch);
        printf("commit massage is: %s", massage);
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);
    }
}
char* extract_massage_shortcut(char* name){
    char * address =  gitFolder();
    char* massage = (char*)calloc(100, sizeof(char));
    char lines[100];
    DIR* dir = opendir(connectTwoString(address, "//config"));
    if(dir) {
        FILE *f = fopen(connectTwoString(address,"//config//shortcut"), "r");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        int index = 0;
        while(fgets(lines, 99, f) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(!strcmp(lines, name) && index%2 == 0){
                fgets(lines, 99, f);
                strcpy(massage, lines);
                return massage;
            }
            index++;
        }
        fclose(f);
        massage[0] = 0;
        return massage;
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address, "//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//shortcut"), "a");
            if(f == NULL){
                printf("an unkown problem!\n");
                exit(-1);
            }
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
        massage[0] = 0;
        return massage;
    }
}
void add_shortcut_massage(char* name, char* massage){
    if(extract_massage_shortcut(name)[0] != 0){
        printf("this name of shortcut is currently exist.\n");
        exit(0);
    }
    char * address =  gitFolder();
    DIR* dir = opendir(connectTwoString(address, "//config"));
    if(dir) {
        FILE *f = fopen(connectTwoString(address,"//config//shortcut"), "a");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        fprintf(f, "%s\n%s\n", name, massage);
        fclose(f);
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address, "//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//shortcut"), "a");
                if(f == NULL){
                    printf("an unkown problem!\n");
                    exit(-1);
                }
            fprintf(f, "%s\n%s\n", name, massage);
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
    }
}
void delete_shortcut_massage(char* name){
    if(extract_massage_shortcut(name)[0] == 0){
        printf("this name of shortcut is not currently exist.\n");
        exit(0);    
    }
    char * address =  gitFolder();
    char lines[1000][100];
    int index = 0;
    DIR* dir = opendir(connectTwoString(address, "//config"));
    if(dir) {
        FILE *f = fopen(connectTwoString(address,"//config//shortcut"), "r");
        if(f == NULL){
            printf("an unkown problem!\n");
            exit(-1);
        }
        char flag = 1;
        while(fgets(lines[index], 99, f) != NULL){
            if(lines[index][strlen(lines[index]) - 1] == '\n' || lines[index][strlen(lines[index]) - 1] == '\r')
                lines[index][strlen(lines[index]) - 1] = 0;
            if(lines[index][strlen(lines[index]) - 1] == '\n' || lines[index][strlen(lines[index]) - 1] == '\r')
                lines[index][strlen(lines[index]) - 1] = 0;
            if(!strcmp(lines[index], name) && index%2 == 0){
                flag = 0;
                strcpy(lines[index], "");
                index++;
                fgets(lines[index], 99, f);
                strcpy(lines[index], "");
            }
            index++;
        }
        fclose(f);
        if(flag){
            printf("can't find shortcut-name in list.\n");
            exit(0);    
        }
        f = fopen(connectTwoString(address,"//config//shortcut"), "w");
        for(int i = 0; i < index; i++){
            if(!strcmp(lines[i],"")) continue;
            fprintf(f, "%s\n", lines[i]);
        }
        fclose(f);
        closedir(dir);
    } else  {
        if (!mkdir(connectTwoString(address, "//config"))){
            FILE *f = fopen(connectTwoString(address,"//config//shortcut"), "a");
            if(f == NULL){
                printf("an unkown problem!\n");
                exit(-1);
            }
            fclose(f);
        }
        else{
            printf("an unkown problem!\n");
            exit(-1);
        }
        printf("can't find shortcut-name in list.\n");
        exit(0);
    }
}
char is_banchName_exist(char* name){
    char* address = gitFolder();
    address = connectTwoString(address, "//config//branch//list");
    FILE* f = fopen(address, "r");
    char lines[100];
    int index = 0;
    while(fgets(lines, 99, f) != NULL){
        if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
            lines[strlen(lines) - 1] = 0;
        if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
            lines[strlen(lines) - 1] = 0;
        if(!strcmp(lines, name) && index%2 == 0){
            return 1;
        }
        index++;
    }
    fclose(f);
    return 0;
}
void create_new_branch(char* name){
    if(is_banchName_exist(name)){
        printf("branch %s is currently exist\n", name);
        exit(0);
    }
    char* address = gitFolder();
    address = connectTwoString(address, "//config//branch//list");
    FILE* f = fopen(address, "a");
    fprintf(f, "%s\n%d\n", name, get_last_hash('a'));
    fclose(f);
}
void show_listOfAllBranches(){
    char* address = gitFolder();
    address = connectTwoString(address, "//config//branch//list");
    FILE* f = fopen(address, "r");
    if(f==NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    char lines[100];
    int index = 0;
    while(fgets(lines, 99, f) != NULL){
        if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
            lines[strlen(lines) - 1] = 0;
        if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
            lines[strlen(lines) - 1] = 0;
        if(index % 2 == 0){
            printf("branch: %s, ", lines);
        }
        else{
            printf("last commit ID: %s\n", lines);
        }
        index++;
    }
    fclose(f);
    address = gitFolder();
    address = connectTwoString(address, "//config//branch//current");
    f = fopen(address, "r");
    if(f==NULL){
        printf("an unkown problem!\n");
        exit(-1);
    }
    fscanf(f, "%s", lines);
    printf("HEAD is on: %s\n", lines);
    fclose(f);
}
folder extract_data_from_commit(char* name, char* address_folder_info){
    folder temp;
    strcpy(temp.name, name);
    FILE* f = fopen(connectTwoString(address_folder_info, "\\massage"), "r");
    char line[200];
    fscanf(f, "%[^\n]s", line);
    strcpy(temp.massage, line);
    fclose(f);
    f = fopen(connectTwoString(address_folder_info, "\\name"), "r");
    fscanf(f, "%[^\n]s", line);
    strcpy(temp.user_name, line);
    fclose(f);
    f = fopen(connectTwoString(address_folder_info, "\\email"), "r");
    fscanf(f, "%[^\n]s", line);
    strcpy(temp.email, line);
    fclose(f);
    f = fopen(connectTwoString(address_folder_info, "\\parent"), "r");
    int number = 0;
    fscanf(f, "%d", &number);
    temp.parent = number;
    fclose(f);
    f = fopen(connectTwoString(address_folder_info, "\\branch"), "r");
    fscanf(f, "%[^\n]s", line);
    strcpy(temp.banch, line);
    fclose(f);
    f = fopen(connectTwoString(address_folder_info, "\\count"), "r");
    int directory = 0, file = 0;
    fscanf(f, "%d %d", &directory, &file);
    temp.count_file = file; temp.count_folder = directory;
    fclose(f);
    f = fopen(connectTwoString(address_folder_info, "\\date"), "r");
    unsigned long long year = 0, month = 0, day = 0, h = 0, m = 0, s = 0, total = 0;
    fscanf(f, "%llu %llu %llu %llu %llu %llu", &year, &month, &day, &h, &m, &s);
    total = s + 60*m + 60*60*h + 60*60*24*day + 4000000llu * month + 4000000000llu * year;
    temp.time = total;
    temp.next = temp.perv = NULL;
    fclose(f);
    return temp;
}
folder* log_conditional(parametrs a, char(*function)(folder, parametrs)){
    folder* list = (folder*)calloc(1, sizeof(folder));
    list->next = NULL;
    list->perv = NULL;
    list->count_file = 0;
    list->count_folder = 0;
    list->time = 0;
    strcpy(list->banch, "");
    strcpy(list->email, "");
    strcpy(list->massage, "");
    strcpy(list->name, "");
    strcpy(list->user_name, "");
    list->parent = 0;
    char* address = gitFolder();
    address = absolute_address_neogit();
    address = connectTwoString(address, "\\commits");
    //printf("%s", address);
    DIR* dir;
    dir = opendir(address);
    struct dirent* entry;
    if(dir == NULL){
        printf("unable to open %s directory\n", address);
        return list;
    }
    folder ff;
    while ((entry = readdir(dir)) != NULL){
        if(!strcheck(entry->d_name, 'i') && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            ff = extract_data_from_commit(entry->d_name, connectTwoString(address, connectTwoString("\\", connectTwoString(entry->d_name, "_info"))));
            folder* temp = list;
            if(!(*function)(ff, a)){
                continue;
            }
            while(temp->next){
                temp = temp->next;
            }
            temp->next = (folder*)calloc(1, sizeof(folder));
            temp->next->next = NULL;
            temp->next->perv = temp;
            temp = temp->next;
            temp->count_file = ff.count_file;
            temp->count_folder = ff.count_folder;
            temp->time = ff.time;
            strcpy(temp->banch, ff.banch);
            strcpy(temp->email, ff.email);
            strcpy(temp->massage, ff.massage);
            strcpy(temp->name, ff.name);
            strcpy(temp->user_name, ff.user_name);
            temp->parent = ff.parent;
        }
    }
    return list;
}
folder** neogitLOG(char(*SORT_function)(folder*, folder*), char(*TO_BE_IN_LIST_function)(folder, parametrs), parametrs TO_BE_IN_LIST_union){
    folder* c = log_conditional(TO_BE_IN_LIST_union, TO_BE_IN_LIST_function);
    unsigned long long count = 0;
    folder* b = c;
    while(b->next){
        count++;
        b = b->next;
    }
    folder ** list = (folder**)calloc(count + 2, sizeof(folder*));
    if(count == 0){
        return list;
    }
    b = c;
    b = b->next;
    for(unsigned long long i = 0; i < count; i++){
        list[i] = b;
        b = b->next;
    }
    for(unsigned long long i = 0; i < count; i++){
        for(unsigned long long j = i+1; j < count; j++){
            if(!SORT_function(list[i], list[j])){
                folder * temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    return list;
}
char TwoFileAreSame(char* address1, char* address2){
    char command[300];
    if(check_type(address1) != -1 || check_type(address2) != -1){
        return 0;
    }
    sprintf(command, "fc /b \"%s\" \"%s\" > ___temp___.Oneogit", address1, address2);
    system(command);
    FILE* f = fopen("___temp___.Oneogit", "r");
    char temp[300];
    fgets(temp, 299, f);
    fgets(temp, 299, f);
    fclose(f);
    remove("___temp___.Oneogit");
    if(strstr(temp, "no differences encountered")){
        return 1;
    }
    return 0;
}
void status_a(){
    DIR* dir;
    dir = opendir(".");
    struct dirent* entry;
    if(dir == NULL){
        printf("unable to open %s directory\n", "current");
        return;
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".neogit")){
            struct address__ address = Help_ADD(entry->d_name);
            char* address_stage = connectTwoString(address.adress_stage_file, entry->d_name);
            char* address_file = (char*)calloc(3, sizeof(char));
            address_file[0] = '\0';
            for(int i = 0; i < address.size_address_cmd; i++){
                address_file = connectTwoString(address_file, connectTwoString(address.address_cmd[i], "\\"));
            }
            address_file = connectTwoString(address_file, entry->d_name);
            char* address_commit = (char*)calloc(3, sizeof(char));
            address_commit[0] = '\0';
            for(int i = 0; i < address.size_address_neogit; i++){
                address_commit = connectTwoString(address_commit, connectTwoString(address.address_neogit[i], "\\"));
            }
            address_commit = connectTwoString(address_commit, ".neogit\\commits\\");
            char temp[100];
            sprintf(temp, "%d", get_last_hash('a'));
            address_commit = connectTwoString(address_commit, temp);
            for(int i = address.size_address_neogit; i < address.size_address_cmd; i++){
                address_commit = connectTwoString(address_commit, connectTwoString("\\", address.address_cmd[i]));
            }
            address_commit = connectTwoString(address_commit, connectTwoString("\\", entry->d_name));
            char isInstage = check_type(address_stage);
            char isInReal = check_type(address_file);
            char isInCommit = check_type(address_commit);
            if(isInReal == -1){
                printf("%s:\tW: %d, S: %d, C: %d\t####\tcompare: W-S: %d, W-C: %d, S-C: %d\n",entry->d_name ,(isInReal == -1)? 1:0, (isInstage == -1)?1:0, (isInCommit==-1)?1:0, TwoFileAreSame(address_file,address_stage), TwoFileAreSame(address_file, address_commit), TwoFileAreSame(address_stage,address_commit));
            }
            if(isInReal == 1){
                printf("%s\\:\tW: %d, S: %d, C: %d\n",entry->d_name ,(isInReal == 1)? 1:0, (isInstage == 1)?1:0, (isInCommit==1)?1:0);
            }
        }
    }
    struct address__ addressA = Help_ADD("");
    char* address_stageA = addressA.adress_stage_file;
    dir = opendir(address_stageA);
    char flag = 1;
    if(dir == NULL){
        flag = 0;
    }
    if(flag){
        while ((entry = readdir(dir)) != NULL){
            if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".neogit")){
                struct address__ address = Help_ADD(entry->d_name);
                char* address_stage = connectTwoString(address.adress_stage_file, entry->d_name);
                char* address_file = (char*)calloc(3, sizeof(char));
                address_file[0] = '\0';
                for(int i = 0; i < address.size_address_cmd; i++){
                    address_file = connectTwoString(address_file, connectTwoString(address.address_cmd[i], "\\"));
                }
                address_file = connectTwoString(address_file, entry->d_name);
                char* address_commit = (char*)calloc(3, sizeof(char));
                address_commit[0] = '\0';
                for(int i = 0; i < address.size_address_neogit; i++){
                    address_commit = connectTwoString(address_commit, connectTwoString(address.address_neogit[i], "\\"));
                }
                address_commit = connectTwoString(address_commit, ".neogit\\commits\\");
                char temp[100];
                sprintf(temp, "%d", get_last_hash('a'));
                address_commit = connectTwoString(address_commit, temp);
                for(int i = address.size_address_neogit; i < address.size_address_cmd; i++){
                    address_commit = connectTwoString(address_commit, connectTwoString("\\", address.address_cmd[i]));
                }
                address_commit = connectTwoString(address_commit, connectTwoString("\\", entry->d_name));
                char isInstage = check_type(address_stage);
                char isInReal = check_type(address_file);
                char isInCommit = check_type(address_commit);
                if(isInstage == -1 && isInReal == 0){
                    printf("%s:\tW: %d, S: %d, C: %d\t####\tcompare: W-S: %d, W-C: %d, S-C: %d\n",entry->d_name ,(isInReal == -1)? 1:0, (isInstage == -1)?1:0, (isInCommit==-1)?1:0, TwoFileAreSame(address_file,address_stage), TwoFileAreSame(address_file, address_commit), TwoFileAreSame(address_stage,address_commit));
                }
                if(isInstage == 1 && isInReal == 0){
                    printf("%s\\:\tW: %d, S: %d, C: %d\n",entry->d_name ,(isInReal == 1)? 1:0, (isInstage == 1)?1:0, (isInCommit==1)?1:0);
                }
            }
        }
    }
    struct address__ addressB = Help_ADD("");
    char* address_commitB = (char*)calloc(3, sizeof(char));
    address_commitB[0] = '\0';
    for(int i = 0; i < addressB.size_address_neogit; i++){
        address_commitB = connectTwoString(address_commitB, connectTwoString(addressB.address_neogit[i], "\\"));
    }
    address_commitB = connectTwoString(address_commitB, ".neogit\\commits\\");
    char tempB[100];
    sprintf(tempB, "%d", get_last_hash('a'));
    address_commitB = connectTwoString(address_commitB, tempB);
    for(int i = addressB.size_address_neogit; i < addressB.size_address_cmd; i++){
        address_commitB = connectTwoString(address_commitB, connectTwoString("\\", addressB.address_cmd[i]));
    }
    dir = opendir(address_commitB);
    flag = 1;
    if(dir == NULL){
        flag = 0;
    }
    if(flag){
        while ((entry = readdir(dir)) != NULL){
            if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".neogit")){
                struct address__ address = Help_ADD(entry->d_name);
                char* address_stage = connectTwoString(address.adress_stage_file, entry->d_name);
                char* address_file = (char*)calloc(3, sizeof(char));
                address_file[0] = '\0';
                for(int i = 0; i < address.size_address_cmd; i++){
                    address_file = connectTwoString(address_file, connectTwoString(address.address_cmd[i], "\\"));
                }
                address_file = connectTwoString(address_file, entry->d_name);
                char* address_commit = (char*)calloc(3, sizeof(char));
                address_commit[0] = '\0';
                for(int i = 0; i < address.size_address_neogit; i++){
                    address_commit = connectTwoString(address_commit, connectTwoString(address.address_neogit[i], "\\"));
                }
                address_commit = connectTwoString(address_commit, ".neogit\\commits\\");
                char temp[100];
                sprintf(temp, "%d", get_last_hash('a'));
                address_commit = connectTwoString(address_commit, temp);
                for(int i = address.size_address_neogit; i < address.size_address_cmd; i++){
                    address_commit = connectTwoString(address_commit, connectTwoString("\\", address.address_cmd[i]));
                }
                address_commit = connectTwoString(address_commit, connectTwoString("\\", entry->d_name));
                char isInstage = check_type(address_stage);
                char isInReal = check_type(address_file);
                char isInCommit = check_type(address_commit);
                if(isInCommit == -1 && isInReal == 0 && isInstage == 0){
                    printf("%s:\tW: %d, S: %d, C: %d\t####\tcompare: W-S: %d, W-C: %d, S-C: %d\n",entry->d_name ,(isInReal == -1)? 1:0, (isInstage == -1)?1:0, (isInCommit==-1)?1:0, TwoFileAreSame(address_file,address_stage), TwoFileAreSame(address_file, address_commit), TwoFileAreSame(address_stage,address_commit));
                }
                if(isInCommit == 1 && isInReal == 0 && isInstage == 0){
                    printf("%s\\:\tW: %d, S: %d, C: %d\n",entry->d_name ,(isInReal == 1)? 1:0, (isInstage == 1)?1:0, (isInCommit==1)?1:0);
                }
            }
        }
    }
}
//End of main functions

int main(int argc, char* argv[]){
    //get inputs        #############################
    int len = argc;
    char** input = tokenizeInput(&len, argv);
    //end of getting    #############################

    //test
    // printf("%d ||", len);
    // for (int i = 0; i < len; i++){
    //     printf("%s||", input[i]);
    // }

    // neogit config -global user.name
    if(equalStrings(input[1], "config") && equalStrings(input[2], "-global") && equalStrings(input[3], "user.name") && strcmp(input[4], "") && equalStrings(input[5], "") && len == 5)
        changeNameGlobal(input[4]);
    // neogit config -global user.email
    if(equalStrings(input[1], "config") && equalStrings(input[2], "-global") && equalStrings(input[3], "user.email") && strcmp(input[4], "") && equalStrings(input[5], "") && len == 5)
        changeEmailGlobal(input[4]);
    // neogit config user.name
    if(equalStrings(input[1], "config") && equalStrings(input[2], "user.name") && strcmp(input[3], "") && equalStrings(input[4], "") && len == 4)
        changeName(input[3]);
    // neogit config user.email
    if(equalStrings(input[1], "config") && equalStrings(input[2], "user.email") && strcmp(input[3], "") && equalStrings(input[4], "") && len == 4)
        changeEmail(input[3]);
    //neogit config -gelobal alias.name "command"
    if(equalStrings(input[1], "config") && equalStrings(input[2], "-global") && (input[3][0] == 'a' && input[3][1] == 'l' && input[3][2] == 'i' && input[3][3] == 'a' && input[3][4] == 's' && input[3][5] == '.' && strlen(input[3]) > 6) && strcmp(input[4], "") && equalStrings(input[5], "") && len == 5){       
        if(strlen(input[4]) > 250){
            printf("Your command is too long!\n");
            exit(-1);
        }
        if(strcheck(input[4], '\"')){
            printf("Your command is invalid!\n");
            exit(-1);
        }
        GlobalAlias(input[3]+6, delete_spaces(input[4]));
    }
    //neogit config alias.name "command"
    if(equalStrings(input[1], "config") && (input[2][0] == 'a' && input[2][1] == 'l' && input[2][2] == 'i' && input[2][3] == 'a' && input[2][4] == 's' && input[2][5] == '.' && strlen(input[2]) > 6) && strcmp(input[3], "") && equalStrings(input[4], "") && len == 4){       
        if(strlen(input[3]) > 250){
            printf("Your command is too long!\n");
            exit(-1);
        }
        if(strcheck(input[3], '\"')){
            printf("Your command is invalid!\n");
            exit(-1);
        }
        Alias(input[2]+6, delete_spaces(input[3]));
    }
    //neogit init
    if(equalStrings(input[1], "init") && equalStrings(input[2], "") && len == 2)
        init();
    //neogit add
    if(equalStrings(input[1], "add") && strcmp(input[2], "") && !strcheck(input[2] , '-') && equalStrings(input[3], "") && len == 3){
        if(strlen(input[2]) > 250){
            printf("Your command is too long!\n");
            exit(-1);
        }
        if(strcheck(input[2], '\"')){
            printf("Your command is invalid!\n");
            exit(-1);
        }
        if(strstr(input[2], ".neogit") == input[2]){
            exit(0);
        }
        if(!strcmp(input[2], ".")){
            system("neogit add *");
            exit(0);
        }
        add(input[2]);
    }
    //neogit add *
    if(equalStrings(input[1], "add") && strcmp(input[2], "") && !strcheck(input[2] , '-') && len > 3){
        gitFoldeerCheck(".neogit", 0, getLevelofAddress(GetAddressHere()));
        for(int i = 2; i < len; i++){
            if(strlen(input[i]) > 250){
                printf("Your path is too long!\n");
                exit(-1);
            }
            if(strcheck(input[i], '\"')){
                printf("Your path is invalid!\n");
                exit(-1);
            }
            char cc[1000];
            sprintf(cc, "neogit add \"%s\"", input[i]);
            system(cc);
        }
        exit(0);
    }
    //neogit add -f
    if(equalStrings(input[1], "add") && equalStrings(input[2], "-f") && strcmp(input[3], "") && len >= 4){
        gitFoldeerCheck(".neogit", 0, getLevelofAddress(GetAddressHere()));
        for(int i = 3; i < len; i++){
            if(strlen(input[i]) > 250){
                printf("Your path is too long!\n");
                exit(-1);
            }
            if(strcheck(input[i], '\"')){
                printf("Your path is invalid!\n");
                exit(-1);
            }
            char cc[1000];
            sprintf(cc, "neogit add \"%s\"", input[i]);
            system(cc);
        }
        exit(0);
    }
    //neogit rest
    if(equalStrings(input[1], "reset") && strcmp(input[2], "") && !strcheck(input[2] , '-') && equalStrings(input[3], "") && len == 3){
        if(strlen(input[2]) > 250){
            printf("Your command is too long!\n");
            exit(-1);
        }
        if(strcheck(input[2], '\"')){
            printf("Your command is invalid!\n");
            exit(-1);
        }
        if(strstr(input[2], ".neogit") == input[2]){
            exit(0);
        }
        if(!strcmp(input[2], ".")){
            system("neogit reset *");
            exit(0);
        }
        rest(input[2]);
    }
    //neogit rest name*
    if(equalStrings(input[1], "reset") && strcmp(input[2], "") && !strcheck(input[2] , '-') && len > 3){
        gitFoldeerCheck(".neogit", 0, getLevelofAddress(GetAddressHere()));
        for(int i = 2; i < len; i++){
            if(strlen(input[i]) > 250){
                printf("Your path is too long!\n");
                exit(-1);
            }
            if(strcheck(input[i], '\"')){
                printf("Your path is invalid!\n");
                exit(-1);
            }
            char cc[1000];
            sprintf(cc, "neogit reset \"%s\"", input[i]);
            system(cc);
        }
        exit(0);
    }

    //neogit reset -f
    if(equalStrings(input[1], "reset") && equalStrings(input[2], "-f") && strcmp(input[3], "") && len >= 4){
        gitFoldeerCheck(".neogit", 0, getLevelofAddress(GetAddressHere()));
        for(int i = 3; i < len; i++){
            if(strlen(input[i]) > 250){
                printf("Your path is too long!\n");
                exit(-1);
            }
            if(strcheck(input[i], '\"')){
                printf("Your path is invalid!\n");
                exit(-1);
            }
            char cc[1000];
            sprintf(cc, "neogit reset \"%s\"", input[i]);
            system(cc);
        }
        exit(0);
    }
    //reset -undo
    if(equalStrings(input[1], "reset") && equalStrings(input[2], "-undo") && len == 3)
        Undo();
    //add -n option
    if(equalStrings(input[1], "___check_if_a_file_is_in_stage__")){
        if(!strcmp(input[3], "1"))
            checkFileInStage(input[2], 1);
        else
            checkFileInStage(input[2], -1);
    }
    //add -n death (death > 1)
    if(equalStrings(input[1], "add") && equalStrings(input[2], "-n") && strcmp(input[3], "") && len == 4){
        int death = atoi(input[3]);
        if(death <= 0){
            printf("invalid death!\n");
            exit(1);
        }
        addNDeath(".", death);
        exit(0);
    }
    //commit
    if(equalStrings(input[1], "commit") && !equalStrings(input[2], "-m") && !equalStrings(input[2], "-s")){
        printf("you must write a massage to commit. (use -m or -s)\n");
        exit(0);
    }
    if(equalStrings(input[1], "commit") && equalStrings(input[2], "-m")){
        if(len > 4){
            printf("lots of inputs!\n");
            exit(0);
        }
        if(len == 3){
            printf("you must write a massage to commit.\n");
            exit(0);
        }
        if(strlen(input[3]) > 72){
            printf("yor commit massage is too long\n");
            exit(0);
        }
        commit(input[3]);
    }
    //shortcuts in commits
    if(equalStrings(input[1], "set") && equalStrings(input[2] , "-m") && strcmp(input[3], "") && equalStrings(input[4] , "-s") && strcmp(input[5], "") && len == 6){
        if(strlen(input[3]) > 72 || strlen(input[5]) > 40){
            printf("Yor text is too long!\n");
            exit(0);
        }
        add_shortcut_massage(input[5], input[3]);
        printf("shortcut added successfully\n");
        exit(0);
    }
    if(equalStrings(input[1], "remove") && equalStrings(input[2] , "-s") && strcmp(input[3], "") && len == 4){
        delete_shortcut_massage(input[3]);
        printf("shortcut deleted successfully\n");
        exit(0);
    }
    if(equalStrings(input[1], "replace") && equalStrings(input[2] , "-m") && strcmp(input[3], "") && equalStrings(input[4] , "-s") && strcmp(input[5], "") && len == 6){
        delete_shortcut_massage(input[5]);
        add_shortcut_massage(input[5], input[3]);
        printf("shortcut replaced successfully\n");
        exit(0);
    }
    if(equalStrings(input[1], "commit") && equalStrings(input[2], "-s") && strcmp(input[3], "") && len == 4){
        char* massage = extract_massage_shortcut(input[3]);
        if(massage[0] == 0){
            printf("this name of shortcut is not currently exist.\n");
            exit(0);  
        }
        char temp[150];
        sprintf(temp, "neogit commit -m \"%s\"", massage);
        system(temp);
        exit(0);
    }
    //create a branch
    if(equalStrings(input[1], "branch") && strcmp(input[2], "") && len ==3){
        create_new_branch(input[2]);
        exit(0);
    }
    if(equalStrings(input[1], "branch") && len == 2){
        show_listOfAllBranches();
        exit(0);
    }
    //neogit log
    if(equalStrings(input[1], "log") && len == 2){
        parametrs condition;
        folder** list = neogitLOG(timeUpToDown, beInList_normal, condition);
        if(list[0] == NULL){
            printf("No commit history.\n");
            exit(0);
        }
        for(int i = 0; list[i] != NULL; i++){
            printf("%d: ID: %s, branch: \"%s\", massage: \"%s\", user name: \"%s\", user email: \"%s\"\n",i + 1, list[i]->name,list[i]->banch, list[i]->massage, list[i]->user_name, list[i]->email);
            printf("count of file(s): %d, count of directory(s): %d, time of commit: ", list[i]->count_file, list[i]->count_folder); print_time(list[i]->time); printf("\n");
        }
        exit(0);
    }
    if(equalStrings(input[1], "log") && equalStrings(input[2], "-n") && strcmp(input[3], "") && len == 4){
        int number = atoi(input[3]);
        if(number <= 0){
            printf("Invalid number!\n");
            exit(-1);
        }
        parametrs condition;
        folder** list = neogitLOG(timeUpToDown, beInList_normal, condition);
        if(list[0] == NULL){
            printf("No commit history.\n");
            exit(0);
        }
        for(int i = 0; list[i] != NULL && number > 0; i++){
            printf("%d: ID: %s, branch: \"%s\", massage: \"%s\", user name: \"%s\", user email: \"%s\"\n",i + 1, list[i]->name,list[i]->banch, list[i]->massage, list[i]->user_name, list[i]->email);
            printf("count of file(s): %d, count of directory(s): %d, time of commit: ", list[i]->count_file, list[i]->count_folder); print_time(list[i]->time); printf("\n");
            number--;
        }
        exit(0);
    }
    if(equalStrings(input[1], "log") && equalStrings(input[2], "-branch") && strcmp(input[3], "") && len == 4){
        parametrs condition;
        strcpy(condition.string, input[3]);
        if(!is_banchName_exist(input[3])){
            printf("%s is not in branch list. you can create it.\n", input[3]);
            exit(0);
        }
        folder** list = neogitLOG(timeUpToDown, beInList_InBranch, condition);
        if(list[0] == NULL){
            printf("No commit history in this branch (%s).\n", input[3]);
            exit(0);
        }
        for(int i = 0; list[i] != NULL; i++){
            printf("%d: ID: %s, branch: \"%s\", massage: \"%s\", user name: \"%s\", user email: \"%s\"\n",i + 1, list[i]->name,list[i]->banch, list[i]->massage, list[i]->user_name, list[i]->email);
            printf("count of file(s): %d, count of directory(s): %d, time of commit: ", list[i]->count_file, list[i]->count_folder); print_time(list[i]->time); printf("\n");
        }
        exit(0);
    }
    if(equalStrings(input[1], "log") && equalStrings(input[2], "-author") && strcmp(input[3], "") && len == 4){
        parametrs condition;
        strcpy(condition.string, input[3]);
        folder** list = neogitLOG(timeUpToDown, beInList_InAuthor, condition);
        if(list[0] == NULL){
            printf("No commit history with this author (%s).\n", input[3]);
            exit(0);
        }
        for(int i = 0; list[i] != NULL; i++){
            printf("%d: ID: %s, branch: \"%s\", massage: \"%s\", user name: \"%s\", user email: \"%s\"\n",i + 1, list[i]->name,list[i]->banch, list[i]->massage, list[i]->user_name, list[i]->email);
            printf("count of file(s): %d, count of directory(s): %d, time of commit: ", list[i]->count_file, list[i]->count_folder); print_time(list[i]->time); printf("\n");
        }
        exit(0);
    }
    if(equalStrings(input[1], "log") && equalStrings(input[2], "-since") && strcmp(input[3], "") && len == 4){
        parametrs condition;
        unsigned long long year = 0, month = 0, day = 0, h  = 0, m = 0, s = 0, total = 0;
        sscanf(input[3], "%llu/%llu/%llu-%llu:%llu:%llu", &year, &month, &day, &h, &m, &s);
        total = s + 60*m + 60*60*h + 60*60*24*day + 4000000llu * month + 4000000000llu * year;
        condition.number_llu = total;
        folder** list = neogitLOG(timeUpToDown, beInList_since, condition);
        if(list[0] == NULL){
            printf("No commit history since ");print_time(total); printf(".\n");
            exit(0);
        }
        for(int i = 0; list[i] != NULL; i++){
            printf("%d: ID: %s, branch: \"%s\", massage: \"%s\", user name: \"%s\", user email: \"%s\"\n",i + 1, list[i]->name,list[i]->banch, list[i]->massage, list[i]->user_name, list[i]->email);
            printf("count of file(s): %d, count of directory(s): %d, time of commit: ", list[i]->count_file, list[i]->count_folder); print_time(list[i]->time); printf("\n");
        }
        exit(0);
    }
    if(equalStrings(input[1], "log") && equalStrings(input[2], "-before") && strcmp(input[3], "") && len == 4){
        parametrs condition;
        unsigned long long year = 0, month = 0, day = 0, h  = 0, m = 0, s = 0, total = 0;
        sscanf(input[3], "%llu/%llu/%llu-%llu:%llu:%llu", &year, &month, &day, &h, &m, &s);
        total = s + 60*m + 60*60*h + 60*60*24*day + 4000000llu * month + 4000000000llu * year;
        condition.number_llu = total;
        folder** list = neogitLOG(timeUpToDown, beInList_before, condition);
        if(list[0] == NULL){
            printf("No commit history before ");print_time(total); printf(".\n");
            exit(0);
        }
        for(int i = 0; list[i] != NULL; i++){
            printf("%d: ID: %s, branch: \"%s\", massage: \"%s\", user name: \"%s\", user email: \"%s\"\n",i + 1, list[i]->name,list[i]->banch, list[i]->massage, list[i]->user_name, list[i]->email);
            printf("count of file(s): %d, count of directory(s): %d, time of commit: ", list[i]->count_file, list[i]->count_folder); print_time(list[i]->time); printf("\n");
        }
        exit(0);
    }
    if(equalStrings(input[1], "log") && equalStrings(input[2], "-search") && strcmp(input[3], "") && len >= 4){
        char** text = (char**)calloc(((unsigned long long)len - 2), sizeof(char*));
        for(int i = 0; i < len - 3; i++){
            text[i] = input[i+3];
        }
        parametrs condition;
        condition.list = text;
        folder** list = neogitLOG(timeUpToDown, beInList_search, condition);
        if(list[0] == NULL){
            printf("No commit history with this condition\n");
            exit(0);
        }
        for(int i = 0; list[i] != NULL; i++){
            printf("%d: ID: %s, branch: \"%s\", massage: \"%s\", user name: \"%s\", user email: \"%s\"\n",i + 1, list[i]->name,list[i]->banch, list[i]->massage, list[i]->user_name, list[i]->email);
            printf("count of file(s): %d, count of directory(s): %d, time of commit: ", list[i]->count_file, list[i]->count_folder); print_time(list[i]->time); printf("\n");
        }
        exit(0);
    }
    //neogit status
    if(equalStrings(input[1], "status") && equalStrings(input[2], "-a") && len == 3){
        status_a();
    }
    return 0;
}