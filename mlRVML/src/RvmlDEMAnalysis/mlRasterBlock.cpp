/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlRasterBlock.cpp
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief դ�����ݿ鴦��Դ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#include "mlBase.h"
#include "mlGdalDataset.h"
#include "mlRasterBlock.h"
#include "mlGeoRaster.h"
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
CmlRasterBlock::CmlRasterBlock()
{
    m_pGdalData = NULL;
    m_nXOffSet = m_nYOffSet = m_nZoom = m_nBytes = m_nHeight = m_nWidth = 0;

}
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

CmlRasterBlock::CmlRasterBlock( SINT nXOffSet, SINT nYOffSet, UINT nW, UINT nH, UINT nBytes, UINT nZoom )
{
    m_pGdalData = NULL;

    this->InitialImg( nH, nW, nBytes );
    m_nXOffSet = nXOffSet;
    m_nYOffSet = nYOffSet;
    m_nZoom = nZoom;
    m_nBytes = nBytes;
}
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
CmlRasterBlock::~CmlRasterBlock()
{
    m_nXOffSet = 0;
    m_nYOffSet = 0;
}
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
bool CmlRasterBlock::InitialImg( UINT nH, UINT nW, UINT nBytes )
{
    if ( true == this->Initial( nH, nW*nBytes ) )
    {
        m_nBytes = nBytes;
        m_nHeight = nH;
        m_nWidth = nW;
        return true;
    }
    else
    {
        return false;
    }
}
/**
* @fn ReSet
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ������ݣ���ɾ���ڴ�
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlRasterBlock::ReSet()
{
    memset( m_pData, m_nTSize, 0 );

    return true;
}
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
bool CmlRasterBlock::Clear()
{
    this->DestoryAll();
    m_nXOffSet = 0;
    m_nYOffSet = 0;
    m_nZoom = 1;

    return true;
}

bool CmlRasterBlock::SetXOffSet( SINT nXOffSet )
{
    m_nXOffSet = nXOffSet;
    return true;
}
bool CmlRasterBlock::SetYOffSet( SINT nYOffSet )
{
    m_nYOffSet = nYOffSet;
    return true;
}
bool CmlRasterBlock::SetZoom( UINT nZoom )
{
    m_nZoom = nZoom;
    return true;
}
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
BYTE* CmlRasterBlock::GetPtrAt( const UINT nH, const UINT nW ) const
{
    if( ( nH >= m_nHeight )||( nW >= m_nWidth )||( this->IsValid() == false ) )
    {
        return NULL;
    }

    return ( m_pData + ( m_nWidth * nH + nW )* m_nBytes );
}
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
bool CmlRasterBlock::SetPtrAt( const UINT nH, const UINT nW, BYTE* pVal )
{
    BYTE* pDes = GetPtrAt( nH, nW );
    if( pDes != NULL )
    {
        memcpy( pDes, pVal, m_nBytes );
    }
    else
    {
        return false;
    }
    return true;
}
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
BYTE CmlRasterBlock::GetAt( const UINT nRow, const UINT nCol )
{
    assert( ( nRow < m_nHeight)&&( nCol < m_nWidth) );
    return m_pData[m_nBytes*( nRow * m_nWidth + nCol )];
}
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
bool CmlRasterBlock::SetAt( const UINT nRow, const UINT nCol, BYTE val )  //����դ���ĳ�����������һ���ֽ�ֵ����blockΪ���ֽ����ͣ���Ϊ��������ֵ
{
    if( (nRow >= m_nHeight) || ( nCol >= m_nWidth ) )
    {
        return false;
    }

    BYTE* pTmp = m_pData + m_nBytes*( nRow * m_nWidth + nCol);
    *pTmp = val;
    return true;
}
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

bool CmlRasterBlock::GetDoubleVal( const UINT nH, const UINT nW, double &dVal ) const
{
    if( ( nH >= m_nHeight ) ||( nW >= m_nWidth ) )
    {
        return false;
    }
    BYTE* pVal = this->GetPtrAt( nH, nW );

    switch( m_GDTType )
    {
    case GDT_Byte:
        dVal = ( (double)(*pVal) );
        break;
    case GDT_Int16:
        dVal = ((double)(*((SSHORT*)pVal)));
        break;
    case GDT_UInt16:
        dVal = ((double)(*((USHORT*)pVal)));
        break;
    case GDT_Int32:
        dVal = ((double)(*((SINT*)pVal)));
        break;
    case GDT_UInt32:
        dVal = ((double)(*((UINT*)pVal)));
        break;
    case GDT_Float32:
        dVal = ((double)(*((FLOAT*)pVal)));
        break;
    case GDT_Float64:
        dVal = ((double)(*((DOUBLE*)pVal)));
        break;
    default:
        return false;
        break;
    }

    return true;
}
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
bool CmlRasterBlock::SetDoubleVal( const UINT nH, const UINT nW, double dVal )
{
    if( ( nH >= m_nHeight ) ||( nW >= m_nWidth ) )
    {
        return false;
    }
    BYTE* pVal = this->GetPtrAt( nH, nW );

    BYTE bTempValByte;
    SSHORT nTempValSShort;
    USHORT nTempValUShort;
    SINT nTempValSInt;
    UINT nTempValUInt;
    FLOAT dTempValFloat;

    switch( m_GDTType )
    {
        case GDT_Byte:
            bTempValByte = (BYTE)(dVal);
            memcpy( pVal, &bTempValByte, sizeof(BYTE) );
            break;
        case GDT_Int16:
            nTempValSShort = (SSHORT)(dVal);
            memcpy( pVal, &nTempValSShort, sizeof(SSHORT) );
            break;
        case GDT_UInt16:
            nTempValUShort = (USHORT)(dVal);
            memcpy( pVal, &nTempValUShort, sizeof(USHORT) );
            break;
        case GDT_Int32:
            nTempValSInt = (SINT)(dVal);
            memcpy( pVal, &nTempValSInt, sizeof(SINT) );
            break;
        case GDT_UInt32:
            nTempValUInt = (UINT)(dVal);
            memcpy( pVal, &nTempValUInt, sizeof(UINT) );
            break;
        case GDT_Float32:
            dTempValFloat = (FLOAT)(dVal);
            memcpy( pVal, &dTempValFloat, sizeof(FLOAT) );
            break;
        case GDT_Float64:
            memcpy( pVal, &dVal, sizeof(DOUBLE) );
        default:
            break;
    }
    return true;
}
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
bool CmlRasterBlock::GetGeoXYZ( const UINT nH, const UINT nW, Pt3d& ptXYZ ) const
{
    if( ( m_pGdalData == NULL )||( m_pGdalData->m_bIsGeoFile != true) )
    {
        return false;
    }
    CmlGeoRaster* pGeoRaster = (CmlGeoRaster*)m_pGdalData;
    ptXYZ.X = (m_nXOffSet + nW)*pGeoRaster->m_dXResolution + pGeoRaster->m_PtOrigin.X ;
    ptXYZ.Y = (m_nYOffSet + nH)*pGeoRaster->m_dYResolution + pGeoRaster->m_PtOrigin.Y ;
    if ( ( true == GetDoubleVal( nH, nW, ptXYZ.Z ) )&&( fabs( ptXYZ.Z - pGeoRaster->GetNoDataVal()) > ML_ZERO ) )
    {
        return true;
    }
    else
    {
        return false;
    }

}
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
bool CmlRasterBlock::GetGeoZ( const DOUBLE dX, const DOUBLE dY, DOUBLE &dZ ) const
{
    if( ( m_pGdalData == NULL )||( m_pGdalData->m_bIsGeoFile != true) )
    {
        return false;
    }
    CmlGeoRaster* pGeoRaster = (CmlGeoRaster*)m_pGdalData;

    double dXCoord = ( dX - pGeoRaster->m_PtOrigin.X ) / pGeoRaster->m_dXResolution ;
    double dYCoord = ( dY - pGeoRaster->m_PtOrigin.Y ) / pGeoRaster->m_dYResolution ;

    if( ( dXCoord < 0 ) || ( dXCoord > ( m_nW - 1) ) || ( dYCoord < 0 ) || ( dYCoord > ( m_nH - 1) ) )
    {
        return false;
    }
    Pt2i ptLT, ptRT, ptLB, ptRB;
    ptLT.X = SINT( dXCoord );
    ptLT.Y = SINT( dYCoord );
    ptRT.X = ptLT.X + 1;
    ptRT.Y = ptLT.Y;
    ptLB.X = ptLT.X;
    ptLB.Y = ptLT.Y + 1;
    ptRB.X = ptRT.X;
    ptRB.Y = ptLB.Y;

    Pt3d ptZLT, ptZRT, ptZLB, ptZRB;
    if( GetGeoXYZ( ptLT.Y, ptLT.X, ptZLT ) &&  GetGeoXYZ( ptRT.Y, ptRT.X, ptZRT ) &&  GetGeoXYZ( ptLB.Y, ptLB.X, ptZLB ) &&  GetGeoXYZ( ptRB.Y, ptRB.X, ptZRB )  )
    {
        dZ = ( ptRB.X - dXCoord )*( ptRB.Y - dYCoord )* ptZLT.Z +
             ( dXCoord - ptLT.X )*( ptRB.Y - dYCoord )* ptZRT.Z +
             ( ptRB.X - dXCoord )*( dYCoord - ptLT.Y )* ptZLB.Z +
             ( dXCoord - ptLT.X )*( dYCoord - ptLT.Y )* ptZRB.Z ;

        return true;
    }
    else
    {
        return false;
    }

}
