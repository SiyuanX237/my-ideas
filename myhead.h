/****************
 *  �����û���  *
 *made by ��˼Զ*
 ****************/

//��
#define True 1

//��
#define False 0

//logo
#define LOGO printf("Made by ��˼Զ\n");

//���ļ�
FILE *Fopen(char *path,char *open_type)
{
	char charater;
	FILE *fp;
retry:
	if((fp=fopen(path,open_type))==NULL)
	{
		printf("�޷����ļ������鵱ǰĿ¼�Ĵ洢�ռ��Ȩ��\n��ϸ��\"%s\"\n����������ԣ����߰�C��ȡ���˳�\n",path);
		charater=getchar();
		if(charater!='\n')
		{
			getchar();
		}
		if((charater!='c')&&(charater!='C'))
		{
			goto retry;
		}
		else
		{
			return NULL;
		}
	}
	return fp;
}

//������
/*int progress(int length,float step,char* text)
{
	int time=0;
	printf("00%%[>");
	for(int i=0;i<length;i++)
	{
		printf(" ");
	}
	printf("]%s",text);
	for(int i=0;i<length/step;i++,time++)
	{
		printf("\r%2d%%[",(int)(100*(time*step/length+0.2)));
		for(int j=0;j<step*(time+1);j++)
		{
			printf("=");
		}
		printf(">");
		Sleep(1000);
		if(kbhit()!=0)
		{
			return False;
		}
	}
	return True;
}


int progress(int past,float finish,int length,int rate,char* text)
{
	int times=0;
	printf("00%%[>");
	for(int i=0;i<length;i++)
	{
		printf(" ");
	}
	printf("]%s",text);
	for(int i=0;i<length*past/finish;i++,times++)
	{
		printf("\r%2d%%[",(int)(100*times*length*past/finish));
		for(int j=0;j<past*length*(times+1)/finish;j++)
		{
			printf("=");
		}
		printf(">");
		Sleep(1000);
		if(kbhit()!=0)
		{
			return False;
		}
	}
	return True;
}
*/

//������
/*
void progress(int past,float finished,int length,char *text)
{
	int times=0;
	past++;
	printf("\r 0%%[");
	for(int i=0;i<length;i++)
	{
		printf("=");
	}
	printf("]%s",text);
	printf("\r%.2d%%[",(int)(100*(past/finished)));
	for(int i=0;i<(past/finished*length*(times+1));i++)
	{
		printf(">");
	}
}
*/

/*
void progress(int past,float finished,int length,char *text)
{
	int times=0;
	past++;
	printf("\r%.2d%%[",(int)(100*(past/finished)));
	for(int i=0;i<(past/finished*length*(times+1));i++)
	{
		printf(">");
	}
	if(past==1)
	{
		for(int i=0;i<(length-(past/finished*length*(times+1)));i++)
		{
			printf("=");
		}
		printf("]");
	}
	if(past==finished)
	{
		printf("%s",text);
	}
}
*/

void progress(int past,int finished,char *text)
{
	if(past==0)
	{
		printf("����: 0%%     25%%     50%%     75%%     100%%\n    �����������Щ��������Щ��������Щ���������   \n");
	}
	
	if(past==finished)
	{
		printf("%s\n",text);
	}
}
