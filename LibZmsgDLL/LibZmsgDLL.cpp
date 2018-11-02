// LibZmsgDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "LibZmsgDLL.h"


#pragma region zd,��ѯ�ļ�����ѯվ��

fnCallBackDatabase m_func;
LIBZMSGDLL_API void Register_CallBack_Database(fnCallBackDatabase func)
{
	m_func = func;
}

fnCallBackStationID m_funStID;
LIBZMSGDLL_API void Register_CallBack_StationID(fnCallBackStationID func)
{
	m_funStID=func;
}

//zdStationID
LIBZMSGDLL_API int zdStationID()
{
	DbHandler   Handler;
	Sint32 siRsltNum;
	/** վ���ѯ */  
	char  szSelectStr[]="uiStationID";// "uiStationID, stCreateTime";
	char  szWhereStr[]= "1 = 1 order by uiStationID desc ";


	//������ѯ���
	Handler=dbNew();
	if (Handler==NULL)
	{
		return 0;
	}

	siRsltNum=dbQueryData(Handler,3503,3,5115,szSelectStr,szWhereStr);
	if (siRsltNum>0)
	{
		// ��ȡ��ѯ���
		while(!dbEof(Handler))
		{
			Uint32 uiStationID = 0;
			Sint32 siRetRslt = dbGetUInt(Handler,  "uiStationID" , &uiStationID);
			m_funStID(uiStationID);
			dbNext(Handler);
		}
	}
}

//��ѯվ���¼����
LIBZMSGDLL_API int zdFileCount( int filetype,char* querysql,HWND pwnd)
{
	// ������ѯ���
	DbHandler Handler = dbNew();
	if(Handler == NULL)
	{
		return 0;
	}
	// ��ѯ�ļ��б�
	Sint32 siRet = dbQueryFile(Handler, filetype, 3, 5115, querysql);
	if(siRet < 0)
	{
		ze_perror(siRet, "dbQueryFile");
		return -1;
	}

	// ��ȡ��ѯ��¼��
	Sint32 siCount = dbCount(Handler);
	return siCount;
}

//��ѯ�ļ�
LIBZMSGDLL_API int zdFile( int filetype,char* querysql,HWND pwnd)
{
	Sint32      siRet;
	Sint8       szName[256];
	Uint32      uiFileNum;
	Sint8       szFileName[256];
	Sint8       szFileNameS[256];
	Sint32      i;
	Sint32      siCount;
	DbHandler   Handler;

	// ������ѯ���
	Handler = dbNew();
	if(Handler == NULL)
	{
		return 0;
	}

	// ��ѯ�ļ��б�
	siRet = dbQueryFile(Handler, filetype, 3, 5115, querysql);
	if(siRet < 0)
	{
		ze_perror(siRet, "dbQueryFile");
		return 0;
	}

	// ��ȡ��ѯ��¼��
	siCount = dbCount(Handler);

	// �洢��ѯ������ļ�
	//siRet = dbDumpToFile(Handler, "HelloFileQuery");

	// ��ȡ��ѯ���
	while(!dbEof(Handler))
	{
		// ��ȡ�ļ�����
		strcpy(szName, "uiFileNum");
		siRet = dbGetUInt(Handler, szName, &uiFileNum);
		if(siRet < 0)
		{
			ze_perror(siRet, "dbGetUInt");
			break;
		}
		printf("%d, ", uiFileNum);

		// ��ȡϵͳ�ļ���
		strcpy(szName, "szFileNameS");
		siRet = dbGetString(Handler, szName, szFileNameS, sizeof(szFileNameS));
		if(siRet < 0)
		{
			ze_perror(siRet, "dbGetString");
			break;
		}
		printf("%s, ", szFileNameS);

		// ��ȡ�û��ļ���
		for(i = 0; i < uiFileNum; i++)
		{
			sprintf(szName, "szFileName[%d]", i+1);
			siRet = dbGetString(Handler, szName, szFileName, sizeof(szFileName));
			if(siRet < 0)
			{
				ze_perror(siRet, "dbGetString");
				break;
			}
			printf("%s, ", szFileName);
			m_func(szFileName,256,szFileNameS,256,filetype,3,5115);
		}
		printf("\n");		
		// �����α�
		dbNext(Handler);
	}

	//SendMessage(pwnd,520,0,0);
	// �رղ�ѯ���
	dbFree(Handler);

	return 1;
}

