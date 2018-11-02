// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBZMSGDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBZMSGDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LIBZMSGDLL_EXPORTS
#define LIBZMSGDLL_API __declspec(dllexport)
#else
#define LIBZMSGDLL_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "ZD.h"
#include "ZE.h"
#include "ZF2.h"
#include "ZM.h"
#include "ZG.h"
#include "CML.h"

using namespace std;

#define IFLI_RNAVIP              5051    //������ȷ������ļ�
#define IFLI_RPACPA              5054;   //·����Ԫ�滮���Ʋ����ļ�
#define IFLI_YSDHX               5000;   //�������ԭʼͼ���ļ�
#define IFLI_YSQJX               5001;    //ȫ�����ԭʼͼ���ļ�
#define IFLI_YSBZX               5002;    //�������ԭʼͼ���ļ�
#define IFLI_ZS                      5016;    //DOM�ļ�
#define IFLI_FYQJX               5026;    //Ѳ����ȫ�����ԭʼ��ɫ��ԭͼ���ļ�
#define IFLI_GC_100CM            5027;    //100��������DEM�����ļ�
#define IFLI_GC_10CM             5028;    //10��������DEM�����ļ�
#define IFLI_GC_1CM              5029;    //1��������DEM�����ļ�
#define IFLI_GC_HIGH             5030;    //1�������¸߷ֱ���DEM�����ļ�
#define IMSI_STATIONCREATE       3503;    //վ���¼�ļ�

char            filename[256];
int             qid;
//ZD��ѯ�ļ�
typedef void (CALLBACK * fnCallBackDatabase)(char* filename,int nName,char* filenames,int nNames,int uiFileTypes,int uiTaskCode,int uiObjCode);
typedef void (CALLBACK * fnCallBackStationID)(int uiStationID);
//zgȫ�ֶη���
typedef void (CALLBACK * zgCallBackVec)(Float64 value1,Float64 value2,Float64 value3);

#ifdef __cplusplus
extern "C" {
#endif 
	//ZD���
	//��ѯվ���¼����
	LIBZMSGDLL_API int zdFileCount( int filetype,char* querysql,HWND pwnd);
	LIBZMSGDLL_API int zdFile( int filetype,char* querysql,HWND pwnd);
	LIBZMSGDLL_API void Register_CallBack_Database(fnCallBackDatabase func);
	//ZD��ѯվ����Ϣ
	LIBZMSGDLL_API int zdStationID();
	LIBZMSGDLL_API void Register_CallBack_StationID(fnCallBackStationID func);
	//zf��أ���ȡ�ļ�
	LIBZMSGDLL_API int zfget( char* filename,char* filenames,int uiFileTypes,int uiTaskCode,int uiObjCode);
	//zf��أ����߼����ļ�
	LIBZMSGDLL_API int zfRecvw( char* strDirecPath,HWND pwnd);
	LIBZMSGDLL_API int zfclose();
	//zg��أ�ȫ�ֶη���
	LIBZMSGDLL_API int zg_vec( int uiTaskCode,int uiObjCode,int vecindex);
	LIBZMSGDLL_API void Register_CallBack_Vec(zgCallBackVec func);

#ifdef __cplusplus
}
#endif 
