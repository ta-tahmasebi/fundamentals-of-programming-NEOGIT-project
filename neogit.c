#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    printf("%d\n", argc);
    for(int i = 0; i < argc; i++){
        printf("|%s|  ", argv[i]);
    }
    //system("mkdir salam");
    return 0;
}