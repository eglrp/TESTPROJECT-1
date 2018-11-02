/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlWBaseProc.cpp
* @date 2011.11.18
* @author �틠 pengman@irsa.ac.cn
* @brief ��������ͼ��Դ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
* �틠  2011.11.29  1.0  ת��Ϊc++���
*/
#include "mlWBaseProc.h"
#include "mlFrameImage.h"
#include "mlStereoProc.h"
#include "mlSiteMapping.h"
#include "mlTypes.h"
#include "SiftMatch.h"
#include "mlCamCalib.h"
using namespace cv;
using namespace std;

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
CmlWBaseProc::CmlWBaseProc()
{
    //ctor
}

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
CmlWBaseProc::~CmlWBaseProc()
{
    //dtor
}
/** @brief WideBaseMappSUINT
  *
  * @todo: document this function
  */

//bool CmlWBaseProc::WideBaseMapping(char *nFileNameIn,char *FileNameOut)
//{
//
//    return true;
//}
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
bool CmlWBaseProc::WideBaseAnalysis(InOriPara NavCamPara, InOriPara PanCamPara, BaseOptions AnaPara,double &OptiBase)
{

    //���������ļ��������������������Ż���
    DOUBLE *dBestBase;
//    DOUBLE dOptiBase;

    //�ж��Ƿ������������
    if((NavCamPara.f == 0)|| (NavCamPara.x == 0) ||(NavCamPara.y == 0))
    {
        SCHAR strErr[] = "Parameters of Navcam Camera are incorrect!";
        LOGAddErrorMsg(strErr);
        return false;
    }
    if((PanCamPara.f == 0)|| (PanCamPara.x == 0) ||(PanCamPara.y == 0))
    {
        SCHAR strErr[] = "Parameters of Pancam Camera are incorrect!";
        LOGAddErrorMsg(strErr);
        return false;
    }
    if((AnaPara.dThresHold != 0.000001)|| (AnaPara.nIterTime < 60))
    {
        SCHAR strErr[] = "Iterative parameters are incorrect!";
        LOGAddErrorMsg(strErr);
        return false;
    }

    OptiBase=this->mlBestBase(NavCamPara,PanCamPara, OptiBase,AnaPara.dFixBase,AnaPara.dPixel,AnaPara.dTarget, AnaPara.nWidth,dBestBase,AnaPara.dThresHold, AnaPara.nIterTime);

    if(OptiBase > 0)
    {
        LOGAddSuccessQuitMsg();
        return true;
    }
    else
    {
        SCHAR strErr[] = "Option base is not calculated!";
        LOGAddErrorMsg(strErr);
        return false;
    }


}
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
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.1
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/

