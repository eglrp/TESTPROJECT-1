/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlLocalization.h
* @date 2011.12.18
* @author ���Ļ� whwan@irsa.ac.cn
* @brief  ��λ������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef CMLLOCALIZATION_H
#define CMLLOCALIZATION_H

#include "mlBase.h"
#include "mlRasterBlock.h"
/**
* @struct tagGCPPt
* @date 2011.12.18
* @author ���Ļ�
* @brief ���Ƶ���Ϣ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagGCPPt
{
    ULONG nID;//!<���Ƶ��ID
    Pt3d ptXYZ;//!<���Ƶ������
} GCPoint;



class CmlLocalization
{
public:
    /**
    * @fn CmlLocalization
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlLocalization��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlLocalization();

    /**
    * @fn ~CmlLocalization
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlLocalization����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual ~CmlLocalization();

    /**
    * @fn LocalInSequenceImg
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief LocalInSequenceImg ����Ӱ��λ
    * @param strSatPath Ӱ��·��
    * @param vecFrameInfo Ӱ�����
    * @param ptLocalRes ��λ���
    * @param dLocalAccuracy ��λ����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool LocalInSequenceImg(  FrameImgInfo FrameInfoSet, const SCHAR* strSatDom, ImgPtSet &frmPts, ImgPtSet &SatPts, LocalBySeqImgOpts stuLocalBySeqOpts, Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );

    /**
    * @fn LocalByBundleResection
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��Ƭ�󷽽���ʵ�ֶ�λ
    * @param vecGCPs ���Ƶ�����
    * @param vecImgPtSets �������
    * @param ptLocalRes ��λ���
    * @param dLocalAccuracy ��λ����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool LocalByBundleResection( vector<Pt3d> vecGCPs, vector< ImgPtSet > &vecImgPtSets,  Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy);


    /**
    * @fn LocalBySImgIntersection
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��Ƭ�󷽽���ʵ�ֶ�λ
    * @param[in] vecGCPs ���Ƶ�����
    * @param[in] vecImgPtSets �������(��ƽ������ϵ)
    * @param[out] exOriRes ��λ����ⷽλԪ��
    * @param[out] vecRMSRes �����
    * @param[out] dTotalRMS �����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool LocalBySImgIntersection( vector<Pt3d> vecGCPs, ImgPtSet imgPts,  ExOriPara &exOriRes, vector<RMS2d> &vecRMSRes, DOUBLE &dTotalRMS  );

    /**
    * @fn LocalIn2Dom
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ӱ��͵���Ӱ���ƥ��ʵ�ֶ�λ
    * @param strLandDom ����Ӱ���ļ�·��
    * @param strSatDom ����Ӱ��ƥ�������
    * @param landPtSet ����Ӱ��ƥ�������
    * @param satPtSet ����Ӱ��ƥ�������
    * @param localByMOpts ��λ����
    * @param ptLocalRes ��λ���
    * @param dLocalAccuracy ��λ����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool LocalIn2Dom(  const char* strLandDom, const char* strSatDom, ImgPtSet &landPtSet, ImgPtSet &satPtSet, LocalByMatchOpts localByMOpts, Pt2d ptCent, Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );

    /**
    * @fn LocalInTwoSite
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief վ���Ӱ��λ
    * @param vecFSite ǰվ������Ӱ��
    * @param vecESite ��վ������Ӱ��
    * @param vecFrontPts ǰվ������ƥ���
    * @param vecEndPts ��վ������ƥ���
    * @param stulocalBy2Opt ��λ����
    * @param ptLocalRes ��λ���
    * @param dLocalAccuracy ��λ����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool LocalInTwoSite( vector<StereoSet> vecFSite, vector<StereoSet> vecESite, vector<ImgPtSet> &vecFrontPts, vector<ImgPtSet> &vecEndPts, LocalBy2SitesOpts stulocalBy2Opt, Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );

    /**
    * @fn LocalByLander
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���õر�Ķ�λ
    * @param vecFSite վ������Ӱ��
    * @param strGCPFile �ر������
    * @param ptLocalRes ��λ���
    * @param dLocalAccuracy ��λ����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool LocalByLander( const vector<StereoSet> &vecFSite, const SCHAR* strGCPFile, Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );

    /**
    * @fn WriteLocalRes
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief д����λ��Ϣ
    * @param strPath ����ļ�·��
    * @param localRes ��λ����̬��Ϣ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool WriteLocalRes( const SCHAR* strPath, ExOriPara localRes );

    /**
    * @fn WriteLocalRes
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief д����λ��Ϣ
    * @param strPath ����ļ�·��
    * @param ptlocalRes ��λ����Ϣ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool WriteLocalRes( const SCHAR* strPath, Pt3d ptlocalRes );

    /**
    * @fn GetImgIDIn2Site
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Ӱ���ID��
    * @param vecFSite ǰվӰ��
    * @param vecESite ��վӰ��
    * @param nFID ǰվӰ���ID��
    * @param nEID ��վӰ���ID��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool GetImgIDIn2Site(  const vector<StereoSet> &vecFSite, const vector<StereoSet> &vecESite, UINT &nFID, UINT &nEID );

    bool GetImgIDIn2SiteReverse(  const vector<StereoSet> &vecFSite, const vector<StereoSet> &vecESite, UINT &nFID, UINT &nEID );
    /**
    * @fn removePtsByDisConsistant
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ͨ���Ӳһ����ȥ������ƥ���
    * @param vecPtsInFrontFrm ǰ֡Ӱ���ȡ����ά������
    * @param ptFOrig ��ʼ֡��ά����
    * @param vecPtsInEndFrm ���֡Ӱ���ȡ����ά������
    * @param ptEOrig ����֡��ά����
    * @param dThreCoef ���ϵ����ֵ
    * @param vecFlags ��ʶ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool removePtsByDisConsistant( vector<Pt3d> vecPtsInFrontFrm, Pt3d ptFOrig, vector<Pt3d> vecPtsInEndFrm, Pt3d ptEOrig, DOUBLE dDisThreCoef, DOUBLE dWeightThreCoef, vector<bool> &vecFlags );


    bool getInsterestRegion( StereoSet sFirstSet, StereoSet sSecondSet, DOUBLE dCamHeight, DOUBLE dFirstSiteRange, DOUBLE dSecondSiteRange, vector<Pt2d> &vecL, vector<Pt2d> &vecR, SINT nNumTilts = 8 );

//    bool getInsterestRegionReverse( StereoSet sFirstSet, StereoSet sSecondSet, DOUBLE dCamHeight, DOUBLE dFirstSiteRange, DOUBLE dSecondSiteRange, vector<Pt2d> &vecL, vector<Pt2d> &vecR, SINT nNumTilts = 8 );


    bool CalcTwoSitesByBA( vector<Pt2d> vecPtsOneL, vector<Pt2d> vecPtsOneR, vector<Pt2d> vecPtsTwoL, vector<Pt2d> vecPtsTwoR, vector<Pt3d> vecXYZ, \
                           StereoSet sFirstSet, StereoSet sSecondSet, ExOriPara &exTwoL, ExOriPara &exTwoR );
protected:
private:
    /**
    * @fn loadGCPFile
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ������Ƶ��ļ�
    * @param strGCPFile ���Ƶ��ļ�·��
    * @param vecGCPs ���Ƶ���Ϣ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool loadGCPFile( const SCHAR* strGCPFile, vector<GCPoint> &vecGCPs );

    /**
    * @fn loadMarkedPtFile
    * @date 2011.12.16
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �����־���ļ�
    * @param clsImgPtSets Ӱ��վ����Ϣ
    * @param mapPts Ͷ���
    * @param frameInfo Ӱ����Ϣ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool loadMarkedPtFile( ImgPtSet clsImgPtSets, map<ULONG, Pt2d> &mapPts, FrameImgInfo &frameInfo );


    bool DealImgSelectionIn2Sites( vector<ExOriPara> vecSiteOne, vector<ExOriPara> vecSiteTwo, UINT nIDOne, UINT nIDTwo );
};

#endif // CMLLOCALIZATION_H
