#define _CRT_SECURE_NO_WARNINGS//��ֹ��sprintf��fopen������
#define  _CRT_NON_CONFORMING_SWPRINTFS
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")//�������д���
#include <iostream>
#include <d:\Desktop\myhead.h>
using namespace std;
int main(int argc,char *argv[])
{
	setlocale(LC_ALL,"chs");
	if(argc==1)
	{
		return 0;
	}
	//����ȡ�ļ�·���洢����
	wchar_t *path=new wchar_t[255];
	wchar_t *pathname=new wchar_t[50];
	wchar_t *filename=new wchar_t[205];
	//��Դ�ļ�
	FILE *fp,*fp2,*fp3;
	fp=Fopen(argv[1],"ab+");
	//���崢��·�����ȱ���
	short *length=new short,*dellength=new short;
	unsigned long filesize,i=0;
	fread(length,2,1,fp);
	fread(dellength,2,1,fp);
	fread(&filesize,4,1,fp);
	fread(path,*length*2,1,fp);
	path[*length]=L'\0';
	getfname(path,filename,pathname);
	wchar_t *output=new wchar_t[256];
	swprintf(output,L"./%ws",filename);
	fseek(fp,*dellength,SEEK_SET);
	fp2=_wfopen(output,L"wb+");
	while(i<filesize)
	{
		fputc(fgetc(fp),fp2);
		i++;
	}
	fp3=fopen("./result.log","at+");
	fputws(filename,fp3);
	fputwc(L'\t',fp3);
	fputws(pathname,fp3);
	fputwc(L'\n',fp3);

	fclose(fp2);
	fclose(fp);
	fclose(fp3);
	
	delete []path;
	delete []pathname;
	delete []filename;
	delete []output;
	delete length;
	delete dellength;
	
	return 0;
}