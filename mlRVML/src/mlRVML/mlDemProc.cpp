/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlDemProc.cpp
* @date 2011.12.18
* @author �⿭  wukai@irsa.ac.cn
* @brief  ��վ����dem���ɹ���ģ����Դ�ļ�(�������ӽ��µ�������)
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#include "mlDemProc.h"
#include <fstream>
/**
 *@fn CmlDemProc()
 *@date 2011.11
 *@author �⿭
 *@brief DEM�����๹�캯��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
 */
CmlDemProc::CmlDemProc()
{
    // ������ʼ��
    m_lPtsNum = 0 ;
    m_nBlockNum = 0 ;
    m_dScale = 5000.0 ;
    m_pTin = NULL ;
    m_dbRectXY.left = MAX_DEM ;
    m_dbRectXY.right = MIN_DEM ;
    m_dbRectXY.bottom = MAX_DEM ;
    m_dbRectXY.top = MIN_DEM  ;
    m_dbRectZ.bottom = MAX_DEM ;
    m_dbRectZ.top = MIN_DEM ;
    m_dbDemRect.left = MIN_DEM ;
    m_dbDemRect.right = MAX_DEM ;
    m_dbDemRect.bottom = MIN_DEM ;
    m_dbDemRect.top = MAX_DEM ;
}

/**
 *@fn ��CmlDemProc()
 *@date 2011.11
 *@author �⿭
 *@brief DEM��������������
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
 */
CmlDemProc::~CmlDemProc()
{

}

/**
 *@fn Resample()
 *@date 2011.11
 *@author �⿭
 *@brief �ز�������
 *@param nType ��������
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
 */
bool CmlDemProc::Resample(SINT nType)
{

    return true;
}


