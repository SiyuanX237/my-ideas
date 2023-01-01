#include <stdio.h>
#include <direct.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include "D:\Desktop\夏思远的.h"
short height,width;//图片宽高数据储存
char temp;//判断适配背景是否为黑
short background;
void togray(FILE *fp2,int *gray);//RGB转仿灰度
int main()
{
	FILE *fp,*fp2;//一大堆定义
	short temp1,temp2,temp3,temp4;//宽高读取临时储存
	char *height_c=NULL,*width_c=NULL;//宽高读为字符，临时储存
	height_c=new char[6];//给宽高字符组储存申请内存
	width_c=new char[6];
	char *path_start=NULL,*path_full=NULL;//文件路径定义
	path_start=new char[50];//给文件路径储存申请内存
	path_full=new char[60];
	logo//人机交互，在"夏思远.h"里
	system("title ASCII picture");//cmd窗口标题
	printf("请把main.bmp放在与本程序同目录下，按回车继续...");
	getchar();
	memset(path_start,'\0',50);//路径初始化并打开文件
	memset(path_full,'\0',60);
	getcwd(path_start,50);
	strcat(path_full,path_start);
	strcat(path_full,"\\main.bmp");
	if((fp=Fopen(path_full,"rb"))==NULL)//打开失败处理
	{
		return 0;
	}
	printf("图片路径:%s\n",path_full);
	memset(path_full,'\0',60);
	strcat(path_full,path_start);
	strcat(path_full,"\\out.txt");
	fp2=fopen(path_full,"w");//新建\打开输出txt文件
	delete [] path_start;//路径没用了，释放内存
	delete [] path_full;
	path_start=NULL;//防治野指针
	path_full=NULL;
	fseek(fp,18L,SEEK_CUR);//获取图片尺寸（宽×高）
	temp1=fgetc(fp);
	temp2=fgetc(fp);
	fseek(fp,2L,SEEK_CUR);
	temp3=fgetc(fp);
	temp4=fgetc(fp);
	sprintf(width_c,"%02x%02x\n",temp2,temp1);//字符拼接，以获取图片尺寸
	sprintf(height_c,"%02x%02x\n",temp4,temp3);
	width=(short)strtol(width_c,NULL,16);//字符型十六进制转整型十进制
	height=(short)strtol(height_c,NULL,16);
	delete [] height_c;//宽高临时储存变量没用了，释放内存
	delete [] width_c;
	height_c=NULL;//防治野指针
	width_c=NULL;
	printf("图片的尺寸:%d*%d\n",width,height);
failure:
	printf("适配黑色背景(Y/N):");
	temp=getchar();
	getchar();
	if(temp=='Y'||temp=='y')
	{
		background=0;
	}
	else if(temp=='N'||temp=='n')
	{
		background=31;
	}
	else
	{
		printf("\n请输入正确的值...");
		goto failure;
	}
	int *hex,*gray;//定义hex(图片一行的RGB码),gray(RBG转成仿灰度)
	hex=new int[width*3];//给数据数组大家伙储存申请内存
	gray=new int[width];
	fseek(fp,-3*width-2,SEEK_END);//寻到图片结尾倒数第一行（因为bmp是倒序的呜呜）
	short i=0,j,k;
	while(i<height)//循环读入并转换（控制行数）
	{
		j=0;
		while(j<3*width)//控制列数
		{
			hex[j]=fgetc(fp);
			j++;
		}
		j=0;
		k=0;
		while(k<width)//转仿灰度
		{
			gray[k]=(hex[j]*11+hex[j+1]*59+hex[j+2]*30)/100;
			j+=3;k++;
		}
		togray(fp2,gray);//转换成字符并写入文件
		fprintf(fp2," \n");//换行进行新一行字符写入
		fseek(fp,-6*width,SEEK_CUR);//再往前偏移两行，开始下一轮的读写
		i++;
	}
	delete [] hex;//大家伙没用了，释放内存（都结束了，好像没有必要了吧）
	delete [] gray;
	hex=NULL;//野指针不要过来啊
	gray=NULL;
	fclose(fp2);//关闭两文件
	fclose(fp);
	printf("完成");
	Sleep(2000);//延时
	return 0;//完美收尾
}

void togray(FILE *fp2,int *gray)
{
	short i=0;
	while(i<=width)//实现写入字符（对应不同的灰度）
	{
		switch(abs(background-((gray[i]>8)+(gray[i]>16)+(gray[i]>24)+(gray[i]>32)+(gray[i]>40)+(gray[i]>48)+(gray[i]>56)+(gray[i]>64)+(gray[i]>72)+(gray[i]>80)+(gray[i]>88)+(gray[i]>96)+(gray[i]>104)+(gray[i]>112)+(gray[i]>120)+(gray[i]>128)+(gray[i]>136)+(gray[i]>144)+(gray[i]>152)+(gray[i]>160)+(gray[i]>168)+(gray[i]>176)+(gray[i]>184)+(gray[i]>192)+(gray[i]>200)+(gray[i]>208)+(gray[i]>216)+(gray[i]>224)+(gray[i]>232)+(gray[i]>240)+(gray[i]>248)+(gray[i]>256))))
		{
			case 0:
				fprintf(fp2,"  ");
				break;
			case 1:
				fprintf(fp2,"..");
				break;
			case 2:
				fprintf(fp2,",,");
				break;
			case 3:
				fprintf(fp2,"**");
				break;
			case 4:
				fprintf(fp2,";;");
				break;
			case 5:
				fprintf(fp2,"!!");
				break;
			case 6:
				fprintf(fp2,"??");
				break;
			case 7:
				fprintf(fp2,"//");
				break;
			case 8:
				fprintf(fp2,"ii");
				break;
			case 9:
				fprintf(fp2,"ll");
				break;
			case 10:
				fprintf(fp2,"uu");
				break;
			case 11:
				fprintf(fp2,"cc");
				break;
			case 12:
				fprintf(fp2,"ff");
				break;
			case 13:
				fprintf(fp2,"vv");
				break;
			case 14:
				fprintf(fp2,"hh");
				break;
			case 15:
				fprintf(fp2,"zz");
				break;
			case 16:
				fprintf(fp2,"++");
				break;
			case 17:
				fprintf(fp2,"xx");
				break;
			case 18:
				fprintf(fp2,"Ll");
				break;
			case 19:
				fprintf(fp2,"&&");
				break;
			case 20:
				fprintf(fp2,"$$");
				break;
			case 21:
				fprintf(fp2,"OO");
				break;
			case 22:
				fprintf(fp2,"QQ");
				break;
			case 23:
				fprintf(fp2,"BB");
				break;
			case 24:
				fprintf(fp2,"GG");
				break;
			case 25:
				fprintf(fp2,"RR");
				break;
			case 26:
				fprintf(fp2,"##");
				break;
			case 27:
				fprintf(fp2,"MM");
				break;
			case 28:
				fprintf(fp2,"%%%%");
				break;
			case 29:
				fprintf(fp2,"WW");
				break;
			case 30:
				fprintf(fp2,"囍");
				break;
			case 31:
				fprintf(fp2,"▓");
		}
		i++;//下一个灰度
	}
}
