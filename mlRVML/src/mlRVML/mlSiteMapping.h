/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlSiteMapping.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief վ����ν���ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef CMLSITEMAPPING_H
#define CMLSITEMAPPING_H

#include "mlBase.h"
#include "mlGeoRaster.h"
#include "mlDemProc.h"
#include "mlDomProc.h"
/**
* @class CmlSiteMapping
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��վ���ν�����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlSiteMapping
{
public :
    DbRect m_dbDemRect ;  //!< ָ��DEM��Χ
    DOUBLE m_dDemRes ; //!<DEM�ֱ���
    UINT m_nW ;//!<DEM��
    UINT m_nH ;//!<DEM��
//    CmlDemProc demProc ;
public:
    /**
        * @fn CmlSiteMapping
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief CmlSiteMapping��ղι��캯��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
    CmlSiteMapping();
    /**
        * @fn ~CmlSiteMapping
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief CmlSiteMapping����������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
    virtual ~CmlSiteMapping();
//    /**
//    * @fn mlSiteParaInit
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ��վ���ν���������ʼ��
//    * @param dbRect �ļ�·��
//    * @param dRes �ֱ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool mlSiteParaInit(DbRect dbRect , DOUBLE dRes) ;
    /**
    * @fn MapByMultiBlock
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief Ӱ���ֱ���ͼ�ϳ�
    * @param vecStereoSet ����Ӱ��������Ϣ
    * @param vecStrMatchFile ƥ����ļ�
    * @param ptLT ��ͼ�������Ͻ�����
    * @param ptRB ��ͼ�������½�����
    * @param dResolution �ֱ���
    * @param strDemPath Dem����·��
    * @param strDomPath Dom����·��
    * @param bIsUsingFeatPt �ж��Ƿ�ʹ��ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

    bool MapByMultiBlock(  vector<StereoSet> &vecStereoSet, vector<string> &vecStrMatchFile, Pt2d ptLT, Pt2d ptRB, DOUBLE dResolution,
                           string strDemPath, string strDomPath, bool bIsUsingFeatPt = true );
    /**
    * @fn MapByInteBlock
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��վһ�廯��ͼ
    * @param vecStereoSet ����Ӱ��������Ϣ
    * @param vecImgPtSets ƥ���
    * @param ptLT ��ͼ�������Ͻ�����
    * @param ptRB ��ͼ�������½�����
    * @param dResolution �ֱ���
    * @param strDemPath Dem����·��
    * @param strDomPath Dom����·��
    * @param bIsUsingFeatPt �ж��Ƿ�ʹ��ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool MapByInteBlock(   vector<StereoSet> &vecStereoSet, vector< ImgPtSet > &vecImgPtSets, Pt2d ptLT, Pt2d ptRB, DOUBLE dResolution,\
                            ExtractFeatureOpt extractPtsOpts, MatchInRegPara matchOpts, RANSACHomePara ransacOpts, MedFilterOpts mFilterOpts, \
                           string strDemPath, string strDomPath, bool bIsUsingFeatPt = true );
//     /**
//    * @fn DisMapByMultiBlock
//    * @date 2011.11.02
//    * @author �틠 pengman@irsa.ac.cn
//    * @brief Ϊ�����Ӳ�ͼ�����ܼ�ƥ��
//    * @param vecStereoSet ����Ӱ��������Ϣ
//    * @param vecStrMatchFile ƥ����ļ�
//    * @param nGrid �Ӳ�ͼ���ɸ�����С
//    * @param nRowRadius �з��������뾶
//    * @param nColRadius �з��������뾶
//    * @param nTempleSize ģ���С
//    * @param strDisPath �Ӳ�ͼ����·��
//    * @param bIsUsingFeatPt �ж��Ƿ�ʹ��ƥ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
    //bool DisMapByBlock( vector<StereoSet> &vecStereoSet, vector<string> &vecStrMatchFile);
    /**
    * @fn MapByOneSite
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��վ������ͼ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool MapByOneSite( );
    /**
    * @fn GetStereoFeatPts
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ӱ���������ƥ�䣬������ά���ƣ������ļ�
    * @param pStereoSet ����Ӱ��������Ϣ
    * @param clsImgPtL ��Ӱ��ƥ���
    * @param clsImgPtR ��Ӱ��ƥ���
    * @param vecPt3ds ��ά����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool GetStereoFeatPts( StereoSet* pStereoSet, \
                           ExtractFeatureOpt extractPtsOpts, MatchInRegPara matchOpts, RANSACHomePara ransacOpts, MedFilterOpts mFilterOpts, \
                          ImgPtSet &clsImgPtL, ImgPtSet &clsImgPtR, vector<Pt3d> &vecPt3ds, Pt3d &ptMinDis );
//    /**
//    * @fn GetStereoDensePts
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ����Ӱ���������ƥ�䣬�ܼ�ƥ�䣬������ά���ƣ������ļ�
//    * @param pStereoSet ����Ӱ��������Ϣ
//    * @param strLPtPath ��Ӱ��ƥ����ļ�·��
//    * @param strRPtPath ��Ӱ��ƥ����ļ�·��
//    * @param vecPt3ds ��ά����
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
    bool GetStereoDensePts( StereoSet* pStereoSet, string strLPtPath, string strRPtPath, vector<Pt3d> &vecPt3ds, UINT nGrid, UINT nRowRadius,UINT nColRadius,UINT nTempleSize,DOUBLE dCoef );
    /**
    * @fn GetStereoDensePts
    * @date 2011.11.02
    * @author �틠
    * @brief ����Ӱ���������ƥ�䣬�ܼ�ƥ�䣬������ά���ƣ������ļ�
    * @param pStereoSet ����Ӱ��������Ϣ
    * @param WidePara ����Ӱ��ƥ�����
    * @param ptSetL ��Ӱ���ܼ�ƥ���
    * @param ptSetR ��Ӱ���ܼ�ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool GetStereoDensePts( StereoSet* pStereoSet,  WideOptions WidePara, ImgPtSet& ptSetL, ImgPtSet& ptSetR );

    /**
    * @fn GetStereoDensePts
    * @date 2011.11.02
    * @author �틠
    * @brief ����Ӱ���������ƥ�䣬�ܼ�ƥ�䣬������ά���ƣ������ļ�
    * @param pStereoSet ����Ӱ��������Ϣ
    * @param WidePara ����Ӱ��ƥ�����
    * @param ptfSetL ��Ӱ������ƥ���
    * @param ptfSetR ��Ӱ������ƥ���
    * @param ptSetL ��Ӱ���ܼ�ƥ���
    * @param ptSetR ��Ӱ���ܼ�ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool GetStereoDensePts( StereoSet* pStereoSet,  WideOptions WidePara, ImgPtSet& ptfSetL, ImgPtSet& ptfSetR ,ImgPtSet& ptSetL, ImgPtSet& ptSetR );
/**
* @fn GetRegionDensePts
* @date 2011.12.14
* @author �틠 pengman@irsa.ac.cn
* @brief Ӱ��ָ�������ܼ�ƥ��
* @param[in] pStereoSet �������
* @param[in] GauPara ��˹�˲�����
* @param[in] ExtractPara ��������ȡ����
* @param[in] MatchPara ������ƥ�����
* @param[in] RanPara RANSACȥ�ֲ����
* @param[in] RectSearch ģ��ƥ��������Χ����
* @param[in] WidePara �ܼ�ƥ�����
* @param[in] Lx ��ƥ����Ӱ��ָ�����η�Χ�����Ͻ�x����
* @param[in] Ly ��ƥ����Ӱ��ָ�����η�Χ�����Ͻ�y����
* @param[in] ColRange ��ƥ����Ӱ��ָ�����η�Χ�Ŀ�
* @param[in] RowRange ��ƥ����Ӱ��ָ�����η�Χ�ĸ�
* @param[out] vecDPtSetL �ܼ�ƥ�����Ӱ�������
* @param[out] vecDPtSetR �ܼ�ƥ�����Ӱ�������
* @param[out] vecPtObj �ܼ�ƥ��ĵ����ά����
* @param[out] vecCorr �ܼ�ƥ������ϵ��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool GetRegionDensePts( StereoSet* pStereoSet, GaussianFilterOpt GauPara, ExtractFeatureOpt ExtractPara, MatchInRegPara MatchPara, RANSACHomePara RanPara, MLRectSearch RectSearch, WideOptions WidePara, SINT Lx, SINT Ly, SINT ColRange, SINT RowRange,
                                   ImgPtSet& ptSetL, ImgPtSet& ptSetR, vector<Pt3d>& vecPtObj, vector<DOUBLE>& vecCorr);
    bool WriteDisMap(vector<Pt3d> vecPt3ds, char* DisPath);

    bool GetRegionDensePts( StereoSet* pStereoSet, vector<StereoMatchPt> vecFeatMatchPt, WideOptions WidePara, SINT Lx, SINT Ly, SINT ColRange, SINT RowRange,
                                  ImgPtSet& ptSetL, ImgPtSet& ptSetR, vector<Pt3d>& vecPtObj, vector<DOUBLE>& vecCorr);

    bool BA( vector<StereoSet> vecStereoSetIn, vector< ImgPtSet > &vecImgPtSets, \
                            ExtractFeatureOpt extractPtsOpts, MatchInRegPara matchOpts, RANSACHomePara ransacOpts, MedFilterOpts mFilterOpts, \
                           vector<StereoSet> &vecStereoOut );

    bool FindTiePoints( vector<StereoSet> vecStereoSetIn, vector< ImgPtSet > &vecImgPtSets, \
                            ExtractFeatureOpt extractPtsOpts, MatchInRegPara matchOpts, RANSACHomePara ransacOpts, MedFilterOpts mFilterOpts );

    bool BASolve( vector<StereoSet> vecStereoIn, vector<ImgPtSet> vecImgPtSets, vector<StereoSet> &vecStereoOut, UINT nModel = 2 );

    bool BASolve( vector<StereoSet> vecStereoIn, vector<ImgPtSet> vecImgPtSets, vector<StereoSet> &vecStereoOut, Pt2d &ptProjErr, UINT nModel = 2 );

    bool BASolve( vector<StereoSet> vecStereoIn, vector<ImgPtSet> vecImgPtSets, vector<bool> vecbImgIsFixed, vector<StereoSet> &vecStereoOut, UINT nModel = 1 );
public:
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author �⿭ wukai@irsa.ac.cn
//    * @brief ��ά��������ָ����ΧDEM��������geotiff�ļ�
//    * @param vec3DPts ��ά����
//    * @param strGeoFilePath �ļ�·��
//    * @param dbDemRect DEM���ɷ�Χ
//    * @param dRes DEM�ֱ���
//    * @param bType �Ƿ��޳��ֲ��
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool mlWriteToGeoFile(vector<Pt3d>& vec3DPts , SCHAR* strGeoFilePath , DbRect dbDemRect , DOUBLE dRes = 1.0 , delErrorType bType = delOff) ;
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author �⿭ wukai@irsa.ac.cn
//    * @brief ��ά����ȫ������DEM��������geotiff�ļ�
//    * @param vec3DPts ��ά����
//    * @param strGeoFilePath �ļ�·��
//    * @param dRes DEM�ֱ���
//    * @param bType �Ƿ��޳��ֲ��
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool mlWriteToGeoFile(vector<Pt3d>& vec3DPts , SCHAR* strGeoFilePath , DOUBLE dRes = 1.0 , delErrorType bType = delOff) ;
    //�ֿ�д�뵽geoTiff�ļ�
//    bool mlWriteToGeoFile(vector<Pt3d>& vec3DPts , SINT nXOrigin , SINT nYOrigin , SINT nBlockWidth , SINT nBlockHeight , SCHAR* strGeoFilePath) ;
protected:
private:
//      /**
//    * @fn getRangeFromPts
//    * @date 2011.11.02
//    * @author �⿭ wukai@irsa.ac.cn
//    * @brief ������ά���Ʒ�Χ
//    * @param vec3DPts ��ά����
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//  bool getRangeFromPts(vector<Pt3d>& vec3DPts) ;
    /**
        * @fn paraInit
        * @date 2011.11.02
        * @author �⿭ wukai@irsa.ac.cn
        * @brief ������ʼ��
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
    bool paraInit() ;

    bool judgeIsOverlap( FrameImgInfo *pSet1, FrameImgInfo *pSet2, DOUBLE &dXOff, DOUBLE &dYOff  );
};

#endif // CMLSITEMAPPING_H
