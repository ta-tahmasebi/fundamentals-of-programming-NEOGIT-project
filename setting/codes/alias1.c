#include<string.h>
#include<stdio.h>
#include<stdlib.h>

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
char ** tokenizeInput(int* len, char** argv){
    if(*len > 95){
        FILE* f = fopen("temp_neogit", "w");
        fprintf(f, "n");
        fclose(f);
        exit(-1);
    }
    char** input = (char**)calloc(110, sizeof(char*));
    int i;
    for(i = 0; i < *len; i++)
        *(input + i) = argv[i+1];
    i--;
    for(; i< 100; i++)
        *(input + i) = (char *)calloc(2,sizeof(char));
    return input;
}


int main(int argc, char* argv[]){
    int len = argc;
    char** input = tokenizeInput(&len, argv);
    len --;
    // printf("%d\n", len);
    // for(int i = 0; i < 50; i++){
    //     printf("%d = %s\n", i, input[i]);
    // }
    if(equalStrings(input[1], "config") && equalStrings(input[2], "-global") && equalStrings(input[3], "user.name") && strcmp(input[4], "") && equalStrings(input[5], "") && len == 5){}
    else if(equalStrings(input[1], "config") && equalStrings(input[2], "-global") && equalStrings(input[3], "user.email") && strcmp(input[4], "") && equalStrings(input[5], "") && len == 5){}
    else if(equalStrings(input[1], "config") && equalStrings(input[2], "user.name") && strcmp(input[3], "") && equalStrings(input[4], "") && len == 4){}
    else if(equalStrings(input[1], "config") && equalStrings(input[2], "user.email") && strcmp(input[3], "") && equalStrings(input[4], "") && len == 4){}
    else if(equalStrings(input[1], "config") && equalStrings(input[2], "-global") && (input[3][0] == 'a' && input[3][1] == 'l' && input[3][2] == 'i' && input[3][3] == 'a' && input[3][4] == 's' && input[3][5] == '.' && strlen(input[3]) > 6) && strcmp(input[4], "") && equalStrings(input[5], "") && len == 5){       }
    else if(equalStrings(input[1], "config") && (input[2][0] == 'a' && input[2][1] == 'l' && input[2][2] == 'i' && input[2][3] == 'a' && input[2][4] == 's' && input[2][5] == '.' && strlen(input[2]) > 6) && strcmp(input[3], "") && equalStrings(input[4], "") && len == 4){       }
    else if(equalStrings(input[1], "init") && equalStrings(input[2], "") && len == 2){}
    else if(equalStrings(input[1], "add") && strcmp(input[2], "") && !strcheck(input[2] , '-') && equalStrings(input[3], "") && len == 3){}
    else if(equalStrings(input[1], "add") && equalStrings(input[2], "-redo") && len == 3){}
    else if(equalStrings(input[1], "add") && strcmp(input[2], "") && !strcheck(input[2] , '-') && len > 3){}
    else if(equalStrings(input[1], "add") && equalStrings(input[2], "-f") && strcmp(input[3], "") && len >= 4){}
    else if(equalStrings(input[1], "status")){}
    else if(equalStrings(input[1], "reset") && strcmp(input[2], "") && !strcheck(input[2] , '-') && equalStrings(input[3], "") && len == 3){}
    else if(equalStrings(input[1], "reset") && strcmp(input[2], "") && !strcheck(input[2] , '-') && len > 3){}
    else if(equalStrings(input[1], "reset") && equalStrings(input[2], "-f") && strcmp(input[3], "") && len >= 4){}
    else if(equalStrings(input[1], "reset") && equalStrings(input[2], "-undo") && len == 3){}
    else if(equalStrings(input[1], "___check_if_a_file_is_in_stage__")){}
    else if(equalStrings(input[1], "add") && equalStrings(input[2], "-n") && strcmp(input[3], "") && len == 4){}
    else if(equalStrings(input[1], "commit") && !equalStrings(input[2], "-m") && !equalStrings(input[2], "-s")){}
    else if(equalStrings(input[1], "commit") && equalStrings(input[2], "-m")){}
    else if(equalStrings(input[1], "set") && equalStrings(input[2] , "-m") && strcmp(input[3], "") && equalStrings(input[4] , "-s") && strcmp(input[5], "") && len == 6){}
    else if(equalStrings(input[1], "log") && len == 2){}
    else if(equalStrings(input[1], "log") && equalStrings(input[2], "-n") && strcmp(input[3], "") && len == 4){}
    else if(equalStrings(input[1], "log") && equalStrings(input[2], "-branch") && strcmp(input[3], "") && len == 4){}
    else if(equalStrings(input[1], "log") && equalStrings(input[2], "-author") && strcmp(input[3], "") && len == 4){}
    else if(equalStrings(input[1], "log") && equalStrings(input[2], "-since") && strcmp(input[3], "") && len == 4){}
    else if(equalStrings(input[1], "log") && equalStrings(input[2], "-before") && strcmp(input[3], "") && len == 4){}
    else if(equalStrings(input[1], "log") && equalStrings(input[2], "-search") && strcmp(input[3], "") && len >= 4){}
    else if(equalStrings(input[1], "status") && equalStrings(input[2], "-a") && len == 3){}
    else if(equalStrings(input[1], "checkout") && strstr(input[2], "HEAD-") == input[2] && len == 3){}
    else if(equalStrings(input[1], "checkout") && strcmp(input[2], "") && len == 3){}
    else if(equalStrings(input[1], "tree")){}
    else if(equalStrings(input[1], "print_double_write_L__")){}
    else if(equalStrings(input[1], "print_double_write_L__M")){}
    else if(equalStrings(input[1], "print_double_write_R__M")){}
    else if(equalStrings(input[1], "print_double_write_R__")){}
    else if(equalStrings(input[1], "diff") && equalStrings(input[2], "-b") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){}
    else if(equalStrings(input[1], "diff") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){}
    else if(equalStrings(input[1], "diff_conflict_neogit") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){}
    else if(equalStrings(input[1], "diff") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && strstr(input[5], "-line1") && strcmp(input[6], "") && len == 7){}
    else if(equalStrings(input[1], "diff") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && strstr(input[5], "-line2") && strcmp(input[6], "") && len == 7){}
    else if(equalStrings(input[1], "diff") && equalStrings(input[2], "-f") && strcmp(input[3], "") && strcmp(input[4], "") && strstr(input[5], "-line1") && strcmp(input[6], "") &&  strstr(input[7], "-line2") && strcmp(input[8], "")  && len == 9){}
    else if(equalStrings(input[1], "diff") && equalStrings(input[2] , "-c") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){}
    else if(equalStrings(input[1], "grep") && equalStrings(input[2], "-f") && strcmp(input[3], "") && equalStrings(input[4], "-p") && strcmp(input[5], "") && len == 6){}
    else if(equalStrings(input[1], "grep") && equalStrings(input[2], "-c") && strcmp(input[3], "") && equalStrings(input[4], "-p") && strcmp(input[5], "") && equalStrings(input[6], "-n") && len == 7){}
    else if(equalStrings(input[1], "grep") && equalStrings(input[2], "-c") && strcmp(input[3], "") && equalStrings(input[4], "-p") && strcmp(input[5], "") && len == 6){}
    else if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "hooks") && equalStrings(input[3], "list") && len ==4){}
    else if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "applied") && equalStrings(input[3], "hooks") && len ==4){}
    else if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "add") && equalStrings(input[3], "hook") && strcmp(input[4], "") && len ==5){}
    else if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "remove") && equalStrings(input[3], "hook") && strcmp(input[4], "") && len ==5){}
    else if(equalStrings(input[1], "pre-commit") && len == 2){}
    else if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "-f") && strcmp(input[3], "") && len == 4){}
    else if(equalStrings(input[1], "pre-commit") && equalStrings(input[2], "-f") && strcmp(input[3], "") && len > 4){}
    else if(equalStrings(input[1], "stash") && equalStrings(input[2], "push") && len == 3){}
    else if(equalStrings(input[1], "stash") && equalStrings(input[2], "push") && equalStrings(input[3], "-m") && strcmp(input[4], "") && len == 5){}
    else if(equalStrings(input[1], "stash") && equalStrings(input[2], "list") && len == 3){}
    else if(equalStrings(input[1], "stash") && equalStrings(input[2], "drop") && equalStrings(input[3], "-n") && strcmp(input[4], "") && len == 5){}
    else if(equalStrings(input[1], "stash") && equalStrings(input[2], "clear") && len == 3){}
    else if(equalStrings(input[1], "stash") && equalStrings(input[2], "drop") && len == 3){}
    else if(equalStrings(input[1], "stash") && equalStrings(input[2], "show") && strcmp(input[3], "") && len == 4){}
    else if(equalStrings(input[1], "tag") && equalStrings(input[2], "-a") && strcmp(input[3], "")){}
    else if(equalStrings(input[1], "tag") && len == 2){}
    else if(equalStrings(input[1], "tag") && equalStrings(input[2], "show") && strcmp(input[3], "") && len == 4){}
    else if(equalStrings(input[1], "merge") && equalStrings(input[2], "-b") && strcmp(input[3], "") && strcmp(input[4], "") && len == 5){}
    else{
        FILE* f = fopen("temp_neogit", "w");
        fprintf(f, "n");
        fclose(f);
    }
}