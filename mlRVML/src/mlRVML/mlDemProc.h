/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlDemProc.h
* @date 2011.12.18
* @author �⿭  wukai@irsa.ac.cn
* @brief  ��վ����dem���ɹ���ģ����ͷ�ļ�(�������ӽ��µ�������)
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef MLDEMPROC_H
#define MLDEMPROC_H

#include "mlTypes.h"
#include "mlKringing.h"
#include "mlGeoRaster.h"

#define  DEM_NO_DATA  9999999999

class CmlDemProc //: public CmlRasterProc
{
public:
    vector<Pt3d> m_vec3DPts ;  // 3ά����
    vector<Pt3d> vecAddPts ;   // �տ�������
    vector<Pt2d> m_vecHoles ; // ��վ�ն�
    vector<Polygon3d> m_vecRegions;
    DbRect m_dbDemRect ;  // ָ��DEM��Χ
    DOUBLE m_dDemRes ; //DEM�ֱ���
    ULONG  m_lPtsNum ; // ��������
    DbRect m_dbRectXY ; // ����DEM�ĵ���XY�ֲ���Χ
    DbRect m_dbRectZ ; // ����DEM�ĵ���Z�ֲ���Χ
    CmlTIN* m_pTin ;  // ������Tin����
    SINT nNumTriangle ; // �����������θ���
    triangulateio* m_pTri ; // DEM���ƹ�����Tin�ṹ
    SINT m_nGlobalW ; // ȫ��DEM���
    SINT m_nGlobalH ; // ȫ��DEM�߶�
    SINT m_nW ; // DEM���
    SINT m_nH ; // DEM�߶�
    SINT  m_nBlockNum ; // �ֿ���
    DOUBLE m_dScale ; // ������������ϵ��
public:
    /**
     *@fn CmlDemProc()
     *@date 2011.11
     *@author �⿭
     *@brief DEM�����๹�캯��
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    CmlDemProc();

    /**
     *@fn ��CmlDemProc()
     *@date 2011.11
     *@author �⿭
     *@brief DEM��������������
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    virtual ~CmlDemProc();

    /**
     *@fn Resample()
     *@date 2011.11
     *@author �⿭
     *@brief �ز�������
     *@param nType ��������
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    virtual bool Resample(SINT nType);

    // �ӿں�����
public:
    /**
    * @fn
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
    bool mlWriteToGeoFile(vector<Pt3d>& vec3DPts , DbRect dbDemRect , DOUBLE dRes , const SCHAR* strGeoFilePath, ImgDotType imgType = T_Float64, string strTriFile = "" ) ;


    bool mlWriteRegionToGeoFile(vector<Pt3d>& vec3DPts , DbRect dbDemRect , DOUBLE dRes , vector<Polygon3d> &vecRegions, const SCHAR* strGeoFilePath, ImgDotType imgType = T_Float64, string strTriFile = "" ) ;
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
    bool mlWriteToGeoFile(vector<Pt3d>& vec3DPts , DOUBLE dRes , const SCHAR* strGeoFilePath ) ;

	bool mlWriteToGeoFile(vector<Pt3d>& vec3DPts , DOUBLE dRes , const SCHAR* strGeoFilePath, ImgDotType imgType, string strTriFile ) ;

private:
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
    bool getRangeFromPts(vector<Pt3d>& vec3DPts, DbRect dbDemRect) ; // ȷ���ƶ�dem��Χ�Ĳ�����Ϣ
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
    bool getRangeFromPts(vector<Pt3d>& vec3DPts) ;  // ȷ��dem������Ϣ
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
//    bool mlCreateRasterFrom3DPts() ;
    bool createRasterFrom3DPts(CmlTIN* pTin , CmlKringing* pKring , DbRect dbDemRect , SINT nW , SINT nH , double* pDem) ;

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
    bool delDulPts(vector<Pt3d>& vec3DPts) ;

    bool delDulPtsByIdx(vector<Pt3d>& vec3DPts) ;

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
    bool denseGridPts(vector<Pt3d>& vec3DPts , DbRect dbDemRect , double dDemTopRes , int nParamidNum , int nParamidRatio) ;

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
    bool densePartion3DPts(vector<Pt3d>& vec3DPts , CmlTIN* pTin , CmlKringing* pKring , SINT nPyramidRatio);
    /**
     * @fn SmoothBySmoothFilter()
     * @date 2011.11.02
     * @author �⿭ wukai@irsa.ac.cn
     * @brief dem ƽ���˲�
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
    bool SmoothBySmoothFilter(int nGridSize , int nW , int nH , double* pDem) ;
};

#endif // MLDEMPROC_H
