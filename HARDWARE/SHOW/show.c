#include "show.h"
#include "remote.h"
#include "delay.h"
#include "stdlib.h"

 
 #define FLASH_SAVE_ADDR  0X08070000	
 #define FLASH_SAVE_ADDR1  0X08071000
 #define FLASH_SAVE_ADDR2  0X08072000	
 #define FLASH_SAVE_ADDR3  0X08073000

u8 pstrlcd[10];
u8 istrlcd[10];
u8 dstrlcd[10];

u8 p1[10];


float num;
float buffer;

void PSelect(void)
{
	u8 i;
	u8 key;
  u8 index = 1;
	u8 pstrlcd[10]={"0"};
	u8 *p = pstrlcd;
  LCD_Fill(250,45,480,65,WHITE);
	do
	{
		key=Remote_Scan();	

			switch(key)
			{		   	    
				case 2:index=0;break;		 	  	   
				case 144:*(p++)='.';break;		    
				case 104:*(p++)='1';break;		  
				case 152:*(p++)='2';break;	   
				case 176:*(p++)='3';break;	    
				case 48:*(p++)='4';break;		    
				case 24:*(p++)='5';break;		    
				case 122:*(p++)='6';break;		  
				case 16:*(p++)='7';break;			   					
				case 56:*(p++)='8';break;	 
				case 90:*(p++)='9';break;
				case 66:*(p++)='0';break;
				case 82:*(p--)=' ';break;		 
			}
		LCD_ShowString(300,50,200,16,16,pstrlcd);
		delay_ms(600);
	}while(index);
  LCD_Fill(250,45,480,60,WHITE);
	POINT_COLOR=BLACK;
  LCD_ShowString(300,50,200,16,16,pstrlcd);
	num=atof(pstrlcd);
 STMFLASH_Write(FLASH_SAVE_ADDR1,(u16*)pstrlcd,10);
}

void iSelect(void)
{
	u8 key;
  u8 index = 1;
	u8 istrlcd[10]={"0"};
	u8 *p = istrlcd;
  LCD_Fill(250,65,480,85,WHITE);
	do
	{
		key=Remote_Scan();	
			switch(key)
			{		   	    
				case 2:index=0;break;		 	  	   
				case 144:*(p++)='.';break;		    
				case 104:*(p++)='1';break;		  
				case 152:*(p++)='2';break;	   
				case 176:*(p++)='3';break;	    
				case 48:*(p++)='4';break;		    
				case 24:*(p++)='5';break;		    
				case 122:*(p++)='6';break;		  
				case 16:*(p++)='7';break;			   					
				case 56:*(p++)='8';break;	 
				case 90:*(p++)='9';break;
				case 66:*(p++)='0';break;
				case 82:*(p--)=' ';break;		 
			}
		LCD_ShowString(300,70,200,16,16,istrlcd);
		delay_ms(600);
	}while(index);
	LCD_Fill(250,65,480,85,WHITE);
	POINT_COLOR=BLACK;
	LCD_ShowString(300,70,200,16,16,istrlcd);
	num=atof(istrlcd);
	STMFLASH_Write(FLASH_SAVE_ADDR2,(u16*)istrlcd,10);
}

void dSelect(void)
{
	u8 key;
  u8 index = 1;
	u8 dstrlcd[10]={"0"};
	u8 *p = dstrlcd;
  LCD_Fill(250,85,480,105,WHITE);
	do
	{
		key=Remote_Scan();	
			switch(key)
			{		   	    
				case 2:index=0;break;		 	  	   
				case 144:*(p++)='.';break;		    
				case 104:*(p++)='1';break;		  
				case 152:*(p++)='2';break;	   
				case 176:*(p++)='3';break;	    
				case 48:*(p++)='4';break;		    
				case 24:*(p++)='5';break;		    
				case 122:*(p++)='6';break;		  
				case 16:*(p++)='7';break;			   					
				case 56:*(p++)='8';break;	 
				case 90:*(p++)='9';break;
				case 66:*(p++)='0';break;
				case 82:*(p--)=' ';break;		 
			}
		LCD_ShowString(300,90,200,16,16,dstrlcd);
		delay_ms(600);
	}while(index);
	LCD_Fill(250,85,480,105,WHITE);
	POINT_COLOR=BLACK;
	LCD_ShowString(300,90,200,16,16,dstrlcd);
	num=atof(dstrlcd);
	STMFLASH_Write(FLASH_SAVE_ADDR3,(u16*)dstrlcd,10);	
}


