
/**
\file       ZG.h
\brief      ȫ�ֶη���
            
            �ṩʹ��ȫ�ֶη���ı�̽ӿڡ�
            
\author     ������
\date       2012-08-16
\version    1.0
\note       WINDOWS/C
\par        �޸ļ�¼ 
            - ������    2012-08-16  ģ�齨��
            
*/


#ifndef _ZG_H__
#define _ZG_H__


#include "BTAS_TYPES.h"
#include "STRTIME.h"


/****************************** �������� ************************************/
#define CN_RDONLY               0               /* ��дģʽ��ֻ��           */
#define CN_RDWR                 1               /* ��дģʽ����д           */
/****************************************************************************/


/***************************** �������� *************************************/
#ifdef __cplusplus
extern "C" {
#endif

Sint32 zg_init(Uint32 uiMisCode,
               Uint32 uiObjCode,
               Uint32 uiRwMode);                /* �����ʼ��               */
void zg_exit(Uint32 uiMisCode, 
             Uint32 uiObjCode);                 /* �����˳�                 */
Sint32 zg_gethostname(Sint8 szHostName[]);      /* ��ȡ������               */
#define zg_getHostName(p1) zg_gethostname(p1)
Sint32 zg_gethoststat(Uint32* puiHostStat);     /* ��ȡ����״̬             */
#define zg_getMainBack(p1) zg_gethoststat(p1)
Sint32 zg_getmisname(Uint32 uiMisCode,
                     Uint32 uiObjCode,
                     Sint8  szMisName[]);       /* ��ȡ������               */
#define zg_getMisName(p1,p2,p3) zg_getmisname(p1,p2,p3)
Sint32 zg_getobjname(Uint32 uiMisCode,
                     Uint32 uiObjCode,
                     Sint8  szObjName[]);       /* ��ȡĿ����               */
#define zg_getObjName(p1,p2,p3) zg_getobjname(p1,p2,p3)
Sint32 zg_getdt(Uint32  uiMisCode,
                Uint32  uiObjCode,
                Sint32* psiDt);                 /* ��ȡ����ʱ��             */
#define zg_getDt(p1,p2,p3) zg_getdt(p1,p2,p3)
Sint32 zg_setdt(Uint32 uiMisCode,
                Uint32 uiObjCode,
                Sint32 siDt);                   /* ��������ʱ��             */
#define zg_setDt(p1,p2,p3) zg_setdt(p1,p2,p3) 
Sint32 zg_getphase(Uint32 uiMisCode,
                   Uint32 uiObjCode,
                   Sint8  szPhase[]);           /* ��ȡ����α�             */
#define zg_getPhase(p1,p2,p3) zg_getphase(p1,p2,p3)
Sint32 zg_setphase(Uint32      uiMisCode,
                   Uint32      uiObjCode,
                   const Sint8 szPhase[]);      /* ���ù���α�             */
#define zg_setPhase(p1,p2,p3) zg_setphase(p1,p2,p3)
Sint32 zg_getrevnum(Uint32  uiMisCode,
                    Uint32  uiObjCode,
                    Uint32* puiRevNum);         /* ��ȡ���Ȧ��             */
#define zg_getRevNum(p1,p2,p3) zg_getrevnum(p1,p2,p3)
Sint32 zg_setrevnum(Uint32 uiMisCode,
                    Uint32 uiObjCode,
                    Uint32 uiRevNum);           /* ���ù��Ȧ��             */
#define zg_setRevNum(p1,p2,p3) zg_setrevnum(p1,p2,p3)
Sint32 zg_gett0flag(Uint32  uiMisCode,
                    Uint32  uiObjCode,
                    Uint32* puiT0Flag);         /* ��ȡT0���ձ�־           */
#define zg_getT0Flag(p1,p2,p3) zg_gett0flag(p1,p2,p3)
Sint32 zg_sett0flag(Uint32 uiMisCode,
                    Uint32 uiObjCode,
                    Uint32 uiT0Flag);           /* ����T0���ձ�־           */
#define zg_setT0Flag(p1,p2,p3) zg_sett0flag(p1,p2,p3)
Sint32 zg_getthtf(Uint32  uiMisCode,
                  Uint32  uiObjCode,
                  Uint32* puiThTf);             /* ��ȡ����TF               */
#define zg_getThTf(p1,p2,p3) zg_getthtf(p1,p2,p3)
Sint32 zg_setthtf(Uint32 uiMisCode,
                  Uint32 uiObjCode,
                  Uint32 uiThTf);               /* ��������TF               */
#define zg_setThTf(p1,p2,p3) zg_setthtf(p1,p2,p3)
Sint32 zg_getstationcode(Uint32      uiMisCode,
                         Uint32      uiObjCode,
                         const Sint8 szSName[],
                         Uint32*     uiSCode);  /* ͨ��վ��ȡվ��           */
#define zg_getStationCode(p1,p2,p3,p4) zg_getstationcode(p1,p2,p3,p4)
Sint32 zg_getstationname(Uint32 uiMisCode,
                         Uint32 uiObjCode,
                         Uint32 uiSCode,
                         Sint8  szSName[]);     /* ͨ��վ��ȡվ��           */
#define zg_getStationName(p1,p2,p3,p4) zg_getstationname(p1,p2,p3,p4)
Sint32 zg_getint(Uint32  uiMisCode,
                 Uint32  uiObjCode,
                 Uint32  uiIndex,
                 Sint8*  pscValid,
                 Sint32* psiValue);             /* ��ȡ��������Ϣ           */
Sint32 zg_setint(Uint32 uiMisCode,
                 Uint32 uiObjCode,
                 Uint32 uiIndex,
                 Sint8  scValid,
                 Sint32 siValue);               /* ������������Ϣ           */
Sint32 zg_getdouble(Uint32   uiMisCode,
                    Uint32   uiObjCode,
                    Uint32   uiIndex,
                    Sint8*   pscValid,
                    Float64* pdValue);          /* ��ȡ��������Ϣ           */
Sint32 zg_setdouble(Uint32  uiMisCode,
                    Uint32  uiObjCode,
                    Uint32  uiIndex,
                    Sint8   scValid,
                    Float64 dValue);            /* ���ø�������Ϣ           */
Sint32 zg_getstring(Uint32 uiMisCode,
                    Uint32 uiObjCode,
                    Uint32 uiIndex,
                    Sint8* pscValid,
                    Sint8  szValue[]);          /* ��ȡ�ַ�������Ϣ         */
Sint32 zg_setstring(Uint32      uiMisCode,
                    Uint32      uiObjCode,
                    Uint32      uiIndex,
                    Sint8       scValid,
                    const Sint8 szValue[]);     /* �����ַ�������Ϣ         */
Sint32 zg_getvec(Uint32   uiMisCode,
                 Uint32   uiObjCode,
                 Uint32   uiIndex,
                 Sint8*   pscValid,
                 Float64* pdValue1,
                 Float64* pdValue2,
                 Float64* pdValue3);            /* ��ȡ��������Ϣ           */
Sint32 zg_setvec(Uint32  uiMisCode,
                 Uint32  uiObjCode,
                 Uint32  uiIndex,
                 Sint8   scValid,
                 Float64 dValue1,
                 Float64 dValue2,
                 Float64 dValue3);              /* ������������Ϣ           */
Sint32 zg_getevt(Uint32   uiMisCode,
                 Uint32   uiObjCode,
                 Uint32   uiIndex,
                 Sint8*   pscValid,
                 ST_Time* pstValue);            /* ��ȡ�¼�����Ϣ           */
Sint32 zg_setevt(Uint32   uiMisCode,
                 Uint32   uiObjCode,
                 Uint32   uiIndex,
                 Sint8    scValid,
                 ST_Time* pstValue);            /* �����¼�����Ϣ           */
Sint32 zg_getevtflag(Uint32 uiMisCode,
                     Uint32 uiObjCode,
                     Uint32 uiIndex,
                     Sint8* pscFlag);           /* ��ȡ�¼�����Ϣ��־       */
#define zg_getTmEvtFlag(p1,p2,p3,p4) zg_getevtflag(p1,p2,p3,p4)
Sint32 zg_setevtflag(Uint32 uiMisCode,
                     Uint32 uiObjCode,
                     Uint32 uiIndex,
                     Sint8  scFlag);            /* �����¼�����Ϣ��־       */
#define zg_setTmEvtFlag(p1,p2,p3,p4) zg_setevtflag(p1,p2,p3,p4)
Sint32 zg_getevttime(Uint32   uiMisCode,
                     Uint32   uiObjCode,
                     Uint32   uiIndex,
                     ST_Time* pstTime);         /* ��ȡ�¼�����Ϣֵ         */
#define zg_getTmEvtTime(p1,p2,p3,p4) zg_getevttime(p1,p2,p3,p4)
Sint32 zg_setevttime(Uint32   uiMisCode,
                     Uint32   uiObjCode,
                     Uint32   uiIndex,
                     ST_Time* pstTime);         /* �����¼�����Ϣֵ         */
#define zg_setTmEvtTime(p1,p2,p3,p4) zg_setevttime(p1,p2,p3,p4)
void zg_perror(Sint32       siErrCode,
               const Sint8* pszErrPre);         /* ��ȡ����˵��             */
Sint8* zg_strerr(Sint32 siErrCode);             /* ��ȡ����˵��             */
Sint32 zg_getcompath(const Sint8 szString[],
                     Sint8       szPath[]);     /* ��ȡ����ִ������·��     */
Sint32 zg_getcomlpath(const Sint8 szString[],
                      Sint8       szPath[]);    /* ��ȡ����ִ���߼�·��     */
Sint32 zg_getmispath(Uint32      uiMisCode,
                     const Sint8 szString[],
                     Sint8       szPath[]);     /* ��ȡ����ִ������·��     */
Sint32 zg_getmislpath(Uint32      uiMisCode,
                      const Sint8 szString[],
                      Sint8       szPath[]);    /* ��ȡ����ִ���߼�·��     */
Sint32 zg_getobjpath(Uint32      uiMisCode,
                     Uint32      uiObjCode,
                     const Sint8 szString[],
                     Sint8       szPath[]);     /* ��ȡĿ��ִ������·��     */
Sint32 zg_getobjlpath(Uint32      uiMisCode,
                      Uint32      uiObjCode,
                      const Sint8 szString[],
                      Sint8       szPath[]);    /* ��ȡĿ��ִ���߼�·��     */
Sint32 zg_getobjlist(Uint32 uiMisCode,
                     Uint32 uiObjList[]);       /* ��ȡĿ���б�             */

#ifdef __cplusplus
}
#endif
/****************************************************************************/

#endif
