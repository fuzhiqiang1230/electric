/**********************************包含头文件**********************************/
#include <reg52.h>
#include "1602.h"
#include<intrins.h> 
/************************************宏定义************************************/
#define uchar unsigned char
#define uint unsigned int
#define VELOCITY_30C	3495       //30摄氏度时的声速，声速V= 331.5 + 0.6*温度； 
//#define VELOCITY_23C	3453       //23摄氏度时的声速，声速V= 331.5 + 0.6*温度； 
/************************************位定义************************************/
sbit INPUT  = P3^2;                //回声接收端口
sbit OUTPUT = P3^6;                  //超声触发端口
sbit Beep   = P2^3;			           // 蜂鸣器
sbit DS     = P2^2;                //define interface
sbit E=P2^5;            //使能信号位，将E位定义为P2.5引脚
sbit BF=P0^7;           //忙碌标志位，，将BF位定义为P0.7引脚
/********************************定义变量和数组********************************/
long int distance=0;               //距离变量
uchar table[]="   Designed by  "; 
uchar table0[]="WeiLu & YuYaojia";
uchar table1[]="There's no echo.";
uchar table3[]="Distance:";
unsigned char code digit[10]={"0123456789"};     //定义字符数组显示数字
unsigned char code Str[]={"Test by DS18B20"};    //说明显示的是温度
unsigned char code Error[]={"Error!Check!"};     //说明没有检测到DS18B20
unsigned char code Temp[]={"T:"};             //说明显示的是温度
unsigned char code V[]={"V:"};              //温度单位
uchar count;
/***********************************函数声明***********************************/
extern void initLCD();//初始化LCD
extern void write_date(uchar date);
extern void write_com(uchar com);
extern void delay(uint x);
long int VELOCITY = 3453;       //摄氏度时的声速，声速V= 331.5 + 0.6*温度；
int fdebug;
/******************************************************************************/
/* 函数名称  : Delay_xMs                                                      */
/* 函数描述  : 延时函数                                                       */
/* 输入参数  : x                                                              */
/* 参数描述  : 延时时间                                                       */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Delay_xMs(unsigned int x)
{
	unsigned int i,j;
  for(i = 0;i < x;i++ )
	{
		for(j = 0;j < 3;j++ )
		{
         ;
    }
  }
}
/******************************************************************************/
/* 函数名称  : Alarm                                                          */
/* 函数描述  : 蜂鸣器发声函数                                                 */
/* 输入参数  : t                                                              */
/* 参数描述  : 发声的频率                                                     */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Alarm(uchar t)
{
	uchar i;
	for(i = 0;i < t;i++)
	{
		Beep = 0;
		Delay_xMs(1000/t);
		Beep = 1;
		Delay_xMs(1000/t);
	}
}	
/******************************************************************************/
/* 函数名称  : delayt                                                         */
/* 函数描述  : 延时函数                                                       */
/* 输入参数  : x                                                              */
/* 参数描述  : 延时时间数据                                                   */
/* 返回值    : 无                                                             */
/******************************************************************************/	
void delayt(uint x)
{
	uchar j;
  while(x-- > 0)
		{
			for(j = 0;j < 125;j++)
			{
            ;
      }
    }
}
/******************************************************************************/
/* 函数名称  : Init_MCU                                                       */
/* 函数描述  : 初始化单片机函数                                               */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Init_MCU(void)
{
	TMOD = 0x01;	  //定时器2初始化,设置为16位自动重装模式
 	TL0 = 0x66;
	TH0 = 0xfc;	    //1ms
  ET0 = 1;	      //开定时器2
	EA = 1;		      //总中断使能
}
/******************************************************************************/
/* 函数名称  : Init_Parameter                                                 */
/* 函数描述  : 初始化参数和IO口函数                                           */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Init_Parameter(void)
{
	 OUTPUT =0;//超声输出关闭
	 INPUT = 1;//超声输入关闭
	 count = 0;
	 distance = 0;
}
/******************************************************************************/
/* 函数名称  : display_char                                                   */
/* 函数描述  : 显示字符串函数                                                 */
/* 输入参数  : point,address                                                  */
/* 参数描述  : 写入的字符串的地址指针 1602显示对应的地址                      */
/* 返回值    : 无                                                             */
/******************************************************************************/
void display_char(uchar *point,uchar address)
{
	uchar i;
	write_com(0x80 + address);
	for(i = 0;i < 16; i++)
	{
		write_date(*point);
		point++;
	}
}
/******************************************************************************/
/* 函数名称  : display                                                        */
/* 函数描述  : 显示数字                                                       */
/* 输入参数  : number，address                                                */
/* 参数描述  : number写入的数据，address地址                                  */
/* 返回值    : 无                                                             */
/******************************************************************************/	
void display(int number,uchar address)
{
	uchar b,c,d,e;
	b= (number / 1000);
	c= (number / 100) % 10;
	d = (number / 10) % 10;
	e = number % 10;
	write_com(0x80 + address);
  write_date(b + 48);
	write_date(c + 48);
	write_date(d + 48);
	write_date(46);           //小数点的ASCII
	write_date(e + 48);
  write_date(99);           //"c"的ASCII
	write_date(109);          //"m"的ASCII
}
void displayv(int number,uchar address)
{
	uchar b,c,d,e;
	b= (number / 1000);
	c= (number / 100) % 10;
	d = (number / 10) % 10;
	e = number % 10;
	write_com(0x80 + address);
  write_date(b + 48);
	write_date(c + 48);
	write_date(d + 48);
	write_date(46);           //小数点的ASCII
	write_date(e + 48);
	write_date(109);          //"m"的ASCII
}
/******************************************************************************/
/* 函数名称  : Trig_SuperSonic                                                */
/* 函数描述  : 发出声波函数                                                   */
/* 输入参数  : i                                                              */
/* 参数描述  : 发出的脉冲次数                                                 */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Trig_SuperSonic()//出发声波40kHz
{
	////////////////////////////////////////////////////////////////////////////////////////////
	  OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
//		/////////////////////////////////////////////////////////////
}
/******************************************************************************/
/* 函数名称  : Measure_Distance                                               */
/* 函数描述  : 计算距离函数                                                   */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 0是超时没收到，1是收到了                                       */
/******************************************************************************/
int Measure_Distance(void)
{
	uchar l;
	int ii;
	uint h,y;
	ii=1;
	while(INPUT)
	{
		if(count ==17)
		{
			ii = 0;
			break;
		}
  }
	TR0 = 0;
	l = TL0;
	h = TH0;
	y = (h << 8) + l;
	y = y - 0xfc66;//us部分
	distance = y + 1000 * count;//计算总时间
	TL0 = 0x66;
	TH0 = 0xfc;
	delayt(30);
	distance = VELOCITY * distance / 20000;
	return ii;
}
/*****************************************************
函数功能：判断液晶模块的忙碌状态
返回值：result。result=1，忙碌;result=0，不忙
***************************************************/
bit BusyTest(void)
{
	bit result;
	RS=0;       //根据规定，RS为低电平，RW为高电平时，可以读状态
  RW=1;
  E=1;        //E=1，才允许读写
  _nop_();   //空操作
  _nop_();
  _nop_(); 
  _nop_();   //空操作四个机器周期，给硬件反应时间	
  result=BF;  //将忙碌标志电平赋给result
  E=0;         //将E恢复低电平
  return result;
}
/*****************************************************
函数功能：将模式设置指令或显示地址写入液晶模块
入口参数：dictate
***************************************************/
void WriteInstruction (unsigned char dictate)
{
	while(BusyTest()==1);   //如果忙就等待
	RS=0;                  //根据规定，RS和R/W同时为低电平时，可以写入指令
	RW=0;   
	E=0;                   //E置低电平(根据表8-6，写指令时，E为高脉冲，
                           // 就是让E从0到1发生正跳变，所以应先置"0"
  _nop_();
	_nop_();               //空操作两个机器周期，给硬件反应时间
	P0=dictate;            //将数据送入P0口，即写入指令或地址
	_nop_();
	_nop_();
	_nop_();
	_nop_();               //空操作四个机器周期，给硬件反应时间
	E=1;                   //E置高电平
	_nop_();
	_nop_();
	_nop_();
	_nop_();               //空操作四个机器周期，给硬件反应时间
	E=0;                  //当E由高电平跳变成低电平时，液晶模块开始执行命令
 }
