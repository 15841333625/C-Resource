#include <stdio.h>
#include <string.h>
#include <conio.h>	// ����getch()������ͷ�ļ�
#include <stdlib.h>
#include <Windows.h>	// system()
#include <mmsystem.h>	// mci��ͷ�ļ�


#pragma comment(lib, "winmm.lib")	// ָ��MCI�⣬mciSendString�����Ķ�����winmm.lib��

static char adress[50][50] = {0};
static int index = 0;   //��index��¼���ŵĵڼ��׸���
static int maxnum = 0;//������

// �����ļ��У�����windows API
void find(char * lpPath) 
{ 
    char szFind[MAX_PATH],szFile[MAX_PATH]; 
    WIN32_FIND_DATA FindFileData; 
	HANDLE hFind;
    strcpy(szFind,lpPath); 
    strcat(szFind,"\\*.mp3");
    hFind = FindFirstFile(szFind,&FindFileData); 
    if(INVALID_HANDLE_VALUE == hFind) 
        return; 
    while(TRUE) 
    { 
        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
        { 
            if(FindFileData.cFileName[0]!='.') 
            { 
                strcpy(szFile,lpPath); 
                strcat(szFile,"\\"); 
                strcat(szFile,FindFileData.cFileName); 
                find(szFile); 
            } 
        } 
        else 
        { 
            printf("%s\n",FindFileData.cFileName);
			// FindFileData.cFileName���ļ���
			//��ά�����е�ַ &adress[1][0]   adress[1]  (adress + 1)
			strcpy(adress[maxnum],FindFileData.cFileName);
			maxnum++;
        } 
        if(!FindNextFile(hFind,&FindFileData)) 
            break; 
    } 
} 
char *getName(){
	return adress[index];
}

int getIndex(){
	return index;
}

void indexDown(){
	if(index>0)
		{
			stop(adress[index]);
			index--;
			play(adress[index]);
		}else{
			stop(adress[index]);
			index = 3;
			play(adress[index]);
		}
}

void indexUp(){
	if(index<(maxnum-1))
		{
			stop(adress[index]);
			index++;
			play(adress[index]);
		}else{
			stop(adress[index]);
			index = 0;	
			play(adress[index]);
		}
}

