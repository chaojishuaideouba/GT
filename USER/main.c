#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "remote.h"
#include "show.h"
#include "timer.h"
#include "stmflash.h"
#include "myprintf.h"
 
 
 #define FLASH_SAVE_ADDR  0X08070000	
 #define FLASH_SAVE_ADDR1  0X08071000
 #define FLASH_SAVE_ADDR2  0X08072000	
 #define FLASH_SAVE_ADDR3  0X08073000
 
 
 
 
 
extern u8  TIM5CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ	
extern u32 temp;                  //���ڼ������뷽������ TIM5
 u16 speed=0;                    //���ת�� 
int pwm;
extern float num;
extern u16   i;
int Encoder;
float Position_KP;
float Position_KI;
float Position_KD;
u16 speed1=0;
u16 speed2=0;
u16 speed3=0;
u16 Target_speed = 120;        //�趨Ŀ���ٶ�Ϊxxx r/min
 static float Bias,Pwm,Integral_bias,Last_Bias;
u16 DrawPointX = 20;
u16 DrawPointY;
u16 buf = 500;
extern float buffer;
u8  stand;
u8  aa;
u8  len;
int Position_PID (int Encoder,int Target);
	

 int main(void)
 {	 
	 u8 datatemp[10];
	u8 key;
	 u8 keyboard;
	u8 t=0;	
 	u8 *str=0;
 
 
	 
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();	
	 setx(150);
	 sety(120);
	 myprintf("%s","close");
	 
	 STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,10);
	 num = atof(datatemp);
	 Target_speed = num;
	 
	 STMFLASH_Read(FLASH_SAVE_ADDR1,(u16*)datatemp,10);
	 num = atof(datatemp);
	 Position_KP = num;
	 LCD_Fill(250,45,480,65,WHITE);
	// LCD_ShowString(300,50,200,16,16,datatemp);
	 setx(300);
	 sety(50);
	 myprintf("%s",datatemp);

	 	STMFLASH_Read(FLASH_SAVE_ADDR2,(u16*)datatemp,10);
	 num = atof(datatemp);
	 Position_KI = num;
	 LCD_Fill(250,65,480,85,WHITE);
	 LCD_ShowString(300,70,200,16,16,datatemp);

	 
	STMFLASH_Read(FLASH_SAVE_ADDR3,(u16*)datatemp,10);
	 num = atof(datatemp);
	 Position_KD = num;
	 LCD_Fill(250,85,480,105,WHITE);
	 LCD_ShowString(300,90,200,16,16,datatemp);
	  	 
	TIM3_PWM_Init(8999,0);
	
	 
	//TIM6_Int_Init(499,7199);//10Khz�ļ���Ƶ�ʣ�������500Ϊ50ms  
	TIM5_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ���  
	 
	Remote_Init();			//������ճ�ʼ��		 	
 
 	POINT_COLOR=RED;		//��������Ϊ��ɫ 
 		 	  		    							  
	while(1)
	{
		key=Remote_Scan();	
		if(key)
		{	 
	
  			
			switch(key)
			{
				case 162:stand = 0;setx(150);sety(120);myprintf("%s","close");break;//LCD_ShowString(150,120,200,16,16,"CLOSE");break;
				case 0:str="ERROR";break;			       
				case 98:str="UP";PSelect();Position_KP = num;break;	    
				case 2:str="PLAY";break;		 
				case 226:str="ALIENTEK";angle();stand=1;break;		  
				case 194:str="RIGHT";targetspeed();Target_speed = num;break;	   
				case 34:str="LEFT";iSelect(); Position_KI =num;break;		  
				case 224:str="VOL-";break;		  
				case 168:str="DOWN";dSelect();Position_KD = num; break;		   
				case 144:str="VOL+";break;		     
			}

		}
////////////�ǶȺ���/////////		
		if(stand)
		{
      
			Target_speed = 60;
			aa = buffer*21/360;
			setx(350);
			sety(200);
			myprintf("%d",buffer);
			//LCD_ShowNum(350,200,buffer,3,16);
			LCD_Fill(250,195,480,220,WHITE);
			if(i>=aa+1)
			{
				TIM_SetCompare2(TIM3,0);
				i = 0;
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				LCD_Fill(250,195,480,220,WHITE);
			}	
			
		}
		speed3=speed2;	
		speed2=speed1;
		speed1=1796407/temp;
		speed=(speed1+speed3+speed2)/3;		
		pwm=pwm-Position_PID(speed,Target_speed);              //===λ��PID������         	
		TIM_SetCompare2(TIM3,pwm);		  // �趨ֵ��0-899֮�䣬�ֱ��Ӧռ�ձ�0-100%	
		lcdshow();		
		setx(150);
		sety(200);
		myprintf("%d",Target_speed);
	//	LCD_ShowNum(150,200,Target_speed,3,16);	
 		LCD_ShowNum(150,240,speed,3,16);	
		if(DrawPointX == 480)
		{
			DrawPointX = 20;
      LCD_Fill(0,350,480,500,WHITE);						
		}
	  DrawPointY  =  buf;
    DrawPointY -= speed;
	  LCD_Fast_DrawPoint(DrawPointX++,DrawPointY,BLACK);		
		/////��������//////////
		printf("%dr/min\n",speed);
				if(USART_RX_STA&0x8000)
		  {					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			for(t=0;t<len;t++)
			{
        num=atof(USART_RX_BUF);
				if(USART_RX_BUF[t]=='t')
				{
					stand = 0;
				Target_speed = num;
				STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)USART_RX_BUF,10);
					LCD_Fill(140,195,480,220,WHITE);
				}
				else if(USART_RX_BUF[t]=='a')
				{
					 buffer = num;
					stand = 1;
					LCD_Fill(150,115,480,135,WHITE);
					LCD_ShowString(150,120,200,16,16,USART_RX_BUF);
				}
				else if(USART_RX_BUF[t]=='p')
				{
					Position_KP = num;
					LCD_ShowString(300,50,200,16,16,USART_RX_BUF);
					STMFLASH_Write(FLASH_SAVE_ADDR1,(u16*)USART_RX_BUF,10);
				}
				else if(USART_RX_BUF[t]=='i')
				{
					Position_KI = num;
					LCD_ShowString(300,70,200,16,16,USART_RX_BUF);
					STMFLASH_Write(FLASH_SAVE_ADDR2,(u16*)USART_RX_BUF,10);
				}
				else if(USART_RX_BUF[t]=='d')
				{
					Position_KD = num;
					LCD_ShowString(300,90,200,16,16,USART_RX_BUF);
					STMFLASH_Write(FLASH_SAVE_ADDR3,(u16*)USART_RX_BUF,10);
				}
				
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
	  	}
	}
}


int Position_PID (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //�������
}

