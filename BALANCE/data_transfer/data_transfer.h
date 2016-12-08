#ifndef		__DATA_TRANSFER_H
#define		__DATA_TRANSFER_H
typedef 	unsigned char	u8;
typedef 	unsigned char 	U8; 
#define BYTE0(dwTemp)       (*(U8 *)(&dwTemp))
#define BYTE1(dwTemp)       (*((U8 *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((U8 *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((U8 *)(&dwTemp) + 3))
void Data_Send_Check(U8 check);
void Data_Receive_Anl(U8 *data_buf,U8 num);
void Data_Send_Senser(float sv,float pv,float tv, float av);
void Data_Send_Status(void);
void Data_Send_Mpu6050(void);
void send_Data_To_Host(float sv,float pv,float tv, float av);
void Data_Send_PID2(void);

extern U8 FLAG_RETURN;
extern U8 data_to_send_ok;
extern U8 Pwm_Unable;
extern U8 data_to_send[40];
#endif
