#ifndef MPC_MPC_WATCHDOG_H_
#define MPC_MPC_WATCHDOG_H_

#define WD_BEAM_MAX_TRIP_COUNT  (10) // < 255
#define WD_BEAM_LIMIT_MUM       (120.0f)
#define WD_BEAM_LIMIT_NM        (120000.0f)
#define WD_SOFB_MAX_TRIP_COUNT  (1) // < 255
#define WD_SOFB_MIN_MARGIN_MA   (500.0f)
#define WD_FOFB_MAX_TRIP_COUNT  (1) // < 255

void MPC_watchdog_initialize(void);

void MPC_watch_beam_mum(float beam_mum, int index);
void MPC_watch_beam_nm(float beam_nm, int index);
void MPC_watch_sofb_mA(float sofb_mA, int index);
void MPC_watch_fofb_mA(float fofb_mA, int index);

int MPC_check_watchdog(void); // no error -> returns 0, error -> returns 1
void MPC_print_watchdog_msg(void);


#endif /* MPC_MPC_WATCHDOG_H_ */
