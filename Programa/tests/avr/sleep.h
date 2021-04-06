#ifndef SLEEP_H
#define SLEEP_H

enum mode_sleep{SLEEP_MODE_PWR_DOWN};

void set_sleep_mode(short);
void sleep_mode(void);
void sei(void);

#endif // SLEEP_H
