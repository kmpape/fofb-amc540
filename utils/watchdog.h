#ifndef WATCHDOG_H_
#define WATCHDOG_H_


#define WD_LEN  (172)

#define WD_SETP_mA_SCALING          (1e3f)
#define WD_SOFB_MIN_MARGIN_SCALED   (2e6)


#define WD_BEAM_MAX_TRIP_COUNT      (10) // < 255
#define WD_BEAM_LIMIT_MUM           (100.0f)
#define WD_BEAM_LIMIT_NM            (100000.0f)
#define WD_BEAM_LIMIT_NM_INT        (100000)

#define WD_SOFB_MAX_TRIP_COUNT      (1) // < 255
#define WD_FOFB_MAX_TRIP_COUNT      (1) // < 255

void watchdog_initialize(void);
void watchdog_read_SOFB_mA(float *sofb_mA); // [mA]

void watch_beam(int *beam_in); // [nm]
void watch_setpoints(int *setp_out);  // [A]*1e6

int check_watchdog(void); // no error -> returns 0, error -> returns 1
void print_watchdog_msg(void);

void test_watchdog(void);


#endif /* WATCHDOG_H_ */