/**
* @fn mlWriteToGeoFile
* @date 2011.11.02
* @author �⿭ wukai@irsa.ac.cn
* @brief ��ά��������ָ����ΧDEM��������geotiff�ļ�
* @param vec3DPts ��ά����
* @param dbDemRect ָ��DEM���ɷ�Χ
* @param dRes DEM�ֱ���
* @param strGeoFilePath �ļ�·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlDemProc::mlWriteToGeoFile(vector<Pt3d>& vec3DPts , DbRect dbDemRect , DOUBLE dRes , const SCHAR* strGeoFilePath, ImgDotType imgType, string strTriFile )
{
        // preprocessing
    m_dScale = dRes / 0.01;
    for(SINT i = 0 ; i < vec3DPts.size() ; i++)
    {
        vec3DPts[i].X = vec3DPts[i].X / m_dScale ;
        vec3DPts[i].Y = vec3DPts[i].Y / m_dScale ;
    }
    DOUBLE dOrigRes = dRes;
    dRes /= m_dScale ;

    dbDemRect.left /= m_dScale;
    dbDemRect.right /= m_dScale;
    dbDemRect.top /= m_dScale;
    dbDemRect.bottom /= m_dScale;
    // ��֤������dem�ֱ��ʵķǸ���
    if(dRes < 0)
    {
        m_dDemRes = -dRes ;
    }
    else if(dRes > 0)
    {
        m_dDemRes = dRes ;
    }
    else
    {
        SCHAR strErr[] = "mlWriteToGeoFile error : dem resolution para is null" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    // �ж�dem��Χ�ĺ�����
    if((dbDemRect.left >= dbDemRect.right) || (dbDemRect.bottom >= dbDemRect.top))
    {
        SCHAR strErr[] = "mlWriteToGeoFile error : dem range para is null" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    // �õ�3ά���Ƶ�����
    m_lPtsNum = vec3DPts.size();
    if( m_lPtsNum ) // ���Ʒǿ�
    {
        SINT lBlockWidth ;
        SINT lBlockHeight ;
        ULONG lBlockSize ;
        ULONG lDemSize ;
        // ����dem��Ʒ�ķֱ��ʣ�ȥ������ĵ�
        if(!getRangeFromPts(vec3DPts , dbDemRect)||!delDulPtsByIdx(vec3DPts))
        {
            return false ;
        }
        m_vec3DPts.clear() ;
        m_vec3DPts = vec3DPts ;
        // ���ƹ���Tin
        CmlTIN oriTin ;
        m_pTin = &oriTin ;
        if(!m_pTin->Build2By3DPt(m_vec3DPts))
        {
            return false ;
        }
        //���̽�⳵Ӱ�� , Ԥ������ܸ�����
//        if(m_dDemRes < 1.0)
//        {
        denseGridPts(vec3DPts , dbDemRect , 2.0 * m_dDemRes, 2 , 2) ;
        m_vec3DPts.clear() ;
        m_vec3DPts = vec3DPts ;
        m_dDemRes = fabs(dRes) ;
        // �õ����ܵ��Ʒֲ���Χ
        if(!getRangeFromPts(m_vec3DPts , dbDemRect))
        {
            return false ;
        }
//        }
        CmlTIN tin;
        CmlTIN* pTin = &tin;
        CmlKringing kring;
        CmlKringing* pKring = &kring;
        pKring->InitVariogram() ;
        // 3ά�㹹Tin
        if(!pTin->Build2By3DPt(m_vec3DPts))
        {
            SCHAR strErr[] = "mlCreateDemFrom3DPts error : building triangulation failed" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        if( strTriFile != "" )
        {
            pTin->WriteToFiles( strTriFile.c_str(), m_dScale );
        }
        m_pTri = &pTin->m_tri ;
        // �жϷֿ���
        lBlockWidth = m_nW ;
        lDemSize = m_nH * m_nW ;
        if(lDemSize <= DEM_BLOCK_SIZE)
        {
            m_nBlockNum = 1 ;
            lBlockHeight = m_nH ;  // �ֿ�ĸ߶�
            lBlockSize = lBlockWidth * lBlockHeight ; // �ֿ��������
        }
        else
        {
            lBlockHeight = (SINT)(DEM_BLOCK_SIZE / lBlockWidth) ; // �ֿ�ĸ߶�
            lBlockSize = lBlockWidth * lBlockHeight ; // �ֿ��������
            m_nBlockNum = (SINT)(m_nH / lBlockHeight) ;
            ULONG lDelta = m_nH % lBlockHeight ;
            if(lDelta != 0)
            {
                m_nBlockNum += 1 ;
            }
        }
        // Dem ���Ͻǵ�
        Pt2d ptOrigin ;
        ptOrigin.X = m_dbDemRect.left * m_dScale;
        ptOrigin.Y = m_dbDemRect.top * m_dScale;
        // ����Geotiff��ʽ��DEM�ļ�
        CmlGeoRaster geoRaster ;
        GDALDataType gType = (GDALDataType)imgType;
        UINT nBytes = 0;
        DOUBLE dNoVal = DEM_NO_DATA;
        switch( imgType )
        {
            case T_Byte:
            nBytes = 1;
            dNoVal = (BYTE)(dNoVal);
            break;
            case T_UInt16:
            nBytes = 2;
            dNoVal = (USHORT)(dNoVal);
            break;
            case T_Int16:
            nBytes = 2;
            dNoVal = (SSHORT)(dNoVal);
            break;
            case T_UInt32:
            nBytes = 4;
            dNoVal = (UINT)(dNoVal);
            break;
            case T_Int32:
            nBytes = 4;
            dNoVal = (SINT)(dNoVal);
            break;
            case T_Float32:
            nBytes = 4;
            dNoVal = (FLOAT)(dNoVal);
            break;
            case T_Float64:
            nBytes = 8;
            break;
            default:
            break;
        }

        if(!geoRaster.CreateGeoFile(strGeoFilePath , ptOrigin , fabs(dOrigRes), -fabs(dOrigRes), m_nH , m_nW , 1 , gType , dNoVal))
        {
            SCHAR strErr[] = "mlCreateGeoFile error : Failed to create geoTiff file\n" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        // �������ݿ���������
        CmlRasterBlock imgRaster ;
        imgRaster.SetGDTType(gType) ;
        DbRect dbDemPartion ;
        // dem ���ݳ����ڴ���ֵʱ�ֿ鴦��
        for( SINT i = 0 ; i < m_nBlockNum ; i++)
        {
            CmlRasterBlock imgRaster ;
            imgRaster.SetGDTType(gType) ;
            // �ֿ�dem��ֵ
            dbDemPartion.left = dbDemRect.left ;
            dbDemPartion.right = dbDemRect.right ;
            dbDemPartion.top = dbDemRect.top - i * lBlockHeight * m_dDemRes ;
            // �ֿ�д��ȫ��dem
            if(i< (m_nBlockNum -1 ))
            {
                imgRaster.InitialImg(lBlockHeight , lBlockWidth , nBytes ) ;
                DOUBLE *pDem = new DOUBLE[lBlockHeight*lBlockWidth];
                dbDemPartion.bottom = dbDemPartion.top - lBlockHeight * m_dDemRes ;
                // ���ƹ�������դ���״����
                printf("Get Block  %d  /  %d Index : ", (i+1), m_nBlockNum );
                if(!createRasterFrom3DPts(pTin , pKring , dbDemPartion , lBlockWidth , lBlockHeight , pDem))
                {
                    delete[] pDem;
                    SCHAR strErr[] = "mlWriteToGeoFile error : dem construction faile" ;
                    LOGAddErrorMsg(strErr) ;
                    return false ;
                }
                else
                {
                    for(UINT tI = 0; tI < (UINT)lBlockHeight; ++tI )
                    {
                        for( UINT tJ = 0; tJ < (UINT)lBlockWidth; ++tJ )
                        {
                            imgRaster.SetDoubleVal( tI, tJ, pDem[tI*lBlockWidth+tJ] );
                        }
                    }
                    delete[] pDem;
                }
            }
            else
            {
                UINT nTHeight, nTWidth;
                nTHeight = m_nH - i*lBlockHeight;
                nTWidth = lBlockWidth;
                imgRaster.InitialImg( nTHeight, nTWidth , nBytes ) ;
                DOUBLE *pDem = new DOUBLE[(nTHeight)*nTWidth];
                dbDemPartion.bottom = dbDemRect.bottom ;
                // ���ƹ�������դ���״����
                printf("Get Block  %d  /  %d Index : ", (i+1), m_nBlockNum );
                if(!createRasterFrom3DPts(pTin , pKring , dbDemPartion , nTWidth , (nTHeight) , pDem))
                {
                    delete[] pDem;
                    SCHAR strErr[] = "mlWriteToGeoFile error : dem construction faile" ;
                    LOGAddErrorMsg(strErr) ;
                    return false ;
                }
                else
                {
                    for(UINT tI = 0; tI < (nTHeight); ++tI )
                    {
                        for( UINT tJ = 0; tJ < nTWidth; ++tJ )
                        {
                            imgRaster.SetDoubleVal( tI, tJ, pDem[tI*nTWidth+tJ] );
                        }
                    }
                    delete[] pDem;
                }
            }
            // ��ָ��dem�ļ���ȡdemդ������
            geoRaster.SaveBlockToFile((UINT)1 , 0 , (UINT)(i * lBlockHeight ) , &imgRaster) ;
        }
    }
    else
    {
        SCHAR strErr[] = "mlWriteToGeoFile error : 3D points para is null" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    return true ;
}
bool CmlDemProc::mlWriteRegionToGeoFile(vector<Pt3d>& vec3DPts , DbRect dbDemRect , DOUBLE dRes , vector<Polygon3d> &vecRegions, const SCHAR* strGeoFilePath, ImgDotType imgType, string strTriFile )
{
    m_dScale = dRes / 0.01;
    m_vecRegions.clear();

    for( UINT i = 0; i < vecRegions.size(); ++i )
    {
        Polygon3d poly = vecRegions[i];
        Polygon3d polyNew;
        polyNew.nID = poly.nID;
        for( UINT j = 0; j < poly.vecVectex.size(); ++j )
        {
            Pt3d ptCur = poly.vecVectex[j];
            ptCur.X /= m_dScale;
            ptCur.Y /= m_dScale;
            polyNew.vecVectex.push_back( ptCur );
        }
        m_vecRegions.push_back( polyNew );
    }



    for(SINT i = 0 ; i < vec3DPts.size() ; i++)
    {
        vec3DPts[i].X = vec3DPts[i].X / m_dScale ;
        vec3DPts[i].Y = vec3DPts[i].Y / m_dScale ;
    }
    DOUBLE dOrigRes = dRes;
    dRes /= m_dScale ;

    dbDemRect.left /= m_dScale;
    dbDemRect.right /= m_dScale;
    dbDemRect.top /= m_dScale;
    dbDemRect.bottom /= m_dScale;
    // ��֤������dem�ֱ��ʵķǸ���
    if(dRes < 0)
    {
        m_dDemRes = -dRes ;
    }
    else if(dRes > 0)
    {
        m_dDemRes = dRes ;
    }
    else
    {
        SCHAR strErr[] = "mlWriteToGeoFile error : dem resolution para is null" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    // �ж�dem��Χ�ĺ�����
    if((dbDemRect.left >= dbDemRect.right) || (dbDemRect.bottom >= dbDemRect.top))
    {
        SCHAR strErr[] = "mlWriteToGeoFile error : dem range para is null" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    // �õ�3ά���Ƶ�����
    m_lPtsNum = vec3DPts.size();
    if( m_lPtsNum ) // ���Ʒǿ�
    {
        SINT lBlockWidth ;
        SINT lBlockHeight ;
        ULONG lBlockSize ;
        ULONG lDemSize ;
        // ����dem��Ʒ�ķֱ��ʣ�ȥ������ĵ�
        if(!getRangeFromPts(vec3DPts , dbDemRect)||!delDulPtsByIdx(vec3DPts))
        {
            return false ;
        }
        m_vec3DPts.clear() ;
        m_vec3DPts = vec3DPts ;
        // ���ƹ���Tin
        CmlTIN oriTin ;
        m_pTin = &oriTin ;
        if(!m_pTin->Build2By3DPt(m_vec3DPts))
        {
            return false ;
        }
        //���̽�⳵Ӱ�� , Ԥ������ܸ�����
//        if(m_dDemRes < 1.0)
//        {
        denseGridPts(vec3DPts , dbDemRect , 2.0 * m_dDemRes, 2 , 2) ;
        m_vec3DPts.clear() ;
        m_vec3DPts = vec3DPts ;
        m_dDemRes = fabs(dRes) ;
        // �õ����ܵ��Ʒֲ���Χ
        if(!getRangeFromPts(m_vec3DPts , dbDemRect))
        {
            return false ;
        }
//        }
        CmlTIN tin;
        CmlTIN* pTin = &tin;
        CmlKringing kring;
        CmlKringing* pKring = &kring;
        pKring->InitVariogram() ;
        // 3ά�㹹Tin
        if(!pTin->Build2By3DPt(m_vec3DPts))
        {
            SCHAR strErr[] = "mlCreateDemFrom3DPts error : building triangulation failed" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        if( strTriFile != "" )
        {
            pTin->WriteToFiles( strTriFile.c_str(), m_dScale );
        }
        m_pTri = &pTin->m_tri ;
        // �жϷֿ���
        lBlockWidth = m_nW ;
        lDemSize = m_nH * m_nW ;
        if(lDemSize <= DEM_BLOCK_SIZE)
        {
            m_nBlockNum = 1 ;
            lBlockHeight = m_nH ;  // �ֿ�ĸ߶�
            lBlockSize = lBlockWidth * lBlockHeight ; // �ֿ��������
        }
        else
        {
            lBlockHeight = (SINT)(DEM_BLOCK_SIZE / lBlockWidth) ; // �ֿ�ĸ߶�
            lBlockSize = lBlockWidth * lBlockHeight ; // �ֿ��������
            m_nBlockNum = (SINT)(m_nH / lBlockHeight) ;
            ULONG lDelta = m_nH % lBlockHeight ;
            if(lDelta != 0)
            {
                m_nBlockNum += 1 ;
            }
        }
        // Dem ���Ͻǵ�
        Pt2d ptOrigin ;
        ptOrigin.X = m_dbDemRect.left * m_dScale;
        ptOrigin.Y = m_dbDemRect.top * m_dScale;
        // ����Geotiff��ʽ��DEM�ļ�
        CmlGeoRaster geoRaster ;
        GDALDataType gType = (GDALDataType)imgType;
        UINT nBytes = 0;
        DOUBLE dNoVal = DEM_NO_DATA;
        switch( imgType )
        {
            case T_Byte:
            nBytes = 1;
            dNoVal = (BYTE)(dNoVal);
            break;
            case T_UInt16:
            nBytes = 2;
            dNoVal = (USHORT)(dNoVal);
            break;
            case T_Int16:
            nBytes = 2;
            dNoVal = (SSHORT)(dNoVal);
            break;
            case T_UInt32:
            nBytes = 4;
            dNoVal = (UINT)(dNoVal);
            break;
            case T_Int32:
            nBytes = 4;
            dNoVal = (SINT)(dNoVal);
            break;
            case T_Float32:
            nBytes = 4;
            dNoVal = (FLOAT)(dNoVal);
            break;
            case T_Float64:
            nBytes = 8;
            break;
            default:
            break;
        }

        if(!geoRaster.CreateGeoFile(strGeoFilePath , ptOrigin , fabs(dOrigRes), -fabs(dOrigRes), m_nH , m_nW , 1 , gType , dNoVal))
        {
            SCHAR strErr[] = "mlCreateGeoFile error : Failed to create geoTiff file\n" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        // �������ݿ���������
        CmlRasterBlock imgRaster ;
        imgRaster.SetGDTType(gType) ;
        DbRect dbDemPartion ;
        // dem ���ݳ����ڴ���ֵʱ�ֿ鴦��
        for( SINT i = 0 ; i < m_nBlockNum ; i++)
        {
            CmlRasterBlock imgRaster ;
            imgRaster.SetGDTType(gType) ;
            // �ֿ�dem��ֵ
            dbDemPartion.left = dbDemRect.left ;
            dbDemPartion.right = dbDemRect.right ;
            dbDemPartion.top = dbDemRect.top - i * lBlockHeight * m_dDemRes ;
            // �ֿ�д��ȫ��dem
            if(i< (m_nBlockNum -1 ))
            {
                imgRaster.InitialImg(lBlockHeight , lBlockWidth , nBytes ) ;
                DOUBLE *pDem = new DOUBLE[lBlockHeight*lBlockWidth];
                dbDemPartion.bottom = dbDemPartion.top - lBlockHeight * m_dDemRes ;
                // ���ƹ�������դ���״����
                printf("Get Block  %d  /  %d Index : ", (i+1), m_nBlockNum );
                if(!createRasterFrom3DPts(pTin , pKring , dbDemPartion , lBlockWidth , lBlockHeight , pDem))
                {
                    delete[] pDem;
                    SCHAR strErr[] = "mlWriteToGeoFile error : dem construction faile" ;
                    LOGAddErrorMsg(strErr) ;
                    return false ;
                }
                else
                {
                    for(UINT tI = 0; tI < (UINT)lBlockHeight; ++tI )
                    {
                        for( UINT tJ = 0; tJ < (UINT)lBlockWidth; ++tJ )
                        {
                            imgRaster.SetDoubleVal( tI, tJ, pDem[tI*lBlockWidth+tJ] );
                        }
                    }
                    delete[] pDem;
                }
            }
            else
            {
                UINT nTHeight, nTWidth;
                nTHeight = m_nH - i*lBlockHeight;
                nTWidth = lBlockWidth;
                imgRaster.InitialImg( nTHeight, nTWidth , nBytes ) ;
                DOUBLE *pDem = new DOUBLE[(nTHeight)*nTWidth];
                dbDemPartion.bottom = dbDemRect.bottom ;
                // ���ƹ�������դ���״����
                printf("Get Block  %d  /  %d Index : ", (i+1), m_nBlockNum );
                if(!createRasterFrom3DPts(pTin , pKring , dbDemPartion , nTWidth , (nTHeight) , pDem))
                {
                    delete[] pDem;
                    SCHAR strErr[] = "mlWriteToGeoFile error : dem construction faile" ;
                    LOGAddErrorMsg(strErr) ;
                    return false ;
                }
                else
                {
                    for(UINT tI = 0; tI < (nTHeight); ++tI )
                    {
                        for( UINT tJ = 0; tJ < nTWidth; ++tJ )
                        {
                            imgRaster.SetDoubleVal( tI, tJ, pDem[tI*nTWidth+tJ] );
                        }
                    }
                    delete[] pDem;
                }
            }
            // ��ָ��dem�ļ���ȡdemդ������
            geoRaster.SaveBlockToFile((UINT)1 , 0 , (UINT)(i * lBlockHeight ) , &imgRaster) ;
        }
    }
    else
    {
        SCHAR strErr[] = "mlWriteToGeoFile error : 3D points para is null" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    return true ;
}
/**
* @fn
* @date 2011.11.02
* @author �⿭ wukai@irsa.ac.cn
* @brief ��ά����ȫ������DEM��������geotiff�ļ�
* @param vec3DPts ��ά����
* @param dRes DEM�ֱ���
* @param strGeoFilePath �ļ�·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlDemProc::mlWriteToGeoFile(vector<Pt3d>& vec3DPts , DOUBLE dRes , const SCHAR* strGeoFilePath )
{
    // preprocessing
    for(SINT i = 0 ; i < vec3DPts.size() ; i++)
    {
        vec3DPts[i].X = vec3DPts[i].X / m_dScale ;
        vec3DPts[i].Y = vec3DPts[i].Y / m_dScale ;
    }
    dRes /= m_dScale ;
    // ��֤������dem�ֱ��ʵķǸ���
    if(dRes < 0)
    {
        m_dDemRes = -dRes ;
    }
    else if(dRes > 0)
    {
        m_dDemRes = dRes ;
    }
    else
    {
        SCHAR strErr[] = "mlWriteToGeoFile error : dem resolution para is null" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    // �õ�3ά���Ƶ�����
    m_lPtsNum = vec3DPts.size();
    if( m_lPtsNum ) // ���Ʒǿ�
    {
        SINT lBlockWidth ;
        SINT lBlockHeight ;
        ULONG lBlockSize ;
        ULONG lDemSize ;
        // ����dem��Ʒ�ķֱ��ʣ�ȥ������ĵ�
        if(!getRangeFromPts(vec3DPts)||!delDulPtsByIdx(vec3DPts)||!getRangeFromPts(vec3DPts))
        {
            return false ;
        }
        m_vec3DPts.clear() ;
        m_vec3DPts = vec3DPts ;
        // ���ƹ���Tin
        CmlTIN oriTin ;
        m_pTin = &oriTin ;
        if(!m_pTin->Build2By3DPt(m_vec3DPts))
        {
            return false ;
        }
        //���̽�⳵Ӱ�� , Ԥ������ܸ�����
//        if(m_dDemRes < 1.0)
//        {
            // Ԥ�������
            denseGridPts(vec3DPts , m_dbDemRect , 2.0 * m_dDemRes , 2 , 2) ;
            m_vec3DPts.clear() ;
            m_vec3DPts = vec3DPts ;
            m_dDemRes = fabs(dRes) ;
            // �õ����ܵ��Ʒֲ���Χ
            if(!getRangeFromPts(m_vec3DPts))
            {
                return false ;
            }
//        }
        CmlTIN tin;
        CmlTIN* pTin = &tin;
        // 3ά�㹹Tin
        if(!pTin->Build2By3DPt(m_vec3DPts))
        {
            SCHAR strErr[] = "mlCreateDemFrom3DPts error : building triangulation failed" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        m_pTri = &pTin->m_tri ;

        CmlKringing kring;
        CmlKringing* pKring = &kring;
        pKring->InitVariogram() ;
        // �жϷֿ���
        lBlockWidth = m_nW ;
        lDemSize = m_nH * m_nW ;
        if(lDemSize <= DEM_BLOCK_SIZE)
        {
            m_nBlockNum = 1 ;
            lBlockHeight = m_nH ; // �ֿ�ĸ߶�
            lBlockSize = lBlockWidth * lBlockHeight ; // �ֿ��������
        }
        else
        {
            lBlockHeight = (SINT)(DEM_BLOCK_SIZE / lBlockWidth) ; // �ֿ�ĸ߶�
            lBlockSize = lBlockWidth * lBlockHeight ; // �ֿ��������
            m_nBlockNum = (SINT)(m_nH / lBlockHeight) ;
            ULONG lDelta = m_nH % lBlockHeight ;
            if(lDelta != 0)
            {
                m_nBlockNum += 1 ;
            }
        }
        // Dem���Ͻǵ�
        Pt2d ptOrigin ;
        ptOrigin.X = m_dbDemRect.left * m_dScale;
        ptOrigin.Y = m_dbDemRect.top * m_dScale ;
        // ����Geotiff��ʽ��DEM�ļ�
        CmlGeoRaster geoRaster ;
        if(!geoRaster.CreateGeoFile(strGeoFilePath , ptOrigin , m_dDemRes * m_dScale , -m_dDemRes * m_dScale, m_nH , m_nW , 1 , GDT_Float64 , DEM_NO_DATA))
        {
            SCHAR strErr[] = "mlCreateGeoFile error : Failed to create geoTiff file\n" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        // �������ݿ���������
        CmlRasterBlock imgRaster ;
        imgRaster.SetGDTType(GDT_Float64) ;
        DbRect dbDemPartion ;
        // dem ���ݳ����ڴ���ֵʱ�ֿ鴦��
        for( SINT i = 0 ; i < m_nBlockNum ; i++)
        {
            CmlRasterBlock imgRaster ;
            imgRaster.SetGDTType(GDT_Float64) ;
            DOUBLE* pDem = NULL ;
            // �ֿ�dem��ֵ
            dbDemPartion.left = m_dbDemRect.left ;
            dbDemPartion.right = m_dbDemRect.right ;
            dbDemPartion.top = m_dbDemRect.top - i * lBlockHeight * m_dDemRes ;
            // �ֿ�д��ȫ��dem
            if(i< (m_nBlockNum -1 ))
            {
                imgRaster.InitialImg(lBlockHeight , lBlockWidth , 8 ) ;
                pDem = (DOUBLE*)imgRaster.GetData() ;
                dbDemPartion.bottom = dbDemPartion.top - lBlockHeight * m_dDemRes ;
                // ���ƹ�������դ���״����
                if(!createRasterFrom3DPts(pTin , pKring , dbDemPartion , lBlockWidth , lBlockHeight , pDem))
                {
                    SCHAR strErr[] = "mlWriteToGeoFile error : dem construction faile" ;
                    LOGAddErrorMsg(strErr) ;
                    return false ;
                }
            }
            else
            {
                imgRaster.InitialImg((m_nH - i*lBlockHeight) , lBlockWidth , 8 ) ;
                pDem = (DOUBLE*)imgRaster.GetData() ;
                dbDemPartion.bottom = m_dbDemRect.bottom ;
                // ���ƹ�������դ���״����
                if(!createRasterFrom3DPts(pTin , pKring , dbDemPartion , lBlockWidth , (m_nH - i*lBlockHeight) , pDem))
                {
                    SCHAR strErr[] = "mlWriteToGeoFile error : dem construction faile" ;
                    LOGAddErrorMsg(strErr) ;
                    return false ;
                }
            }
            // ��ָ��dem�ļ���ȡdemդ������
            geoRaster.SaveBlockToFile((UINT)1 , 0 , (UINT)(i * lBlockHeight ) , &imgRaster) ;
        }
    }
    else
    {
        SCHAR strErr[] = "mlWriteToGeoFile error : 3D points para is null" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    return true ;
}
bool CmlDemProc::mlWriteToGeoFile(vector<Pt3d>& vec3DPts , DOUBLE dRes , const SCHAR* strGeoFilePath, ImgDotType imgType, string strTriFile )
{
	// preprocessing
	m_dScale = dRes / 0.01;
	for(SINT i = 0 ; i < vec3DPts.size() ; i++)
	{
		vec3DPts[i].X = vec3DPts[i].X / m_dScale ;
		vec3DPts[i].Y = vec3DPts[i].Y / m_dScale ;
	}
	DOUBLE dOrigRes = dRes;
	dRes /= m_dScale ;

	
	// ��֤������dem�ֱ��ʵķǸ���
	if(dRes < 0)
	{
		m_dDemRes = -dRes ;
	}
	else if(dRes > 0)
	{
		m_dDemRes = dRes ;
	}
	else
	{
		SCHAR strErr[] = "mlWriteToGeoFile error : dem resolution para is null" ;
		LOGAddErrorMsg(strErr) ;
		return false ;
	}
	
	// �õ�3ά���Ƶ�����
	m_lPtsNum = vec3DPts.size();
	if( m_lPtsNum ) // ���Ʒǿ�
	{
		SINT lBlockWidth ;
		SINT lBlockHeight ;
		ULONG lBlockSize ;
		ULONG lDemSize ;
		// ����dem��Ʒ�ķֱ��ʣ�ȥ������ĵ�
		if(!getRangeFromPts(vec3DPts )||!delDulPtsByIdx(vec3DPts)||!getRangeFromPts(vec3DPts ))
		{
			return false ;
		}
		m_vec3DPts.clear() ;
		m_vec3DPts = vec3DPts ;
		// ���ƹ���Tin
		CmlTIN oriTin ;
		m_pTin = &oriTin ;
		if(!m_pTin->Build2By3DPt(m_vec3DPts))
		{
			return false ;
		}
		//���̽�⳵Ӱ�� , Ԥ������ܸ�����
		//        if(m_dDemRes < 1.0)
		//        {
		denseGridPts(vec3DPts , m_dbDemRect , 2.0 * m_dDemRes, 2 , 2) ;
		m_vec3DPts.clear() ;
		m_vec3DPts = vec3DPts ;
		m_dDemRes = fabs(dRes) ;
		// �õ����ܵ��Ʒֲ���Χ
		if(!getRangeFromPts(m_vec3DPts ))
		{
			return false ;
		}
		//        }
		CmlTIN tin;
		CmlTIN* pTin = &tin;
		CmlKringing kring;
		CmlKringing* pKring = &kring;
		pKring->InitVariogram() ;
		// 3ά�㹹Tin
		if(!pTin->Build2By3DPt(m_vec3DPts))
		{
			SCHAR strErr[] = "mlCreateDemFrom3DPts error : building triangulation failed" ;
			LOGAddErrorMsg(strErr) ;
			return false ;
		}
		if( strTriFile != "" )
		{
			pTin->WriteToFiles( strTriFile.c_str(), m_dScale );
		}
		m_pTri = &pTin->m_tri ;
		// �жϷֿ���
		lBlockWidth = m_nW ;
		lDemSize = m_nH * m_nW ;
		if(lDemSize <= DEM_BLOCK_SIZE)
		{
			m_nBlockNum = 1 ;
			lBlockHeight = m_nH ;  // �ֿ�ĸ߶�
			lBlockSize = lBlockWidth * lBlockHeight ; // �ֿ��������
		}
		else
		{
			lBlockHeight = (SINT)(DEM_BLOCK_SIZE / lBlockWidth) ; // �ֿ�ĸ߶�
			lBlockSize = lBlockWidth * lBlockHeight ; // �ֿ��������
			m_nBlockNum = (SINT)(m_nH / lBlockHeight) ;
			ULONG lDelta = m_nH % lBlockHeight ;
			if(lDelta != 0)
			{
				m_nBlockNum += 1 ;
			}
		}
		// Dem ���Ͻǵ�
		Pt2d ptOrigin ;
		ptOrigin.X = m_dbDemRect.left * m_dScale;
		ptOrigin.Y = m_dbDemRect.top * m_dScale;
		// ����Geotiff��ʽ��DEM�ļ�
		CmlGeoRaster geoRaster ;
		GDALDataType gType = (GDALDataType)imgType;
		UINT nBytes = 0;
		DOUBLE dNoVal = DEM_NO_DATA;
		switch( imgType )
		{
		case T_Byte:
			nBytes = 1;
			dNoVal = (BYTE)(dNoVal);
			break;
		case T_UInt16:
			nBytes = 2;
			dNoVal = (USHORT)(dNoVal);
			break;
		case T_Int16:
			nBytes = 2;
			dNoVal = (SSHORT)(dNoVal);
			break;
		case T_UInt32:
			nBytes = 4;
			dNoVal = (UINT)(dNoVal);
			break;
		case T_Int32:
			nBytes = 4;
			dNoVal = (SINT)(dNoVal);
			break;
		case T_Float32:
			nBytes = 4;
			dNoVal = (FLOAT)(dNoVal);
			break;
		case T_Float64:
			nBytes = 8;
			break;
		default:
			break;
		}

		if(!geoRaster.CreateGeoFile(strGeoFilePath , ptOrigin , fabs(dOrigRes), -fabs(dOrigRes), m_nH , m_nW , 1 , gType , dNoVal))
		{
			SCHAR strErr[] = "mlCreateGeoFile error : Failed to create geoTiff file\n" ;
			LOGAddErrorMsg(strErr) ;
			return false ;
		}
		// �������ݿ���������
		CmlRasterBlock imgRaster ;
		imgRaster.SetGDTType(gType) ;
		DbRect dbDemPartion ;

		DbRect dbDemRect = m_dbDemRect;

		// dem ���ݳ����ڴ���ֵʱ�ֿ鴦��
		for( SINT i = 0 ; i < m_nBlockNum ; i++)
		{
			CmlRasterBlock imgRaster ;
			imgRaster.SetGDTType(gType) ;
			// �ֿ�dem��ֵ
			dbDemPartion.left = dbDemRect.left ;
			dbDemPartion.right = dbDemRect.right ;
			dbDemPartion.top = dbDemRect.top - i * lBlockHeight * m_dDemRes ;
			// �ֿ�д��ȫ��dem
			if(i< (m_nBlockNum -1 ))
			{
				imgRaster.InitialImg(lBlockHeight , lBlockWidth , nBytes ) ;
				DOUBLE *pDem = new DOUBLE[lBlockHeight*lBlockWidth];
				dbDemPartion.bottom = dbDemPartion.top - lBlockHeight * m_dDemRes ;
				// ���ƹ�������դ���״����
				printf("Get Block  %d  /  %d Index : ", (i+1), m_nBlockNum );
				if(!createRasterFrom3DPts(pTin , pKring , dbDemPartion , lBlockWidth , lBlockHeight , pDem))
				{
					delete[] pDem;
					SCHAR strErr[] = "mlWriteToGeoFile error : dem construction faile" ;
					LOGAddErrorMsg(strErr) ;
					return false ;
				}
				else
				{
					for(UINT tI = 0; tI < (UINT)lBlockHeight; ++tI )
					{
						for( UINT tJ = 0; tJ < (UINT)lBlockWidth; ++tJ )
						{
							imgRaster.SetDoubleVal( tI, tJ, pDem[tI*lBlockWidth+tJ] );
						}
					}
					delete[] pDem;
				}
			}
			else
			{
				UINT nTHeight, nTWidth;
				nTHeight = m_nH - i*lBlockHeight;
				nTWidth = lBlockWidth;
				imgRaster.InitialImg( nTHeight, nTWidth , nBytes ) ;
				DOUBLE *pDem = new DOUBLE[(nTHeight)*nTWidth];
				dbDemPartion.bottom = dbDemRect.bottom ;
				// ���ƹ�������դ���״����
				printf("Get Block  %d  /  %d Index : ", (i+1), m_nBlockNum );
				if(!createRasterFrom3DPts(pTin , pKring , dbDemPartion , nTWidth , (nTHeight) , pDem))
				{
					delete[] pDem;
					SCHAR strErr[] = "mlWriteToGeoFile error : dem construction faile" ;
					LOGAddErrorMsg(strErr) ;
					return false ;
				}
				else
				{
					for(UINT tI = 0; tI < (nTHeight); ++tI )
					{
						for( UINT tJ = 0; tJ < nTWidth; ++tJ )
						{
							imgRaster.SetDoubleVal( tI, tJ, pDem[tI*nTWidth+tJ] );
						}
					}
					delete[] pDem;
				}
			}
			// ��ָ��dem�ļ���ȡdemդ������
			geoRaster.SaveBlockToFile((UINT)1 , 0 , (UINT)(i * lBlockHeight ) , &imgRaster) ;
		}
	}
	else
	{
		SCHAR strErr[] = "mlWriteToGeoFile error : 3D points para is null" ;
		LOGAddErrorMsg(strErr) ;
		return false ;
	}
	return true ;
}
/**
* @fn mlGetRangeFromPts����
* @date 2011.11.02
* @author �⿭ wukai@irsa.ac.cn
* @brief  ���ݵ��Ƽ�ָ�����η�Χ���dem��Χ
* @param vec3DPts ��ά����
* @param dbDemRect ָ�����η�Χ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlDemProc::getRangeFromPts(vector<Pt3d>& vec3DPts , DbRect dbDemRect)
{
    // �õ���������
    if(!(m_lPtsNum = vec3DPts.size()))
    {
        return false ;
    }
    else
    {
        // dem ��Χ��ʼ��
        DbRect dbRectXY , dbRectZ ;
        dbRectXY.left = MAX_DEM ;
        dbRectXY.right = MIN_DEM ;
        dbRectXY.bottom = MAX_DEM ;
        dbRectXY.top = MIN_DEM  ;
        dbRectZ.bottom = MAX_DEM ;
        dbRectZ.top = MIN_DEM ;
        // ���ݵ��Ƶõ�DEM��Χ
        for(UINT i = 0 ; i < m_lPtsNum ; i++)
        {
            Pt3d ptTemp = vec3DPts[i] ;
            m_dbRectXY.left = MIN(ptTemp.X , m_dbRectXY.left) ;
            m_dbRectXY.right = MAX(ptTemp.X , m_dbRectXY.right) ;
            m_dbRectXY.bottom = MIN(ptTemp.Y , m_dbRectXY.bottom) ;
            m_dbRectXY.top = MAX(ptTemp.Y , m_dbRectXY.top) ;
            m_dbRectZ.bottom = MIN(ptTemp.Z , m_dbRectZ.bottom) ;
            m_dbRectZ.top = MAX(ptTemp.Z , m_dbRectZ.top) ;
        }
        //  ȫ��dem�жϹ�ϵ
        if( (m_dbRectXY.left >= m_dbRectXY.right) || (m_dbRectXY.top <= m_dbRectXY.bottom))
        {
            return false ;
        }
        m_dbDemRect = dbDemRect ;
        // ȷ��dem��Ʒ���ɷ�Χ
        m_nW = (SINT)((m_dbDemRect.right - m_dbDemRect.left +  EPSILON)/m_dDemRes) ;
        m_nH = (SINT)((m_dbDemRect.top - m_dbDemRect.bottom  + EPSILON)/m_dDemRes) ;
        m_dbDemRect.right = m_dbDemRect.left + m_nW * m_dDemRes ;
        m_dbDemRect.bottom = m_dbDemRect.top - m_nH * m_dDemRes ;
        return true ;
    }
}

/**
 * @fn mlGetRangeFromPts����
 * @date 2011.11.02
 * @author �⿭ wukai@irsa.ac.cn
 * @brief  ���ݵ������dem��Χ
 * @param vec3DPts ��ά����
 * @retval TRUE �ɹ�
 * @retval FALSE ʧ��
 * @version 1.0
 * @par �޸���ʷ��
 * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
bool CmlDemProc::getRangeFromPts(vector<Pt3d>& vec3DPts)
{
    // �õ���������
    if(!(m_lPtsNum = vec3DPts.size()))
    {
        return false ;
    }
    else
    {
        // dem ��Χ��ʼ��
        DbRect dbRectXY , dbRectZ ;
        dbRectXY.left = MAX_DEM ;
        dbRectXY.right = MIN_DEM ;
        dbRectXY.bottom = MAX_DEM ;
        dbRectXY.top = MIN_DEM  ;
        dbRectZ.bottom = MAX_DEM ;
        dbRectZ.top = MIN_DEM ;
        // ���ݵ��Ƶõ�DEM��Χ
        for(UINT i = 0 ; i < m_lPtsNum ; i++)
        {
            Pt3d ptTemp = vec3DPts[i] ;
            m_dbRectXY.left = MIN(ptTemp.X , m_dbRectXY.left) ;
            m_dbRectXY.right = MAX(ptTemp.X , m_dbRectXY.right) ;
            m_dbRectXY.bottom = MIN(ptTemp.Y , m_dbRectXY.bottom) ;
            m_dbRectXY.top = MAX(ptTemp.Y , m_dbRectXY.top) ;
            m_dbRectZ.bottom = MIN(ptTemp.Z , m_dbRectZ.bottom) ;
            m_dbRectZ.top = MAX(ptTemp.Z , m_dbRectZ.top) ;
        }
        //  ȫ��dem�жϹ�ϵ
        if( (m_dbRectXY.left >= m_dbRectXY.right) || (m_dbRectXY.top <= m_dbRectXY.bottom))
        {
            return false ;
        }
        // ȷ��dem��Ʒ���ɷ�Χ
        m_nGlobalW = (SINT)((m_dbRectXY.right - m_dbRectXY.left +  EPSILON)/ m_dDemRes) +1;
        m_nGlobalH = (SINT)((m_dbRectXY.top - m_dbRectXY.bottom  + EPSILON)/ m_dDemRes) +1;
        m_dbRectXY.right = m_dbRectXY.left +  m_nGlobalW * m_dDemRes ;
        m_dbRectXY.bottom = m_dbRectXY.top - m_nGlobalH * m_dDemRes ;
        m_dbDemRect = m_dbRectXY ;
        m_nW = m_nGlobalW ;
        m_nH = m_nGlobalH ;
        return true ;
    }
}
/**
     * @fn denseGridPts()
     * @date 2011.11.02
     * @author �⿭ wukai@irsa.ac.cn
     * @brief ����dem�ķֱ�������Ӧ���ܵ���
     * @param vec3DPts ��ά����
     * @param dbDemRect ���Ƶķֲ���Χ
     * @param dDemTopRes ���ܳ�ʼ����Ӧ������ֵ
     * @param dDemTopRes ���������ܲ���
     * @param nParamidRatio �ֲ���ܲ����ı���ϵ��
     * @retval TRUE �ɹ�
     * @retval FALSE ʧ��
     * @version 1.0
     * @par �޸���ʷ��
     * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
bool CmlDemProc::denseGridPts(vector<Pt3d>& vec3DPts , DbRect dbDemRect , double dDemTopRes , int nParamidNum , int nParamidRatio)
{
    // ��ι�����������ֵ
    m_dDemRes = dDemTopRes ;
    SINT lBlockWidth ;
    SINT lBlockHeight ;
    ULONG lBlockSize ;
    ULONG lDemSize ;
    vecAddPts.clear() ;
    for( SINT n = 0 ; n < nParamidNum ; n++)
    {
        // ����������ֵ
        if(!getRangeFromPts(vec3DPts , dbDemRect)||!delDulPtsByIdx(vec3DPts))
        {
            SCHAR strErr[] = "mlWriteToGeoFile error : dem para initialization faile" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        // �жϷֿ���
        lBlockWidth = m_nW ;
        lDemSize = m_nH * m_nW ;
        if(lDemSize <= DEM_BLOCK_SIZE)
        {
            m_nBlockNum = 1 ;
            lBlockHeight = m_nH ;   // �ֿ�ĸ߶�
            lBlockSize = lBlockWidth * lBlockHeight ; // �ֿ��������
        }
        else
        {
            lBlockHeight = (SINT)(DEM_BLOCK_SIZE / lBlockWidth) ; // �ֿ�ĸ߶�
            lBlockSize = lBlockWidth * lBlockHeight ;  // �ֿ��������
            m_nBlockNum = (SINT)(lDemSize / lBlockSize) ;
            ULONG lDelta = lDemSize % lBlockSize ;
            if(lDelta != 0)
            {
                m_nBlockNum += 1 ;
            }
        }
        DbRect dbDemPartion ;
        CmlTIN tin;
        CmlTIN* pTin = &tin;
        // 3ά�㹹Tin
        if(!pTin->Build2By3DPt(vec3DPts))
        {
            SCHAR strErr[] = "mlCreateDemFrom3DPts error : building triangulation failed" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        m_pTri = &pTin->m_tri ;
        nNumTriangle = pTin->m_tri.numOfTriangles ;
        // dem ���ݳ����ڴ���ֵʱ�ֿ鴦��
        for( SINT i = 0 ; i < m_nBlockNum ; i++)
        {
            CmlKringing kring;
            CmlKringing* pKring = &kring;
            pKring->InitVariogram() ;
            // �ֿ鴦�����ݿ鷶Χ��ֵ
            dbDemPartion.left = dbDemRect.left ;
            dbDemPartion.right = dbDemRect.right ;
            dbDemPartion.top = dbDemRect.top - i * lBlockHeight * m_dDemRes ;
            // �ֿ�������ݿ����
            if(i< (m_nBlockNum -1 ))
            {
                dbDemPartion.bottom = dbDemPartion.top - lBlockHeight * m_dDemRes ;
                // ����Ӧ������������ܵ���
                if(!densePartion3DPts(vec3DPts , pTin , pKring , nParamidRatio))
                {
                    return false ;
                }
            }
            else
            {
                dbDemPartion.bottom = dbDemRect.bottom ;
                // ����Ӧ������������ܵ���
                if(!densePartion3DPts(vec3DPts , pTin , pKring , nParamidRatio))
                {
                    return false ;
                }
            }
        }
        vec3DPts.clear() ;
        vec3DPts = m_vec3DPts ;
        // ���ܵ������䵽ԭʼ����
        vec3DPts.insert(vec3DPts.end() ,vecAddPts.begin() , vecAddPts.end()) ;

		// �õ���һ�����ܴ���dem�ֱ���
		m_dDemRes /= nParamidRatio ;
    }
    return true ;
}
/**
   * @fn densePartion3DPts()
   * @date 2011.11.02
   * @author �⿭ wukai@irsa.ac.cn
   * @brief ���Ƽ��ֿܷ鴦��
   * @param vec3DPts �ֿ����ά����
   * @param pTin ���ƶ�Ӧ��Tin�ṹ
   * @param *pKring ������ֵ��
   * @param nParamidRatio �ֲ���ܲ����ı���ϵ��
   * @retval TRUE �ɹ�
   * @retval FALSE ʧ��
   * @version 1.0
   * @par �޸���ʷ��
   * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
   */
