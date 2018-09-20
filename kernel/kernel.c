#include "screen.h"

void kernel_main() {
    cls();
    char *msg = "Welcome to KawaiiOS, the eduactional operating system\n";
    print_string(msg);

    char *author = "By: Ahmed Khaled <nemoload@aol.com>\n\n";
    print_string(author);

    print_char('\nR',x,y,4);
    print_char('\nG',x,y,2);
    print_char('\nB',x,y,1);
    // print_string(msg);
    // char *video = (char*)0xb8000;
    // // video[0] = 'X';
    // // video[1] = 'Y';
    // // video[3] = 'Z';
    // // video[5] = 'A';
    // // video[1] = 0x0F;
    // int i = 0; 
    // int y = 0;   
    // while(1)
    // {
    //     if (msg[y] == 0){
    //         // *video = msg[1];
    //         break;
    //     }
    //     video[i] = msg[y];
    //     i+=2;
    //     y++;

    // }

}