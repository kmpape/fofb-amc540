/*
 * timing_utils.c
 *
 *  Created on: Jul 21, 2020
 *      Author: idris
 */

#include <c6x.h>
#include <stdio.h>
#include "timing_utils.h"

const double CLOCK_RATE = 1000000000.0;
long int t0, t1;

void init_timer(void) {
    TSCL = 0;
}

void tic() {
    t0 = _itoll(TSCH, TSCL);
}
void toc() {
    t1 = _itoll(TSCH, TSCL);
}
long int get_elapsed_ticks() {
    return (t1 - t0);
}

void print_timing_info(const int n_ops_total, const long int elapsed_ticks, const char* name) {
    const int n_cycles = (int)(elapsed_ticks);
    printf("+++++++++++++++++++++++\n");
    printf("%s: n cycles = %d\n%s: ops per cycle = %f (n_ops=%d)\n", name, n_cycles,
           name, (((double)n_ops_total) / ((double)n_cycles)), n_ops_total);
    printf("%s: time = %f s e-6\n", name, ((double)n_cycles) / CLOCK_RATE * 1000.0 * 1000.0);
    printf("-----------------------\n");
}

