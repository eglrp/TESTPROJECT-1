
#ifndef __PARSEXMLDOC_H__
#define __PARSEXMLDOC_H__

#include "cml_global.h"


#ifdef __cplusplus
extern "C" {
#endif 
 
/*
*˵��������XML�ĵ����ݣ������ĵ����������cmlGetϵ�к���ȡ���ݡ�
       ������ѹ�������ݻ���δѹ�������ݣ������øú���������
*������ pucContent  ���ݵ�ַ��
        siSize      ���ݳ��ȡ�
*����ֵ���ɹ������ĵ������ʧ�ܷ��� 0 ��
*/
extern CmlDocHandler cmlLoadDocFromMem(const Sint8 *pucContent,Sint32 siSize);


/*
*˵��������XML�ļ��������ĵ���������ú�����cmlGetϵ�к���ȡ���ݡ�
*������ pscFileName ���ݵ�ַ��
*����ֵ���ɹ������ĵ������ʧ�ܷ��� 0 ��
*/
extern CmlDocHandler cmlLoadDocFromFile(const Sint8 *pscFileName);


/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ�ַ�����
*������handle      �ĵ�ָ��
*      pscPath     XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*      pucContent  �洢���ݵĻ�������
*      siSize      ���������ȣ��û�Ӧȷ���������㹻����ʵ�����ݣ�����������-1��
                   ����������Ӧ��ʵ�����ݳ��ȴ�1����Ϊ�ú���Ҫ���ַ���ĩβ���Ͻ�������
*����ֵ:�ɹ������ַ������ȣ�ʧ�ܷ���-1
*/
extern Sint32 cmlGetString(CmlDocHandler handle,const Sint8* pscPath,  Sint8* pucContent, Sint32 siSize);



/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ���������ݡ�
*����:handle     �ĵ�ָ��
*     pscPath    XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     pucContent ���ݻ����ַ
*     siSize    ��
*����ֵ���ɹ����ض��������ݳ��ȣ�ʧ�ܷ���-1��
*/
extern Sint32 cmlGetBinary(CmlDocHandler handle,const Sint8* pscPath, Sint8* pucContent, Sint32 siSize);



/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ8λ�з������͡�
*����:handle   �ĵ�ָ��
*     pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     pscValue �洢����ĵ�ַ��
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetByte(CmlDocHandler handle,const Sint8* pscPath, Sint8 *pscValue);


/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ8λ�޷������͡�
*����:handle   �ĵ�ָ��
*     pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     pucValue �洢����ĵ�ַ��
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetUByte(CmlDocHandler handle,const Sint8* pscPath, Uint8 *pucValue);



/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ16λ�з������͡�
*����:handle   �ĵ�ָ��
*     pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     pssValue �洢����ĵ�ַ��
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetShort(CmlDocHandler handle,const Sint8* pscPath,  Sint16 *pssValue);



/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ16λ�޷������͡�
*����:handle   �ĵ�ָ��
*     pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     pusValue �洢����ĵ�ַ��
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetUShort(CmlDocHandler handle,const Sint8* pscPath,  Uint16 *pusValue);




/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ32λ�з������͡�
*����:handle   �ĵ�ָ��
*     pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     psiValue �洢����ĵ�ַ��
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetInt(CmlDocHandler handle,const Sint8* pscPath,  Sint32 *psiValue);



/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ32λ�޷������͡�
*����:handle   �ĵ�ָ��
*     pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     puiValue �洢����ĵ�ַ��
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetUInt(CmlDocHandler handle,const Sint8* pscPath,  Uint32 *puiValue);


/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ64λ�з������͡�
*����:handle   �ĵ�ָ��
*     pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     pslValue �洢����ĵ�ַ��
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetLong(CmlDocHandler handle,const Sint8* pscPath,  Sint64 *pslValue);


/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ64λ�޷������͡�
*����:handle   �ĵ�ָ��
*     pscPath  XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     pulValue �洢����ĵ�ַ��
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetULong(CmlDocHandler handle,const Sint8* pscPath,  Uint64 *pulValue);



/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ�����ȸ����͡�
*����:handle     �ĵ�ָ��
*     pscPath    XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     pfValue    �洢����ĵ�ַ
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetFloat(CmlDocHandler handle,const Sint8* pscPath,  Float32 *pfValue);



/*
*˵������ȡ�ĵ���ĳԪ�ص����ݣ���Ԫ��ʵ����������Ϊ˫���ȸ����͡�
*����:handle     �ĵ�ָ��
*     pscPath    XPath���ʽ����λ�ĵ��е�ΨһԪ�ء�
*     pdValue    �洢����ĵ�ַ
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
extern Sint32 cmlGetDouble(CmlDocHandler handle,const Sint8* pscPath, Float64 *pdValue);


/*
*˵����   ���ú��������ѹ���ͷ�ѹ�����ĵ�����Ϊ��ѹ���ġ�
*����:    pcInput    �������ݵ�ַ   
				  siInputSize �������ݳ���
				  pcOutput ��������ַ
				  siOutputSize ������峤��
				  psiUncompressSize  �������ʵ�ʳ���
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
 extern Sint32 unzipCml(const Sint8* pcInput, 
				  const Sint32 siInputSize,
				  Sint8* pcOutput,
				  Sint32 siOutputSize,
				  Sint32* psiUncompressSize);
				  

#ifdef __cplusplus
}
#endif


#endif /*__PARSEXMLDOC_H__*/