#pragma endregion zdFile,��ѯ�ļ�

#pragma region zfget,��ȡ�ļ�

LIBZMSGDLL_API int zfget( char* filename,char* filenames,int uiFileTypes,int uiTaskCode,int uiObjCode)
{
	int ret;
	ZF_FileHead filehead;
	filehead.uiFileType=uiFileTypes;
	filehead.uiTaskCode=uiTaskCode;
	filehead.uiObjCode=uiObjCode;

	// �����ʼ����UNIX�汾��ѡ��
	ret = zf2_init();
	if(ret < 0)
	{
		ze_perror(ret, "zf_init");
		return -1;
	}
	ret = zf2_getone(&filehead,filename,filenames);

	if(ret < 0)
	{
		ze_perror(ret, "zf2_getone");
		return -2;
	}
	return 1;
}

#pragma endregion zfget,��ȡ�ļ�

#pragma region zf��أ����߼����ļ�

LIBZMSGDLL_API int zfRecvw( char* strDirecPath,HWND pwhd) //const char* strDirecPath
{
	int             ret;
	//unsigned int    msgtype[] = {IFLI_RNAVIP,IFLI_RPACPA,IFLI_YSDHX,IFLI_YSQJX,IFLI_YSBZX,IFLI_ZS,IFLI_FYQJX,IFLI_GC_100CM,IFLI_GC_10CM,IFLI_GC_1CM,IFLI_GC_HIGH}; 
    unsigned int    msgtype[] = {100,5051,5084,5054,5000,5001,5002,5016,5026,5027,5028,5029,5030,5520}; 
	ZM_MsgHead      msghead;
	char            buf[1024*64];
	ZM_Addr         from;
	int             cnt = 0;
	CmlDocHandler   handler;
	char            path[256];
	int             i;
	unsigned int    filenum;
	char            filenames[256];
	char            strval[256];
	char            floder[256];
	//char*            FileFloder;


	// �����ʼ��
	ret = zm_init();
	if(ret < 0)
	{
		ze_perror(ret, "zm_init");
		return -1;
	}
	ret = zf2_init();
	if(ret < 0)
	{
		ze_perror(ret, "zf_init");
		return -2;
	}

	// �����ļ�
	qid = zm_open(sizeof(msgtype)/sizeof(int), msgtype, ZM_REM_DUP, 0, 0, 1024*1024*1);
	if(qid < 0)
	{
		ze_perror(qid, "zm_open");
		return -3;
	}

	// ��ȡ�����ļ�
	if (strDirecPath==NULL)
	{
		sprintf(strDirecPath, "D:\\CE3Map\\");
	}


	// ���մ����ļ�
	while(1)
	{
		
		// ����֪ͨ
		ret = zm_recvw(qid, &msghead, buf, sizeof(buf), &from);
		if(ret < 0)
		{
			ze_perror(ret, "ms_recvw");
			break;
		}

		printf("no%d rcvlen=%d M=%d T=%x O=%x form [%s:%s]\n",
			++cnt, 
			ret,
			msghead.uiMsgType,
			msghead.uiTaskCode,
			msghead.uiObjCode,
			//from.szHostName,
			from.szProcName);

		// ��ȡ֪ͨ����ȡ�ļ�
		handler = cmlLoadDocFromMem(buf, ret);
		if(handler == NULL)
		{
			break;
		}
		cmlGetString(handler, "/cmlRoot/szFileNameS", filenames, sizeof(filenames));
		cmlGetUInt(handler, "/cmlRoot/uiFileNum", &filenum);
		for(i = 0; i < filenum; i++)
		{
			memset(filename,0,256);
			memset(floder,0,256);
			sprintf(path, "/cmlRoot/szFileName[%d]", i+1);
			cmlGetString(handler, path, strval, sizeof(strval));

			if (msghead.uiMsgType==5051||msghead.uiMsgType==5084)
			{
				sprintf(floder,"\\IFLI_RNAVIP 5051\\%s",strval);					
			}
			else if (msghead.uiMsgType==5054)
			{
				sprintf(floder,"\\IFLI_RPACPA 5054\\%s",strval);
			}
			else if (msghead.uiMsgType==5000)
			{
				sprintf(floder,"\\IFLI_YSDHX 5000\\%s",strval);
			}
			else if (msghead.uiMsgType==5001)
			{
				sprintf(floder,"\\IFLI_YSQJX 5001\\%s",strval);
			}
			else if (msghead.uiMsgType==5002)
			{
				sprintf(floder,"\\IFLI_YSBZX 5002\\%s",strval);
			}
			else if (msghead.uiMsgType==5016)
			{
				sprintf(floder,"\\IFLI_ZS 5016\\%s",strval);
			}
			else if (msghead.uiMsgType==5026)
			{
				sprintf(floder,"\\IFLI_FYQJX 5026\\%s",strval);
			}
			else if (msghead.uiMsgType==5027)
			{
				sprintf(floder,"\\IFLI_GC_100CM 5027\\%s",strval);
			}
			else if (msghead.uiMsgType==5028)
			{
				sprintf(floder,"\\IFLI_GC_10CM 5028\\%s",strval);
			}
			else if (msghead.uiMsgType==5029)
			{
				sprintf(floder,"\\IFLI_GC_1CM 5029\\%s",strval);
			}
			else if (msghead.uiMsgType==5030)
			{
				sprintf(floder,"\\IFLI_GC_HIGH 5030\\%s",strval);
			}
			else if (msghead.uiMsgType==5520)
			{
				sprintf(floder,"\\IFLI_RZLLAND 5520\\%s",strval);
			}
			else
			{
				break;
			}

			sprintf(filename, "%s%s", strDirecPath, floder);

				/*char* szTmp=(char*)malloc(sizeof(char)*1024);
				memset(szTmp, 0, sizeof(char)*1024);
				sprintf(szTmp, "%s%s", strDirecPath, floder);

				strDirecPath=szTmp;
				sprintf(filename, strDirecPath);*/
			//}
			ret = zf2_getone((ZF_FileHead*)&msghead, filename, filenames);
			if(ret < 0)
			{
				ze_perror(ret, "zf2_getone");
				break;
			}

			ofstream in ;
			in.open("D:\\filerec.txt",ios::trunc);
			for (int i=0;i<256;i++)
			{
				if (filename[i]!=-52)
				{
					in<<filename[i];
				}
			}
			in.close();
			// �ͷ�XML�ĵ� *
			cmlFreeDocHandler(handler);

			//����һ������Ϊ521����Ϣ�������������
			if (msghead.uiMsgType==5520)
			{
				Sleep(1000);
				SendMessage(pwhd,5520,0,0);
			}
			else
			{
				SendMessage(pwhd,521,0,0);
			}
				
		}


	}


	return 1;
}

LIBZMSGDLL_API int zfclose()
{
	return zm_close(qid);
}

#pragma endregion zf��أ����߼����ļ�

#pragma region zg,ȫ�ֶη���

zgCallBackVec m_zgfunc;
LIBZMSGDLL_API void Register_CallBack_Vec(zgCallBackVec func)
{
	m_zgfunc = func;
}

LIBZMSGDLL_API int zg_vec( int uiTaskCode,int uiObjCode,int vecindex)
{
	Sint32 ret;
	Sint8  pscValid;
	Float64 pdValue1;
	Float64 pdValue2;
	Float64 pdValue3;

	ret=zg_init(uiTaskCode, uiObjCode,CN_RDONLY);
	if (ret<0)
	{
		return -1;
	}
	ret=zg_getvec(uiTaskCode, uiObjCode,vecindex,&pscValid, &pdValue1,&pdValue2,&pdValue3);
	if (ret<0)
	{
		return -2;
	}

	m_zgfunc(pdValue1,pdValue2,pdValue3);

	return 1;
}

#pragma endregion zg,ȫ�ֶη���