bool CmlWBaseProc::WideBaseMapping(vector<StereoSet> vecStereoSet, WideOptions WidePara,vector<ImgPtSet>& vecFPtSetL, vector<ImgPtSet>& vecFPtSetR, vector<ImgPtSet>& vecDPtSetL, vector<ImgPtSet>& vecDPtSetR, SCHAR *strDemFile)
{
    bool bIsUsingPartion=WidePara.bIsUsingPartion;
//    bool bIsUsingFeatPt=WidePara.bIsUsingPartion;

    string demstr;
    int nPos = string(strDemFile).rfind("/");
    demstr.assign( string(strDemFile), 0, nPos );
//    int tt=vecStereoSet.size();

    //�ж�������ImgPtSet�е��Զ�ƥ����Ƿ���ڣ�����������ƥ��
    vector<Pt3d> vecFObjs, vecDObjs, vec3dPts;
    if(bIsUsingPartion==true)
    {
        //ÿ��Ӱ��ֱ�����DEM
        for(UINT i=0; i<vecStereoSet.size(); i++)
        {

            int nNuml = vecFPtSetL[i].vecPts.size();
//            int nNumr = vecFPtSetR[i].vecPts.size();
            if(nNuml>0)
            {
                //�������е��ܼ�ƥ��
                StereoSet* pStereoSet = &vecStereoSet[i];
                CmlFrameImage clsImgL, clsImgR;
                clsImgL.LoadFile(pStereoSet->imgLInfo.strImgPath.c_str());
                clsImgR.LoadFile(pStereoSet->imgRInfo.strImgPath.c_str());

                CmlPtsManage clsPtsManage;
                vector<StereoMatchPt> vecMatchPts;
                clsPtsManage.GetPairPts(vecFPtSetL[i], vecFPtSetR[i], vecMatchPts);

                //��������Ӱ��������������ܼ�ƥ��

                return false;
            }
            else
            {
                StereoSet* pStereoSet = &vecStereoSet[i];
                vector<Pt3d> vec3dPt;
                CmlFrameImage clsImgL, clsImgR;

                FrameImgInfo ImgLinfo, ImgRinfo;
                ImgLinfo = pStereoSet->imgLInfo;
                ImgRinfo = pStereoSet->imgRInfo;

                clsImgL.LoadFile(ImgLinfo.strImgPath.c_str());
                clsImgR.LoadFile(ImgRinfo.strImgPath.c_str());

                //������ƥ��
                vector<Pt2d> vecFLPts, vecFRPts, vecDLPts, vecDRPts;
                vector<Pt3d> vecFObj, vecDObj;
                WideFeaMatch(clsImgL.m_DataBlock, clsImgR.m_DataBlock, WidePara, vecFLPts, vecFRPts);
                SCHAR strMsgFea[] = "finishing wide baseline feature matching!";
                LOGAddNoticeMsg(strMsgFea);

                //�ܼ�ƥ��
                vector<Pt2d> temFPtL, temFPtR;
                temFPtL = vecFLPts;
                temFPtR = vecFRPts;
                WideDenseMatch(clsImgL.m_DataBlock, clsImgR.m_DataBlock, WidePara, temFPtL, temFPtR, vecDLPts, vecDRPts);

                SCHAR strMsgDense[] = "finishing wide baseline dense matching!";
                LOGAddNoticeMsg(strMsgDense);
                // ǰ������������ά��
                WideBase3Ds(pStereoSet, vecFLPts, vecFRPts, vecFObj);
                WideBase3Ds(pStereoSet, vecDLPts, vecDRPts, vecDObj);

                //������������ܼ�������˲�
                WidePtsFilter(vecFObj, vecDObj, vec3dPt);

                //���ܼ���תΪImgPtSet
                vecDPtSetL[i].imgInfo = pStereoSet->imgLInfo;
                vecDPtSetR[i].imgInfo = pStereoSet->imgRInfo;

                Pt2d tempLPt, tempRPt;
                for(UINT k=0; k<vecDLPts.size(); k++)
                {
                    tempLPt.X = vecDLPts[k].X;
                    tempLPt.Y = vecDLPts[k].Y;
                    tempLPt.lID = pStereoSet->imgLInfo.nImgIndex * 10e11 + pStereoSet->imgRInfo.nImgIndex * 10e7 + k + 1;
                    tempLPt.byType = 1;
                    tempRPt.X = vecDRPts[k].X;
                    tempRPt.Y = vecDRPts[k].Y;
                    tempRPt.lID = tempLPt.lID;
                    tempRPt.byType = 1;
                    vecDPtSetL[i].vecPts.push_back(tempLPt);
                    vecDPtSetR[i].vecPts.push_back(tempRPt);
                }
                //���ݸ�����ȫ��DEM������·����ȡÿ��Ӱ��DEM��·��
                demstr.append( "/" );
                string strTLPath = demstr;
//                SINT nTTPos = demstr.rfind("/");
//                string strLTempHead;
//                strLTempHead.assign(demstr, nTTPos+1,demstr.length());
//                SINT nTTBPos = strLTempHead.rfind(".");
//                string strLTempFinal;
//                strLTempFinal.assign(strLTempHead, 0, nTTBPos);
//                strTLPath.append( strLTempFinal);
                char tt[128];
                sprintf(tt,"%d",i);
                strTLPath.append( string(tt));
                strTLPath.append( ".tif" );

                CmlDemProc cls;
                SCHAR *sdem = const_cast<char*>(strTLPath.c_str());
                cls.mlWriteToGeoFile(vec3dPt, WidePara.XResolution, sdem);
            }
        }
    }
    else
    {
        //�ֱ��ÿ����Խ���ƥ��
        for(UINT i=0; i<vecStereoSet.size(); i++)
        {

            int nNuml = vecFPtSetL[i].vecPts.size();
//            int nNumr = vecFPtSetR[i].vecPts.size();
            if(nNuml>0)
            {
                //�������е��ܼ�ƥ��
                StereoSet* pStereoSet = &vecStereoSet[i];
                CmlFrameImage clsImgL, clsImgR;
                clsImgL.LoadFile(pStereoSet->imgLInfo.strImgPath.c_str());
                clsImgR.LoadFile(pStereoSet->imgRInfo.strImgPath.c_str());

                //������ƥ������
                CmlPtsManage clsPtsManage;
                vector<StereoMatchPt> vecMatchPts;
                clsPtsManage.GetPairPts(vecFPtSetL[i], vecFPtSetR[i], vecMatchPts);

                //��������Ӱ��������������ܼ�ƥ��
                vector<Pt2d> vecFLPts, vecFRPts, vecDLPts, vecDRPts;
                StereoMatchPt tempMatch;
                Pt2d tempLPt, tempRPt;
                for(UINT j=0; j<vecMatchPts.size(); j++)
                {
                    tempMatch = vecMatchPts[i];
                    tempLPt.X = tempMatch.ptLInImg.X;
                    tempLPt.Y = tempMatch.ptLInImg.Y;
                    vecFLPts.push_back(tempLPt);
                    tempRPt.X = tempMatch.ptRInImg.X;
                    tempRPt.Y = tempMatch.ptRInImg.Y;
                    vecFRPts.push_back(tempRPt);
                }
                WideDenseMatch(clsImgL.m_DataBlock, clsImgR.m_DataBlock, WidePara, vecFLPts, vecFRPts, vecDLPts, vecDRPts);

                // ǰ������������ά��
                WideBase3Ds(pStereoSet, vecFLPts, vecFRPts, vecFObjs);
                WideBase3Ds(pStereoSet, vecDLPts, vecDRPts, vecDObjs);
                WidePtsFilter(vecFObjs, vecDObjs, vec3dPts);

                //���ܼ���תΪImgPtSet
                vecDPtSetL[i].imgInfo = pStereoSet->imgLInfo;
                vecDPtSetR[i].imgInfo = pStereoSet->imgRInfo;

                //������Ӱ���õ��ܼ���ת��ImgPtSet��ʽ
                for(UINT k=0; k<vecDLPts.size(); k++)
                {
                    tempLPt.X = vecDLPts[i].X;
                    tempLPt.Y = vecDLPts[i].Y;
                    tempLPt.lID = pStereoSet->imgLInfo.nImgIndex * 10e11 + pStereoSet->imgRInfo.nImgIndex * 10e7 + k + 1;
                    tempRPt.X = vecDRPts[i].X;
                    tempRPt.Y = vecDRPts[i].Y;
                    tempRPt.lID = tempLPt.lID;
                    vecDPtSetL[i].vecPts.push_back(tempLPt);
                    vecDPtSetR[i].vecPts.push_back(tempRPt);
                }

                return true;
            }
            else
            {

                StereoSet* pStereoSet = &vecStereoSet[i];
                CmlFrameImage clsImgL, clsImgR;

                FrameImgInfo ImgLinfo, ImgRinfo;
                ImgLinfo = pStereoSet->imgLInfo;
                ImgRinfo = pStereoSet->imgRInfo;

                clsImgL.LoadFile(ImgLinfo.strImgPath.c_str());
                clsImgR.LoadFile(ImgRinfo.strImgPath.c_str());

                //������ƥ��
                vector<Pt2d> vecFLPts, vecFRPts, vecDLPts, vecDRPts;
                WideFeaMatch(clsImgL.m_DataBlock, clsImgR.m_DataBlock, WidePara, vecFLPts, vecFRPts);
                SCHAR strMsgFea[] = "finishing wide baseline feature matching!";
                LOGAddNoticeMsg(strMsgFea);

                //�ܼ�ƥ��
                vector<Pt2d> temFPtL, temFPtR;
                temFPtL = vecFLPts;
                temFPtR = vecFRPts;
                if( false == WideDenseMatch(clsImgL.m_DataBlock, clsImgR.m_DataBlock, WidePara, temFPtL, temFPtR, vecDLPts, vecDRPts) )
                {
                    return false;
                }
                if( vecDLPts.size() != vecDRPts.size() )
                {
                    return false;
                }

                SCHAR strMsgDense[] = "finishing wide baseline dense matching!";
                LOGAddNoticeMsg(strMsgDense);
                // ǰ������������ά��
                WideBase3Ds(pStereoSet, vecFLPts, vecFRPts, vecFObjs);
                WideBase3Ds(pStereoSet, vecDLPts, vecDRPts, vecDObjs);

                //������������ܼ�������˲�
                WidePtsFilter(vecFObjs, vecDObjs, vec3dPts);

                //���ܼ���תΪImgPtSet
                vecDPtSetL[i].imgInfo = pStereoSet->imgLInfo;
                vecDPtSetR[i].imgInfo = pStereoSet->imgRInfo;

                Pt2d tempLPt, tempRPt;
                for(UINT k=0; k<vecDLPts.size(); k++)
                {
                    tempLPt.X = vecDLPts[k].X;
                    tempLPt.Y = vecDLPts[k].Y;
                    tempLPt.lID = pStereoSet->imgLInfo.nImgIndex * 10e11 + pStereoSet->imgRInfo.nImgIndex * 10e7 + k + 1;
                    tempLPt.byType = 1;
                    tempRPt.X = vecDRPts[k].X;
                    tempRPt.Y = vecDRPts[k].Y;
                    tempRPt.lID = tempLPt.lID;
                    tempRPt.byType = 1;
                    vecDPtSetL[i].vecPts.push_back(tempLPt);
                    vecDPtSetR[i].vecPts.push_back(tempRPt);
                }

            }
        }
        //����������Ի����ά�ܼ�������DEM
        CmlDemProc clsDemProc;
        clsDemProc.mlWriteToGeoFile(vec3dPts, WidePara.XResolution, strDemFile);


    }

    return true;
}

