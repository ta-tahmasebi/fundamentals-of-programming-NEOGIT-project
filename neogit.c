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
            printf("not a neogit repository (or any of the parent directories): .neogit");
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
        FILE* f = fopen(".____neogit_temp", "r");
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
        printf("Initialized empty neogit repository\n");
    }
    else{
        printf("an unkown problem!\n");
        exit(-1);
    }
}
char check_type(char* name){ // 1 -> folder 0-> not found  -1->file
    if(!system("echo A > .____neogit_temp")){
        if(!system(connectTwoString("if exist \"", connectTwoString(name, "/*\" echo Q > .____neogit_temp")))){
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
                    FILE* f = fopen(".____neogit_temp", "r");
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
}
void add(char *name){
    char * address_stage = gitFolder();
    char mode = check_type(name);
    if(!mode){
        printf("file not found!");
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
        FILE* f = fopen(".____neogit_temp", "r");
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
    if(mode == -1){
        char* command = (char*)calloc(10000,sizeof(char));
        sprintf(command, "if not exist \"%s\\*\" mkdir \"%s\"", dis, dis);
        if(!system(command)){
            FILE* f = fopen(".__E__neogit_temp.bat", "w");
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
            FILE* f = fopen(".__E__neogit_temp.bat", "w");
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

//End of main functions

int main(int argc, char* argv[]){
    //get inputs        #############################
    int len = argc;
    char** input = tokenizeInput(&len, argv);
    //end of getting    #############################

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
    if(equalStrings(input[1], "add") && strcmp(input[2], "") && equalStrings(input[3], "") && len == 3){
        if(strlen(input[2]) > 250){
            printf("Your command is too long!\n");
            exit(-1);
        }
        if(strcheck(input[2], '\"')){
            printf("Your command is invalid!\n");
            exit(-1);
        }
        add(input[2]);
    }





    // printf("%d", len);
    // for (int i = 0; i < len; i++){
    //     printf("%s||", input[i]);
    // }
    return 0;
}