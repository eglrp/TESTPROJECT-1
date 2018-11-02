/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlStereoProc.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ����ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef CMLSTEREOPROC_H
#define CMLSTEREOPROC_H

#include "mlBase.h"
#include "mlGdalDataset.h"

//����ά��ṹ��������������Ӱ��㣬��Ӱ��㣨���ߵ�ṹ��

/**
* @class CmlStereoProc
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ������
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlStereoProc
{
public:
    /**
    * @fn CmlStereoProc
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlStereoProc��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlStereoProc();
    /**
    * @fn CmlStereoProc
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlStereoProc���вι��캯��
    * @param m_pDataL ��Ӱ��
    * @param m_pDataR ��Ӱ��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlStereoProc( CmlGdalDataset* m_pDataL, CmlGdalDataset* m_pDataR );
    /**
    * @fn ~CmlStereoProc
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlStereoProc����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual ~CmlStereoProc();
    /**
    * @fn mlGetRansacPts
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ransac�����޳�����ƥ���ֲ�
    * @param MatchPts ���������ƥ���
    * @param RanSacPts ���������ƥ���
    * @param dThresh ��ֵ
    * @param dConfidence ���Ŷ�
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlGetRansacPts(vector<StereoMatchPt> &MatchPts, vector<StereoMatchPt> &RanSacPts, DOUBLE dThresh = 3, DOUBLE dConfidence = 0.99 );
    /**
    * @fn mlGetRansacPts
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ransac�����޳�����ƥ���ֲ�
    * @param MatchPts ����ƥ���
    * @param dThresh ��ֵ
    * @param dConfidence ���Ŷ�
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlGetRansacPts(vector<StereoMatchPt> &MatchPts, DOUBLE dThresh = 3, DOUBLE dConfidence = 0.99 );
    /**
    * @fn mlGetRansacPtsByAffineT
    * @date 2011.11.02
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����Ransac��������任ģ���޳�����ƥ���ֲ�
    * @param vxl ��Ӱ��ƥ���X
    * @param vyl ��Ӱ��ƥ���y
    * @param vxr ��Ӱ��ƥ���x
    * @param vyr ��Ӱ��ƥ���y
    * @param RanSacPts ���������ƥ���
    * @param dSigma ������ֵ
    * @param dConfidence ��С��������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    SINT mlGetRansacPtsByAffineT(vector<DOUBLE> vxl, vector<DOUBLE> vyl, vector<DOUBLE> vxr, vector<DOUBLE> vyr,\
                                 vector<StereoMatchPt> &RanSacPts, DOUBLE dSigma, UINT nMinItera );

    /**
    * @fn mlGetRansacPts
    * @date 2012.2.10
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����Ransac�����޳�����ƥ���ֲ�
    * @param vxl ��Ӱ��ƥ���X
    * @param vyl ��Ӱ��ƥ���y
    * @param vxr ��Ӱ��ƥ���x
    * @param vyr ��Ӱ��ƥ���y
    * @param LRanPts �޳��ֲ����Ӱ��ƥ���
    * @param RRanPts �޳��ֲ����Ӱ��ƥ���
    * @param dThresh ��ֵ
    * @param dConfidence ���Ŷ�
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlGetRansacPts( vector<DOUBLE> vxl, vector<DOUBLE> vyl, vector<DOUBLE> vxr, vector<DOUBLE> vyr,\
                         vector<StereoMatchPt> &vecRanPts, DOUBLE dThresh, DOUBLE dConfidence );

    /**
    * @fn mlGetRansacPtsByAffineT
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ransac�����޳�����ƥ���ֲ�
    * @param MatchPts ����ƥ���
    * @param RanSacPts ȥ���ֲ���
    * @param nMinLierSetNum ��С�ڵ㼯����
    * @param dMaxError ������
    * @return  ȥ���ֲ���ĸ���
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlGetRansacPtsByAffineT( vector<StereoMatchPt> &MatchPts, vector<StereoMatchPt> &RanSacPts, DOUBLE dSegma, DOUBLE dMaxError );

    bool mlGetRansacPtsByAffineT( vector<StereoMatchPt> &MatchPts, DOUBLE dSegma, DOUBLE dMaxError );
    /**
    * @fn mlFilterPtsByMedian
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��ֵ�˲�
    * @param MatchPts ����ƥ���
    * @param nTemplateSize ģ���С
    * @param dThresCoef ��ֵ����ֵ����ֵ
    * @param dThres ��С�Ӳ��޲�
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlFilterPtsByMedian( vector<StereoMatchPt> &MatchPts, SINT nTemplateSize = 5, DOUBLE dThresCoef = 0.1, DOUBLE dThres = 5 );

    bool mlFilterPtsByMedianByCol( vector<StereoMatchPt> &MatchPts );
    /**
    * @fn mlTemplateMatchInFeatPt
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ͼ���������ģ��ƥ��
    * @param rectSearch ƥ�䷶Χ
    * @param nTemplateSize ƥ�䴰�ڴ�С
    * @param dCoef ���ϵ����ֵ
    * @param nXOffSet ����ƫ����
    * @param nYOffSet ����ƫ����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    //�˺���ר����FrameImage�Ȳ���ֿ�����,������� m_vecFeatMatchPt; ��Ƭ��������Χ���� ��Ƭ��Ӧ�� + rectSearch + offset;��������m_vecFeatMatchPt��
    bool mlTemplateMatchInFeatPt( MLRect rectSearch, SINT nTemplateSize, DOUBLE dCoef = 0.75, SINT nXOffSet = 0, SINT nYOffSet = 0 );


    /**
    * @fn mlTemplateMatch
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����ͼ���ģ��ƥ��
    * @param pLeftImg ��Ӱ��Block
    * @param pRightImg ��Ӱ��Block
    * @param vecPtL ��Ӱ��ƥ���
    * @param vecPtR ��Ӱ��ƥ���
    * @param vecMatchPts ƥ�䷶Χ
    * @param rectSearch ƥ�䷶Χ
    * @param nTemplateSize ƥ�䴰�ڴ�С
    * @param dCoef ���ϵ����ֵ
    * @param nXOffSet ����ƫ����
    * @param nYOffSet ����ƫ����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlTemplateMatch( CmlRasterBlock* pLeftImg, CmlRasterBlock* pRightImg, vector<Pt2i> &vecPtL, \
                          vector<Pt2i> &vecPtR, vector<StereoMatchPt> &vecMatchPts, MLRect rectSearch, \
                          SINT nTemplateSize, DOUBLE dCoef = 0.75, SINT nXOffSet = 0, SINT nYOffSet = 0, bool bIsRemoveAbPixel = false );

    bool mlTemplateMatchWithAccu( CmlRasterBlock* pLeftImg, CmlRasterBlock* pRightImg, vector<Pt2i> &vecPtL, \
                          vector<Pt2i> &vecPtR, vector<StereoMatchPt> &vecMatchPts, MLRect rectSearch, \
                          SINT nTemplateSize, DOUBLE dCoef = 0.75, SINT nXOffSet = 0, SINT nYOffSet = 0, bool bIsRemoveAbPixel = false );
    /**
    * @fn mlTemplateMatchInRegion
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ������Ӱ����һ��ȡ����Ӱ����ͬ����
    * @param pLeftImg ��Ӱ��Block
    * @param pRightImg ��Ӱ��Block
    * @param ptLeft ��Ӱ��ĳ��
    * @param ptRight ��Ӱ���ƥ���
    * @param nXMin ƥ�䷶Χ���Ͻ�X
    * @param nXMax ƥ�䷶Χ���½�X
    * @param nYMin ƥ�䷶Χ���Ͻ�Y
    * @param nYMax ƥ�䷶Χ���½�Y
    * @param nTemplateSize ƥ�䴰�ڴ�С
    * @param dCoef ���ϵ����ֵ
    * @param nXOffSet ����ƫ����
    * @param nYOffSet ����ƫ����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlTemplateMatchInRegion( CmlRasterBlock* pLeftImg, CmlRasterBlock* pRightImg, Pt2i ptLeft, Pt2i &ptRight, DOUBLE &dCoef,\
                                  SINT nXMin, SINT nXMax, SINT nYMin, SINT nYMax, \
                                  SINT nTemplateSize, DOUBLE dCoefThres = 0.75, SINT nXOffSet = 0, SINT nYOffSet = 0, bool bIsRemoveAbPixel = false  );

    bool mlTemplateMatchInTwoFeatPtsVerify( const SCHAR* pLImg, const SCHAR* pRImg, vector<Pt2i> vecLPts, vector<Pt2i> vecRPts, vector<StereoMatchPt> &vecSMPts, \
                                           MatchInRegPara matchPara, bool bIsRemoveAbPixel = false );

    bool mlTemplateMatchInLFeatPtsToAll( const SCHAR* pLImg, const SCHAR* pRImg, vector<Pt2i> vecLPts, vector<StereoMatchPt> &vecSMPts, \
                                           MatchInRegPara matchPara, bool bIsRemoveAbPixel = false );

    bool mlTemplateMatchInRFeatPtsToAll( const SCHAR* pLImg, const SCHAR* pRImg, vector<Pt2i> vecRPts, vector<StereoMatchPt> &vecSMPts, \
                                           MatchInRegPara matchPara, bool bIsRemoveAbPixel = false );

    bool mlFindCorPtsInRegFeatPts( const char* pImgLPath, const char* pImgRPath, Pt2i ptL, Pt2i &ptR, DOUBLE &dCoef, \
                                   ExtractFeatureOpt extFeatOpts, MatchInRegPara matchPara );


    bool mlFindCorPtsInRegFeatPts( CmlRasterBlock* pBlockL, CmlRasterBlock* pBlockR, vector<Pt2i> vecPtsInRImg, Pt2i ptL, Pt2i &ptR, DOUBLE &dCoef, \
                                   ExtractFeatureOpt extFeatOpts, MatchInRegPara matchPara );



     /**
    * @fn mlLsMatchInFrameImg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ӱ����С����ƥ�䣬�õ�������ƥ���
    * @param vecMatchPt ����Ӱ��ƥ�������
    * @param nTemplateSize ƥ�䴰�ڴ�С
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlLsMatchInFrameImg(  vector<StereoMatchPt> &vecMatchPt, SINT nTempSize );
    /**
    * @fn mlLsMatch
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ӱ����С����ƥ�䣬������Ӱ����һ��ȡ����Ӱ����ͬ����
    * @param pBlockL ��Ӱ��Block
    * @param pBlockR ��Ӱ��Block
    * @param dLx ��Ӱ��ƥ���X
    * @param dLy ��Ӱ��ƥ���Y
    * @param dRx ��Ӱ���ƥ���X
    * @param dRy ��Ӱ���ƥ���Y
    * @param nTempSize ƥ�䴰�ڴ�С
    * @param dCoef ���ϵ����ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlLsMatch( CmlRasterBlock* pBlockL,  CmlRasterBlock* pBlockR, DOUBLE dLx, DOUBLE dLy, DOUBLE& dRx, DOUBLE& dRy, SINT nTempSize, DOUBLE& dCoef );

    /**
    * @fn mlInterSectionInFrameImg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ӱ��ռ�ǰ������
    * @param vecMatchPt ƥ�����ռ���ά����ߵ�ṹ��
    * @param dThres ������ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlInterSectionInFrameImg(  vector<StereoMatchPt> &vecMatchPt, DOUBLE dThres = 0.0001 );

    bool mlInterSectionInFrameImg(  vector<StereoMatchPt> &vecMatchPt, vector<bool> &vecbIsValid, DOUBLE dThres = 0.0001 );


    /**
    * @fn mlInterSectionInFrameImg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ӱ��ռ�ǰ������
    * @param[in] vecMatchPt ƥ�����ռ���ά����ߵ�ṹ��
    * @param[out] vec3dPts �ռ���ά��
    * @param dThres ������ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlInterSectionInFrameImg(  vector<StereoMatchPt> &vecMatchPt, vector<Pt3d> &vec3dPts, DOUBLE dThres = 0.0001 );
    //�˺����ڲ�������У������
    /**
    * @fn mlInterSection
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��������У�����ܵ�ͨ�ÿռ�ǰ�����ắ��
    * @param ptL ��ƥ���
    * @param ptR ��ƥ���
    * @param nHeightL ��Ӱ���
    * @param nHeightR ��Ӱ���
    * @param ptXYZ ��ά������
    * @param pInOriL ��Ӱ���ڷ�λ
    * @param pExOriL ��Ӱ���ⷽλ
    * @param pInOriR ��Ӱ���ڷ�λ
    * @param pExOriR ��Ӱ���ⷽλ
    * @param dThres ������ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlInterSection(  Pt2d ptL, Pt2d ptR, SINT nHeightL, SINT nHeightR, Pt3d &ptXYZ, \
                          InOriPara* pInOriL, ExOriPara* pExOriL, InOriPara* pInOriR, ExOriPara* pExOriR, DOUBLE dThres = 0.0001 );

    bool mlInterSection(  Pt2d ptL, Pt2d ptR, Pt3d &ptXYZ, \
                          InOriPara* pInOriL, ExOriPara* pExOriL, InOriPara* pInOriR, ExOriPara* pExOriR, DOUBLE dThres = 0.0001 );
    /**
    * @fn mlInterSection
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��������У�����ܵ�ͨ�ÿռ�ǰ�����ắ��
    * @param dLx ��ƥ���X
    * @param dLy ��ƥ���Y
    * @param dRx ��ƥ���X
    * @param dRy ��ƥ���Y
    * @param pMatL ��Ӱ����ת����
    * @param pMatR ��Ӱ����ת����
    * @param PtXsYsZsL ��Ӱ���ⷽλ��Ԫ��
    * @param PtXsYsZsR ��Ӱ���ⷽλ��Ԫ��
    * @param f1 ��������
    * @param f2 ��������
    * @param PtXYZ �����ά������
    * @param dThres ������ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlInterSection( DOUBLE dLx, DOUBLE dLy, DOUBLE dRx, DOUBLE dRy, CmlMat* pMatL, CmlMat* pMatR, Pt3d PtXsYsZsL, Pt3d PtXsYsZsR, DOUBLE f1, DOUBLE f2, Pt3d &PtXYZ, DOUBLE dThres = 0.0001 );

    bool mlInterSection( DOUBLE dLx, DOUBLE dLy, DOUBLE dRx, DOUBLE dRy, CmlMat* pMatL, CmlMat* pMatR, Pt3d PtXsYsZsL, Pt3d PtXsYsZsR, DOUBLE f1, DOUBLE f2, \
                         Pt3d &ptXYZ, Pt2d &ptLxyAccu, Pt2d &ptRxyAccu, Pt3d &ptXYZAccu, DOUBLE dThres = 0.0001 );
    /**
    * @fn mlGetEpipolarImg
    * @date 2011.11.27
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ���Ǻ���Ӱ���ز����ɺ���Ӱ��
    * @param pLOriImg ��Ӱ���
    * @param pROriImg ��Ӱ���
    * @param pInOriL ��Ӱ���ڷ�λ
    * @param pExOriL ��Ӱ���ⷽλ
    * @param pInOriR ��Ӱ���ڷ�λ
    * @param pExOriR ��Ӱ���ⷽλ
    * @param pLEpiImg �����Ӱ��
    * @param pREpiImg �Һ���Ӱ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlGetEpipolarImg( CmlRasterBlock *pLOriImg, CmlRasterBlock *pROriImg, InOriPara* pInOriL, ExOriPara* pExOriL, \
                           InOriPara* pInOriR, ExOriPara* pExOriR, CmlRasterBlock *pLEpiImg, CmlRasterBlock *pREpiImg );
    /**
    * @fn mlGetEpipolarImg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ӱ��������ں���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlGetEpipolarImg();
    /**
    * @fn mlDenseMatch
    * @date 2011.12.14
    * @author �틠 pengman@irsa.ac.cn
    * @brief Ӱ���ܼ�ƥ��
    * @param pBlockL ��Ӱ���
    * @param pBlockR ��Ӱ���
    * @param vecMatchPt Ӱ��ƥ��������
    * @param WidePara ƥ������ṹ
    * @param vecLPts �ܼ�ƥ�����Ӱ�������
    * @param vecRPts �ܼ�ƥ�����Ӱ�������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlDenseMatch(CmlRasterBlock* pBlockL,  CmlRasterBlock* pBlockR,vector<StereoMatchPt> &vecMatchPt, WideOptions WidePara, \
                      vector<Pt2d> &vecLPts,  vector<Pt2d> &vecRPts);

    /**
    * @fn mlDenseMatch
    * @date 2011.12.14
    * @author �틠 pengman@irsa.ac.cn
    * @brief Ӱ���ܼ�ƥ��
    * @param pBlockL ��Ӱ���
    * @param pBlockR ��Ӱ���
    * @param vecMatchPt Ӱ��ƥ��������
    * @param WidePara ƥ������ṹ
    * @param rectMatch ָ��ƥ������
    * @param vecLPts �ܼ�ƥ�����Ӱ�������
    * @param vecRPts �ܼ�ƥ�����Ӱ�������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlDenseMatch(CmlRasterBlock* pBlockL,  CmlRasterBlock* pBlockR,vector<StereoMatchPt> &vecMatchPt, WideOptions WidePara, \
                      MLRect rectMatch, vector<Pt2d> &vecLPts,  vector<Pt2d> &vecRPts, vector<DOUBLE> &vecCorr, bool bIsRemoveAbPixel = false );

    /**
    * @fn mlDisEstimate
    * @date 2011.12.14
    * @author �틠 pengman@irsa.ac.cn
    * @brief ������ȷƥ������������������������ӲΧԤ��
    * @param vFeaPtL ������������Ӳ�
    * @param nStep �ܼ�ƥ��ĸ�����С
    * @param nRadius �Ӳ���Ƶ������뾶��С
    * @param vecPt ��ƥ��������
    * @param vecDisxy ��ƥ�����ӲΧ
    * @return �����ӲΧԤ���ƥ������
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    SINT mlDisEstimate(vector<Pt3d> &vFeaPtL, UINT nStep,SINT nRadius,vector<Pt2i> &vecPt,vector<Pt2i> &vecDisxy);
    /**
    * @fn mlUniquePt
    * @date 2011.12.20
    * @author �틠 pengman@irsa.ac.cn
    * @brief ȥ��������ƥ�����ظ��ĵ�
    * @param MatchPts ����ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlUniquePt(vector<StereoMatchPt> &MatchPts);
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ����ά��
//    * @param strPath �ļ�·��
//    * @param vecPt3d ��ά��
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool ReadFeatMatchPts( string strPath, vector<Pt3d> &vecPt3d );
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ������ƥ���
//    * @param strPath �ļ�·��
//    * @param vecStereoPt ����ƥ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool ReadFeatMatchPts( string strPath, vector<StereoMatchPt> &vecStereoPt );
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ������ƥ���
//    * @param strLPath ���ļ�·��
//    * @param strRPath ���ļ�·��
//    * @param vecStereoPt ����ƥ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool ReadFeatMatchPts( string strLPath, string strRPath, vector<Pt3d> &vecStereoPt );
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ������ƥ���
//    * @param strLPath ���ļ�·��
//    * @param strRPath ���ļ�·��
//    * @param vecStereoPt ����ƥ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool ReadFeatMatchPts( string strLPath, string strRPath, vector<StereoMatchPt> &vecStereoPt );
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ������ƥ���д���ļ�
//    * @param strPath �ļ�·��
//    * @param vecFeatMatchPt ����ƥ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool WriteFeatMatchPts( string strPath, vector<StereoMatchPt> &vecFeatMatchPt );
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ������ƥ���д���ļ�
//    * @param strLPath ���ļ�·��
//    * @param strRPath ���ļ�·��
//    * @param pStereoSet �������Ӱ����Ϣ
//    * @param vecFeatMatchPt ƥ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool WriteFeatMatchPts( string strLPath, string strRPath, StereoSet *pStereoSet, vector<StereoMatchPt> &vecFeatMatchPt );
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ��ȡ�ܼ�ƥ���
//    * @param strLPath ���ļ�·��
//    * @param strRPath ���ļ�·��
//    * @param vecStereoPt �ܼ�ƥ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool ReadDenseMatchPts( string strLPath, string strRPath, vector<Pt3d> &vecStereoPt );
//    /**
//    * @fn
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ��ȡ�ܼ�ƥ���
//    * @param strLPath ���ļ�·��
//    * @param strRPath ���ļ�·��
//    * @param vecStereoPt �ܼ�ƥ��㼯
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool ReadDenseMatchPts( string strLPath, string strRPath, vector<StereoMatchPt> &vecStereoPt );
//    /**
//    * @fn WriteDenseMatchPts
//    * @date 2011.11.02
//    * @author ���Ļ� whwan@irsa.ac.cn
//    * @brief ��ȡ�ܼ�ƥ���
//    * @param strLPath ���ļ�·��
//    * @param strRPath ���ļ�·��
//    * @param pStereoSet �������Ӱ����Ϣ
//    * @param vecFeatMatchPt �ܼ�ƥ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool WriteDenseMatchPts( string strLPath, string strRPath, StereoSet *pStereoSet, vector<StereoMatchPt> &vecFeatMatchPt );

//    /**
//    * @fn ReadDmfPts
//    * @date 2011.11.02
//    * @author �틠 pengman@irsa.ac.cn
//    * @brief ��ȡ�ܼ�ƥ���
//    * @param strLPath ���ļ�·��
//    * @param strRPath ���ļ�·��
//    * @param vecFeatMatchPt �ܼ�ƥ���
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ��
//    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//    */
//    bool ReadDmfPts( string strLPath, string strRPath, vector<StereoMatchPt> &vecStereoPt );

    /**
    * @fn DisparityMap
    * @date 2011.11.02
    * @author �틠 pengman@irsa.ac.cn
    * @brief �ܼ�ƥ��������Ӳ�ͼ
    * @param imgPtL ���ļ��ܼ�ƥ���
    * @param imgPtR ���ļ��ܼ�ƥ���
    * @param DstFile �Ӳ�ͼ�ļ�
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool DisparityMap( ImgPtSet& imgPtL, ImgPtSet& imgPtR, char* DstFile);

    CmlGdalDataset* m_pDataL;//!<��Ӱ��
    CmlGdalDataset* m_pDataR;//!<��Ӱ��

    vector<StereoMatchPt> m_vecFeatMatchPt;//!<����ƥ���
    vector<StereoMatchPt> m_vecDenseMatchPt;//!<�ܼ�ƥ���

    /**
    * @fn Match2LargeImg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Ŵ�Ӱ����ƥ��(ʹ��SIFT)
    * @param strL ���ļ�·��
    * @param strR ���ļ�·��
    * @param vecMatchPts ƥ�����
    * @param stuSiftPara siftƥ�����
    * @param stuRANSACPara RANSAC����
    * @param dRatio ����ϵ��������Ӱ���߳��Դ�ϵ����ͬ��Ӱ��ƥ�䣬�Ա���õ�ʵ��ƥ�䡣����ϵ����Ӱ����������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool Match2LargeImg( const SCHAR* strL, const SCHAR* strR, vector<StereoMatchPt> &vecMatchPts, SiftMatchPara stuSiftPara, RANSACAffineModPara stuRANSACPara, DOUBLE dRatio = 1.0, UINT nMaxBlockSize = 3000, UINT nMaxOverlap = 200, UINT nTilts = 8, bool bIsSIFTNorASIFT = true  );

    bool AffineSIFTMatch( const SCHAR* strL, const SCHAR* strR, UINT nNumTilts, vector<StereoMatchPt> &vecOutMPts );


     /**
    * @fn mlDenseMatchPyra
    * @date 2011.12.14
    * @author �틠 pengman@irsa.ac.cn
    * @brief ����������Ӱ���ܼ�ƥ��
    * @param pBlockL ��Ӱ���
    * @param pBlockR ��Ӱ���
    * @param vecMatchPt Ӱ��ƥ��������
    * @param WidePara ƥ������ṹ
    * @param vecLPts �ܼ�ƥ�����Ӱ�������
    * @param vecRPts �ܼ�ƥ�����Ӱ�������
    * @param nSize �����������Ĳ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlDenseMatchPyra(CmlRasterBlock* pBlockL,  CmlRasterBlock* pBlockR,vector<StereoMatchPt> &vecMatchPt, WideOptions WidePara, \
                                 vector<Pt2d> &vecLPts, vector<Pt2d> &vecRPts,SINT nSize=2);
    /**
    * @fn mlMatchPtPyra
    * @date 2011.12.14
    * @author �틠 pengman@irsa.ac.cn
    * @brief ����ԭʼӰ����ȡ��������������Ӱ��������������
    * @param vecMatchPtIn �����ԭʼӰ��ƥ��������
    * @param vecMatchPtOut ����Ľ�����Ӱ��ƥ��������
    * @param nSize ��������С����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlMatchPtPyra(vector<StereoMatchPt> &vecMatchPtIn, vector<StereoMatchPt> &vecMatchPtOut, SINT nSize, SINT nCase);
protected:
private:

};

#endif // CMLSTEREOPROC_H
