/************************************宏定义************************************/
#define uchar unsigned char
#define uint unsigned int
/************************************位定义************************************/
sbit dula  = P2^6;
sbit wela  = P2^7;
sbit RS    = P1^0;
sbit RW    = P1^1;
sbit lcden = P2^5;
/******************************************************************************/
/* 函数名称  : delay                                                          */
/* 函数描述  : 延时函数                                                       */
/* 输入参数  : x                                                              */
/* 参数描述  : 延时时间                                                       */
/* 返回值    : 无                                                             */
/******************************************************************************/
void delay(uint x)
{
	uint a,b;
	for(a = x;a > 0;a--)
    {
		for(b = 10;b > 0;b--) 
        {
            ;
        }
    }
}
/******************************************************************************/
/* 函数名称  : write_com                                                      */
/* 函数描述  : 1602写命令函数                                                 */
/* 输入参数  : com                                                            */
/* 参数描述  : 控制命令                                                       */
/* 返回值    : 无                                                             */
/******************************************************************************/
void write_com(uchar com)
{
	P0 = com;
	RS = 0;
	lcden = 0;
	delay(10);
	lcden = 1;
	delay(10);
	lcden = 0;	
}
/******************************************************************************/
/* 函数名称  : write_date                                                     */
/* 函数描述  : 1602写数据函数                                                 */
/* 输入参数  : date                                                           */
/* 参数描述  : 要写入的数据                                                   */
/* 返回值    : 无                                                             */
/******************************************************************************/
void write_date(uchar date)
{
	P0 = date;
	RS = 1;
	lcden = 0;
	delay(10);
	lcden = 1;
	delay(10);
	lcden = 0;	
}
/******************************************************************************/
/* 函数名称  : initLCD                                                        */
/* 函数描述  : 1602初始化函数                                                 */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void initLCD(void)
{
	dula = 0;
	wela = 0;
	write_com(0x38);
	delay(20);
	write_com(0x0f);
	delay(20);
	write_com(0x06);
	delay(20);
	write_com(0x01);
	delay(20);	
}
/******************************************************************************/
