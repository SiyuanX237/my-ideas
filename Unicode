#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <wchar.h>
#include <time.h>
#include <Windows.h>
#include <locale.h>

int main()
{
	void wrong();									//声明错误函数
	int choose();									//声明选择函数
	wchar_t word[100];								//声明输入文字储存变量
	wchar_t u=0x300;								//声明"乱码"unicode码起始位置
	int i,j;										//声明循环变量
	wchar_t temp;									//声明临时字符储存变量
	FILE *fp;										//声明文件指针
	wchar_t ra,rb;									//声明插入文字的位置(ra)和数量(rb)
	int num;										//声明数目变量
	srand((int)(time(0)));								//设置随机种子
	ra=rand()%111;									//设置乱码位置
	printf("本程序可以在输入的文字中随机插入组合变音符号，以此来达到乱码效果，结果会输出到同目录下的unicode.txt中\n");
	num=choose();									//获取字符个数
	getchar();										//获取多余回车符
	rb=rand()%num;									//设置乱码个数
	if((fp=fopen(".\\unicode.txt","ab"))==NULL)						//在根目录打开文件
	{
		printf("无法打开文件，请检查当前目录的权限或存储空间\n");
		return 0;
	}
	setlocale(LC_ALL,"");									//设置unicode语言区间
	i=0;										//清零计数
	printf("请输入你要乱码的内容（按\"#\"）以结束输入\n");//开始输入
	while(1)
	{
		if((temp=getwchar())!=L'#')							//为word变量赋值
		{
			word[i]=temp;
			i++;
		}
		else
		{
			word[i]=L'\0';							//为word添加结尾，使其变成字符串
			break;
		}
	}
	for(i=0;i < (int)wcslen(word);i++)							//循环插入"乱码"，控制位置
	{
		for(j=0;j<rb;j++)								//控制个数
		{
			fwprintf(fp,L"%lc",u+ra);
			ra=rand()%111;
		}
		fwprintf(fp,L"%lc",word[i]);							//插入源字符
		rb=rand()%num;								//控制个数
	}
	fclose(fp);										//关闭文件
	system(".\\unicode.txt");								//打开文档
	return 0;
}

int choose()
{
	int i;
	printf("请输入你要的乱码数目(0~99)\n");
	scanf("%2d",&i);
	if(i<0 || i>99)									//判断输入是否有误
	{
		wrong();
	}
	return i;
}

void wrong()
{
	printf("ERROR!输入有误！请重新输入！！！\n");						//输出错误信息
	main();
}
