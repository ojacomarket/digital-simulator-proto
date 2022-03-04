## 1. Go to branch demo.
## 2. Clone that branch into your local directory on PC.
## 3. You have to start from a file "part1.c" this is a file, where you will have ready STRUCT with data fetched from a file data.txt.
### 3.1 I've left comments in a code in order to better understand what's going on.
## 4. Your task is to make an algorithm, that will iterate, let's say 5000 times and during those iteration it will change logic gate value dependending on some conditions.
## 5. Look at this little demo, try to understand and implement:
```
struct gate1 {
    int value = 0;
    unsigned char name[10] = x1;
    int time = 2;
    enum gates logic_gate = or;
    int *inputs[MAX_INPUT] = a, x2;
}

struct gate2 {
    int value = 0;
    unsigned char name[10] = x2;
    int time = 0;
    enum gates logic_gate = not;
    int *inputs[MAX_INPUT] = x1;
}

struct generator {
    int value = 0;
    unsigned char name[10] = a;
    int time = 3;
    enum gates logic_gate = gen;
    int *inputs[MAX_INPUT] = NULL;
}

timer = 0; //0 - 10
next[size = size of logic gate, in our case = 3] = { 0 }; // hold next value of logic gate, until time to change is obtained
wait[3] = { 0 }; // "1" if value of gate hve been changed and we wait for correct time, "0" if no actions been happend.

while (timer < 10) {

     // Iteration nr. 1, timer = 0
    
     gate1 ? --> input[0] = 0 --> input[1] = 0 --> 0 or 0 --> next[0] = 0 --> next[0] == gate1.value ? --> yes --> OK
     
     gate2 ? ... input[0] = 0 --> input[1] = NULL --> 0 not NULL = 1 --> next[1] = 1 --> next[1] == gate2.value ? --> no --> gate2.time == timer? --> yes --> gate2.value = next[1] --> wait[0] = 0 --> /* since changes were made, update all time values of gates (not gen) */ gate1.time = (timer + gate1.time) --> gate2.time = (timer + gate2.time) --> OK
     
     gen ? ... gen.value =? --> 0 --> OK
     
     //Iteration nr. 2, timer = 1
     
     gate1 ? --> input[0] = 0 --> input[1] = 1 --> 0 or 1 --> next[0] = 1 --> next[0] == gate1.value ? --> no --> gate2.time == timer? --> no (timer is 1 and gate1.time is 2) --> next[1] = 1 --> wait[1] = 1 --> OK
     
     gate2 ? ... input[0] = 0 --> input[1] = NULL --> 0 not NULL = 1 --> next[1] = 1 --> next[1] == gate2.value ? --> yes --> OK
     
     gen ? ... gen.value =? --> 0 --> OK
     
     //Itearation nr. 3, timer = 2
     
     gate1 ? --> input[0] = 0 --> input[1] = 1 --> 0 or 1 --> next[0] = 1 --> next[0] == gate1.value ? --> no --> gate2.time == timer? --> yes (timer is 2 and gate1.time is 2) --> gate1.value = next[0] --> wait[0] = 0 --> /* since changes were made, update all time values of gates (not gen) */ gate1.time = (timer + gate1.time) --> gate2.time = (timer + gate2.time) --> OK
     
     gate2 ? -->input[0] = 1 --> input[1] = NULL --> 1 not NULL = 1 --> next[1] = 0 --> next[1] == gate2.value ? --> no --> gate2.time == timer ? --> yes --> gate2.value = next[1] --> wait[1] = 0 /* since changes were made, update all time values of gates (not gen) */ gate1.time = (timer + gate1.time) --> gate2.time = (timer + gate2.time) --> OK
     
     gen ? ... gen.value =? --> 0 --> OK
     
     // And so on..
     
}
```

## 6. I hope you got an idea! Now let me explain how to use existing code.
## 7. You look at the struct:

```
struct gate1 {
    int value = 0; // this is value, that you SHOULD update in your program
    unsigned char name[10] = x1; // don't update this
    int time = 2; // this is value you SHOULD update in your program
    enum gates logic_gate = or; // don't update this
    int *inputs[MAX_INPUT] = a, x2; // don't update this (this is pointers, they will assign values as any changes been made)
}
```
## 8. So you build up algorithm ON TOP of the existing code, and basically all you need is this struct array, which is already inside a file "part1.c".
## 9. All other logic you implement by your self.
