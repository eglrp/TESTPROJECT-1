
/**
\file       DUP.h
\brief      ˫������
            
            ����˫������ı�̽ӿڡ�
            
\author     ������
\date       2009-11-18
\version    1.0
\note       WINDOSW/C
\par        �޸ļ�¼ 
            - ������ 2009-11-18 ģ�齨��
            
*/


#ifndef _DUP_H__
#define _DUP_H__


/************************** �������� ********************************/
#ifdef __cplusplus
extern "C" {
#endif

int dup_open();                             /* ��˫��α�豸       */
int dup_close(int siDupFd);                 /* �ر�˫��α�豸       */
int getdupsts(int           siDupFd,
              unsigned int* puiDupSts);     /* ��ȡ˫��״̬         */

#ifdef __cplusplus
}
#endif
/********************************************************************/


#endif
