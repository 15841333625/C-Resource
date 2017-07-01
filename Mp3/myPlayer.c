#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>  //getch()
#include <Windows.h>	// system()
#include <mmsystem.h>	// mci��ͷ�ļ�

#include"PlayInterface.h"
#include"Interface.h"
 
//#define STATUS_STOP 0     ���������
//#define STATUS_PLAY 1
//#define STATUS_PAUSE 2

enum STATUS{               //ö������ �������� ��һ��Ĭ��Ϊ0�������������
	STATUS_STOP = 0,
	STATUS_PLAY,
	STATUS_PAUSE,
};

//���κ����Ĺؼ��֣�static �� extern 
//static�޶��������ڱ��ļ��� 

static void PlayControlMenu(char adress[]);
static void VoiceControlMenu();
void VolumnUp(const char *name);
void VolumnDown(const char *name);

void MainControlMenu(){
	int input = -1;//-1���ڴ��д���ǲ��� 
	//printf("�������������\n");
	//gets(adress);
	//puts(adress);
	//system("cls");

	system("pause");
	while(input){
		system("cls");
		printf("1.���ſ���\n");
		printf("2.��������\n");
		printf("0.�˳�\n");
		//scanf("%d",&input);    ��׼��������⺯�����ڻ�����  �������������Ҫ�ӻس�
		input = getch(); //����ֵΪ�ַ�'1',ת��ΪASCAII��
		input -= 48;
		switch(input){
			case 1:{
				PlayControlMenu(getName());
				break;
			}
			case 2:{
				VoiceControlMenu();
				break;
			}
			case 0:{
				break;
			}
			default:{
				printf("��Ч����");
				break;
			}
		}
    }
}

void PlayControlMenu()
{
	int sinput = -1;
	static enum STATUS status = STATUS_STOP; //��status��¼����״̬��0����ֹͣ��1���ţ�2��ͣ
	while(sinput){
		system("cls");
		if(status == STATUS_PLAY)
		{printf("���ڲ��ŵ�%d�׸���----%s\n",getIndex()+1,getName());}
		else if(status == STATUS_PAUSE)
		{printf("��ͣ\n");}
		else if(status == STATUS_STOP)
		{printf("ֹͣ\n");}
		printf("1.����/��ͣ\n");
		printf("2.ֹͣ\n");
		printf("3.��һ��\n");
		printf("4.��һ��\n");
		printf("0.�˳�\n"); 
		sinput = getch();
		sinput -= 48;
		switch(sinput){
		    case 1:{
		    	if(status != STATUS_PLAY)
		    	{
		    		play(getName());
					status = STATUS_PLAY;
				}else if(status == STATUS_PLAY){
					pause(getName());
					status = STATUS_PAUSE;
				}
				break;
			}
			case 2:{
				stop(getName());
			    status = STATUS_STOP;
				break;
			}
			case 3:{
				indexDown();
			    break;
			}
			case 4:{
				indexUp();
				break;
			}
            case 0:{
				break;
			}
			default:{
				printf("��Ч����");
				break;
			}
		}	
	}
}

void VoiceControlMenu(){
	int tinput = -1;
	while(tinput){
		system("cls");
		printf("��ǰΪֹͣ״̬\n");
		printf("1.��������\n");
	    printf("2.������С\n");
		printf("0.�˳�\n");
		tinput = getch();
		tinput -= 48;
		switch(tinput){
			case 1:{
				VolumnUp(getName());
				break;
			}
			case 2:{
				VolumnDown(getName());
				break;
			}
			case 0:{
				break;
			}
			default:{
				printf("��Ч����");
				break;
			}
		} 	
	}
}

void VolumnUp(const char *name)
{
	char path[MAX_PATH] = {0};
	char cmd[MAX_PATH] = {0};	
	char res[MAX_PATH] = {0};
	int volumn = 0;

	// ��·��
	sprintf(path, ".\\music\\%s", name);
	// GetShortPathName����ת��������Ҫ��ת���ĸ�����������ָ��Ŀ¼���ҵ��ļ�������ת��ʧ�ܡ�
	// ��һ��������Դ�ļ������ڶ���������Ŀ���ļ�����������������Ŀ�����鳤�ȡ�
	GetShortPathName(path, path, MAX_PATH);
	sprintf(cmd, "status %s volume", path);
	mciSendString(cmd, res, MAX_PATH, NULL);

	// ����ת��Ϊ���Σ������ӷ�����
	volumn = atoi(res);
	volumn += 100;

	// ƴ��������������
	sprintf(cmd, "setaudio %s volume to %d", path, volumn);

	// ����������������
	mciSendString(cmd, "", 0, NULL);
}

void VolumnDown(const char *name)
{
	char path[MAX_PATH] = {0};
	char cmd[MAX_PATH] = {0};	
	char res[MAX_PATH] = {0};
	int volumn = 0;
	
	// ��·��
	sprintf(path, ".\\music\\%s", name);
	// GetShortPathName����ת��������Ҫ��ת���ĸ�����������ָ��Ŀ¼���ҵ��ļ�������ת��ʧ�ܡ�
	// ��һ��������Դ�ļ������ڶ���������Ŀ���ļ�����������������Ŀ�����鳤�ȡ�
	GetShortPathName(path, path, MAX_PATH);
	sprintf(cmd, "status %s volume", path);
	mciSendString(cmd, res, MAX_PATH, NULL);
	// res�Ǹ��ַ����飬����ʵ�ּ���������������atoi()ת��Ϊ����
	volumn = atoi(res);
	volumn -= 100;
	// ���������������͸�MCI�����趨
	sprintf(cmd, "setaudio %s volume to %d", path, volumn);
	mciSendString(cmd, "", 0, NULL);
}