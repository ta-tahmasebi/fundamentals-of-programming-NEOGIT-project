#include<conio.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "neogitV1.c"

void check_near_main(){
    char address[500];
    strcpy(address, absolute_address_neogit());
    address[strlen(address) - 8] = 0;
    char s [500];
    getcwd(s, 499);
    if(strcmp(s, address)){
        printf("\033[33mfirst cd in main folder of project.\033[0m\n");
        exit(0);
    }
}
//grep and diff
char compare_two_tokenized_string(char** line1, char** line2, int* number1, int* number2, int i, char* name1, char* name2){
    if(line1 == NULL){
        system("neogit print_double_write_L__");
        printf("\033[94m%s\033[0m-%d\n\033[96mNULL\033[0m\n\033[94m%s\033[0m-%d\n", name1, number1[i], name2, number2[i]);
        printf("\033[33m");
        for(int j = 0; line2[j] != NULL; j++){
            printf("%s ", line2[j]);
        }
        printf("\033[0m\n");
        system("neogit print_double_write_R__");
        printf("\n");
    }
    else if(line2 == NULL){
        system("neogit print_double_write_L__");
        printf("\033[94m%s\033[0m-%d\n\033[96m", name1, number1[i]);
        for(int j = 0; line1[j] != NULL; j++){
            printf("%s ", line1[j]);
        }
        printf("\033[0m\n\033[94m%s\033[0m-%d\n", name2, number2[i]);
        printf("\033[33mNULL");
        printf("\033[0m\n");
        system("neogit print_double_write_R__");
        printf("\n");
    }
    else{
        int count1 = 0, count2 = 0;
        for(int j = 0; line1[j] != NULL; j++){
            count1++;
        }
        for(int j = 0; line2[j] != NULL; j++){
            count2++;
        }
        if(count1 != count2){
            system("neogit print_double_write_L__");
            printf("\033[94m%s\033[0m-%d\n\033[96m", name1, number1[i]);
            for(int j = 0; line1[j] != NULL; j++){
                printf("%s ", line1[j]);
            }
            printf("\033[0m\n\033[94m%s\033[0m-%d\n", name2, number2[i]);
            printf("\033[33m");
            for(int j = 0; line2[j] != NULL; j++){
                printf("%s ", line2[j]);
            }
            printf("\033[0m\n");
            system("neogit print_double_write_R__");
            printf("\n");
        }
        else{
            int count = 0;
            int index = 0;
            for(int j = 0; j < count1; j++){
                if(strcmp(line1[j], line2[j])){
                    index = j;
                    count++;
                }
            }
            if(count == 0){
                return 1;
            }
            if(count > 1){
                system("neogit print_double_write_L__");
                printf("\033[94m%s\033[0m-%d\n\033[96m", name1, number1[i]);
                for(int j = 0; line1[j] != NULL; j++){
                    printf("%s ", line1[j]);
                }
                printf("\033[0m\n\033[94m%s\033[0m-%d\n", name2, number2[i]);
                printf("\033[33m");
                for(int j = 0; line2[j] != NULL; j++){
                    printf("%s ", line2[j]);
                }
                printf("\033[0m\n");
                system("neogit print_double_write_R__");
                printf("\n");
            }
            if(count == 1){
                system("neogit print_double_write_L__");
                printf("\033[94m%s\033[0m-%d\n\033[96m", name1, number1[i]);
                for(int j = 0; line1[j] != NULL; j++){
                    if(j == index) system("neogit print_double_write_R__M");
                    if(index == j) printf("%s", line1[j]);
                    else printf("%s ", line1[j]);
                    if(j == index) {system("neogit print_double_write_L__M"); printf(" ");}                }
                printf("\033[0m\n\033[94m%s\033[0m-%d\n", name2, number2[i]);
                printf("\033[33m");
                for(int j = 0; line2[j] != NULL; j++){
                    if(j == index) system("neogit print_double_write_R__M");
                    if(index == j) printf("%s", line2[j]);
                    else printf("%s ", line2[j]);
                    if(j == index) {system("neogit print_double_write_L__M"); printf(" ");}
                }
                printf("\033[0m\n");
                system("neogit print_double_write_R__");
                printf("\n");
            }
        }
    }
    return 0;
}


void print_double_write_L(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L"%s\n", L"«««««");
    exit(0);
}
void print_double_write_LM(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L"%s", L"«");
    exit(0);
}
void print_double_write_R(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L"%s", L"»»»»»");
    exit(0);
}
void print_double_write_RM(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L"%s", L"»");
    exit(0);
}
void Help_checkAllFiles_compare_commits(char* address1, char* address2, int id1, int id2){
    if(address1[0] == 0){
        address1 = absolute_address_neogit();
        address1 = connectTwoString(address1, "\\commits\\");
        char temp[10];
        sprintf(temp, "%d", id1);
        address1 = connectTwoString(address1, temp);
        address2 = absolute_address_neogit();
        address2 = connectTwoString(address2, "\\commits\\");
        sprintf(temp, "%d", id2);
        address2 = connectTwoString(address2, temp);
        //printf("%s %s\n", address1,address2);
        if(!check_type(address1) || !check_type(address2)){
            printf("\033[31minvalid ID\033[0m!\n");
            exit(0);
        }
    }
    char directiries[100][400];
    int numberdir = 0;
    char* address_free1;
    char* address_free2;
    DIR* dir;
    dir = opendir(address1);
    struct dirent* entry;
    if(dir == NULL){
        printf("\033[31munable to open %s directory\033[0m\n", address1);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free1 = connectTwoString(address1, "");
            address_free2 = connectTwoString(address2, "");
            char isDir1, isDir2;
            address_free1 = connectTwoString(address_free1, connectTwoString("\\", entry->d_name));
            address_free2 = connectTwoString(address_free2, connectTwoString("\\", entry->d_name));
            isDir1 = check_type(address_free1);
            isDir2 = check_type(address_free2);
            if(isDir1 == 1){
                if(isDir2 != 1){
                    char* a = strstr(address_free1, "\\.neogit\\commits\\");
                    a = a + 23;
                    printf("\033[94m%s\\\033[0m is in commit \033[94m%d\033[0m but it is \033[31mnot\033[0m in commit \033[94m%d\033[0m\n", a, id1, id2);
                    continue;
                }
                strcpy(directiries[numberdir], address_free1);
                numberdir++;
            }
            else{
                char* a = strstr(address_free1, "\\.neogit\\commits\\");
                a = a + 23;
                if(isDir2 != -1){
                    printf("\033[94m%s\033[0m is in commit \033[94m%d\033[0m but it is \033[31mnot\033[0m in commit \033[94m%d\033[0m\n", a, id1, id2);
                    continue;
                }
                printf("comparing \033[94m%s\033[0m in commit \033[94m%d\033[0m and commit \033[94m%d\033[0m:\n", a, id1, id2);
                char temp[200];
                sprintf(temp, "neogit diff -f \"%s\" \"%s\"", address_free1, address_free2);
                system(temp);
            }
        }
    }
    closedir(dir);
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        char* name = connectTwoString(directiries[i], "");
        char* temp = strstr(name, ".neogit\\commits\\");
        temp = temp + 16;
        sprintf(temp, "%d", id2);
        temp[strlen(temp)] = '\\';
        Help_checkAllFiles_compare_commits(directiries[i], name, id1, id2);
    }
}
void Help_checkAllFiles_compare_commits2(char* address1, char* address2, int id1, int id2){
    if(address1[0] == 0){
        address1 = absolute_address_neogit();
        address1 = connectTwoString(address1, "\\commits\\");
        char temp[10];
        sprintf(temp, "%d", id1);
        address1 = connectTwoString(address1, temp);
        address2 = absolute_address_neogit();
        address2 = connectTwoString(address2, "\\commits\\");
        sprintf(temp, "%d", id2);
        address2 = connectTwoString(address2, temp);
        //printf("%s %s\n", address1,address2);
        if(!check_type(address1) || !check_type(address2)){
            printf("\033[31minvalid ID\033[0m!\n");
            exit(0);
        }
    }
    char directiries[100][400];
    int numberdir = 0;
    char* address_free1;
    char* address_free2;
    DIR* dir;
    dir = opendir(address1);
    struct dirent* entry;
    if(dir == NULL){
        printf("\033[31munable to open %s directory\033[0m\n", address1);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free1 = connectTwoString(address1, "");
            address_free2 = connectTwoString(address2, "");
            char isDir1, isDir2;
            address_free1 = connectTwoString(address_free1, connectTwoString("\\", entry->d_name));
            address_free2 = connectTwoString(address_free2, connectTwoString("\\", entry->d_name));
            isDir1 = check_type(address_free1);
            isDir2 = check_type(address_free2);
            if(isDir1 == 1){
                if(isDir2 != 1){
                    char* a = strstr(address_free1, "\\.neogit\\commits\\");
                    a = a + 23;
                    printf("\033[94m%s\\\033[0m is in commit \033[94m%d\033[0m but it is \033[31mnot\033[0m in commit \033[94m%d\033[0m\n", a, id1, id2);
                    continue;
                }
                strcpy(directiries[numberdir], address_free1);
                numberdir++;
            }
            else{
                char* a = strstr(address_free1, "\\.neogit\\commits\\");
                a = a + 23;
                if(isDir2 != -1){
                    printf("\033[94m%s\033[0m is in commit \033[94m%d\033[0m but it is \033[31mnot\033[0m in commit \033[94m%d\033[0m\n", a, id1, id2);
                    continue;
                }
            }
        }
    }
    closedir(dir);
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        char* name = connectTwoString(directiries[i], "");
        char* temp = strstr(name, ".neogit\\commits\\");
        temp = temp + 16;
        sprintf(temp, "%d", id2);
        temp[strlen(temp)] = '\\';
        Help_checkAllFiles_compare_commits2(directiries[i], name, id1, id2);
    }
}
void compare_two_commit(int ID1, int ID2){
    Help_checkAllFiles_compare_commits("", "", ID1, ID2);
    Help_checkAllFiles_compare_commits2("", "", ID2, ID1);
}
char check_if_word_in_line(char* word, char* line){
    char** text = delete_spaces(line);
    int is = 0;
    for(int i = 0; text[i] != NULL; i++){
        if(strmatchWildcard(text[i], word, strlen(text[i]), strlen(word))){
            is = 1;
            break;
        }
    }
    if(!is){
        return 0;
    }
    for(int i = 0; text[i] != NULL; i++){
        if(!strmatchWildcard(text[i], word, strlen(text[i]), strlen(word))){
            printf("\033[96m%s \033[0m", text[i]);
        }
        else{
            printf("\033[33m%s \033[0m", text[i]);
        }
    }
    printf("\n");
    return 1;
}
char check_if_word_in_line_n(char* word, char* line, int l){
    char** text = delete_spaces(line);
    int is = 0;
    for(int i = 0; text[i] != NULL; i++){
        if(strmatchWildcard(text[i], word, strlen(text[i]), strlen(word))){
            is = 1;
            break;
        }
    }
    if(!is){
        return 0;
    }
    printf("%d: ", l);
    for(int i = 0; text[i] != NULL; i++){
        if(!strmatchWildcard(text[i], word, strlen(text[i]), strlen(word))){
            printf("\033[96m%s \033[0m", text[i]);
        }
        else{
            printf("\033[33m%s \033[0m", text[i]);
        }
    }
    printf("\n");
    return 1;
}
void grep_n_commit(char* address1, int ID, char* word){
    if(address1[0] == 0){
        address1 = absolute_address_neogit();
        address1 = connectTwoString(address1, "\\commits\\");
        char temp[10];
        sprintf(temp, "%d", ID);
        address1 = connectTwoString(address1, temp);
        if(!check_type(address1)){
            printf("invalid ID!\n");
            exit(0);
        }
    }
    char directiries[100][400];
    int numberdir = 0;
    char* address_free1;
    DIR* dir;
    dir = opendir(address1);
    struct dirent* entry;
    if(dir == NULL){
        printf("unable to open %s directory\n", address1);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free1 = connectTwoString(address1, "");
            char isDir1;
            address_free1 = connectTwoString(address_free1, connectTwoString("\\", entry->d_name));
            isDir1 = check_type(address_free1);
            if(isDir1 == 1){
                strcpy(directiries[numberdir], address_free1);
                numberdir++;
            }
            else{
                char* a = strstr(address_free1, "\\.neogit\\commits\\");
                a = a + 23;
                printf("grep \033[94m%s\033[0m in commit \033[94m%d\033[0m (%s):\n", a, ID, word);
                char temp[200];
                sprintf(temp, "neogit grep -f \"%s\" -p \"%s\" -n", address_free1, word);
                system(temp);
            }
        }
    }
    closedir(dir);
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        grep_n_commit(directiries[i], ID, word);
    }
}
void grep_commit(char* address1, int ID, char* word){
    if(address1[0] == 0){
        address1 = absolute_address_neogit();
        address1 = connectTwoString(address1, "\\commits\\");
        char temp[10];
        sprintf(temp, "%d", ID);
        address1 = connectTwoString(address1, temp);
        if(!check_type(address1)){
            printf("invalid ID!\n");
            exit(0);
        }
    }
    char directiries[100][400];
    int numberdir = 0;
    char* address_free1;
    DIR* dir;
    dir = opendir(address1);
    struct dirent* entry;
    if(dir == NULL){
        printf("unable to open %s directory\n", address1);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free1 = connectTwoString(address1, "");
            char isDir1;
            address_free1 = connectTwoString(address_free1, connectTwoString("\\", entry->d_name));
            isDir1 = check_type(address_free1);
            if(isDir1 == 1){
                strcpy(directiries[numberdir], address_free1);
                numberdir++;
            }
            else{
                char* a = strstr(address_free1, "\\.neogit\\commits\\");
                a = a + 23;
                printf("grep \033[94m%s\033[0m in commit \033[94m%d\033[0m (%s):\n", a, ID, word);
                char temp[200];
                sprintf(temp, "neogit grep -f \"%s\" -p \"%s\"", address_free1, word);
                system(temp);
            }
        }
    }
    closedir(dir);
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        grep_commit(directiries[i], ID, word);
    }
}
//end of grep and diff

