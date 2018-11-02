/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlFileRaster.cpp
* @date 2011.11.02
* @author ������ liuzq@irsa.ac.cn
* @brief Ӱ���ļ���дԴ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/

#include "mlFileRaster.h"

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
CmlFileRaster::CmlFileRaster()
{
    //ctor
}
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
CmlFileRaster::~CmlFileRaster()
{
    //dtor
}
/**
* @fn SaveBlockToFile
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��դ��Ӱ�������ļ�
* @param nBands դ��Ӱ�񲨶κ�
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
bool CmlFileRaster::SaveBlockToFile(SINT nBand, SINT nXOffSet, SINT nYOffSet, CmlRasterBlock* pImgBlock, SINT nBlockBand)
{
    return true;
}
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
bool CmlFileRaster::CreateFile(SCHAR *FileName, SINT nW,SINT nH,SINT nBands,SINT nBytes,SCHAR *BitsOut)
{
    return true;
}

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
bool CmlFileRaster::LoadFile(SCHAR *FileName, SINT nType)
{
    return true;
}

///** @brief GetHight
//  *
//  * @todo: document this function
//  */
//SINT CmlFileRaster::GetHight() const
//{
//
//}
//
///** @brief GetWidth
//  *
//  * @todo: document this function
//  */
//SINT CmlFileRaster::GetWidth() const
//{
//
//}
//
///** @brief GetBytes
//  *
//  * @todo: document this function
//  */
//SINT CmlFileRaster::GetBytes() const
//{
//
//}
//
///** @brief GetBands
//  *
//  * @todo: document this function
//  */
//SINT CmlFileRaster::GetBands() const
//{
//
//}
//