/*****************************************************
函数功能：指定字符显示的实际地址
入口参数：x
***************************************************/
void WriteAddress(unsigned char x)
{
	WriteInstruction(x|0x80); //显示位置的确定方法规定为"80H+地址码x"
}
/*****************************************************
函数功能：将数据(字符的标准ASCII码)写入液晶模块
入口参数：y(为字符常量)
***************************************************/
void WriteData(unsigned char y)
{
	while(BusyTest()==1);  
	RS=1;           //RS为高电平，RW为低电平时，可以写入数据
	RW=0;
	E=0;            //E置低电平(根据表8-6，写指令时，E为高脉冲，
                     // 就是让E从0到1发生正跳变，所以应先置"0"
	P0=y;           //将数据送入P0口，即将数据写入液晶模块
	_nop_();
	_nop_();
 	_nop_();
  _nop_();       //空操作四个机器周期，给硬件反应时间
	E=1;           //E置高电平
	_nop_();
	_nop_();
	_nop_();
	_nop_();        //空操作四个机器周期，给硬件反应时间
	E=0;            //当E由高电平跳变成低电平时，液晶模块开始执行命令
}
/*****************************************************
函数功能：对LCD的显示模式进行初始化设置
***************************************************/
void LcdInitiate(void)
{
    Delay_xMs(15);               //延时15ms，首次写指令时应给LCD一段较长的反应时间
    WriteInstruction(0x38);     //显示模式设置：16×2显示，5×7点阵，8位数据接口
	  Delay_xMs(5);                //延时5ms　，给硬件一点反应时间
    WriteInstruction(0x38);
	  Delay_xMs(5);               //延时5ms　，给硬件一点反应时间
	  WriteInstruction(0x38);     //连续三次，确保初始化成功
	  Delay_xMs(5);               //延时5ms　，给硬件一点反应时间
	  WriteInstruction(0x0c);     //显示模式设置：显示开，无光标，光标不闪烁
	  Delay_xMs(5);               //延时5ms　，给硬件一点反应时间
	  WriteInstruction(0x06);     //显示模式设置：光标右移，字符不移
	  Delay_xMs(5);                //延时5ms　，给硬件一点反应时间
	  WriteInstruction(0x01);     //清屏幕指令，将以前的显示内容清除
	  Delay_xMs(5);             //延时5ms　，给硬件一点反应时间
 } 