//hook
char isTodo(char* line, char mode){ //1 -> c,cpp 0->txt
    char** text = delete_spaces(line);
    if(mode){
        for(int i = 0; text[i] != NULL; i++){
            if(strmatchWildcard(text[i], "//TODO", strlen(text[i]), strlen("//TODO"))){
                return 1;
            }
        }
        return 0;
    }
    else{
        for(int i = 0; text[i] != NULL; i++){
            //printf("<<%s>>", text[i]);
            if(strmatchWildcard(text[i], "TODO", strlen(text[i]), strlen("TODO"))){
                //printf("<%s>",text[i]);
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
char* check_format(char* address){
    char* type = (char*)calloc(100, 1);
    int j = 0, flag = 1;;
    for(int i = strlen(address) - 1; i >= 0; i--){
        if(address[i] == '.'){
            flag = 0;
            break;
        }
        else{
            type[j] = address[i];
            j++;
        }
    }
    if(j > 50 || flag == 1){
        return "NULL"; //means no type
    }
    int len = strlen(type);
    for(int i = 0; i < len / 2 ; i++){
        if(i == len - i - 1) break;
        type[i] ^= type[len - i - 1];
        type[len - i - 1] ^= type[i];
        type[i] ^= type[len - i - 1];
    }
    return type;
}
char HOOKcheck_errors(char* address){
    char* type = check_format(address);
    if(!strcmp(type, "cpp") || !strcmp(type, "c")){
        FILE* f = fopen(address, "r");
        if (f == NULL) return 0;
        fclose(f);
        char temp[300];
        sprintf(temp, "gcc -fsyntax-only \"%s\" 2>___T___.neogit", address);
        //printf("%s", temp);
        system (temp);
        f = fopen("___T___.neogit", "r");
        temp[0] = 0;
        fscanf(f, "%s", temp);
        fclose(f);
        remove("___T___.neogit");
        if(temp[0] == 0) return 1;
        return -1;
    }
    return 0;
}
char HOOKTODO_check(char* address){
    char* type = check_format(address);
    if(!strcmp(type, "cpp") || !strcmp(type, "c") || !strcmp(type, "txt")){
        if(!strcmp(type, "txt")){
            FILE* f = fopen(address, "r");
            if(f==NULL) return 0;
            char line[1000];
            while(fgets(line, 199, f) != NULL){
                while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
                    line[strlen(line) - 1] = 0;
                if(isTodo(line, 0)){
                    fclose(f);
                    return -1;
                }
            }
            fclose(f);
            return 1;
        }
        else{
            FILE* f = fopen(address, "r");
            if(f==NULL) return 0;
            char line[200];
            while(fgets(line, 199, f) != NULL){
                while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
                    line[strlen(line) - 1] = 0;
                if(isTodo(line, 1)){
                    fclose(f);
                    return -1;
                }
            }
            fclose(f);
            return 1;
        }
    }
    else{
        return 0;
    }
}
int count_ofB1(char* line){
    int count = 0;
    for(unsigned long long i = 0; i < strlen(line); i++){
        if(line[i] == '('){
            count ++;
        }
        if(line[i] == ')'){
            count --;
        }
    }
    return count;
}
int count_ofB2(char* line){
    int count = 0;
    for(unsigned long long i = 0; i < strlen(line); i++){
        if(line[i] == '['){
            count ++;
        }
        if(line[i] == ']'){
            count --;
        }
    }
    return count;
}
int count_ofB3(char* line){
    int count = 0;
    for(unsigned long long i = 0; i < strlen(line); i++){
        if(line[i] == '{'){
            count ++;
        }
        if(line[i] == '}'){
            count --;
        }
    }
    return count;
}
char HOOKbracets_check(char* address){
    char* type = check_format(address);
    if(!strcmp(type, "cpp") || !strcmp(type, "c") || !strcmp(type, "txt")){
        FILE* f = fopen(address, "r");
        if (f == NULL) return 0;
        int c1=0,c2=0,c3=0;
        char line[1000];
        while(fgets(line, 199, f) != NULL){
            while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
                line[strlen(line) - 1] = 0;
            c1 += count_ofB1(line);
            c2 += count_ofB2(line);
            c3 += count_ofB3(line);
        }
        fclose(f);
        if(c1 == c2 && c2 == c3 && c3 == 0){
            return 1;
        }
        return -1;
    }
    return 0;
}
char HOOKblank(char* address){
    char* type = check_format(address);
    if(!strcmp(type, "cpp") || !strcmp(type, "c") || !strcmp(type, "txt")){
        FILE* f = fopen(address, "r");
        if (f == NULL) return 0;
        char line[1000];
        char is = 0;
        while(fgets(line, 199, f) != NULL){
            is = 0;
            while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r')
                line[strlen(line) - 1] = 0;
            if(strlen(line) == 0){
                is = 1;
                continue;
            }
            if(line[strlen(line) - 1] == ' ' || line[strlen(line) - 1] == '\t'){
                is = 1;
            }
        }
        fclose(f);
        if(is)
            return -1;
        return 1;
    }
    return 0;
}
char HOOKformat_check(char* address){
    char* format = check_format(address);
    if(equalStrings(format, "txt") || equalStrings(format, "c") || equalStrings(format, "cpp") || equalStrings(format, "mp3") || equalStrings(format, "mp4") || equalStrings(format, "wav") || equalStrings(format, "py")){
        return 1;
    }
    return -1;
}
char HOOKgetSizeMB(char* address){
    FILE* f = fopen(address, "r");
    if(f==NULL) return 0;
    fseek(f, 0, SEEK_END);
    unsigned long long size = ftell(f); 
    fseek(f, 0, SEEK_SET);
    size = size / 1024 / 1024;
    if(size>=5)
        return -1;
    return 1;
}
char HOOKcount_char(char* address){
    char* type = check_format(address);
    if(!(!strcmp(type, "cpp") || !strcmp(type, "c") || !strcmp(type, "txt"))) return 0;
    FILE* f = fopen(address, "r");
    if(f==NULL)return 0;
    char ch;
    int count = 0;
    while (1) {
        ch = fgetc(f);
        if (ch == EOF)
            break;
        ++count;
        if(count >= 20000){
            return -1;
        }
    }
    return 1;
}
char checkHooks_stage(char* address, int functions, char mode){ //mode 'w' = write on screen
    if(address[0] == 0){
        address = absolute_address_neogit();
        address = connectTwoString(address, "\\stage\\");
        if(!check_type(address)){
            printf("\033[31man unknown problem\033[0m!\n");
            exit(0);
        }
    }
    char directiries[100][400];
    int numberdir = 0;
    char* address_free1;
    DIR* dir;
    dir = opendir(address);
    struct dirent* entry;
    if(dir == NULL){
        printf("\033[31munable to open %s directory\033[0m\n", address);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free1 = connectTwoString(address, "");
            char isDir1;
            address_free1 = connectTwoString(address_free1, connectTwoString("\\", entry->d_name));
            isDir1 = check_type(address_free1);
            if(isDir1 == 1){
                strcpy(directiries[numberdir], address_free1);
                numberdir++;
            }
            else{
                char* a = strstr(address_free1, "\\.neogit\\stage");
                a += 15;
                if(mode == 'w') printf("\"%s\": \n", a);
                if((functions & 1) == (1)){
                    char ans = HOOKTODO_check(address_free1);
                    if(ans == 1 && mode == 'w'){
                        printf("\033[32mtodo-check...................PASSED\n\033[0m");
                    }
                    if(ans == 0 && mode =='w'){
                        printf("\033[33mtodo-check...................SKIPPED\n\033[0m");
                    }
                    if(ans == -1 && mode == 'w'){
                        printf("\033[31mtodo-check...................FAILED\n\033[0m");
                    }
                    if(ans == -1 && mode!= 'w'){
                        return 0;
                    }
                }
                if((functions & (1<<1)) == (1<<1)){
                    char ans = HOOKblank(address_free1);
                    if(ans == 1 && mode == 'w'){
                        printf("\033[32meof-blank-space...................PASSED\n\033[0m");
                    }
                    if(ans == 0 && mode =='w'){
                        printf("\033[33meof-blank-space...................SKIPPED\n\033[0m");
                    }
                    if(ans == -1 && mode == 'w'){
                        printf("\033[31meof-blank-space...................FAILED\n\033[0m");
                    }
                    
                    if(ans == -1 && mode!= 'w'){
                        return 0;
                    }
                }
                if((functions & (1<<2)) == (1<<2)){
                    char ans = HOOKformat_check(address_free1);
                    if(ans == 1 && mode == 'w'){
                        printf("\033[32mformat-check...................PASSED\n\033[0m");
                    }
                    if(ans == 0 && mode =='w'){
                        printf("\033[33mformat-check...................SKIPPED\n\033[0m");
                    }
                    if(ans == -1 && mode == 'w'){
                        printf("\033[31mformat-check...................FAILED\n\033[0m");
                    }
                    
                    if(ans == -1 && mode!= 'w'){
                        return 0;
                    }
                }
                if((functions & (1<<3)) == (1<<3)){
                    char ans = HOOKbracets_check(address_free1);
                    if(ans == 1 && mode == 'w'){
                        printf("\033[32mbalance-bracets...................PASSED\n\033[0m");
                    }
                    if(ans == 0 && mode =='w'){
                        printf("\033[33mbalance-bracets...................SKIPPED\n\033[0m");
                    }
                    if(ans == -1 && mode == 'w'){
                        printf("\033[31mbalance-bracets...................FAILED\n\033[0m");
                    }
                    
                    if(ans == -1 && mode!= 'w'){
                        return 0;
                    }
                }
                if((functions & (1<<4)) == (1<<4)){
                    char ans = HOOKcheck_errors(address_free1);
                    if(ans == 1 && mode == 'w'){
                        printf("\033[32mstatic-error-check...................PASSED\n\033[0m");
                    }
                    if(ans == 0 && mode =='w'){
                        printf("\033[33mstatic-error-check...................SKIPPED\n\033[0m");
                    }
                    if(ans == -1 && mode == 'w'){
                        printf("\033[31mstatic-error-check...................FAILED\n\033[0m");
                    }
                    
                    if(ans == -1 && mode!= 'w'){
                        return 0;
                    }
                }
                if((functions & (1<<5)) == (1<<5)){
                    char ans = HOOKgetSizeMB(address_free1);
                    if(ans == 1 && mode == 'w'){
                        printf("\033[32mfile-size-check...................PASSED\n\033[0m");
                    }
                    if(ans == 0 && mode =='w'){
                        printf("\033[33mfile-size-check...................SKIPPED\n\033[0m");
                    }
                    if(ans == -1 && mode == 'w'){
                        printf("\033[31mfile-size-check...................FAILED\n\033[0m");
                    }
                    if(ans == -1 && mode!= 'w'){
                        return 0;
                    }
                }
                if((functions & (1<<6)) == (1<<6)){
                    char ans = HOOKcount_char(address_free1);
                    if(ans == 1 && mode == 'w'){
                        printf("\033[32mcharacter-limit...................PASSED\n\033[0m");
                    }
                    if(ans == 0 && mode =='w'){
                        printf("\033[33mcharacter-limit...................SKIPPED\n\033[0m");
                    }
                    if(ans == -1 && mode == 'w'){
                        printf("\033[31mcharacter-limit...................FAILED\n\033[0m");
                    }
                    if(ans == -1 && mode!= 'w'){
                        return 0;
                    }
                }
            }
        }
    }
    closedir(dir);
    int r = 1;
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        if(!checkHooks_stage(directiries[i], functions, mode))
            r = 0;
    }
    return r;
}
char checkHooks_file(char* address, int functions, char mode){ //mode 'w' = write on screen
    char modeF = check_type(address);
    if(modeF == 0){printf("\033[31mNO\033[0m such a file in working directory. (%s)\n", address); exit(0);}
    if(modeF == 1){printf("\033[31mNOT file!\033[0m this is a folder in working directory. (%s)\n", address); exit(0);}
    struct address__  addr = Help_ADD(address);
    address = connectTwoString(addr.adress_stage_file, addr.address_given[addr.size_address_given - 1]);
    modeF = check_type(address);
    if(modeF == 0){printf("\033[31mNO\033[0m such a file in stage area. (%s)\n", address); exit(0);}
    if(modeF == 1){printf("\033[31mNOT file!\033[0m this is a folder in stage area. (%s)\n", address); exit(0);}
    char* a = strstr(address, "\\.neogit\\stage");
    a += 15;
    if(mode == 'w') printf("\"%s\": \n", a);
    if((functions & 1) == (1)){
        char ans = HOOKTODO_check(address);
        if(ans == 1 && mode == 'w'){
            printf("\033[32mtodo-check...................PASSED\n\033[0m");
        }
        if(ans == 0 && mode =='w'){
            printf("\033[33mtodo-check...................SKIPPED\n\033[0m");
        }
        if(ans == -1 && mode == 'w'){
            printf("\033[31mtodo-check...................FAILED\n\033[0m");
        }
        if(ans == -1 && mode!= 'w'){
            return 0;
        }
    }
    if((functions & (1<<1)) == (1<<1)){
        char ans = HOOKblank(address);
        if(ans == 1 && mode == 'w'){
            printf("\033[32meof-blank-space...................PASSED\n\033[0m");
        }
        if(ans == 0 && mode =='w'){
            printf("\033[33meof-blank-space...................SKIPPED\n\033[0m");
        }
        if(ans == -1 && mode == 'w'){
            printf("\033[31meof-blank-space...................FAILED\n\033[0m");
        }
        
        if(ans == -1 && mode!= 'w'){
            return 0;
        }
    }
    if((functions & (1<<2)) == (1<<2)){
        char ans = HOOKformat_check(address);
        if(ans == 1 && mode == 'w'){
            printf("\033[32mformat-check...................PASSED\n\033[0m");
        }
        if(ans == 0 && mode =='w'){
            printf("\033[33mformat-check...................SKIPPED\n\033[0m");
        }
        if(ans == -1 && mode == 'w'){
            printf("\033[31mformat-check...................FAILED\n\033[0m");
        }
        
        if(ans == -1 && mode!= 'w'){
            return 0;
        }
    }
    if((functions & (1<<3)) == (1<<3)){
        char ans = HOOKbracets_check(address);
        if(ans == 1 && mode == 'w'){
            printf("\033[32mbalance-bracets...................PASSED\n\033[0m");
        }
        if(ans == 0 && mode =='w'){
            printf("\033[33mbalance-bracets...................SKIPPED\n\033[0m");
        }
        if(ans == -1 && mode == 'w'){
            printf("\033[31mbalance-bracets...................FAILED\n\033[0m");
        }
        
        if(ans == -1 && mode!= 'w'){
            return 0;
        }
    }
    if((functions & (1<<4)) == (1<<4)){
        char ans = HOOKcheck_errors(address);
        if(ans == 1 && mode == 'w'){
            printf("\033[32mstatic-error-check...................PASSED\n\033[0m");
        }
        if(ans == 0 && mode =='w'){
            printf("\033[33mstatic-error-check...................SKIPPED\n\033[0m");
        }
        if(ans == -1 && mode == 'w'){
            printf("\033[31mstatic-error-check...................FAILED\n\033[0m");
        }
        
        if(ans == -1 && mode!= 'w'){
            return 0;
        }
    }
    if((functions & (1<<5)) == (1<<5)){
        char ans = HOOKgetSizeMB(address);
        if(ans == 1 && mode == 'w'){
            printf("\033[32mfile-size-check...................PASSED\n\033[0m");
        }
        if(ans == 0 && mode =='w'){
            printf("\033[33mfile-size-check...................SKIPPED\n\033[0m");
        }
        if(ans == -1 && mode == 'w'){
            printf("\033[31mfile-size-check...................FAILED\n\033[0m");
        }
        if(ans == -1 && mode!= 'w'){
            return 0;
        }
    }
    if((functions & (1<<6)) == (1<<6)){
        char ans = HOOKcount_char(address);
        if(ans == 1 && mode == 'w'){
            printf("\033[32mcharacter-limit...................PASSED\n\033[0m");
        }
        if(ans == 0 && mode =='w'){
            printf("\033[33mcharacter-limit...................SKIPPED\n\033[0m");
        }
        if(ans == -1 && mode == 'w'){
            printf("\033[31mcharacter-limit...................FAILED\n\033[0m");
        }
        if(ans == -1 && mode!= 'w'){
            return 0;
        }
    }
    return 1;
}
//End of hook
//stash
void push_stash(char* address, int id){
    if(equalStrings(address, ".") || equalStrings(address, "..") || equalStrings(address, ".neogit")) return;
    char mode = check_type(address);
    char address_stash[100];
    sprintf(address_stash, ".neogit\\stash\\%d\\", id);
    char command[200];
    if(mode == 1){
        mkdir(connectTwoString(address_stash, address));
        sprintf(command, "xcopy \"%s\\*\" \"%s\\*\" /e/h/c/i/y > NUL",  address, connectTwoString(address_stash, address));
        if(system(command)) {printf("\033[31man unknown problem\033[0m!\n"); return;}
    }
    if(mode == -1){
        sprintf(command, "copy \"%s\" \"%s\" > NUL",  address, address_stash);
        if(system(command)) {printf("\033[31man unknown problem\033[0m!\n"); return;}
    }
}
void clear_stage(){
    char* address_neogit = absolute_address_neogit();
    address_neogit = connectTwoString(address_neogit, "\\stage\\");
    DIR* dir;
    dir = opendir(address_neogit);
    struct dirent* entry;
    if(dir == NULL){
        printf("unable to open %s directory\n", address_neogit);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            char* address_free = connectTwoString(address_neogit, entry->d_name);
            char isDir = check_type(address_free);
            char command[400];
            if(isDir == 1){
                sprintf(command, "rmdir /s /q \"%s\"", address_free);
                if(system(command)){
                    printf("\033[31man unknown problem\033[0m!\n");
                    continue;
                }
            }
            else{
                sprintf(command, "del /f /q \"%s\"", address_free);
                if(system(command)){
                    printf("\033[31man unknown problem\033[0m!\n");
                    continue;
                }
            }
        }
    }
}
void append_end_stash_list(int id){ // YOU should be on main folder!
    FILE* f = fopen(".neogit\\stash\\list", "r");
    char line[200][100];
    int a = 0;
    while(fgets(line[a], 99, f) != NULL){
        while(line[a][strlen(line[a]) - 1] == '\n' || line[a][strlen(line[a]) - 1] == '\r' || line[a][strlen(line[a]) - 1] == ' ')
            line[a][strlen(line[a]) - 1] = 0;
        a++;
    }
    fclose(f);
    f = fopen(".neogit\\stash\\list", "w");
    fprintf(f,"%d\n", id);
    for(int i = 0; i < a; i++){
        fprintf(f,"%s\n", line[i]);
    }
    fclose(f);
}
void show_list_stash(){
    char* address = absolute_address_neogit();
    address = connectTwoString(address, "\\stash\\list");
    FILE* f = fopen(address, "r");
    char line[100];
    int a = 0;
    while(fgets(line, 99, f) != NULL){
        while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
            line[strlen(line) - 1] = 0;
        if(line[0] == 0) continue;;
        printf("ID: \033[36m%d\033[0m; ", a);
        address = absolute_address_neogit();
        address = connectTwoString(address, "\\stash\\");
        char temp[100];
        sprintf(temp, "%d_info\\", atoi(line));
        address = connectTwoString(address, temp);
        char* branch_A = connectTwoString(address, "branch");
        char branch[20];
        FILE*ff = fopen(branch_A, "r"); fscanf(ff, "%s", branch); fclose(ff);
        printf("BRANCH: <\033[36m%s\033[0m>; ", branch);
        char* mas_A = connectTwoString(address, "massage");
        char massage[200];
        ff = fopen(mas_A, "r"); fscanf(ff, "%[^\n]s", massage); fclose(ff);
        printf("MASSAGE: <\033[36m%s\033[0m>\n", massage);
        a++;
    }
} 
int findHash_stash(int id){
    //printf("%d", id);
    char* address = absolute_address_neogit();
    address = connectTwoString(address, "\\stash\\list");
    FILE* f = fopen(address, "r");
    char line[100];
    int a = 0;
    while(fgets(line, 99, f) != NULL){
        while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
            line[strlen(line) - 1] = 0;
        if(line[0] == 0) continue;
        if(id == a){
            return atoi(line);
        }
        a++;
    }
    return 0;
} 
void delete_stash(int id){
    //printf("%d", id);
    char* address = absolute_address_neogit();
    address = connectTwoString(address, "\\stash\\");
    char temp[100];
    sprintf(temp, "%d", id);
    address = connectTwoString(address, temp);
    char command[200];
    sprintf(command, "rmdir /s /q \"%s\"", address);
    if(system(command)){
        printf("\033[31man unknown problem\033[0m!\n");
        return;
    }
    sprintf(command, "rmdir /s /q \"%s_info\"", address);
    if(system(command)){
        printf("\033[31man unknown problem\033[0m!\n");
        return;
    }
    FILE* f = fopen(".neogit\\stash\\list", "r");
    char line[200][100];
    int a = 0;
    while(fgets(line[a], 99, f) != NULL){
        while(line[a][strlen(line[a]) - 1] == '\n' || line[a][strlen(line[a]) - 1] == '\r' || line[a][strlen(line[a]) - 1] == ' ')
            line[a][strlen(line[a]) - 1] = 0;
        if(atoi(line[a]) == id){
            line[a][0] = 0;
        }
        else{
            a++;
        }
        //printf("%s|", line[a-1]);
    }
    fclose(f);
    f = fopen(".neogit\\stash\\list", "w");
    for(int i = 0; i < a; i++){
        if(line[i][0] != 0){
            fprintf(f,"%s\n", line[i]);
            //printf("%s\n", line[i]);
            //printf("Y");
        }
    }
    fclose(f);
}
void Help_checkAllFiles_compare_stash_commits(char* address1, char* address2, int id1, int id2, int id3){
    // printf("<%s><%s>\n", address1, address2);
    if(address1[0] == 0){
        address1 = absolute_address_neogit();
        address1 = connectTwoString(address1, "\\stash\\");
        char temp[10];
        sprintf(temp, "%d", id1);
        address1 = connectTwoString(address1, temp);
        address2 = absolute_address_neogit();
        address2 = connectTwoString(address2, "\\commits\\");
        sprintf(temp, "%d", id2);
        address2 = connectTwoString(address2, temp);
        //printf("%s %s\n", address1,address2);
        if(!check_type(address1) || !check_type(address2)){
            printf("\033[31minvalid ID\033[0m!\n");
            exit(0);
        }
    }
    char directiries[100][400];
    int numberdir = 0;
    char* address_free1;
    char* address_free2;
    DIR* dir;
    dir = opendir(address1);
    struct dirent* entry;
    if(dir == NULL){
        printf("\033[31munable to open %s directory\033[0m\n", address1);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free1 = connectTwoString(address1, "");
            address_free2 = connectTwoString(address2, "");
            char isDir1, isDir2;
            address_free1 = connectTwoString(address_free1, connectTwoString("\\", entry->d_name));
            address_free2 = connectTwoString(address_free2, connectTwoString("\\", entry->d_name));
            isDir1 = check_type(address_free1);
            isDir2 = check_type(address_free2);
            if(isDir1 == 1){
                if(isDir2 != 1){
                    char* a = strstr(address_free1, "\\.neogit\\stash\\");
                    a = a + 21;
                    printf("<%s><%s>\n", address_free1, address_free2);
                    printf("\033[94m%s\\\033[0m is in stash \033[94m%d\033[0m but it is \033[31mnot\033[0m in commit \033[94m%d\033[0m\n", a, id3,id2);
                    continue;
                }
                strcpy(directiries[numberdir], address_free1);
                numberdir++;
            }
            else{
                char* a = strstr(address_free1, "\\.neogit\\stash\\");
                a = a + 21;
                if(isDir2 != -1){
                    // printf("<%s><%s>\n", address_free1, address_free2);
                    printf("\033[94m%s\033[0m is in stash \033[94m%d\033[0m but it is \033[31mnot\033[0m in commit \033[94m%d\033[0m\n", a,id3 ,id2);
                    continue;
                }
                printf("comparing \033[94m%s\033[0m in stash \033[94m%d\033[0m and commit \033[94m%d\033[0m:\n", a, id3, id2);
                char temp[200];
                sprintf(temp, "neogit diff -f \"%s\" \"%s\"", address_free1, address_free2);
                system(temp);
            }
        }
    }
    closedir(dir);
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        char* name = connectTwoString(directiries[i], "");
        char* temp = strstr(name, ".neogit\\stash\\");
        temp = temp + 8;
        sprintf(temp, "commits\\%d", id2);
        temp[strlen(temp) + 1] = '\0';
        temp[strlen(temp)] = '\\';
        temp = strstr(directiries[i], ".neogit\\stash\\");
        temp = temp + 21;
        name = connectTwoString(name, temp);
        Help_checkAllFiles_compare_stash_commits(directiries[i], name, id1, id2, id3);
    }
}
void Help_checkAllFiles_compare_stash_commits2(char* address1, char* address2, int id1, int id2, int id3){
    if(address1[0] == 0){
        address1 = absolute_address_neogit();
        address1 = connectTwoString(address1, "\\stash\\");
        char temp[10];
        sprintf(temp, "%d", id1);
        address1 = connectTwoString(address1, temp);
        address2 = absolute_address_neogit();
        address2 = connectTwoString(address2, "\\commits\\");
        sprintf(temp, "%d", id2);
        address2 = connectTwoString(address2, temp);
        if(!check_type(address1) || !check_type(address2)){
            printf("\033[31minvalid ID\033[0m!\n");
            exit(0);
        }
    }

    char directiries[100][400];
    int numberdir = 0;
    char* address_free1;
    char* address_free2;
    DIR* dir;
    dir = opendir(address2);
    struct dirent* entry;
    if(dir == NULL){
        printf("\033[31munable to open %s directory\033[0m\n", address2);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free1 = connectTwoString(address1, "");
            address_free2 = connectTwoString(address2, "");
            char isDir1, isDir2;
            address_free1 = connectTwoString(address_free1, connectTwoString("\\", entry->d_name));
            address_free2 = connectTwoString(address_free2, connectTwoString("\\", entry->d_name));
            isDir1 = check_type(address_free1);
            isDir2 = check_type(address_free2);
            if(isDir2 == 1){
                if(isDir1 != 1){
                    char* a = strstr(address_free2, "\\.neogit\\commits\\");
                    a = a + 24;
                    printf("\033[94m%s\\\033[0m is in commit \033[94m%d\033[0m but it is \033[31mnot\033[0m in stash \033[94m%d\033[0m\n", a, id2,id3);
                    continue;
                }
                strcpy(directiries[numberdir], address_free2);
                numberdir++;
            }
            else{
                char* a = strstr(address_free2, "\\.neogit\\commits");
                a = a + 24;
                if(isDir1 != -1){
                    printf("\033[94m%s\033[0m is in commit \033[94m%d\033[0m but it is \033[31mnot\033[0m in stash \033[94m%d\033[0m\n", a,id2 ,id3);
                    continue;
                }
            }
        }
    }
    closedir(dir);
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        char* name = connectTwoString(directiries[i], "");
        char* temp = strstr(name, ".neogit\\commits\\");
        temp = temp + 8;
        sprintf(temp, "stash\\%d", id1);
        temp[strlen(temp) + 1] = '\0';
        temp[strlen(temp)] = '\\';
        temp = strstr(directiries[i], ".neogit\\commits\\");
        temp = temp + 23;
        name = connectTwoString(name, temp);
        Help_checkAllFiles_compare_stash_commits2(name, directiries[i], id1, id2, id3);
    }
}
void compare_stash_commit(int stash, int commit, int index){
    Help_checkAllFiles_compare_stash_commits("", "", stash, commit, index);
    Help_checkAllFiles_compare_stash_commits2("", "", stash, commit, index);
}
//end ofstash
//tag
void append_new_tag(char* name, int commit_id, char* userName, char* userEmail, unsigned long long date, char* day, char*massage){
    char* address = absolute_address_neogit();
    address = connectTwoString(address, "\\config\\tag");
    FILE* f = fopen(address, "a");
    fprintf(f, "tag %s\ncommit %d\nAuthor: %s <%s>\nDate: <%s> ", name, commit_id,userName, userEmail , day);
    fprint_time(f, date);
    fprintf(f, "\nMassage: \"%s\"\n", massage);
}
int is_Exist_tag(char* name){ // -1 -> not found    != -1 -> line number
    char* address = absolute_address_neogit();
    address = connectTwoString(address, "\\config\\tag");
    FILE* f = fopen(address, "r");
    char line[100];
    int a = 0;
    while(fgets(line, 99, f) != NULL){
        while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
            line[strlen(line) - 1] = 0;
        if(line[0] == 0) continue;
        char nameI[200];
        nameI[0] = 0;
        sscanf(line, "tag %[^\n]s", nameI);
        if(equalStrings(name, nameI)) return a;
        a++;
    }
    return -1;
}
void delete_tag(char* name){
    char* address = absolute_address_neogit();
    address = connectTwoString(address, "\\config\\tag");
    FILE* f = fopen(address, "r");
    char line[2000][100];
    int a = 0;
    while(fgets(line[a], 99, f) != NULL){
        while(line[a][strlen(line[a]) - 1] == '\n' || line[a][strlen(line[a]) - 1] == '\r' || line[a][strlen(line[a]) - 1] == ' ')
            line[a][strlen(line[a]) - 1] = 0;
        if(line[a][0] == 0) continue;
        char nameI[200];
        nameI[0] = 0;
        sscanf(line[a], "tag %[^\n]s", nameI);
        if(equalStrings(name, nameI)){
            fgets(line[a], 99, f);fgets(line[a], 99, f);fgets(line[a], 99, f);fgets(line[a], 99, f);
            a--;
        }
        a++;
    }
    fclose(f);
    f = fopen(address, "w");
    for(int i = 0; i < a; i++){
        fprintf(f, "%s\n", line[i]);
    }
    fclose(f);
}
//end of tag
//merge
void check_no_conflict_two_branch(char* address1, char* address2, int id1, int id2){
    if(address1[0] == 0){
        address1 = absolute_address_neogit();
        address1 = connectTwoString(address1, "\\commits\\");
        char temp[10];
        sprintf(temp, "%d", id1);
        address1 = connectTwoString(address1, temp);
        address2 = absolute_address_neogit();
        address2 = connectTwoString(address2, "\\commits\\");
        sprintf(temp, "%d", id2);
        address2 = connectTwoString(address2, temp);
        //printf("%s %s\n", address1,address2);
        if(!check_type(address1) || !check_type(address2)){
            printf("\033[31minvalid ID\033[0m!\n");
            exit(0);
        }
    }
    char directiries[100][400];
    int numberdir = 0;
    char* address_free1;
    char* address_free2;
    DIR* dir;
    dir = opendir(address1);
    struct dirent* entry;
    if(dir == NULL){
        printf("\033[31munable to open %s directory\033[0m\n", address1);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free1 = connectTwoString(address1, "");
            address_free2 = connectTwoString(address2, "");
            char isDir1, isDir2;
            address_free1 = connectTwoString(address_free1, connectTwoString("\\", entry->d_name));
            address_free2 = connectTwoString(address_free2, connectTwoString("\\", entry->d_name));
            isDir1 = check_type(address_free1);
            isDir2 = check_type(address_free2);
            if(isDir1 == 1){
                if(isDir2 != 1){
                    char* address_merge = connectTwoString(address_free1, "");
                    char* temp = strstr(address_merge, "\\.neogit\\commits");
                    temp += 9;
                    *temp = 0;
                    address_merge = connectTwoString(address_merge, "merge\\");
                    temp = strstr(address_free1, "\\.neogit\\commits");
                    temp += 24;
                    address_merge = connectTwoString(address_merge, temp);
                    char command[200];
                    sprintf(command, "mkdir \"%s\"", address_merge);
                    system(command);
                    sprintf(command, "xcopy \"%s\\*\" \"%s\\*\" /e/h/c/i/y > NUL",  address_free1, address_merge);
                    if(system(command)) {printf("\033[31man unknown problem\033[0m!\n");}
                    continue;
                }
                char* address_merge = connectTwoString(address_free1, "");
                char* temp = strstr(address_merge, "\\.neogit\\commits");
                temp += 9;
                *temp = 0;
                address_merge = connectTwoString(address_merge, "merge\\");
                temp = strstr(address_free1, "\\.neogit\\commits");
                temp += 24;
                address_merge = connectTwoString(address_merge, temp);
                char command[200];
                sprintf(command, "mkdir \"%s\"", address_merge);
                system(command);
                strcpy(directiries[numberdir], address_free1);
                numberdir++;
            }
            else{
                char* a = strstr(address_free1, "\\.neogit\\commits\\");
                a = a + 23;
                if(isDir2 != -1){
                    char* address_merge = connectTwoString(address_free1, "");
                    char* temp = strstr(address_merge, "\\.neogit\\commits");
                    temp += 9;
                    *temp = 0;
                    address_merge = connectTwoString(address_merge, "merge\\");
                    temp = strstr(address_free1, "\\.neogit\\commits");
                    temp += 24;
                    address_merge = connectTwoString(address_merge, temp);
                    char command[200];
                    sprintf(command, "copy \"%s\" \"%s\" > NUL",  address_free1, address_merge);
                    if(system(command)) {printf("\033[31man unknown problem\033[0m!\n");}
                    continue;
                }
                if(!TwoFileAreSame(address_free1, address_free2)){
                    printf("you have \033[31mconflict\033[0m in %s!\n", a);
                    char temp[200];
                    sprintf(temp, "neogit diff_conflict_neogit -f \"%s\" \"%s\"", address_free1, address_free2);
                    system(temp);
                    exit(0);
                }
                else{
                    char* address_merge = connectTwoString(address_free1, "");
                    char* temp = strstr(address_merge, "\\.neogit\\commits");
                    temp += 9;
                    *temp = 0;
                    address_merge = connectTwoString(address_merge, "merge\\");
                    temp = strstr(address_free1, "\\.neogit\\commits");
                    temp += 24;
                    address_merge = connectTwoString(address_merge, temp);
                    char command[200];
                    sprintf(command, "copy \"%s\" \"%s\" > NUL",  address_free1, address_merge);
                    if(system(command)) {printf("\033[31man unknown problem\033[0m!\n");}
                    continue;
                }
            }
        }
    }
    closedir(dir);
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        char* name = connectTwoString(directiries[i], "");
        char* temp = strstr(name, ".neogit\\commits\\");
        temp = temp + 16;
        sprintf(temp, "%d", id2);
        temp[strlen(temp)] = '\\';
        check_no_conflict_two_branch(directiries[i], name, id1, id2);
    }
}
void check_no_conflict_two_branch2(char* address1, char* address2, int id1, int id2){
    if(address1[0] == 0){
        address1 = absolute_address_neogit();
        address1 = connectTwoString(address1, "\\commits\\");
        char temp[10];
        sprintf(temp, "%d", id1);
        address1 = connectTwoString(address1, temp);
        address2 = absolute_address_neogit();
        address2 = connectTwoString(address2, "\\commits\\");
        sprintf(temp, "%d", id2);
        address2 = connectTwoString(address2, temp);
        //printf("%s %s\n", address1,address2);
        if(!check_type(address1) || !check_type(address2)){
            printf("\033[31minvalid ID\033[0m!\n");
            exit(0);
        }
    }
    char directiries[100][400];
    int numberdir = 0;
    char* address_free1;
    char* address_free2;
    DIR* dir;
    dir = opendir(address1);
    struct dirent* entry;
    if(dir == NULL){
        printf("\033[31munable to open %s directory\033[0m\n", address1);
        exit(-1);
    }
    while ((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            address_free1 = connectTwoString(address1, "");
            address_free2 = connectTwoString(address2, "");
            char isDir1, isDir2;
            address_free1 = connectTwoString(address_free1, connectTwoString("\\", entry->d_name));
            address_free2 = connectTwoString(address_free2, connectTwoString("\\", entry->d_name));
            isDir1 = check_type(address_free1);
            isDir2 = check_type(address_free2);
            if(isDir1 == 1){
                if(isDir2 != 1){
                    char* address_merge = connectTwoString(address_free1, "");
                    char* temp = strstr(address_merge, "\\.neogit\\commits");
                    temp += 9;
                    *temp = 0;
                    address_merge = connectTwoString(address_merge, "merge\\");
                    temp = strstr(address_free1, "\\.neogit\\commits");
                    temp += 24;
                    address_merge = connectTwoString(address_merge, temp);
                    char command[200];
                    sprintf(command, "mkdir \"%s\"", address_merge);
                    system(command);
                    sprintf(command, "xcopy \"%s\\*\" \"%s\\*\" /e/h/c/i/y > NUL",  address_free1, address_merge);
                    if(system(command)) {printf("\033[31man unknown problem\033[0m!\n");}
                    continue;
                }
                strcpy(directiries[numberdir], address_free1);
                numberdir++;
            }
            else{
                char* a = strstr(address_free1, "\\.neogit\\commits\\");
                a = a + 23;
                if(isDir2 != -1){
                    char* address_merge = connectTwoString(address_free1, "");
                    char* temp = strstr(address_merge, "\\.neogit\\commits");
                    temp += 9;
                    *temp = 0;
                    address_merge = connectTwoString(address_merge, "merge\\");
                    temp = strstr(address_free1, "\\.neogit\\commits");
                    temp += 24;
                    address_merge = connectTwoString(address_merge, temp);
                    char command[200];
                    sprintf(command, "copy \"%s\" \"%s\" > NUL",  address_free1, address_merge);
                    if(system(command)) {printf("\033[31man unknown problem\033[0m!\n");}
                    continue;
                }
            }
        }
    }
    closedir(dir);
    for(int i = 0; i < numberdir; i++){
        if(!strcmp(directiries[i], ".neogit")) continue;
        char* name = connectTwoString(directiries[i], "");
        char* temp = strstr(name, ".neogit\\commits\\");
        temp = temp + 16;
        sprintf(temp, "%d", id2);
        temp[strlen(temp)] = '\\';
        check_no_conflict_two_branch2(directiries[i], name, id1, id2);
    }
}
int* Help_current_countOfMergeFiles(char* address){
    if(address[0] == 0){
        address = absolute_address_neogit();
        address = connectTwoString(address, "\\merge");
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
struct count_directory_file current_countOfMergeFiles(){
    int* a = Help_current_countOfMergeFiles("");
    struct count_directory_file b;
    b.file = a[1];
    b.directory = a[0];
    return b;
}
void delete_branch_from_list(char* name){
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
        if(!strcmp(line[i], name)){
            char temp[100];
            fgets(temp, 99, f);
            i--;
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
void append_merge_list(char* name,int scr ,int dis){
    char* address = gitFolder();
    address = connectTwoString(address, "//config//merge");
    FILE* f = fopen(address, "a");
    fprintf(f, "%s\n%d %d\n", name, scr, dis);

}

void commit_merge_list(char* branch, int last_id, char* branch1, char*branch2, int id2){
    char* name = current_name();
    char* email = current_email();
    int id = current_id();
    char** date = current_dateTime();
    struct count_directory_file count = current_countOfMergeFiles();
    if(count.directory == 0 && count.file == 0){
        printf("There is \033[31mnothing\033[0m in mearge area.\n");
        exit(0);
    }
    char* maasage = calloc(200, 1);
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
        sprintf(maasage, "merge branch %s and %s", branch1, branch2);
        fprintf(f, "%s", maasage);
        fclose(f);
        char* address_neogit = absolute_address_neogit();
        address_neogit = connectTwoString(address_neogit, "\\merge");
        ///////////////////// commiting
        DIR* dir;
        dir = opendir(address_neogit);
        struct dirent* entry;
        if(dir == NULL){
            printf("\033[31munable to open %s directory\033[0m\n", address_neogit);
            exit(-1);
        }
        char* address_free;
        sprintf(temp, "%d", id);
        char* address_commit_absolut = connectTwoString(absolute_address_neogit(), connectTwoString("\\commits\\", temp));
        char command[400];
        sprintf(command, "xcopy \"%s\\*\" \"%s\" /e/h/c/i/y > NUL", address_neogit, address_commit_absolut);
        if(system(command)){
            printf("\033[31man unknown problem\033[0m!\n");
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
                        printf("\033[31man unknown problem\033[0m!\n");
                        continue;
                    }
                }
                else{
                    sprintf(command, "del /f /q \"%s\"", address_free);
                    if(system(command)){
                        printf("\033[31man unknown problem\033[0m!\n");
                        continue;
                    }
                }
            }
        }
        closedir(dir);
        /////////////////////
        append_merge_list(branch2,id2 ,id);
        delete_branch_from_list(branch2);
        printf("\033[93m%d\033[0m \033[35mdirectory(s)\033[0m and \033[93m%d\033[0m \033[35mfile(s)\033[0m \033[32mcommited\033[0m by ID \033[93m%d\033[0m  at \033[94m%s/%s/%s-%s:%s:%s\033[0m on branch \033[93m%s\033[0m\n", count.directory, count.file, id, date[0],date[1],date[2],date[3],date[4],date[5], branch);
        printf("\033[90mcommit massage is\033[0m: \033[96m%s\033[0m\n", maasage);
    }
    else{
        printf("\033[31man unkown problem\033[0m!\n");
        exit(-1);
    }
}
void merge(int id1, int id2, char*branch1, char*branch2){
    check_no_conflict_two_branch("", "", id1, id2);
    check_no_conflict_two_branch2("", "", id2, id1);
    commit_merge_list(branch1, id1, branch1, branch2, id2);
}
void get_commands_V2(char**  input, int len){
    //temps
    if(equalStrings(input[1], "print_double_write_L__")){
        print_double_write_L();
    }
    if(equalStrings(input[1], "print_double_write_L__M")){
        print_double_write_LM();
    }
    if(equalStrings(input[1], "print_double_write_R__M")){
        print_double_write_RM();
    }
    if(equalStrings(input[1], "print_double_write_R__")){
        print_double_write_R();
    }
    //diff normal files
    if(equalStrings(input[1], "diff") && equalStrings(input[2], "-b") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){
        FILE* f1 = fopen(input[3], "r");
        FILE* f2 = fopen(input[4], "r");
        if(f1 == NULL || f2 == NULL){
            printf("Invalid address!\n");
            exit(0);
        }
        if(TwoFileAreSame(input[3], input[4])){
            printf("this files are the \033[32msame\033[0m(binary mode).\n");
        }
        else{
            printf("this files are \033[31mnot\033[0m the same(binary mode).\n");
        }
    }
    if(equalStrings(input[1], "diff") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){
        FILE* f1 = fopen(input[3], "r");
        FILE* f2 = fopen(input[4], "r");
        if(f1 == NULL || f2 == NULL){
            printf("Invalid address!\n");
            exit(0);
        }
        char *** lines1 = (char***)calloc(1000, sizeof(char**));
        int index1 = 0;
        int* numbers1 = (int*)calloc(1000, sizeof(int));
        int a = 1;
        char *** lines2 = (char***)calloc(1000, sizeof(char**));
        int index2 = 0;
        int* numbers2 = (int*)calloc(1000, sizeof(int));
        int b = 1;
        char* lines = (char*)calloc(1000, sizeof(char));
        while(fgets(lines, 999, f1) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0){
                lines1[index1] = delete_spaces(lines);
                numbers1[index1] = a;
                index1++;
            }
            a++;
        }
        while(fgets(lines, 999, f2) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0){
                lines2[index2] = delete_spaces(lines);
                numbers2[index2] = b;
                index2++;
            }
            b++;
        }
        char flag = 1;
        for(int i = 0; lines2[i] != NULL || lines1[i] != NULL; i++){
            if(!compare_two_tokenized_string(lines1[i], lines2[i], numbers1, numbers2, i, input[3], input[4])){
                flag = 0;
            }
        }
        if(flag){
            printf("this files are the \033[32msame\033[0m.\n");
        }
    }
    if(equalStrings(input[1], "diff_conflict_neogit") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){
        FILE* f1 = fopen(input[3], "r");
        FILE* f2 = fopen(input[4], "r");
        if(f1 == NULL || f2 == NULL){
            printf("Invalid address!\n");
            exit(0);
        }
        char *** lines1 = (char***)calloc(1000, sizeof(char**));
        int index1 = 0;
        int* numbers1 = (int*)calloc(1000, sizeof(int));
        int a = 1;
        char *** lines2 = (char***)calloc(1000, sizeof(char**));
        int index2 = 0;
        int* numbers2 = (int*)calloc(1000, sizeof(int));
        int b = 1;
        char* lines = (char*)calloc(1000, sizeof(char));
        while(fgets(lines, 999, f1) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0){
                lines1[index1] = delete_spaces(lines);
                numbers1[index1] = a;
                index1++;
            }
            a++;
        }
        while(fgets(lines, 999, f2) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0){
                lines2[index2] = delete_spaces(lines);
                numbers2[index2] = b;
                index2++;
            }
            b++;
        }
        char flag = 1;
        for(int i = 0; lines2[i] != NULL || lines1[i] != NULL; i++){
            if(!compare_two_tokenized_string(lines1[i], lines2[i], numbers1, numbers2, i, input[3], input[4])){
                flag = 0;
            }
        }
        if(flag){
            printf("\033[31mfiles are binary or they have some differents in null spaces\033[0m!\n");
        }
        char* address = absolute_address_neogit();
        address = connectTwoString(address, "\\merge");
        char command[200];
        char type = check_type(address);
        if(type){
            printf("%d %s", type, address);
            sprintf(command, "rmdir /s /q \"%s\\\"", address);
            system(command);
            sprintf(command, "mkdir \"%s\"", address);
            system(command);
        }
        exit(0);
    }
    if(equalStrings(input[1], "diff") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && strstr(input[5], "-line1") && strcmp(input[6], "") && len == 7){
        int line_a1 = 0;
        int line_z1 = 0;
        sscanf(input[6], "%d-%d", &line_a1, &line_z1);
        FILE* f1 = fopen(input[3], "r");
        FILE* f2 = fopen(input[4], "r");
        if(f1 == NULL || f2 == NULL){
            printf("Invalid address!\n");
            exit(0);
        }
        char *** lines1 = (char***)calloc(1000, sizeof(char**));
        int index1 = 0;
        int* numbers1 = (int*)calloc(1000, sizeof(int));
        int a = 1;
        char *** lines2 = (char***)calloc(1000, sizeof(char**));
        int index2 = 0;
        int* numbers2 = (int*)calloc(1000, sizeof(int));
        int b = 1;
        char* lines = (char*)calloc(1000, sizeof(char));
        while(fgets(lines, 999, f1) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0 && a >= line_a1 && a <= line_z1){
                lines1[index1] = delete_spaces(lines);
                numbers1[index1] = a;
                index1++;
            }
            a++;
        }
        while(fgets(lines, 999, f2) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0){
                lines2[index2] = delete_spaces(lines);
                numbers2[index2] = b;
                index2++;
            }
            b++;
        }
        char flag = 1;
        for(int i = 0; lines2[i] != NULL || lines1[i] != NULL; i++){
            if(!compare_two_tokenized_string(lines1[i], lines2[i], numbers1, numbers2, i, input[3], input[4])){
                flag = 0;
            }
        }
        if(flag){
            printf("this files are the \033[32msame\033[0m.\n");
        }    
    }
    if(equalStrings(input[1], "diff") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && strstr(input[5], "-line2") && strcmp(input[6], "") && len == 7){
        int line_a2 = 0;
        int line_z2 = 0;
        sscanf(input[6], "%d-%d", &line_a2, &line_z2);
        FILE* f1 = fopen(input[3], "r");
        FILE* f2 = fopen(input[4], "r");
        if(f1 == NULL || f2 == NULL){
            printf("Invalid address!\n");
            exit(0);
        }
        char *** lines1 = (char***)calloc(1000, sizeof(char**));
        int index1 = 0;
        int* numbers1 = (int*)calloc(1000, sizeof(int));
        int a = 1;
        char *** lines2 = (char***)calloc(1000, sizeof(char**));
        int index2 = 0;
        int* numbers2 = (int*)calloc(1000, sizeof(int));
        int b = 1;
        char* lines = (char*)calloc(1000, sizeof(char));
        while(fgets(lines, 999, f1) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0){
                lines1[index1] = delete_spaces(lines);
                numbers1[index1] = a;
                index1++;
            }
            a++;
        }
        while(fgets(lines, 999, f2) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0 && b >= line_a2 && b <= line_z2){
                lines2[index2] = delete_spaces(lines);
                numbers2[index2] = b;
                index2++;
            }
            b++;
        }
        char flag = 1;
        for(int i = 0; lines2[i] != NULL || lines1[i] != NULL; i++){
            if(!compare_two_tokenized_string(lines1[i], lines2[i], numbers1, numbers2, i, input[3], input[4])){
                flag = 0;
            }
        }
        if(flag){
            printf("this files are the \033[32msame\033[0m.\n");
        }    
    }
    if(equalStrings(input[1], "diff") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && strstr(input[5], "-line1") && strcmp(input[6], "") &&  strstr(input[7], "-line2") && strcmp(input[8], "")  && len == 9){
        int line_a2 = 0;
        int line_z2 = 0;
        sscanf(input[8], "%d-%d", &line_a2, &line_z2);
        int line_a1 = 0;
        int line_z1 = 0;
        sscanf(input[6], "%d-%d", &line_a1, &line_z1);
        FILE* f1 = fopen(input[3], "r");
        FILE* f2 = fopen(input[4], "r");
        if(f1 == NULL || f2 == NULL){
            printf("Invalid address!\n");
            exit(0);
        }
        char *** lines1 = (char***)calloc(1000, sizeof(char**));
        int index1 = 0;
        int* numbers1 = (int*)calloc(1000, sizeof(int));
        int a = 1;
        char *** lines2 = (char***)calloc(1000, sizeof(char**));
        int index2 = 0;
        int* numbers2 = (int*)calloc(1000, sizeof(int));
        int b = 1;
        char* lines = (char*)calloc(1000, sizeof(char));
        while(fgets(lines, 999, f1) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0 && a >= line_a1 && a <= line_z1){
                lines1[index1] = delete_spaces(lines);
                numbers1[index1] = a;
                index1++;
            }
            a++;
        }
        while(fgets(lines, 999, f2) != NULL){
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            if(lines[strlen(lines) - 1] == '\n' || lines[strlen(lines) - 1] == '\r')
                lines[strlen(lines) - 1] = 0;
            while(lines[strlen(lines) - 1] == ' '){
                lines[strlen(lines) - 1] = 0;
                if(strlen(lines) == 0)
                    break;
            }
            if(lines[0] != 0 && b >= line_a2 && b <= line_z2){
                lines2[index2] = delete_spaces(lines);
                numbers2[index2] = b;
                index2++;
            }
            b++;
        }
        char flag = 1;
        for(int i = 0; lines2[i] != NULL || lines1[i] != NULL; i++){
            if(!compare_two_tokenized_string(lines1[i], lines2[i], numbers1, numbers2, i, input[3], input[4])){
                flag = 0;
            }
        }
        if(flag){
            printf("this files are the \033[32msame\033[0m.\n");
        }    
    }
    //dif commits
    if(equalStrings(input[1], "diff") && equalStrings(input[2] , "-c") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){
        compare_two_commit(atoi(input[3]), atoi(input[4]));
    }
    //grep
    if(equalStrings(input[1], "grep") && equalStrings(input[2], "-f") && strcmp(input[3], "") && equalStrings(input[4], "-p") && strcmp(input[5], "") && len == 6){
        FILE* f1 = fopen(input[3], "r");
        if(f1 == NULL){
            printf("Invalid address!\n");
            exit(0);
        }
        char line[200];
        int flag = 1;
        while(fgets(line, 199, f1) != NULL){
            while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
                line[strlen(line) - 1] = 0;
            if(check_if_word_in_line(input[5], line)){
                flag = 0;
            }
        }
        if(flag){
            printf("\033[31No\033[0m line fount that contains \"%s\"\n", input[5]);
        }
    }
    if(equalStrings(input[1], "grep") && equalStrings(input[2], "-f") && strcmp(input[3], "") && equalStrings(input[4], "-p") && strcmp(input[5], "") && equalStrings(input[6], "-n") && len == 7){
        FILE* f1 = fopen(input[3], "r");
        if(f1 == NULL){
            printf("Invalid address!\n");
            exit(0);
        }
        char line[200];
        int flag = 1;
        int a = 1;
        while(fgets(line, 199, f1) != NULL){
            while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
                line[strlen(line) - 1] = 0;
            if(check_if_word_in_line_n(input[5], line, a)){
                flag = 0;
            }
            a++;
        }
        if(flag){
            printf("\033[31mNo\033[0m line fount that contains \"%s\"\n", input[5]);
        }
    }
    if(equalStrings(input[1], "grep") && equalStrings(input[2], "-c") && strcmp(input[3], "") && equalStrings(input[4], "-p") && strcmp(input[5], "") && equalStrings(input[6], "-n") && len == 7){
        grep_n_commit("", atoi(input[3]), input[5]);
    }
    if(equalStrings(input[1], "grep") && equalStrings(input[2], "-c") && strcmp(input[3], "") && equalStrings(input[4], "-p") && strcmp(input[5], "") && len == 6){
        grep_commit("", atoi(input[3]), input[5]);
    }
    //hook
    if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "hooks") && equalStrings(input[3], "list") && len ==4){
        printf("todo-check\neof-blank-space\nformat-check\nbalance-bracets\nstatic-error-check\nfile-size-check\ncharacter-limit\n");
        exit(0);
    }
    if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "applied") && equalStrings(input[3], "hooks") && len ==4){
        int number = extract_hook_status();
        char flag = 1;
        if((number & 1) == 1){
            printf("todo-check\n"); flag = 0;
        }
        if((number & (1<<1)) == (1<<1)){
            printf("eof-blank-space\n"); flag = 0;
        }
        if((number & (1<<2)) == (1<<2)){
            printf("format-check\n"); flag = 0;
        }
        if((number & (1<<3)) == (1<<3)){
            printf("balance-bracets\n"); flag = 0;
        }
        if((number & (1<<4)) == (1<<4)){
            printf("static-error-check\n"); flag = 0;
        }
        if((number & (1<<5)) == (1<<5)){
            printf("file-size-check\n"); flag = 0;
        }
        if((number & (1<<6)) == (1<<6)){
            printf("character-limit\n"); flag = 0;
        }
        if(flag){
            printf("\033[35mEMPTY\033[0m\n");
        }
    }
    if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "add") && equalStrings(input[3], "hook") && strcmp(input[4], "") && len ==5){
        int number = extract_hook_status();
        if(equalStrings(input[4], "todo-check") && (number & 1) == 0){ number += (1 << 0);}    
        else if(equalStrings(input[4], "eof-blank-space") && (number & (1<<1)) == 0){number += (1 << 1);}    
        else if(equalStrings(input[4], "format-check") && (number & (1 << 2)) == 0){number += (1 << 2);}    
        else if(equalStrings(input[4], "balance-bracets") && (number & (1 << 3)) == 0){number += (1 << 3);}    
        else if(equalStrings(input[4], "static-error-check") && (number & (1 << 4)) == 0){number += (1 << 4);}    
        else if(equalStrings(input[4], "file-size-check") && (number & (1 << 5)) == 0){number += (1 << 5);}    
        else if(equalStrings(input[4], "character-limit") && (number & (1 << 6)) == 0){number += (1 << 6);} 
        else{printf("\033[31mInvalid\033[0m hook id!\n"); exit(0);};   
        write_new_hook_status(number);
        printf("%s added \033[32msuccessfully\033[0m.\n", input[4]);
    }
    if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "remove") && equalStrings(input[3], "hook") && strcmp(input[4], "") && len ==5){
        int number = extract_hook_status();
        if(equalStrings(input[4], "todo-check") && (number & 1) != 0){ number -= (1 << 0);}    
        else if(equalStrings(input[4], "eof-blank-space") && (number & (1<<1)) != 0){number -= (1 << 1);}    
        else if(equalStrings(input[4], "format-check") && (number & (1 << 2)) != 0){number -= (1 << 2);}    
        else if(equalStrings(input[4], "balance-bracets") && (number & (1 << 3)) != 0){number -= (1 << 3);}    
        else if(equalStrings(input[4], "static-error-check") && (number & (1 << 4)) != 0){number -= (1 << 4);}    
        else if(equalStrings(input[4], "file-size-check") && (number & (1 << 5)) != 0){number -= (1 << 5);}    
        else if(equalStrings(input[4], "character-limit") && (number & (1 << 6)) != 0){number -= (1 << 6);} 
        else{printf("\033[31mInvalid\033[0m hook id!\n"); exit(0);};   
        write_new_hook_status(number);
        printf("%s removed \033[32msuccessfully\033[0m.\n", input[4]);
    }
    if(equalStrings(input[1], "pre-commit") && len == 2){
        int number = extract_hook_status();
        if(!number){printf("hook list is \033[35mEMPTY\033[0m!\n"); exit(0);}
        checkHooks_stage("", number, 'w');
    }
    if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "-f") && strcmp(input[3], "") && len == 4){
        int number = extract_hook_status();
        checkHooks_file(input[3], number, 'w');
    }
    if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "-f") && strcmp(input[3], "") && len > 4){
        for(int i = 3; i < len; i++){
            char temp[300];
            sprintf(temp, "neogit pre-commit -f \"%s\"", input[i]);
            system(temp);
        }
    }
    //stash
    if(equalStrings(input[1], "stash") && equalStrings(input[2], "push") && len == 3){
        check_near_main();
        char s [500];
        getcwd(s, 499);
        char address[500];
        strcpy(address, absolute_address_neogit());
        address[strlen(address) - 8] = 0;
        int id = current_id();
        chdir(address);
        char* dir_ = ".neogit\\stash";
        char command[300];
        if(check_type(dir_) != 1) {
            sprintf(command, "mkdir \"%s\"", dir_);
            system(command);
        }
        DIR* dir;
        dir = opendir(".");
        struct dirent* entry;
        if(dir == NULL){
            printf("unable to open %s directory\n", address);
            exit(-1);
        }

        char address_st[200];
        sprintf(address_st, ".neogit\\stash\\%d", id);
        sprintf(command, "mkdir \"%s\"", address_st);
        system(command);

        while ((entry = readdir(dir)) != NULL){
            push_stash(entry->d_name, id);
        }
        //stash created!
        char address_info[200];
        char address_info_commit[200];
        sprintf(address_info, ".neogit\\stash\\%d_info", id);
        sprintf(command, "mkdir \"%s\"", address_info);
        system(command);
        char* branch = calloc(100, sizeof(char));
        FILE* f = fopen(connectTwoString(address_info, "\\branch"), "w");
        int last_commit = get_last_hash('a');
        sprintf(address_info_commit, ".neogit\\commits\\%d_info\\", last_commit);

        //check branch
        char* branch_current = get_current_brach();
        if(last_commit == 0) strcpy(branch, "master");
        else{
            FILE* ff = fopen(connectTwoString(address_info_commit, "branch"), "r");
            fscanf(ff, "%[^\n]s", branch);
            fclose(ff);
        }
        if((branch_current[0] > '9' || branch_current[0] < '0') && last_commit != 0){
            strcpy(branch, branch_current);
        }
        fprintf(f, "%s", branch);
        fclose(f);
        //end of branch
        //massage
        f = fopen(connectTwoString(address_info, "\\massage"), "w");
        fprintf(f, "%s", "NULL");
        fclose(f);
        //end of massage
        //commit
        f = fopen(connectTwoString(address_info, "\\commit"), "w");
        fprintf(f, "%d", last_commit);
        fclose(f);
        //end of commit

        clear_stage();
        if(last_commit != 0)
            checkOut_byID(last_commit);
        else{
            printf("\033[35mNO COMMIT YET\033[0m.\n");
        }
        closedir(dir);
        append_end_stash_list(id);
        printf("\033[32mData are in stash now.\033[0m Now rou are on commit \033[34m%d\033[0m\n", last_commit);
        chdir(s);
    }
    if(equalStrings(input[1], "stash") && equalStrings(input[2], "push") && equalStrings(input[3], "-m") && strcmp(input[4], "") && len == 5){
        check_near_main();
        char s [500];
        getcwd(s, 499);
        char address[500];
        strcpy(address, absolute_address_neogit());
        address[strlen(address) - 8] = 0;
        int id = current_id();
        chdir(address);
        char* dir_ = ".neogit\\stash";
        char command[300];
        if(check_type(dir_) != 1) {
            sprintf(command, "mkdir \"%s\"", dir_);
            system(command);
        }
        DIR* dir;
        dir = opendir(".");
        struct dirent* entry;
        if(dir == NULL){
            printf("unable to open %s directory\n", address);
            exit(-1);
        }

        char address_st[200];
        sprintf(address_st, ".neogit\\stash\\%d", id);
        sprintf(command, "mkdir \"%s\"", address_st);
        system(command);

        while ((entry = readdir(dir)) != NULL){
            push_stash(entry->d_name, id);
        }
        //stash created!
        char address_info[200];
        char address_info_commit[200];
        sprintf(address_info, ".neogit\\stash\\%d_info", id);
        sprintf(command, "mkdir \"%s\"", address_info);
        system(command);
        char* branch = calloc(100, sizeof(char));
        FILE* f = fopen(connectTwoString(address_info, "\\branch"), "w");
        int last_commit = get_last_hash('a');
        sprintf(address_info_commit, ".neogit\\commits\\%d_info\\", last_commit);

        //check branch
        char* branch_current = get_current_brach();
        if(last_commit == 0) strcpy(branch, "master");
        else{
            FILE* ff = fopen(connectTwoString(address_info_commit, "branch"), "r");
            fscanf(ff, "%[^\n]s", branch);
            fclose(ff);
        }
        if((branch_current[0] > '9' || branch_current[0] < '0') && last_commit != 0){
            strcpy(branch, branch_current);
        }
        fprintf(f, "%s", branch);
        fclose(f);
        //end of branch

        f = fopen(connectTwoString(address_info, "\\massage"), "w");
        fprintf(f, "%s", input[4]);
        fclose(f);
        f = fopen(connectTwoString(address_info, "\\commit"), "w");
        fprintf(f, "%d", last_commit);
        fclose(f);


        clear_stage();
        if(last_commit != 0)
            checkOut_byID(last_commit);
        else{
            printf("\033[35mNO COMMIT YET\033[0m.\n");
        }
        closedir(dir);
        append_end_stash_list(id);
        printf("\033[32mData are in stash now.\033[0m Now rou are on commit \033[34m%d\033[0m\n", last_commit);
        chdir(s);
    }
    if(equalStrings(input[1], "stash") && equalStrings(input[2], "list") && len == 3){
        if(!findHash_stash(0)){
            printf("stash area is \033[35mempty\033[0m.\n");
            exit(0);
        }
        show_list_stash();
    }
    if(equalStrings(input[1], "stash") && equalStrings(input[2], "drop") && equalStrings(input[3], "-n") && strcmp(input[4], "") && len == 5){
        int id = findHash_stash(atoi(input[4]));
        if(id == 0){
            printf("\033[31mInvalid number\033[0m!\n");
            exit(0);
        }
        delete_stash(id);
        printf("\033[32mDeleted\033[0m.\n");
    }
    if(equalStrings(input[1], "stash") && equalStrings(input[2], "clear") && len == 3){
        int flag = 1;
        while(findHash_stash(0) != 0){
            flag = 0;
            delete_stash(findHash_stash(0));
        } 
        if(flag){
            printf("stash area is \033[35mempty\033[0m.\n");
        }
        else{
            printf("\033[32mDeleted\033[0m.\n");
        }
    }
    if(equalStrings(input[1], "stash") && equalStrings(input[2], "drop") && len == 3){
        int flag = 1;
        if(findHash_stash(0) != 0){
            flag = 0;
            delete_stash(findHash_stash(0));
        } 
        if(flag){
            printf("stash area is \033[35mempty\033[0m.\n");
        }
        else{
            printf("\033[32mDeleted\033[0m.\n");
        }
    }
    if(equalStrings(input[1], "stash") && equalStrings(input[2], "show") && strcmp(input[3], "") && len == 4){
        int id = findHash_stash(atoi(input[3]));
        if(id == 0){
            printf("\033[31mInvalid number\033[0m!\n");
            exit(0);
        }
        char* address = absolute_address_neogit();
        address = connectTwoString(address, "\\stash\\");
        char temp[100];
        sprintf(temp, "%d_info\\", id);
        address = connectTwoString(address, temp);
        FILE* f = fopen(connectTwoString(address, "commit"), "r");
        int commit = 0;
        fscanf(f, "%d", &commit);
        compare_stash_commit(id, commit, atoi(input[3]));
    }
    //tag
    if(equalStrings(input[1], "tag") && equalStrings(input[2], "-a") && strcmp(input[3], "")){
        char* massage = (char*)calloc(200, sizeof(char));
        strcpy(massage, "NULL");
        for(int i = 0; i < len; i++){
            if(equalStrings(input[i], "-m")){
                strcpy(massage, input[i+1]);
                break;
            }
        }
        int id = get_last_hash('a');
        for(int i = 0; i < len; i++){
            if(equalStrings(input[i], "-c")){
                id = atoi(input[i+1]);
                break;
            }
        }
        char f = 0;
        for(int i = 0; i < len; i++){
            if(equalStrings(input[i], "-f")){
                f = 1;
                break;
            }
        }

        if(is_Exist_tag(input[3]) != -1 && f == 0){
            printf("\033[35mtag name is existed!\033[0m\n");
            exit(0);
        }
        if(is_Exist_tag(input[3]) != -1 && f){
            delete_tag(input[3]);
        }
        if(id == 0){
            printf("\033[35mNo commit yet\033[0m\n");
            exit(0);
        }
        char* address1 = absolute_address_neogit();
        address1 = connectTwoString(address1, "\\commits\\");
        char temp[10];
        sprintf(temp, "%d", id);
        address1 = connectTwoString(address1, temp);
        if(!check_type(address1)){
            printf("\033[31minvalid\033[0m commit ID!\n");
            exit(0);
        }
        char** t = current_dateTime();
        unsigned long long total = atoi(t[5]) + 60*atoi(t[4]) + 60*60*atoi(t[3]) + 60*60*24*atoi(t[2]) + 4000000llu * atoi(t[1]) + 4000000000llu * atoi(t[0]);
        append_new_tag(input[3], id, current_name(), current_email(), total, dayOfNow(), massage);
        printf("a new tag \033[32mcreated\033[0m.\n");
    }
    if(equalStrings(input[1], "tag") && len == 2){
        char* address = absolute_address_neogit();
        char** names = calloc(200, sizeof(char));
        int index = 0;
        address = connectTwoString(address, "\\config\\tag");
        FILE* f = fopen(address, "r");
        char line[100];
        while(fgets(line, 99, f) != NULL){
            while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
                line[strlen(line) - 1] = 0;
            if(line[0] == 0) continue;
            char nameI[200];
            nameI[0] = 0;
            sscanf(line, "tag %[^\n]s", nameI);
            if(!equalStrings("", nameI)){
                names[index] = calloc(200, sizeof(char));
                strcpy(names[index], nameI);
                index++;
            }
        }
        fclose(f);
        for(int i = 0; names[i] != NULL; i++){
            for (int j = i+1; names[j] != NULL; j++){
                if(strcmp(names[i], names[j]) == 1){
                    char* temp = names[i];
                    names[i] = names[j];
                    names[j] = temp;
                }
            }
        }
        int flag = 1;
        for(int i = 0; names[i] != NULL; i++){
            flag = 0;
            printf("\033[36m{\033[0m%s\033[36m}\033[0m\n", names[i]);
        }
        if(flag){
            printf("\033[35mNo tag found\033[0m!\n");
        }
    }
    if(equalStrings(input[1], "tag") && equalStrings(input[2], "show") && strcmp(input[3], "") && len == 4){
        int lineN;
        if((lineN = is_Exist_tag(input[3])) == -1){
            printf("tag \033[31mnot found\033[0m!\n"); exit(0);
        }
        printf("\033[34m#############\033[0m\n");
        char* address = absolute_address_neogit();
        address = connectTwoString(address, "\\config\\tag");
        FILE* f = fopen(address, "r");
        char line[100];
        int a = 0;
        while(fgets(line, 99, f) != NULL){
            while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
                line[strlen(line) - 1] = 0;
            if(line[0] == 0) continue;
            char nameI[200];
            nameI[0] = 0;
            sscanf(line, "tag %[^\n]s", nameI);
            if(a == lineN){
                printf("%s\n", line);
                fgets(line, 99, f);
                printf("%s", line);
                fgets(line, 99, f);
                printf("%s", line);
                fgets(line, 99, f);
                printf("%s", line);
                fgets(line, 99, f);
                printf("%s", line);
                break;
            }
            a++;
        }
        printf("\033[34m#############\033[0m\n");
    }
    //merge
    if(equalStrings(input[1], "merge") && equalStrings(input[2], "-b") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){
        int a = extract_last_id_branch(input[3]);
        int b = extract_last_id_branch(input[4]);
        if(a <= 0 || b <= 0){
            printf("\033[31mInvalid branch name or no commit yet in branch!\033[0m\n");
            exit(0);
        }
        merge(a, b, input[3], input[4]);
    }
}   

int main(int argc, char* argv[]){
    //get inputs        #############################
    int len = argc;
    char** input = tokenizeInput(&len, argv);
    //end of getting    #############################
    get_commands_V1(input, len);
    get_commands_V2(input, len);
    return 0;
}