bool CmlDemProc::densePartion3DPts(vector<Pt3d>& vec3DPts , CmlTIN* pTin , CmlKringing* pKring  , SINT nPyramidRatio)
{
    SINT* pTriIndex = NULL ;
    pTriIndex = new SINT[nNumTriangle] ;
    vector<Pt3d> vecDensPts ;
    // ������������������ֲ�������
    if( m_vecRegions.size() == 0 )
    {
        pTin->GetCenterTriIndex(pTriIndex , vecDensPts, &m_dbDemRect , m_dDemRes , &m_vecHoles) ;
    }
    else
    {
        pTin->GetCenterTriIndex(pTriIndex , vecDensPts, &m_dbDemRect , m_dDemRes , &m_vecRegions, &m_vecHoles) ;
    }

//    DOUBLE x,y,z;
    SINT nTriNeighbor[4];//���������α��,[0]������������α��
    Pt3d PtTemp ;
    SINT nIndex = 0 ;
    // �������������������ǵ���
    for( SINT i = 0 ; i < nNumTriangle ; i++)
    {
        if(pTriIndex[i] == NULL_INDEX)
        {
            continue ;
        }
        else
        {
            // ��������������
            nTriNeighbor[0]=*(pTriIndex+i);
            PtTemp = vecDensPts[nIndex++] ;
            PtTemp.Z = DEM_NO_DATA ;
            // �����������ڽ�����������
            for (SINT k=0; k<3; k++)
            {
                nTriNeighbor[k+1]=m_pTri->neighborList[3*nTriNeighbor[0]+k] ;
            }
            // �õ����ܵ�ĸ߳�ֵ
            if(!(pKring->GetValueFromTins(vec3DPts,m_pTri,nTriNeighbor,PtTemp) &&
                    (PtTemp.Z >= m_dbRectZ.bottom) && (PtTemp.Z <= m_dbRectZ.top)))
            {
                pKring->GetValueFromTin(vec3DPts,m_pTri,nTriNeighbor,PtTemp , KRIGING_OFF) ;
                continue ;
            }
            // �����������ĵ������ܵ�����
            if(((PtTemp.Z >= m_dbRectZ.bottom) && (PtTemp.Z <= m_dbRectZ.top)))
            {
                vecAddPts.push_back(PtTemp) ;
            }
        }
    }
    if(pTriIndex)
    {
        delete [] pTriIndex ;
    }
   
    return true  ;
}
/**
    * @fn mlGetRangeFromPts����
    * @date 2011.11.02
    * @author �⿭ wukai@irsa.ac.cn
    * @brief ����3ά���Ƶõ��������dem�ĸ߳�����
    * @param pTin 3ά���ƶ�Ӧ��Tin
    * @param *pKring ������ֵ��
    * @param dbDemRect dem�ֲ���Χ
    * @param nW ����dem����
    * @param nH ����dem����
    * @param *pDem �������dem�߳�����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
bool CmlDemProc::createRasterFrom3DPts(CmlTIN* pTin , CmlKringing* pKring , DbRect dbDemRect , SINT nW , SINT nH , double* pDem)
{
    SINT* pTinIndex = NULL  ;
    if(!(pTinIndex = new SINT[nW * nH]))
    {
        return false ;
    }
    else
    {
        // ������������������ֲ�������
        if( m_vecRegions.size() == 0 )
        {
            pTin->GetGridTriIndex(pTinIndex , nW , nH , &dbDemRect , m_dDemRes , &m_vecHoles) ;
        }
        else
        {
            pTin->GetGridTriIndex(pTinIndex , nW , nH , &dbDemRect , m_dDemRes, &m_vecRegions, &m_vecHoles) ;
        }

        SINT* pOriTinIndex = NULL  ;
        if(!(pOriTinIndex = new SINT[nW * nH]))
        {
            return false ;
        }
        if( m_vecRegions.size() == 0 )
        {
            m_pTin->GetGridTriIndex(pOriTinIndex , nW , nH , &dbDemRect , m_dDemRes , &m_vecHoles) ;
        }
        else
        {
            m_pTin->GetGridTriIndex(pOriTinIndex , nW , nH , &dbDemRect , m_dDemRes , &m_vecRegions, &m_vecHoles) ;
        }

        // Kringing��ֵ����DEM
        DOUBLE dMinX= dbDemRect.left;
        DOUBLE dMinY= dbDemRect.bottom;
//        DOUBLE dMaxY = dbDemRect.top ;
        DOUBLE x,y,z;
        SINT nTriNeighbor[4];//���������α��,[0]������������α��
        Pt3d PtTemp ;
        // demդ�����ݳ�ʼ��
        for (SINT i=nH-1; i>=0; i--)
        {
            for (SINT j=0; j< nW ; j++)
            {
                *(pDem+i* nW+j) = DEM_NO_DATA ;
            }
        }
        // dem դ�����ݸ̸߳�ֵ
        for (SINT i = nH-1; i >= 0 ; i--)
        {
            for (SINT j=0; j< nW; j++)
            {
                y = dMinY + i*m_dDemRes ;
                x = dMinX + j*m_dDemRes;
                z = DEM_NO_DATA;
                PtTemp.X = x ;
                PtTemp.Y = y ;
                PtTemp.Z = z ;
                //��������������
                nTriNeighbor[0]=*(pTinIndex+i* nW+j);
                if ((nTriNeighbor[0] > NULL_INDEX) && (*(pOriTinIndex + i * nW + j) > NULL_INDEX))
                {
                    // �����������ڽ�����������
                    for (SINT k=0; k<3; k++)
                    {
                        nTriNeighbor[k+1]=m_pTri->neighborList[3*nTriNeighbor[0]+k] ;
                    }
                    // �õ�դ���ĸ߳�ֵ
                    if(!(pKring->GetValueFromTin(m_vec3DPts,m_pTri,nTriNeighbor,PtTemp , KRIGING_ON) &&
                            (PtTemp.Z >= m_dbRectZ.bottom) && (PtTemp.Z <= m_dbRectZ.top)))
                    {
                        pKring->GetValueFromTin(m_vec3DPts,m_pTri,nTriNeighbor,PtTemp , KRIGING_OFF) ;
                    }
                    memcpy(pDem+ (nH-1-i)*nW+j,&PtTemp.Z,sizeof(DOUBLE));
                }
                // �����������ĵ����߳�ֵ����
//                if(((PtTemp.Z >= m_dbRectZ.bottom) && (PtTemp.Z <= m_dbRectZ.top)))
//                {
//
//                }
            }
            if( ( (nH - i )*10 %nH ) == 0 )
            {
                printf( "---%d  ", ((nH-i)*10 / nH ) );
            }
        }
        if(pTinIndex)
        {
            delete [] pTinIndex ;
        }
        if(pOriTinIndex)
        {
            delete [] pOriTinIndex ;
        }
    }
    //  ����ģ��Ϊ5�Ĵ���ƽ��dem�߳�����
    SmoothBySmoothFilter(5 , nW , nH ,pDem) ;
    return true ;
}

/**
     * @fn mlDelDulPts()
     * @date 2011.11.02
     * @author �⿭ wukai@irsa.ac.cn
     * @brief �޳����ƹ����ܼ��ĵ�
     * @param vec3DPts ��ά����
     * @retval TRUE �ɹ�
     * @retval FALSE ʧ��
     * @version 1.0
     * @par �޸���ʷ��
     * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
bool CmlDemProc::delDulPts(vector<Pt3d>& vec3DPts)
{
    Pt3d dbPoint;
    ULONG nCount = vec3DPts.size();
    if(!nCount)
    {
        return false ;
    }
    else
    {
        //��X�����������
        for (ULONG i=1; i<nCount; i++)
        {
            for (ULONG j=i+1; j<nCount; j++)
            {
                if (vec3DPts[j].X < vec3DPts[i].X)
                {
                    dbPoint   = vec3DPts[i];
                    vec3DPts[i] = vec3DPts[j];
                    vec3DPts[j] = dbPoint;
                }
            }
        }
        //����dem�ֱ��ʵ�Ҫ��ɾ�����Ƶ������
//        ULONG nDuplicate = 0;
        vector<Pt3d>::iterator itr ;
        for (ULONG i=1; i<nCount; i++)
        {
            for (ULONG j=i+1; j<nCount; j++)
            {
                if (abs(vec3DPts[j].X - vec3DPts[i].X) < m_dDemRes )
                {
                    if (abs(vec3DPts[j].Y - vec3DPts[i].Y) < m_dDemRes )
                    {
                        itr = vec3DPts.begin() + j ;
                        vec3DPts.erase(itr) ;
                        nCount--;
                    }
                }
            }
        }
        return true ;
    }
}
bool CmlDemProc::delDulPtsByIdx(vector<Pt3d>& vec3DPts)
{
    // �õ���������

    DbRect dbRectXY ;
    dbRectXY.left = MAX_DEM ;
    dbRectXY.right = MIN_DEM ;
    dbRectXY.bottom = MAX_DEM ;
    dbRectXY.top = MIN_DEM  ;

    DOUBLE dInterVal = m_dDemRes * 0.5;
    // ���ݵ��Ƶõ�DEM��Χ
    vector<UINT> vecFlags;
    for(UINT i = 0 ; i < vec3DPts.size() ; i++)
    {
        Pt3d ptTemp = vec3DPts[i] ;
        dbRectXY.left = MIN(ptTemp.X , dbRectXY.left) ;
        dbRectXY.right = MAX(ptTemp.X , dbRectXY.right) ;
        dbRectXY.bottom = MIN(ptTemp.Y , dbRectXY.bottom) ;
        dbRectXY.top = MAX(ptTemp.Y , dbRectXY.top) ;
    }
    //--------------------------------------------
    DOUBLE dXRange = dbRectXY.right - dbRectXY.left;
    DOUBLE dYRange = dbRectXY.top - dbRectXY.bottom;

    UINT nW = UINT( 1 + ( dXRange ) / dInterVal );
    UINT nH = UINT( 1 + ( dYRange ) / dInterVal );

    UINT nGridSize = nW * nH;

    UINT nBlockH  = DEM_BLOCK_SIZE / nW;

    UINT nBlockNum =  nH / nBlockH;
    if( 0 !=  nH % nBlockH )
    {
        nBlockNum++;
    }

    for( UINT i = 0; i < nBlockNum; ++i )
    {
        UINT nTmpW = nW;
        UINT nTmpH = nBlockH;
        if( i == nBlockNum - 1 )
        {
            nTmpH = nH - i * nBlockH;
        }
        Pt2d ptOrig;
        ptOrig.X = dbRectXY.left;
        ptOrig.Y = dbRectXY.bottom + i * nBlockH;
        UINT* pIdxGrid = new UINT[nTmpW*nTmpH];
        UINT nS = nTmpH * nTmpW;
        for( UINT k = 0; k < nS; ++k )
        {
            pIdxGrid[k] = UINT(-1);
        }
        for( UINT k = 0; k < vec3DPts.size(); ++k )
        {
            Pt3d ptTmp = vec3DPts[k];
            UINT nIdxX = UINT(( ptTmp.X - ptOrig.X ) / dInterVal);
            UINT nIdxY = UINT(( ptTmp.Y - ptOrig.Y ) / dInterVal);
            UINT nCurIdx = nIdxY*nTmpW+nIdxX;
            if( nCurIdx < nS )
            {
                pIdxGrid[nCurIdx] = k;
            }

        }
        for( UINT k = 0; k < nS; ++k )
        {
            if( pIdxGrid[k] != UINT(-1))
            {
                vecFlags.push_back( pIdxGrid[k] );
            }
        }
        delete[] pIdxGrid;
    }

    vector<Pt3d> vecPts;
    for( UINT i = 0; i < vecFlags.size(); ++i )
    {
        vecPts.push_back( vec3DPts[vecFlags[i]] );
    }
    vec3DPts = vecPts;

    return true;
}
/**
 * @fn SmoothBySmoothFilter()
 * @date 2011.11.02
 * @author �⿭ wukai@irsa.ac.cn
 * @brief demƽ���˲�
 * @param nGridSize �˲�ģ���С
 * @param nW dem��Ӧ������
 * @param nH dem��Ӧ������
 * @param *pDem �������dem�߳�����
 * @retval TRUE �ɹ�
 * @retval FALSE ʧ��
 * @version 1.0
 * @par �޸���ʷ��
 * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
bool CmlDemProc::SmoothBySmoothFilter(int nGridSize , int nW , int nH , double* pDem)
{
    double *pNewData = new double[nW * nH];
    memcpy( pNewData, pDem, nH*nW*sizeof(double) );
    int nTemp = nGridSize / 2; // ��ֵ�˲��뾶

    vector<double> vecMidFilter ;
//    SINT nCount = 0 ;
    // ���α���DEMդ������� �� �����ڽ�һ����Χ�ĵ�ƽ��
    for ( int i = nH - 1 - nTemp; i >= nTemp; --i )
    {
        for ( int j = nTemp; j < nW - nTemp; ++j )
        {
            double* pData = pDem + i * nW + j;
            double* pTempNewData = pNewData + i * nW + j;
            // ԭdemդ���ʱ��ֱֵ�ӷ���
            if ( *pData == DEM_NO_DATA )
            {
                continue;
            }
            double dTotal = 0;
            long nFlag = 0;
            for ( int h = -nTemp; h <= nTemp; ++h )
            {
                for ( int k = -nTemp; k <= nTemp; ++k )
                {
                    // ���������� ��������
                    if ( ( h == 0 )||( k == 0 ) )
                    {
                        continue;
                    }
                    double* pTempData = pData + h * nW +  k ;
                    if ( *pTempData == DEM_NO_DATA )
                    {
                        continue;
                    }
                    vecMidFilter.push_back(*pTempData) ;
                    dTotal += *pTempData;
                    nFlag++;
                }
            }

            // �õ���ƽ��ֵ
            if(nFlag)
            {
                *pTempNewData = dTotal/nFlag ;
            }
        }
    }
    for ( int i = nH - 1 - nTemp; i >= nTemp; --i )
    {
        for ( int j = nTemp; j < nW - nTemp; ++j )
        {
            double* pData = pDem + i * nW + j;
            double* pTempNewData = pNewData + i * nW + j;
            *pData = *pTempNewData;
        }
    }
    if(pNewData)
    {
        delete [] pNewData ;
    }
    return TRUE;
}











