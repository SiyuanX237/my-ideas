#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <d:\Desktop\��˼Զ��.h>
#include <sys/stat.h>
int main(int argc,char* argv[])
{
	FILE *fp,*fp2;//�ֱ��Դ�ļ�(fp)��Ŀ���ļ�(fp2)
	long filesize;//����ļ���С
	if(argv[1]==NULL)//ʹ��ʱ���ò���ʵ�ֵ�
	{
		printf("%s","����������[uc�ļ�·��|about]\n��������˳�\n");
		getchar();
		return 0;
	}
	else if(!strcmp(argv[1],"about"))
	{
		printf("Made by ������˼\n");
		printf("������ʵ�ֶ����������ֻ���uc�ļ����з������Ϊmp3��ʽ\n������ѧϰĿ�ģ���֧������\n��������˳�\n");//�͵���
		getchar();
		return 0;
	}
	fp=Fopen(argv[1],"rb");//�Ӳ��������·�����ļ�
	if(fp==NULL)
	{
		printf("�û���ȡ������,�����˳�\n");
		Sleep(1000);
	}
	fp2=Fopen("./result.mp3","wb");//��Ŀ��д���ļ�
	if(fp2==NULL)
	{
		printf("�û���ȡ������,�����˳�\n");
		Sleep(1000);
	}
	size_t getFileSizel(const char argv[1]);//��ȡ�ļ���С
	struct stat statbuf;
	stat(argv[1],&statbuf);
	filesize = statbuf.st_size;
	printf("�������ļ�\n�ļ�·��:%s\n�ļ���С:%.2fMB\n",argv[1],filesize/1048576.0);//�ļ���Ϣ
	/*fseek(fp,0, SEEK_END);
	filesize=ftell(fp);
	fseek(fp,0, SEEK_SET);*/
	unsigned short* buffer = new unsigned short[filesize];//��̬����һ���ڴ�������uc�ļ�
	long i=0;
	while (i<filesize)//ѭ����ȡ,�����޷��Ŷ�����������,д���ļ�
	{
		fputc(fgetc(fp)^0xA3,fp2);
		i++;
	}
	delete buffer;//�ͷ�������ڴ棬��ֹ�ڴ�й©
	fclose(fp);
	fclose(fp2);//�ر����ļ�
	printf("���������\n");
	Sleep(1000);
	return 0;
}