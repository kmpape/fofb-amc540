#ifndef IMC_WATCHDOG_H_
#define IMC_WATCHDOG_H_

#define WD_IMC_LEN  (192)

#define WD_IMC_BEAM_MAX_TRIP_COUNT  (10) // < 255
#define WD_IMC_BEAM_LIMIT_MUM       (100.0f)
#define WD_IMC_BEAM_LIMIT_NM        (100000.0f)
#define WD_IMC_SOFB_MAX_TRIP_COUNT  (1) // < 255
#define WD_IMC_SOFB_MIN_MARGIN_A    (2.0f)
#define WD_IMC_FOFB_MAX_TRIP_COUNT  (1) // < 255

void IMC_watchdog_initialize(void);

void IMC_watch_beam_mum(float beam_mum, int index);
void IMC_watch_beam_nm(float beam_nm, int index);
void IMC_watch_sofb_mA(float sofb_mA, int index);
void IMC_watch_fofb_mA(float fofb_mA, int index);

int IMC_check_watchdog(void); // no error -> returns 0, error -> returns 1
char* IMC_get_watchdog_msg(void);


#endif /* IMC_WATCHDOG_H_ */
