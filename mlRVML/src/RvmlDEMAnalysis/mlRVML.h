#ifndef _MLRVML_H_
#define _MLRVML_H_
#include "mlBase.h"
#include "mlTypes.h"
/**
* @fn mlSingleCamCalib
* @date 2012.2.21
* @author �⿭ wukai@irsa.ac.cn
* @brief ������궨
* @param vecImgPts ��־������������
* @param vecObjPts ��־���﷽��������
* @param nW Ӱ����
* @param nH Ӱ��߶�
* @param inPara ����ڷ�λ����
* @param exPara ����ⷽλ����
* @param vecError ��־���񷽲в�����
* @param bFlag �ж��ǽ�������ٱ궨�������Ǽ����񷽾��ȼ��
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
* @param vecLImgPts ��־�����������������
* @param vecRImgPts ��־�����������������
* @param vecObjPts ��־��������﷽��������
* @param vecObjPts ��־��������﷽��������
* @param nW Ӱ����
* @param nH Ӱ��߶�
* @param inLPara ������ڷ�λ����
* @param inRPara ������ڷ�λ����
* @param exLPara ������ⷽλ����
* @param exRPara ������ⷽλ����
* @param exStereoPara �����������ⷽλ����
* @param vecError ��־���﷽�в�����
* @param bFlag �ж��ǽ�������ٱ궨�������Ǽ����﷽���ȼ��
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
* @param imgpts ��־��������
* @param InOriInput �ڷ�λԪ��
* @param exOriOut ��Ƭ�ⷽλԪ��
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
* @param NavCamPara,�����������
* @param PanCamPara,ȫ���������
* @param AnaPara,ȫ���������
* @param OptiBase,��������Ż���
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
* @param vecStereoSet,�������
* @param WidePara��������ƥ��ṹ�����
* @param vecFPtSetL���������Ӱ��������
* @param vecFPtSetR���������Ӱ��������
* @param vecDPtSetL���������Ӱ���ܼ���
* @param vecDPtSetR���������Ӱ���ܼ���
* @param strDemFile������DEM�ļ�·��
* @param strDomFile������DOM�ļ�·��
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
MLAPI( bool )  mlDenseMatch(StereoSet* pStereoSet, WideOptions WidePara, ImgPtSet& vecDPtSetL, ImgPtSet& vecDPtSetR);
/**
* @fn mlDisparityMap
* @date 2011.11.02
* @author �틠 pengman@irsa.ac.cn
* @brief �����ܼ�ƥ��������Ӳ�ͼ
* @param imgPtL ��Ӱ���ܼ�ƥ���
* @param imgPtR ��Ӱ���ܼ�ƥ���
* @param strDisFile �Ӳ�ͼ����·��
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
 *@param pArr ������������ָ��
 *@param strumat ת����ϵ�ṹ��
 *@param pTransResult ����ת������
 *@param nflag ת��״̬���� Ĭ��Ϊ0
         ����ת����ϵ B = R*A + T (RΪ��ת����TΪƽ������)
         ��nflag=0ʱ����ʾ��A��B��
         ��nflagΪ����ֵ����ʾ��B��A
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

*/
MLAPI( bool )  mlCoordTransResult(DOUBLE* pArr,TransMat strumat,DOUBLE* pTransResult,SINT nflag);

