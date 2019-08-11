#include "myprintf.h"
#include<stdarg.h>
#include"lcd.h"

 
int width = 200;
int height= 16;
 int x;
 int y;
 u16 bufferx;
 u16 buffery;
 
 
 
 
void print_int(int argint);
void print_float(double argflt);
void print_str(char *argstr);




   void myprintf(char *format,...)
    {
    	char ch;
    	int argint;
    	float argflt;
    	char *argstr;
    	va_list va;				//����һ��va_list���͵�ָ���βε�ָ��va
    	va_start(va,format);			//��ʼ��va��ʹ��ָ���һ���ɱ����
    			 x= bufferx;
           y= buffery;
    	while((ch = *format++) != '\0') //��formatָ���ֵ����ch��Ȼ��formatָ����һ���ַ�
    	{
    		if(ch != '%')				//δ����%֮ǰ��ֱ�����
    		{
    			putchar(ch);
    			continue;
    		}
    		
    		//formatָ����ַ���\0�ͷ���\0�����ǵĻ���������ַ�����formatָ����һ���ַ�
    		switch(*format != '\0'?*format++:'\0')
    		{
    			case '\0':
    			{
    				putchar('%');
    				break;
    			}
    			case 'd':
    			{
    				argint = va_arg(va,int);
    				print_int(argint);				
    				break;
    			}
    			case 'l':
    			{
    				if(*format == 'f')//���%l����f��ִ�д�ӡ������
    				{
    					argflt = va_arg(va,double);
    					print_float(argflt);
    					format ++;
    				}
    				break;
    			}
    			case 'f':
    			{
    				argflt = va_arg(va,double);
    				print_float(argflt);
    				break;
    			}			
    			case 'c':
    			{
    				putchar(va_arg(va,int));
    				break;
    			}
    			case 's':
    			{
    				argstr = va_arg(va,char *);
    				print_str(argstr);				
    				break;
    			}
    			case '%':		//��������%%ʱ�ȴ�ӡ��һ��%
    			{
    				
    			}
    			default :
    			{
    				format --;	//��ָ���ƻص�һ��%���棬������һ���ж�
    				break;
    			}
    		}
    	}
    	va_end(va);				//�����ɱ�����Ļ�ȡ
    }
     
    /*�˺�������Ϊ���ʮ�����������õݹ��ȡ��ķ�ʽ���δ�ӡ��ߵ����*/
    void print_int(int argint)//���������123������ִ��˳��Ϊ1,2,3,4...
    {
			int temp;
    	int value = argint / 10;//1.valueΪ12 3.valueΪ1 5.valueΪ0��argintΪ1
    	if(value != 0)
    	{
    		print_int(value);//2.valueΪ12���������������� 4.valueΪ1����������������
    	}
    	value = argint % 10;//6.��argintȡ�ำ��value
      temp = value + '0';//7.����������ת���ַ�������
    	LCD_ShowChar(x,y,temp,16,0);
			x+=8;
    }
     
    void print_float(double argflt)
    {
    	int i;
    	int num;
			long int n; 
    	char ptr[7];
    	ptr[6] = '\0';
    	print_int(argflt);
    	LCD_ShowChar(x,y,'.',16,0);
    	x+=8;
    	 n = argflt * 1000000;
    	n = n % 1000000;
    	for(i = 5;i > -1;i--)
    	{
    		num = n % 10;
    		n = n / 10;
    		ptr[i] = num + '0';
    	}
    	print_str(ptr);
    }
     
    void print_str(char *argstr)		
    {
				u8 x0=x;
    	 while(*argstr != '\0')
    	{

	      width+=x;
	      height+=y;
     
        if(x>=width){x=x0;y+=16;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*argstr,16,0);
        x+=8;
        argstr++;									
    	}			
    }
void setx(num)
{
	    bufferx = num;
			
			
}
void sety(num)
{
	    buffery = num;
	
			
}
