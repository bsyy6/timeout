# Timeout

Timeout is a simple utility that allows you to set a timeout for a specific task or operation in your firmware. It helps you control the maximum time a task can take, preventing it from running indefinitely.

## example:
I want to communicate with some device and wait for its response

```
// pseudo code
send connect_with_device command
while(no repsone){
    // do nothing 
}
start communication
```
becomes this

```
// pseudo code
send connect_with_device command
timeOutBegin();
while(no repsone){
    // do nothing 
    if (timeoutCheck){
        break;
    }
}

if (!timoutCheck){
    start communication
}else{
    inform user while loop timed out
}
```

This function also avoids `timer-overflows`

## I could just make some counter myself.
Yes, you can also build your own computer from with beer taps too.

## How it Works

1. have counter `uint16_t` incrementing inside some time-based interrupt.
2. inside the interrupt add this line to detect overflows.

```c
// assume my counter is T1 uint16_t
if(T1 == T1max) wrapped = !wrapped; // flips on each overflow.
T1++;
 ```

3. before the while loop call the timeOutBegin on an timeout object.
```c
timeOutObj timeout;
timeout = timeOutBegin(&T1, 20, &wrapped); // [timeout at => T1 + 20]
```
4. add this line inside your while loop.
```c
while(someConditon){
    // do other things...
    if(timeOutCheck(&timeout)){
            printf("Timeout!\n");
            break;
    }
}
```
## Author
Created by: Waleed Alghilan, May-2024 (Artificial Hands Area in Scuola Superiore Sant'Anna)