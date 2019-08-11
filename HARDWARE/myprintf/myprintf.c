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
    	va_list va;				//声明一个va_list类型的指向形参的指针va
    	va_start(va,format);			//初始化va，使其指向第一个可变参数
    			 x= bufferx;
           y= buffery;
    	while((ch = *format++) != '\0') //将format指向的值赋给ch，然后format指向下一个字符
    	{
    		if(ch != '%')				//未遇到%之前都直接输出
    		{
    			putchar(ch);
    			continue;
    		}
    		
    		//format指向的字符是\0就返回\0，不是的话返回这个字符并让format指向下一个字符
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
    				if(*format == 'f')//如果%l后是f就执行打印浮点型
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
    			case '%':		//发现连续%%时先打印第一个%
    			{
    				
    			}
    			default :
    			{
    				format --;	//将指针移回第一个%后面，进行下一轮判断
    				break;
    			}
    		}
    	}
    	va_end(va);				//结束可变参数的获取
    }
     
    /*此函数功能为输出十进制整数。用递归和取余的方式依次打印最高到最低*/
    void print_int(int argint)//以入参整数123举例，执行顺序为1,2,3,4...
    {
			int temp;
    	int value = argint / 10;//1.value为12 3.value为1 5.value为0，argint为1
    	if(value != 0)
    	{
    		print_int(value);//2.value为12做参数调用自身函数 4.value为1做参数调用自身函数
    	}
    	value = argint % 10;//6.对argint取余赋给value
      temp = value + '0';//7.将整型数字转成字符型数字
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
        if(y>=height)break;//退出
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