/************************************************************************
以下是DS18B20的操作程序
 ************************************************************************/ 
sbit DQ=P2^2;
unsigned char time;   //设置全局变量，专门用于严格延时
/*****************************************************
函数功能：将DS18B20传感器初始化，读取应答信号
出口参数：flag 
***************************************************/
bit Init_DS18B20(void)	
{
 bit flag;         //储存DS18B20是否存在的标志，flag=0，表示存在；flag=1，表示不存在
 DQ = 1;           //先将数据线拉高
 for(time=0;time<2;time++) //略微延时约6微秒
     ;
 DQ = 0;           //再将数据线从高拉低，要求保持480~960us
 for(time=0;time<200;time++)  //略微延时约600微秒
     ;         //以向DS18B20发出一持续480~960us的低电平复位脉冲 
 DQ = 1;           //释放数据线（将数据线拉高） 
 for(time=0;time<10;time++)
     ;  //延时约30us（释放总线后需等待15~60us让DS18B20输出存在脉冲）
 flag=DQ;          //让单片机检测是否输出了存在脉冲（DQ=0表示存在）      
 for(time=0;time<200;time++)  //延时足够长时间，等待存在脉冲输出完毕
      ;
 return (flag);    //返回检测成功标志
}
/*****************************************************
函数功能：从DS18B20读取一个字节数据
出口参数：dat
***************************************************/ 
unsigned char ReadOneChar(void)
{
	unsigned char i=0;	
	unsigned char dat;  //储存读出的一个字节数据
	for (i=0;i<8;i++)
	{
		DQ =1;       // 先将数据线拉高
		_nop_();	    //等待一个机器周期	 
		DQ = 0;      //单片机从DS18B20读书据时,将数据线从高拉低即启动读时序
		dat>>=1;
		_nop_();     //等待一个机器周期		   
		DQ = 1;     //将数据线"人为"拉高,为单片机检测DS18B20的输出电平作准备
		for(time=0;time<2;time++)
             ;      //延时约6us，使主机在15us内采样
		if(DQ==1)
			dat|=0x80;  //如果读到的数据是1，则将1存入dat
		else
		  dat|=0x00;//如果读到的数据是0，则将0存入dat
		     //将单片机检测到的电平信号DQ存入r[i]	
		for(time=0;time<8;time++)
		      	;              //延时3us,两个读时序之间必须有大于1us的恢复期	
	 }	                    
	 return (dat);    //返回读出的十进制数据
}
/*****************************************************
函数功能：向DS18B20写入一个字节数据
入口参数：dat
***************************************************/  
WriteOneChar(unsigned char dat)
{
	unsigned char i=0;
	for (i=0; i<8; i++)
	{
		DQ =1;         // 先将数据线拉高
		_nop_();	     //等待一个机器周期	 
		DQ=0;          //将数据线从高拉低时即启动写时序       
		DQ=dat&0x01;   //利用与运算取出要写的某位二进制数据,
                       //并将其送到数据线上等待DS18B20采样	
		for(time=0;time<10;time++)	
		     ;//延时约30us，DS18B20在拉低后的约15~60us期间从数据线上采样
		DQ=1;          //释放数据线		    
		for(time=0;time<1;time++)
			  ;//延时3us,两个写时序间至少需要1us的恢复期
		dat>>=1;       //将dat中的各二进制位数据右移1位
	}
	for(time=0;time<4;time++)
	              ; //稍作延时,给硬件一点反应时间
}
/******************************************************************************
以下是与温度有关的显示设置
 ******************************************************************************/
 /*****************************************************
函数功能：显示没有检测到DS18B20
***************************************************/   
void display_error(void)
{
	unsigned char i;
	WriteAddress(0x00);    //写显示地址，将在第1行第1列开始显示
  i = 0;                //从第一个字符开始显示
  while(Error[i] != '\0')  //只要没有写到结束标志，就继续写
		{
			WriteData(Error[i]);   //将字符常量写入LCD
			i++;                 //指向下一个字符
			Delay_xMs(100);//延时100ms较长时间，以看清关于显示的说明
		}	
	while(1)              //进入死循环，等待查明原因
				  ;
} 
/*****************************************************
函数功能：显示温度的整数部分
入口参数：x
***************************************************/ 
void display_temp1(unsigned char x)
{
	unsigned char j,k,l;     //j,k,l分别储存温度的百位、十位和个位
  j=x/100;              //取百位
	k=(x%100)/10;    //取十位
	l=x%10;             //取个位  
	WriteAddress(0x02);    //写显示地址,将在第2行第7列开始显示
	WriteData(digit[j]);    //将百位数字的字符常量写入LCD
	WriteData(digit[k]);    //将十位数字的字符常量写入LCD
	WriteData(digit[l]);    //将个位数字的字符常量写入LCD
	Delay_xMs(50);         //延时1ms给硬件一点反应时间     
 }
 /*****************************************************
函数功能：显示温度的小数数部分
入口参数：x
***************************************************/ 
 void display_temp2(unsigned char x)
{
 	WriteAddress(0x06);      //写显示地址,将在第2行第11列开始显示
	WriteData(digit[x]);     //将小数部分的第一位数字字符常量写入LCD
	Delay_xMs(50);          //延时1ms给硬件一点反应时间
}
/*****************************************************
函数功能：做好读温度的准备
***************************************************/ 
void ReadyReadTemp(void)
{
	Init_DS18B20();     //将DS18B20初始化
	WriteOneChar(0xCC); // 跳过读序号列号的操作
	WriteOneChar(0x44); // 启动温度转换	  
	for(time=0;time<100;time++);	 //温度转换需要一点时间
	Init_DS18B20();     //将DS18B20初始化
	WriteOneChar(0xCC); //跳过读序号列号的操作
	WriteOneChar(0xBE); //读取温度寄存器,前两个分别是温度的低位和高位	
}

