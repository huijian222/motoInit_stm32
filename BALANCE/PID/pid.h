#ifndef		__PID_H
#define		__PID_H
typedef struct PID{float SetSpeed,ActualSpeed,err,err_last,Kp,Ki,Kd,voltage,integral;}PID;

void PID_init(void);
float PID_realize(float speed ,float actual);
float PID_application(float target,float adc);
extern PID PID_PID_2;
#endif
