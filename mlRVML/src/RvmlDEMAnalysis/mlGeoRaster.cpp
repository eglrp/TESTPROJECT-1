/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlGeoRaster.cpp
* @date 2011.11.21
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����դ����ʵ��Դ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#include "mlGeoRaster.h"
/**
 *@fn CmlGeoRaster
 *@date 2011.11
 *@author ���Ļ�
 *@brief CmlGeoRaster�๹�캯��
 *@version 1.0
 *@par �޸���ʷ��
 <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
CmlGeoRaster::CmlGeoRaster()
{
    //ctor
    for( int i = 0; i < 6; ++i )
    {
        m_dGdalTransPara[i] = 0;
    }
    m_dXResolution = m_dYResolution = 1.0;
    m_PtOrigin.X = m_PtOrigin.Y = 0;
}
/**
 *@fn ��CmlGeoRaster
 *@date 2011.11
 *@author ���Ļ�
 *@brief CmlGeoRaster����������
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
CmlGeoRaster::~CmlGeoRaster()
{
    //dtor
}
/**
 *@fn ASCIIDemToGeoTiff
 *@date 2011.11
 *@author ���Ļ�
 *@brief ASCII��ʽDEMתΪGeoTiff
 *@param strPathASCII ASCII��ʽDEM·��
 *@param strOutPathGeoTiff ת����GeoTiff�ļ�·��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
bool CmlGeoRaster::ASCIIDemToGeoTiff( char* strPathASCII, char* strOutPathGeoTiff )
{
    fstream stm;
    stm.open( strPathASCII );
    if(!stm)
    {
        return false;
    }

    string sTemp;
    int nCol, nRow;
    double dResolution, dNoData, dLX, dLY;
    stm >> sTemp >> nCol >> sTemp >> nRow ;
    stm >> sTemp >> dLX >> sTemp >> dLY ;
    stm >> sTemp >> dResolution >> sTemp >> dNoData ;

    double* pdZVal = new double[nRow*nCol];

    for( int i = 0; i < nRow; ++i )
    {
        for( int j = 0; j < nCol; ++j )
        {
            double* pdZ = &pdZVal[i*nCol+j];
            double dZ;
            stm >> dZ;
            *pdZ = dZ;
        }
    }
    Pt2d ptLL;
    ptLL.X = dLX;
    ptLL.Y = dLY + dResolution*(nRow-1);

    CmlGeoRaster dem;

    dem.CreateGeoFile( strOutPathGeoTiff, ptLL, dResolution, -dResolution, nRow, nCol, 1, GDT_Float64, dNoData );
    dem.SaveToGeoFile( pdZVal );

    delete[] pdZVal;
    return true;

}
/**
 *@fn GeoTiffToASCIIDem
 *@date 2011.11
 *@author ���Ļ�
 *@brief GeoTiff��ʽDEMתΪASCII��ʽ
 *@param strOutPathGeoTiff GeoTiff�ļ�·��
 *@param strPathASCII ת����ASCII��ʽDEM·��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
bool CmlGeoRaster::GeoTiffToASCIIDem( char* strOutPathGeoTiff, char* strPathASCII )
{
    return true;
}
/**
 *@fn LoadGeoFile
 *@date 2011.11
 *@author ���Ļ�
 *@brief ��������������դ������
 *@param sPath �����ļ�·��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
bool CmlGeoRaster::LoadGeoFile( const SCHAR* sPath )
{
    if ( false == this->LoadFile( sPath ))
    {
        return false;
    }
    m_bIsGeoFile = true;
    GetGdalDataSet()->GetGeoTransform( m_dGdalTransPara );
    m_dXResolution = m_dGdalTransPara[1];
    m_dYResolution = m_dGdalTransPara[5];
    m_PtOrigin.X = m_dGdalTransPara[0];
    m_PtOrigin.Y = m_dGdalTransPara[3];

    return true;

}
/**
 *@fn CreateGeoFile
 *@date 2011.11
 *@author ���Ļ�
 *@brief ���������������դ������Ӳ���ļ�
 *@param sPath �����ļ�·��
 *@param ptLL ���Ͻ�����
 *@param dXResolution X����ֱ���
 *@param dYResolution Y����ֱ���
 *@param nH ����ͼ���
 *@param nW ����ͼ���
 *@param nBands ������
 *@param GDTType դ������
 *@param dNoData ��ֵ
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
 */
