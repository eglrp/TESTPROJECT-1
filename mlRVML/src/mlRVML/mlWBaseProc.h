/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlWBaseProc.h
* @date 2011.11.18
* @author �틠 pengman@irsa.ac.cn
* @brief ��������ͼ��ͷ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
* �틠  2011.11.29  1.0  ת��Ϊc++���
*/
#ifndef MLWBASEPROC_H
#define MLWBASEPROC_H

#include "mlWBaseProc.h"
#include "mlBase.h"
#include "mlMat.h"
#include "mlFrameImage.h"
#include "mlTypeConvert.h"
#include "mlPtsManage.h"

/**
* @class CmlWBaseProc
* @date 2011.11.18
* @author �틠 pengman@irsa.ac.cn
* @brief ��������ͼ����ģ���ඨ��
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*
*/
class CmlWBaseProc
{
public:
    /**
    * @fn CmlWBaseProc()
    * @date 2011.12.1
    * @author �틠
    * @brief �ղι��캯��
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    CmlWBaseProc();

    /**
    * @fn ~CmlWBaseProc()
    * @date 2011.12.1
    * @author �틠
    * @brief ��������
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    virtual ~CmlWBaseProc();

    /**
    * @fn WideBaseAnalysis
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
    bool WideBaseAnalysis(InOriPara NavCamPara, InOriPara PanCamPara, BaseOptions AnaPara,double &OptiBase);

    /**
    * @fn WideBaseMapping
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
   // bool WideBaseMapping(vector<StereoSet> &vecStereoSet, vector<string> &vecStrMatchFile, int nColRadius,int nRowRadius,int nTemplateSize,int nGridSize,DOUBLE dRes,DOUBLE dCoef, char * strDemPath, bool bIsUsingFeatPt, bool bIsUsingPartion );

    bool WideBaseMapping(vector<StereoSet> vecStereoSet, WideOptions WidePara,vector<ImgPtSet>& vecFPtSetL, vector<ImgPtSet>& vecFPtSetR, vector<ImgPtSet>& vecDPtSetL, vector<ImgPtSet>& vecDPtSetR,SCHAR *strDemFile);


    /**
    * @fn WideBase3Ds
    * @date 2011.12.1
    * @author �틠
    * @brief �����ߵ�������
    * @param vecStereoSet,�������
    * @param vecLPts����Ӱ��ƥ���
    * @param vecRPts����Ӱ��ƥ���
    * @param vec3ds�����ɵ����ļ�
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    bool WideBase3Ds(StereoSet* pStereoSet, vector<Pt2d>& vecLPts, vector<Pt2d>& vecRPts, vector<Pt3d>& vec3ds);

    //bool WideBase3Ds(StereoSet* pStereoSetf, StereoSet* pStereoSets, vector<Pt2d>& vecLPts, vector<Pt2d>& vecRPts, vector<Pt3d>& vec3ds);

    /**
    * @fn WideDenseMatch
    * @date 2011.12.1
    * @author �틠
    * @brief �ܼ�ƥ��
    * @param LOriImg,��ƥ����Ӱ��
    * @param ROriImg����ƥ����Ӱ��
    * @param WidePara��������ƥ����ز���
    * @param vecFPtL����Ӱ��������
    * @param vecFPtR����Ӱ��������
    * @param vecMPtL����Ӱ���ܼ���
    * @param vecMPtR����Ӱ���ܼ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    bool WideDenseMatch(CmlRasterBlock LOriImg,CmlRasterBlock ROriImg, WideOptions WidePara, vector<Pt2d> &vecFPtL, vector<Pt2d> &vecFPtR, vector<Pt2d> &vecMPtL, vector<Pt2d> &vecMPtR);

    /**
    * @fn WideFeaMatch
    * @date 2011.12.1
    * @author �틠
    * @brief ����ƥ��
    * @param LOriImg,��ƥ����Ӱ��
    * @param ROriImg����ƥ����Ӱ��
    * @param WidePara��������ƥ����ز���
    * @param vecPtL����Ӱ��������
    * @param vecPtR����Ӱ��������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    bool WideFeaMatch(CmlRasterBlock LOriImg,CmlRasterBlock ROriImg, WideOptions WidePara, vector<Pt2d> &vecPtL, vector<Pt2d> &vecPtR);

    /**
    * @fn WidePtsFilter
    * @date 2011.12.1
    * @author �틠
    * @brief �Գ������ܼ������ά�����˲�ȥ���ֲ�
    * @param vecFPts,��������ά��������
    * @param vecDPts,�ܼ�����ά��������
    * @param vec3dPts, �ܵ���ά��������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    bool WidePtsFilter(vector<Pt3d>& vecFPts, vector<Pt3d>& vecDPts, vector<Pt3d>& vec3dPts);
    /**
    * @fn mlBestBase
    * @date 2011.12.1
    * @author �틠
    * @brief �������Ż��߳�
    * @param mlNav,�����������
    * @param mlPan, ȫ���������
    * @param dOptiBase,���Ż��߳�
    * @param dFixBase,��������̶����߳�
    * @param dPixel,����ƥ�����
    * @param dTarget,Ŀ�����
    * @param nWidth,Ӱ����
    * @param dBase,���߳���������
    * @param dThreshold,��ֵ��С
    * @param dIterTime,��������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    DOUBLE mlBestBase(InOriPara mlNav, InOriPara mlPan,DOUBLE dOptiBase,DOUBLE dFixBase, DOUBLE dPixel, DOUBLE dTarget, UINT nWidth,DOUBLE * dBase,DOUBLE dThresHold, DOUBLE dIterTime);
protected:

//private:
public:
    /**
    * @fn mlFunAcc
    * @date 2011.12.1
    * @author �틠
    * @brief ��ͼ���Ⱥ�����һ�׵����Ͷ��׵���
    * @param dFixBase,��������̶����߳�
    * @param dBase,���߳���������
    * @param dFunAcc,һ�׵����Ͷ��׵���
    * @param mlNav,�����������
    * @param mlPan,ȫ���������
    * @param dPixel,����ƥ�����
    * @param dTarget,Ŀ�����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void mlFunAcc(DOUBLE dFixBase,DOUBLE dBase,DOUBLE dFunAcc[2],InOriPara mlNav, InOriPara mlPan,DOUBLE dPixel, DOUBLE dTarget);

    /**
    * @fn mlNewTon
    * @date 2011.11.22
    * @author �틠
    * @brief ţ�ٵ�������⺯��ֵ
    * @param dFixBase,��������̶����߳�
    * @param dBase,���߳���������
    * @param dThreshold,��ֵ��С
    * @param dIterTime,��������
    * @param mlNav,�����������
    * @param mlPan,ȫ���������
    * @param dPixel,����ƥ�����
    * @param dTarget,Ŀ�����
    * @retval TRUE �ɹ�
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    DOUBLE mlNewTon(DOUBLE dFixBase,DOUBLE * dBase,DOUBLE dThresHold, DOUBLE dIterTime,InOriPara mlNav, InOriPara mlPan,DOUBLE dPixel, DOUBLE dTarget);

    /**
    * @fn mlOriPtToEpi
    * @date 2011.12.1
    * @author �틠
    * @brief ��ԭʼӰ���ƥ���ת������Ӱ���ϵĵ�
    * @param vecOPtsL��ԭʼ��Ӱ��ƥ���
    * @param vecOPtsR��ԭʼ��Ӱ��ƥ���`
    * @param LeftHomo����Ӱ��͸�Ӿ���
    * @param RightHomo����Ӱ��͸�Ӿ���
    * @param vecEPtsL,�����Ӱ��ƥ���
    * @param vecEPtsR,�Һ���Ӱ��ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    bool mlOriPtToEpi(const vector<Pt2d>& vecOPtsL, const vector<Pt2d>& vecOPtsR,CmlMat& LeftHomo, CmlMat& RightHomo, vector<Pt2d>& vecEPtsL, vector<Pt2d>& vecEPtsR);

    /**
    * @fn mlEpiPtToOri
    * @date 2011.12.1
    * @author �틠
    * @brief ������Ӱ���ƥ���ת��ԭʼӰ���ϵĵ�
    * @param vecEPtsL,�����Ӱ��ƥ���
    * @param vecEPtsR,�Һ���Ӱ��ƥ���
    * @param LeftHomo����Ӱ��͸�Ӿ���
    * @param RightHomo����Ӱ��͸�Ӿ���
    * @param vecOPtsL��ԭʼ��Ӱ��ƥ���
    * @param vecOPtsR��ԭʼ��Ӱ��ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    bool mlEpiPtToOri(const vector<Pt2d>& vecEPtsL, const vector<Pt2d>& vecEPtsR,CmlMat& LeftHomo, CmlMat& RightHomo, vector<Pt2d>& vecOPtsL, vector<Pt2d>& vecOPtsR);

    /**
    * @fn mlWideEpiImg
    * @date 2011.12.9
    * @author �틠
    * @brief ������ȷƥ��ĵ��������������ɳ�����Ӱ��ĺ���Ӱ��
    * @param vecEPtsL,��Ӱ��ƥ�����
    * @param vecEPtsR,��Ӱ��ƥ�����
    * @param pLOriImg,ԭʼ��Ӱ��
    * @param pROriImg,ԭʼ��Ӱ��
    * @param pLEpiImg,��Ӱ�����Ӱ��
    * @param pREpiImg,��Ӱ�����Ӱ��
    * @param LeftHomo,��Ӱ��Ӧ����
    * @param RightHomo,��Ӱ��Ӧ����
    * @retval TRUE �ɹ�
    * @version 1.1
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    bool mlWideEpiImg(const vector<Pt2d>& vecEPtsL, const vector<Pt2d>& vecEPtsR, CmlRasterBlock *pLOriImg, CmlRasterBlock *pROriImg, CmlRasterBlock *pLEpiImg, CmlRasterBlock *pREpiImg, CmlMat &LeftHomo, CmlMat &RightHomo);

};

#endif // MLWBASEPROC_H
