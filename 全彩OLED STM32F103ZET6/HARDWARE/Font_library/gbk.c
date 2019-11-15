#include "gbk.h"
#include "sys.h"
#include "W25Q64.h"
#include "oled_display.h"

//���������ֿ������Ϣ����ַ����С��
_font_info ftinfo;
//��ʼ������
//����ֵ:0,�ֿ����.
//		 ����,�ֿⶪʧ
u8 font_init(void)
{
	u8 t=0;
	while(t<5)//������ȡ5��,���Ǵ���,˵��ȷʵ��������,�ø����ֿ���
	{
		t++;
		W25QXX_Read((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));//����ftinfo�ṹ������ ��ȡ֮���ֿ�ṹ������˳�ֵ
		if(ftinfo.fontok==0XAA)
			break;
		delay_ms(20);
	}
	/*ftinfo.ugbkaddr=FONTINFOADDR+sizeof(ftinfo);		//��Ϣͷ֮�󣬽���UNIGBKת�����
	ftinfo.ugbksize=UGBKSIZE;												//UNIGBK��С
	ftinfo.f12addr=ftinfo.ugbkaddr+ftinfo.ugbksize;	//UNIGBK֮�󣬽���GBK12�ֿ�
	ftinfo.gbk12size=GBK12SIZE;											//GBK12�ֿ��С
	ftinfo.f16addr=ftinfo.f12addr+ftinfo.gbk12size;	//GBK12֮�󣬽���GBK16�ֿ�
	ftinfo.gbk16size=GBK16SIZE;											//GBK16�ֿ��С
	ftinfo.f24addr=ftinfo.f16addr+ftinfo.gbk16size;	//GBK16֮�󣬽���GBK24�ֿ�
	ftinfo.gkb24size=GBK24SIZE;											//GBK24�ֿ��С*/
	if(ftinfo.fontok!=0XAA)
		return 1;
	return 0;		    
}

//code �ַ�ָ�뿪ʼ
//���ֿ��в��ҳ���ģ
//code �ַ����Ŀ�ʼ��ַ,GBK��
//mat  ���ݴ�ŵ�ַ (size/8+((size%8)?1:0))*(size) bytes��С	
//size:�����С
void Get_HzMat(unsigned char *code,unsigned char *mat,u8 size)
{
	unsigned char qh,ql;
	unsigned char i;					  
	unsigned long foffset; 
	u8 csize=(size/8+((size%8)?1:0))*(size);//�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
	qh=*code;
	ql=*(++code);
	if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//�� ���ú���
	{   		    
	    for(i=0;i<csize;i++)*mat++=0x00;//�������
	    return; //��������
	}          
	if(ql<0x7f)ql-=0x40;//ע��!
	else ql-=0x41;
	qh-=0x81;   
	foffset=((unsigned long)190*qh+ql)*csize;	//�õ��ֿ��е��ֽ�ƫ����  		  
	switch(size)
	{
		case 12:
			W25QXX_Read(mat,foffset+ftinfo.f12addr,csize);
			break;
		case 16:
			W25QXX_Read(mat,foffset+ftinfo.f16addr,csize);
			break;
		case 24:
			W25QXX_Read(mat,foffset+ftinfo.f24addr,csize);
			break;
	}     												    
}




