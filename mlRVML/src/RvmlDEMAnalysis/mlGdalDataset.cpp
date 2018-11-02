/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlGdalDataset.cpp
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief GDALͼ���������Դ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#include "mlGdalDataset.h"

/**
* @fn CmlGdalDataset
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief CmlGdalDataset��ղι��캯��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlGdalDataset::CmlGdalDataset()
{
    m_nBands =0;
    m_nBytes  =0;
    m_nWidth =0;
    m_nHeight =0;

    m_pDataset =  NULL;
    m_ppBands = NULL;

    m_minSampleValues = NULL;
    m_maxSampleValues = NULL;
    m_max_mins = NULL;

    m_bIsGeoFile = false;

}
/**
* @fn ~CmlGdalDataset
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief CmlGdalDataset����������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlGdalDataset::~CmlGdalDataset()
{
    if( m_pDataset )
        delete m_pDataset;

    if( m_ppBands )
        delete[] m_ppBands;

    if( m_minSampleValues )
        delete[] m_minSampleValues;

    if( m_maxSampleValues )
        delete[] m_maxSampleValues;

    if( m_max_mins )
        delete[] m_max_mins;
}
/**
* @fn LoadFile
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����դ���ļ�ͷ��Ϣ
* @param FileName �ļ�·��
* @param nType �ļ�����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlGdalDataset::LoadFile( const SCHAR *FileName, const SINT nType)
{
    if( m_pDataset != NULL )
    {
        return false;
    }

    SCHAR msg[256];

    //��Ӱ���ļ������������ļ����ڴ�֮��Ĺ�ϵ
    GDALAllRegister();
    m_pDataset = (GDALDataset *)GDALOpen( FileName, GA_Update );

    if( m_pDataset == NULL )
    {
        sprintf( msg, "GDALOpen failed - %d\n%s\n", CPLGetLastErrorNo(), CPLGetLastErrorMsg() );

        return FALSE;
    }

    // read general info.
    GDALDriverH hDriver = GDALGetDatasetDriver( m_pDataset );
    sprintf(msg, "Driver: %s/%s\n", GDALGetDriverShortName( hDriver ), GDALGetDriverLongName( hDriver ) );
    //ȡӰ����
    m_nWidth = m_cacheInfo.imgWid = m_pDataset->GetRasterXSize();
    m_nHeight = m_cacheInfo.imgHei = m_pDataset->GetRasterYSize();
    //������

    if(m_nWidth < 1 || m_nHeight < 1) return FALSE;

    //ȷ��Ӱ���ļ��м���ͨ��
    m_cacheInfo.samplesPerPixel = GDALGetRasterCount( m_pDataset );
    m_nBands=m_cacheInfo.samplesPerPixel;

//	//�޶���ദ����������RGBӰ������ң��Ӱ��ͨ��ת���������˳���
//	if(m_cacheInfo.samplesPerPixel > 3 ) m_cacheInfo.samplesPerPixel = 3;

    ///////////////////////////////////////////
    m_minSampleValues = new USHORT[m_cacheInfo.samplesPerPixel];
    m_maxSampleValues = new USHORT[m_cacheInfo.samplesPerPixel];
    m_max_mins = new USHORT[m_cacheInfo.samplesPerPixel];

    ///////////////////////////////////////////
    //Ϊÿ��ͨ������һ����������ָ�룬������˳�����ΪBMPϰ�ߵ� RGB ˳��
    m_ppBands = new GDALRasterBand*[ m_cacheInfo.samplesPerPixel ] ;
    SINT band;
    for( band=0; band < m_cacheInfo.samplesPerPixel; band++)
    {

        //��������˳��       m_ppBands[band] = m_pDataset->GetRasterBand( m_cacheInfo.samplesPerPixel - band );
        m_ppBands[band] = m_pDataset->GetRasterBand( band+1 );
        m_colorInterp = GDALGetRasterColorInterpretation( m_ppBands[band] );
    }

    //ȷ��Tile��
    m_ppBands[0]->GetBlockSize( &m_cacheInfo.tile_wid, &m_cacheInfo.tile_hei );
    m_tile_wid = m_cacheInfo.tile_wid;
    m_tile_hei = m_cacheInfo.tile_hei;
    m_isTiled = ( m_cacheInfo.tile_wid < m_cacheInfo.imgWid );

    //ȷ��ÿ�����ֽ���
    m_dataType = GDALGetRasterDataType( m_ppBands[0] );

    m_bitsPerSample = 0;
    switch( m_dataType )
    {
    case GDT_Byte:
        m_bitsPerSample = 1; //8bits
        break;
    case GDT_UInt16:
    case GDT_Int16:
        m_bitsPerSample = 2; //16bits
        break;
    case GDT_UInt32:
    case GDT_Int32:
    case GDT_Float32:
        m_bitsPerSample = 4; //32bits
        break;
    case GDT_Float64:
        m_bitsPerSample = 8;
        break;
    default:
        break;
    }
    if(!m_bitsPerSample) return FALSE;

    m_nBytes = m_bitsPerSample;
    //��ʼ��ÿ�������ص���С���ֵ
    m_cacheInfo.bytesPerPixel = m_cacheInfo.samplesPerPixel;
    DOUBLE adfCMinMax[2];
    GDALComputeRasterMinMax( m_ppBands[0], TRUE, adfCMinMax );

    for( band=0; band < m_cacheInfo.samplesPerPixel; band++)
    {
        m_minSampleValues[band] = adfCMinMax[0];
        m_maxSampleValues[band] = adfCMinMax[1];
        m_max_mins[band] = adfCMinMax[1] - adfCMinMax[0];
    }

    SINT bGotNodata;
    m_dNoDataValue = GDALGetRasterNoDataValue( m_ppBands[0], &bGotNodata );
    return true;
}
/**
* @fn CreateFile
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ڴ����д���դ���ļ�
* @param FileName �ļ�����
* @param nW դ��Ӱ���
* @param nH դ��Ӱ���
* @param nBands դ��Ӱ�񲨶���
* @param GDTType դ��Ӱ����������
* @param BitsOut ����ͼ������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlGdalDataset::CreateFile( const SCHAR *FileName, const UINT nW, const UINT nH, const UINT nBands, const GDALDataType GDTType,const SCHAR *BitsOut)
{
    if( m_pDataset != NULL )
    {
        return false;
    }

    GDALAllRegister();
    GDALDriver *poDriver;
    poDriver = GetGDALDriverManager()->GetDriverByName(BitsOut);
    if( poDriver == NULL )
    {
        return false;
    }
    m_ppBands = new GDALRasterBand*[nBands];

    //SCHAR* Options=NULL;

    GDALDataType NBY = GDTType;
    SINT nBytes = 0;
    switch( NBY )
    {
    case GDT_Byte:
        nBytes = 1;
        break;
    case GDT_UInt16:
        nBytes = 2;
        break;
    case GDT_Int16:
        nBytes = 2;
        break;
    case GDT_UInt32:
        nBytes = 4;
        break;
    case GDT_Int32:
        nBytes = 4;
        break;
    case GDT_Float32:
        nBytes = 4;
        break;
    case GDT_Float64:
        nBytes = 8;
        break;
    default:
        NBY = GDT_Byte;
        break;
        break;
    }

    m_pDataset = poDriver->Create(FileName,nW,nH,nBands,NBY,/*&Options8*/NULL);
    if( m_pDataset == NULL )
    {
        return false;
    }

    m_dataType = GDTType;
    ////////////////////////////////////////////////////////////////////

    // read general info.
    GDALDriverH hDriver = GDALGetDatasetDriver( m_pDataset );
    SCHAR msg[128];
    sprintf(msg, "Driver: %s/%s\n", GDALGetDriverShortName( hDriver ), GDALGetDriverLongName( hDriver ) );

    m_nWidth = m_cacheInfo.imgWid = m_pDataset->GetRasterXSize();
    m_nHeight = m_cacheInfo.imgHei = m_pDataset->GetRasterYSize();
    m_nBands = nBands;
    if( (m_nWidth < 1 ) || ( m_nHeight < 1 ) ) return FALSE;

    m_cacheInfo.samplesPerPixel = GDALGetRasterCount( m_pDataset );

    ///////////////////////////////////////////
    m_minSampleValues = new USHORT[m_cacheInfo.samplesPerPixel];
    m_maxSampleValues = new USHORT[m_cacheInfo.samplesPerPixel];
    m_max_mins = new USHORT[m_cacheInfo.samplesPerPixel];

    ///////////////////////////////////////////
    SINT band;
    for( band=0; band < m_cacheInfo.samplesPerPixel; band++)
    {
        m_ppBands[band] = m_pDataset->GetRasterBand( band+1 );
    }
    //m_ppBands[0]->SetColorInterpretation(GCI_BlueBand);
    //m_ppBands[1]->SetColorInterpretation(GCI_GreenBand);
    //m_ppBands[2]->SetColorInterpretation(GCI_RedBand);

    m_ppBands[0]->GetBlockSize( &m_cacheInfo.tile_wid, &m_cacheInfo.tile_hei );
