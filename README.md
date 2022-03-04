### 1. Go to branch demo.
### 2. Clone that branch into your local directory on PC.
### 3. You have to start from a file "part1.c" this is a file, where you will have ready STRUCT with data fetched from a file data.txt.
## 3.1 I've left comments in a code in order to better understand what's going on.
### 4. Your task is to make an algorithm, that will iterate, let's say 5000 times and during those iteration it will change logic gate value dependending on some conditions.
### 5. Look at this little demo, try to understand and implement:
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
    int time = 1;
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

timer = 0; 
array_of_previous_values[size = size of logic gate, in our case = 3] = { 0 };
waiting_for_change[3] = { 0 };
while (timer < 4) {
     // Iteration nr. 1, timer = 0
     // Check all logic gates and input, is there anything to change?
     gate1 ? .. input[0] = a(what value is a? = 0) .. input[1] = x2 (what value is x2 = 0) .. 0 or 0 = 0 ..previous[0] == 0? yes .. dont change .. gate1.value = 0
     
     gate2 ? ... input[0] = x1(what value is x1? = 0) ... input[1] = NULL (skip) ... 0 not NULL = 1 ... previous[1] == 1? no ... gate2.time == timer? no ... waiting[1] = 1 ... time = timer + 1) ... gate2.value = 0
     
     gen ? ... value ? (=0) .. time == timer? ... (3 == 0) ? ... no .. continue...
     
     //Iteration nr. 2, timer = 1
     gate1 ? ... all remains the same ...
     gate2 ? ... value is still 1 (0 not NULL) ... time == timer ? .. yes .. waiting[1] == 1? .. yes .. gate2.value = 1 .. set waiting[1] = 0, set previous[1] = 1
     // SINCE CHANGE WAS MADE refresh gate1.time = timer + 2, gate2.time = timer + 1, don't do it on generator :)
     gen .. remains the same...
     
     //Itearation nr. 3, timer = 2
     gate1 ? ..input[0] = 0... input[1] = 1 ... previous[0] == (0 or 1 = 1)? .. no .. time == timer? .. (1+2=3 == 2)? .. no .. previous[0] =
}
```

