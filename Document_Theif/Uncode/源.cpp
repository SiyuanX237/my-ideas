#define _CRT_SECURE_NO_WARNINGS//防止因sprintf和fopen而狗叫
#define  _CRT_NON_CONFORMING_SWPRINTFS
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")//隐藏运行窗口
#include <iostream>
#include <d:\Desktop\myhead.h>
using namespace std;
int main(int argc,char *argv[])
{
	short index=1;
	setlocale(LC_ALL,"chs");
	if(argc==1)
	{
		return 0;
	}
	start:
	//定义取文件路径存储变量
	wchar_t *path=new wchar_t[255];
	wchar_t *pathname=new wchar_t[50];
	wchar_t *filename=new wchar_t[205];
	//打开源文件
	FILE *fp,*fp2,*fp3;
	fp=Fopen(argv[index],"ab+");
	//定义储存路径长度变量
	short *length=new short,*dellength=new short;
	unsigned long filesize,i=0;
	fread(length,2,1,fp);
	fread(dellength,2,1,fp);
	fread(&filesize,4,1,fp);
	fread(path,*length*2,1,fp);
	path[*length]=L'\0';
	getfname(path,filename,pathname);
	
	fp3=fopen("./output/result.log","a+");
	fputws(filename,fp3);
	fputws(L"\t<",fp3);
	fputws(pathname,fp3);
	fputws(L">\n",fp3);

	wchar_t *output=new wchar_t[256];
	swprintf(output,L"./output/%ws",filename);
	fseek(fp,*dellength,SEEK_SET);
	fp2=_wfopen(output,L"wb+");
	while(i<filesize)
	{
		fputc(fgetc(fp),fp2);
		i++;
	}

	fclose(fp2);
	fclose(fp);
	fclose(fp3);
	
	delete []path;
	delete []pathname;
	delete []filename;
	delete []output;
	delete length;
	delete dellength;
	index++;
	if(index<argc)
	{
		goto start;
	}
	return 0;
}