bool CmlGeoRaster::CreateGeoFile( const SCHAR* sPath, Pt2d ptLL, double dXResolution,double dYResolution, int nH, int nW, int nBands, GDALDataType GDTType, double dNoData )
{
    if( GetGdalDataSet() != NULL )
    {
        return false;
    }
    if( false == this->CreateFile( sPath, nW, nH, nBands, GDTType, "GTiff" ) )
    {
        return false;
    }
    if( GetGdalDataSet() == NULL )
    {
        return false;
    }
    m_dXResolution = dXResolution;
    m_dYResolution = dYResolution;
    m_PtOrigin = ptLL;

    m_dGdalTransPara[1] = m_dXResolution;
    m_dGdalTransPara[5] = m_dYResolution;
    m_dGdalTransPara[0] = m_PtOrigin.X;
    m_dGdalTransPara[3] = m_PtOrigin.Y;

    GetGdalDataSet()->SetGeoTransform( m_dGdalTransPara );
    SetNoDataVal(dNoData);
    return true;
}
/**
 *@fn
 *@date 2011.11
 *@author ���Ļ�
 *@brief �����������Gdal�ļ���
 *@param vecZVal ���Ͻǡ���˳��洢��Zֵ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
 */
bool CmlGeoRaster::SaveToGeoFile( vector<double> &vecZVal )
{
    //Ϊ���ɵ�ֱ������DEM��ע�⣬��д���Ӳ���ļ��ݶ�Ϊdouble��TIFF
    if( vecZVal.size() != (UINT) GetHeight()*GetWidth() )
    {
        return false;
    }
    CmlRasterBlock block;
    int nW = GetWidth();
    int nH = GetHeight();
    block.InitialImg( nH, nW, 8 );
    block.SetGDTType( GDT_Float64 );
    for( int i = 0; i < nH; ++i )
    {
        for( int j = 0; j < nW; ++j )
        {
            block.SetPtrAt( i, j, (BYTE*)(&vecZVal[i*nW+j]));
        }
    }

    this->SaveBlockToFile( 1, 0, 0, &block, 1 );
    return true;
}
/**
 *@fn
 *@date 2011.11
 *@author ���Ļ�
 *@brief �����������Gdal�ļ���
 *@param ���Ͻǡ���˳��洢��Zֵ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
 */
bool CmlGeoRaster::SaveToGeoFile( double* pZVal )
{
    //Ϊ���ɵ�ֱ������DEM��ע�⣬��д���Ӳ���ļ��ݶ�Ϊdouble��TIFF
    CmlRasterBlock block;
    int nW = GetWidth();
    int nH = GetHeight();
    block.InitialImg( nH, nW, 8 );
    block.SetGDTType( GDT_Float64 );
    for( int i = 0; i < nH; ++i )
    {
        for( int j = 0; j < nW; ++j )
        {
            block.SetPtrAt( i, j, (BYTE*)(pZVal+i*nW+j));
        }
    }

//    double dVal ;
//    for( int i = 0; i < nH; ++i )
//    {
//        for( int j = 0; j < nW; ++j )
//        {
//            block.GetDoubleVal( i, j , dVal);
//            cout << dVal << "   ";
//        }
//    }

    this->SaveBlockToFile( 1, 0, 0, &block, 1 );
    return true;
}
/**
 *@fn
 *@date 2011.11
 *@author ���Ļ�
 *@brief ��Block���ݴ���Gdal�ļ���.
 *@param nBand д�벨�κ�
 *@param nXOffSet д���ļ���ʼX����
 *@param nYOffSet д���ļ���ʵY����
 *@param pBlock д������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
 */
bool CmlGeoRaster::SaveToGeoFile(int nBand, int nXOffSet, int nYOffSet, CmlRasterBlock* pBlock )
{
    //ע�⣬Block����Ӧ��ͬӲ���ļ�������ͬ����������
    this->SaveBlockToFile( nBand, nXOffSet, nYOffSet, pBlock, 1 );
    return true;
}


