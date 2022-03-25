/*
 * fgm_timing_utils.c
 *
 *  Created on: Apr 7, 2020
 *      Author: idris
 */
#include "fgm_utils.h"

/* Profiling Utilities */
#ifdef FGM_MPC_PROFILING
FGM_MPC_Timer FGM_MPC_total_timer;
FGM_MPC_Timer FGM_MPC_all_timers[FGM_MPC_n_timers];
#if (FGM_MPC_PROFILING_LEVEL == 2)
FGM_MPC_Timer FGM_MPC_grad_step_timer;      // 1
FGM_MPC_Timer FGM_MPC_proj_step_timer;      // 2
FGM_MPC_Timer FGM_MPC_beta_step_timer;      // 3
FGM_MPC_Timer FGM_MPC_term_step_timer;      // 4
FGM_MPC_Timer FGM_MPC_obsv_step_timer;      // 5
FGM_MPC_Timer FGM_MPC_init_vec_step_timer;  // 6
FGM_MPC_Timer FGM_MPC_init_proj_step_timer; // 7
char * FGM_MPC_timer_names[FGM_MPC_n_timers] =
{   "total", "grad_step", "proj_step", "beta_step", "term_step", "obsv_step", "init_vec_step", "init_proj_step"};
#else
char * FGM_MPC_timer_names[FGM_MPC_n_timers] =
{   "total"};
#endif /* FGM_MPC_PROFILING_LEVEL */
#endif /* FGM_MPC_PROFILING */

#ifdef FGM_MPC_PROFILING
FGM_MPC_Timer * FGM_MPC_get_all_timers(void)
{
    return &(FGM_MPC_all_timers[0]);
}

int FGM_MPC_get_num_timers(void)
{
    return FGM_MPC_n_timers;
}

char ** FGM_MPC_get_timer_names(void)
{
    return FGM_MPC_timer_names;
}

void FGM_MPC_init_timers(void)
{
    int i;
    FGM_MPC_all_timers[0] = FGM_MPC_total_timer;
#if (FGM_MPC_PROFILING_LEVEL > 1)
    FGM_MPC_all_timers[1] = FGM_MPC_grad_step_timer;
    FGM_MPC_all_timers[2] = FGM_MPC_proj_step_timer;
    FGM_MPC_all_timers[3] = FGM_MPC_beta_step_timer;
    FGM_MPC_all_timers[4] = FGM_MPC_term_step_timer;
    FGM_MPC_all_timers[5] = FGM_MPC_obsv_step_timer;
    FGM_MPC_all_timers[6] = FGM_MPC_init_vec_step_timer;
    FGM_MPC_all_timers[7] = FGM_MPC_init_proj_step_timer;
#endif
    for (i = 0; i < FGM_MPC_n_timers; i++)
    {
        FGM_MPC_all_timers[i].t_cumsum = 0.0;
        FGM_MPC_all_timers[i].n_calls = 0;
        FGM_MPC_all_timers[i].cycles_cumsum = 0;
    }
#ifdef SOC_C6678
    TSCL = 0;
#endif
}

void FGM_MPC_tic(const int i_timer)
{
#ifdef SOC_C6678
    FGM_MPC_all_timers[i_timer].tic = _itoll(TSCH, TSCL); // read 64bit register
#else
    clock_gettime(CLOCK_MONOTONIC, &(FGM_MPC_all_timers[i_timer].tic));
#endif // SOC_C6678
}

void FGM_MPC_toc(const int i_timer)
{
#ifdef SOC_C6678
    FGM_MPC_all_timers[i_timer].toc = _itoll(TSCH, TSCL); // read 64bit register
    FGM_MPC_all_timers[i_timer].cycles_cumsum += FGM_MPC_all_timers[i_timer].toc - FGM_MPC_all_timers[i_timer].tic;
    FGM_MPC_all_timers[i_timer].t_cumsum += (float)(FGM_MPC_all_timers[i_timer].toc - FGM_MPC_all_timers[i_timer].tic) / CLOCK_RATE;
    FGM_MPC_all_timers[i_timer].n_calls += 1;
#else
    struct timespec temp;

    clock_gettime(CLOCK_MONOTONIC, &(FGM_MPC_all_timers[i_timer].toc));

    if ((FGM_MPC_all_timers[i_timer].toc.tv_nsec - FGM_MPC_all_timers[i_timer].tic.tv_nsec) < 0)
    {
        temp.tv_sec = FGM_MPC_all_timers[i_timer].toc.tv_sec - FGM_MPC_all_timers[i_timer].tic.tv_sec - 1;
        temp.tv_nsec = 1e9 + FGM_MPC_all_timers[i_timer].toc.tv_nsec - FGM_MPC_all_timers[i_timer].tic.tv_nsec;
    }
    else
    {
        temp.tv_sec = FGM_MPC_all_timers[i_timer].toc.tv_sec - FGM_MPC_all_timers[i_timer].tic.tv_sec;
        temp.tv_nsec = FGM_MPC_all_timers[i_timer].toc.tv_nsec - FGM_MPC_all_timers[i_timer].tic.tv_nsec;
    }

    FGM_MPC_all_timers[i_timer].t_cumsum += (float)temp.tv_sec + (float)temp.tv_nsec / 1e9;
    FGM_MPC_all_timers[i_timer].n_calls += 1;
#endif // SOC_C6678
}

float FGM_MPC_average_time(FGM_MPC_Timer *t)
{
    return t->t_cumsum / ((float)t->n_calls);
}

float FGM_MPC_total_time(FGM_MPC_Timer *t)
{
    return t->t_cumsum;
}

void FGM_MPC_print_timer_info(FGM_MPC_Timer timer, char *timer_name)
{
    const double avg_time_seconds = FGM_MPC_average_time(&timer);
    const double total_time_seconds = FGM_MPC_total_time(&timer);
    const long int ncycles = timer.cycles_cumsum;
    printf("%s: Total time = %.6f s e-6, Time / n_calls = %.6f s e-6 (n_calls=%d) (Freq = %.6f Hz) (Cycles = %ld)\n",
            timer_name, total_time_seconds*1000000.0, avg_time_seconds*1000000.0, (int)timer.n_calls,
            1.0 / (avg_time_seconds), ncycles);
}
#endif
