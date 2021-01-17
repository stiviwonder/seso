#ifndef func_h
#define func_h
void create_threads(float f_clock, int f_timer, int f_pgen);
void init_cpu(int core_kop);
int mmu(int faddr, int vaddr);
int* read_op(int bin);
void free_the_mem(int addr, int size);
void print_program(int address, int size, int id);
#endif
