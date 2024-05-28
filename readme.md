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

## Concerns.
- "I can write this myself"
Yes, you can also build your own computer with beer caps too.

- "It is too complicated/heavy"
No, this is dead simple code optimized for embedded systems development. 
100~ bytes total for whole library/object and its usage all c all using standard libraries.
before adding the object (no printf included):

```sh
> size example.exe
   text    data     bss     dec     hex filename
   9980    2824     384   13188    3384 example.exe
```
after adding the object:

```sh
> size example.exe
   text    data     bss     dec     hex filename
  10012    2824     384   13220    33a4 example.exe
```

## How it Works

1. have counter `uint16_t` incrementing inside some time-based interrupt.
2. inside the interrupt add this line to detect overflows.

```c
// assume my counter is T1 uint16_t
if(T1 == T1max) wrapped = !wrapped; // flips on each overflow.
T1++;
 ```
where T1max is the maximum value ot T1 before it overflows to 0.

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