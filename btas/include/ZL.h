
/**
\file       ZL.h
\brief      ��־����
            
            �ṩʹ����־����ı�̽ӿڡ�
            
\author     ������
\date       2009-11-18
\version    1.0
\note       WINDOWS/C
\par        �޸ļ�¼ 
            - ������ 2009-11-18 ģ�齨��
            
*/


#ifndef _ZL_H__
#define _ZL_H__


/********************************** �������� ****************************/
#ifdef __cplusplus
extern "C" {
#endif

int zl_init();                                  /* �����ʼ��           */
int zl_send(unsigned char ucLogType,
            unsigned int  uiMisCode,
            unsigned int  uiObjCode,
            const char    szLogContent[]);      /* ������־             */
void zl_perror(int        siErrCode,
               const char szErrPre[]);          /* ��ȡ����˵��         */
char* zl_strerr(int siErrCode);                 /* ��ȡ����˵��         */

#ifdef __cplusplus
}
#endif
/************************************************************************/


#endif
