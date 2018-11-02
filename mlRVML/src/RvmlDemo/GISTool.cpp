/************************************************************
  Copyright (C), 2011-2012, PMRS Lab, IRSA, CAS
  �ļ�����: GISTool.cpp
  ��������: 2011.11.6
  ��    ��: ��Ρ
  ��    ��: ���η�������
  �汾��ţ�1.0
  �޸���ʷ:   <����>   <ʱ��>   <�汾���>   <����>

***********************************************************/

#include "GISTool.h"

CPL_CVSID("$Id: gdal_contour.cpp 21191 2010-12-03 20:02:34Z rouault $");

/*************************************************
  ��������:    mlComeputeContour
  ��    ��:   ��Ρ
  ����������   �ȸ�������
  ��    �룺
  ����1���ȸ߾�
  ����2��DEM�ļ�·��
  ����3�������shape�ļ�·��
  ����4���Ƿ��Զ���Nodata
  ����5�����bCNodata����Ϊtrue����dNodata ��ֵ�ڼ���ʱ��������Чֵ�Դ�
  ����6������shape�ļ��̵߳��������ƣ�Ĭ��Ϊelev
  ��    ���� ����ֵ��1������ִ�У�-1��gdal�汾���ͣ�-2���ȸ߾���������-3�������ļ�������-4 ������ļ�������
  �汾��ţ�   1.0
  �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
  *************************************************/
int mlComeputeContour(double dHinterval, char* strSrcfilename, char* strDstfilename ,bool bCNodata , double dNodata ,char* strAttrib )
{
    GDALDatasetH	hSrcDS;
    int b3D = FALSE, bIgnoreNoData = FALSE;
    int bNoDataSet = bCNodata;
    int nBandIn = 1;
    double dfNoData = dNodata;
    double dfInterval = 0.0,dfOffset = 0.0;
    const char *pszSrcFilename = NULL;
    const char *pszDstFilename = NULL;
    const char *pszElevAttrib = NULL;
    const char *pszFormat = "ESRI Shapefile";
    double adfFixedLevels[1000];
    int    nFixedLevelCount = 0;
    const char *pszNewLayerName = "contour";
    int bQuiet = FALSE;
    GDALProgressFunc pfnProgress = NULL;

    /* Check that we are running against at least GDAL 1.4 */
    /* Note to developers : if we use newer API, please change the requirement */
    if (atoi(GDALVersionInfo("VERSION_NUM")) < 1400)
    {
        // gdal �汾����
        return -1;
    }

    GDALAllRegister();
    OGRRegisterAll();

    pszElevAttrib = strAttrib;
    dfInterval = dHinterval;
    if( dfInterval == 0.0 && nFixedLevelCount == 0 )
    {
        // �ȸ߾�Ϊ��
       return -2;
    }
    pszSrcFilename = strSrcfilename;
    if (pszSrcFilename == NULL)
    {
        //  Դ�ļ���������
        return -3;
    }
    pszDstFilename = strDstfilename;
    if (pszDstFilename == NULL)
    {
        // Ŀ���ļ���������
        return -4;
    }

    if (!bQuiet)
    {
        pfnProgress = GDALTermProgress;
    }


/* -------------------------------------------------------------------- */
/*      Open source raster file.                                        */
/* -------------------------------------------------------------------- */
    GDALRasterBandH hBand;
    hSrcDS = GDALOpen( pszSrcFilename, GA_ReadOnly );
    if( hSrcDS == NULL )
    {
        // Դ�ļ���������
        return -3;
    }
    nBandIn = 1;
    hBand = GDALGetRasterBand( hSrcDS, nBandIn );
    if( hBand == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Band %d does not exist on dataset.",
                  nBandIn );
                // Դ�ļ���������
        return -3;
    }
    if( !bNoDataSet && !bIgnoreNoData )
    {
        dfNoData = GDALGetRasterNoDataValue( hBand, &bNoDataSet );
    }

/* -------------------------------------------------------------------- */
/*      Try to get a coordinate system from the raster.                 */
/* -------------------------------------------------------------------- */
    OGRSpatialReferenceH hSRS = NULL;

    const char *pszWKT = GDALGetProjectionRef( hSrcDS );

    if( pszWKT != NULL && strlen(pszWKT) != 0 )
    {
        hSRS = OSRNewSpatialReference( pszWKT );
    }
/* -------------------------------------------------------------------- */
/*      Create the outputfile.                                          */
/* -------------------------------------------------------------------- */
    OGRDataSourceH hDS;
    OGRSFDriverH hDriver = OGRGetDriverByName( pszFormat );
    OGRFieldDefnH hFld;
    OGRLayerH hLayer;

    hDS = OGR_Dr_CreateDataSource( hDriver, pszDstFilename, NULL );
    if( hDS == NULL )
    {
        // Ŀ���ļ���������
        return -4;
    }


    hLayer = OGR_DS_CreateLayer( hDS, pszNewLayerName, hSRS,
                                 b3D ? wkbLineString25D : wkbLineString,
                                 NULL );
    if( hLayer == NULL )
    {
        // Ŀ���ļ�������
        return -4;
    }

    hFld = OGR_Fld_Create( "ID", OFTInteger );
    OGR_Fld_SetWidth( hFld, 8 );
    OGR_L_CreateField( hLayer, hFld, FALSE );
    OGR_Fld_Destroy( hFld );

    if( pszElevAttrib )
    {
        hFld = OGR_Fld_Create( pszElevAttrib, OFTReal );
        OGR_Fld_SetWidth( hFld, 12 );
        OGR_Fld_SetPrecision( hFld, 3 );
        OGR_L_CreateField( hLayer, hFld, FALSE );
        OGR_Fld_Destroy( hFld );
    }

/* -------------------------------------------------------------------- */
/*      Invoke.                                                         */
/* -------------------------------------------------------------------- */
    CPLErr eErr;

    eErr = GDALContourGenerate( hBand, dfInterval, dfOffset,
                         nFixedLevelCount, adfFixedLevels,
                         bNoDataSet, dfNoData, hLayer,
                         OGR_FD_GetFieldIndex( OGR_L_GetLayerDefn( hLayer ),
                                               "ID" ),
                         (pszElevAttrib == NULL) ? -1 :
                                 OGR_FD_GetFieldIndex( OGR_L_GetLayerDefn( hLayer ),
                                                       pszElevAttrib ),
                         pfnProgress, NULL );

    OGR_DS_Destroy( hDS );
    GDALClose( hSrcDS );

    if (hSRS)
    {
        OSRDestroySpatialReference( hSRS );
    }
    GDALDestroyDriverManager();
    OGRCleanupAll();
    return 1;
}



