#include<conio.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "neogitV1.c"

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
            printf("invalid ID!\n");
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
        printf("unable to open %s directory\n", address1);
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
            printf("invalid ID!\n");
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
        printf("unable to open %s directory\n", address1);
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