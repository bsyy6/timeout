
#include <stdio.h>
#include <stdbool.h>
#include "timeout.h"
unsigned char T1 = 250;
const unsigned char T1max = 0xFF;  
bool clockedIn = false;
bool wrapped = false;

void incrementT1(){
    // this is mimicking counter going inside some timer interrupt
    if(T1 == T1max) wrapped = !wrapped; // flips on each overflow.
    T1++;
}

int main()
{
    bool someCondition = false;    
    timeOutObj timeout = timeOutBegin(&T1, 20, &wrapped);
    printf("%d - > %d [In] \n", T1, timeout.ttimeOut);
    while(!someCondition){
        // This while loop will check someCondition unitl it is true or timeout is reached.
        incrementT1();
        incrementT1(); 
        //someCondition = (T1 == 4);
        printf("%d - > %d\n", T1,timeout.ttimeOut);
        if(timeOutCheck(&timeout)){
            printf("Timeout!\n");
            break;
        }
    }
    printf("%d - > %d [Out] \n", T1, timeout.ttimeOut);
    return 0;
}