/**
* @fn mlSatMatch
* @date 2012.2.21
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ��������ƥ��
* @param sLimgPath ��Ӱ��·��
* @param sRimgPath ��Ӱ��·��
* @param satPara ƥ�����
* @param vecRanPts ƥ���
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
* @param vecLineEo  Ӱ����Ԫ��
* @param vecAngleEo Ӱ���Ԫ��
* @param vecImg_time Ӱ��ÿ�г���ʱ��
* @param vecE ÿ��Ӱ����ⷽλԪ��
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
* @param satProj ����Ӱ��DEM��DOM���ɹ��̲���
* @param satPara ����Ӱ��DEM��DOM���ɲ���
* @param vecRanPts ƥ���
* @param vecDensePts �ܼ�ƥ��㼰�﷽��ά��
* @param vecPres  �﷽��ά�㾫��
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
* @param vecStereoSet ��վ���������Ϣ
* @param vecImgPtSets ������Զ�Ӧ�ĵ���Ϣ�����������������ƥ��
* @param ptLT �����ɷ�Χ���Ͻ�
* @param ptRB �����ɷ�Χ���½�
* @param dResolution DEM��DOM���ɵķֱ���
* @param strDemPath DEM����·��
* @param strDomPath Dom����·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
MLAPI( bool )  mlMapByInteBlock(   vector<StereoSet> &vecStereoSet, vector< ImgPtSet > &vecImgPtSets, Pt2d ptLT, Pt2d ptRB, DOUBLE dResolution,
                                   string strDemPath, string strDomPath );

/**
* @fn mlPanoMatchPts
* @date 2012.2.21
* @author ����
* @brief ����ԭʼͼ�������ƥ����ļ�
* @param vecParam ȫ��ƴ�Ӳ���
* @param vecFrmInfo ԭʼͼ��ͼ����Ϣ
* @param vecImgPtSets ԭʼͼ���Ӧ����Ϣ
* @param strOutPath ���ƥ����ļ�·��
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
* @param vecParam ȫ��ƴ�Ӳ���
* @param vecFrmInfo ԭʼͼ��ͼ����Ϣ
* @param vecImgPtSets ԭʼͼ���Ӧ����Ϣ
* @param strOutPath ���ȫ��ͼ��·��
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
 *@param vecPt3dIn ��Ҫ�򻯵�������������
 *@param vecPt3dOut �򻯺��������������
 *@param simpleIndex ��ϵ�� ȡֵΪ0��1֮��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlTinSimply(vector<Pt3d> &vecPt3dIn,vector<Pt3d> &vecPt3dOut,DOUBLE simpleIndex);
/**
 *@fn mlCalcTransMatrixByLatLong
 *@date 2011.11
 *@author ������
 *@brief ���������ݶ�λ�ľ�γ��ʵ���¹�ϵ���ֲ�����ϵת����ϵ���
 *@param dLat ��λ��γ��  ��λΪ��   ��ΧΪ-90�ȡ�90��  ��γΪ�� ��γΪ��
 *@param dLong ��λ�ľ��� ��λΪ��   ��ΧΪ-180-180��  ����Ϊ�� ����Ϊ��
 *@param tmat  �洢ת������ת������ƽ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

*/
MLAPI( bool )  mlCalcTransMatrixByLatLong(DOUBLE dLat,DOUBLE dLong,TransMat& tmat);
/**
 *@fn mlCalcTransMatrixByXYZ
 *@date 2011.11
 *@author ������
 *@brief ������ʵ���¹�ϵ���ֲ�����ϵת����ϵ���
 *@param dLocResult_x ��½�����¹�ϵ�µþ�ȷ��λ���X
 *@param dLocResult_y ��½�����¹�ϵ�µþ�ȷ��λ���Y
 *@param dLocResult_z ��½�����¹�ϵ�µþ�ȷ��λ���Z
 *@param tmat  �洢ת������ת������ƽ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

*/
MLAPI( bool )  mlCalcTransMatrixByXYZ(DOUBLE dLocResult_x,DOUBLE dLocResult_y,DOUBLE dLocResult_z,TransMat& tmat);
/**
 *@fn mlVisualImage
 *@date 2012.02
 *@author ������
 *@brief ����DEM��DOM����ָ���ӽ��µķ���ͼ��
 *@param strDem DEM·�����ļ�����geotiff�ļ���ʽ��������������
 *@param strDom DOM·�����ļ�����geotiff�ļ���ʽ��������������
 *@param outImg ����ļ�����
 *@param ExOriPara ָ���ӽ��ⷽλԪ��
 *@param fx��fy ����
 *@param nImgWid nImgHei ����ͼ��Ŀ���
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlVisualImage( const SCHAR* strDem,const SCHAR* strDom,const SCHAR* outImg,ExOriPara exori,DOUBLE fx,DOUBLE fy,SINT nImgWid,SINT nImgHei);

/**
 *@fn mlPano2Prespective
 *@date 2012.02
 *@author ����
 *@brief ����ȫ��ͼ�񣬶���֪��Χ����͸��ͼ��
 *@param cInputPanoFile �����ȫ��ͼ��·��
 *@param cOutputImage �����͸��ͼ��·��
 *@param nOriginX ѡȡ��Χ�����Ͻǵ�X����
 *@param nOriginY ѡȡ��Χ�����Ͻǵ�Y����
 *@param nPanoRoiW ѡȡ��Χ�Ŀ��
 *@param nPanoRoiH ѡȡ��Χ�ĸ߶�
 *@param dFocus ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlPano2Prespective( const SCHAR *cInputPanoFile, const SCHAR * cOutputImage, SINT nOriginX, SINT nOriginY, SINT nPanoRoiW, SINT nPanoRoiH, DOUBLE dFocus);

/**
 *@fn mlDEMMosaic
 *@date 2012.02
 *@author ����
 *@brief demƴ��
 *@param vecInputFiles �����ԭʼdem
 *@param cOutputFile ����ļ�·��, DOUBLE , DOUBLE , SINT , SINT
 *@param dXResl ����ļ�x����ֱ���
 *@param dYResl ����ļ�����ֱ���
 *@param nResampleAlg �ز����㷨��Ĭ��˫���Բ�ֵ)
 *@param nDisCultLine ƴ���ߣ�Ĭ��Ϊ�գ�
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlDEMMosaic( vector<string> vecInputFiles, const SCHAR* cOutputFile, DOUBLE dXResl, DOUBLE dYResl, SINT nResampleAlg, SINT nDisCultLine);
/**
* @fn mlComputeInsightMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ���������DEM���ݺ��ӵ����꣬����ͨ��ͼ
* @param sInputDEM,  ����DEM�ļ�·��
* @param nxLocation, �ӵ�x����
* @param nyLocation, �ӵ�y����
* @param ViewHight��  �ӵ�������ĸ߶�
* @param sDestDEM��   ����ļ�·��
* @param InverseHeight�� �Ƿ񽫸̷߳�ת
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeInsightMap( const SCHAR * sInputDEM, SINT nxLocation ,SINT nyLocation, DOUBLE dViewHight, const SCHAR * sDestDEM, bool InverseHeight);

/**
* @fn mlComputeSlopeMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݣ��ͼ��㴰�ڴ�С������¶�
* @param sInputDEM,  ����DEM�ļ�·��
* @param nWindowSize, ���㴰�ڴ�С
* @param sDestDEM, ����ļ�·��
* @param dZfactor�� �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
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
* @param sInputDEM,  ����DEM�ļ�·��
* @param nWindowSize, ���㴰�ڴ�С
* @param sDestDEM, ����ļ�·��
* @param dZfactor�� �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
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
* @param sInputDEM,  ����DEM�ļ�·��
* @param nWindowSize, ���㴰�ڴ�С
* @param sDestDEM, ����ļ�·��
* @param dZfactor�� �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
* @param ObPara: �ϰ�ͼ�����ṹ��
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
* @param dHinterval,  �ȸ߾�
* @param strSrcfilename, �����DEM�ļ�·��
* @param strDstfilename, �����shape�ļ�·��
* @param bCNodata�� ��ʾ�Ƿ��Զ���Nodataֵ
* @param dNodata�� ���bCNodata����Ϊtrue����dNodata ��ֵ�ڼ���ʱ��������Чֵ�Դ�
* @param cAttrib������shape�ļ��̵߳��������ƣ�Ĭ��Ϊelev
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
 *@param strFileIn ���ü��������ļ�
 *@param strFileOut �ü�������ļ�
 *@param pttl �ü����Ͻǵ�
 *@param ptbr �ü����½ǵ�
 *@param nWidth nHeight �ü��� ��
 *@param nflag ָ���ü���ʽ 1Ϊ�����زü� 2Ϊ����������ü�
 *@param nCutBands ָ���ü����� Ϊ����ʱ��ʾ���в��ζ��ü� Ϊ��ʱ�ü��ض��Ĳ���
 *@param dZoom����ϵ�� Ĭ��Ϊ1
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlGeoRasterCut( const SCHAR* strFileIn,const SCHAR* strFileOut,DOUBLE pttl_x,DOUBLE pttl_y,DOUBLE ptbr_x,DOUBLE ptbr_y,SINT nflag, SINT nCutBands, DOUBLE dZoom);
/**
* @fn mlLocalByMatch
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ��͵���Ӱ���ƥ��ʵ�ֶ�λ
* @param strLandDom ����Ӱ���ļ�·��
* @param strSatDom ����Ӱ��ƥ�������
* @param LandImgPtset ����Ӱ��ƥ�������
* @param SatImgPtset ����Ӱ��ƥ�������
* @param localByMOpts ƥ�����
* @param ptLocalRes ��λ���
* @param dLocalAccuracy ��λ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlLocalByMatch( const SCHAR* strLandDom, const SCHAR* strSatDom,  ImgPtSet &LandImgPtset, ImgPtSet &SatImgPtset, LocalByMatchOpts localByMOpts, Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );
/**
* @fn mlLocalByIntersection
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
MLAPI( bool )  mlLocalByIntersection( vector<Pt3d> vecGCPs, vector< ImgPtSet > &vecImgPtSets,  Pt3d &ptLocalRes, DOUBLE &dLocalAccuracy );
/**
* @fn mlLocalIn2Site
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief վ���Ӱ��λ
* @param vecFrontSite ǰվ������Ӱ��
* @param vecEndSite ��վ������Ӱ��
* @param vecFrontPts ǰվ���������
* @param vecEndPts ��վ���������
* @param localBy2Opt ��λ��������
* @param ptLocalRes ��λ���
* @param dLocalAccuracy ��λ����
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
* @param FrameInfoSet ����Ӱ��·������Ϣ
* @param strSatDom ����Ӱ��·��
* @param frmPts ����Ӱ��㼯
* @param SatPts ����Ӱ��㼯
* @param stuLocalBySeqOpts ��λ��������
* @param ptLocalRes ��λ���
* @param dLocalAccuracy ��λ����
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
* @param vecStereoSet վ����������Ӱ��
* @param vecGCPs ��������ά����
* @param vecImgPts ƥ����
* @param stuLocalByLanderOpts ��λ����
* @param vecLocalRes ��λ���
* @param vecLocalAccuracy ��λ����
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
* @param nTemplateSize �˲�ģ���С
* @param dCoef �˲��˲���,һ����0.8Ϊ��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlSmoothByGaussian(const SCHAR* strFileIn, SINT nTemplateSize, DOUBLE dCoef );
/**
* @fn mlGetEpipolarImg
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���ɺ���Ӱ��
* @param pStereoSet ���������Ϣ
* @param strFileOutL ��Ӱ�����Ӱ��·��
* @param strFileOutR ��Ӱ�����Ӱ��·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlGetEpipolarImg(StereoSet* pStereoSet, const SCHAR* strFileOutL, const SCHAR* strFileOutR);

/**
* @fn mlSift
* @date 2011.12.16
* @author �틠  pengman@irsa.ac.cn
* @brief siftƥ�书��
* @param pStereoSet ���������Ϣ
* @param WidePara ƥ������ṹ��
* @param strFileOutL ƥ������·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlSift(StereoSet* pStereoSet, WideOptions WidePara,const SCHAR* strFileOut);

/**
* @fn mlASift
* @date 2011.12.16
* @author �틠  pengman@irsa.ac.cn
* @brief Asiftƥ�书��
* @param pStereoSet ���������Ϣ
* @param strFileOutL ƥ������·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlASift(StereoSet* pStereoSet, const SCHAR* strFileOut);

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
MLAPI( bool )  mlTemplateMatchImg(SCHAR* pLeftImg, SCHAR* pRightImg, vector<Pt2i> &vecPtL, \
                                  vector<Pt2i> &vecPtR, vector<StereoMatchPt> &vecFeatMatchPts, MLRect rectSearch, SINT nTemplateSize, \
                                  DOUBLE dCoef, SINT nXOffSet, SINT nYOffSet);

/**
* @fn mlLSMatchImg
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ����С����ƥ�䣬������Ӱ����һ��ȡ����Ӱ����ͬ����
* @param pLeftImg ��Ӱ��·��
* @param pRightImg ��Ӱ��·��
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
MLAPI( bool )  mlLSMatchImg(SCHAR* pLeftImg, SCHAR* pRightImg, DOUBLE dLx, DOUBLE dLy, DOUBLE& dRx, DOUBLE& dRy, SINT nTempSize, DOUBLE& dCoef);
/**
* @fn mlExtractFeatPtByForstner
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ��Forstner������ȡ������
* @param pImg  ����Ӱ��·��
* @param m_vecFeaPts ��ȡ��������
* @param nGridSize ������С
* @param nPtNum ����ȡ�ĵ���
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlExtractFeatPtByForstner( SCHAR* pImg, vector<Pt2i> m_vecFeaPts, SINT nGridSize, SINT nPtNum = 0);

/**
* @fn mlRansacPts
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ransac�����޳�����ƥ���ֲ�
* @param MatchPts ����ƥ���
* @param dThresh ��ֵ
* @param dConfidence ���Ŷ�
* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlRansacPts( vector<StereoMatchPt> &MatchPts, DOUBLE dThresh, DOUBLE dConfidence);
/*
* @fn GmlGetNewStereoPtID
* @date 2012.02.10
* @author  ���Ļ� whwan@irsa.ac.cn
* @brief ��ȡƥ���ı��
* @param clsLPts ��Ӱ����Ϣ
* @param clsRPts ��Ӱ����Ϣ
* @param lID ƥ���ı��
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
* @param clsImgPts Ӱ����Ϣ
* @param lID ƥ���ı��
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
* @param strFileName ��־·��
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

#endif


