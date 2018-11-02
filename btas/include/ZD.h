
/**
\file       ZD.h
            ���ݿ��ѯ����
            
            �ṩʹ�����ݿ��ѯ����ı�̽ӿڡ�
            
\author     ������
\date       2012-09-06
\version    1.0
\note       WINDOWS/C
\par        �޸ļ�¼ 
            - ������ 2012-09-06 ģ�齨��
            
*/


#ifndef _ZD_H__
#define _ZD_H__


#include "BTAS_TYPES.h"


/***************************** �ṹ���� *********************************************/
typedef void*   DbHandler;                          /* ���ݿ��ѯ���               */
/************************************************************************************/


/***************************** �������� *********************************************/
#ifdef __cplusplus
extern "C" {
#endif

DbHandler dbNew();                                  /* ������ѯ���                 */
void dbFree(DbHandler Handler);                     /* �رղ�ѯ���                 */
Sint32 dbQueryFile(DbHandler   Handler, 
                   Uint32      uiFileType, 
                   Uint32      uiTaskCode, 
                   Uint32      uiObjCode,
                   const Sint8 szCond[]);           /* ��ѯ�ļ�                     */
Sint32 dbQueryData(DbHandler   Handler, 
                   Uint32      uiDataType, 
                   Uint32      uiTaskCode, 
                   Uint32      uiObjCode,
                   const Sint8 szPara[],
                   const Sint8 szCond[]);           /* ��ѯ����                     */
Sint32 dbGetByte(DbHandler   Handler, 
                 const Sint8 szName[], 
                 Sint8*      pscValue);             /* ��ȡ��ѯ���(8λ�з�������)  */
Sint32 dbGetUByte(DbHandler   Handler, 
                  const Sint8 szName[], 
                  Uint8*      pucValue);            /* ��ȡ��ѯ���(8λ�޷�������)  */
Sint32 dbGetShort(DbHandler   Handler, 
                  const Sint8 szName[], 
                  Sint16*     pssValue);            /* ��ȡ��ѯ���(16λ�з�������) */
Sint32 dbGetUShort(DbHandler   Handler, 
                   const Sint8 szName[], 
                   Uint16*     pusValue);           /* ��ȡ��ѯ���(16λ�޷�������) */
Sint32 dbGetInt(DbHandler   Handler, 
                const Sint8 szName[], 
                Sint32*     psiValue);              /* ��ȡ��ѯ���(32λ�з�������) */
Sint32 dbGetUInt(DbHandler   Handler, 
                 const Sint8 szName[], 
                 Uint32*     puiValue);             /* ��ȡ��ѯ���(32λ�޷�������) */
Sint32 dbGetLong(DbHandler   Handler, 
                 const Sint8 szName[], 
                 Sint64*     pslValue);             /* ��ȡ��ѯ���(64λ�з�������) */
Sint32 dbGetULong(DbHandler   Handler, 
                  const Sint8 szName[], 
                  Uint64*     pulValue);            /* ��ȡ��ѯ���(64λ�޷�������) */
Sint32 dbGetFloat(DbHandler   Handler, 
                  const Sint8 szName[], 
                  Float32*    pfValue);             /* ��ȡ��ѯ���(�����ȸ�����)   */
Sint32 dbGetDouble(DbHandler   Handler, 
                   const Sint8 szName[], 
                   Float64*    pdValue);            /* ��ȡ��ѯ���(˫���ȸ�����)   */
Sint32 dbGetString(DbHandler   Handler, 
                   const Sint8 szName[], 
                   Sint8       szValue[], 
                   Sint32      siLen);              /* ��ȡ��ѯ���(�ַ�����)       */
Sint32 dbNext(DbHandler Handler);                   /* �����α�                     */
Sint32 dbPrev(DbHandler Handler);                   /* ǰ���α�                     */
Sint32 dbSeek(DbHandler Handler, 
              Sint32    siOffset, 
              Sint32    siWhence);                  /* ��λ�α�                     */
Sint32 dbTell(DbHandler Handler);                   /* ��ȡ�α�                     */
Sint32 dbEof(DbHandler Handler);                    /* �����ж�                     */
Sint32 dbCount(DbHandler Handler);                  /* ��ȡ��ѯ��¼��               */
Sint32 dbDumpToFile(DbHandler   Handler, 
                    const Sint8 szFileName[]);      /* �洢��ѯ������ļ�           */

#ifdef __cplusplus
}
#endif
/************************************************************************************/


#endif
