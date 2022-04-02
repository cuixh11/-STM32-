#include "xianshispi.h"
#include "oledfont.h"

/**
  * @brief Timing of write operations（SPI）
  * @retval None
  */
void OLED_WR_Byte(unsigned char dat,unsigned char cmd) //在 4 线串行模式下，只能往模块写数据而不能读数据(only write)
{	
	unsigned char i;			  
	if(cmd) 
		{OLED_DC(1);}  //D/C选择命令（0）或者数据（1）
	else  
		{OLED_DC(0);}	  
	
	OLED_CS(0);				//拉低片选CS
	
	for(i=0;i<8;i++)	//时钟线SCLK不断产生时钟信号，上升沿数据线有效
		{			  
			OLED_SCL(0);
			if(dat&0x80)	//10001000 10000000判断置1位的真假，if-else
				{
					OLED_SDIN(1);
				}
			else
				{
					OLED_SDIN(0);
				}
			OLED_SCL(1); 	//拉高释放
			dat<<=1;			//右移，判断下一位for
		}		
		
	OLED_CS(1);				//释放
	//OLED_DC(1);   	  
} 


/**
  * @brief Set the starting coordinates
  * @retval None
  */
void OLED_Set_Pos(unsigned char x, unsigned char y) 	//设置起始坐标
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);											//命令为 0XB0~B7，该命令用于设置页地址，其低三位D0,D1,D1的值对应着 GRAM 的页地址0-7。
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);					//??1010 yyyy&0x1111 0000=0x1010 0000>>4=0000 1010 | 0001 0000=0001 1010=0X1~该指令用于设置显示时的起始列地址高四位。右移动4位并保存，且让第5位为1
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 						  //??xxxx 0101&0000 1111=0000 0101 | 0000 0001=0000 0101=0X0~该指令用于设置显示时的起始列地址低四位。保留最后一位数据，并让最后一位数据置1
}   	

/**
  * @brief Open or Close the show
  * @retval None
  */
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //电荷泵设置
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON，bit2，开启/关闭0001 0100
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD); 
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}	

/**
  * @brief Erase the image information, refresh?
  * @retval None
  */
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);//页地址
		OLED_WR_Byte (0x02,OLED_CMD);  //??列地址低四位   //0000 0010
		OLED_WR_Byte (0x10,OLED_CMD);  //??列地址高四位   //0001 0000   
		for(n=0;n<128;n++) OLED_WR_Byte(0x00,OLED_DATA); 
	}
}
//void OLED_Clear2(void)  
//{  
//	unsigned char i,n;		    
//	for(i=0;i<2;i++)  
//	{  
//		OLED_WR_Byte (0xb0+i,OLED_CMD);
//		OLED_WR_Byte (0x02,OLED_CMD);    
//		OLED_WR_Byte (0x10,OLED_CMD);       
//		for(n=0;n<128;n++)OLED_WR_Byte(0xff,OLED_DATA); 
//	} 
//}

/**
  * @brief Display character function
  * @retval None
  */
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned int chr)	//显示字符函数,页寻址模式
{      	
	unsigned int c=0,i=0;	
	c=chr-' ';												// chr会锁定字符在字库中的的序号 https://blog.csdn.net/Qinhaifu/article/details/88865639
	if(x>Max_Column-1){x=0;y=y+2;} 		//x大于128列，x回车，y+2，对
	/* 根据字符的大小选择相应字库，根据chr得到具体的字符地址 */
	if(SIZE==16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		{OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);}		//font高8*宽16
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)														//换页见font
		{OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);}
	}
	else 																					//font高6*宽12,未考虑24*12
	{	
		OLED_Set_Pos(x,y+1);
		for(i=0;i<6;i++)
		{
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);
		}
	}
	
}


/**
  * @brief mode：0是反显，1是正常显示，这里采用两个函数解决
  * @retval None
  */
void OLED_ShowChar111(unsigned char x,unsigned char y,unsigned int chr)
{      	
	unsigned int c=0,i=0;	
	c=chr-' ';			
	if(x>Max_Column-1){x=0;y=y+2;}
	if(SIZE==16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		OLED_WR_Byte(~F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte(~F8X16[c*16+i+8],OLED_DATA);
	}
	else 
	{	
		OLED_Set_Pos(x,y+1);
		for(i=0;i<6;i++)
		{
			OLED_WR_Byte(~F6x8[c][i],OLED_DATA);
		}
	}
}


/**
  * @brief 返回m*n的结果
  * @retval result
  */
//unsigned int oled_pow(unsigned char m,unsigned char n)
//{
//	unsigned int result=1;	 
//	while(n--)result*=m;    
//	return result;
//}		

/**
  * @brief ？？未用到
  * @retval None
  */
//void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size)
//{         	
//	unsigned char t,temp;
//	unsigned char enshow=0;						   
//	for(t=0;t<len;t++)
//	{
//		temp=(num/oled_pow(10,len-t-1))%10;
//		if(enshow==0&&t<(len-1))
//		{
//			if(temp==0)
//			{
//				OLED_ShowChar(x+(size/2)*t,y,' ');
//				continue;
//			}else enshow=1;  
//		}
//	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
//	}
//} 



/**
  * @brief Display string function
  * @retval None
  */
/* （x,y）是显示的坐标，*p是字符串的首地址，no是正反显示 */
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char no) 
{
	unsigned int j=0;  
	while (chr[j]!='\0')							//str的截止符判断
	{		
		if(no)	{OLED_ShowChar(x,y,chr[j]);}
		else		{OLED_ShowChar111(x,y,chr[j]);}		
		x+=8;													 //留一个‘\0’的空间
		if(x>120){x=0;y+=2;}					/* 如果初始行放不下，移动到下下行 */
		j++;
	}
}


