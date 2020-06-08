
#ifndef JOYSTICK_H_
#define JOYSTICK_H_


#define REF_AVCC (1 <<REFS0) // Reference = AVCC = 5 V
#define REF_INT (1 << REFS0) | (1 << REFS1) //Internal reference 2.56 V
#define JOYSTICK_INIT 632
#define DELTA 25

unsigned short coords[2];

void ADC_init();
void wait(long numOP);
void joystickTest();
void fetchAnalogStick();


#endif /* JOYSTICK_H_ */
