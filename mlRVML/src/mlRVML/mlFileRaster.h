/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlFileRaster.h
* @date 2011.11.02
* @author ������ liuzq@irsa.ac.cn
* @brief Ӱ���ļ���дͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef CFILEIMAGE_H
#define CFILEIMAGE_H

#include"gdal_header.h"
#include "mlBase.h"
#include "mlRasterBlock.h"

/**
* @class CmlFileRaster
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief դ�������
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlFileRaster
{
public:
    /**
    * @fn CmlFileRaster
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlFileRaster��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlFileRaster();
    /**
    * @fn ~CmlFileRaster
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlFileRaster����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual ~CmlFileRaster();

public:
    virtual UINT GetBands() const = 0;//!<�õ�դ��Ӱ�񲨶���
    virtual UINT GetBytes() const = 0;//!<�õ�դ��Ӱ�������
    virtual UINT GetWidth() const = 0;//!<�õ�դ��Ӱ���
    virtual UINT GetHeight() const = 0;//!<�õ�դ��Ӱ���

    /**
    * @fn LoadFile
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����դ��Ӱ���ļ�
    * @param FileName �ļ�����
    * @param nType Ӱ��ԭ��λ�ñ�ʶ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual bool LoadFile(SCHAR *FileName, SINT nType=0);//nType 0--Ӱ��ԭ�������Ͻ� 1--Ӱ��ԭ�������½�
    /**
    * @fn CreateFile
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����դ��Ӱ���ļ�
    * @param FileName �ļ�����
    * @param nW դ��Ӱ���
    * @param nH դ��Ӱ���
    * @param nBands դ��Ӱ�񲨶���
    * @param nBytes դ��Ӱ�������
    * @param BitsOut ����ͼ������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual bool CreateFile(SCHAR *FileName, SINT nW,SINT nH,SINT nBands,SINT nBytes,SCHAR *BitsOut);
    /**
    * @fn SaveBlockToFile
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��դ��Ӱ�������ļ�
    * @param nBand դ��Ӱ�񲨶κ�
    * @param FileName �ļ�����
    * @param nXOffSet դ��Ӱ��X����ƫ����
    * @param nYOffSet դ��Ӱ��Y����ƫ����
    * @param pImgBlock դ��Ӱ���
    * @param nBlockBand Ŀ���ļ����κ�
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual bool SaveBlockToFile( SINT nBand, SINT nXOffSet, SINT nYOffSet, CmlRasterBlock* pImgBlock, SINT nBlockBand);

    string m_strFileName;//!<�ļ���
protected:
private:
};


#endif // CFILEIMAGE_H
