#include <stdbool.h>
#include <limits.h>
#include "timeout.h"


timeOutObj timeOutBegin(uint16_t* currentTimePtr,uint16_t delay, bool* wrapped){
    // returns a timoutObj
    timeOutObj to;
    
    const uint16_t currentTime_max = UINT16_MAX; // change if type  of currentTime is changed
    to.currentTimePtr = currentTimePtr;
    to.ttimeOut = (*currentTimePtr + delay) % (currentTime_max) + 1;
    
    if(to.ttimeOut < *currentTimePtr){
     to.wrapCycle = !*wrapped;
    }else{
     to.wrapCycle = *wrapped;
    }
    to.waitForTimerWrap = wrapped;
    to.currentWrapStatusPtr = wrapped;
    
    return (to);
}

bool timeOutCheck(timeOutObj *toPtr){
    // returns true when timeout passed 
    return !(*toPtr->currentTimePtr < toPtr->ttimeOut  || *toPtr->currentWrapStatusPtr != toPtr->wrapCycle);
}
