#include "HK711.h"

unsigned long read_ad()//���س���
{
	unsigned long count;//�������
	unsigned char i;
	
	scl(0);//����������B7,����A/Dת������δ׼�����������
	count=0;
	
	while(dt);//�ȴ����ݶ˿�Ϊ1��������������
	for(i=0;i<24;i++)//Ȼ���ȡ24λ
	{
		scl(1);
		count=count<<1;//�½�����ʱ����count����һλ���Ҳಹ��
		scl(0);
		
		if(dt){count++;}//����Ǹߵ�ƽ����������λ���1���Ͳ���
	}
	
		scl(1);
		count=count^0x800000;//ת��ԭ�룬���������0x1000 0000 0000 0000 0000 0000����ΪHX711�����У������ǲ�����ʽ���֡���25�������½�����ʱ��ת������(ACK?)
		scl(0);
	
		return count;
}
