
/**
\file       ZF.h
\brief      �ļ��������
            
            �ṩ�ļ��������ı�̽ӿڡ�
            
\author     ������
\date       2009-11-18
\version    1.0
\note       WINDOSW/C
\par        �޸ļ�¼ 
            - ������ 2009-11-18 ģ�齨��
            
*/


#ifndef _ZF_H__
#define _ZF_H__


/************************** �������� ********************************/
#ifdef __cplusplus
extern "C" {
#endif

int zf_init();                              /* �����ʼ��           */
int zf_get(unsigned int uiMisCode,
           unsigned int uiObjCode,
           const char   szHost[],
           const char   szRemFile[],
           const char   szLocFile[],
           char         scType);            /* �����ļ�             */
int zf_put(unsigned int uiMisCode,
           unsigned int uiObjCode,
           const char   szHost[],
           const char   szRemFile[],
           const char   szLocFile[],
           char         scType);            /* �ϴ��ļ�             */
void zf_perror(int        siErrCode,
               const char szErrPre[]);      /* ��ȡ����˵��         */
char* zf_strerr(int siErrCode);             /* ��ȡ����˵��         */

#ifdef __cplusplus
}
#endif
/********************************************************************/


#endif
