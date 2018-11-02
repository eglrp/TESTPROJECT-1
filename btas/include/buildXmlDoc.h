
#ifndef __BUILDXMLDOC_H__
#define __BUILDXMLDOC_H__

/*#include "vld.h" �����ڴ����*/

#include "cml_global.h"

#ifdef __cplusplus
extern "C" {
#endif 
 

/*
*˵  �������ڴ��д���һ���յ�xml�ĵ�������ʹ��cmlPut*
         ϵ�к�������ĵ���������ݡ�
*��  ����pscSchemaName �ĵ���Ӧschema�����ƣ�����0��β���ַ�����
*����ֵ���ɹ������ĵ������������С��0��ֵ ��
*/
extern CmlDocHandler cmlNewEmptyDoc(const Sint8 *pscSchemaName);


/*
*˵�������ĵ�ָ��λ����ӣ����޸ģ��ַ������͵�Ԫ�أ����ָ��Ԫ�ز����ڣ�
       �����Ԫ�أ����ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*������handle     �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*      pscPath    XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*      pscContent ���ݵ�ַ
*      siSize     ���ݳ���
*����ֵ:�ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutString(CmlDocHandler handle,const Sint8* pscPath, const Sint8* pscContent, Sint32 siSize);


/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ����������͵�Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��:handle     �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*       pscPath    XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*       pscContent ���ݵ�ַ
*       siSize   ���ݳ���
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutBinary(CmlDocHandler handle,const Sint8* pscPath, const void* pscContent,  Sint32 siSize);



/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ��1�ֽ��з�������Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle   �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        scValue  Ҫ��ӵ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutByte(CmlDocHandler handle,const Sint8* pscPath, Sint8 scValue);



/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ��1�ֽ��޷�������Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle   �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        ucValue  Ҫ��ӵ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutUByte(CmlDocHandler handle,const Sint8* pscPath, Uint8 ucValue);




/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ��2�ֽ��з�������Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle   �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        ssValue  Ҫ��ӵ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutShort(CmlDocHandler handle,const Sint8* pscPath, Sint16 ssValue);


/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ��2�ֽ��޷�������Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle   �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        usValue  Ҫ��ӵ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutUShort(CmlDocHandler handle,const Sint8* pscPath, Uint16 usValue);



/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ��4�ֽ��з�������Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle  �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscPath XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        siValue Ҫ��ӵ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutInt(CmlDocHandler handle,const Sint8* pscPath, Sint32 siValue);


/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ��4�ֽ��޷�������Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle  �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscPath XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        uiValue Ҫ��ӵ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutUInt(CmlDocHandler handle,const Sint8* pscPath, Uint32 uiValue);


/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ��8�ֽ��з�������Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle   �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        slValue  Ҫ��ӵ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutLong(CmlDocHandler handle,const Sint8* pscPath, Sint64 slValue);



/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ��8�ֽ��޷�������Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle   �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        ulValue  Ҫ��ӵ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutULong(CmlDocHandler handle,const Sint8* pscPath, Uint64 ulValue);



/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ�������ȸ�����Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle   �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pPath    XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        fValue   Ҫ��ӵĸ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutFloat(CmlDocHandler handle,const Sint8* pscPath, Float32 fValue);




/*
*˵  �������ĵ�ָ��λ����ӣ����޸ģ�һ��˫���ȸ�����Ԫ�أ����ָ��Ԫ�ز����ڣ��������Ԫ��
         ���ָ��Ԫ���Ѵ����򸲸�ԭ���ݡ�
*��  ��: handle   �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*        dValue   Ҫ��ӵĸ�����ֵ
*����ֵ���ɹ�����0��������С��0��ֵ
*/
extern Sint32 cmlPutDouble(CmlDocHandler handle,const Sint8* pscPath, Float64 dValue);





/*
*˵  �������ĵ������ȡ������xml�ĵ������ݣ�����δѹ����
*��  ����handle    �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
         ppcData   ������ݵ�ַ��ָ�룬�ɵ����߸����ͷ�pData��ָ��Ŀռ䣬
		     psiSize   ���ݳ���

*����ֵ����ȷ����0��������С��0��ֵ;
*/
/*extern int cmlDumpRawDocToMem(CmlDocHandler handle,Sint8** ppcData, Sint32* psiSize);*/



/*
*˵  ������δѹ�����ĵ����ݴ�ŵ��ļ��С�
*��  ����handle      �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
         pscFileName ����ĵ����ݵ��ļ�����
 
*����ֵ����ȷ����0��������С��0��ֵ;
*/
/*extern int cmlDumpRawDocToFile(CmlDocHandler handle,const Sint8* pscFileName);*/


/*
*˵  �������ĵ������ȡ������xml�ĵ������ݣ����ݾ���ѹ����
*��  ����handle  �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
         ppcData   ������ݵ�ַ��ָ�룬�ɵ����߸����ͷ�pData��ָ��Ŀռ䣬
         psiSize   ������ݳ��ȵĵ�ַ
*����ֵ����ȷ����0,������С��0��ֵ.
*/
/*extern int cmlDumpCompressDocToMem(CmlDocHandler handle,Sint8** ppcData,Sint32* psiSize);*/



/*
*˵  ������ѹ������ĵ����ݴ�ŵ��ļ��С�
*��  ����handle    �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
         pFileName ����ĵ����ݵ��ļ�����
  
*����ֵ����ȷ����0,������С��0��ֵ.
*/
/*extern int cmlDumpCompressDocToFile(CmlDocHandler handle,const Sint8* pscFileName);*/


/*
*˵�������ĵ������ȡ������xml�ĵ�������
*������handle    �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*      ppcData   ������ݵ�ָ���ַ��
       psiSize   ������ݳ��ȵĵ�ַ
*      siIfCompress 0 ��ѹ����1ѹ��
*����ֵ����ȷ����0,������С��0��ֵ.
*/
extern Sint32 cmlDumpDocToMem(CmlDocHandler handle,Sint8** ppcData, Sint32* psiSize, Sint32  siIfCompress);
 


/*
*˵�������ĵ������ȡ������xml�ĵ�������
*��  ����handle      �ĵ������cmlNewEmptyDoc�����ķ���ֵ��
*        pscFileName ����ĵ����ݵ��ļ�����
*        siIfCompress 0 ��ѹ����1ѹ��
*����ֵ����ȷ����0,������С��0��ֵ.
*/

extern Sint32 cmlDumpDocToFile(CmlDocHandler handle,const Sint8* pscFileName ,Sint32 siIfCompress);
 


#ifdef __cplusplus
}
#endif


#endif /*__BUILDXMLDOC_H__*/

