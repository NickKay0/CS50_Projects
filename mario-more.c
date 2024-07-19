#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//assignment:

//implement a program in C that recreates that pyramid, using hashes (#) for bricks, as in the below:
//   #  #
//  ##  ##
// ###  ###
//####  ####

//start
int main(void){
    //get input
    printf("Enter height: ");
    int height = 0;
    while(height<=0 || height > 8){
        char heightStr[256];
        scanf("%s", heightStr);

        height = atoi(heightStr);
        if(height<=0 || height > 8){
            printf("Invalid Height. Input Again: ");
        }
    }

    //build pyramid(s)
    for(int i = 1; i<=height;i++){
        for(int j = height; j > 0; j--){
            if(j<=i){
                printf("#");
            }else{
                printf(" ");
            }
        }

        printf(" ");
        printf(" ");

        for(int j = 1; j <= height; j++){
            if(j<=i){
                printf("#");
            }
        }

        printf("\n");
    }
}
