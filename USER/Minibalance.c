#include "sys.h"
#include "control.h"	
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
�˴���Ŀ����㷨��ͨ����֤�ģ�������ͬѧ�ǲ�Ҫֱ��ʹ�õ��������棬��Ϊ��ͬ�ĵ������ͬ�Ľⷨ���������İ�װ������Ӱ�쵽���յĿ���ϵͳ
����ݳ���ĵײ�Ϳ��ƴ���������Ӳ��һ��һ������ƥ��
**************************************************************************/
u8 Way_Angle=1;                             //��ȡ�Ƕȵ��㷨��1:DMP2�������� ���Ըĳ�3 �������˲���
u8 Flag_Show=0,Flag_Stop=1;                 //��ʾ��־λ ��ͣ��־λ
int Temperature;                            //��ʾ�¶�
int Moto1,Moto2,Moto3,Moto4;               //���PWM���� Ӧ��Motor�� ��Moto�¾�	
void initMoto(void);
int main(void)
{ 
    
	Stm32_Clock_Init(9);            //ϵͳʱ������
	delay_init(72);                 //��ʱ��ʼ�� 
	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
	LED_Init();                     //��ʼ���� LED ���ӵ�Ӳ���ӿ�
	KEY_Init();                     //������ʼ��
	OLED_Init();                    //OLED��ʼ��
	uart_init(72,115200);           //��ʼ������1
    uart2_init(36,9600);            //����2��ʼ��
	MiniBalance_PWM_Init(1999,144);   //=====��ʼ��PWM 10KHZ������������� �����ʼ������ӿ� ��ΪMiniBalance_PWM_Init(9999,35) 200HZ �޸ĵ�50HZ 
    initMoto();
    IIC_Init();                     //ģ��IIC��ʼ��
    MPU6050_initialize();           //=====MPU6050��ʼ��	
	DMP_Init();                     //��ʼ��DMP     
  //Timer1_Init(49,7199);           //=====5MS��һ���жϷ�����
	//Set_Pwm(3900,3900,3900,3900);
	//delay_ms(1000);

//	Set_Pwm(3500,3500,3500,3500);
//	delay_ms(1000);
//	Set_Pwm(200,200,200,200);
	while(1)
		{
//     	if(Way_Angle==1)                     //DMPû���漰���ϸ��ʱ�����⣬����������ȡ
//				{
//					Read_DMP();                      //===��ȡ���ٶȺ����
//				}  
//				if(Flag_Stop==1)//ʹ��OLED��ʾ����PC�˴��ڵ�������
//				{
//					Way_Angle=1;//ʹ��DMP
//					Temperature=Read_Temperature();  //===��ȡMPU6050�����¶ȴ��������ݣ����Ʊ�ʾ�����¶ȡ�	
//					oled_show(); //===��ʾ����
//					printf("x:%f  Y%f   gyro[0]%d gyro[1]%d\r\n",Pitch,Roll,gyro[0],gyro[1]);//����λ����������
//				}	
//				
	} 
}

void initMoto(void) { //ң�ظ������2MS ������ ����� 1ms �� Ȼ��Ϳ��Է���
    
    Set_Pwm(1000,1000,1000,1000);  //����PWM����Ϊ250HZ һ������Ϊ4MS ��ΪPWM����Ϊ2000 ��������1000 �� PWM�ߵ�ƽ2MS
    delay_ms(1800);   //���ӳٿ��ܵ����ⲻ��
    delay_ms(1800);
    Set_Pwm(500,500,500,500); //500������ͬ�� һ������4MS 500/2000 ��0.5MS �����ӳٷ�ֹ�޷���⵽
    delay_ms(1000);
    Set_Pwm(1000,1000,1000,1000);    
}
