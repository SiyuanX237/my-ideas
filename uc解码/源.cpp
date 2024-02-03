#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <d:\Desktop\夏思远的.h>
#include <sys/stat.h>
int main(int argc,char* argv[])
{
	FILE *fp,*fp2;//分别打开源文件(fp)，目标文件(fp2)
	long filesize;//存放文件大小
	if(argv[1]==NULL)//使用时是用参数实现的
	{
		printf("%s","操作参数：[uc文件路径|about]\n按任意键退出\n");
		getchar();
		return 0;
	}
	else if(!strcmp(argv[1],"about"))
	{
		printf("Made by 个人隐思\n");
		printf("本程序实现对网易云音乐缓存uc文件进行反向解密为mp3格式\n仅用于学习目的，请支持正版\n按任意键退出\n");//客道话
		getchar();
		return 0;
	}
	fp=Fopen(argv[1],"rb");//从参数给与的路径打开文件
	if(fp==NULL)
	{
		printf("用户已取消操作,程序将退出\n");
		Sleep(1000);
	}
	fp2=Fopen("./result.mp3","wb");//打开目标写入文件
	if(fp2==NULL)
	{
		printf("用户已取消操作,程序将退出\n");
		Sleep(1000);
	}
	size_t getFileSizel(const char argv[1]);//获取文件大小
	struct stat statbuf;
	stat(argv[1],&statbuf);
	filesize = statbuf.st_size;
	printf("已载入文件\n文件路径:%s\n文件大小:%.2fMB\n",argv[1],filesize/1048576.0);//文件信息
	/*fseek(fp,0, SEEK_END);
	filesize=ftell(fp);
	fseek(fp,0, SEEK_SET);*/
	unsigned short* buffer = new unsigned short[filesize];//动态申请一段内存来储存uc文件
	long i=0;
	while (i<filesize)//循环读取,继续无符号二进制异或计算,写入文件
	{
		fputc(fgetc(fp)^0xA3,fp2);
		i++;
	}
	delete buffer;//释放申请的内存，防止内存泄漏
	fclose(fp);
	fclose(fp2);//关闭两文件
	printf("操作已完成\n");
	Sleep(1000);
	return 0;
}