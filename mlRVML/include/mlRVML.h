#ifndef _MLRVML_H_
#define _MLRVML_H_

#include "mlTypes.h"
/**
* @fn mlSingleCamCalib
* @date 2012.2.21
* @author �⿭ wukai@irsa.ac.cn
* @brief ������궨
* @param[in] vecImgPts ��־������������
* @param[in] vecObjPts ��־���﷽��������
* @param[in] nW Ӱ����
* @param[in] nH Ӱ��߶�
* @param[in] bFlag �ж��ǽ�������ٱ궨�������Ǽ����񷽾��ȼ��
* @param[out] inPara ����ڷ�λ����
* @param[out] exPara ����ⷽλ����
* @param[out] vecError ��־���񷽲в�����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlSingleCamCalib(vector<Pt2d>& vecImgPts, const vector<Pt3d>& vecObjPts ,  SINT nW , SINT nH , InOriPara& inPara ,
                                ExOriPara& exPara , vector<Pt3d>& vecError , bool bFlag = 1);
/**
* @fn mlStereoCamCalib
* @date 2012.2.21
* @author �⿭ wukai@irsa.ac.cn
* @brief ��������궨
* @param[in] vecLImgPts ��־�����������������
* @param[in] vecRImgPts ��־�����������������
* @param[in] vecObjPts ��־���﷽��������
* @param[in] nW Ӱ����
* @param[in] nH Ӱ��߶�
* @param[in] bFlag �ж��ǽ�������ٱ궨�������Ǽ����﷽���ȼ��
* @param[out] inLPara ������ڷ�λ����
* @param[out] inRPara ������ڷ�λ����
* @param[out] exLPara ������ⷽλ����
* @param[out] exRPara ������ⷽλ����
* @param[out] exStereoPara �����������ⷽλ����
* @param[out] vecError ��־���﷽�в�����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlStereoCamCalib(const vector<Pt2d>& vecLImgPts , const vector<Pt2d>& vecRImgPts , vector<Pt3d>& vecObjPts ,
                                SINT nW , SINT nH , InOriPara& inLPara , InOriPara& inRPara , ExOriPara& exLPara , ExOriPara& exRPara , ExOriPara& exStereoPara , vector<Pt3d>& vecError , bool bFlag = 1);
/**
* @fn mlMonoSurvey
* @date 2012.2.21
* @author �틠 pengman@irsa.ac.cn
* @brief ��Ŀ����
* @param[in] imgpts ��־��������
* @param[in] vecObjPts ��־���﷽����
* @param[in] InOriInput �ڷ�λԪ��
* @param[out] exOriOut ��Ƭ�ⷽλԪ��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlMonoSurvey(vector<Pt2d> imgpts, vector<Pt3d> vecObjPts, InOriPara& InOriInput, ExOriPara &exOriOut);
/**
* @fn mlWideBaseAnalysis
* @date 2011.12.1
* @author �틠
* @brief ��������ͼ���Ż��߷���
* @param[in] NavCamPara �����������
* @param[in] PanCamPara ȫ���������
* @param[in] AnaPara ȫ���������
* @param[out] OptiBase ��������Ż���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.1
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
MLAPI( bool )  mlWideBaseAnalysis(InOriPara NavCamPara, InOriPara PanCamPara, BaseOptions AnaPara,DOUBLE &OptiBase);
/**
* @fn mlWideBaseMapping
* @date 2011.12.1
* @author �틠
* @brief ��������ͼ
* @param[in] vecStereoSet ������Բ���
* @param[in] WidePara ������ƥ��ṹ�����
* @param[out] vecFPtSetL �������Ӱ��������
* @param[out] vecFPtSetR �������Ӱ��������
* @param[out] vecDPtSetL �������Ӱ���ܼ���
* @param[out] vecDPtSetR �������Ӱ���ܼ���
* @param[out] strDemFile ����DEM�ļ�·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.1
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
MLAPI( bool )  mlWideBaseMapping(vector<StereoSet> vecStereoSet, WideOptions WidePara,vector<ImgPtSet>& vecFPtSetL, vector<ImgPtSet>& vecFPtSetR, vector<ImgPtSet>& vecDPtSetL, vector<ImgPtSet>& vecDPtSetR, SCHAR *strDemFile);
/**
* @fn mlDenseMatch
* @date 2011.12.14
* @author �틠 pengman@irsa.ac.cn
* @brief Ӱ���ܼ�ƥ��
* @param[in] pStereoSet �������
* @param[in] WidePara ƥ������ṹ
* @param[out] vecFPtSetL ����ƥ�����Ӱ�������
* @param[out] vecFPtSetR ����ƥ�����Ӱ�������
* @param[out] vecDPtSetL �ܼ�ƥ�����Ӱ�������
* @param[out] vecDPtSetR �ܼ�ƥ�����Ӱ�������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlDenseMatch(StereoSet* pStereoSet, WideOptions WidePara, ImgPtSet& vecFPtSetL, ImgPtSet& vecFPtSetR, ImgPtSet& vecDPtSetL, ImgPtSet& vecDPtSetR);


/**
* @fn mlDenseMatchRegion
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
MLAPI( bool )  mlDenseMatchRegion(StereoSet* pStereoSet, GaussianFilterOpt GauPara, ExtractFeatureOpt ExtractPara, MatchInRegPara MatchPara, RANSACHomePara RanPara, \
                                  MLRectSearch RectSearch, WideOptions WidePara,  SINT Lx, SINT Ly, SINT ColRange, SINT RowRange, ImgPtSet& vecDPtSetL, ImgPtSet& vecDPtSetR, vector<Pt3d>& vecPtObj, vector<DOUBLE>& vecCorr);

/**
* @fn mlDisparityMap
* @date 2011.11.02
* @author �틠 pengman@irsa.ac.cn
* @brief �����ܼ�ƥ��������Ӳ�ͼ
* @param[in] imgPtL ��Ӱ���ܼ�ƥ���
* @param[in] imgPtR ��Ӱ���ܼ�ƥ���
* @param[out] strDisFile �Ӳ�ͼ����·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlDisparityMap(ImgPtSet& imgPtL, ImgPtSet& imgPtR, SCHAR *strDisFile);
 /**
 *@fn mlCoordTransResult
 *@date 2012.02
 *@author ������
 *@brief ���ݸ�������ת�����ƽ���������ת���������
 *@param[in] pArr ������������ָ��
 *@param[in] strumat ת����ϵ�ṹ��
 *@param[in] nflag ת��״̬���� Ĭ��Ϊ0
         ����ת����ϵ B = R*A + T (RΪ��ת����TΪƽ������)
         ��nflag=0ʱ����ʾ��A��B��
         ��nflagΪ����ֵ����ʾ��B��A
 *@param[out] pTransResult ����ת������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
MLAPI( bool )  mlCoordTransResult(DOUBLE* pArr,TransMat strumat,DOUBLE* pTransResult,SINT nflag);

/**
* @fn mlSatMatch
* @date 2012.2.21
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ��������ƥ��
* @param[in] sLimgPath ��Ӱ��·��
* @param[in] sRimgPath ��Ӱ��·��
* @param[in] satPara ƥ�����
* @param[in] nMethod ƥ�䷽��
* @param[out] vecRanPts ƥ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlSatMatch(const string sLimgPath, const string sRimgPath, SatOptions &satPara, vector<StereoMatchPt> &vecRanPts, SINT nMethod = 0);

/**
* @fn mlGetLinearImgEop
* @date 2012.2.21
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��ȡ����Ӱ����ⷽλ
* @param[in] vecLineEo  Ӱ����Ԫ��
* @param[in] vecAngleEo Ӱ���Ԫ��
* @param[in] vecImg_time Ӱ��ÿ�г���ʱ��
* @param[out] vecEo ÿ��Ӱ����ⷽλԪ��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlGetLinearImgEop(vector<LineEo> &vecLineEo, vector<AngleEo> &vecAngleEo, vector<DOUBLE> &vecImg_time, vector<ExOriPara> *vecEo);

/**
* @fn mlSatMappingByPts
* @date 2012.2.21
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ������Ӱ��ƥ��������ܼ�ƥ��㼰�﷽��ά�㣬����DEM��DOM
* @param[in] satproj ����Ӱ��DEM��DOM���ɹ��̲���
* @param[in] satPara ����Ӱ��DEM��DOM���ɲ���
* @param[in] vecRanPts ƥ���
* @param[out] vecDensePts �ܼ�ƥ��㼰�﷽��ά��
* @param[out]  vecPres  �﷽��ά�㾫��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlSatMappingByPts(SatProj &satproj, SatOptions &satPara, vector<StereoMatchPt> &vecRanPts, vector<StereoMatchPt> &vecDensePts, vector<Pt3d> &vecPres);
/**
* @fn mlMapByInteBlock
* @date 2012.2.21
* @author ���Ļ�
* @brief �ɵ�վ�����������DEM��DOM
* @param[in] vecStereoSet ��վ���������Ϣ
* @param[in]  vecImgPtSets ������Զ�Ӧ�ĵ���Ϣ�����������������ƥ��
* @param[in] ptLT �����ɷ�Χ���Ͻ�
* @param[in] ptRB �����ɷ�Χ���½�
* @param[in] dResolution DEM��DOM���ɵķֱ���
* @param[in] extractPtsOpts ��������ȡ����
* @param[in] matchOpts ƥ�����
* @param[in] ransacOpts �ֲ��޳�����
* @param[out] strDemPath DEM����·��
* @param[out] strDomPath Dom����·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlMapByInteBlock(   vector<StereoSet> &vecStereoSet, vector< ImgPtSet > &vecImgPtSets, Pt2d ptLT, Pt2d ptRB, DOUBLE dResolution,\
                                        ExtractFeatureOpt extractPtsOpts, MatchInRegPara matchOpts, RANSACHomePara ransacOpts, MedFilterOpts mFilterOpts, \
                                   string strDemPath, string strDomPath );

MLAPI( bool )  mlSiteBA( vector<StereoSet> vecStereoSetIn, vector< ImgPtSet > &vecImgPtSets, \
                            ExtractFeatureOpt extractPtsOpts, MatchInRegPara matchOpts, RANSACHomePara ransacOpts, MedFilterOpts mFilterOpts, \
                           vector<StereoSet> &vecStereoOut );

/**
* @fn mlPanoMatchPts
* @date 2012.2.21
* @author ����
* @brief ����ԭʼͼ�������ƥ����ļ�
* @param[in] vecParam ȫ��ƴ�Ӳ���
* @param[in] vecFrmInfo ԭʼͼ��ͼ����Ϣ
* @param[in] vecImgPtSets ԭʼͼ���Ӧ����Ϣ
* @param[out] strOutPath ���ƥ����ļ�·��
* @param[out] bNeedAddPts ����Ƿ��˹��ӵ��ʶ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )   mlPanoMatchPts( vector<char*> vecParam, vector<FrameImgInfo> vecFrmInfo, vector<ImgPtSet> &vecImgPtSets, char* strOutPath, bool &bNeedAddPts );

/**
* @fn mlPanoMosic
* @date 2012.2.21
* @author ����
* @brief ȫ��ƴ�Ӻ���
* @param[in] vecPara ȫ��ƴ�Ӳ���
* @param[out] vecFrmInfo ԭʼͼ��ͼ����Ϣ
* @param[out] vecImgPtSets ԭʼͼ���Ӧ����Ϣ
* @param[out] strOutPath ���ȫ��ͼ��·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )   mlPanoMosic( vector<char*> vecPara, vector<FrameImgInfo> vecFrmInfo, vector< ImgPtSet > &vecImgPtSets, char* strOutPath );

/**
 *@fn mlTinSimply
 *@date 2012.02
 *@author ������
 *@brief ��������������
 *@param[in] vecPt3dIn ��Ҫ�򻯵�������������
 *@param[in] simpleIndex ��ϵ�� ȡֵΪ0��1֮��
 *@param[out] vecPt3dOut �򻯺��������������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 * @par �޸���ʷ:
 * <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlTinSimply(vector<Pt3d> &vecPt3dIn,vector<Pt3d> &vecPt3dOut,DOUBLE simpleIndex);
/**
 *@fn mlCalcTransMatrixByLatLong
 *@date 2011.11
 *@author ������
 *@brief ���������ݶ�λ�ľ�γ��ʵ���¹�ϵ���ֲ�����ϵת����ϵ���
 *@param[in] dLat ��λ��γ��  ��λΪ��   ��ΧΪ-90�ȡ�90��  ��γΪ�� ��γΪ��
 *@param[in] dLong ��λ�ľ��� ��λΪ��   ��ΧΪ-180-180��  ����Ϊ�� ����Ϊ��
 *@param[out] tmat  �洢ת������ת������ƽ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

*/
MLAPI( bool )  mlCalcTransMatrixByLatLong(DOUBLE dLat,DOUBLE dLong,TransMat& tmat);
/**
 *@fn mlCalcTransMatrixByXYZ
 *@date 2011.11
 *@author ������
 *@brief ������ʵ���¹�ϵ���ֲ�����ϵת����ϵ���
 *@param[in] dLocResult_x ��½�����¹�ϵ�µþ�ȷ��λ���X
 *@param[in] dLocResult_y ��½�����¹�ϵ�µþ�ȷ��λ���Y
 *@param[in] dLocResult_z ��½�����¹�ϵ�µþ�ȷ��λ���Z
 *@param[out] tmat  �洢ת������ת������ƽ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlCalcTransMatrixByXYZ(DOUBLE dLocResult_x,DOUBLE dLocResult_y,DOUBLE dLocResult_z,TransMat& tmat);
/**
 *@fn mlVisualImage
 *@date 2012.02
 *@author ������
 *@brief ����DEM��DOM����ָ���ӽ��µķ���ͼ��
 *@param[in] strDem DEM·�����ļ�����geotiff�ļ���ʽ��������������
 *@param[in] strDom DOM·�����ļ�����geotiff�ļ���ʽ��������������
 *@param[in] exori ָ���ӽ��ⷽλԪ��
 *@param[in] fx x���򽹾�
 *@param[in] fy y���򽹾�
 *@param[in] nImgWid ����ͼ��Ŀ�
 *@param[in] nImgHei ����ͼ��ĸ�
 *@param[out] outImg ����ļ�����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlVisualImage( const SCHAR* strDem,const SCHAR* strDom,const SCHAR* outImg,ExOriPara exori,DOUBLE fx,DOUBLE fy,SINT nImgWid,SINT nImgHei);

/**
 *@fn mlPano2Prespective
 *@date 2012.02
 *@author ����
 *@brief ����ȫ��ͼ�񣬶���֪��Χ����͸��ͼ��
 *@param[in] cInputPanoFile �����ȫ��ͼ��·��
 *@param[in] nOriginX ѡȡ��Χ�����Ͻǵ�X����
 *@param[in] nOriginY ѡȡ��Χ�����Ͻǵ�Y����
 *@param[in] nPanoRoiW ѡȡ��Χ�Ŀ��
 *@param[in] nPanoRoiH ѡȡ��Χ�ĸ߶�
 *@param[in] dFocus ����
 *@param[out] cOutputImage �����͸��ͼ��·��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlPano2Prespective( const SCHAR *cInputPanoFile, const SCHAR * cOutputImage, SINT nOriginX, SINT nOriginY, SINT nPanoRoiW, SINT nPanoRoiH, DOUBLE dFocus);

/**
 *@fn mlDEMMosaic
 *@date 2012.02
 *@author ����
 *@brief demƴ��
 *@param[in] vecInputFiles �����ԭʼdem
 *@param[in] dXResl ����ļ�x����ֱ���
 *@param[in] dYResl ����ļ�����ֱ���
 *@param[in] nResampleAlg �ز����㷨��Ĭ��˫���Բ�ֵ)
 *@param[in] nDisCultLine ƴ���ߣ�Ĭ��Ϊ�գ�
 *@param[out] cOutputFile ����ļ�·��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlDEMMosaic( vector<string> vecInputFiles, const SCHAR* cOutputFile, DOUBLE dXResl, DOUBLE dYResl, SINT nResampleAlg, SINT nDisCultLine);
/**
* @fn mlComputeInsightMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ���������DEM���ݺ��ӵ����꣬����ͨ��ͼ
* @param[in] sInputDEM ����DEM�ļ�·��
* @param[in] nxLocation �ӵ�x����
* @param[in] nyLocation �ӵ�y����
* @param[in] dViewHight  �ӵ�������ĸ߶�
* @param[in] InverseHeight �Ƿ񽫸̷߳�ת
* @param[out] sDestDEM   ����ļ�·��
*@retval TRUE �ɹ�
*@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
*@par �޸���ʷ��
*<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeInsightMap( const SCHAR * sInputDEM, SINT nxLocation ,SINT nyLocation, DOUBLE dViewHight, const SCHAR * sDestDEM, bool InverseHeight);

/**
* @fn mlComputeSlopeMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݣ��ͼ��㴰�ڴ�С������¶�
* @param[in] sInputDEM  ����DEM�ļ�·��
* @param[in] nWindowSize ���㴰�ڴ�С
* @param[in] dZfactor �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
* @param[out] sDestDEM ����ļ�·��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeSlopeMap(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor );
/**
* @fn mlComputeSlopeAspectMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݣ��ͼ��㴰�ڴ�С���������
* @param[in] sInputDEM  ����DEM�ļ�·��
* @param[in] nWindowSize ���㴰�ڴ�С
* @param[in] dZfactor �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
* @param[out] sDestDEM ����ļ�·��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeSlopeAspectMap(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor );
/**
* @fn mlComputeBarrierMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݣ��ͼ��㴰�ڴ�С���ϰ�ͼ���������ϰ�ͼ
* @param[in] sInputDEM  ����DEM�ļ�·��
* @param[in]  nWindowSize ���㴰�ڴ�С
* @param[in]  dZfactor �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
* @param[in]  ObPara �ϰ�ͼ�����ṹ��
* @param[out] sDestDEM ����ļ�·��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeBarrierMap(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor,ObstacleMapPara ObPara);
/**
* @fn mlComputeContourMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݺ͵ȸ߾࣬����ȸ���ͼ
* @param[in] dHinterval  �ȸ߾�
* @param[in] strSrcfilename �����DEM�ļ�·��
* @param[in] bCNodata ��ʾ�Ƿ��Զ���Nodataֵ
* @param[in] dNodata ���bCNodata����Ϊtrue����dNodata ��ֵ�ڼ���ʱ��������Чֵ�Դ�
* @param[in] strAttrib ����shape�ļ��̵߳��������ƣ�Ĭ��Ϊelev
* @param[out] strDstfilename �����shape�ļ�·��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeContourMap(DOUBLE dHinterval, SCHAR* strSrcfilename, SCHAR* strDstfilename ,bool bCNodata = false , DOUBLE dNodata = 0.0 ,SCHAR* strAttrib = "elev" );
/**
 *@fn mlGeoRasterCut
 *@date 2011.11
 *@author ������
 *@brief �������ض�DEM��DOM���вü�
 *@param[in] strFileIn ���ü��������ļ�
 *@param[in]  pttl_x �ü����Ͻ�x����
 *@param[in]  pttl_y �ü����Ͻ�y����
 *@param[in]  ptbr_x �ü����½�x����
 *@param[in]  ptbr_y �ü����½�y����
 *@param[in] nflag ָ���ü���ʽ 1Ϊ�����زü� 2Ϊ����������ü�
 *@param[in] nCutBands ָ���ü����� Ϊ����ʱ��ʾ���в��ζ��ü� Ϊ��ʱ�ü��ض��Ĳ���
 *@param[in] dZoom  ����ϵ�� Ĭ��Ϊ1
 *@param[out] strFileOut �ü�������ļ�
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlGeoRasterCut( const SCHAR* strFileIn,const SCHAR* strFileOut,DOUBLE pttl_x,DOUBLE pttl_y,DOUBLE ptbr_x,DOUBLE ptbr_y,SINT nflag, SINT nCutBands, DOUBLE dZoom);
/**
* @fn mlLocalByMatch
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ��͵���Ӱ���ƥ��ʵ�ֶ�λ
* @param[in] strLandDom ����Ӱ���ļ�·��
* @param[in] strSatDom ����Ӱ��ƥ�������
* @param[in] LandImgPtset ����Ӱ��ƥ�������
* @param[in] SatImgPtset ����Ӱ��ƥ�������
* @param[in] localByMOpts ƥ�����
* @param[out] ptLocalRes ��λ���
* @param[out]  dLocalAccuracy ��λ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlLocalByMatch( const SCHAR* strLandDom, const SCHAR* strSatDom,  ImgPtSet &LandImgPtset, ImgPtSet &SatImgPtset, LocalByMatchOpts localByMOpts, Pt2d ptCent, Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );
/**
* @fn mlLocalByIntersection
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��Ƭ�󷽽���ʵ�ֶ�λ
* @param[in] vecGCPs ���Ƶ�����
* @param[in] vecImgPtSets �������
* @param[out] ptLocalRes ��λ���
* @param[out] dLocalAccuracy ��λ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlLocalByIntersection( vector<Pt3d> vecGCPs, vector< ImgPtSet > &vecImgPtSets,  Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );
/**
* @fn mlLocalBySImgIntersection
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
MLAPI( bool )  mlLocalBySImgIntersection( vector<Pt3d> vecGCPs, ImgPtSet imgPts,  ExOriPara &exOriRes, vector<RMS2d> &vecRMSRes, DOUBLE &dTotalRMS  );
/**
* @fn mlLocalIn2Site
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief վ���Ӱ��λ
* @param[in] vecFrontSite ǰվ������Ӱ��
* @param[in] vecEndSite ��վ������Ӱ��
* @param[in] vecFrontPts ǰվ���������
* @param[in] vecEndPts ��վ���������
* @param[in] localBy2Opt ��λ��������
* @param[out] ptLocalRes ��λ���
* @param[out] dLocalAccuracy ��λ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlLocalIn2Site( vector<StereoSet> vecFrontSite, vector<StereoSet> vecEndSite, vector<ImgPtSet> &vecFrontPts, vector<ImgPtSet> &vecEndPts, LocalBy2SitesOpts localBy2Opt, Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );
/**
* @fn mlLocalBySeqence
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief LocalInSequenceImg ����Ӱ��λ
* @param[in] FrameInfoSet ����Ӱ��·������Ϣ
* @param[in] strSatDom ����Ӱ��·��
* @param[in] frmPts ����Ӱ��㼯
* @param[in] SatPts ����Ӱ��㼯
* @param[in] stuLocalBySeqOpts ��λ��������
* @param[out] ptLocalRes ��λ���
* @param[out] dLocalAccuracy ��λ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlLocalBySeqence(  FrameImgInfo FrameInfoSet, const SCHAR* strSatDom, ImgPtSet &frmPts, ImgPtSet &SatPts, LocalBySeqImgOpts stuLocalBySeqOpts, Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );
/**
* @fn mlLocalByLander
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ������½���Ķ�λ
* @param[in] vecStereoSet վ����������Ӱ��
* @param[in] vecGCPs ��������ά����
* @param[in] vecImgPts ƥ����
* @param[in] stuLocalByLanderOpts ��λ����
* @param[out] vecLocalRes ��λ���
* @param[out] vecLocalAccuracy ��λ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlLocalByLander(  vector<StereoSet> vecStereoSet, vector<Pt3d> vecGCPs, vector<ImgPtSet> &vecImgPts, LocalByLanderOpts stuLocalByLanderOpts, vector<Pt3d> &vecLocalRes, vector<DOUBLE> &vecLocalAccuracy );
/**
* @fn mlSmoothByGaussian
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ��ȥ���˹�˲�
* @param[in] strFileIn ����ԭʼӰ��·��
* @param[in] nTemplateSize �˲�ģ���С
* @param[in] dCoef �˲��˲���,һ����0.8Ϊ��
* @param[out] strFileOut ����˲���Ӱ��·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlSmoothByGaussian(const SCHAR* strFileIn, SINT nTemplateSize, DOUBLE dCoef, const SCHAR* strFileOut );
/**
* @fn mlGetEpipolarImg
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���ɺ���Ӱ��
* @param[in] pStereoSet ���������Ϣ
* @param[out] strFileOutL ��Ӱ�����Ӱ��·��
* @param[out] inOriL �����Ӱ��У�����ڷ�λ
* @param[out] exOriL �����Ӱ��У�����ⷽλ
* @param[out] strFileOutR ��Ӱ�����Ӱ��·��
* @param[out] inOriR �����Ӱ��У�����ڷ�λ
* @param[out] exOriR �Һ���Ӱ��У�����ⷽλ

* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlGetEpipolarImg( StereoSet* pStereoSet,
                                        const SCHAR* strFileOutL,
                                        InOriPara &inOriL,
                                        ExOriPara &exOriL,
                                        const SCHAR* strFileOutR,
                                        InOriPara &inOriR,
                                        ExOriPara &exOriR,
                                        CAMTYPE nLCamType = Nav_Cam,
                                        CAMTYPE nRCamType = Nav_Cam,
                                        DOUBLE dZoomCoef = 1.0  );

/**
* @fn mlSift
* @date 2011.12.16
* @author �틠  pengman@irsa.ac.cn
* @brief siftƥ�书��
* @param[in] pStereoSet ���������Ϣ
* @param[in] WidePara ƥ������ṹ��
* @param[out] vecFLPts ��Ƭƥ���
* @param[out] vecFRPts ��Ƭƥ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlSift(StereoSet* pStereoSet, SiftMatchPara siftPara, RANSACAffineModPara ransacPara, vector<Pt2d> &vecFLPts, vector<Pt2d> &vecFRPts);

/**
* @fn mlASift
* @date 2011.12.16
* @author �틠  pengman@irsa.ac.cn
* @brief Asiftƥ�书��
* @param[in] pStereoSet ���������Ϣ
* @param[out] strFileOut ƥ������·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlASift(StereoSet* pStereoSet, ASiftMatchPara asiftPara, RANSACAffineModPara ransacPara, vector<Pt2d> &vecFLPts, vector<Pt2d> &vecFRPts);

/**
* @fn mlTemplateMatch
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ͼ���ģ��ƥ��
* @param[in] pLeftImg ��Ӱ��·��
* @param[in] pRightImg ��Ӱ��·��
* @param[in] vecPtL ��Ӱ���ƥ���
* @param[in] vecPtR ��Ӱ���ƥ���
* @param[in] MatchPara ģ��ƥ�����
* @param[out] vecMatchPts ���ƥ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlTemplateMatchImg( const SCHAR* pLeftImg, const SCHAR* pRightImg, vector<Pt2i> &vecPtL, vector<Pt2i> &vecPtR,\
                                       MatchInRegPara MatchPara, vector<StereoMatchPt> &vecFeatMatchPts);
/**
* @fn mlStereoMatch
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ͼ���ƥ�䲢�����Ӧ��ά���
* @param[in] pStereo ����Ӱ��·��
* @param[in] extractOpts ��Ȥ����ȡ����
* @param[in] matchOpts ƥ�����
* @param[in] ransacOpts RANSAC����
* @param[out] imgLPts ��Ӱ������ƥ���
* @param[out] imgRPts ��Ӱ������ƥ���
* @param[out] vec3dPts �����Ӧ����ά����
* @param MatchPara ģ��ƥ�����
* @param vecMatchPts ���ƥ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlStereoMatchInFrmImg( StereoSet* pStereo, ExtractFeatureOpt extractOpts, MatchInRegPara matchOpts, RANSACHomePara ransacOpts, \
                                  ImgPtSet &imgLPts, ImgPtSet &imgRPts, vector<Pt3d> &vec3dPts );
/**
* @fn mlLSMatchImg
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ����С����ƥ�䣬������Ӱ����һ��ȡ����Ӱ����ͬ����
* @param[in] pLeftImg ��Ӱ��·��
* @param[in] pRightImg ��Ӱ��·��
* @param[in] dLx ��Ӱ��ƥ���X
* @param[in] dLy ��Ӱ��ƥ���Y
* @param[in,out] dRx ��Ӱ���ƥ���X
* @param[in,out] dRy ��Ӱ���ƥ���Y
* @param[in] nTempSize ƥ�䴰�ڴ�С
* @param[in] dCoef ���ϵ����ֵ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlLSMatchImg(SCHAR* pLeftImg, SCHAR* pRightImg, DOUBLE dLx, DOUBLE dLy, DOUBLE& dRx, DOUBLE& dRy, SINT nTempSize, DOUBLE& dCoef);


///**
//* @fn mlDOMGeneration
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief DOM����
//* @param[in] vec3dPts  ��άƥ���
//* @param[in] strPath DEM·��
//* @param[in] dbDemRect DEM���ɷ�Χ
//* @param[in] dResolution ���ɷֱ���
//* @version 1.0
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//MLAPI( bool )  mlDEMGeneration( vector<Pt3d> &vec3dPts, const SCHAR* strPath, DbRect dbDemRect, DOUBLE dResolution );

///**
//* @fn mlDOMGeneration
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief DOM����
//* @param[in] vecStereoSets  ������������Ӱ��
//* @param[in] strDEMPath DEM·��
//* @param[in] strDOMPath DOM·��
//
//* @version 1.0
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//MLAPI( bool )  mlDOMGeneration( vector<StereoSet> &vecStereoSets, const SCHAR* strDEMPath, const SCHAR* strDOMPath );
/**
* @fn mlRansacPts
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ransac�����޳�����ƥ���ֲ�
* @param[in,out] MatchPts ����ƥ���
* @param[in] dThresh ��ֵ
* @param[in] dConfidence ���Ŷ�
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlRansacPts( vector<StereoMatchPt> &MatchPts, DOUBLE dThresh, DOUBLE dConfidence);
/**
* @fn GmlGetNewStereoPtID
* @date 2012.02.10
* @author  ���Ļ� whwan@irsa.ac.cn
* @brief ��ȡƥ���ı��
* @param[in] clsLPts ��Ӱ����Ϣ
* @param[in] clsRPts ��Ӱ����Ϣ
* @param[out] lID ƥ���ı��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlGetNewStereoPtID( ImgPtSet &clsLPts, ImgPtSet &clsRPts, ULONG &lID );
/**
* @fn mlGetNewSinglePtID
* @date 2012.02.10
* @author  ���Ļ� whwan@irsa.ac.cn
* @brief ��ȡ������ı��
* @param[in] clsImgPts Ӱ����Ϣ
* @param[out] lID ƥ���ı��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlGetNewSinglePtID( ImgPtSet &clsPts, ULONG &lID );


//////////////////////////////////////////////////////////////////////////////////
/**
* @fn mlSetLogFilePath
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ������־�ļ�·����������־ģʽ
* @param[in] strFileName ��־·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlSetLogFilePath(char *strFileName);

/**
* @fn mlCloseLogFile
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ر���־�ļ�ģʽ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlCloseLogFile( );

MLAPI( bool )  mlExOriTrans( ExOriPara* pExOriL, ExOriPara* pExOriRela, ExOriPara* pExOriR );

MLAPI( bool )  mlGetRelaOri( ExOriPara* pExOriL, ExOriPara* pExOriR, ExOriPara* pExOriRela );

MLAPI( bool )  mlGetOPKAngle( DOUBLE *pRMat, DOUBLE *pOPK );

MLAPI( bool )  mlGetRMatByOPK( DOUBLE *pOPK, DOUBLE *pRMat );

MLAPI( bool )  mlSemiAutoMatchInRegion( const SCHAR* strPathL, const SCHAR* strPathR, Pt2i ptL, MatchInRegPara matchPara, Pt2i &ptR, DOUBLE &dCoef );


MLAPI( bool )  mlCalcNewAngle( OriAngle oriA, DOUBLE dRollAngle );
////////////////////////////////////////////////////////////////////////////////////
/**
* @fn mlWallisFilter
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief Wallis�˲�����
* @param[in] strInPath  ����ͼ��·��
* @param[in] strOutPath  ���ͼ��·��
* @param[in] fPara  �˲�����
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlWallisFilter( const SCHAR* strInPath, const SCHAR* strOutPath, WallisFPara fPara );
/**
* @fn mlGuassFilter
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��˹�˲�����
* @param[in] strInPath  ����ͼ��·��
* @param[in] strOutPath  ���ͼ��·��
* @param[in] nTemplateSize  �˲�����
* @param[in] dCoef  �˲�����
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlGuassFilter(  const SCHAR* strInPath, const SCHAR* strOutPath,  SINT nTemplateSize, DOUBLE dCoef );

/**
* @fn mlHistogramEqualize
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ֱ��ͼ���⻯
* @param[in] strInPath  ����ͼ��·��
* @param[in] strOutPath  ���ͼ��·��
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlHistogramEqualize(  const SCHAR* strInPath, const SCHAR* strOutPath );
/**
* @fn mlGrayTensile
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ֱ��ͼ����
* @param[in] strInPath  ����ͼ��·��
* @param[in] strOutPath  ���ͼ��·��
* @param[in] nMin  �������С�Ҷ�
* @param[in] nMax  ��������Ҷ�
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlGrayTensile(   const SCHAR* strInPath, const SCHAR* strOutPath, UINT nMin = 0, UINT nMax = 255 );
/**
* @fn mlExtractFeatPtByForstner
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ��Forstner������ȡ������
* @param[in] pImg  ����Ӱ��·��
* @param[out] m_vecFeaPts ��ȡ��������
* @param[in] nGridSize ������С
* @param[in] nPtNum ����ȡ�ĵ���
* @param[in] dCoef ϵ����ֵ
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlExtractFeatPtByForstner( const SCHAR* pImg, vector<Pt2i>& vecFeaPts, SINT nGridSize, SINT nPtNum = 0, DOUBLE dCoef = 1.0, bool bIsRemoveAbPixel = false );

/**
* @fn mlUnDistortForNavPanCam
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ȫ���������������������
* @param[in] ptIn  �����ά��
* @param[in] nHeight ͼ��߶�
* @param[in] inOri �ڷ�λԪ��
* @param[out] ptOutRes ����������
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlUnDistort( Pt2d ptIn, UINT nHeight, InOriPara inOri, Pt2d &ptOutRes, CAMTYPE nCamType = Nav_Cam );

MLAPI( bool )  mlUnDistortImg( const SCHAR* strIn, InOriPara inOri, const SCHAR* strOut, CAMTYPE camType = Nav_Cam, DOUBLE dRatio = 1.0 );
///**
//* @fn mlUnDistortForNavPanCam
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief �����������������
//* @param[in] ptIn  �����ά��
//* @param[in] nHeight ͼ��߶�
//* @param[in] inOri �ڷ�λԪ��
//* @param[out] ptOutRes ����������
//* @version 1.0
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//MLAPI( bool )  mlUnDistortForHazCam( Pt2d ptIn, UINT nHeight, InOriPara inOri, Pt2d &ptOutRes );

MLAPI( bool ) mlCreateImg( const SCHAR* strPath, UINT nW, UINT nH, ImgDotType imgType, void* pData = NULL );

MLAPI( bool ) mlCreateGeoImg( const SCHAR* strPath, UINT nW, UINT nH, Pt2d ptOrig, DOUBLE dXRes, DOUBLE dYRes, ImgDotType imgType, void* pData = NULL );
/**
* @fn mlExtractFeatPtByForstnerWithSRegion
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ��Forstner������ȡ������
* @param[in] pImg  ����Ӱ��·��
* @param[out] m_vecFeaPts ��ȡ��������
* @param[in] vecDisableRange ʧЧ���򼯺�
* @param[in] nGridSize ������С
* @param[in] nPtNum ����ȡ�ĵ���
* @param[in] dCoef ϵ����ֵ
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlExtractFeatPtByForstnerWithSRegion( const SCHAR* pImg, vector<Pt2i>& vecFeaPts, vector<MLRect> vecDisableRange, SINT nGridSize, SINT nPtNum = 0, DOUBLE dCoef = 1.0 );


MLAPI( bool )  mlExtractFeatPtByCanny( const SCHAR* pImg, vector<Pt2i> &vecFeatPts, DOUBLE dThres1, DOUBLE dThres2 );
/**
* @fn mlTemplateMatchInFeatPts
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ��Forstner������ȡ������
* @param[in] pLImg  ����Ӱ��·��
* @param[in] pRImg  ����Ӱ��·��
* @param[in] vecLPts  ��Ӱ��������
* @param[in] vecRPts  ��Ӱ��������
* @param[out] m_vecFeaPts ��ȡ��������
* @param[in] vecDisableRange ʧЧ���򼯺�
* @param[in] nGridSize ������С
* @param[in] nPtNum ����ȡ�ĵ���
* @param[in] dCoef ϵ����ֵ
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlTemplateMatchInFeatPts( const SCHAR* pLImg, const SCHAR* pRImg, vector<Pt2i> vecLPts, vector<Pt2i> vecRPts, vector<StereoMatchPt> &vecSMPts, MatchInRegPara matchPara, bool bIsRemoveAbPixel = false );

//�������������������໥��֤;����1��ʾΪ���Ҹ�����֤��ƥ�䣬����2��ʾ��Ƭ����Ƭ��ȫ������ƥ�䣬��������ʾ��Ƭ����Ƭ��ȫ������, �����ı�ʾ��������ƥ�䷽��
MLAPI( bool )  mlTemplateMatchInFeatPtsVT( const SCHAR* pLImg, const SCHAR* pRImg, vector<Pt2i> vecLPts, vector<Pt2i> vecRPts, vector<StereoMatchPt> &vecSMPts, MatchInRegPara matchPara, UINT nMethod = 1, bool bIsRemoveAbPixel = false);


/**
* @fn mlTemplateMatchInFeatPts
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ��Forstner������ȡ������
* @param[in] pLImg  ����Ӱ��·��
* @param[in] pRImg  ����Ӱ��·��
* @param[in] vecLPts  ��Ӱ��������
* @param[in] vecRPts  ��Ӱ��������
* @param[out] m_vecFeaPts ��ȡ��������
* @param[in] vecDisableRange ʧЧ���򼯺�
* @param[in] nGridSize ������С
* @param[in] nPtNum ����ȡ�ĵ���
* @param[in] dCoef ϵ����ֵ
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlTemplateMatchInFeatPtsWithGivenPts( const SCHAR* pLImg, const SCHAR* pRImg, Pt2d ptL, Pt2d ptR, UINT nRange, UINT nTemplateS, \
                                                     Pt2d &ptRes, DOUBLE &dCoefRes, DOUBLE dCoefThres = -1.0 );



/**
* @fn mlSift
* @date 2011.12.16
* @author �틠  pengman@irsa.ac.cn
* @brief siftƥ�书��
* @param[in] strLPath ��Ӱ����Ϣ
* @param[in] strRPath ��Ӱ����Ϣ
* @param[in] dRatio ƥ����ֵϵ��
* @param[in] nMaxBlockSize �ֿ����ߴ�
* @param[in] nOverLaySize ����ص���С
* @param[out] vecOutRes ƥ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlSiftMatch( const SCHAR* strLPath, const SCHAR* strRPath, DOUBLE dRatio, UINT nMaxBlockSize, UINT nOverLaySize, vector<StereoMatchPt> &vecOutRes );

MLAPI( double* ) mlSiftMatchVT( const SCHAR* strLPath, const SCHAR* strRPath, DOUBLE dRatio, DOUBLE dbRansacSigma, UINT nMaxBlockSize, UINT nOverLaySize, int &nPtSize );

MLAPI( bool )  mlFreeSiftPts( double *pPts );

MLAPI( bool )  mlSiftMatchWHomo( const SCHAR* strLPath, const SCHAR* strRPath, DOUBLE dRatio, vector<StereoMatchPt> &vecOutRes );
/**
* @fn mlDenseMatchRegion
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
MLAPI( bool )  mlDenseMatchRegion(StereoSet* pStereoSet, GaussianFilterOpt GauPara, ExtractFeatureOpt ExtractPara, MatchInRegPara MatchPara, RANSACHomePara RanPara, \
                                  MLRectSearch RectSearch, WideOptions WidePara,  SINT Lx, SINT Ly, SINT ColRange, SINT RowRange, ImgPtSet& vecDPtSetL, ImgPtSet& vecDPtSetR, vector<Pt3d>& vecPtObj, vector<DOUBLE>& vecCorr);
/**
* @fn mlDenseMatchInRegion
* @date 2011.12.14
* @author �틠 pengman@irsa.ac.cn
* @brief Ӱ��ָ�������ܼ�ƥ��
* @param[in] strInPutLImgPath ��Ӱ��
* @param[in] strInPutLImgPath ��Ӱ��
* @param[in] vecFeatMPts ������㼯
* @param[in] nStep ƥ�䲽��
* @param[in] nRadiusX ����X����뾶����
* @param[in] nRadiusY ����Y����뾶����
* @param[in] nXOff X��������λ��ƫ����
* @param[in] nYOff Y��������λ��ƫ����
* @param[in] nTemplateSize ģ���С
* @param[in] dCoefThres ���ϵ����ֵ
* @param[in] rect ��Ӱ���ϴ�ƥ��ķ�Χ
* @param[out] vecOutMRes ƥ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlDenseMatchInRegion( const SCHAR* strInPutLImgPath, const SCHAR* strInPutRImgPath, vector<StereoMatchPt> vecFeatMPts, UINT nStep, UINT nRadiusX, UINT nRadiusY, SINT nXOff, SINT nYOff, \
                                     UINT nTemplateSize, DOUBLE dCoefThres, MLRect rect, vector<StereoMatchPt> &vecOutMRes, bool bIsRemoveAbPixel = false );


MLAPI( bool )  mlDenseMatchInAdaptRegion( const SCHAR* strInPutLImgPath, const SCHAR* strInPutRImgPath, vector<StereoMatchPt> vecFeatMPts, UINT nRadiusX, UINT nRadiusY, SINT nXOff, SINT nYOff, \
                                     UINT nTemplateSize, DOUBLE dCoefThres, stuBlockDeal stuBDData, vector<StereoMatchPt> &vecOutMRes, bool bIsRemoveAbPixel = false );
/**
* @fn mlRansacPtsByHomo
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���õ�Ӧ����ģ���޳��ֲ�
* @param[in] vecStereoPts  ƥ���Խ��
* @param[in] dThres  �޳�������ֵ
* @param[in] dConfidence  �޳�������ֵ
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlRansacPtsByHomo( vector<StereoMatchPt> &vecStereoPts, DOUBLE dThresh = 3, DOUBLE dConfidence = 0.99 );

MLAPI( bool )  mlRansacPtsByHomoVT( vector<StereoMatchPt> vecStereoPts, vector<StereoMatchPt> &vecOutStereoPts, DOUBLE dThresh = 3, DOUBLE dConfidence = 0.99 );

/**
* @fn mlRansacPtsByAffineT
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���÷���仯ģ���޳��ֲ�
* @param[in] vecStereoPts  ƥ���Խ��
* @param[in] dSegma  �޳�������ֵ
* @param[in] dMaxError  �޳�������ֵ
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlRansacPtsByAffineT( vector<StereoMatchPt> vecStereoInPts, DOUBLE dSegma, DOUBLE dMaxError, vector<StereoMatchPt> &vecStereoOutPts );

MLAPI( bool )  mlFilterPtsByMedian( vector<StereoMatchPt> &MatchPts, SINT nTemplateSize = 5, DOUBLE dThresCoef = 0.1, DOUBLE dThres = 5 );
/**
* @fn mlLsMatch
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ����С����ƥ�䣬������Ӱ����һ��ȡ����Ӱ����ͬ����
* @param strPathL ��Ӱ��·��
* @param strPathR ��Ӱ��·��
* @param ptL ��Ӱ��ƥ���
* @param nTempSize ƥ�䴰�ڴ�С
* @param ptR ��Ӱ��ƥ���
* @param dCoef ���ϵ����ֵ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlLsMatch( const SCHAR* strPathL, const SCHAR* strPathR, Pt2d ptL, UINT nTemplateSize, Pt2d &ptR, DOUBLE &dCoef );

/**
* @fn mlInterSection
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��������У�����ܵ�ͨ�ÿռ�ǰ�����ắ��
* @param ptL ��ƥ���
* @param ptR ��ƥ���
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
MLAPI( bool )  mlIntersection(  Pt2d ptL, Pt2d ptR, Pt3d &ptXYZ, \
                          InOriPara* pInOriL, ExOriPara* pExOriL, InOriPara* pInOriR, ExOriPara* pExOriR, DOUBLE dThres = 0.0001 );

MLAPI( bool )  mlIntersectionWithDis( Pt2d ptL, Pt2d ptR, SINT nHeightL, SINT nHeightR, Pt3d &ptXYZ, InOriPara* pInOriL, ExOriPara* pExOriL, InOriPara* pInOriR, ExOriPara* pExOriR, DOUBLE dThres = 0.0001 );

MLAPI( bool )  mlIntersectionVT(  Pt2d ptL, Pt2d ptR,  ExOriPara exOriL, ExOriPara exOriR, DOUBLE df1, DOUBLE df2, Pt3d &ptXYZ, DOUBLE dCoefConf = 0.0001 );

MLAPI( bool )  mlIntersectionWithAccu(  Pt2d ptL, Pt2d ptR, DOUBLE dCoefConf, DOUBLE df1, DOUBLE df2, ExOriPara exOriL, ExOriPara exOriR, \
                                        Pt3d &ptXYZ, Pt3d &ptOutXYZAccu, DOUBLE &dOutTotalAccu );
MLAPI( bool )  mlResectionNoInitialVal(  vector<Pt3d> vecGCPs, vector<Pt2d> vecImgPts, DOUBLE dFocalLength, ExOriPara &exOriRes );


MLAPI( bool )  mlResection( Pt2d *pImgPt,Pt3d *pGroundPt, double fx,double fy, SINT nPtNum,ExOriPara *pInitExOripara, ExOriPara *pExOripara );

MLAPI( bool )  mlSolvePts( vector<Pt3d> vecOldPts, vector<Pt3d> vecNewPts, UINT nTimes, ExOriPara* pInitialOri );
/**
* @fn mlRelaOriCalcWithOrigPts
* @date 2012.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��Զ���
* @param vecMatchPts ����ƥ��㣬������
* @param inOriL ���ڲ���
* @param inOriR ���ڲ���
* @param exOriRela ��Զ����������Ӱ��Ϊ��׼
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlRelaOriCalcWithOrigPts( vector<StereoMatchPt> vecMatchPts, InOriPara inOriL, UINT nHL, InOriPara inOriR, UINT nHR, ExOriPara &exOriRela  );
/**
* @fn mlSiteFindTiePoints
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief DOM����
* @param[in] vecStereoImg  ��ƽ��Ӱ�����Ϣ
* @param[out] vecTiePoints ���ӵ���Ϣ
* @param[in] extractPtsOpt ��������ȡ����
* @param[in] matchOpts ƥ�����
* @param[in] ransacOpts ransac����
* @param[in] mFilterOpts ��ֵ�˲�����
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlSiteFindTiePoints( vector<StereoSet> vecStereoImg, vector<ImgPtSet> &vecTiePoints, ExtractFeatureOpt extractPtsOpts, MatchInRegPara matchOpts, RANSACHomePara ransacOpts, MedFilterOpts mFilterOpts );


/**
* @fn mlBASolve
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief DOM����
* @param[in] vecStereoIn  ����Ӱ��Եĳ�ʼ��Ϣ
* @param[in] vecImgPtSets ���ӵ���Ϣ
* @param[out] vecStereoOut ���ƽ���������Ϣ
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

MLAPI( bool )  mlBASolve( vector<StereoSet> vecStereoIn, vector<ImgPtSet> vecImgPtSets, vector<StereoSet> &vecStereoOut, UINT nModel = 2 );

MLAPI( bool )  mlBASolveWithErr( vector<StereoSet> vecStereoIn, vector<ImgPtSet> vecImgPtSets, vector<StereoSet> &vecStereoOut, Pt2d &ptProjErr, UINT nModel = 2 );

MLAPI( bool )  mlBASolveVT( vector<StereoSet> vecStereoIn, vector<ImgPtSet> vecImgPtSets, vector<bool> vecbImgIsFixed, vector<StereoSet> &vecStereoOut, UINT nModel = 1 );
/**
* @fn mlDOMGeneration
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief DOM����
* @param[in] vec3dPts  ��άƥ���
* @param[in] strPath DEM·��
* @param[in] dbDemRect DEM���ɷ�Χ
* @param[in] dResolution ���ɷֱ���
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlDEMGenerationNoRect( vector<Pt3d> &vec3dPts, const SCHAR* strPath, DOUBLE dResolution, ImgDotType imgType, string strTriFile = ""  );

MLAPI( bool )  mlDEMGeneration( vector<Pt3d> &vec3dPts, const SCHAR* strPath, DbRect dbDemRect, DOUBLE dResolution, ImgDotType imgType, string strTriFile = "" );

MLAPI( bool )  mlDEMGenerationInRegion( vector< vector< Pt3d> > &vec3dPts, const SCHAR* strPath, DbRect dbDemRect, DOUBLE dResolution, ImgDotType imgType, string strTriFile = "" );

/**
* @fn mlDOMGeneration
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief DOM����
* @param[in] vecStereoSets  ������������Ӱ��
* @param[in] strDEMPath DEM·��
* @param[in] strDOMPath DOM·��

* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlDOMGeneration( vector<StereoSet> &vecStereoSets, const SCHAR* strDEMPath, const SCHAR* strDOMPath, ImgDotType imgType );
/**
* @fn mlPlaneNormal
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��ķ�����
* @param[in] vecXYZ  ��ά�㼯
* @param[out] pPlaneNormal1 ������1
* @param[out] pPlaneNormal2 ������2
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlPlaneNormal( vector<Pt3d> vecXYZ, Pt3d &pPlaneNormal );

/**
* @fn mlCalcLandPtCoord
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��ķ�����
* @param[in] ptObImgCentxy �۲�ͼ��վ���ͼ������
* @param[in] vecStereoMPts ƥ�����Ϣ�������Ϊ�۲�ͼ�������Ϊ��ͼ
* @param[out] ptLandPosInBMap վ���ڵ�ͼ�ϵ�ͼ������
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlCalcLandPtCoord( Pt2d ptObImgCentxy, vector<StereoMatchPt> vecStereoMPts, Pt2d &ptLandPosInBMap, DOUBLE &dPrecision );

/**
* @fn mlDealSiteImgSelection
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ѡ��ǰ��վ��������ͬ���������
* @param[in] vecSiteOne ��һվ��Ӱ���ⷽλ����
* @param[in] vecSiteTwo �ڶ�վ��Ӱ���ⷽλ����
* @param[out] nIDOne ��һվӰ�񼯺�����ѡ��Ӱ�����
* @param[out] nIDTwo �ڶ�վӰ�񼯺�����ѡ��Ӱ�����
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlDealSiteImgSelectionV( vector<StereoSet> vecSiteOne, vector<StereoSet> vecSiteTwo, UINT &nIDOne, UINT &nIDTwo );

MLAPI( bool )  mlDealSiteImgSelection( vector<StereoSet> vecSiteOne, vector<StereoSet> vecSiteTwo, StereoSet &sFSiteSet, StereoSet &sSSiteSet );

MLAPI( bool )  mlDealSiteImgSelectionReverse( vector<StereoSet> vecSiteOne, vector<StereoSet> vecSiteTwo, StereoSet &sFSiteSet, StereoSet &sSSiteSet );


MLAPI( bool )  mlSiteSIFTMatch( StereoSet sFirstSet, StereoSet sSecondSet, UINT nNumTilts, vector<Pt2d> &vecPtsInSiteOneLImg, vector<Pt2d> &vecPtsInSiteTwoLImg, DOUBLE dDisIn2SiteThres = 3, DOUBLE dCamHeight = 1.5 );

MLAPI( bool )  mlSiteSIFTMatchReverse( StereoSet sFirstSet, StereoSet sSecondSet, UINT nNumTilts, vector<Pt2d> &vecPtsInSiteOneLImg, vector<Pt2d> &vecPtsInSiteTwoLImg, DOUBLE dDisIn2SiteThres = 3, DOUBLE dCamHeight = 1.5 );

MLAPI( bool )  mlProjMap( StereoSet sFirstSet, StereoSet sSecondSet, DOUBLE dCamHeight, DOUBLE dRes, DOUBLE dRange, const SCHAR* strLProjMap, const SCHAR* strRProjMap );

MLAPI( bool )  mlSiteMatchByProjMap( StereoSet sFirstSet, StereoSet sSecondSet, DOUBLE dCamHeight, DOUBLE dRes, DOUBLE dRange, const SCHAR* strLProjMap, const SCHAR* strRProjMap, \
                                     vector<StereoMatchPt> vecInitSMPts, vector<Pt2d> &vecPtsInSiteOneLImg, vector<Pt2d> &vecPtsInSiteTwoLImg );

MLAPI( bool )  mlAffineSIFT( const SCHAR* strLImgPath, const SCHAR* strRImgPath, UINT nNumTilts, vector<Pt2d> &vecPtsInSiteOneLImg, vector<Pt2d> &vecPtsInSiteTwoLImg );

MLAPI( bool )  mlStereoMatchWithPtSet( const SCHAR* strL, const SCHAR* strR, vector<Pt2d> vecLPts, MatchInRegPara matchPara, vector<Pt2d> &vecRPts, vector<bool> &vecFlags );

MLAPI( bool )  mlGetMatchedPtsInTwoSites(   vector<Pt2d> vecPtsInSiteOneLImg,    //��һվ��ͼ�����õ��ĵ����꣬��ASIFT�õ�
                                            vector<Pt2d> vecPtsInSiteOneRImg,    //��һվ��ͼ�����õ��ĵ����꣬����Ӱ������������ϵ���õ�
                                            vector<bool> vecValidFlagInSiteOne,  // �������ϵ����һ���ɹ�������ƥ��ʱ�����ƥ��������������ģ��ڴ˽������룬���ж���Щ��Ӱ����Ǵ��ڶ�Ӧ��Ӱ��ƥ����

                                            vector<Pt2d> vecPtsInSiteTwoLImg,    //ͬ�ϣ�Ϊ�ڶ�վ���������Ϊ����
                                            vector<Pt2d> vecPtsInSiteTwoRImg,
                                            vector<bool> vecValidFlagInSiteTwo,

                                            vector<StereoMatchPt> &vecSMPtsInSiteOne,  //��һվ�е�ƥ����
                                            vector<StereoMatchPt> &vecSMPtsInSiteTwo  //�ڶ�վ�е�ƥ���ԣ����У������һվ�еĵ�Դ��ڶ�Ӧ��ϵ���� ��������ͬһ��� ��ʾ �ĵ� ͬ��
                                        );

MLAPI( bool ) mlDeletePtsByDisConsist( Pt3d ptCentXYZSiteOne, vector<Pt3d> vecPtXYZInSiteOne, Pt3d ptCentXYZSiteTwo, vector<Pt3d> vecPtXYZInSiteTwo, \
                                       DOUBLE dDisThres, DOUBLE dWeightThres, vector<bool> &vecFlags );

MLAPI( bool ) mlCalcSiteOirByStereoMPts( vector<StereoMatchPt> vecMatchedPtsInSiteOne,   //��һվƥ����
                                        vector<StereoMatchPt> vecMatchedPtsInSiteTwo,   //�ڶ�վƥ���ԣ�ͬvecMatchedPtsInSiteOne��һһ��Ӧ��ͬ�����ϵ
                                        StereoSet imgInSiteOne,           //�����һվӰ����ڡ��ⷽλԪ��
                                        StereoSet imgInSiteTwo,           //�����2վӰ����ڡ��ⷽλԪ��
                                        ExOriPara  exOriSiteTwoOrgin,      //�����2վ�� ̽�⳵ ��ʼ�� �ⷽλ������Ӱ���ⷽλ��ͬ�ڳ����ⷽλ����ͨ��ǰ��Ӱ���ⷽλ�ı仯���� �����ⷽλ��

                                        ExOriPara  &exOriSiteTwoModefied,  //��������Ҫ�ĳ����ⷽλ���
                                        Pt3d      &rmsXYZ,                //��λXYZ�����
                                        DOUBLE    &dTotalRMS,             //�������
                                        CAMTYPE  nCamTypeFirst = Nav_Cam,
                                        CAMTYPE  nCamTypeSecond = Nav_Cam
                                        );

MLAPI( bool ) mlCalcSiteOirByStereoMPtsVT( vector<StereoMatchPt> vecMatchedPtsInSiteOne,   //��һվƥ����
                                        vector<StereoMatchPt> vecMatchedPtsInSiteTwo,   //�ڶ�վƥ���ԣ�ͬvecMatchedPtsInSiteOne��һһ��Ӧ��ͬ�����ϵ
                                        StereoSet imgInSiteOne,           //�����һվӰ����ڡ��ⷽλԪ��
                                        StereoSet imgInSiteTwo,           //�����2վӰ����ڡ��ⷽλԪ��
                                        ExOriPara  exOriSiteTwoOrgin,      //�����2վ�� ̽�⳵ ��ʼ�� �ⷽλ������Ӱ���ⷽλ��ͬ�ڳ����ⷽλ����ͨ��ǰ��Ӱ���ⷽλ�ı仯���� �����ⷽλ��

                                        ExOriPara  &exOriSiteTwoModefied,  //��������Ҫ�ĳ����ⷽλ���
                                        Pt3d      &rmsXYZ,                //��λXYZ�����
                                        DOUBLE    &dTotalRMS,             //�������
                                        CAMTYPE  nCamTypeFirst = Nav_Cam,
                                        CAMTYPE  nCamTypeSecond = Nav_Cam
                                        );

MLAPI( bool ) mlMatchByCentPtLSM( const SCHAR* strL, const SCHAR* strR, Pt2d ptL, Pt2d ptGivenR, UINT nRange, UINT nTemplateSize, DOUBLE dCoefThres, \
                                  Pt2d &ptOutRes, DOUBLE &dCoef );

MLAPI( bool ) mlRegionDenseMatch( const SCHAR* strInPutLImgPath, const SCHAR* strInPutRImgPath, vector<StereoMatchPt> vecFeatMPts, UINT nStep, UINT nRadiusX, UINT nRadiusY, SINT nXOff, SINT nYOff, \
                                  UINT nTemplateSize, DOUBLE dCoefThres, DOUBLE dXmid, DOUBLE dYmid, UINT nHeight, UINT nWidth, vector<StereoMatchPt> &vecOutMRes  );
//����ľ����зֱ�Ϊ������λ�ã����ף��������������
/**
* @fn mlDealSiteImgSelection
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����չ���ǡ�ƫ���ǡ������Ǻͱ궨�İ��þ����������ڱ�������ϵ�µ���̬��λ�ã����뵥λΪ������ף������������
* @param[in] dExpAngle չ����
* @param[in] dYawAngle ƫ����
* @param[in] dPitchAngle ������
* @param[in] matMastExp2Body չ������ڱ���İ�װ����
* @param[in] matMastYaw2Exp ƫ�������չ���İ�װ����
* @param[in] matMastPitch2Yaw ���������ƫ���İ�װ����
* @param[in] matLCamBase2Pitch �������׼����ڸ����İ�װ����
* @param[in] matRCamBase2LCamBase �������׼������������׼�İ�װ����
* @param[in] matLCamCap2Base �������������ڻ�׼�İ�װ����
* @param[in] matRCamCap2Base �������������ڻ�׼�İ�װ����
* @param[out] exOriCamL ������ⷽλ
* @param[out] exOriCamR ������ⷽλ

* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool ) mlCalcCamOriByGivenInstallMatrix( DOUBLE dExpAngle, DOUBLE dYawAngle, DOUBLE dPitchAngle, stuInsMat matMastExp2Body, stuInsMat matMastYaw2Exp, stuInsMat matMastPitch2Yaw, \
                                         stuInsMat matLCamBase2Pitch, stuInsMat matRCamBase2LCamBase, stuInsMat matLCamCap2Base, stuInsMat matRCamCap2Base, \
                                         ExOriPara &exOriCamL, ExOriPara &exOriCamR );

MLAPI( bool ) mlCalcCamOriInWorldByGivenInsMat( stuInsMat matBase, DOUBLE dExpAngle, DOUBLE dYawAngle, DOUBLE dPitchAngle, stuInsMat matMastExp2Body, stuInsMat matMastYaw2Exp, stuInsMat matMastPitch2Yaw, \
                                         stuInsMat matLCamBase2Pitch, stuInsMat matRCamBase2LCamBase, stuInsMat matLCamCap2Base, stuInsMat matRCamCap2Base, \
                                         ExOriPara &exOriCamL, ExOriPara &exOriCamR );


MLAPI( bool ) mlCalcHazCamInWorld( stuInsMat matLCamBase2Body, stuInsMat matRCamBase2LCamBase, stuInsMat matLCamCap2Base, stuInsMat matRCamCap2Base, \
                                    ExOriPara &exOriCamL, ExOriPara &exOriCamR );

MLAPI( bool ) mlCalcHazCamInBodyVT( stuInsMat matLCamCap2Body, stuInsMat matLCamCap2RCamCap, ExOriPara &exOriCamL, ExOriPara &exOriCamR );

MLAPI( bool ) mlPt3dTrans( Pt3d ptXYZOrig, ExOriPara exOri, Pt3d &ptXYZRes );

MLAPI( bool ) mlPt3dTransBody2Cam( Pt3d ptXYZOrig, ExOriPara exOri, Pt3d &ptXYZRes );

MLAPI( bool ) mlGeoFileTrans( const SCHAR* pImgIn, const SCHAR* pImgOut, ImgDotType imgType );

/**
* @fn mlDenseMatchPyra
* @date 2011.12.14
* @author �틠 pengman@irsa.ac.cn
* @brief Ӱ��������ܼ�ƥ��
* @param[in] strInPutLImgPath ��Ӱ��
* @param[in] strInPutLImgPath ��Ӱ��
* @param[in] vecFeatMPts ������㼯
* @param[in] nStep ƥ�䲽��
* @param[in] nRadiusX ����X����뾶����
* @param[in] nRadiusY ����Y����뾶����
* @param[in] nXOff X��������λ��ƫ����
* @param[in] nYOff Y��������λ��ƫ����
* @param[in] nTemplateSize ģ���С
* @param[in] dCoefThres ���ϵ����ֵ.000000
* @param[in] nlevel ����������
* @param[out] vecOutMRes ƥ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlDenseMatchPyra( const SCHAR* strInPutLImgPath, const SCHAR* strInPutRImgPath, vector<StereoMatchPt> vecFeatMPts, UINT nStep, UINT nRadiusX, UINT nRadiusY, SINT nXOff, SINT nYOff, \
                                        UINT nTemplateSize, DOUBLE dCoefThres, vector<StereoMatchPt> &vecOutMRes, SINT nlevel = 2 );



MLAPI( bool )  mlGeoRasterVerify( const SCHAR* strDemIn,  const SCHAR* strDomIn,  const SCHAR* strDemOut );

MLAPI( bool )  mlGetGeoInfo( const SCHAR* strGeoFile, Pt2d &ptOrig, DOUBLE &dXRes, DOUBLE &dYRes, UINT &nW, UINT &nH, DOUBLE &dNoDataVal );

MLAPI( bool )  mlSetGeoInfo( const SCHAR* strGeoFile, Pt2d ptOrig, DOUBLE dXRes, DOUBLE dYRes, DOUBLE dNoDataVal );

MLAPI( bool )  mlGeoMergeInRegion( const SCHAR* strBaseMap, const SCHAR* strToProceedMap, const SCHAR* strOutRes, vector<Polygon2d> vecPolygon );

MLAPI( bool )  mlGeoMerge( const SCHAR* strBaseMap, const SCHAR* strToProceedMap, const SCHAR* strOutRes, bool bIsDem = true );

MLAPI( bool )  mlConvertGeoFileYRes( const SCHAR* strSrcFile, const SCHAR* strDstFile );

MLAPI( bool )  mlCalcDisparityPerRow( DOUBLE dUnitDis, DOUBLE dCamHeight, UINT nImgH, UINT nMinStep, UINT nMaxStep, UINT nBlockSize, DOUBLE df, ExOriPara exOriL, stuBlockDeal &stuBDRes );

MLAPI( bool )  mlCalcMinXOff( DOUBLE dCamHeight, UINT nImgH, DOUBLE df, DOUBLE dBaseLength, ExOriPara exOriL, SINT &nXOffMin );

MLAPI( bool )  mlGeoFileEnLargeUnit( const SCHAR* strInGeoFile, const SCHAR* strOutGeoFile, DOUBLE dRatio = 1000 );

MLAPI( bool )  mlPt2dInDifImg( Pt2d ptOrig, UINT nOriHeight, InOriPara inOri1, ExOriPara exOri1, CAMTYPE nCamType, UINT nNewHeight, InOriPara inOri2, ExOriPara exOri2, Pt2d &ptRes );

MLAPI( bool )  mlPt3dProjInOrigImg( Pt3d ptXYZ, InOriPara inOri, ExOriPara exOri, UINT nH, CAMTYPE nCamType, Pt2d &ptRes );
//------------------------------------------------------------------------------
MLAPI( bool )  mlFindMatchHoleInImg( vector<Pt2i> vecMatchedPts, UINT nW, UINT nH, UINT nHoleRange, vector<Polygon2d> &vecHolePolys );

//-----------------------------------------------------------------------------
MLAPI( bool )  mlGetGeoFilePtr( const SCHAR* strGeoFile, void* &geoDataPtr );
MLAPI( bool )  mlGetGeoZ( void* geoDataPtr, Pt2d ptXY, DOUBLE &dZ );
MLAPI( bool )  mlGetGeoZByIdx( void* geoDataPtr, UINT nX, UINT nY, Pt3d &ptXYZ );
MLAPI( bool )  mlFreeGeoPtr( void* &geoDataPtr );

MLAPI( bool )  mlJPToGeoTiff( const SCHAR* strJPG, const SCHAR *strOutTiff, Pt2d ptOrig, DOUBLE dXRes, DOUBLE dYRes, DOUBLE dNoDataVal );





















#endif


