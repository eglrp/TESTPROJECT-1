#ifndef __BACCXMLGLOBAL_H__
#define __BACCXMLGLOBAL_H__


#include "cml_global.h"


#ifdef __cplusplus
extern "C" {
#endif 


/*
*˵  ������֤xml�ĵ��Ƿ�Ϸ���
*��  ����handle �ĵ����
*����ֵ: 0 �Ϸ���<0 ���Ϸ�
*/
extern Sint32 cmlValidateDoc(CmlDocHandler handle);


/*
*���ã������֤�ļ�����·��
*����������·��
*����ֵ�� ��
*/

extern void cmlAddXsdDir(const Sint8* psiXsdPath);





#ifdef __cplusplus
}
#endif 


#endif //__BACCXMLGLOBAL_H__