//	m_tileSize.cx = m_cacheInfo.tile_wid;
//	m_tileSize.cy = m_cacheInfo.tile_hei;
    m_isTiled = ( m_cacheInfo.tile_wid < m_cacheInfo.imgWid );

    GDALColorInterp colorInterp;
    colorInterp = GDALGetRasterColorInterpretation( m_ppBands[0] );
    GDALDataType	dataType = GDALGetRasterDataType( m_ppBands[0] );

    m_bitsPerSample = 0;
    switch( dataType )
    {
    case GDT_Byte:
        m_bitsPerSample = 1; //8bits
        break;
    case GDT_UInt16:
    case GDT_Int16:
        m_bitsPerSample = 2; //16bits
        break;
    case GDT_UInt32:
    case GDT_Int32:
    case GDT_Float32:
        m_bitsPerSample = 4; //32bits
        break;
    case GDT_Float64:
        m_bitsPerSample = 8; //32bits
        break;
    case GDT_Unknown:
        break;
    case GDT_CInt16:
        break;
    case GDT_CInt32:
        break;
    case GDT_CFloat32:
        break;
    case GDT_CFloat64:
        break;
    case GDT_TypeCount:
        break;
    }
    if(!m_bitsPerSample) return FALSE;

    m_cacheInfo.bytesPerPixel = m_cacheInfo.samplesPerPixel;
    DOUBLE adfCMinMax[2];
    GDALComputeRasterMinMax( m_ppBands[0], TRUE, adfCMinMax );

    for( band=0; band < m_cacheInfo.samplesPerPixel; band++)
    {
        m_minSampleValues[band] = adfCMinMax[0];
        m_maxSampleValues[band] = adfCMinMax[1];
        m_max_mins[band] = adfCMinMax[1] - adfCMinMax[0];
    }

    SINT bGotNodata;
    m_dNoDataValue = GDALGetRasterNoDataValue( m_ppBands[0], &bGotNodata );

    return true;
}
/**
* @fn SaveBlockToFile
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��block���ݴ����Ӧ�Ĵ����ļ�
* @param nBand դ��Ӱ�񲨶κ�
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
bool CmlGdalDataset::SaveBlockToFile( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, CmlRasterBlock* pImgBlock, const UINT nBlockBand )
{
    if( m_nBands == 0 )
    {
        return false;
    }
    if( (nBand > m_nBands)||(nBand == 0 ) )
    {
        return false;
    }
    if( pImgBlock->GetGDTType() != m_dataType )
    {
        return false;
    }
    CPLErr cplError = m_ppBands[nBand-1]->RasterIO( GF_Write, nXOffSet, nYOffSet, pImgBlock->GetW(), pImgBlock->GetH(), \
                      pImgBlock->GetData(), pImgBlock->GetW(), pImgBlock->GetH(), \
                      pImgBlock->GetGDTType(), m_bitsPerSample, pImgBlock->GetW()*m_bitsPerSample);

    if( cplError == CE_None )
    {
        return true;
    }
    else
    {
        return false;
    }
}
/**
* @fn SaveBlockToFile
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��block���ݴ����Ӧ�Ĵ����ļ�
* @param nBand դ��Ӱ�񲨶κ�
* @param nXOffSet դ��Ӱ��X����ƫ����
* @param nYOffSet դ��Ӱ��Y����ƫ����
* @param pImgBlock դ��Ӱ���
* @param nBlockXOffSet ���洢���ݿ���block��X����ƫ����
* @param nBlockYOffSet ���洢���ݿ���block��Y����ƫ����
* @param nW ���洢���ݿ��
* @param nH ���洢���ݿ��
* @param nBlockBand Ŀ���ļ����κ�
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlGdalDataset::SaveBlockToFile( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, CmlRasterBlock* pImgBlock, const UINT nBlockXOffSet, \
                                      const UINT nBlockYOffSet, const UINT nW, const UINT nH, const UINT nBlockBand)
{
    if( m_nBands == 0 )
    {
        return false;
    }
    if( (nBand > m_nBands)||(nBand == 0 ) )
    {
        return false;
    }
    if( pImgBlock->IsValid() == false )
    {
        return false;
    }
    if( pImgBlock->GetGDTType() != m_dataType )
    {
        return false;
    }
    if( ( ( nBlockXOffSet + nW ) > pImgBlock->GetW() )||( ( nBlockYOffSet + nH ) > pImgBlock->GetH() ) )
    {
        return false;
    }

    CmlRasterBlock subBlock;
    if( false == subBlock.InitialImg( nH, nW, pImgBlock->GetBytes() ) )
    {
        return false;
    }
    for( SINT i = 0; i < nH; ++i )
    {
        for( SINT j = 0; j < nW; ++j )
        {
            BYTE* pSrc = pImgBlock->GetPtrAt( i+nBlockYOffSet, j+nBlockXOffSet );
            BYTE* pDes = subBlock.GetPtrAt( i, j );
            memcpy( pDes, pSrc, m_bitsPerSample );
        }
    }

    CPLErr cplError = m_ppBands[nBand-1]->RasterIO( GF_Write, nXOffSet+nBlockXOffSet, nYOffSet+nBlockYOffSet, subBlock.GetW(), subBlock.GetH(), \
                      subBlock.GetData(), subBlock.GetW(), subBlock.GetH(), \
                      pImgBlock->GetGDTType(), m_bitsPerSample, subBlock.GetW()*m_bitsPerSample);

    if( cplError == CE_None )
    {
        return true;
    }
    else
    {
        return false;
    }
}
/**
* @fn etRasterGrayBlock
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��GdalDataSet�еõ�ĳ������ĳ��λ��������ǿ��GDT_BYTE���͵�Ӱ���
* @param nBand Ӱ�񲨶κ�(��1��ʼ)
* @param nXOffSet Ӱ���X�������
* @param nYOffSet Ӱ���Y�������
* @param nW Ӱ����
* @param nH Ӱ����
* @param nZoom Ӱ�������ϵ��
* @param pImgBlock դ��Ӱ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlGdalDataset::GetRasterGrayBlock( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const UINT nZoom,CmlRasterBlock* pImgBlock )
{
    if (nZoom < 1 )
    {
        return false;
    }
    SINT nHBufSize = nZoom * nH;
    SINT nWBufSize = nZoom * nW;
    if( (nBand > m_nBands)||(nBand == 0 ) )
    {
        return false;
    }
    if( (( nXOffSet + nW ) > m_nWidth ) ||(( nYOffSet + nH ) > m_nHeight ) )
    {
        return false;
    }

    if( false == pImgBlock->InitialImg( nHBufSize, nWBufSize ) )
    {
        return false;
    }

    CPLErr cplError = m_ppBands[nBand-1]->RasterIO( GF_Read, nXOffSet, nYOffSet, nW, nH, pImgBlock->GetData(), nWBufSize, nHBufSize,  GDT_Byte, 1, nWBufSize );
    if(  cplError != CE_None )
    {
        return false;
    }

    pImgBlock->m_pGdalData = this;
    pImgBlock->SetXOffSet( nXOffSet );
    pImgBlock->SetYOffSet( nYOffSet );
    pImgBlock->SetZoom( nZoom );
    pImgBlock->SetGDTType( GDT_Byte );

    return true;
}
/**
* @fn GetRasterGrayBlock
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��GdalDataSet�еõ�ĳ������ĳ��λ��������ǿ��GDT_BYTE���͵�Ӱ���
* @param nBand Ӱ�񲨶κ�(��1��ʼ)
* @param nXOffSet Ӱ���X�������
* @param nYOffSet Ӱ���Y�������
* @param nW Ӱ����
* @param nH Ӱ����
* @param nZoom Ӱ�������ϵ��
* @param pImgBlock դ��Ӱ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlGdalDataset::GetRasterGrayBlock( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const DOUBLE dZoom,CmlRasterBlock* pImgBlock )
{
    if (dZoom < 0 )
    {
        return false;
    }
    SINT nHBufSize = SINT(dZoom * nH);
    SINT nWBufSize = SINT(dZoom * nW);

    if( (nBand > m_nBands)||(nBand == 0 ) )
    {
        return false;
    }

    if( (( nXOffSet + nW ) > m_nWidth ) ||(( nYOffSet + nH ) > m_nHeight ) )
    {
        return false;
    }

    if( false == pImgBlock->InitialImg( nHBufSize, nWBufSize ) )
    {
        if( ( pImgBlock->GetH() != nHBufSize )||( pImgBlock->GetW() != nWBufSize ) ||( pImgBlock->GetBytes() != 1 ))
        {
            return false;
        }
    }

    CPLErr cplError = m_ppBands[nBand-1]->RasterIO( GF_Read, nXOffSet, nYOffSet, nW, nH, pImgBlock->GetData(), nWBufSize, nHBufSize,  GDT_Byte, 1, nWBufSize );

    if( cplError != CE_None )
    {
        return false;
    }
    pImgBlock->m_pGdalData = this;
    pImgBlock->SetXOffSet( nXOffSet );
    pImgBlock->SetYOffSet( nYOffSet );
    pImgBlock->SetGDTType( GDT_Byte );

    return true;
}
/**
* @fn GetRasterGrayBlock
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��GdalDataSet�еõ�ĳ�������Σ�ǿ��GDT_BYTE�������䵱��R��G��B���κ�ϳ�block��block����ǿ��ΪGDT_BYTE��1����
* @param nBandR Ӱ���R������ȡӰ�񲨶κ�
* @param nBandG Ӱ���G������ȡӰ�񲨶κ�
* @param nBandB Ӱ���B������ȡӰ�񲨶κ�
* @param nXOffSet Ӱ���X�������
* @param nYOffSet Ӱ���Y�������
* @param nW Ӱ����
* @param nH Ӱ����
* @param nZoom Ӱ�������ϵ��
* @param pImgBlock դ��Ӱ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlGdalDataset::GetRasterGrayBlock( const UINT nBandR, const UINT nBandG, const UINT nBandB, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const UINT nZoom,CmlRasterBlock* pImgBlock )
{
    if (nZoom < 1 )
    {
        return false;
    }
    SINT nHBufSize = nZoom * nH;
    SINT nWBufSize = nZoom * nW;

    if( ( nBandR > m_nBands )||( nBandG > m_nBands )||( nBandB > m_nBands ) )
    {
        return false;
    }

    if( (( nXOffSet + nW ) > m_nWidth ) ||(( nYOffSet + nH ) > m_nHeight ) )
    {
        return false;
    }

    if( false == pImgBlock->InitialImg( nHBufSize, nWBufSize ) )
    {
        if( ( pImgBlock->GetH() != nHBufSize )||( pImgBlock->GetW() != nWBufSize ) ||( pImgBlock->GetBytes() != 1 ))
        {
            return false;
        }
    }

    BYTE* pBufR = new BYTE[nHBufSize*nWBufSize];
    BYTE* pBufG = new BYTE[nHBufSize*nWBufSize];
    BYTE* pBufB = new BYTE[nHBufSize*nWBufSize];

    CPLErr cplE1 = m_ppBands[nBandR-1]->RasterIO( GF_Read, nXOffSet, nYOffSet, nW, nH, pBufR, nWBufSize, nHBufSize,  GDT_Byte, 1, nWBufSize );
    if( cplE1 != CE_None )
    {
        delete[] pBufR;
        delete[] pBufG;
        delete[] pBufB;
        return false;
    }

    CPLErr cplE2 = m_ppBands[nBandG-1]->RasterIO( GF_Read, nXOffSet, nYOffSet, nW, nH, pBufG, nWBufSize, nHBufSize,  GDT_Byte, 1, nWBufSize );
    if( cplE2 != CE_None )
    {
        delete[] pBufR;
        delete[] pBufG;
        delete[] pBufB;
        return false;
    }

    CPLErr cplE3 = m_ppBands[nBandB-1]->RasterIO( GF_Read, nXOffSet, nYOffSet, nW, nH, pBufB, nWBufSize, nHBufSize,  GDT_Byte, 1, nWBufSize );
    if( cplE3 != CE_None )
    {
        delete[] pBufR;
        delete[] pBufG;
        delete[] pBufB;
        return false;
    }

    for( SINT i = 0; i < pImgBlock->GetTPixelSize(); ++i )
    {
        *(pImgBlock->GetData() + i) = RGB2GRAY( pBufR[i], pBufG[i], pBufB[i] );
    }
    pImgBlock->m_pGdalData = this;
    pImgBlock->SetXOffSet( nXOffSet );
    pImgBlock->SetYOffSet( nYOffSet );
    pImgBlock->SetZoom( nZoom );
    pImgBlock->SetGDTType( GDT_Byte );

    delete[] pBufR;
    delete[] pBufG;
    delete[] pBufB;

    return true;
}
/**
* @fn GetRasterRGBBlock
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��GdalDataSet�еõ�ĳ��������
* @param nBandR Ӱ���R������ȡӰ�񲨶κ�
* @param nBandG Ӱ���G������ȡӰ�񲨶κ�
* @param nBandB Ӱ���B������ȡӰ�񲨶κ�
* @param nXOffSet Ӱ���X�������
* @param nYOffSet Ӱ���Y�������
* @param nW Ӱ����
* @param nH Ӱ����
* @param nZoom Ӱ�������ϵ��
* @param pImgBlock դ��Ӱ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlGdalDataset::GetRasterRGBBlock( const UINT nBandR, const UINT nBandG, const UINT nBandB, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const UINT nZoom,CmlRasterBlock* pImgBlock )
{
    return true;
}
/**
* @fn GetRasterOriginBlock
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��GdalDataSet�еõ�ĳ�����Σ�����ԭʼ���ݵ���block�У�block����ͬDataSet��ͬ
* @param nBand Ӱ�񲨶κ�(��1��ʼ)
* @param nXOffSet Ӱ���X�������
* @param nYOffSet Ӱ���Y�������
* @param nW Ӱ����
* @param nH Ӱ����
* @param nZoom Ӱ���SINT������ϵ��
* @param pImgBlock դ��Ӱ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlGdalDataset::GetRasterOriginBlock( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const UINT nZoom,CmlRasterBlock* pImgBlock )
{
    if (nZoom < 1 )
    {
        return false;
    }
    SINT nHBufSize = nZoom * nH;
    SINT nWBufSize = nZoom * nW;

    if( (nBand > m_nBands)||(nBand == 0 ) )
    {
        return false;
    }

    if( (( nXOffSet + nW ) > m_nWidth ) ||(( nYOffSet + nH ) > m_nHeight ) )
    {
        return false;
    }

    if( false == pImgBlock->InitialImg( nHBufSize, nWBufSize, m_bitsPerSample ) )
    {
        if( ( pImgBlock->GetH() != nHBufSize )||( pImgBlock->GetW() != nWBufSize )||( pImgBlock->GetBytes() != m_bitsPerSample ) )
        {
            return false;
        }
    }
    m_ppBands[nBand-1]->RasterIO( GF_Read, nXOffSet, nYOffSet, nW, nH, pImgBlock->GetData(), nWBufSize, nHBufSize,  m_dataType, m_bitsPerSample, nWBufSize*m_bitsPerSample );

    pImgBlock->m_pGdalData = this;
    pImgBlock->SetXOffSet( nXOffSet );
    pImgBlock->SetYOffSet( nYOffSet );
    pImgBlock->SetZoom( nZoom );
    pImgBlock->SetGDTType( m_dataType );

    return true;
}
/**
* @fn GetRasterOriginBlock
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��GdalDataSet�еõ�ĳ�����Σ�����ԭʼ���ݵ���block�У�block����ͬDataSet��ͬ
* @param nBand Ӱ�񲨶κ�(��1��ʼ)
* @param nXOffSet Ӱ���X�������
* @param nYOffSet Ӱ���Y�������
* @param nW Ӱ����
* @param nH Ӱ����
* @param dZoom Ӱ���DOUBLE������ϵ��
* @param pImgBlock դ��Ӱ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlGdalDataset::GetRasterOriginBlock( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const DOUBLE dZoom,CmlRasterBlock* pImgBlock )
{
    UINT nHBufSize = UINT(dZoom * nH);
    UINT nWBufSize = UINT(dZoom * nW);

    if( (nBand > m_nBands)||(nBand == 0 ) )
    {
        return false;
    }

    if( (( nXOffSet + nW ) > m_nWidth ) ||(( nYOffSet + nH ) > m_nHeight ) )
    {
        return false;
    }

    if( false == pImgBlock->InitialImg( nHBufSize, nWBufSize, m_bitsPerSample ) )
    {
        if( ( pImgBlock->GetH() != nHBufSize )||( pImgBlock->GetW() != nWBufSize )||( pImgBlock->GetBytes() != m_bitsPerSample ) )
        {
            return false;
        }
    }
    m_ppBands[nBand-1]->RasterIO( GF_Read, nXOffSet, nYOffSet, nW, nH, pImgBlock->GetData(), nWBufSize, nHBufSize,  m_dataType, m_bitsPerSample, nWBufSize*m_bitsPerSample );

    pImgBlock->m_pGdalData = this;
    pImgBlock->SetXOffSet( nXOffSet );
    pImgBlock->SetYOffSet( nYOffSet );
    pImgBlock->SetGDTType( m_dataType );

    return true;
}
/**
* @fn SetNoDataVal
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����DataSet�п�ֵ�Ĵ���ֵ
* @param dNoData �����趨��ֵ����ֵ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlGdalDataset::SetNoDataVal( DOUBLE dNoData )
{
    for( SINT i = 0; i < m_nBands; ++i )
    {
        GDALSetRasterNoDataValue( m_ppBands[i], dNoData );
    }
    m_dNoDataValue = dNoData;
    return true;
}


