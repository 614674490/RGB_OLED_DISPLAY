#ifndef __GBK_H_
#define __GBK_H_
#include "sys.h"

//�ֿ�����ռ�õ�����������С(3���ֿ�+unigbk��+�ֿ���Ϣ=3238700�ֽ�,Լռ791��W25QXX����)
#define FONTSECSIZE	 	791
//�ֿ�����ʼ��ַ 1Byte(�ֽ�)=8Bit(λ)1KB=1024Byte 1MB=1024KB 1GB=1024MB=1024*1024KB=1024*1024*1024Byte
#define FONTINFOADDR 	1024*1024*4 //��4M��ַ�Ժ�ʼ����ֿ�
																	//ǰ��4M��fatfsռ����
																	//4M�Ժ����3���ֿ�+UNIGBK.BIN,�ܴ�С3.09M,���ֿ�ռ����,���ܶ�!
																	//7.10M�Ժ�,�û���������ʹ��.����������100K�ֽڱȽϺ�.					
																	

//�ֿ���Ϣ�ṹ�嶨��
//���������ֿ������Ϣ����ַ����С��
__packed typedef struct 
{
	u8 fontok;				//�ֿ���ڱ�־��0XAA���ֿ��������������ֿⲻ����
	u32 ugbkaddr; 			//unigbk�ĵ�ַ
	u32 ugbksize;			//unigbk�Ĵ�С	 
	u32 f12addr;			//gbk12��ַ	
	u32 gbk12size;			//gbk12�Ĵ�С	 
	u32 f16addr;			//gbk16��ַ
	u32 gbk16size;			//gbk16�Ĵ�С		 
	u32 f24addr;			//gbk24��ַ
	u32 gkb24size;			//gbk24�Ĵ�С 
}_font_info; 
extern _font_info ftinfo;	//�ֿ���Ϣ�ṹ��

void Get_HzMat(unsigned char *code,unsigned char *mat,u8 size);
u8 font_init(void);
#endif


