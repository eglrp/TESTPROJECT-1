#ifndef __FREEXMLDOC_H__
#define __FREEXMLDOC_H__

#include "cml_global.h"

#ifdef __cplusplus
extern "C" {
#endif 


/*
*˵  ���� �ͷ�handler��ռ��Դ��ʹ��baccNewEmptyXmlDoc��
          baccNewDocFromRaw��baccNewDocFromZip��baccNewDocFromFile
          ���ĸ�����������xml�ĵ��������Ҫ���øú����ͷ���Դ��
          ����ᵼ���ڴ�й¶��
*��  ���� handle �ĵ����
*����ֵ�� ��
*/
extern void cmlFreeDocHandler(CmlDocHandler handle);


#ifdef __cplusplus
}
#endif 

#endif /*__FREEXMLDOC_H__*/

