#include "neogitV1.c"

int main(int argc, char* argv[]){
    //get inputs        #############################
    int len = argc;
    char** input = tokenizeInput(&len, argv);
    //end of getting    #############################
    get_commands_V1(input, len);
    return 0;
}