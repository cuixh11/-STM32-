#include "HK711.h"

unsigned long read_ad()//称重程序
{
	unsigned long count;//定义变量
	unsigned char i;
	
	scl(0);//将总线拉低B7,表明A/D转换器还未准备好输出数据
	count=0;
	
	while(dt);//等待数据端口为1，即有数据输入
	for(i=0;i<24;i++)//然后读取24位
	{
		scl(1);
		count=count<<1;//下降沿来时变量count左移一位，右侧补零
		scl(0);
		
		if(dt){count++;}//如果是高电平，就往数据位里加1，低不管
	}
	
		scl(1);
		count=count^0x800000;//转换原码，将数据异或0x1000 0000 0000 0000 0000 0000，因为HX711驱动中，数据是补码形式出现。第25个脉冲下降沿来时，转换数据(ACK?)
		scl(0);
	
		return count;
}