/******************************************************************************/
/* 函数名称  : main                                                           */
/* 函数描述  : 主函数                                                         */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/					
void main(void)
{
	unsigned char TL;     //储存暂存器的温度低位
  unsigned char TH;    //储存暂存器的温度高位
  unsigned char TN;      //储存温度的整数部分
	unsigned char TD;       //储存温度的小数部分
	int fflag;
	fdebug=0;
	VELOCITY=3453;       //23摄氏度时的声速，声速V= 331.5 + 0.6*温度；
  RW = 0;
	initLCD();
	Init_MCU();
	Init_Parameter();
	//Alarm(2);
	display_char(table,0x00);
	display_char(table0,0x40);
	Delay_xMs(30000);
	display_char(table0,0x00);
	display_char(table1,0x40);
	if(Init_DS18B20()==1)
		display_error();
	display_char(Temp,0x00);
	display_char(".",0x05);
	display_char(V,0x08);
	while(1)
	{
		fflag=0;
		Init_Parameter();
		TR0 = 1;
	  OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		OUTPUT = 1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	  OUTPUT = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();		
		//Trig_SuperSonic();         //触发超声波发射
//		TR0 = 1; 
//Delay_xMs(1);
		//TR0 = 1; 
		 while(INPUT==0)          //等待回声
         {
//             if (count==17)
//							 break;
         }
//				 Alarm(2);
		 fflag=Measure_Distance();        //计算脉宽并转换为距离
		 ReadyReadTemp();     //读温度准备
	   TL=ReadOneChar();    //先读的是温度值低位
		 TH=ReadOneChar();    //接着读的是温度值高位
		 TN=TH*16+TL/16;      //实际温度值=(TH*256+TL)/16,即：TH*16+TL/16
			                  //这样得出的是温度的整数部分,小数部分被丢弃了
		 VELOCITY=3315+6*TN;// 331.5 + 0.6*温度；
	   TD=(TL%16)*10/16;    //计算温度的小数部分,将余数乘以10再除以16取整，
			                  //这样得到的是温度小数部分的第一位数字(保留1位小数)
	   display_temp1(TN);    //显示温度的整数部分
	   display_temp2(TD);    //显示温度的小数部分
		 display_char(table3,0x40);
		 if(fflag){
		 display(distance,0x49);    //显示距离
		 }
		 displayv(VELOCITY,0x0a);
		 Init_Parameter();          // 参数重新初始化
		 delayt(1000);               //延时，两次发射之间要至少有10ms间隔
	 }	
}
/******************************************************************************/
/* 函数名称  : timer0                                                         */
/* 函数描述  : T0中断处理函数                                                 */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                              */
/******************************************************************************/
void timer0 (void) interrupt 1
{
	TF0 = 0;
	TL0 = 0x66;
	TH0 = 0xfc;
	count++;
	if(count == 18)//超声波回声脉宽最多18ms
	{
		TR0 =0;
		TL0 = 0x66; 
		TH0 = 0xfc;
		count = 0;
	}
}
/******************************************************************************/