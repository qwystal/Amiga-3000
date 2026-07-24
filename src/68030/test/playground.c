#include <stdio.h>
#include <windows.h>

typedef struct
{
    void (*increment)(void);
    void (*decrement)(void);
    void (*delete)(void);
    int counter;
} PG;


// And C gets closer and closer to Classes and Methods
void initialize(PG *pg, void (*func)(PG*), void (**func_ptr)(void)) {   // take struct to be passed as an argument to the function, as well as
                                                                        // the function requiring a pointer to a PG struct as an argument, as well as
                                                                        // a pointer to a pointer to a void function, that gets set to the address of the intermediate function
    
    unsigned char *ins = VirtualAlloc(NULL, 64, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );

    unsigned char code[] = {
        0x48, 0x83, 0xEC, 0x28, // sub rsp, 40 apparently win api requires shadow space + alignement???
        0x48, 0xB9, // mov rcx, imm64
        0,0,0,0,0,0,0,0, // PG *
        0x48, 0xB8, // mov rax, imm64
        0,0,0,0,0,0,0,0, // pointer to function
        0xFF, 0xD0, // call rax
        0x48, 0x83, 0xC4, 0x28, // add rsp, 40
        0xC3 // ret
    };

    uintptr_t struct_addr  = (uintptr_t)pg;
    uintptr_t function_addr  = (uintptr_t)func;

    for (int i = 0; i < 8; i++) {
        code[6 + i] = (struct_addr >> (8 * i)) & 0xFF;
    }

    for (int i = 0; i < 8; i++) {
        code[16 + i] = (function_addr >> (8 * i)) & 0xFF;
    }

    for (int i = 0; i < sizeof(code); i++) {
        ins[i] = code[i];
    }

    *func_ptr = (void*)ins;
}

void inc(PG *pg) {
    pg->counter++;
}

void dec(PG *pg) {
    pg->counter = pg->counter / 2;
}

void delete(PG *pg) {
    free(pg);
}

int main() {
    PG *pg = malloc(sizeof(PG));
    memset(pg, 0, sizeof(PG));

    initialize(pg, &inc, &pg->increment);
    initialize(pg, &dec, &pg->decrement);
    initialize(pg, &delete, &pg->delete);

    printf("Value of counter: %d\n", pg->counter);

    pg->increment();
    pg->increment();
    pg->increment();
    pg->increment();

    printf("Value of counter: %d\n", pg->counter);

    pg->decrement();

    printf("Value of counter: %d\n", pg->counter);

    pg->delete();
    printf("Deleted.\n");
    printf("Value of counter: %d\n", pg->counter);

    return 0;
}