void targetspeed(void)
{
	u8 key;
  u8 index = 1;
	u8 str[10]={"0"};
	u8 *p = str;
  LCD_Fill(140,195,480,220,WHITE);
	do
	{
		key=Remote_Scan();	
			switch(key)
			{		   	    
				case 2:index=0;break;		 	  	   
				case 144:*(p++)='.';break;		    
				case 104:*(p++)='1';break;		  
				case 152:*(p++)='2';break;	   
				case 176:*(p++)='3';break;	    
				case 48:*(p++)='4';break;		    
				case 24:*(p++)='5';break;		    
				case 122:*(p++)='6';break;		  
				case 16:*(p++)='7';break;			   					
				case 56:*(p++)='8';break;	 
				case 90:*(p++)='9';break;
				case 66:*(p++)='0';break;
				case 82:*(p--)=' ';break;		 
			}
		LCD_ShowString(150,200,200,16,16,str);
		delay_ms(600);
	}while(index);
	
	num=atof(str);	
	if(num<=40)num = 40;
	if(num>=120)num = 120;
  LCD_Fill(140,195,480,220,WHITE);
		STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)str,10);
}

void lcdshow(void)
{
	
	 LCD_ShowString(30,50,200,16,16,"Proportion:");
	 LCD_ShowString(30,70,200,16,16,"Integration:");	
	 LCD_ShowString(30,90,200,16,16,"Differentiation:");
  	LCD_ShowString(30,120,200,16,16,"angle");
   LCD_ShowString(30,200,200,16,16,"Target_speed:");
	 LCD_ShowString(30,240,200,16,16,"speed:");	
	 POINT_COLOR=GREEN;
	 LCD_DrawRectangle(20, 360, 478, 500);	
	 POINT_COLOR=RED;
	 LCD_ShowNum(0,500,0,3,16);
	 LCD_ShowNum(0,430,60,3,16);
	LCD_ShowNum(0,370,120,3,16);
	LCD_ShowString(300,90,200,16,16,dstrlcd);
	LCD_ShowString(300,70,200,16,16,istrlcd);
  LCD_ShowString(360,50,200,16,16,p1);
}


void angle(void)
{
		u8 key;
  u8 index = 1;
	u8 str[10]={"0"};
	u8 *p = str;
  LCD_Fill(150,115,480,135,WHITE);
	do
	{
		key=Remote_Scan();	
		LCD_ShowString(30,120,200,16,16,"angle");
			switch(key)
			{		   	    
				case 2:index=0;break;		 	  	   
				case 144:*(p++)='.';break;		    
				case 104:*(p++)='1';break;		  
				case 152:*(p++)='2';break;	   
				case 176:*(p++)='3';break;	    
				case 48:*(p++)='4';break;		    
				case 24:*(p++)='5';break;		    
				case 122:*(p++)='6';break;		  
				case 16:*(p++)='7';break;			   					
				case 56:*(p++)='8';break;	 
				case 90:*(p++)='9';break;
				case 66:*(p++)='0';break;
				case 82:*(p--)=' ';break;		 
			}
		LCD_ShowString(150,120,200,16,16,str);
		delay_ms(600);
	}while(index);
	buffer=atof(str);		
	TIM_SetCompare2(TIM3,0);		
	
}






























