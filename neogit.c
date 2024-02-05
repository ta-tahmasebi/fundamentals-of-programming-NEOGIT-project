#include "neogitV2.c"

//   *(IN THE NAME OF THE GOD)*
//   ** AMIRMAHDI TAHMASEBI  **
//           402106178


void get_commands_alias(char* name){
    //global
    char* address;
    FILE* f;
    char line[1000];
    int index = 0;
    address = connectTwoString("D:\\SETTINGS\\config\\alias", "");
    f = fopen(address, "r");
    while(fgets(line, 199, f) != NULL){
        while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
            line[strlen(line) - 1] = 0;
        if(equalStrings(line, name) && index % 2 == 0){
            fgets(line, 199, f);
            while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
                line[strlen(line) - 1] = 0;
            system(line);
            exit(0);
        }
        index++;
    }
    //local
    address =  gitFolder();
    address = connectTwoString(address,"//config//alias");
    f = fopen(address, "r");
    index = 0;
    while(fgets(line, 199, f) != NULL){
        while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
            line[strlen(line) - 1] = 0;
        if(equalStrings(line, name) && index % 2 == 0){
            fgets(line, 199, f);
            while(line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == ' ')
                line[strlen(line) - 1] = 0;
            system(line);
            exit(0);
        }
        index++;
    }
}


int main(int argc, char* argv[]){
    //get inputs        #############################
    int len = argc;
    char** input = tokenizeInput(&len, argv);
    //end of getting    #############################
    get_commands_V1(input, len);
    //get_commands_V2(input, len);
    get_commands_alias(input[1]);
    printf("\033[31mInvalid inputs\033[0m!\n");
    return 0;
}