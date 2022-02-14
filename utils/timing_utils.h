/*
 * timing_utils.h
 *
 *  Created on: Jul 21, 2020
 *      Author: idris
 */

#ifndef TIMING_UTILS_H_
#define TIMING_UTILS_H_

void init_timer(void);
void print_timing_info(const int n_ops_total, const long int elapsed_ticks, const char* name);
void tic(void);
void toc(void);
long int get_elapsed_ticks(void);

#endif /* TIMING_UTILS_H_ */
