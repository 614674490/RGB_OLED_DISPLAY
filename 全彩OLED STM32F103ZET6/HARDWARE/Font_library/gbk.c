#include "gbk.h"
#include "sys.h"
#include "W25Q64.h"
#include "oled_display.h"

//用来保存字库基本信息，地址，大小等
_font_info ftinfo;
//初始化字体
//返回值:0,字库完好.
//		 其他,字库丢失
u8 font_init(void)
{
	u8 t=0;
	while(t<5)//连续读取5次,都是错误,说明确实是有问题,得更新字库了
	{
		t++;
		W25QXX_Read((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));//读出ftinfo结构体数据 读取之后，字库结构体便有了初值
		if(ftinfo.fontok==0XAA)
			break;
		delay_ms(20);
	}
	/*ftinfo.ugbkaddr=FONTINFOADDR+sizeof(ftinfo);		//信息头之后，紧跟UNIGBK转换码表
	ftinfo.ugbksize=UGBKSIZE;												//UNIGBK大小
	ftinfo.f12addr=ftinfo.ugbkaddr+ftinfo.ugbksize;	//UNIGBK之后，紧跟GBK12字库
	ftinfo.gbk12size=GBK12SIZE;											//GBK12字库大小
	ftinfo.f16addr=ftinfo.f12addr+ftinfo.gbk12size;	//GBK12之后，紧跟GBK16字库
	ftinfo.gbk16size=GBK16SIZE;											//GBK16字库大小
	ftinfo.f24addr=ftinfo.f16addr+ftinfo.gbk16size;	//GBK16之后，紧跟GBK24字库
	ftinfo.gkb24size=GBK24SIZE;											//GBK24字库大小*/
	if(ftinfo.fontok!=0XAA)
		return 1;
	return 0;		    
}

//code 字符指针开始
//从字库中查找出字模
//code 字符串的开始地址,GBK码
//mat  数据存放地址 (size/8+((size%8)?1:0))*(size) bytes大小	
//size:字体大小
void Get_HzMat(unsigned char *code,unsigned char *mat,u8 size)
{
	unsigned char qh,ql;
	unsigned char i;					  
	unsigned long foffset; 
	u8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数	 
	qh=*code;
	ql=*(++code);
	if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//非 常用汉字
	{   		    
	    for(i=0;i<csize;i++)*mat++=0x00;//填充满格
	    return; //结束访问
	}          
	if(ql<0x7f)ql-=0x40;//注意!
	else ql-=0x41;
	qh-=0x81;   
	foffset=((unsigned long)190*qh+ql)*csize;	//得到字库中的字节偏移量  		  
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




