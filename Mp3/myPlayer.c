#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>  //getch()
#include <Windows.h>	// system()
#include <mmsystem.h>	// mci库头文件

#include"PlayInterface.h"
#include"Interface.h"
 
//#define STATUS_STOP 0     不参与编译
//#define STATUS_PLAY 1
//#define STATUS_PAUSE 2

enum STATUS{               //枚举类型 经过编译 第一个默认为0，其后依次增加
	STATUS_STOP = 0,
	STATUS_PLAY,
	STATUS_PAUSE,
};

//修饰函数的关键字：static 和 extern 
//static限定作用域在本文件内 

static void PlayControlMenu(char adress[]);
static void VoiceControlMenu();
void VolumnUp(const char *name);
void VolumnDown(const char *name);

void MainControlMenu(){
	int input = -1;//-1在内存中存的是补码 
	//printf("请输入歌曲名称\n");
	//gets(adress);
	//puts(adress);
	//system("cls");

	system("pause");
	while(input){
		system("cls");
		printf("1.播放控制\n");
		printf("2.音量调节\n");
		printf("0.退出\n");
		//scanf("%d",&input);    标准输入输出库函数存在缓冲区  所以输入输出后要加回车
		input = getch(); //返回值为字符'1',转换为ASCAII码
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
				printf("无效操作");
				break;
			}
		}
    }
}

void PlayControlMenu()
{
	int sinput = -1;
	static enum STATUS status = STATUS_STOP; //用status记录播放状态，0代表停止，1播放，2暂停
	while(sinput){
		system("cls");
		if(status == STATUS_PLAY)
		{printf("正在播放第%d首歌曲----%s\n",getIndex()+1,getName());}
		else if(status == STATUS_PAUSE)
		{printf("暂停\n");}
		else if(status == STATUS_STOP)
		{printf("停止\n");}
		printf("1.播放/暂停\n");
		printf("2.停止\n");
		printf("3.上一曲\n");
		printf("4.下一首\n");
		printf("0.退出\n"); 
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
				printf("无效操作");
				break;
			}
		}	
	}
}

void VoiceControlMenu(){
	int tinput = -1;
	while(tinput){
		system("cls");
		printf("当前为停止状态\n");
		printf("1.音量增大\n");
	    printf("2.音量减小\n");
		printf("0.退出\n");
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
				printf("无效操作");
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

	// 加路径
	sprintf(path, ".\\music\\%s", name);
	// GetShortPathName用来转换短名，要求被转换的歌名必须能在指定目录下找到文件，否则转换失败。
	// 第一个参数：源文件名，第二个参数：目的文件名，第三个参数：目的数组长度。
	GetShortPathName(path, path, MAX_PATH);
	sprintf(cmd, "status %s volume", path);
	mciSendString(cmd, res, MAX_PATH, NULL);

	// 音量转换为整形，并作加法操作
	volumn = atoi(res);
	volumn += 100;

	// 拼接设置音量命令
	sprintf(cmd, "setaudio %s volume to %d", path, volumn);

	// 发送设置音量命令
	mciSendString(cmd, "", 0, NULL);
}

void VolumnDown(const char *name)
{
	char path[MAX_PATH] = {0};
	char cmd[MAX_PATH] = {0};	
	char res[MAX_PATH] = {0};
	int volumn = 0;
	
	// 加路径
	sprintf(path, ".\\music\\%s", name);
	// GetShortPathName用来转换短名，要求被转换的歌名必须能在指定目录下找到文件，否则转换失败。
	// 第一个参数：源文件名，第二个参数：目的文件名，第三个参数：目的数组长度。
	GetShortPathName(path, path, MAX_PATH);
	sprintf(cmd, "status %s volume", path);
	mciSendString(cmd, res, MAX_PATH, NULL);
	// res是个字符数组，不能实现减法操作，所以用atoi()转换为整形
	volumn = atoi(res);
	volumn -= 100;
	// 将变更后的音量发送给MCI进行设定
	sprintf(cmd, "setaudio %s volume to %d", path, volumn);
	mciSendString(cmd, "", 0, NULL);
}