/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlRasterBlock.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief դ�����ݿ鴦��ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef CMLRASTERBLOCK_H
#define CMLRASTERBLOCK_H


/*************************
�ನ�ε�ͼ�����ݿ飬���ε���֯��BSQʵ�֣�һ�����ν�һ�����δ洢��(����ʵ��)
**************************/
#include "mlBase.h"
#include"gdal_header.h"



class CmlGdalDataset;
/**
* @class CmlRasterBlock
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �����д���դ��ʱ����Ԫ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlRasterBlock : protected CmlTemplateMat<BYTE>
{
public:
    /**
    * @fn CmlRasterBlock
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlRasterBlock��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlRasterBlock();
    /**
    * @fn ~CmlRasterBlock
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlRasterBlock����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

    ~CmlRasterBlock();
    /**
    * @fn CmlRasterBlock
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief դ�����ݿ��ʼ������
    * @param nXOffSet  դ�����ݿ�Xƫ����
    * @param nYOffSet  դ�����ݿ�Yƫ����
    * @param nW  դ�����ݿ��
    * @param nH  դ�����ݿ��
    * @param nBytes դ�����ݿ�λ��
    * @param nZoom  դ�����ݿ�����ϵ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlRasterBlock( const SINT nXOffSet, const SINT nYOffSet, const UINT nW, const UINT nH, const UINT nBytes, const UINT nZoom );

public:
    /**
    * @fn InitialImg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��ʼ��դ���ڴ溯��
    * @param nW  դ�����ݿ��
    * @param nH  դ�����ݿ��
    * @param nBytes դ�����ݿ�λ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool InitialImg( const UINT nH, const UINT nW, const UINT nBytes = 1 );
    /**
    * @fn ReSet
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ɾ�����ݣ���ɾ���ڴ�ռ�
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool ReSet();
    /**
    * @fn Clear
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���ýṹ��������ݣ�������Ϣ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool Clear();

    /**
    * @fn GetPtrAt
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �õ�ĳ��������ֵ��ͷָ��
    * @param nH  դ�����ݿ��
    * @param nW  դ�����ݿ��
    * @return ĳ��������ֵ��ͷָ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    BYTE* GetPtrAt( const UINT nH, const UINT nW ) const;
    /**
    * @fn SetPtrAt
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����ĳ��������ֵ
    * @param nH  դ�����ݿ��
    * @param nW  դ�����ݿ��
    * @param pVal ������ֵ��BYTE��ͷָ��
    * @return ĳ��������ֵ��ͷָ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    //��ԭ����ȡ�����ݵ�ͷָ�루BYTE�ͣ�������Ҫ���õ�ֵת����BYTEָ����뼴��
    bool  SetPtrAt( const UINT nH, const UINT nW, BYTE* pVal );
    /**
    * @fn GetAt
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �õ�դ���ĳ�����������һ���ֽ�ֵ����blockΪ���ֽ����ͣ���Ϊ����ֵ
    * @param nRow  դ�������к�
    * @param nCol դ�����ݿ��к�
    * @return դ���ĳ�����������һ���ֽ�ֵ
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    BYTE  GetAt( const UINT nRow, const UINT nCol );
    /**
    * @fn SetAt
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����դ���ĳ�����������һ���ֽ�ֵ����blockΪ���ֽ����ͣ���Ϊ��������ֵ
    * @param nRow  դ�������к�
    * @param nCol դ�����ݿ��к�
    * @param val դ���ĳ�����������һ���ֽ�ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool  SetAt( const UINT nRow, const UINT nCol, BYTE val );
    /**
    * @fn GetH
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �õ�դ��block�ĸ�
    * @return դ��block�ĸ�
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    UINT GetH() const
    {
        return m_nHeight;
    };
    /**
    * @fn GetW
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �õ�դ��block�Ŀ�
    * @return դ��block�Ŀ�
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    UINT GetW() const
    {
        return m_nWidth;
    };
    /**
    * @fn GetData
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �õ�դ��block���ݵ�ͷָ��
    * @return դ��block���ݵ�ͷָ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    BYTE* GetData() const
    {
        return m_pData;
    };
    /**
    * @fn GetTPixelSize
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �õ�դ��block���ݿ��ڵ���������ֵ����������
    * @return ������
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    SINT GetTPixelSize() const
    {
        return ( m_nTSize / m_nBytes );
    };
    /**
    * @fn IsValid
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �жϸ����ݿ��Ƿ���ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool IsValid() const
    {
        return (!m_bIsNULL);
    };

    bool SetXOffSet( SINT nXOffSet );//!<����Xƫ����
    bool SetYOffSet( SINT nXOffSet );//!<����Yƫ����
    bool SetZoom( UINT nZoom );

    SINT GetXOffSet()const//!<�õ�Xƫ����
    {
        return m_nXOffSet;
    };
    SINT GetYOffSet()const//!<�õ�Yƫ����
    {
        return m_nYOffSet;
    };
    UINT GetZoom() const//!<�õ�����ϵ��
    {
        return m_nZoom;
    };
    UINT GetBytes() const//!<�õ�������
    {
        return m_nBytes;
    };
    /**
    * @fn SetGDTType
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �������ݿ�����������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool SetGDTType( GDALDataType gType )
    {
        return (m_GDTType = gType);
    };
    /**
    * @fn SetGDTType
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �õ����ݿ�����������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    GDALDataType GetGDTType()const
    {
        return m_GDTType;
    };
    /**
    * @fn GetDoubleVal
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �õ����ݿ������ص�ֵ��ǿ��ת����doubleֵ��
    * @param nH  ���ݿ��
    * @param nW  ���ݿ��
    * @param dVal ����ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool GetDoubleVal  ( const UINT nH, const UINT nW, double &dVal )const;
    /**
        * @fn SetDoubleVal
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �������ݿ������ص�ֵ����doubleֵת��Ϊ��Ӧ���͵�ֵ��
        * @param nH  ���ݿ��
        * @param nW  ���ݿ��
        * @param dVal ����ֵ
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
    bool SetDoubleVal ( const UINT nH, const UINT nW, double dVal );
    /**
        * @fn GetGeoXYZ
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �õ���������Ϣ�����ݿ��ڵ���ά����ֵ
        * @param nH  �к�
        * @param nW  �к�
        * @param ptXYZ ��ά����ֵ
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
    bool GetGeoXYZ  ( const UINT nH, const UINT nW, Pt3d& ptXYZ ) const;

    bool GetGeoXYZ  ( const UINT nH, const UINT nW, Pt2d ptOrig, const DOUBLE dXRes, const DOUBLE dYRes, const DOUBLE dNoVal, Pt3d& ptXYZ ) const;
    /**
        * @fn GetGeoZ
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �õ���������Ϣ�����ݿ��ڵ���ά�߳�ֵ
        * @param dX  �к�
        * @param dY  �к�
        * @param dZ ��ά�߳�ֵ
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
    bool GetGeoZ  ( const DOUBLE dX, const DOUBLE dY, DOUBLE &dZ ) const;

    bool GetGeoZ  ( const DOUBLE dX, const DOUBLE dY, Pt2d ptOrig, const DOUBLE dXRes, const DOUBLE dYRes, const DOUBLE dNoVal, DOUBLE &dZ ) const;

    bool FreeData();

    bool GetSubRasterBlock( UINT nX, UINT nY, UINT nXSize, UINT nYSize, CmlRasterBlock &clsSubBlocks );

    bool GetCentRasterBlock( CmlRasterBlock clsBlocks, UINT &nX, UINT &nY, CmlRasterBlock &clsSubBlock );
    CmlGdalDataset *m_pGdalData;//!<����ͷָ��
private:

    UINT m_nWidth;//!<���ݿ��
    UINT m_nHeight;//!<���ݿ��
    SINT m_nXOffSet;//!<���ݿ�Xƫ����
    SINT m_nYOffSet;//!<���ݿ�Yƫ����
    UINT m_nZoom;//!<���ݿ�����ϵ��
    UINT m_nBytes;//!<���ݿ������
    GDALDataType m_GDTType;//!<���ݿ�����

};

typedef struct stuGeoRasterBlock
{
    CmlRasterBlock* pImgBlockData;
    DOUBLE dXRes;
    DOUBLE dYRes;
    DOUBLE dNoVal;
    Pt2d ptOrig;
	stuGeoRasterBlock()
	{
		pImgBlockData = NULL;
		dXRes = dYRes = dNoVal = 0;
	}
}GeoRasBlock;
#endif // CMLRASTERBLOCK_H