/**
  * @brief Display Chinese string
  * @retval None
  */
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char z,unsigned char no,unsigned char no1)
{   //显示中文字符串“”。第一个是X轴位置，第二个是Y轴位置，第三个是显示字的个数	,第四个是字在字库中的位置，第五个没有用    
	unsigned char t,i,adder=0;
	if(no1)
	{
		for(i=0;i<z;i++)
		{
				OLED_Set_Pos(x+i*16,y);		
				for(t=0;t<16;t++)	
					{
						OLED_WR_Byte(Hzk[2*no+i*2][t],OLED_DATA);	
						adder+=1; //地址偏移
					}
				OLED_Set_Pos(x+i*16,y+1);	
				for(t=0;t<16;t++)	
					{
						OLED_WR_Byte(Hzk[2*no+i*2+1][t],OLED_DATA);
						adder+=1; //地址偏移
					}	
		}	
	}
	else{
				for(i=0;i<z;i++)
					{
						OLED_Set_Pos(x+i*16,y);		
						for(t=0;t<16;t++)
							{
								OLED_WR_Byte(~Hzk[2*no+i*2][t],OLED_DATA);
								adder+=1;
							}
						OLED_Set_Pos(x+i*16,y+1);	
						for(t=0;t<16;t++)
							{
								OLED_WR_Byte(~Hzk[2*no+i*2+1][t],OLED_DATA);
								adder+=1;
							}	
					}	
			}
}


//用不到
//void OLED_ShowCHinese1(unsigned char x,unsigned char y,unsigned char z,unsigned char no)
//{      			    
//	unsigned char t,i,adder=0;
//	for(i=0;i<z;i++)
//	{

//			OLED_Set_Pos(x+i*16,y);		for(t=0;t<16;t++){OLED_WR_Byte(Hzk1[2*no+i*2][t],OLED_DATA);adder+=1;}
//			OLED_Set_Pos(x+i*16,y+1);	for(t=0;t<16;t++){OLED_WR_Byte(Hzk1[2*no+i*2+1][t],OLED_DATA);adder+=1;}	
//	}						
//}


/**
  * @brief ？？未用到
  * @retval None
  */
//void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char *p)
//{ 	
// 	unsigned int j=0;
// 	unsigned char x,y;
// 	if(y1%8==0) y=y1/8;      
// 	else y=y1/8+1;
//	for(y=y0;y<y1;y++)
//	{
//		OLED_Set_Pos(x0,y);
//   	 	for(x=x0;x<x1;x++)
//	    {      
//	    	OLED_WR_Byte(*p++,OLED_DATA);	    	
//	    }
//	}
//} 				


/**
  * @brief Initialization function
  * @retval None
  */
void OLED_Init(void) 
{
/* 复位 */	
  HAL_Delay(1);
  OLED_RST(1);
	
	HAL_Delay(1);
	OLED_RST(0);
	
	HAL_Delay(1);
	OLED_RST(1); 
	
	HAL_Delay(1);
	
/* 开始写入初始化命令 */	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel，关闭显示
	
	OLED_WR_Byte(0x02,OLED_CMD);//---set low column address，指令用于设置显示时的起始列地址低四位
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address，指令用于设置显示时的起始列地址高四位
	
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)，设置显示开始行[5:0]
	
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register，对比度设置
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness，默认0x7F（范围1~255，越大越亮）
	
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping,段重定义设置,bit0: 0,0->0; 1,0->127;     
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction,设置COM扫描方向;取决于bit3,0普通模式;1重定义模式 COM[N-1]->COM0;N:驱动路数   
	
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display，设置显示方式;bit0:1,反相显示;0,正常显示
	
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)，设置驱动路数
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty，路数默认0x3F（1/64）
	
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)，设置显示偏移 
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset,偏移默认为0
	
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency,设置时钟分频因子
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period,设置预充电周期
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock,[3:0],PHASE 1;[7:4],PHASE 2;
	
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration,设置COM硬件引脚配置
	OLED_WR_Byte(0x12,OLED_CMD);//[5:4]配置
	
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh,设置VCOMH 电压倍率
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level,设置显示开始行[5:0]
	
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02),设置内存地址模式
	OLED_WR_Byte(0x02,OLED_CMD);//[1:0],00，水平地址模式  ;01，垂直地址模式;   10,页地址模式;默认10;
	
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable,电荷泵设置
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable,bit2，开启/关闭
	
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5),全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) ,设置显示方式;bit0:1,反相显示;0,正常显示
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel,开启显示
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	
	OLED_Clear();
	
	OLED_Set_Pos(0,0); 	
}  


