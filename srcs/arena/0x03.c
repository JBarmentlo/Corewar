#include "arena.h"

void    x03(t_arena *arena, t_process *process)
{
    byte    *dest;
    byte    *src;

    src = reg_nb_to_ptr(process, arena->args->val[0]);
    if (arena->args->type[1] == T_REG)
    {
        dest = reg_nb_to_ptr(process, arena->args->val[1]);
        reg_write_uint(process, process->registre[arena->args->val[0]], arena->args->val[1]);
    }
    else
    {
        dest = ind_to_ptr_idx(arena, arena->args->val[1], process->PC);
        mem_memcopy_endian_switch(arena, src, (process->PC + (arena->args->val[1] % IDX_MOD)) % MEM_SIZE, REG_SIZE);
    }
    printf("0x03\n");
}