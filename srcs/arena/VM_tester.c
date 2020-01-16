#include "arena.h"
#include "stdlib.h"
#include "bitMasks.h"


t_arena *make_vm()
{
    t_arena     *arena;
    t_args      *args;
    t_process   *process;
    int         i;

    arena = malloc(sizeof(t_arena));
    args = malloc(sizeof(t_args));
    process = malloc(sizeof(t_process));

    i = 0;
    while (i < MEM_SIZE)
    {
        arena->memory[i] = 0;
        i++;
    }
    arena->cycle = 0;
    arena->args = args;
    args->opcode = 17;

    i = 0;
    while (i < REG_NUMBER)
    {
        process->registre[i] = 0;
        i++;
    }
    process->registre[0] = 1;
    process->bytecode_size = 0;
    process->carry = 0;
    process->PC = 0;
    process->current_op = NULL;
    process->last_live = 0;
    process->next = NULL;

    set_args_to_zero(args);

}

byte      bytecode_gen(int one, int two, int three) // 1 reg, 2 dir, 3 ind
{
    byte    out;

    out = 0;
    out = out + one * SEVEN;
    out += two * FIVE;
    out += three * THREE;

    return (out);
}

/*
int     test_all_bytecodes(byte opcode, t_arena *arena)
{
    int i;
    int j;
    int k;

    int arg_num;

    arg_num = g_op_tab[opcode].arg_nb;
    arena->memory[0] = opcode;
    i = 1;
    
    while (i < 4)
    {
        j = 1;
        while (j < 4)
        {
            k = 1;
            while (k < 4)
            {
                arena->memory[1] = bytecode_gen(i, j, k * (k < arg_num));
                k++;
            }
            j++;
        }
        i++;
    }

}
*/