/**
* @fn WideBase3Ds
* @date 2011.12.1
* @author �틠
* @brief �����ߵ�Ԫ����
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
bool CmlWBaseProc::WideBase3Ds(StereoSet* pStereoSet, vector<Pt2d>& vecLPts, vector<Pt2d>& vecRPts, vector<Pt3d>& vec3ds)
{

    //����StereoSet��ȡ���ⷽλԪ��
    CmlFrameImage clsImgL, clsImgR;
    if((!clsImgL.LoadFile( pStereoSet->imgLInfo.strImgPath.c_str() )) || (!clsImgR.LoadFile( pStereoSet->imgRInfo.strImgPath.c_str() )))
    {
        SCHAR strErr[] = "Fail to load image file!\n" ;
        LOGAddErrorMsg(strErr) ;
        return false;
    }

    vector<StereoMatchPt> MatchPts;
    SINT nCountl = vecLPts.size();
    SINT nCountr = vecRPts.size();
    StereoMatchPt tempPts;

    if((nCountl ==0) || (nCountr ==0) )
    {
        SCHAR strErr[] = "Input matched points are invalid!\n" ;
        LOGAddErrorMsg(strErr) ;
        return false;
    }
    if (nCountl != nCountr)
    {
        SCHAR strErr[] = "Input matched points are not the same!\n" ;
        LOGAddErrorMsg(strErr) ;
        return false;
    }
    clsImgL.m_InOriPara = pStereoSet->imgLInfo.inOri;
    clsImgL.m_ExOriPara = pStereoSet->imgLInfo.exOri;

    // clsImgR.LoadFile( pStereoSet->imgRInfo.strImgPath.c_str() );
    clsImgR.m_InOriPara = pStereoSet->imgRInfo.inOri;
    clsImgR.m_ExOriPara = pStereoSet->imgRInfo.exOri;

    CmlStereoProc clsStereoProc;
    clsStereoProc.m_pDataL = &clsImgL;
    clsStereoProc.m_pDataR = &clsImgR;


    for(int i=0; i< nCountl; i++)
    {
        tempPts.ptLInImg.X = vecLPts[i].X;
        tempPts.ptLInImg.Y = vecLPts[i].Y;
        tempPts.ptRInImg.X = vecRPts[i].X;
        tempPts.ptRInImg.Y = vecRPts[i].Y;
        MatchPts.push_back(tempPts);
    }

    //ǰ�����������ά����
    clsStereoProc.mlInterSectionInFrameImg( MatchPts );
    SINT nCount =  MatchPts.size();
    for( int i = 0; i < nCount; ++i )
    {
        vec3ds.push_back( MatchPts[i] );
    }
//    LOGAddSuccessQuitMsg();
    return true;

}


//bool CmlWBaseProc::WideBase3Ds(StereoSet* pStereoSetf, StereoSet* pStereoSets, vector<Pt2d>& vecLPts, vector<Pt2d>& vecRPts, vector<Pt3d>& vec3ds)
//{
//    //����StereoSet��ȡ���ⷽλԪ��
//    CmlFrameImage clsImgL, clsImgR;
//
//    if((!clsImgL.LoadFile( pStereoSetf->imgLInfo.strImgPath.c_str() )) || (!clsImgR.LoadFile( pStereoSetf->imgRInfo.strImgPath.c_str() )))
//    {
//        SCHAR strErr[] = "Fail to load image file!\n" ;
//        LOGAddErrorMsg(strErr) ;
//        return false;
//    }
//
//    vector<StereoMatchPt> MatchPts;
//    SINT nCountl = vecLPts.size();
//    SINT nCountr = vecLPts.size();
//    StereoMatchPt tempPts;
//
//    if((nCountl ==0) || (nCountr ==0) )
//    {
//        SCHAR strErr[] = "Input matched points are invalid!\n" ;
//        LOGAddErrorMsg(strErr) ;
//        return false;
//    }
//    if (nCountl != nCountr)
//    {
//        SCHAR strErr[] = "Input matched points are not the same!\n" ;
//        LOGAddErrorMsg(strErr) ;
//        return false;
//    }
//    //clsImgL.LoadFile( pStereoSetf->imgLInfo.strImgPath.c_str() );
//    clsImgL.m_InOriPara = pStereoSetf->imgLInfo.inOri;
//    clsImgL.m_ExOriPara = pStereoSetf->imgLInfo.exOri;
//
//    //clsImgR.LoadFile( pStereoSets->imgLInfo.strImgPath.c_str() );
//    clsImgR.m_InOriPara = pStereoSets->imgLInfo.inOri;
//    clsImgR.m_ExOriPara = pStereoSets->imgLInfo.exOri;
//
//    CmlStereoProc clsStereoProc;
//    clsStereoProc.m_pDataL = &clsImgL;
//    clsStereoProc.m_pDataR = &clsImgR;
//
//
//    for(int i=0; i< nCountl; i++)
//    {
//        tempPts.ptLInImg.X = vecLPts[i].X;
//        tempPts.ptLInImg.Y = vecLPts[i].Y;
//        tempPts.ptRInImg.X = vecRPts[i].X;
//        tempPts.ptRInImg.Y = vecRPts[i].Y;
//        MatchPts.push_back(tempPts);
//    }
//
//    //ǰ�����������ά����
//    clsStereoProc.mlInterSectionInFrameImg( MatchPts );
//    UINT nCount =  MatchPts.size();
//    for( int i = 0; i < nCount; ++i )
//    {
//        vec3ds.push_back( MatchPts[i] );
//    }
//    return true;
//}
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
* @param vecMPtL����Ӱ���ܼ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.1
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
bool CmlWBaseProc::WideDenseMatch(CmlRasterBlock LOriImg,CmlRasterBlock ROriImg, WideOptions WidePara, vector<Pt2d> &vecFPtLs, vector<Pt2d> &vecFPtRs, vector<Pt2d> &vecMPtLs, vector<Pt2d> &vecMPtRs)
{

    //��������ƥ�亯��
    //WideFeaMatch(LOriImg, ROriImg, WidePara, vecFPtLs, vecFPtRs);
    //cout<<vecFPtLs.size()<<endl;

    //�ж�����Ӱ���Ƿ�Ϊ��
    if((sizeof(LOriImg) == 0) || (sizeof(ROriImg) == 0))
    {
        SCHAR strErr[] = "Images are not loaded accurately!\n" ;
        LOGAddErrorMsg(strErr) ;
        return false;
    }
    //ʹ�����������ɺ���Ӱ��
    CmlRasterBlock pLEpiImg, pREpiImg;
    CmlMat LH,  RH;
    LH.Initial(3, 3);
    RH.Initial(3, 3);
    mlWideEpiImg(vecFPtLs, vecFPtRs, &LOriImg, &ROriImg, &pLEpiImg, &pREpiImg, LH, RH);


    //��������ת���ɺ���Ӱ��ĵ�
    vector<Pt2d> vecEPtsL,  vecEPtsR;
    mlOriPtToEpi(vecFPtLs, vecFPtRs, LH, RH, vecEPtsL, vecEPtsR);


    //�Ժ���Ӱ��block���и�˹�˲�
    CmlFrameImage clsFrame;
    clsFrame.SmoothByGuassian(pLEpiImg, 7, 0.6);
    clsFrame.SmoothByGuassian(pREpiImg, 7, 0.6);

    //���������vectorת��StereoMatchPt��ʽ
    vector<StereoMatchPt> vecPts;
    StereoMatchPt tempPt;
    UINT nNum = vecEPtsL.size();
    Pt2d temptl, temptr;
    for(UINT i=0; i < nNum; i++)
    {
        temptl = vecEPtsL[i];
        tempPt.ptLInImg.X = temptl.X;
        tempPt.ptLInImg.Y = temptl.Y;

        temptr = vecEPtsR[i];
        tempPt.ptRInImg.X = temptr.X;
        tempPt.ptRInImg.Y = temptr.Y;
        vecPts.push_back(tempPt);

    }

    //�ں���Ӱ���Ͻ����ܼ�ƥ��
    vector<Pt2d> vecEDPtsL, vecEDPtsR;
    CmlStereoProc clsStereo;
    bool bDense;
    bDense = clsStereo.mlDenseMatch(&pLEpiImg, &pREpiImg, vecPts, WidePara, vecEDPtsL, vecEDPtsR);
    if(!bDense)
    {
        return false;
    }

    //����Ӱ���ϵ��ܼ��㷴�㵽ԭʼӰ��
    mlEpiPtToOri(vecEDPtsL, vecEDPtsR, LH, RH, vecMPtLs, vecMPtRs);

    return true;


}

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
bool CmlWBaseProc:: WideFeaMatch(CmlRasterBlock LOriImg,CmlRasterBlock ROriImg, WideOptions WidePara, vector<Pt2d> &vecPtL, vector<Pt2d> &vecPtR)
{
    //�ж�����Ӱ���Ƿ�Ϊ��
    if((sizeof(LOriImg) == 0) || (sizeof(ROriImg) == 0))
    {
        return false;
    }

    UINT nMaxCheck = WidePara.nMaxCheck;
    DOUBLE dRatio = WidePara.dRatio;
    DOUBLE dThresh = WidePara.dThresh;
    DOUBLE dConfidence = WidePara.dConfidence;
    CmlStereoProc clsStereo;

    //siftƥ��
    vector<double> vxl;
    vector<double> vyl;
    vector<double> vxr;
    vector<double> vyr;

    UINT nPtNum = SiftMatchVector((char*)LOriImg.GetData( ),LOriImg.GetW(),LOriImg.GetH(),8,(char*)ROriImg.GetData( ),ROriImg.GetW(),ROriImg.GetH(),8,vxl,vyl,vxr,vyr,nMaxCheck,dRatio);

    if(nPtNum <=0 )
    {
        return false;
    }
    vector<StereoMatchPt> MatchPts;
    SINT nCount;
    StereoMatchPt tempPts;
    for(UINT i=0; i<nPtNum; i++)
    {
        tempPts.ptLInImg.X = vxl[i];
        tempPts.ptLInImg.Y = vyl[i];
        tempPts.ptRInImg.X = vxr[i];
        tempPts.ptRInImg.Y = vyr[i];
        MatchPts.push_back(tempPts);
    }

    //ɾ���ظ�Ԫ��
    nCount = clsStereo.mlGetRansacPts(MatchPts,dThresh,dConfidence);
    clsStereo.mlUniquePt(MatchPts);

    nCount = MatchPts.size();

    if(nCount<=0)
    {
        return false;
    }
    Pt2d temptl, temptr;
    for(int i=0; i<nCount; i++)
    {

        temptl.X = MatchPts[i].ptLInImg.X;
        temptl.Y = MatchPts[i].ptLInImg.Y;
        vecPtL.push_back(temptl);
        temptr.X = MatchPts[i].ptRInImg.X;
        temptr.Y = MatchPts[i].ptRInImg.Y;
        vecPtR.push_back(temptr);
    }

    return true;

}
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
bool CmlWBaseProc::WidePtsFilter(vector<Pt3d>& vecFPts, vector<Pt3d>& vecDPts, vector<Pt3d>& vec3dPts)
{
    //�����������ƻ�þ��η�Χ
    DbRect rectFea;
    SINT nNum, nNumDense ;
    nNum = vecFPts.size();
    nNumDense = vecDPts.size();
    if((nNum<=0) || (nNumDense <=0))
    {

        return false ;
    }
    Pt3d ptTemp ;
    for(SINT i = 0 ; i < nNum ; i++)
    {
        ptTemp = vecFPts[i] ;
        rectFea.left = MIN(ptTemp.X , rectFea.left) ;
        rectFea.right = MAX(ptTemp.X , rectFea.right) ;
        rectFea.bottom = MIN(ptTemp.Y , rectFea.bottom) ;
        rectFea.top = MAX(ptTemp.Y , rectFea.top) ;
    }

    vector<Pt3d> vecDPtf;


    //�����������Ƶķ�Χȥ���ܼ�ƥ���õ���ɢ��
    for(SINT i = 0 ; i < nNumDense ; i++)
    {
        ptTemp = vecDPts[i];
        if((ptTemp.X >= rectFea.left)&&(ptTemp.X <= rectFea.right)&&(ptTemp.Y >= rectFea.bottom)&&(ptTemp.Y <= rectFea.top))
        {
            vecDPtf.push_back(ptTemp);
        }

    }

    //������㼯�ϳ����õ���������ȥ���ֲ��֤���ɵ�����ȷ
    vector<Pt3d>   vecTemp;
    vecTemp.insert(vecTemp.end(),   vecFPts.begin(),   vecFPts.end());
    vecTemp.insert(vecTemp.end(),   vecDPtf.begin(),   vecDPtf.end());

    //�������˲���ĵ��Ƶ���
    vec3dPts = vecTemp;
    return true;

}

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

void CmlWBaseProc::mlFunAcc(DOUBLE dFixBase,DOUBLE dBase,DOUBLE dFunAcc[2],InOriPara mlNav, InOriPara mlPan,DOUBLE dPixel, DOUBLE dTarget)
{
    DOUBLE dFocaln = mlNav.f;
    DOUBLE dFocalp = mlPan.f;


    //DOUBLE dMinbase = 1.0;
    //DOUBLE dMaxbase = (dFocalp/ nWidth) * dTarget;

    DOUBLE dCoeFir = pow(dTarget,2)*dPixel*dPixel/(8*dFixBase*dFixBase*dFocaln*dFocaln);
    DOUBLE dCoeSec = pow(dTarget,4)*dPixel*dPixel/(dFocalp*dFocalp);

    dFunAcc[0] = 0.5*(pow(dCoeFir*dBase*dBase+dCoeSec/dBase/dBase,-0.5))*(2*dCoeFir*dBase - 2*dCoeSec/dBase/dBase/dBase);
    dFunAcc[1] = -0.25*(pow(dCoeFir*dBase*dBase+dCoeSec/dBase/dBase,-1.5))*(pow((2*dCoeFir*dBase - 2*dCoeSec/dBase/dBase/dBase),2))+0.5*(pow(dCoeFir*dBase*dBase+dCoeSec/dBase/dBase,-0.5))*(2*dCoeFir+6*dCoeSec/dBase/dBase/dBase/dBase);

}

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

DOUBLE CmlWBaseProc::mlNewTon(DOUBLE dFixBase,DOUBLE * dBase,DOUBLE dThresHold, DOUBLE dIterTime,InOriPara mlNav, InOriPara mlPan,DOUBLE dPixel, DOUBLE dTarget)
{
    UINT nK,nL;
    DOUBLE dFun[2], dD,dP,dBase0;
    DOUBLE dBase1 = 0;
    nL = dIterTime;
    nK = 1;
    dBase0 = *dBase;
    mlFunAcc(dFixBase,dBase0,dFun, mlNav, mlPan, dPixel, dTarget);
    dD = dThresHold+1.0;
    dBase = 0;

    while ((dD>=dThresHold) && (nL!=0))
    {
        if (fabs(dFun[1])+1.0 ==1.0)
        {
            printf("err\n");
            return(-1);
        }
        dBase1=dBase0-dFun[0]/dFun[1];
        mlFunAcc(dFixBase,dBase1, dFun, mlNav, mlPan, dPixel, dTarget);
        dD=fabs(dBase1-dBase0);
        dP=fabs(dFun[0]);
        if(dP>dD)
            dD = dP;

        dBase0 = dBase1;
        nL = nL-1;

    }
    *dBase = dBase1;
    nK = dIterTime-1;
    return(*dBase);
}

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

DOUBLE CmlWBaseProc::mlBestBase(InOriPara mlNav, InOriPara mlPan,DOUBLE dOptiBase,DOUBLE dFixBase, DOUBLE dPixel, DOUBLE dTarget, UINT nWidth,DOUBLE * dBase,DOUBLE dThresHold, DOUBLE dIterTime)
{

    DOUBLE dFocalp = mlPan.f;


    DOUBLE dMinbase = 1.0;
    DOUBLE dMaxbase = (dFocalp/ nWidth/dPixel) * dTarget;

    dBase = &dMinbase;
    dOptiBase = mlNewTon(dFixBase,dBase, dThresHold, dIterTime, mlNav, mlPan, dPixel, dTarget);

    if((dOptiBase < dMaxbase)&&(dOptiBase > 0))
        return(dOptiBase);

    else
        return 0;

}

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

bool CmlWBaseProc::mlOriPtToEpi(const vector<Pt2d>& vecOPtsL, const vector<Pt2d>& vecOPtsR,CmlMat& LeftHomo, CmlMat& RightHomo, vector<Pt2d>& vecEPtsL, vector<Pt2d>& vecEPtsR)
{
    //�ж������ƥ����Ƿ�Ϊ�ղ������
    if ((vecOPtsL.size()==0)||(vecOPtsR.size()==0)||(vecOPtsL.size()!=vecOPtsR.size()))
    {
        return false;
    }

    //�ж�͸�Ӿ����Ƿ����0
    int nNuml=0, nNumr=0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j <3; j++)
        {
            if(LeftHomo.GetAt(i,j)==0)
                nNuml++;

        }

    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j <3; j++)
        {
            if(RightHomo.GetAt(i,j)==0)
                nNumr++;

        }

    }

    if(nNuml==9||nNumr==9)
    {
        return false;
    }

    CmlMat  MatOPtsL, MatOPtsR, MatEpiL, MatEpiR;
    MatOPtsL.Initial(3,1);
    MatOPtsR.Initial(3,1);
    MatEpiL.Initial(3,1);
    MatEpiR.Initial(3,1);


    //����͸�ӱ任�ļ��ι�ϵ��͸�Ӿ��������M*[xepi yepi 1]=[tXori tYori t]����ת��
    for(UINT i=0; i<vecOPtsL.size(); i++)
    {
        Pt2d TemPtL, TemPtR, TemPtEL, TemPtER;
        //�����Ӱ��ĵ����ת��
        TemPtL=vecOPtsL[i];
        MatOPtsL.SetAt(0,0,TemPtL.X);
        MatOPtsL.SetAt(1,0,TemPtL.Y);
        MatOPtsL.SetAt(2,0,1);
        mlMatMul(&LeftHomo,&MatOPtsL,&MatEpiL);
        if(MatEpiL.GetAt(2,0) ==0)
        {
            return false;
        }
        TemPtEL.X=MatEpiL.GetAt(0,0)/MatEpiL.GetAt(2,0);
        TemPtEL.Y=MatEpiL.GetAt(1,0)/MatEpiL.GetAt(2,0);
        vecEPtsL.push_back(TemPtEL);

        //���ұ�Ӱ��ĵ����ת��
        TemPtR=vecOPtsR[i];
        MatOPtsR.SetAt(0,0,TemPtR.X);
        MatOPtsR.SetAt(1,0,TemPtR.Y);
        MatOPtsR.SetAt(2,0,1);
        mlMatMul(&RightHomo,&MatOPtsR,&MatEpiR);
        if(MatEpiR.GetAt(2,0) ==0)
        {
            return false;
        }
        TemPtER.X=MatEpiR.GetAt(0,0)/MatEpiR.GetAt(2,0);
        TemPtER.Y=MatEpiR.GetAt(1,0)/MatEpiR.GetAt(2,0);
        vecEPtsR.push_back(TemPtER);

    }

    return true;


}


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

bool CmlWBaseProc::mlEpiPtToOri(const vector<Pt2d>& vecEPtsL, const vector<Pt2d>& vecEPtsR,CmlMat& LeftHomo, CmlMat& RightHomo, vector<Pt2d>& vecOPtsL, vector<Pt2d>& vecOPtsR)
{
    //�ж������ƥ����Ƿ����
    if ((vecEPtsL.size()==0)||(vecEPtsR.size()==0)||(vecEPtsL.size()!=vecEPtsR.size()))
    {
        return false;
    }


    //�ж�͸�Ӿ����Ƿ����0
    int nNuml=0, nNumr=0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j <3; j++)
        {
            if(LeftHomo.GetAt(i,j)==0)
                nNuml++;

        }

    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j <3; j++)
        {
            if(RightHomo.GetAt(i,j)==0)
                nNumr++;

        }

    }

    if(nNuml==9||nNumr==9)
    {
        return false;
    }


    //��ʼ��͸�Ӿ���������LeftHomoTran,RightHomoTran; ��ʼ������Ӱ���Ϻ�ԭʼԭʼӰ���ϵ�ƥ������MatEPTs,MatOri
    CmlMat LeftHomoTran, RightHomoTran, MatEPtsL, MatEPtsR, MatOriL, MatOriR;
    LeftHomoTran.Initial(3, 3);
    RightHomoTran.Initial(3,3);
    MatEPtsL.Initial(3, 1);
    MatEPtsR.Initial(3, 1);
    MatOriL.Initial(3, 1);
    MatOriR.Initial(3, 1);

    if(mlMatInv(&LeftHomo,&LeftHomoTran)&&mlMatInv(&RightHomo,&RightHomoTran))
    {
        for(UINT i=0; i<vecEPtsL.size(); i++)
        {
            Pt2d TemPtL, TemPtR, TemPtOL, TemPtOR;
            //����͸�ӱ任�ļ��ι�ϵ��͸�Ӿ���������M*[xepi yepi 1]=[tXori tYori t]�����Ӱ��ĵ����ת��
            TemPtL=vecEPtsL[i];
            MatEPtsL.SetAt(0,0,TemPtL.X);
            MatEPtsL.SetAt(1,0,TemPtL.Y);
            MatEPtsL.SetAt(2,0,1);
            mlMatMul(&LeftHomoTran,&MatEPtsL,&MatOriL);
            if(MatOriL.GetAt(2,0) ==0)
            {
                return false;
            }
            TemPtOL.X=MatOriL.GetAt(0,0)/MatOriL.GetAt(2,0);
            TemPtOL.Y=MatOriL.GetAt(1,0)/MatOriL.GetAt(2,0);
            vecOPtsL.push_back(TemPtOL);
            //���ұ�Ӱ��ĵ����ת��
            TemPtR=vecEPtsR[i];
            MatEPtsR.SetAt(0,0,TemPtR.X);
            MatEPtsR.SetAt(1,0,TemPtR.Y);
            MatEPtsR.SetAt(2,0,1);
            mlMatMul(&RightHomoTran,&MatEPtsR,&MatOriR);
            if(MatOriR.GetAt(2,0) ==0)
            {
                return false;
            }
            TemPtOR.X=MatOriR.GetAt(0,0)/MatOriR.GetAt(2,0);
            TemPtOR.Y=MatOriR.GetAt(1,0)/MatOriR.GetAt(2,0);
            vecOPtsR.push_back(TemPtOR);
        }

        return true;
    }
    else
    {
        return false;
    }

}


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
* @retval false ʧ��
* @version 1.1
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/

bool CmlWBaseProc::mlWideEpiImg(const vector<Pt2d>&vecEPtsL, const vector<Pt2d>& vecEPtsR,  CmlRasterBlock* pLOriImg, CmlRasterBlock* pROriImg, CmlRasterBlock* pLEpiImg, CmlRasterBlock* pREpiImg, CmlMat& LeftHomo, CmlMat& RightHomo)
{

    //�ж������ƥ����Ƿ����
    if ((vecEPtsL.size() == 0) || (vecEPtsR.size() == 0) || (vecEPtsL.size()!=vecEPtsR.size()) )
    {
        return false;
    }
    int nNum = vecEPtsL.size();

    IplImage* pOriImgL = NULL;
    IplImage* pOriImgR = NULL;


    vector<cv::Point2f> points1, points2;

    //��vector����ת��opencv��ʽPoint2f
    for(int i=0 ; i< nNum; i++)
    {

        points1.push_back(cv::Point2f(vecEPtsL[i].X,vecEPtsL[i].Y));
        points2.push_back(cv::Point2f(vecEPtsR[i].X,vecEPtsR[i].Y));
    }

    //ʹ��7���㷨������Լ�Ļ�������
    cv::Mat FundMatri = cv::findFundamentalMat(points1, points2, cv::FM_7POINT, 3, 0.99);

    if(CmlRBlock2IplImg(pLOriImg, pOriImgL)&&CmlRBlock2IplImg( pROriImg, pOriImgR))
    {
        cv::Mat ImgL, ImgR, rectified1, rectified2, H1, H2;

        //��iplImgת��mat����
        ImgL =  pOriImgL;
        ImgR =  pOriImgR;

        //����У���任
        stereoRectifyUncalibrated(points1, points2, FundMatri, ImgL.size(), H1, H2);

        //������Ӱ��ĺ���Ӱ��
        warpPerspective(ImgL, rectified1, H1, ImgL.size());


        //��Matת��IplImage
        IplImage *pEpiImgL  = new IplImage(rectified1);
        //IplImageת��RasterBlock
        IplImage2CmlRBlock(pEpiImgL,pLEpiImg);

        warpPerspective(ImgR, rectified2, H2, ImgR.size());

        IplImage  *pEpiImgR  = new IplImage(rectified2);
        IplImage2CmlRBlock(pEpiImgR,pREpiImg);

        //��͸�Ӿ���ת��CvMat����
        CvMat MatHL = H1;
        CvMat MatHR = H2;
        CvMat2mlMat(&MatHL, &LeftHomo);
        CvMat2mlMat(&MatHR, &RightHomo);

//        if( pEpiImgL != NULL)
//        {
//            cvReleaseImage( &pEpiImgL );
//        }
//
//        if( pEpiImgR != NULL)
//        {
//            cvReleaseImage( &pEpiImgR );
//        }

        return true;
    }
    return false;

}







