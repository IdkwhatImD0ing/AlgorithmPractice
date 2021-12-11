#ifndef __QUICK_H__
#define __QUICK_H__

#include <stdint.h>

extern uint32_t max_stack_size;
extern uint32_t max_queue_size;

void quick_sort_stack(uint32_t *A, uint32_t n);

void quick_sort_queue(uint32_t *A, uint32_t n);

uint32_t get_quick_moves(void);

uint32_t get_quick_compares(void);

uint32_t get_sq_max();

#endif
