/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlStereoProc.cpp
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ����Դ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#include "mlStereoProc.h"
#include "mlTypeConvert.h"
#include "mlFrameImage.h"
#include "mlMat.h"
#include "mlTIN.h"
#include "mlPtsManage.h"
#include "mlGeoRaster.h"
#include "mlBlockCalculation.h"
#include "mlPhgProc.h"
#include "SiftMatch.h"
#include "ASift.h"
#include "RANSAC.h"
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
CmlStereoProc::CmlStereoProc()
{
    m_pDataL = NULL;
    m_pDataR = NULL;
}
/**
    * @fn ~CmlLogRecord
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlLogRecord����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

CmlStereoProc::~CmlStereoProc()
{
    //dtor
}
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

CmlStereoProc::CmlStereoProc(CmlGdalDataset* m_pDataL, CmlGdalDataset* m_pDataR)
{

}
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
bool CmlStereoProc::mlFilterPtsByMedian( vector<StereoMatchPt> &MatchPts, SINT nTemplateSize, double dThresCoef, double dThres )
{
    vector<bool> vecFlag;
    SINT nHalfSize = ( nTemplateSize / 2 );
//    SINT nSize = nHalfSize * 2 + 1;
    SINT nPtSize = MatchPts.size();
    for( int i = 0; i < nPtSize; ++i )
    {
        if( i < nHalfSize )
        {
            vecFlag.push_back( false );
            continue;
        }
        if( i >= nPtSize - nHalfSize )
        {
            vecFlag.push_back( false);
            continue;
        }
        StereoMatchPt* pt = &MatchPts[i];
        SINT nCurParal = pt->ptLInImg.X - pt->ptRInImg.X;
        vector<SINT> vecParal;

        for( SINT j = -nHalfSize; j <= nHalfSize; ++j )
        {
            StereoMatchPt* pt = &MatchPts[i+j];
            SINT nCurParal = pt->ptLInImg.X - pt->ptRInImg.X;
            vecParal.push_back( nCurParal );
        }
        std::sort( vecParal.begin(),  vecParal.end() );//��С��������
        SINT nCurMedVal = vecParal[nHalfSize];

        DOUBLE dParalThres = nCurMedVal*dThresCoef;
        dParalThres = ( dParalThres < dThres ) ? dThres : dParalThres;

        if( abs(nCurMedVal - nCurParal) > dParalThres )
        {
            vecFlag.push_back( false );
        }
        else
        {
            vecFlag.push_back( true );
        }
    }

    vector<StereoMatchPt> vecTempSPt( MatchPts);
    MatchPts.clear();
    for( SINT i = 0; i < nPtSize; ++i )
    {
        if( vecFlag[i] == true )
        {
            MatchPts.push_back( vecTempSPt[i] );
        }
    }
    return true;
}
/**
    * @fn
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ransac�����޳�����ƥ���ֲ�
    * @param MatchPts ����ƥ���
    * @param dThresh ��ֵ
    * @param dConfidence ���Ŷ�
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
bool CmlStereoProc::mlGetRansacPts(vector<StereoMatchPt> &MatchPts, DOUBLE dThresh, DOUBLE dConfidence )
{
    vector<StereoMatchPt> ranPts;
    if( false == mlGetRansacPts( MatchPts, ranPts, dThresh, dConfidence ) )
    {
        return false;
    }

    MatchPts.clear();
    for( UINT i = 0; i < ranPts.size(); ++i )
    {
        MatchPts.push_back( ranPts[i] );
    }

    return true;

}
DOUBLE getModelError( StereoMatchPt pt, DOUBLE *dCoef )
{
    DOUBLE dErrorX = dCoef[0]*pt.ptLInImg.X - dCoef[1]*pt.ptLInImg.Y + dCoef[2] - pt.ptRInImg.X;
    DOUBLE dErrorY = dCoef[1]*pt.ptLInImg.X + dCoef[0]*pt.ptLInImg.Y + dCoef[3] - pt.ptRInImg.Y;
    return sqrt( dErrorX*dErrorX + dErrorY*dErrorY );
}
bool getAffineCoef( vector<StereoMatchPt> vecPt, double* dCoef, double &dError )
{
    SINT nNum = vecPt.size();

    if( nNum < 2 )
    {
        return false;
    }
    CmlMat matAT, matLT, matXT;
    matAT.Initial( 2*nNum, 4 );
    matLT.Initial( 2*nNum, 1 );

    for( int i = 0; i < nNum; ++i )
    {
        StereoMatchPt pt = vecPt[i];
        matAT.SetAt( 2*i, 0, pt.ptLInImg.X );
        matAT.SetAt( 2*i, 1, -1.0*pt.ptLInImg.Y );
        matAT.SetAt( 2*i, 2, 1 );
        matAT.SetAt( 2*i, 3, 0 );

        matAT.SetAt( 2*i+1, 0, pt.ptLInImg.Y );
        matAT.SetAt( 2*i+1, 1, pt.ptLInImg.X );
        matAT.SetAt( 2*i+1, 2, 0 );
        matAT.SetAt( 2*i+1, 3, 1 );

        matLT.SetAt( 2*i, 0, pt.ptRInImg.X );
        matLT.SetAt( 2*i+1, 0, pt.ptRInImg.Y );
    }

    mlMatSolveSVD( &matAT, &matLT, &matXT );
    for( int i = 0; i < 4; ++i )
    {
        dCoef[i] = matXT.GetAt( i, 0 );
    }
    DOUBLE dErrorAll = 0;
    for( int i = 0; i < nNum; ++i )
    {
        StereoMatchPt pt = vecPt[i];
        DOUBLE dErrorX = dCoef[0]*pt.ptLInImg.X - dCoef[1]*pt.ptLInImg.Y + dCoef[2] - pt.ptRInImg.X;
        DOUBLE dErrorY = dCoef[1]*pt.ptLInImg.X + dCoef[0]*pt.ptLInImg.Y + dCoef[3] - pt.ptRInImg.Y;
        dErrorAll +=  dErrorX*dErrorX + dErrorY*dErrorY;
    }
    dErrorAll = dErrorAll / nNum;
    dErrorAll = sqrt( dErrorAll );

    return true;
}
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
bool CmlStereoProc::mlGetRansacPtsByAffineT( vector<StereoMatchPt> &MatchPts, vector<StereoMatchPt> &RanSacPts, DOUBLE dSegma, DOUBLE dMaxError )
{
    vector<DOUBLE> vecLX, vecLY, vecRX, vecRY;
    vector<bool> vecFlags;
    for( UINT i = 0; i < MatchPts.size(); ++i )
    {
        StereoMatchPt ptCur = MatchPts[i];
        vecLX.push_back( ptCur.ptLInImg.X );
        vecLY.push_back( ptCur.ptLInImg.Y );
        vecRX.push_back( ptCur.ptRInImg.X );
        vecRY.push_back( ptCur.ptRInImg.Y );
    }
    if( true == getRanSacPts( vecLX, vecLY, vecRX, vecRY, vecFlags, dSegma, dMaxError ) )
    {
        for( UINT i = 0; i < MatchPts.size(); ++i )
        {
            if( true == vecFlags[i] )
            {
                RanSacPts.push_back( MatchPts[i]);
            }
        }
        return true;
    }
    return false;
//    DOUBLE dMaxTempError = 999999999;
//    vector< StereoMatchPt > vecTInlier;
//    if( MatchPts.size() <= 0 )
//    {
//        return false;
//    }
//    for( SINT i = 0; i < (MatchPts.size()-1); ++i )
//    {
//        for( SINT j = i+1; j < MatchPts.size(); ++j )
//        {
//            vector<StereoMatchPt> vecTempInlier;
//            vector<DOUBLE> vecTempError;
//            DOUBLE dCoef[4];
//            DOUBLE dError;
//            vector<StereoMatchPt> vecTempPt;
//            vecTempPt.push_back( MatchPts.at(i) );
//            vecTempPt.push_back( MatchPts.at(j) );
//            getAffineCoef( vecTempPt, dCoef, dError );
//
//            vecTempInlier.push_back( MatchPts.at(i));
//            vecTempInlier.push_back( MatchPts.at(j));
//
//            DOUBLE dTempE = 0;
//            for( int k = 0; k < MatchPts.size(); ++k )
//            {
//                if( ( k != i  )&& ( k != j ) )
//                {
//                    DOUBLE dTE = getModelError( MatchPts.at(k), dCoef );
//                    if( dMaxError >  dTE )
//                    {
//                        dTempE += dTE;
//                        vecTempInlier.push_back( MatchPts.at(k) );
//                    }
//                }
//            }
//            dTempE /= vecTempInlier.size();
//            if( vecTempInlier.size() > nMinLierSetNum )
//            {
//                if( dMaxTempError > dTempE )
//                {
//                    vecTInlier.clear();
//                    vecTInlier = vecTempInlier;
//                    dMaxTempError = dTempE;
//                }
//            }
//
//        }
//    }
//    RanSacPts = vecTInlier;

    return true;
}
bool CmlStereoProc::mlGetRansacPtsByAffineT( vector<StereoMatchPt> &MatchPts, DOUBLE dSegma, DOUBLE dMaxError )
{
    vector<StereoMatchPt> vecSPtsTemp;
    if( true == this->mlGetRansacPtsByAffineT( MatchPts, vecSPtsTemp, dSegma, dMaxError ) )
    {
        MatchPts.clear();
        MatchPts = vecSPtsTemp;
        return true;
    }
    return false;
}

/**
* @fn
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
SINT CmlStereoProc::mlGetRansacPtsByAffineT(vector<DOUBLE> vxl, vector<DOUBLE> vyl, vector<DOUBLE> vxr, vector<DOUBLE> vyr,\
        vector<StereoMatchPt> &RanSacPts, DOUBLE dSigma, UINT nMinItera )
{
    if( nMinItera <= 0 )
    {
        SCHAR strErr[] = "Interation Times less than 0 in Ransac Algrithm!\n" ;
        LOGAddErrorMsg(strErr) ;
        return false;
    }
    vector<bool> vecFlags;
    if( false == getRanSacPts( vxl, vyl, vxr, vyr, vecFlags, dSigma, nMinItera ) )
    {
        return -1;
    }

    for( UINT i = 0; i < vecFlags.size(); ++i )
    {
        if( true == vecFlags[i] )
        {
            StereoMatchPt ptCur;
            ptCur.ptLInImg.X = vxl[i];
            ptCur.ptLInImg.Y = vyl[i];
            ptCur.ptRInImg.X = vxr[i];
            ptCur.ptRInImg.Y = vyr[i];
            RanSacPts.push_back( ptCur );
        }
    }
    return RanSacPts.size();
}
/**
* @fn
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ransac�����޳�����ƥ���ֲ�
* @param MatchPts ���������ƥ���
* @param RanSacPts ���������ƥ���
* @param dThresh ��ֵ
* @param dConfidence ���Ŷ�
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlStereoProc::mlGetRansacPts(vector<StereoMatchPt> &MatchPts, vector<StereoMatchPt> &RanSacPts, DOUBLE dThresh, DOUBLE dConfidence )
{
//    vector<DOUBLE> vecXL, vecYL, vecXR, vecYR;
//    for( SINT i = 0; i < MatchPts.size(); ++i )
//    {
//        StereoMatchPt ptCur = MatchPts[i];
//        vecXL.push_back( ptCur.ptLInImg.X );
//        vecYL.push_back( ptCur.ptLInImg.Y );
//        vecXR.push_back( ptCur.ptRInImg.X );
//        vecYR.push_back( ptCur.ptRInImg.Y );
//    }
//
//    vector<bool> vecFlags;
//    if( false == getRanSacPts( vecXL, vecYL, vecXR, vecYR, vecFlags, 5.5, 5000 ) )
//    {
//        return -1;
//    }
//
//    for( SINT i = 0; i < MatchPts.size(); ++i )
//    {
//        if( true == vecFlags[i] )
//        {
//            StereoMatchPt ptCur;
//            ptCur.ptLInImg.X = vecXL[i];
//            ptCur.ptLInImg.Y = vecYL[i];
//            ptCur.ptRInImg.X = vecXR[i];
//            ptCur.ptRInImg.Y = vecYR[i];
//            RanSacPts.push_back( ptCur );
//        }
//    }
//    return RanSacPts.size();
    std::vector<cv::Point2f> Lpts,Rpts;
    vector<uchar> Mask0;
    cv::Point2f tempXY1, tempXY2;
    UINT nRows = MatchPts.size();
    StereoMatchPt tempPts;
    //��StereoMatchPtת����cv::Point2f��ʽ
    for (UINT i = 0; i< nRows; i++)
    {
        tempPts = MatchPts.at(i);
        Lpts.push_back(cv::Point2f(tempPts.ptLInImg.X,tempPts.ptLInImg.Y));
        Rpts.push_back(cv::Point2f(tempPts.ptRInImg.X,tempPts.ptRInImg.Y));
    }
    if( ( Lpts.size() == 0 ) || ( Rpts.size() == 0 ) )
    {
        return false;
    }
    //RANSACȥ���ֲMask0����Ƿ�Ϊ�ֲ��
    cv::Mat fundamentalMatrix = cv::findFundamentalMat(Lpts, Rpts, cv::FM_RANSAC, dThresh, dConfidence, Mask0);
    //���ڵ�洢��StereoMatchPt�ṹ��
    UINT nCount = 0;
    for ( UINT j = 0; j < nRows; j++ )
    {
        //Mask0Ϊ0ʱΪ�ֲ�㣬1Ϊ�ڵ�
        if( (SINT)Mask0[j] == 1 )
        {
            tempPts.lID = MatchPts[j].lID;
            tempPts.ptLInImg.lID = MatchPts[j].ptLInImg.lID;
            tempPts.ptRInImg.lID = MatchPts[j].ptRInImg.lID;
            tempPts.ptLInImg.X = Lpts[j].x;
            tempPts.ptLInImg.Y = Lpts[j].y;
            tempPts.ptRInImg.X = Rpts[j].x;
            tempPts.ptRInImg.Y = Rpts[j].y;
            tempPts.dRelaCoef = MatchPts[j].dRelaCoef;
            RanSacPts.push_back(tempPts);
            nCount++;
        }
        else
        {
            continue;
        }
    }
    return true;
}
/**
* @fn
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
bool CmlStereoProc::mlGetRansacPts( vector<DOUBLE> vxl, vector<DOUBLE> vyl, vector<DOUBLE> vxr, vector<DOUBLE> vyr,\
                                    vector<StereoMatchPt> &vecRanPts, DOUBLE dThresh, DOUBLE dConfidence )
{
    std::vector<cv::Point2f> Lpts,Rpts;
    vector<uchar> Mask0;
    StereoMatchPt tempPts;
    cv::Point2f tmpPt2f;
    //ת����cv::Point2f��ʽƥ���
    for (UINT i = 0; i< vxl.size(); i++)
    {
        Lpts.push_back(cv::Point2f(vxl[i],vyl[i]));
        Rpts.push_back(cv::Point2f(vxr[i],vyr[i]));
    }
    if( ( Lpts.size() == 0 ) || ( Rpts.size() == 0 ) )
    {
        return false;
    }
    //RANSACȥ���ֲMask0����Ƿ�Ϊ�ֲ��
    cv::Mat fundamentalMatrix = cv::findFundamentalMat(Lpts, Rpts, cv::FM_RANSAC, dThresh, dConfidence, Mask0);
    UINT nCount = 0;
    for ( UINT j = 0; j < vxl.size(); j++ )
    {
        if( (SINT)Mask0[j] == 1 )
        {
            tempPts.ptLInImg.X = Lpts[j].x;
            tempPts.ptLInImg.Y = Lpts[j].y;
            tempPts.ptRInImg.X = Rpts[j].x;
            tempPts.ptRInImg.Y = Rpts[j].y;
            vecRanPts.push_back(tempPts);
            nCount++;
        }
        else
        {
            continue;
        }
    }
    return true;
}

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
bool CmlStereoProc::mlTemplateMatchInFeatPt( MLRect rectSearch, SINT nTemplateSize, DOUBLE dCoef, SINT nXOffSet, SINT nYOffSet )
{
    if( ( m_pDataL == NULL ) || ( m_pDataR == NULL ) )
    {
        return false;
    }
    CmlFrameImage* pFImgL = (CmlFrameImage*)m_pDataL;
    CmlFrameImage* pFImgR = (CmlFrameImage*)m_pDataR;
    return ( this->mlTemplateMatch( &(pFImgL->m_DataBlock), &(pFImgR->m_DataBlock), pFImgL->m_vecFeaPtsList, pFImgR->m_vecFeaPtsList, m_vecFeatMatchPt, \
                                    rectSearch, nTemplateSize, dCoef, nXOffSet, nYOffSet ) );
}
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

bool CmlStereoProc::mlTemplateMatchInRegion( CmlRasterBlock* pLeftImg, CmlRasterBlock* pRightImg, Pt2i ptLeft, Pt2i &ptRight, DOUBLE &dCoef, \
        SINT nXMin, SINT nXMax, SINT nYMin, SINT nYMax, \
        SINT nTemplateSize, DOUBLE dCoefThres , SINT nXOffSet, SINT nYOffSet, bool bIsRemoveAbPixel )
{
    if( ( nXMin > nXMax ) || ( nYMin > nYMax ) )
    {
        return false;
    }
    vector<Pt2i> vecPtL, vecPtR;
    vecPtL.push_back( ptLeft );
    MLRect rectS;
    rectS.dXMin = nXMin;
    rectS.dYMin = nYMin;
    rectS.dXMax = nXMax;
    rectS.dYMax = nYMax;
    for( SINT i = ptLeft.X + nXMin; i <= ptLeft.X + nXMax; ++i )
    {
        for( SINT j = ptLeft.Y + nYMin; j <= ptLeft.Y + nYMax; ++j )
        {
            Pt2i ptTemp;
            ptTemp.X = i+nXOffSet;
            ptTemp.Y = j+nYOffSet;
            vecPtR.push_back( ptTemp );
        }
    }
    vector<StereoMatchPt> vecSPts;
    this->mlTemplateMatch( pLeftImg, pRightImg, vecPtL, vecPtR, vecSPts, rectS, nTemplateSize, dCoefThres, nXOffSet, nYOffSet, bIsRemoveAbPixel );
    if( vecSPts.size() != 1 )
    {
        return false;
    }
    StereoMatchPt ptRes = vecSPts[0];
    ptRight.X = SINT(ptRes.ptRInImg.X + 0.1);
    ptRight.Y = SINT(ptRes.ptRInImg.Y + 0.1);
    dCoef = ptRes.dRelaCoef;

    return true;
}

bool CmlStereoProc::mlTemplateMatchInTwoFeatPtsVerify( const SCHAR* pLImg, const SCHAR* pRImg, vector<Pt2i> vecLPts, vector<Pt2i> vecRPts, vector<StereoMatchPt> &vecSMPts, \
                                                       MatchInRegPara matchPara, bool bIsRemoveAbPixel )
{
    CmlFrameImage clsImgL, clsImgR;
    if( ( false == clsImgL.LoadFile( pLImg ) )||( false == clsImgR.LoadFile( pRImg ) ) )
    {
        return false;
    }
    CmlStereoProc clsStereoProc;

    map<ULONG, UINT> mapLMatchRes;

    SINT nXMin = SINT( matchPara.dXMin + 0.5 );
    SINT nYMin = SINT( matchPara.dYMin + 0.5 );
    SINT nXMax = SINT( matchPara.dXMax + 0.5 );
    SINT nYMax = SINT( matchPara.dYMax + 0.5 );
    SINT nXOff = SINT( matchPara.dXOff + 0.5 );
    SINT nYOff = SINT( matchPara.dYOff + 0.5 );
    for( UINT i = 0; i < vecLPts.size(); ++i )
    {
        Pt2i ptCur = vecLPts[i];
        Pt2i ptRRes;
        DOUBLE dCoef = -1;
        if( true == clsStereoProc.mlTemplateMatchInRegion( &clsImgL.m_DataBlock, &clsImgR.m_DataBlock, ptCur, ptRRes, dCoef, \
                                                           nXMin, nXMax, nYMin, nYMax, matchPara.nTempSize, matchPara.dCoefThres, \
                                                           nXOff, nYOff, bIsRemoveAbPixel ) )
        {
            ULONG nTmp = ptCur.X * 1000000000000 + ptCur.Y * 100000000 + ptRRes.X * 10000 + ptRRes.Y;
            mapLMatchRes.insert( map<ULONG, UINT>::value_type( nTmp, i ) );
        }
    }

    for( UINT i = 0; i < vecRPts.size(); ++i )
    {
        Pt2i ptCur = vecRPts[i];
        Pt2i ptRRes;
        DOUBLE dCoef = -1;
        if( true == clsStereoProc.mlTemplateMatchInRegion( &clsImgR.m_DataBlock, &clsImgL.m_DataBlock, ptCur, ptRRes, dCoef, \
                                                           -nXMax, -nXMin, -nYMax, -nYMin, matchPara.nTempSize, matchPara.dCoefThres, \
                                                           -nXOff, -nYOff, bIsRemoveAbPixel ) )
        {
            ULONG nTmp = ptRRes.X * 1000000000000 + ptRRes.Y * 100000000 + ptCur.X * 10000 + ptCur.Y;
            map<ULONG, UINT>::iterator it = mapLMatchRes.find( nTmp );
            if( it != mapLMatchRes.end() )
            {
                StereoMatchPt ptSMPt;
                ptSMPt.ptLInImg.X = ptRRes.X;
                ptSMPt.ptLInImg.Y = ptRRes.Y;
                ptSMPt.ptRInImg.X = ptCur.X;
                ptSMPt.ptRInImg.Y = ptCur.Y;
                ptSMPt.dRelaCoef = dCoef;
                vecSMPts.push_back( ptSMPt );
            }
        }
    }
    return true;
}
bool CmlStereoProc::mlTemplateMatchInLFeatPtsToAll( const SCHAR* pLImg, const SCHAR* pRImg, vector<Pt2i> vecLPts, vector<StereoMatchPt> &vecSMPts, \
                                           MatchInRegPara matchPara, bool bIsRemoveAbPixel )
{
    CmlFrameImage clsImgL, clsImgR;
    if( ( false == clsImgL.LoadFile( pLImg ) )||( false == clsImgR.LoadFile( pRImg ) ) )
    {
        return false;
    }
    CmlStereoProc clsStereoProc;

    SINT nXMin = SINT( matchPara.dXMin + 0.5 );
    SINT nYMin = SINT( matchPara.dYMin + 0.5 );
    SINT nXMax = SINT( matchPara.dXMax + 0.5 );
    SINT nYMax = SINT( matchPara.dYMax + 0.5 );
    SINT nXOff = SINT( matchPara.dXOff + 0.5 );
    SINT nYOff = SINT( matchPara.dYOff + 0.5 );
    for( UINT i = 0; i < vecLPts.size(); ++i )
    {
        Pt2i ptCur = vecLPts[i];
        Pt2i ptRRes;
        DOUBLE dCoef = -1;
        if( true == clsStereoProc.mlTemplateMatchInRegion( &clsImgL.m_DataBlock, &clsImgR.m_DataBlock, ptCur, ptRRes, dCoef, \
                                                           nXMin, nXMax, nYMin, nYMax, matchPara.nTempSize, matchPara.dCoefThres, \
                                                           nXOff, nYOff, bIsRemoveAbPixel ) )
        {
            StereoMatchPt ptSMPt;
            ptSMPt.lID = ptCur.lID;
            ptSMPt.ptLInImg.lID = ptCur.lID;
            ptSMPt.ptLInImg.X = ptCur.X;
            ptSMPt.ptLInImg.Y = ptCur.Y;
            ptSMPt.ptRInImg.lID = ptCur.lID;
            ptSMPt.ptRInImg.X = ptRRes.X;
            ptSMPt.ptRInImg.Y = ptRRes.Y;
            ptSMPt.dRelaCoef = dCoef;
            vecSMPts.push_back( ptSMPt );
        }
    }
    return true;
}
bool CmlStereoProc::mlTemplateMatchInRFeatPtsToAll( const SCHAR* pLImg, const SCHAR* pRImg, vector<Pt2i> vecRPts, vector<StereoMatchPt> &vecSMPts, \
                                           MatchInRegPara matchPara, bool bIsRemoveAbPixel )
{
    CmlFrameImage clsImgL, clsImgR;
    if( ( false == clsImgL.LoadFile( pLImg ) )||( false == clsImgR.LoadFile( pRImg ) ) )
    {
        return false;
    }
    CmlStereoProc clsStereoProc;

    SINT nXMin = SINT( matchPara.dXMin + 0.5 );
    SINT nYMin = SINT( matchPara.dYMin + 0.5 );
    SINT nXMax = SINT( matchPara.dXMax + 0.5 );
    SINT nYMax = SINT( matchPara.dYMax + 0.5 );
    SINT nXOff = SINT( matchPara.dXOff + 0.5 );
    SINT nYOff = SINT( matchPara.dYOff + 0.5 );
    for( UINT i = 0; i < vecRPts.size(); ++i )
    {
        Pt2i ptCur = vecRPts[i];
        Pt2i ptRRes;
        DOUBLE dCoef = -1;
        if( true == clsStereoProc.mlTemplateMatchInRegion( &clsImgR.m_DataBlock, &clsImgL.m_DataBlock, ptCur, ptRRes, dCoef, \
                                                           -nXMax, -nXMin, -nYMax, -nYMin, matchPara.nTempSize, matchPara.dCoefThres, \
                                                           -nXOff, -nYOff, bIsRemoveAbPixel ) )
        {
            StereoMatchPt ptSMPt;
            ptSMPt.ptLInImg.X = ptRRes.X;
            ptSMPt.ptLInImg.Y = ptRRes.Y;
            ptSMPt.ptRInImg.X = ptCur.X;
            ptSMPt.ptRInImg.Y = ptCur.Y;
            ptSMPt.dRelaCoef = dCoef;
            vecSMPts.push_back( ptSMPt );
        }
    }
    return true;
}
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

bool CmlStereoProc::mlTemplateMatch( CmlRasterBlock* pLeftImg, CmlRasterBlock* pRightImg, vector<Pt2i> &vecPtL, \
                                     vector<Pt2i> &vecPtR, vector<StereoMatchPt> &vecFeatMatchPts, MLRect rectSearch, SINT nTemplateSize, \
                                     DOUBLE dCoef, SINT nXOffSet, SINT nYOffSet, bool bIsRemoveAbPixel )
{
    if( ( pLeftImg == NULL )||( pRightImg == NULL )||( pLeftImg->IsValid() == false )||( pRightImg->IsValid() == false ) )
    {
        return false;
    }

    SINT nTempHalfSize = nTemplateSize / 2;
    nTemplateSize = 2*nTempHalfSize + 1;

    MLRect RectLeft, RectRight;
    RectLeft.dXMin = 0.0 + nTempHalfSize;
    RectLeft.dXMax = pLeftImg->GetW() - 1 - nTempHalfSize;
    RectLeft.dYMin = 0.0 + nTempHalfSize;
    RectLeft.dYMax = pLeftImg->GetH() - 1 - nTempHalfSize;

    RectRight.dXMin = 0.0 + nTempHalfSize;
    RectRight.dXMax = pRightImg->GetW() - 1 - nTempHalfSize;
    RectRight.dYMin = 0.0 + nTempHalfSize;
    RectRight.dYMax = pRightImg->GetH() - 1 - nTempHalfSize;

    SINT nLW = pLeftImg->GetW();
    SINT nRW = pRightImg->GetW();

    SINT nLPtSize = vecPtL.size();
    SINT nRPtSize = vecPtR.size();
    DOUBLE *pdG1G1 = new DOUBLE[nLPtSize];
    DOUBLE *pdG1Avg = new DOUBLE[nLPtSize];


    BYTE *pLeftImgPtr = pLeftImg->GetData();
    BYTE *pRightImgPtr = pRightImg->GetData();

    for( UINT i = 0; i < vecPtL.size(); ++i )
    {
        Pt2i ptLeftTemp = vecPtL[i];
        SINT nX = ptLeftTemp.X;
        SINT nY = ptLeftTemp.Y;

        if( false == PtInRect( ptLeftTemp, RectLeft) )
        {
            pdG1G1[i] = -99999;
            continue;
        }
        else
        {
            DOUBLE dTempF = 0;
            DOUBLE dTempS = 0;
            bool bIsInAbPixelL = false;
            for ( SINT j = nY - nTempHalfSize; j <= nY + nTempHalfSize; ++j )
            {
                for ( SINT k = nX - nTempHalfSize; k <= nX + nTempHalfSize; ++k )
                {
                    DOUBLE dTemp = *( pLeftImgPtr + j * nLW + k );
                    if( ( true == bIsRemoveAbPixel )&&( false == bIsInAbPixelL) )
                    {
                        if( fabs(dTemp-255) < ML_ZERO )
                        {
                            bIsInAbPixelL = true;
                        }
                    }
                    dTempS += dTemp;
                    dTemp *= dTemp;
                    dTempF += dTemp;
                }
            }
            if( ( true == bIsRemoveAbPixel )&&( true == bIsInAbPixelL ) )
            {
                pdG1G1[i] = -99999;
            }
            else
            {
                dTempS /= ( nTemplateSize* nTemplateSize );
                pdG1Avg[i] = dTempS;
                pdG1G1[i] = dTempF / ( nTemplateSize * nTemplateSize ) - dTempS * dTempS;
            }

        }

    }


    DOUBLE *pdG2G2 = new DOUBLE[nRPtSize];
    DOUBLE *pdG2Avg = new DOUBLE[nRPtSize];

    for( UINT i = 0; i < vecPtR.size(); ++i )
    {
        Pt2i ptRightTemp = vecPtR[i];
        SINT nX = ptRightTemp.X;
        SINT nY = ptRightTemp.Y;

        if( false == PtInRect( ptRightTemp, RectRight) )
        {
            pdG2G2[i] = -99999;
            continue;
        }
        else
        {
            DOUBLE dTempF = 0;
            DOUBLE dTempS = 0;
            bool bIsInAbPixelR = false;
            for ( SINT j = nY - nTempHalfSize; j <= nY + nTempHalfSize; ++j )
            {
                for ( SINT k = nX - nTempHalfSize; k <= nX + nTempHalfSize; ++k )
                {
                    DOUBLE dTemp = *( pRightImgPtr + j * nRW + k );
                    if( ( true == bIsRemoveAbPixel )&&( false == bIsInAbPixelR) )
                    {
                        if( fabs(dTemp-255) < ML_ZERO )
                        {
                            bIsInAbPixelR = true;
                        }
                    }
                    dTempS += dTemp;
                    dTemp *= dTemp;
                    dTempF += dTemp;
                }
            }
            if( ( true == bIsRemoveAbPixel )&&( true == bIsInAbPixelR ) )
            {
                pdG2G2[i] = -99999;
            }
            else
            {
                dTempS /= ( nTemplateSize* nTemplateSize );
                pdG2Avg[i] = dTempS;
                pdG2G2[i] = dTempF / ( nTemplateSize * nTemplateSize ) - dTempS * dTempS;
            }

        }

    }

    for( UINT i = 0; i < vecPtL.size(); ++i )
    {
        if( *(pdG1G1+i) < -1000 )
        {
            continue;
        }
        DOUBLE dCoe = -99999;

        Pt2i ptTemResR;

        Pt2i ptTempL = vecPtL[i];

        MLRect RectRighSearch;
        RectRighSearch.dXMin = ptTempL.X + rectSearch.dXMin + nXOffSet;
        RectRighSearch.dXMax = ptTempL.X + rectSearch.dXMax + nXOffSet;
        RectRighSearch.dYMin = ptTempL.Y + rectSearch.dYMin + nYOffSet;
        RectRighSearch.dYMax = ptTempL.Y + rectSearch.dYMax + nYOffSet;

        for( UINT j = 0;  j < vecPtR.size(); ++j )
        {
            Pt2i ptTempR = vecPtR[j];

            if( *(pdG2G2+j) < -1000 )
            {
                continue;
            }

            if( false == PtInRect( ptTempR, RectRighSearch) )
            {
                continue;
            }

            DOUBLE dTemp = 0;
            for ( SINT k = -nTempHalfSize; k <= nTempHalfSize; ++k )
            {
                for ( SINT l = -nTempHalfSize; l <= nTempHalfSize; ++l )
                {
                    DOUBLE dg1 = *( pLeftImgPtr +  ( k + ptTempL.Y ) * nLW + l + ptTempL.X ) ;
                    DOUBLE dg2 = *( pRightImgPtr + ( k + ptTempR.Y ) * nRW + l + ptTempR.X ) ;
                    dTemp += dg1 * dg2;
                }
            }
            dTemp /= ( nTemplateSize * nTemplateSize );
            dTemp -= ( ( *( pdG1Avg + i ) ) * ( *( pdG2Avg + j ) ) );
            dTemp /= sqrt( ( *( pdG1G1 + i ) ) * ( *( pdG2G2 + j ) ) );
            if ( dCoe < dTemp )
            {
                dCoe = dTemp;
                ptTemResR = ptTempR;
            }

        }
        if ( dCoe > dCoef )
        {
            StereoMatchPt pt;
            pt.ptLInImg.X = ptTempL.X;
            pt.ptLInImg.Y = ptTempL.Y;
            pt.ptRInImg.X = ptTemResR.X;
            pt.ptRInImg.Y = ptTemResR.Y;
            pt.dRelaCoef = dCoe;

            vecFeatMatchPts.push_back( pt );
        }

    }
    delete[] pdG1Avg;
    delete[] pdG2Avg;
    delete[] pdG1G1;
    delete[] pdG2G2;

    return true;

}


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
bool CmlStereoProc::mlLsMatchInFrameImg(  vector<StereoMatchPt> &vecMatchPt, SINT nTempSize )
{
    if( ( m_pDataL == NULL ) || ( m_pDataR == NULL ) )
    {
        return false;
    }
    CmlFrameImage* pFImgL = (CmlFrameImage*)m_pDataL;
    CmlFrameImage* pFImgR = (CmlFrameImage*)m_pDataR;

    for( UINT i = 0; i < vecMatchPt.size(); ++i )
    {
        StereoMatchPt* pPtTemp = &( vecMatchPt.at(i) );
        DOUBLE dCoef = 0;
        if( true == mlLsMatch( &pFImgL->m_DataBlock, &pFImgR->m_DataBlock, \
                               pPtTemp->ptLInImg.X, pPtTemp->ptLInImg.Y, pPtTemp->ptRInImg.X, pPtTemp->ptRInImg.Y, nTempSize, dCoef ) )

        {
            pPtTemp->dRelaCoef = dCoef;
        }
    }
    return true;
}

bool getCoef( DOUBLE* pL, DOUBLE* pR, SINT nTSize, DOUBLE& dCoef )
{
    DOUBLE ddG1G1 = 0;
    DOUBLE ddG1Avg = 0;

    SINT nTempSize,nTempTotalSize;
    nTempSize = nTSize / 2;
    nTempTotalSize = nTSize * nTSize;

    ////////////////////////////////////////////////////////////////////////

    DOUBLE dTempF = 0;
    DOUBLE dTempS = 0;

    for ( SINT i = 0; i < nTempTotalSize; ++i )
    {
        DOUBLE dTemp = pL[i];
        dTempS += dTemp;
        dTemp *= dTemp;
        dTempF += dTemp;

    }
    ddG1Avg = dTempS;
    ddG1G1 = dTempF - ddG1Avg * ddG1Avg / nTempTotalSize;


    DOUBLE  ddG2G2 = 0;
    DOUBLE  ddG2Avg = 0;
    dTempF = 0;
    dTempS = 0;

    for ( SINT i = 0; i < nTempTotalSize; ++i )
    {
        DOUBLE dTemp = pR[i];
        dTempS += dTemp;
        dTemp *= dTemp;
        dTempF += dTemp;

    }
    ddG2Avg = dTempS;
    ddG2G2 = dTempF - ddG2Avg * ddG2Avg / nTempTotalSize;

    DOUBLE dtemp = 0;
    for ( SINT i = 0; i < nTempTotalSize; ++i )
    {
        dtemp += pL[i] * pR[i];
    }
    dtemp -= ddG1Avg * ddG2Avg / nTempTotalSize;
    DOUBLE dT = sqrt( ddG1G1 * ddG2G2 );
    if( dT < 10e-7 )
    {
        dCoef = 0;
    }
    else
    {
        dCoef = dtemp / dT;
    }
    return TRUE;
}
bool CmlStereoProc::mlTemplateMatchWithAccu( CmlRasterBlock* pLeftImg, CmlRasterBlock* pRightImg, vector<Pt2i> &vecPtL, \
                          vector<Pt2i> &vecPtR, vector<StereoMatchPt> &vecMatchPts, MLRect rectSearch, \
                          SINT nTemplateSize, DOUBLE dCoef, SINT nXOffSet, SINT nYOffSet, bool bIsRemoveAbPixel)
{
    vector<StereoMatchPt> vecTmpMPts;
    if( false == this->mlTemplateMatch( pLeftImg, pRightImg, vecPtL, vecPtR, vecTmpMPts, rectSearch, nTemplateSize, dCoef, nXOffSet, nYOffSet, bIsRemoveAbPixel ) )
    {
        return false;
    }
    MLRect rectTmp;

    for( UINT i = 0; i < vecTmpMPts.size(); ++i )
    {
        StereoMatchPt ptSPt = vecTmpMPts[i];
        Pt2i ptL, ptR, ptRRes;
        ptL.X = SINT(ptSPt.ptLInImg.X + 0.5);
        ptL.Y = SINT(ptSPt.ptLInImg.Y + 0.5);
        ptR.X = SINT(ptSPt.ptRInImg.X + 0.5);
        ptR.Y = SINT(ptSPt.ptRInImg.Y + 0.5);
        ptRRes = ptR;
        DOUBLE dCoefCur = ptSPt.dRelaCoef;
        if( true == this->mlTemplateMatchInRegion( pLeftImg, pRightImg, ptL, ptRRes, dCoefCur, (ptR.X-2), (ptR.X+2), (ptR.Y-2), (ptR.Y+2), nTemplateSize, dCoef, \
                                                  0, 0, bIsRemoveAbPixel ))
        {
            rectTmp.dXMax = ptL.X + rectSearch.dXMax + nXOffSet;
            rectTmp.dXMin = ptL.X + rectSearch.dXMin + nXOffSet;
            rectTmp.dYMax = ptL.Y + rectSearch.dYMax + nYOffSet;
            rectTmp.dYMin = ptL.Y + rectSearch.dYMin + nYOffSet;
            if( true == PtInRect( ptRRes, rectTmp) )
            {
                ptR = ptRRes;
            }
        }
        StereoMatchPt sPtCur;
        sPtCur.ptLInImg.X = ptL.X;
        sPtCur.ptLInImg.Y = ptL.Y;
        sPtCur.ptRInImg.X = ptR.X;
        sPtCur.ptRInImg.Y = ptR.Y;
        sPtCur.dRelaCoef = dCoefCur;
        vecMatchPts.push_back( sPtCur );
    }
    return true;
}

bool resample( CmlRasterBlock* pImage, DOUBLE dx, DOUBLE dy, SINT nTempSize, DOUBLE* x_par, DOUBLE* y_par, DOUBLE* pData )
{
    SINT nHSize = nTempSize / 2;
    if ( ( ( dx+nHSize) >= pImage->GetW() )||( dx < -nHSize )||( ( dy+nHSize) >= pImage->GetH() )||( dy < -nHSize ) )
    {
        return false;
    }

    for ( SINT i = -nHSize; i <= nHSize; ++i  )//row
    {

        for ( SINT j = -nHSize; j <= nHSize; ++j )//col
        {
            DOUBLE dTx = dx + j;
            DOUBLE dTy = dy + i;
            dTx = x_par[0] + x_par[1]*dTx + x_par[2]*dTx;
            dTy = y_par[0] + y_par[1]*dTy + y_par[2]*dTy;

            dTx += 1.0e-6;
            dTy += 1.0e-6;

            SINT nxL = SINT( dTx );
            SINT nxH = nxL+1;
            SINT nyL = SINT( dTy );
            SINT nyH = nyL+1;

            if( ( nxL < 0 )||( nxH >= SINT(pImage->GetW() ) )||( nyL < 0 )||( nyH >= SINT(pImage->GetH()) ) )
            {
                return false;
            }

            BYTE* pLLG = (pImage->GetData() + nyL*pImage->GetW() + nxL);

            DOUBLE dGray =	(dTx - nxL)*(dTy - nyL)*( *(pLLG + pImage->GetW() + 1) ) +
                            (dTx - nxL)*(nyH - dTy)*( *(pLLG + 1 ) ) +
                            (nxH - dTx)*(dTy - nyL)*( *(pLLG + pImage->GetW() ) ) +
                            (nxH - dTx)*(nyH - dTy)*( *(pLLG) );

            pData[(i+nHSize)*nTempSize+j+nHSize] = dGray;
        }
    }
    return true;
}
bool grayRectify( DOUBLE* pData, DOUBLE* pDst, SINT nTSize,DOUBLE h0, DOUBLE h1 )
{
    SINT nS = nTSize*nTSize;
    for ( SINT i = 0; i < nS; ++i )
    {
        pDst[i] = pData[i]*h1 + h0;
    }
    return true;
}

bool getCoreImg( DOUBLE* pSrc, DOUBLE* pDst, SINT nDstTempSize )
{
    SINT nSrc = nDstTempSize + 2;
    for ( SINT i = 0; i < nDstTempSize; ++i )
    {
        for ( SINT j = 0; j < nDstTempSize; ++j)
        {
            pDst[i*nDstTempSize+j] = pSrc[(i+1)*nSrc+j+1];
        }
    }
    return true;
}
DOUBLE getDifX( DOUBLE* pRTemp, SINT nx, SINT ny, SINT nRegionSize  )
{
    DOUBLE* pX1 = pRTemp + (ny + 1)*(nRegionSize+2) + nx ;
    DOUBLE* pX2 = pX1 + 2;

    return 0.5*( (*pX2) - *pX1 );
}
DOUBLE getDifY( DOUBLE* pRTemp, SINT nx, SINT ny, SINT nRegionSize  )
{
    DOUBLE* pY1 = pRTemp + (ny )*(nRegionSize+2) + nx + 1 ;
    DOUBLE* pY2 = pY1 + 2*(nRegionSize + 2);

    return 0.5*( (*pY2) - *pY1 );
}
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
bool CmlStereoProc::mlLsMatch( CmlRasterBlock* pBlockL,  CmlRasterBlock* pBlockR, DOUBLE dLx, DOUBLE dLy, DOUBLE& dRx, DOUBLE& dRy, SINT nTempSize, DOUBLE& dCoef )
{
    DOUBLE dOrgRx, dOrgRy;
    dOrgRx = dRx;
    dOrgRy = dRy;

    DOUBLE* pLOrig = new DOUBLE[nTempSize*nTempSize];
    DOUBLE* pRRegion = new DOUBLE[nTempSize*nTempSize];
    DOUBLE* pRRectRegion = new DOUBLE[nTempSize*nTempSize];

    SINT nRSize = nTempSize + 2;
    DOUBLE* pRTemp = new DOUBLE[nRSize*nRSize];
    DOUBLE* pRRect = new DOUBLE[nRSize*nRSize];

    DOUBLE h0, h1;

    DOUBLE x_par[3], y_par[3];
    x_par[0] = 0;
    x_par[1] = 1;
    x_par[2] = 0;
    y_par[0] = 0;
    y_par[1] = 0;
    y_par[2] = 1;

    //////////////////////////////////////////////////////////////////////////
    if( false == resample( pBlockL, dLx, dLy, nTempSize, x_par, y_par, pLOrig ) )
    {
        delete[] pLOrig;
        delete[] pRRegion;
        delete[] pRRectRegion;

        delete[] pRTemp;
        delete[] pRRect;
        return false;
    }

    //////////////////////////////////////////////////////////////////////////
    x_par[0] = dRx - dLx;
    x_par[1] = 1;
    x_par[2] = 0;
    y_par[0] = dRy - dLy;
    y_par[1] = 0;
    y_par[2] = 1;
    h0 = 0;
    h1 = 1;

    SINT nTotalS = nTempSize*nTempSize;
    CvMat* pA = cvCreateMat( nTotalS, 8, CV_64F );
    CvMat* pLM = cvCreateMat( nTotalS, 1, CV_64F );
    CvMat* pX = cvCreateMat( 8, 1, CV_64F );

    dCoef = 0;

    DOUBLE x_t[3], y_t[3], h0_t, h1_t;
    x_t[0] = x_par[0];
    x_t[1] = x_par[1];
    x_t[2] = x_par[2];
    y_t[0] = y_par[0];
    y_t[1] = y_par[1];
    y_t[2] = y_par[2];
    h0_t = h0;
    h1_t = h1;

    for ( SINT i = 0; i < 5; ++i )
    {
        bool bIsOk = resample( pBlockR, dLx, dLy, nRSize, x_t, y_t, pRTemp );
        if ( !bIsOk )
        {
            cvReleaseMat( &pA );
            cvReleaseMat( &pLM );
            cvReleaseMat( &pX );

            delete[] pLOrig;
            delete[] pRRegion;
            delete[] pRRectRegion;

            delete[] pRTemp;
            delete[] pRRect;

            return false;
        }
        grayRectify( pRTemp , pRRect, nRSize, h0_t, h1_t );
        getCoreImg( pRRect, pRRectRegion, nTempSize );
        getCoreImg( pRTemp, pRRegion, nTempSize );
        DOUBLE dCoefTemp = 0;
        getCoef( pLOrig, pRRectRegion, nTempSize, dCoefTemp );
        if ( dCoefTemp < dCoef )
        {
            break;
        }
        else
        {
            dCoef = dCoefTemp;

            x_par[0] = x_t[0];
            x_par[1] = x_t[1];
            x_par[2] = x_t[2];

            y_par[0] = y_t[0];
            y_par[1] = y_t[1];
            y_par[2] = y_t[2];

            h0 = h0_t;
            h1 = h1_t;

        }

        SINT nHSize;
        nHSize = nTempSize / 2;

        for ( SINT i = 0; i < nTempSize; ++i )//row
        {
            for ( SINT j = 0; j < nTempSize; ++j )//col
            {
                DOUBLE dTemp = 0;
                SINT nIndex = i*nTempSize+j;

                dTemp = 1.0;
                cvmSet( pA, nIndex, 0, dTemp );

                dTemp = pRRegion[nIndex];
                cvmSet( pA, nIndex, 1, dTemp );

                DOUBLE difX = getDifX( pRTemp, j, i, nTempSize );

                dTemp = difX;
                cvmSet( pA, nIndex, 2, dTemp );

                dTemp = /*(dLx - nHSize + j)*/0*difX;
                cvmSet( pA, nIndex, 3, dTemp );

                dTemp = /*(dLy - nHSize + i)*/0*difX;
                cvmSet( pA, nIndex, 4, dTemp );

                DOUBLE difY = getDifY( pRTemp, j, i, nTempSize );

                dTemp = difY;
                cvmSet( pA, nIndex, 5, dTemp );

                dTemp = /*(dLx - nHSize + j)*/0*difY;
                cvmSet( pA, nIndex, 6, dTemp );

                dTemp = /*(dLy - nHSize + i)*/0*difY;
                cvmSet( pA, nIndex, 7, dTemp );


                dTemp = pLOrig[nIndex] - pRRegion[nIndex];
                cvmSet( pLM, nIndex, 0, dTemp );
            }
        }

        cvSolve( pA, pLM, pX, CV_NORMAL );

        DOUBLE dh0 = cvmGet( pX, 0, 0 );
        DOUBLE dh1 = cvmGet( pX, 1, 0 );
        DOUBLE da0 = cvmGet( pX, 2, 0 );
        DOUBLE da1 = cvmGet( pX, 3, 0 );
        DOUBLE da2 = cvmGet( pX, 4, 0 );
        DOUBLE db0 = cvmGet( pX, 5, 0 );
        DOUBLE db1 = cvmGet( pX, 6, 0 );
        DOUBLE db2 = cvmGet( pX, 7, 0 );

        x_t[0] = x_par[0] + da0 + x_par[0]*da1 + y_par[0]*da2;
        x_t[1] = x_par[1] + x_par[1]*da1 + y_par[1]*da2;
        x_t[2] = x_par[2] + x_par[2]*da1 + y_par[2]*da2;

        y_t[0] = y_par[0] + db0 + x_par[0]*db1 + y_par[0]*db2;
        y_t[1] = y_par[1] + x_par[1]*db1 + y_par[1]*db2;
        y_t[2] = y_par[2] + x_par[2]*db1 + y_par[2]*db2;

        h0_t = h0 + dh0 + h0*dh1;
        h1_t = h1 + h1*dh1;

        if ( ( abs(da0) > 3.0 )||( abs( db0) > 3.0 ) )
        {
            break;
        }

        if ( ( abs(da0) < 0.001 )&&( abs(db0) < 0.001 ) )
        {
            break;
        }



    }
    //////////////////////////////////////////////////////////////////////////
    delete[] pLOrig;
    delete[] pRRegion;
    delete[] pRRectRegion;

    delete[] pRTemp;
    delete[] pRRect;
    cvReleaseMat( &pA );
    cvReleaseMat( &pLM );
    cvReleaseMat( &pX );

    DOUBLE dTTRx = x_par[0] + x_par[1]*dLx + x_par[2]*dLy;
    DOUBLE dTTRy = y_par[0] + y_par[1]*dLx + y_par[2]*dLy;

    if ( ( abs( dRx - dTTRx ) > 1.0 )||( abs( dRy - dTTRy ) > 1.0 ) )
    {
        return false;
    }
    else
    {
        dRx = dTTRx;
        dRy = dTTRy;
    }

    return true;

}
///**
//* @fn getxyFromXYZ
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief ������ά�㼰�ⷽλԪ�������
//* @param x ���x
//* @param y ���y
//* @param X ��ά��X
//* @param Y ��ά��Y
//* @param Z ��ά��Z
//* @param XsYsZs �ⷽλ��Ԫ��
//* @param R ��ת����
//* @param fx x���򽹾�
//* @param fy y���򽹾�
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @version 1.0
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//bool getxyFromXYZ( DOUBLE& x, DOUBLE& y, DOUBLE X, DOUBLE Y, DOUBLE Z, DOUBLE *XsYsZs, DOUBLE *R, DOUBLE fx, DOUBLE fy )
//{
//    DOUBLE dX = X - XsYsZs[0];
//    DOUBLE dY = Y - XsYsZs[1];
//    DOUBLE dZ = Z - XsYsZs[2];
//
//    DOUBLE dCoefX = R[0] * dX + R[3] * dY + R[6] * dZ;
//    DOUBLE dCoefY = R[1] * dX + R[4] * dY + R[7] * dZ;
//    DOUBLE dCoefZ = R[2] * dX + R[5] * dY + R[8] * dZ;
//
//    x = -fx * dCoefX / dCoefZ;
//    y = -fy * dCoefY / dCoefZ;
//
//    return true;
//}
//bool getxyFromXYZ( Pt2d &ptxy, Pt3d ptXYZ, Pt3d ptXYZOrg, CmlMat matOPK, DOUBLE fx, DOUBLE fy )
//{
//    DOUBLE dX = ptXYZ.X - ptXYZOrg.X;
//    DOUBLE dY = ptXYZ.Y - ptXYZOrg.Y;
//    DOUBLE dZ = ptXYZ.Z - ptXYZOrg.Z;
//
//    DOUBLE dCoefX = matOPK.GetAt( 0, 0 ) * dX + matOPK.GetAt( 1, 0 ) * dY + matOPK.GetAt( 2, 0 ) * dZ;
//    DOUBLE dCoefY = matOPK.GetAt( 0, 1 ) * dX + matOPK.GetAt( 1, 1 ) * dY + matOPK.GetAt( 2, 1 ) * dZ;
//    DOUBLE dCoefZ = matOPK.GetAt( 0, 2 ) * dX + matOPK.GetAt( 1, 2 ) * dY + matOPK.GetAt( 2, 2 ) * dZ;
//
//    ptxy.X = -fx * dCoefX / dCoefZ;
//    ptxy.Y = -fy * dCoefY / dCoefZ;
//
//    return true;
//}
/**
* @fn
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ��ռ�ǰ������
* @param vecMatchPt ƥ���
* @param vecPts �ռ���ά��
* @param dThres ������ֵ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlStereoProc::mlInterSectionInFrameImg(  vector<StereoMatchPt> &vecMatchPt, vector<Pt3d> &vecPts, DOUBLE dThres )
{
    if( ( m_pDataL == NULL ) || ( m_pDataR == NULL ) )
    {
        return false;
    }
    SINT nWL,nWR,nHL,nHR;
    nWL = m_pDataL->GetWidth();
    nHL = m_pDataL->GetHeight();
    nWR = m_pDataR->GetWidth();
    nHR = m_pDataR->GetHeight();
    CmlFrameImage* pImgL = (CmlFrameImage*)(m_pDataL);
    CmlFrameImage* pImgR = (CmlFrameImage*)(m_pDataR);

    for( UINT i = 0; i < vecMatchPt.size(); ++i )
    {
        StereoMatchPt* pt = &(vecMatchPt[i]);
        Pt3d ptXYZ;
        if( true == mlInterSection( pt->ptLInImg, pt->ptRInImg, nHL, nHR, ptXYZ, &pImgL->m_InOriPara, &pImgL->m_ExOriPara, &pImgR->m_InOriPara, &pImgR->m_ExOriPara, dThres ) )
        {
            vecPts.push_back( ptXYZ );
        }
    }
    return true;
}
/**
* @fn
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
bool CmlStereoProc::mlInterSectionInFrameImg(  vector<StereoMatchPt> &vecMatchPt, DOUBLE dThres )
{
    if( ( m_pDataL == NULL ) || ( m_pDataR == NULL ) )
    {
        return false;
    }
    SINT nWL,nHL,nWR,nHR;
    nWL = m_pDataL->GetWidth();
    nHL = m_pDataL->GetHeight();
    nWR = m_pDataR->GetWidth();
    nHR = m_pDataR->GetHeight();
    CmlFrameImage* pImgL = (CmlFrameImage*)(m_pDataL);
    CmlFrameImage* pImgR = (CmlFrameImage*)(m_pDataR);

    for( UINT i = 0; i < vecMatchPt.size(); ++i )
    {
        StereoMatchPt* pt = &(vecMatchPt[i]);
        mlInterSection( pt->ptLInImg, pt->ptRInImg, nHL, nHR, *pt, &pImgL->m_InOriPara, &pImgL->m_ExOriPara, &pImgR->m_InOriPara, &pImgR->m_ExOriPara, dThres );
    }
    return true;
}
bool CmlStereoProc::mlInterSectionInFrameImg(  vector<StereoMatchPt> &vecMatchPt, vector<bool> &vecbIsValid, DOUBLE dThres )
{
    if( ( m_pDataL == NULL ) || ( m_pDataR == NULL ) )
    {
        return false;
    }
    SINT nWL,nHL,nWR,nHR;
    nWL = m_pDataL->GetWidth();
    nHL = m_pDataL->GetHeight();
    nWR = m_pDataR->GetWidth();
    nHR = m_pDataR->GetHeight();
    CmlFrameImage* pImgL = (CmlFrameImage*)(m_pDataL);
    CmlFrameImage* pImgR = (CmlFrameImage*)(m_pDataR);

    for( UINT i = 0; i < vecMatchPt.size(); ++i )
    {
        StereoMatchPt* pt = &(vecMatchPt[i]);
        if( true == mlInterSection( pt->ptLInImg, pt->ptRInImg, nHL, nHR, *pt, &pImgL->m_InOriPara, &pImgL->m_ExOriPara, &pImgR->m_InOriPara, &pImgR->m_ExOriPara, dThres ) )
        {
            vecbIsValid.push_back( true );
        }
        else
        {
            vecbIsValid.push_back( false );
        }
    }
    return true;
}
/**
* @fn
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ������У�����ܵ�ͨ�ÿռ�ǰ�����ắ��
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
bool CmlStereoProc::mlInterSection(  Pt2d ptL, Pt2d ptR, SINT nHeightL, SINT nHeightR, Pt3d &ptXYZ, InOriPara* pInOriL, ExOriPara* pExOriL, InOriPara* pInOriR, ExOriPara* pExOriR, DOUBLE dThres )
{
    if( ( NULL == pInOriL )||( NULL == pInOriR )||( NULL == pExOriL )||( NULL == pExOriR ) )
    {
        return false;
    }

    CmlMat matRotaL, matRotaR, matA;
    OPK2RMat( &pExOriL->ori, &matRotaL );
    OPK2RMat( &pExOriR->ori, &matRotaR );

//    DOUBLE x1, y1, x2, y2;
    CmlFrameImage clsFrmImg;
    Pt2d ptLUnDis, ptRUnDis;
    clsFrmImg.UnDisCorToPlaneFrame( ptL, *pInOriL, nHeightL, ptLUnDis );
    clsFrmImg.UnDisCorToPlaneFrame( ptR, *pInOriR, nHeightR, ptRUnDis );

    return ( this->mlInterSection( ptLUnDis.X, ptLUnDis.Y, ptRUnDis.X, ptRUnDis.Y, &matRotaL, &matRotaR, pExOriL->pos, pExOriR->pos, pInOriL->f, pInOriR->f, ptXYZ,  dThres ) );
}
bool CmlStereoProc::mlInterSection(  Pt2d ptL, Pt2d ptR, Pt3d &ptXYZ, \
                      InOriPara* pInOriL, ExOriPara* pExOriL, InOriPara* pInOriR, ExOriPara* pExOriR, DOUBLE dThres )
{
    CmlMat matRotaL, matRotaR, matA;
    OPK2RMat( &pExOriL->ori, &matRotaL );
    OPK2RMat( &pExOriR->ori, &matRotaR );

    return ( this->mlInterSection( ptL.X, ptL.Y, ptR.X, ptR.Y, &matRotaL, &matRotaR, pExOriL->pos, pExOriR->pos, pInOriL->f, pInOriR->f, ptXYZ,  dThres ) );
}
/**
* @fn
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
bool CmlStereoProc::mlInterSection( DOUBLE dLx, DOUBLE dLy, DOUBLE dRx, DOUBLE dRy, CmlMat* pMatL, CmlMat* pMatR, Pt3d PtXsYsZsL, Pt3d PtXsYsZsR, DOUBLE f1, DOUBLE f2, Pt3d &PtXYZ, DOUBLE dThres )
{
//    if( ( pMatL == NULL )||(  pMatL->IsValid() == false )||( pMatR == NULL)||(  pMatR->IsValid() == false ) )
//    {
//        return false;
//    }
//    DOUBLE f1x, f1y, f2x, f2y;
//    f1x = f1y = f1;
//    f2x = f2y = f2;
//
//    DOUBLE x1, y1, x2, y2;
//    x1 = dLx;
//    y1 = dLy;
//    x2 = dRx;
//    y2 = dRy;
//
//    DOUBLE R1[9], R2[9];
//    memcpy( R1, pMatL->GetData(), sizeof(DOUBLE)*9 );
//    memcpy( R2, pMatR->GetData(), sizeof(DOUBLE)*9 );
//
//    DOUBLE XYZ[3], XsYsZs1[3], XsYsZs2[3];
//    XsYsZs1[0] = PtXsYsZsL.X;
//    XsYsZs1[1] = PtXsYsZsL.Y;
//    XsYsZs1[2] = PtXsYsZsL.Z;
//
//    XsYsZs2[0] = PtXsYsZsR.X;
//    XsYsZs2[1] = PtXsYsZsR.Y;
//    XsYsZs2[2] = PtXsYsZsR.Z;
//
//    CmlMat matA;
//    if( false == matA.Initial( 4, 3 ) )
//    {
//        return false;
//    }
//
//    matA.SetAt( 0, 0, f1x * R1[0] + x1 * R1[2] );
//    matA.SetAt( 0, 1, f1x * R1[3] + x1 * R1[5] );
//    matA.SetAt( 0, 2, f1x * R1[6] + x1 * R1[8] );
//
//    matA.SetAt( 1, 0, f1y * R1[1] + y1 * R1[2] );
//    matA.SetAt( 1, 1, f1y * R1[4] + y1 * R1[5] );
//    matA.SetAt( 1, 2, f1y * R1[7] + y1 * R1[8] );
//
//    matA.SetAt( 2, 0, f2x * R2[0] + x2 * R2[2] );
//    matA.SetAt( 2, 1, f2x * R2[3] + x2 * R2[5] );
//    matA.SetAt( 2, 2, f2x * R2[6] + x2 * R2[8] );
//
//    matA.SetAt( 3, 0, f2y * R2[1] + y2 * R2[2] );
//    matA.SetAt( 3, 1, f2y * R2[4] + y2 * R2[5] );
//    matA.SetAt( 3, 2, f2y * R2[7] + y2 * R2[8] );
//
//    CmlMat matB;
//    matB.Initial( 4, 1 );
//
//    DOUBLE dTempVal = 0;
//    dTempVal = f1x * R1[0] * XsYsZs1[0] + f1x * R1[3] * XsYsZs1[1] + f1x * R1[6] * XsYsZs1[2] +
//               x1 * R1[2] * XsYsZs1[0] + x1 * R1[5] * XsYsZs1[1] + x1 * R1[8] * XsYsZs1[2];
//    matB.SetAt( 0, 0, dTempVal );
//
//
//    dTempVal = f1y * R1[1] * XsYsZs1[0] + f1y * R1[4] * XsYsZs1[1] + f1y * R1[7] * XsYsZs1[2] +
//               y1 * R1[2] * XsYsZs1[0] + y1 * R1[5] * XsYsZs1[1] + y1 * R1[8] * XsYsZs1[2];
//    matB.SetAt( 1, 0, dTempVal );
//
//
//    dTempVal = f2x * R2[0] * XsYsZs2[0] + f2x * R2[3] * XsYsZs2[1] + f2x * R2[6] * XsYsZs2[2] +
//               x2 * R2[2] * XsYsZs2[0] + x2 * R2[5] * XsYsZs2[1] + x2 * R2[8] * XsYsZs2[2];
//    matB.SetAt( 2, 0, dTempVal );
//
//    dTempVal = f2y * R2[1] * XsYsZs2[0] + f2y * R2[4] * XsYsZs2[1] + f2y * R2[7] * XsYsZs2[2] +
//               y2 * R2[2] * XsYsZs2[0] + y2 * R2[5] * XsYsZs2[1] + y2 * R2[8] * XsYsZs2[2];
//    matB.SetAt( 3, 0, dTempVal );
//
//    CmlMat matX;
//
//    mlMatSolveSVD( &matA, &matB, &matX );
//
//    XYZ[0] = matX.GetAt( 0, 0 );
//    XYZ[1] = matX.GetAt( 1, 0 );
//    XYZ[2] = matX.GetAt( 2, 0 );
//
//    //////////////////////////////////////////////////////////////////////////
//    Pt3d ptPixelL, ptPixelR;
//    ptPixelL.X = R1[0]*x1+R1[1]*y1+R1[2]*(-1.0*f1);
//    ptPixelL.Y = R1[3]*x1+R1[4]*y1+R1[5]*(-1.0*f1);
//    ptPixelL.Z = R1[6]*x1+R1[7]*y1+R1[8]*(-1.0*f1);
//
//    Pt3d pt3dL, pt3dR;
//    pt3dL.X = XYZ[0] - XsYsZs1[0];
//    pt3dL.Y = XYZ[1] - XsYsZs1[1];
//    pt3dL.Z = XYZ[2] - XsYsZs1[2];
//
//    DOUBLE dTempMod = ptPixelL.X * pt3dL.X + ptPixelL.Y * pt3dL.Y + ptPixelL.Z * pt3dL.Z;
//    if( dTempMod < 0 )
//    {
//        return false;
//    }
//
//    ptPixelR.X = R2[0]*x2+R2[1]*y2+R2[2]*(-1.0*f2);
//    ptPixelR.Y = R2[3]*x2+R2[4]*y2+R2[5]*(-1.0*f2);
//    ptPixelR.Z = R2[6]*x2+R2[7]*y2+R2[8]*(-1.0*f2);
//
//    pt3dR.X = XYZ[0] - XsYsZs2[0];
//    pt3dR.Y = XYZ[1] - XsYsZs2[1];
//    pt3dR.Z = XYZ[2] - XsYsZs2[2];
//
//    dTempMod = ptPixelR.X * pt3dR.X + ptPixelR.Y * pt3dR.Y + ptPixelR.Z * pt3dR.Z;
//    if( dTempMod < 0 )
//    {
//        return false;
//    }
//
//
//    //////////////////////////////////////////////////////////////////////////
//
//    for ( SINT i = 0; i < 10; ++i )
//    {
//
//        DOUBLE dZCoef1 = R1[2] * ( XYZ[0] - XsYsZs1[0] ) + R1[5] * ( XYZ[1] - XsYsZs1[1] ) + R1[8] * ( XYZ[2] - XsYsZs1[2] );
//        DOUBLE dZCoef2 = R2[2] * ( XYZ[0] - XsYsZs2[0] ) + R2[5] * ( XYZ[1] - XsYsZs2[1] ) + R2[8] * ( XYZ[2] - XsYsZs2[2] );
//
//        dTempVal = -1 / dZCoef1 * ( R1[0] * f1x + R1[2] * x1 );
//        matA.SetAt( 0, 0, dTempVal );
//
//        dTempVal = -1 / dZCoef1 * ( R1[3] * f1x + R1[5] * x1 );
//        matA.SetAt( 0, 1, dTempVal );
//
//        dTempVal = -1 / dZCoef1 * ( R1[6] * f1x + R1[8] * x1 );
//        matA.SetAt( 0, 2, dTempVal );
//
//        dTempVal = -1 / dZCoef1 * ( R1[1] * f1y + R1[2] * y1 );
//        matA.SetAt( 1, 0, dTempVal );
//
//        dTempVal = -1 / dZCoef1 * ( R1[4] * f1y + R1[5] * y1 );
//        matA.SetAt( 1, 1, dTempVal );
//
//        dTempVal = -1 / dZCoef1 * ( R1[7] * f1y + R1[8] * y1 );
//        matA.SetAt( 1, 2, dTempVal );
//
//        dTempVal = -1 / dZCoef2 * ( R2[0] * f2x + R2[2] * x2 );
//        matA.SetAt( 2, 0, dTempVal );
//
//        dTempVal = -1 / dZCoef2 * ( R2[3] * f2x + R2[5] * x2 );
//        matA.SetAt( 2, 1, dTempVal );
//
//        dTempVal = -1 / dZCoef2 * ( R2[6] * f2x + R2[8] * x2 );
//        matA.SetAt( 2, 2, dTempVal );
//
//        dTempVal = -1 / dZCoef2 * ( R2[1] * f2y + R2[2] * y2 );
//        matA.SetAt( 3, 0, dTempVal );
//
//        dTempVal = -1 / dZCoef2 * ( R2[4] * f2y + R2[5] * y2 );
//        matA.SetAt( 3, 1, dTempVal );
//
//        dTempVal = -1 / dZCoef2 * ( R2[7] * f2y + R2[8] * y2 );
//        matA.SetAt( 3, 2, dTempVal );
//
//        DOUBLE dTempx, dTempy;
//        getxyFromXYZ( dTempx, dTempy, XYZ[0], XYZ[1], XYZ[2], XsYsZs1, R1, f1x, f1y );
//        matB.SetAt( 0, 0, ( x1 - dTempx ) );
//        matB.SetAt( 1, 0, ( y1 - dTempy ) );
//
//        getxyFromXYZ( dTempx, dTempy, XYZ[0], XYZ[1], XYZ[2], XsYsZs2, R2, f2x, f2y );
//
//        matB.SetAt( 2, 0, ( x2 - dTempx ) );
//        matB.SetAt( 3, 0, ( y2 - dTempy ) );
//
//        mlMatSolveSVD( &matA, &matB, &matX );
//
//        DOUBLE dAlpx = matX.GetAt( 0, 0 );
//        DOUBLE dAlpy = matX.GetAt( 1, 0 );
//        DOUBLE dAlpz = matX.GetAt( 2, 0 );
//
//        XYZ[0] += dAlpx;
//        XYZ[1] += dAlpy;
//        XYZ[2] += dAlpz;
//
//        if( ( dAlpx < dThres )&&( dAlpy < dThres)&&( dAlpz < dThres) )
//        {
//            break;
//        }
//    }
//
//    PtXYZ.X = XYZ[0];
//    PtXYZ.Y = XYZ[1];
//    PtXYZ.Z = XYZ[2];
//
//    return true;
    Pt2d ptLxyAccu, ptRxyAccu;
    Pt3d ptXYZAccu;
    return this->mlInterSection( dLx, dLy, dRx, dRy, pMatL, pMatR, PtXsYsZsL, PtXsYsZsR, f1, f2, PtXYZ, ptLxyAccu, ptRxyAccu, ptXYZAccu, dThres );
}
bool CmlStereoProc::mlInterSection( DOUBLE dLx, DOUBLE dLy, DOUBLE dRx, DOUBLE dRy, CmlMat* pMatL, CmlMat* pMatR, Pt3d PtXsYsZsL, Pt3d PtXsYsZsR, DOUBLE f1, DOUBLE f2, \
                         Pt3d &ptXYZ, Pt2d &ptLxyAccu, Pt2d &ptRxyAccu, Pt3d &ptXYZAccu, DOUBLE dThres )
{
    if( ( pMatL == NULL )||(  pMatL->IsValid() == false )||( pMatR == NULL)||(  pMatR->IsValid() == false ) )
    {
        return false;
    }
    DOUBLE f1x, f1y, f2x, f2y;
    f1x = f1y = f1;
    f2x = f2y = f2;

    DOUBLE x1, y1, x2, y2;
    x1 = dLx;
    y1 = dLy;
    x2 = dRx;
    y2 = dRy;

    DOUBLE R1[9], R2[9];
    memcpy( R1, pMatL->GetData(), sizeof(DOUBLE)*9 );
    memcpy( R2, pMatR->GetData(), sizeof(DOUBLE)*9 );

    DOUBLE XYZ[3], XsYsZs1[3], XsYsZs2[3];
    XsYsZs1[0] = PtXsYsZsL.X;
    XsYsZs1[1] = PtXsYsZsL.Y;
    XsYsZs1[2] = PtXsYsZsL.Z;

    XsYsZs2[0] = PtXsYsZsR.X;
    XsYsZs2[1] = PtXsYsZsR.Y;
    XsYsZs2[2] = PtXsYsZsR.Z;

    CmlMat matA;
    if( false == matA.Initial( 4, 3 ) )
    {
        return false;
    }

    matA.SetAt( 0, 0, f1x * R1[0] + x1 * R1[2] );
    matA.SetAt( 0, 1, f1x * R1[3] + x1 * R1[5] );
    matA.SetAt( 0, 2, f1x * R1[6] + x1 * R1[8] );

    matA.SetAt( 1, 0, f1y * R1[1] + y1 * R1[2] );
    matA.SetAt( 1, 1, f1y * R1[4] + y1 * R1[5] );
    matA.SetAt( 1, 2, f1y * R1[7] + y1 * R1[8] );

    matA.SetAt( 2, 0, f2x * R2[0] + x2 * R2[2] );
    matA.SetAt( 2, 1, f2x * R2[3] + x2 * R2[5] );
    matA.SetAt( 2, 2, f2x * R2[6] + x2 * R2[8] );

    matA.SetAt( 3, 0, f2y * R2[1] + y2 * R2[2] );
    matA.SetAt( 3, 1, f2y * R2[4] + y2 * R2[5] );
    matA.SetAt( 3, 2, f2y * R2[7] + y2 * R2[8] );

    CmlMat matB;
    matB.Initial( 4, 1 );

    DOUBLE dTempVal = 0;
    dTempVal = f1x * R1[0] * XsYsZs1[0] + f1x * R1[3] * XsYsZs1[1] + f1x * R1[6] * XsYsZs1[2] +
               x1 * R1[2] * XsYsZs1[0] + x1 * R1[5] * XsYsZs1[1] + x1 * R1[8] * XsYsZs1[2];
    matB.SetAt( 0, 0, dTempVal );


    dTempVal = f1y * R1[1] * XsYsZs1[0] + f1y * R1[4] * XsYsZs1[1] + f1y * R1[7] * XsYsZs1[2] +
               y1 * R1[2] * XsYsZs1[0] + y1 * R1[5] * XsYsZs1[1] + y1 * R1[8] * XsYsZs1[2];
    matB.SetAt( 1, 0, dTempVal );


    dTempVal = f2x * R2[0] * XsYsZs2[0] + f2x * R2[3] * XsYsZs2[1] + f2x * R2[6] * XsYsZs2[2] +
               x2 * R2[2] * XsYsZs2[0] + x2 * R2[5] * XsYsZs2[1] + x2 * R2[8] * XsYsZs2[2];
    matB.SetAt( 2, 0, dTempVal );

    dTempVal = f2y * R2[1] * XsYsZs2[0] + f2y * R2[4] * XsYsZs2[1] + f2y * R2[7] * XsYsZs2[2] +
               y2 * R2[2] * XsYsZs2[0] + y2 * R2[5] * XsYsZs2[1] + y2 * R2[8] * XsYsZs2[2];
    matB.SetAt( 3, 0, dTempVal );

    CmlMat matX;

    mlMatSolveSVD( &matA, &matB, &matX );

    XYZ[0] = matX.GetAt( 0, 0 );
    XYZ[1] = matX.GetAt( 1, 0 );
    XYZ[2] = matX.GetAt( 2, 0 );

    //////////////////////////////////////////////////////////////////////////
    Pt3d ptPixelL, ptPixelR;
    ptPixelL.X = R1[0]*x1+R1[1]*y1+R1[2]*(-1.0*f1);
    ptPixelL.Y = R1[3]*x1+R1[4]*y1+R1[5]*(-1.0*f1);
    ptPixelL.Z = R1[6]*x1+R1[7]*y1+R1[8]*(-1.0*f1);

    Pt3d pt3dL, pt3dR;
    pt3dL.X = XYZ[0] - XsYsZs1[0];
    pt3dL.Y = XYZ[1] - XsYsZs1[1];
    pt3dL.Z = XYZ[2] - XsYsZs1[2];

    DOUBLE dTempMod = ptPixelL.X * pt3dL.X + ptPixelL.Y * pt3dL.Y + ptPixelL.Z * pt3dL.Z;
    if( dTempMod < 0 )
    {
        return false;
    }

    ptPixelR.X = R2[0]*x2+R2[1]*y2+R2[2]*(-1.0*f2);
    ptPixelR.Y = R2[3]*x2+R2[4]*y2+R2[5]*(-1.0*f2);
    ptPixelR.Z = R2[6]*x2+R2[7]*y2+R2[8]*(-1.0*f2);

    pt3dR.X = XYZ[0] - XsYsZs2[0];
    pt3dR.Y = XYZ[1] - XsYsZs2[1];
    pt3dR.Z = XYZ[2] - XsYsZs2[2];

    dTempMod = ptPixelR.X * pt3dR.X + ptPixelR.Y * pt3dR.Y + ptPixelR.Z * pt3dR.Z;
    if( dTempMod < 0 )
    {
        return false;
    }
    //////////////////////////////////////////////////////////////////////////

    for ( UINT i = 0; i < 10; ++i )
    {

        DOUBLE dZCoef1 = R1[2] * ( XYZ[0] - XsYsZs1[0] ) + R1[5] * ( XYZ[1] - XsYsZs1[1] ) + R1[8] * ( XYZ[2] - XsYsZs1[2] );
        DOUBLE dZCoef2 = R2[2] * ( XYZ[0] - XsYsZs2[0] ) + R2[5] * ( XYZ[1] - XsYsZs2[1] ) + R2[8] * ( XYZ[2] - XsYsZs2[2] );

        dTempVal = -1 / dZCoef1 * ( R1[0] * f1x + R1[2] * x1 );
        matA.SetAt( 0, 0, dTempVal );

        dTempVal = -1 / dZCoef1 * ( R1[3] * f1x + R1[5] * x1 );
        matA.SetAt( 0, 1, dTempVal );

        dTempVal = -1 / dZCoef1 * ( R1[6] * f1x + R1[8] * x1 );
        matA.SetAt( 0, 2, dTempVal );

        dTempVal = -1 / dZCoef1 * ( R1[1] * f1y + R1[2] * y1 );
        matA.SetAt( 1, 0, dTempVal );

        dTempVal = -1 / dZCoef1 * ( R1[4] * f1y + R1[5] * y1 );
        matA.SetAt( 1, 1, dTempVal );

        dTempVal = -1 / dZCoef1 * ( R1[7] * f1y + R1[8] * y1 );
        matA.SetAt( 1, 2, dTempVal );

        dTempVal = -1 / dZCoef2 * ( R2[0] * f2x + R2[2] * x2 );
        matA.SetAt( 2, 0, dTempVal );

        dTempVal = -1 / dZCoef2 * ( R2[3] * f2x + R2[5] * x2 );
        matA.SetAt( 2, 1, dTempVal );

        dTempVal = -1 / dZCoef2 * ( R2[6] * f2x + R2[8] * x2 );
        matA.SetAt( 2, 2, dTempVal );

        dTempVal = -1 / dZCoef2 * ( R2[1] * f2y + R2[2] * y2 );
        matA.SetAt( 3, 0, dTempVal );

        dTempVal = -1 / dZCoef2 * ( R2[4] * f2y + R2[5] * y2 );
        matA.SetAt( 3, 1, dTempVal );

        dTempVal = -1 / dZCoef2 * ( R2[7] * f2y + R2[8] * y2 );
        matA.SetAt( 3, 2, dTempVal );

        DOUBLE dTempx, dTempy;
        getxyFromXYZ( dTempx, dTempy, XYZ[0], XYZ[1], XYZ[2], XsYsZs1, R1, f1x, f1y );
        matB.SetAt( 0, 0, ( x1 - dTempx ) );
        matB.SetAt( 1, 0, ( y1 - dTempy ) );

        getxyFromXYZ( dTempx, dTempy, XYZ[0], XYZ[1], XYZ[2], XsYsZs2, R2, f2x, f2y );

        matB.SetAt( 2, 0, ( x2 - dTempx ) );
        matB.SetAt( 3, 0, ( y2 - dTempy ) );

        mlMatSolveSVD( &matA, &matB, &matX );

        DOUBLE dAlpx = matX.GetAt( 0, 0 );
        DOUBLE dAlpy = matX.GetAt( 1, 0 );
        DOUBLE dAlpz = matX.GetAt( 2, 0 );

        XYZ[0] += dAlpx;
        XYZ[1] += dAlpy;
        XYZ[2] += dAlpz;

        if( ( dAlpx < dThres )&&( dAlpy < dThres)&&( dAlpz < dThres) )
        {
            break;
        }
    }

    ptXYZ.X = XYZ[0];
    ptXYZ.Y = XYZ[1];
    ptXYZ.Z = XYZ[2];

    Pt2d ptTempL;
    getxyFromXYZ( ptTempL, ptXYZ, PtXsYsZsL, *pMatL, f1, f1 );
    ptLxyAccu.X = abs( dLx - ptTempL.X );
    ptLxyAccu.Y = abs( dLy - ptTempL.Y );

    Pt2d ptTempR;
    getxyFromXYZ( ptTempR, ptXYZ, PtXsYsZsR, *pMatR, f2, f2 );
    ptRxyAccu.X = abs( dRx - ptTempR.X );
    ptRxyAccu.Y = abs( dRy - ptTempR.Y );
    ////////////////////////////
    DOUBLE dUnitAccu = sqrt( ptLxyAccu.X * ptLxyAccu.X + ptLxyAccu.Y * ptLxyAccu.Y + ptRxyAccu.X * ptRxyAccu.X + ptRxyAccu.Y * ptRxyAccu.Y );

    CmlMat matATrans, matATA, matATAInv;
    if( ( false == mlMatTrans( &matA, &matATrans ) ) || ( false == mlMatMul( &matATrans, &matA, &matATA )) || ( false == mlMatInv( &matATA, &matATAInv ) ) )
    {
        return false;
    }
    if( ( matATAInv.GetH() != 3 )||( matATAInv.GetW() != 3 )  )
    {
        return false;
    }
    ptXYZAccu.X = dUnitAccu * sqrt( matATAInv.GetAt( 0, 0 ) );
    ptXYZAccu.Y = dUnitAccu * sqrt( matATAInv.GetAt( 1, 1 ) );
    ptXYZAccu.Z = dUnitAccu * sqrt( matATAInv.GetAt( 2, 2 ) );

    return true;
}
/**
* @fn mlGetEpipolarCoordinate
* @date 2011.11.27
* @author ��һ�� ylliu@irsa.ac.cn
* @brief �������Ӱ��������ڷǺ���Ӱ���ϵ�x,y����
* @param pLOriImg ��Ӱ���
* @param pROriImg ��Ӱ���
* @param pInOriL ��Ӱ���ڷ�λ
* @param pExOriL ��Ӱ���ⷽλ
* @param pInOriR ��Ӱ���ڷ�λ
* @param pExOriR ��Ӱ���ⷽλ
* @param pLEpiCoo ��Ǻ���Ӱ���ϵ�����
* @param pREpiCoo �ҷǺ���Ӱ���ϵ�����
* @param MatRH ����Ӱ����ת����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool mlGetEpipolarCoordinate( CmlRasterBlock *pLOriImg, CmlRasterBlock *pROriImg, InOriPara* pInOriL, ExOriPara* pExOriL, \
                              InOriPara* pInOriR, ExOriPara* pExOriR, CRasterPt2D *pLEpiCoo, CRasterPt2D *pREpiCoo, CmlMat *MatRH )
{
    //������ת����
    CmlMat MatRL, MatRR;
    MatRL.Initial(3,3);
    MatRR.Initial(3,3);
    OriAngle LOriAngle, ROriAngle;
    LOriAngle = pExOriL->ori;
    ROriAngle = pExOriR->ori;

    OPK2RMat( &LOriAngle, &MatRL );
    OPK2RMat( &ROriAngle, &MatRR );

    /*******��������ϵ����ת����************/
    CmlMat X_axis, Zt_axis, Y_axis, Z_axis, MatO;

    /**X�ᣬ���߷���**/
    X_axis.Initial( 3, 1 );
    X_axis.SetAt( 0, 0, pExOriR->pos.X - pExOriL->pos.X );
    X_axis.SetAt( 1, 0, pExOriR->pos.Y - pExOriL->pos.Y );
    X_axis.SetAt( 2, 0, pExOriR->pos.Z - pExOriL->pos.Z );

    /**Zt_axis, ��Ӱ�������ᣨ��Ӱ����ָ�������㣩**/
    MatO.Initial( 3, 1 );
    MatO.SetAt( 0, 0, 0 );
    MatO.SetAt( 1, 0, 0 );
    MatO.SetAt( 2, 0, -1.0*pInOriL->f );
    Zt_axis.Initial( 3, 1 );
    mlMatMul(&MatRL, &MatO, &Zt_axis);
    /**Y�ᣬ��ֱ�ں�������**/
    Y_axis.Initial( 3, 1 );
    mlMatCross3( &X_axis, &Zt_axis, &Y_axis );

    //Z�ᣬ���ֶ�������
    Z_axis.Initial( 3, 1 );
    mlMatCross3( &X_axis, &Y_axis, &Z_axis );

    //����RH,����Ӱ����ת����
    DOUBLE dX, dY, dZ;
    dX = sqrt(X_axis.GetAt(0, 0)*X_axis.GetAt(0, 0)+X_axis.GetAt(1, 0)*X_axis.GetAt(1, 0)+X_axis.GetAt(2, 0)*X_axis.GetAt(2, 0));
    dY = sqrt(Y_axis.GetAt(0, 0)*Y_axis.GetAt(0, 0)+Y_axis.GetAt(1, 0)*Y_axis.GetAt(1, 0)+Y_axis.GetAt(2, 0)*Y_axis.GetAt(2, 0));
    dZ = sqrt(Z_axis.GetAt(0, 0)*Z_axis.GetAt(0, 0)+Z_axis.GetAt(1, 0)*Z_axis.GetAt(1, 0)+Z_axis.GetAt(2, 0)*Z_axis.GetAt(2, 0));
    MatRH->Initial( 3, 3 );
    MatRH->SetAt( 0, 0, X_axis.GetAt( 0, 0 ) / dX );
    MatRH->SetAt( 1, 0, X_axis.GetAt( 1, 0 ) / dX );
    MatRH->SetAt( 2, 0, X_axis.GetAt( 2, 0 ) / dX );
    MatRH->SetAt( 0, 1, Y_axis.GetAt( 0, 0 ) / dY );
    MatRH->SetAt( 1, 1, Y_axis.GetAt( 1, 0 ) / dY );
    MatRH->SetAt( 2, 1, Y_axis.GetAt( 2, 0 ) / dY );
    MatRH->SetAt( 0, 2, Z_axis.GetAt( 0, 0 ) / dZ );
    MatRH->SetAt( 1, 2, Z_axis.GetAt( 1, 0 ) / dZ );
    MatRH->SetAt( 2, 2, Z_axis.GetAt( 2, 0 ) / dZ );

    /**�������inv(RL)*RH,inv(RR)*RH**/
    CmlMat invMatRL,invMatRR,MatRLH, MatRRH;
    mlMatInv( &MatRL, &invMatRL );
    mlMatInv( &MatRR, &invMatRR );
    mlMatMul( &invMatRL, MatRH, &MatRLH );
    mlMatMul( &invMatRR, MatRH, &MatRRH );

    /**�������Ӱ���ϸ�������ԭʼ����Ӱ���ϵ�x��y����**/
    DOUBLE hf, lf, rf;
    //���Һ���Ӱ�񽹾������ԭʼӰ�񽹾�
    hf = lf = pInOriL->f;
    rf = pInOriR->f;
    UINT St,Lt;
    DOUBLE Xt, Yt;
    DOUBLE Xt0,Yt0;
    Xt0 = pLOriImg->GetW()/2 - 0.5;
    Yt0 = pLOriImg->GetH()/2 - 0.5;
    Pt2d tempXY;
    //�洢ͼ���X�кţ�Y�к�
    //������Ƭ
    for( St = 0; St < pLOriImg->GetW(); St++ )
    {
        for( Lt = 0; Lt < pLOriImg->GetH(); Lt++)
        {
            Xt = St - Xt0;
            Yt = Yt0 - Lt;
            tempXY.X = -lf*(MatRLH.GetAt(0,0)*Xt+MatRLH.GetAt(0,1)*Yt-MatRLH.GetAt(0,2)*hf)/(MatRLH.GetAt(2,0)*Xt+MatRLH.GetAt(2,1)*Yt-MatRLH.GetAt(2,2)*hf);
            tempXY.Y = -lf*(MatRLH.GetAt(1,0)*Xt+MatRLH.GetAt(1,1)*Yt-MatRLH.GetAt(1,2)*hf)/(MatRLH.GetAt(2,0)*Xt+MatRLH.GetAt(2,1)*Yt-MatRLH.GetAt(2,2)*hf);
            tempXY.X = tempXY.X + pInOriL->x;
            tempXY.Y = pInOriL->y - tempXY.Y;
            pLEpiCoo->SetAt( Lt, St, tempXY );
        }
    }
    //������Ƭ
    for( St = 0; St < pROriImg->GetW(); St++ )
    {
        for( Lt = 0; Lt < pROriImg->GetH(); Lt++)
        {
            Xt = St - Xt0;
            Yt = Yt0 - Lt;
            tempXY.X = -rf*(MatRRH.GetAt(0,0)*Xt+MatRRH.GetAt(0,1)*Yt-MatRRH.GetAt(0,2)*hf)/(MatRRH.GetAt(2,0)*Xt+MatRRH.GetAt(2,1)*Yt-MatRRH.GetAt(2,2)*hf);
            tempXY.Y = -rf*(MatRRH.GetAt(1,0)*Xt+MatRRH.GetAt(1,1)*Yt-MatRRH.GetAt(1,2)*hf)/(MatRRH.GetAt(2,0)*Xt+MatRRH.GetAt(2,1)*Yt-MatRRH.GetAt(2,2)*hf);
            tempXY.X = tempXY.X + pInOriR->x;
            tempXY.Y = pInOriR->y - tempXY.Y;
            pREpiCoo->SetAt( Lt, St, tempXY );
        }
    }
    return true;
}
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
bool CmlStereoProc::mlGetEpipolarImg( CmlRasterBlock *pLOriImg, CmlRasterBlock *pROriImg, InOriPara* pInOriL, ExOriPara* pExOriL, \
                                      InOriPara* pInOriR, ExOriPara* pExOriR, CmlRasterBlock *pLEpiImg, CmlRasterBlock *pREpiImg )
{
    //���ȼ������Ӱ���ϵĸ�������ԭʼӰ���ϵ����꣨���������꣩
    CRasterPt2D LEpiCoo, REpiCoo;
    CmlMat MatRH;
    LEpiCoo.Initial( pLOriImg->GetH(), pLOriImg->GetW() );
    REpiCoo.Initial( pROriImg->GetH(), pROriImg->GetW() );
    bool H1, H2, H3;
    H1 = mlGetEpipolarCoordinate( pLOriImg, pROriImg, pInOriL, pExOriL, pInOriR, pExOriR, &LEpiCoo, &REpiCoo, &MatRH );

    //�洢����Ӱ���ⷽλ��Ԫ��
    OriAngle epiOri;
    RMat2OPK( &MatRH, &epiOri );

    if(H1)
    {
        //�Լ�����ķ���������ֵ���лҶ��ڲ�
        //�õ��������꣬�����Ҷ�ֵ������Ӧ�ĺ���Ӱ�������
        H2 = ((CmlFrameImage*)(m_pDataL))->mlGrayInterpolation( pLOriImg, &LEpiCoo, pLEpiImg, 0 );
        H3 = ((CmlFrameImage*)(m_pDataR))->mlGrayInterpolation( pROriImg, &REpiCoo, pREpiImg, 0 );
        //����Ӱ����Ӱ����Ϊ����Ӱ������
        //����Ӱ��Ļ������ϵ��Ϊ��
        pInOriL->x =  pLOriImg->GetW() / 2.0 - 0.5;
        pInOriL->y =  pLOriImg->GetH() / 2.0 - 0.5;
        pInOriL->k1 = 0;
        pInOriL->k2 = 0;
        pInOriL->k3 = 0;
        pInOriL->p1 = 0;
        pInOriL->p2 = 0;
        pInOriL->alpha = 0;
        pInOriL->beta = 0;

        pInOriR->x = pInOriL->x;
        pInOriR->y = pInOriL->y;
        pInOriR->f = pInOriL->f;
        pInOriR->k1 = 0;
        pInOriR->k2 = 0;
        pInOriR->k3 = 0;
        pInOriR->p1 = 0;
        pInOriR->p2 = 0;
        pInOriR->alpha = 0;
        pInOriR->beta = 0;

        pExOriL->ori = epiOri;
        pExOriR->ori = epiOri;

        return ( H2 && H3 );
    }
    else
    {
        return false;
    }
}
/**
* @fn
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ��������ں���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlStereoProc::mlGetEpipolarImg()
{
    if( ( m_pDataL == NULL ) || ( m_pDataR == NULL ) )
    {
        return false;
    }
    CmlFrameImage* pFImgL = (CmlFrameImage*)m_pDataL;
    CmlFrameImage* pFImgR = (CmlFrameImage*)m_pDataR;
    //��ʼ������Ӱ���С
    CmlRasterBlock ImgL, ImgR;
    ImgL.InitialImg( pFImgL->GetHeight(), pFImgL->GetWidth() );
    ImgR.InitialImg( pFImgR->GetHeight(), pFImgR->GetWidth() );
    //�������Ӱ��
    this->mlGetEpipolarImg( &pFImgL->m_DataBlock, &pFImgR->m_DataBlock, &pFImgL->m_InOriPara, &pFImgL->m_ExOriPara, \
                            &pFImgR->m_InOriPara, &pFImgR->m_ExOriPara, &ImgL, &ImgR );
    memcpy( pFImgL->m_DataBlock.GetData(), ImgL.GetData(), ImgL.GetH()*ImgL.GetW() );
    memcpy( pFImgR->m_DataBlock.GetData(), ImgR.GetData(), ImgR.GetH()*ImgR.GetW() );

    return true;
}
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
SINT CmlStereoProc::mlDisEstimate(vector<Pt3d> &vFeaPtL,UINT nStep,SINT nRadius,vector<Pt2i> &vecPt,vector<Pt2i> &vecDisxy)
{
    //���TIN��ָ�벻Ϊ�գ��������¹�TIN
    UINT nSize = vFeaPtL.size();
    if (nSize<3)
    {
        return 0;
    }
    else
    {
        //���������㹹��������
        CmlTIN FeaTin;
        if( false == FeaTin.Build2By3DPt(vFeaPtL) )
        {
            return 0;
        }

        UINT nTinNum = FeaTin.GetNumOfTriangles();
        bool bCorner;//��ʶ�Ƿ��������ǵ�

        //��ÿ�����������λ�ȡ���������Ӳ�ֵ
        for(UINT k=0; k<nTinNum; ++k)
        {
            Pt3d pCorner[3];
            bCorner = FeaTin.GetCornersByTriIndex(k, pCorner);
            if (bCorner==TRUE)
            {
                //����ÿ��������������б��ֵ����ʼ������,A*B=b
                CmlMat MatA, MatB,Matb, MatATran;
                FLOAT ft1a,ft1b,ft1c;

                if( ( false == MatA.Initial(3,3) )||(false == MatB.Initial(3,1))||( false == Matb.Initial(3,1)) )
                {
                    continue;                }

                MatA.SetAt(0,0,pCorner[0].X);
                MatA.SetAt(1,0,pCorner[1].X);
                MatA.SetAt(2,0,pCorner[2].X);

                MatA.SetAt(0,1,pCorner[0].Y);
                MatA.SetAt(1,1,pCorner[1].Y);
                MatA.SetAt(2,1,pCorner[2].Y);

                MatA.SetAt(0,2,1);
                MatA.SetAt(1,2,1);
                MatA.SetAt(2,2,1);

                Matb.SetAt(0,0,pCorner[0].Z);
                Matb.SetAt(1,0,pCorner[1].Z);
                Matb.SetAt(2,0,pCorner[2].Z);

                //�����������Ӳ�������Сֵ
                SINT dmindis=9999, dmaxdis=-9999;
                for(UINT i=0; i<3; i++)
                {
                    if (pCorner[i].Z>dmaxdis)
                    {
                        dmaxdis = pCorner[i].Z;
                    }
                    if (pCorner[i].Z<dmindis)
                    {
                        dmindis = pCorner[i].Z;
                    }

                }

                if (mlMatInv(&MatA,&MatATran))
                {
                    mlMatMul(&MatATran,&Matb,&MatB);

                    ft1a = MatB.GetAt(0, 0);
                    ft1b = MatB.GetAt(1, 0);
                    ft1c = MatB.GetAt(2, 0);
                }
                else
                {
                    ft1a = 0;
                    ft1b = 0;
                    ft1c = 0;
                }

                float ftrix[3], ftriy[3],ftrix_temp, ftriy_temp;//�������εĽǵ������������
                for(UINT j=0; j<3; ++j)
                {
                    ftrix[j] = pCorner[j].X;
                    ftriy[j] = pCorner[j].Y;
                }
                //��С�����к�����
                for(UINT j=0; j<3; ++j)
                {
                    for(UINT k=0; k<j; ++k)
                    {
                        if(ftrix[k]>ftrix[j])
                        {
                            ftrix_temp = ftrix[j];
                            ftrix[j] = ftrix[k];
                            ftrix[k] = ftrix_temp;
                            ftriy_temp = ftriy[j];
                            ftriy[j] = ftriy[k];
                            ftriy[k] = ftriy_temp;
                        }
                    }
                }
                //���¶���ǵ�
                FLOAT Ax = ftrix[0];
                FLOAT Bx = ftrix[1];
                FLOAT Cx = ftrix[2];
                FLOAT Ay = ftriy[0];
                FLOAT By = ftriy[1];
                FLOAT Cy = ftriy[2];

                //�������������νǵ��ֱ�ߵ�б�ʺͽؾ�
                FLOAT AB_a = 0;
                FLOAT AC_a = 0;
                FLOAT BC_a = 0;
                if((UINT)Ax!=(UINT)Bx)
                    AB_a = (Ay-By)/(Ax-Bx);
                if((UINT)Ax!=(UINT)Cx)
                    AC_a = (Ay-Cy)/(Ax-Cx);
                if((UINT)Bx!=(UINT)Cx)
                    BC_a = (By-Cy)/(Bx-Cx);

                FLOAT AB_b = Ay - AB_a*Ax;
                FLOAT AC_b = Ay - AC_a*Ax;
                FLOAT BC_b = By - BC_a*Bx;

                //�Ե�һ���ּ����ӲΧ��A-B��
                for(UINT nx = Ax; nx<Bx; nx+=nStep)
                {
                    SINT ny1 = (SINT)(AC_a*(FLOAT)nx+AC_b);
                    SINT ny2 = (SINT)(AB_a*(FLOAT)nx+AB_b);
                    for(SINT ny=min(ny1,ny2); ny<max(ny1,ny2); ny+=nStep)
                    {
                        //ȷ�������С�Ӳ������Ӳ�
                        SINT ndisx = (SINT)(ft1a*nx+ft1b*ny+ft1c);
                        Pt2i ptTemp;
                        ptTemp.X = nx;
                        ptTemp.Y = ny;
                        vecPt.push_back(ptTemp);

                        Pt2i disTemp;
                        disTemp.X = max(ndisx-nRadius,dmindis);
                        disTemp.Y = min(ndisx+nRadius,dmaxdis);
                        vecDisxy.push_back(disTemp);
                    }
                }

                //�Եڶ����ּ����ӲΧ��B-C��
                for(UINT nx = Bx; nx<Cx; nx+=nStep)
                {
                    SINT ny1 = (SINT)(AC_a*(FLOAT)nx+AC_b);
                    SINT ny2 = (SINT)(BC_a*(FLOAT)nx+BC_b);
                    for(SINT ny=min(ny1,ny2); ny<max(ny1,ny2); ny+=nStep)
                    {
                        //ȷ�������С�Ӳ������Ӳ�
                        SINT ndisx = (SINT)(ft1a*nx+ft1b*ny+ft1c);
                        Pt2i ptTemp;
                        ptTemp.X = nx;
                        ptTemp.Y = ny;
                        vecPt.push_back(ptTemp);

                        Pt2i disTemp;
                        disTemp.X = max(ndisx-nRadius,dmindis);
                        disTemp.Y = min(ndisx+nRadius,dmaxdis);
                        vecDisxy.push_back(disTemp);
                    }
                }
            }
        }
    }

    return vecDisxy.size();
}

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
bool CmlStereoProc::mlDenseMatch(CmlRasterBlock* pBlockL,  CmlRasterBlock* pBlockR,vector<StereoMatchPt> &vecMatchPt, WideOptions WidePara, \
                                 vector<Pt2d> &vecLPts, vector<Pt2d> &vecRPts )
{
    if(( pBlockL == NULL)||( pBlockR == NULL ) )
    {
        return false;
    }
    if(vecMatchPt.size()== 0 )
    {
        return false;
    }
    if((vecLPts.size() != 0)|| (vecRPts.size()!= 0))
    {
        return false;
    }
    vector<Pt2i> vecPt,  vecDisx, vecDisy;
    vector<Pt3d> vFeaPtLx, vFeaPtLy;
    SINT nTemplateSize = WidePara.nTemplateSize;
    DOUBLE dCoefThres = WidePara.dCoef;
    UINT nXOffSet = WidePara.nXOffSet;
    UINT nYOffSet = WidePara.nYOffSet;
    UINT nStep = WidePara.nStep;
    UINT nRadiusX = WidePara.nRadiusX;
    UINT nRadiusY = WidePara.nRadiusY;

    for(UINT i=0; i < vecMatchPt.size(); i++)
    {
        StereoMatchPt pt1 = vecMatchPt[i];

        Pt3d tempPt1,tempPt2;
        tempPt1.X = SINT (pt1.ptLInImg.X);
        tempPt1.Y = SINT (pt1.ptLInImg.Y);
        tempPt1.Z = SINT (-pt1.ptLInImg.X+pt1.ptRInImg.X);
        vFeaPtLx.push_back(tempPt1);

        tempPt2.X = SINT (pt1.ptLInImg.X);
        tempPt2.Y = SINT (pt1.ptLInImg.Y);
        tempPt2.Z = SINT (-pt1.ptLInImg.Y+pt1.ptRInImg.Y);
        vFeaPtLy.push_back(tempPt2);
    }


    //����������������������(x,y,���Ӳ�)�����������������ӲΧvecDisx
    SINT nSize1;
    nSize1 = mlDisEstimate(vFeaPtLx, nStep, nRadiusX,vecPt,vecDisx);
    //����������������������(x,y,���Ӳ�)�����������������ӲΧvecDisy
    SINT nSize2;
    nSize2 = mlDisEstimate(vFeaPtLy, nStep, nRadiusY,vecPt,vecDisy);

    SINT nCount = vecDisx.size();
    DOUBLE dcoef, dLX, dLY, dRX, dRY;
    Pt2d temPt2d;
    for(SINT i=0; i<nCount; i++)
    {
        SINT nXmin = vecDisx[i].X;
        SINT nXmax = vecDisx[i].Y;
        SINT nYmin = vecDisy[i].X;
        SINT nYmax = vecDisy[i].Y;
        Pt2i temPtL;
        Pt2i temPtR;
        temPtL.X = vecPt[i].X;
        temPtL.Y = vecPt[i].Y;

        bool bmark;
        bmark = mlTemplateMatchInRegion(pBlockL, pBlockR,temPtL,temPtR, dcoef, nXmin,nXmax,nYmin,nYmax,nTemplateSize, dCoefThres,nXOffSet,nYOffSet);
        if(true == bmark)
        {

            dLX = temPtL.X;
            dLY = temPtL.Y;
            dRX = temPtR.X;
            dRY = temPtR.Y;
            temPt2d.X = dLX;
            temPt2d.Y = dLY;
            vecLPts.push_back(temPt2d);
//           temPt2d.X = dRX;
//           temPt2d.Y = dRY;
//           vecRPts.push_back(temPt2d);
            this->mlLsMatch(pBlockL, pBlockR, dLX, dLY, dRX, dRY, nTemplateSize, dcoef );
            temPt2d.X = dRX;
            temPt2d.Y = dRY;
            vecRPts.push_back(temPt2d);
        }

    }
    if( ( vecLPts.size() == 0 )||(( vecRPts.size() == 0 )) )
    {
        return false;
    }

    return true;
}

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
   * @param vecCorr �ܼ�ƥ������ϵ��ֵ
   * @retval TRUE �ɹ�
   * @retval FALSE ʧ��
   * @version 1.0
   * @par �޸���ʷ��
   * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
   */
bool  CmlStereoProc::mlDenseMatch(CmlRasterBlock* pBlockL,  CmlRasterBlock* pBlockR,vector<StereoMatchPt> &vecMatchPt, WideOptions WidePara, \
                                  MLRect rectMatch, vector<Pt2d> &vecLPts,  vector<Pt2d> &vecRPts, vector<DOUBLE> &vecCorr, bool bIsRemoveAbPixel)
{
    if(( pBlockL == NULL)||( pBlockR == NULL ) )
    {
        return false;
    }
    if(vecMatchPt.size()== 0 )
    {
        return false;
    }
    if((vecLPts.size() != 0)|| (vecRPts.size()!= 0))
    {
        return false;
    }
    vector<Pt2i> vecPt,  vecDisx, vecDisy;
    vector<Pt3d> vFeaPtLx, vFeaPtLy;
    SINT nTemplateSize = WidePara.nTemplateSize;
    DOUBLE dCoefThres = WidePara.dCoef;
    UINT nXOffSet = WidePara.nXOffSet;
    UINT nYOffSet = WidePara.nYOffSet;
    UINT nStep = WidePara.nStep;
    UINT nRadiusX = WidePara.nRadiusX;
    UINT nRadiusY = WidePara.nRadiusY;

    for(UINT i=0; i < vecMatchPt.size(); i++)
    {
        StereoMatchPt pt1 = vecMatchPt[i];

        Pt3d tempPt1,tempPt2;
        tempPt1.X = SINT (pt1.ptLInImg.X);
        tempPt1.Y = SINT (pt1.ptLInImg.Y);
        tempPt1.Z = SINT (-pt1.ptLInImg.X+pt1.ptRInImg.X);
        vFeaPtLx.push_back(tempPt1);

        tempPt2.X = SINT (pt1.ptLInImg.X);
        tempPt2.Y = SINT (pt1.ptLInImg.Y);
        tempPt2.Z = SINT (-pt1.ptLInImg.Y+pt1.ptRInImg.Y);
        vFeaPtLy.push_back(tempPt2);
    }


    //����������������������(x,y,���Ӳ�)�����������������ӲΧvecDisx
    SINT nSize1;
    nSize1 = mlDisEstimate(vFeaPtLx, nStep, nRadiusX,vecPt,vecDisx);
    //����������������������(x,y,���Ӳ�)�����������������ӲΧvecDisy
    SINT nSize2;
    nSize2 = mlDisEstimate(vFeaPtLy, nStep, nRadiusY,vecPt,vecDisy);

    UINT nCount = vecDisx.size();
    DOUBLE dcoef, dLX, dLY, dRX, dRY;

    Pt2d temPt2d;
    for(UINT i=0; i<nCount; i++)
    {
        Pt2i temPtL;
        Pt2i temPtR;
        temPtL.X = vecPt[i].X;
        temPtL.Y = vecPt[i].Y;

        SINT nXmin = vecDisx[i].X;
        SINT nXmax = vecDisx[i].Y;
        SINT nYmin = vecDisy[i].X;
        SINT nYmax = vecDisy[i].Y;

        if(PtInRect(temPtL, rectMatch)== true)
        {
            bool bmark;
            bmark = mlTemplateMatchInRegion(pBlockL, pBlockR,temPtL,temPtR, dcoef, nXmin,nXmax,nYmin,nYmax,nTemplateSize, dCoefThres,nXOffSet,nYOffSet, bIsRemoveAbPixel );
            if(true == bmark)
            {

                dLX = temPtL.X;
                dLY = temPtL.Y;
                dRX = temPtR.X;
                dRY = temPtR.Y;
                temPt2d.X = dLX;
                temPt2d.Y = dLY;
                vecLPts.push_back(temPt2d);

                this->mlLsMatch(pBlockL, pBlockR, dLX, dLY, dRX, dRY, nTemplateSize, dcoef );
                temPt2d.X = dRX;
                temPt2d.Y = dRY;
                vecRPts.push_back(temPt2d);
                vecCorr.push_back(dcoef);
            }
        }
    }

    if( ( vecLPts.size() == 0 )||(( vecRPts.size() == 0 )) )
    {
        return false;
    }

    return true;
}




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
bool CmlStereoProc::mlUniquePt(vector<StereoMatchPt> &MatchPts)
{
    vector<StereoMatchPt> vecTempSPt( MatchPts);
    UINT nPtSize= MatchPts.size();
    vector<SINT> vecFlag(nPtSize,0);
    for(UINT i=0; i<nPtSize-1; i++)
    {
        for(UINT j=i+1; j<nPtSize; j++)
        {
            if((vecFlag[i]==0)&&(MatchPts.at(i).ptLInImg.X==MatchPts.at(j).ptLInImg.X)&&(MatchPts.at(i).ptLInImg.Y==MatchPts.at(j).ptLInImg.Y))
                vecFlag[i]=1;
        }

    }


    MatchPts.clear();
    for( UINT i = 0; i < nPtSize; ++i )
    {
        if( vecFlag[i] == 0 )
        {
            MatchPts.push_back( vecTempSPt[i] );
        }
    }
    return true;
}
/**
* @fn
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ά��
* @param strPath �ļ�·��
* @param vecPt3d ��ά��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

//bool CmlStereoProc::ReadFeatMatchPts( string strPath, vector<Pt3d> &vecPt3d )
//{
//    SINT nStrPos = strPath.rfind(".");
//
//    string sTempPath;
//    sTempPath.assign(strPath, nStrPos, strPath.length() );
//    if( 0 != strcmp( sTempPath.c_str(), ".fmf" ) )
//    {
//        return false;
//    }
//    FILE* pF = NULL;
//    pF = fopen( strPath.c_str(), "r" );
//    if( pF != NULL )
//    {
//        char cHead[128];
//        fscanf( pF, "%s\n", cHead );
//        if( 0 != strcmp( cHead, "ML_FEATURE_MATCHING_POINT_FILE" ) )
//        {
//            return false;
//        }
//        DOUBLE dVersion;
//        fscanf( pF, "%lf\n", &dVersion );
//
//        SINT nPtNum;
//        fscanf( pF, "%d\n", &nPtNum );
//
//        for( SINT i = 0; i < nPtNum; ++i )
//        {
//            char strID[20];
//            Pt3d ptTemp;
//            DOUBLE dLx, dLy, dRx, dRy;
//            if( EOF != fscanf( pF, "%s %lf %lf %lf %lf %lf %lf %lf\n", strID, &dLx, &dLy, &dRx, &dRy, &ptTemp.X, &ptTemp.Y, &ptTemp.Z ) )
//            {
//                vecPt3d.push_back( ptTemp );
//            }
//            else
//            {
//                break;
//            }
//        }
//        fclose(pF);
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
///**
//* @fn
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief ������ƥ���
//* @param strPath �ļ�·��
//* @param vecStereoPt ����ƥ���
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @version 1.0
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//bool CmlStereoProc::ReadFeatMatchPts( string strPath, vector<StereoMatchPt> &vecStereoPt )
//{
//    SINT nStrPos = strPath.rfind(".");
//
//    string sTempPath;
//    sTempPath.assign(strPath, nStrPos, strPath.length() );
//    if( 0 != strcmp( sTempPath.c_str(), ".fmf" ) )
//    {
//        return false;
//    }
//    FILE* pF = NULL;
//    pF = fopen( strPath.c_str(), "r" );
//    if( pF != NULL )
//    {
//        char cHead[128];
//        fscanf( pF, "%s\n", cHead );
//        if( 0 != strcmp( cHead, "ML_FEATURE_MATCHING_POINT_FILE" ) )
//        {
//            return false;
//        }
//        DOUBLE dVersion;
//        fscanf( pF, "%lf\n", &dVersion );
//
//        SINT nPtNum;
//        fscanf( pF, "%d\n", &nPtNum );
//
//        for( SINT i = 0; i < nPtNum; ++i )
//        {
//            char strID[20];
//            StereoMatchPt ptTemp;
//            if( EOF != fscanf( pF, "%s %lf %lf %lf %lf %lf %lf %lf\n", strID, &ptTemp.ptLInImg.X, &ptTemp.ptLInImg.Y, &ptTemp.ptRInImg.X, &ptTemp.ptRInImg.Y, &ptTemp.X, &ptTemp.Y, &ptTemp.Z ) )
//            {
//                vecStereoPt.push_back( ptTemp );
//            }
//            else
//            {
//                break;
//            }
//        }
//        fclose(pF);
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
///**
//* @fn
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief ������ƥ���
//* @param strLPath ���ļ�·��
//* @param strRPath ���ļ�·��
//* @param vecStereoPt ����ƥ���
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @version 1.0
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//bool CmlStereoProc::ReadFeatMatchPts( string strLPath, string strRPath, vector<Pt3d> &vecStereoPt )
//{
//    vector<StereoMatchPt> vecMPt;
//    if( true == ReadFeatMatchPts( strLPath, strRPath, vecMPt ) )
//    {
//        for( UINT i = 0; i < vecMPt.size(); ++i )
//        {
//            StereoMatchPt ptStereo = vecMPt[i];
//            Pt3d pt;
//            pt.X = ptStereo.X;
//            pt.Y = ptStereo.Y;
//            pt.Z = ptStereo.Z;
//            vecStereoPt.push_back( pt );
//        }
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
///**
//* @fn
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief ������ƥ���
//* @param strLPath ���ļ�·��
//* @param strRPath ���ļ�·��
//* @param vecStereoPt ����ƥ���
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @version 1.0
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//bool CmlStereoProc::ReadFeatMatchPts( string strLPath, string strRPath, vector<StereoMatchPt> &vecStereoPt )
//{
//
//    SINT nStrLPos = strLPath.rfind(".");
//    SINT nStrRPos = strRPath.rfind(".");
//
//    string sTempLPath;
//    string sTempRPath;
//    sTempLPath.assign(strLPath, nStrLPos, strLPath.length() );
//    sTempRPath.assign(strRPath, nStrRPos, strRPath.length() );
//    if( ( 0 != strcmp( sTempLPath.c_str(), ".fmf" ))||( 0 != strcmp( sTempRPath.c_str(), ".fmf" ) ) )
//    {
//        return false;
//    }
//
//    FILE* pLF = NULL;
//    FILE* pRF = NULL;
//    pLF = fopen( strLPath.c_str(), "r" );
//    pRF = fopen( strRPath.c_str(), "r" );
//    if( ( pLF != NULL )&&( pRF != NULL ) )
//    {
//        char cLHead[128], cRHead[128];
//        fscanf( pLF, "%s\n", cLHead );
//        fscanf( pRF, "%s\n", cRHead );
//        if( ( 0 != strcmp( cLHead, "ML_FEATURE_MATCHING_POINT_FILE" ) )||( 0 != strcmp( cRHead, "ML_FEATURE_MATCHING_POINT_FILE" ) ))
//        {
//            return false;
//        }
//
//        DOUBLE dLVersion, dRVersion;
//        fscanf( pLF, "%lf\n", &dLVersion );
//        fscanf( pRF, "%lf\n", &dRVersion );
//
//        StereoSet tmpSSet;
//
//
//        ExOriPara *pTmpLExOri = &tmpSSet.imgLInfo.exOri;
//        fscanf( pLF, "%lf %lf %lf %lf %lf %lf\n", &pTmpLExOri->pos.X, &pTmpLExOri->pos.Y, &pTmpLExOri->pos.Z, &pTmpLExOri->ori.omg, &pTmpLExOri->ori.phi, &pTmpLExOri->ori.kap );
//        ExOriPara *pTmpRExOri = &tmpSSet.imgRInfo.exOri;
//        fscanf( pRF, "%lf %lf %lf %lf %lf %lf\n", &pTmpRExOri->pos.X, &pTmpRExOri->pos.Y, &pTmpRExOri->pos.Z, &pTmpRExOri->ori.omg, &pTmpRExOri->ori.phi, &pTmpRExOri->ori.kap );
//
//        fscanf( pLF, "%d %d\n", &tmpSSet.imgLInfo.nW, &tmpSSet.imgLInfo.nH );
//        fscanf( pRF, "%d %d\n", &tmpSSet.imgRInfo.nW, &tmpSSet.imgRInfo.nH );
//
//        InOriPara *pTmpLInOri = &tmpSSet.imgLInfo.inOri;
//        InOriPara *pTmpRInOri = &tmpSSet.imgRInfo.inOri;
//        fscanf( pLF, "%lf %lf %lf\n", &pTmpLInOri->f, &pTmpLInOri->x, &pTmpLInOri->y );
//        fscanf( pRF, "%lf %lf %lf\n", &pTmpRInOri->f, &pTmpRInOri->x, &pTmpRInOri->y );
//
//        fscanf( pLF, "%lf %lf %lf\n", &pTmpLInOri->k1, &pTmpLInOri->k2, &pTmpLInOri->k3 );
//        fscanf( pRF, "%lf %lf %lf\n", &pTmpRInOri->k1, &pTmpRInOri->k2, &pTmpRInOri->k3 );
//
//        fscanf( pLF, "%lf %lf\n", &pTmpLInOri->p1, &pTmpLInOri->p2 );
//        fscanf( pRF, "%lf %lf\n", &pTmpRInOri->p1, &pTmpRInOri->p2 );
//
//        fscanf( pLF, "%lf %lf\n", &pTmpLInOri->alpha, &pTmpLInOri->beta );
//        fscanf( pRF, "%lf %lf\n", &pTmpRInOri->alpha, &pTmpRInOri->beta );
//
//        fscanf( pLF, "%d\n", &tmpSSet.imgLInfo.nImgIndex );
//        fscanf( pRF, "%d\n", &tmpSSet.imgRInfo.nImgIndex );
//
//        SINT nLPtNum, nRPtNum;
//        fscanf( pLF, "%d\n", &nLPtNum );
//        fscanf( pRF, "%d\n", &nRPtNum );
//
//        map<ULONG, Pt2d> mapLImgPt;
//        for( SINT i = 0; i < nLPtNum; ++i )
//        {
//            ULONG nTID;
//            Pt2d ptTemp;
//            SINT nType;
//            fscanf( pLF, "%llu %lf %lf %d\n", &nTID, &ptTemp.X, &ptTemp.Y, &nType );
//            mapLImgPt.insert( map<ULONG, Pt2d> :: value_type( nTID, ptTemp ));
//        }
//
//        for( SINT i = 0; i < nRPtNum; ++i )
//        {
//            ULONG nTID;
//            Pt2d ptTemp;
//            SINT nType;
//            fscanf( pRF, "%llu %lf %lf %d\n", &nTID, &ptTemp.X, &ptTemp.Y, &nType );
//
//            map<ULONG, Pt2d>::iterator it = mapLImgPt.find( nTID );
//            if( it != mapLImgPt.end() )
//            {
//                Pt3d ptXYZ;
//                this->mlInterSection( it->second, ptTemp, tmpSSet.imgLInfo.nH, tmpSSet.imgRInfo.nH, ptXYZ, &tmpSSet.imgLInfo.inOri, &tmpSSet.imgLInfo.exOri,\
//                                            &tmpSSet.imgRInfo.inOri, &tmpSSet.imgRInfo.exOri );
//                StereoMatchPt ptMPt;
//                ptMPt.ptLInImg.X = (it->second).X;
//                ptMPt.ptLInImg.Y = (it->second).Y;
//                ptMPt.ptRInImg.X = ptTemp.X;
//                ptMPt.ptRInImg.Y = ptTemp.Y;
//                ptMPt.X = ptXYZ.X;
//                ptMPt.Y = ptXYZ.Y;
//                ptMPt.Z = ptXYZ.Z;
//                vecStereoPt.push_back( ptMPt );
//            }
//            else
//            {
//                continue;
//            }
//        }
//        fclose(pLF);
//        fclose(pRF);
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
///**
//* @fn
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief ������ƥ���д���ļ�
//* @param strPath �ļ�·��
//* @param vecFeatMatchPt ����ƥ���
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @version 1.0
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//bool CmlStereoProc::WriteFeatMatchPts( string strPath, vector<StereoMatchPt> &vecFeatMatchPt )
//{
//    SINT nStrPos = strPath.rfind(".");
//
//    string sTempPath;
//    sTempPath.assign(strPath, nStrPos, strPath.length() );
//    if( 0 != strcmp( sTempPath.c_str(), ".fmf" ) )
//    {
//        return false;
//    }
//    FILE* pF = NULL;
//    pF = fopen( strPath.c_str(), "w" );
//    if( pF != NULL )
//    {
//        fprintf( pF, "%s\n", "ML_FEATURE_MATCHING_POINT_FILE" );
//
//        DOUBLE dVersion = 1.0;
//        fprintf( pF, "%lf\n", dVersion );
//
//        SINT nPtNum = vecFeatMatchPt.size();
//        fprintf( pF, "%d\n", nPtNum );
//
//        for( SINT i = 0; i < nPtNum; ++i )
//        {
//            StereoMatchPt* ptTemp = &vecFeatMatchPt.at(i);
//            fprintf( pF, "%d %lf %lf %lf %lf %lf %lf %lf\n", i, ptTemp->ptLInImg.X, ptTemp->ptLInImg.Y, ptTemp->ptRInImg.X, ptTemp->ptRInImg.Y, ptTemp->X, ptTemp->Y, ptTemp->Z );
//        }
//        fclose(pF);
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
///**
//* @fn
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief ������ƥ���д���ļ�
//* @param strLPath ���ļ�·��
//* @param strRPath ���ļ�·��
//* @param pStereoSet �������Ӱ����Ϣ
//* @param vecFeatMatchPt ƥ���
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @version 1.0
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//bool CmlStereoProc::WriteFeatMatchPts( string strLPath, string strRPath, StereoSet *pStereoSet, vector<StereoMatchPt> &vecFeatMatchPt )
//{
//    if( pStereoSet == NULL )
//    {
//        return false;
//    }
//
//    SINT nStrLPos = strLPath.rfind(".");
//    SINT nStrRPos = strRPath.rfind(".");
//
//    string sTempLPath;
//    string sTempRPath;
//    sTempLPath.assign(strLPath, nStrLPos, strLPath.length() );
//    sTempRPath.assign(strRPath, nStrRPos, strRPath.length() );
//    if( ( 0 != strcmp( sTempLPath.c_str(), ".fmf" ))||( 0 != strcmp( sTempRPath.c_str(), ".fmf" ) ) )
//    {
//        return false;
//    }
//    FILE* pLF = NULL;
//    FILE* pRF = NULL;
//    pLF = fopen( strLPath.c_str(), "w" );
//    pRF = fopen( strRPath.c_str(), "w" );
//    if( ( pLF != NULL )&&( pRF != NULL ) )
//    {
//        fprintf( pLF, "%s\n", "ML_FEATURE_MATCHING_POINT_FILE" );
//        fprintf( pRF, "%s\n", "ML_FEATURE_MATCHING_POINT_FILE" );
//
//        DOUBLE dVersion = 1.0;
//        fprintf( pLF, "%lf\n", dVersion );
//        fprintf( pRF, "%lf\n", dVersion );
//
//        ExOriPara tmpLExOri = pStereoSet->imgLInfo.exOri;
//        fprintf( pLF, "%lf %lf %lf %lf %lf %lf\n", tmpLExOri.pos.X, tmpLExOri.pos.Y, tmpLExOri.pos.Z, tmpLExOri.ori.omg, tmpLExOri.ori.phi, tmpLExOri.ori.kap );
//        ExOriPara tmpRExOri = pStereoSet->imgRInfo.exOri;
//        fprintf( pRF, "%lf %lf %lf %lf %lf %lf\n", tmpRExOri.pos.X, tmpRExOri.pos.Y, tmpRExOri.pos.Z, tmpRExOri.ori.omg, tmpRExOri.ori.phi, tmpRExOri.ori.kap );
//
//        fprintf( pLF, "%d %d\n", pStereoSet->imgLInfo.nW, pStereoSet->imgLInfo.nH );
//        fprintf( pRF, "%d %d\n", pStereoSet->imgRInfo.nW, pStereoSet->imgRInfo.nH );
//
//        InOriPara tmpLInOri = pStereoSet->imgLInfo.inOri;
//        InOriPara tmpRInOri = pStereoSet->imgRInfo.inOri;
//        fprintf( pLF, "%lf %lf %lf\n", tmpLInOri.f, tmpLInOri.x, tmpLInOri.y );
//        fprintf( pRF, "%lf %lf %lf\n", tmpRInOri.f, tmpRInOri.x, tmpRInOri.y );
//
//        fprintf( pLF, "%lf %lf %lf\n", tmpLInOri.k1, tmpLInOri.k2, tmpLInOri.k3 );
//        fprintf( pRF, "%lf %lf %lf\n", tmpRInOri.k1, tmpRInOri.k2, tmpRInOri.k3 );
//
//        fprintf( pLF, "%lf %lf\n", tmpLInOri.p1, tmpLInOri.p2 );
//        fprintf( pRF, "%lf %lf\n", tmpRInOri.p1, tmpRInOri.p2 );
//
//        fprintf( pLF, "%lf %lf\n", tmpLInOri.alpha, tmpLInOri.beta );
//        fprintf( pRF, "%lf %lf\n", tmpRInOri.alpha, tmpRInOri.beta );
//
//        fprintf( pLF, "%d\n", pStereoSet->imgLInfo.nImgIndex );
//        fprintf( pRF, "%d\n", pStereoSet->imgRInfo.nImgIndex );
//
//        SINT nPtNum = vecFeatMatchPt.size();
//        fprintf( pLF, "%d\n", nPtNum );
//        fprintf( pRF, "%d\n", nPtNum );
//
//        for( SINT i = 0; i < nPtNum; ++i )
//        {
//            StereoMatchPt* ptTemp = &vecFeatMatchPt.at(i);
//            ULONG nTmpID = pStereoSet->imgLInfo.nImgIndex * 10e11 + pStereoSet->imgRInfo.nImgIndex * 10e7 + i + 1;
//
//            fprintf( pLF, "%llu %lf %lf %d\n", nTmpID, ptTemp->ptLInImg.X, ptTemp->ptLInImg.Y, 0 );
//            fprintf( pRF, "%llu %lf %lf %d\n", nTmpID, ptTemp->ptRInImg.X, ptTemp->ptRInImg.Y, 0 );
//        }
//        fclose(pLF);
//        fclose(pRF);
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
///**
//* @fn
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief ��ȡ�ܼ�ƥ���
//* @param strLPath ���ļ�·��
//* @param strRPath ���ļ�·��
//* @param vecStereoPt �ܼ�ƥ���
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @version 1.0
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//bool CmlStereoProc::ReadDenseMatchPts( string strLPath, string strRPath, vector<Pt3d> &vecStereoPt )
//{
//    vector<StereoMatchPt> vecMPt;
//    if( true == ReadDenseMatchPts( strLPath, strRPath, vecMPt ) )
//    {
//        for( UINT i = 0; i < vecMPt.size(); ++i )
//        {
//            Pt3d pt;
//            pt.X = vecStereoPt[i].X;
//            pt.Y = vecStereoPt[i].Y;
//            pt.Z = vecStereoPt[i].Z;
//            vecStereoPt.push_back( pt );
//        }
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
///**
//* @fn
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief ��ȡ�ܼ�ƥ���
//* @param strLPath ���ļ�·��
//* @param strRPath ���ļ�·��
//* @param vecStereoPt �ܼ�ƥ��㼯
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @version 1.0
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//bool CmlStereoProc::ReadDenseMatchPts( string strLPath, string strRPath, vector<StereoMatchPt> &vecStereoPt )
//{
//
//    SINT nStrLPos = strLPath.rfind(".");
//    SINT nStrRPos = strRPath.rfind(".");
//
//    string sTempLPath;
//    string sTempRPath;
//    sTempLPath.assign(strLPath, nStrLPos, strLPath.length() );
//    sTempRPath.assign(strRPath, nStrRPos, strRPath.length() );
//    if( ( 0 != strcmp( sTempLPath.c_str(), ".dmf" ))||( 0 != strcmp( sTempRPath.c_str(), ".dmf" ) ) )
//    {
//        return false;
//    }
//
//    FILE* pLF = NULL;
//    FILE* pRF = NULL;
//    pLF = fopen( strLPath.c_str(), "r" );
//    pRF = fopen( strRPath.c_str(), "r" );
//    if( ( pLF != NULL )&&( pRF != NULL ) )
//    {
//        char cLHead[128], cRHead[128];
//        fscanf( pLF, "%s\n", cLHead );
//        fscanf( pRF, "%s\n", cRHead );
//        if( ( 0 != strcmp( cLHead, "ML_DENSE_MATCHING_POINT_FILE" ) )||( 0 != strcmp( cRHead, "ML_DENSE_MATCHING_POINT_FILE" ) ))
//        {
//            return false;
//        }
//
//        DOUBLE dLVersion, dRVersion;
//        fscanf( pLF, "%lf\n", &dLVersion );
//        fscanf( pRF, "%lf\n", &dRVersion );
//
//        StereoSet tmpSSet;
//
//
//        ExOriPara *pTmpLExOri = &tmpSSet.imgLInfo.exOri;
//        fscanf( pLF, "%lf %lf %lf %lf %lf %lf\n", &pTmpLExOri->pos.X, &pTmpLExOri->pos.Y, &pTmpLExOri->pos.Z, &pTmpLExOri->ori.omg, &pTmpLExOri->ori.phi, &pTmpLExOri->ori.kap );
//        ExOriPara *pTmpRExOri = &tmpSSet.imgRInfo.exOri;
//        fscanf( pRF, "%lf %lf %lf %lf %lf %lf\n", &pTmpRExOri->pos.X, &pTmpRExOri->pos.Y, &pTmpRExOri->pos.Z, &pTmpRExOri->ori.omg, &pTmpRExOri->ori.phi, &pTmpRExOri->ori.kap );
//
//        fscanf( pLF, "%d %d\n", &tmpSSet.imgLInfo.nW, &tmpSSet.imgLInfo.nH );
//        fscanf( pRF, "%d %d\n", &tmpSSet.imgRInfo.nW, &tmpSSet.imgRInfo.nH );
//
//        InOriPara *pTmpLInOri = &tmpSSet.imgLInfo.inOri;
//        InOriPara *pTmpRInOri = &tmpSSet.imgRInfo.inOri;
//        fscanf( pLF, "%lf %lf %lf\n", &pTmpLInOri->f, &pTmpLInOri->x, &pTmpLInOri->y );
//        fscanf( pRF, "%lf %lf %lf\n", &pTmpRInOri->f, &pTmpRInOri->x, &pTmpRInOri->y );
//
//        fscanf( pLF, "%lf %lf %lf\n", &pTmpLInOri->k1, &pTmpLInOri->k2, &pTmpLInOri->k3 );
//        fscanf( pRF, "%lf %lf %lf\n", &pTmpRInOri->k1, &pTmpRInOri->k2, &pTmpRInOri->k3 );
//
//        fscanf( pLF, "%lf %lf\n", &pTmpLInOri->p1, &pTmpLInOri->p2 );
//        fscanf( pRF, "%lf %lf\n", &pTmpRInOri->p1, &pTmpRInOri->p2 );
//
//        fscanf( pLF, "%lf %lf\n", &pTmpLInOri->alpha, &pTmpLInOri->beta );
//        fscanf( pRF, "%lf %lf\n", &pTmpRInOri->alpha, &pTmpRInOri->beta );
//
//        fscanf( pLF, "%d\n", &tmpSSet.imgLInfo.nImgIndex );
//        fscanf( pRF, "%d\n", &tmpSSet.imgRInfo.nImgIndex );
//
//        SINT nLPtNum, nRPtNum;
//        fscanf( pLF, "%d\n", &nLPtNum );
//        fscanf( pRF, "%d\n", &nRPtNum );
//
//        map<ULONG, Pt2d> mapLImgPt;
//        for( SINT i = 0; i < nLPtNum; ++i )
//        {
//            ULONG nTID;
//            Pt2d ptTemp;
//            SINT nType;
//            fscanf( pLF, "%llu %lf %lf %d\n", &nTID, &ptTemp.X, &ptTemp.Y, &nType );
//            mapLImgPt.insert( map<ULONG, Pt2d> :: value_type( nTID, ptTemp ));
//        }
//
//        for( SINT i = 0; i < nRPtNum; ++i )
//        {
//            ULONG nTID;
//            Pt2d ptTemp;
//            SINT nType;
//            fscanf( pRF, "%llu %lf %lf %d\n", &nTID, &ptTemp.X, &ptTemp.Y, &nType );
//
//            map<ULONG, Pt2d>::iterator it = mapLImgPt.find( nTID );
//            if( it != mapLImgPt.end() )
//            {
//                Pt3d ptXYZ;
//                this->mlInterSection( it->second, ptTemp, tmpSSet.imgLInfo.nH, tmpSSet.imgRInfo.nH, ptXYZ, \
//                                           &tmpSSet.imgLInfo.inOri, &tmpSSet.imgLInfo.exOri, &tmpSSet.imgRInfo.inOri, &tmpSSet.imgRInfo.exOri );
//                StereoMatchPt ptMPt;
//                ptMPt.ptLInImg.X = (it->second).X;
//                ptMPt.ptLInImg.Y = (it->second).Y;
//                ptMPt.ptRInImg.X = ptTemp.X;
//                ptMPt.ptRInImg.Y = ptTemp.Y;
//                ptMPt.X = ptXYZ.X;
//                ptMPt.Y = ptXYZ.Y;
//                ptMPt.Z = ptXYZ.Z;
//                vecStereoPt.push_back( ptMPt );
//            }
//            else
//            {
//                continue;
//            }
//        }
//        fclose(pLF);
//        fclose(pRF);
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
///**
//* @fn WriteDenseMatchPts
//* @date 2011.11.02
//* @author ���Ļ� whwan@irsa.ac.cn
//* @brief ��ȡ�ܼ�ƥ���
//* @param strLPath ���ļ�·��
//* @param strRPath ���ļ�·��
//* @param pStereoSet �������Ӱ����Ϣ
//* @param vecFeatMatchPt �ܼ�ƥ���
//* @retval TRUE �ɹ�
//* @retval FALSE ʧ��
//* @version 1.0
//* @par �޸���ʷ��
//* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//*/
//bool CmlStereoProc::WriteDenseMatchPts( string strLPath, string strRPath, StereoSet *pStereoSet, vector<StereoMatchPt> &vecFeatMatchPt )
//{
//    if( pStereoSet == NULL )
//    {
//        return false;
//    }
//
//    SINT nStrLPos = strLPath.rfind(".");
//    SINT nStrRPos = strRPath.rfind(".");
//
//    string sTempLPath;
//    string sTempRPath;
//    sTempLPath.assign(strLPath, nStrLPos, strLPath.length() );
//    sTempRPath.assign(strRPath, nStrRPos, strRPath.length() );
//    if( ( 0 != strcmp( sTempLPath.c_str(), ".dmf" ))||( 0 != strcmp( sTempRPath.c_str(), ".dmf" ) ) )
//    {
//        return false;
//    }
//    FILE* pLF = NULL;
//    FILE* pRF = NULL;
//    pLF = fopen( strLPath.c_str(), "w" );
//    pRF = fopen( strRPath.c_str(), "w" );
//    if( ( pLF != NULL )&&( pRF != NULL ) )
//    {
//        fprintf( pLF, "%s\n", "ML_DENSE_MATCHING_POINT_FILE" );
//        fprintf( pRF, "%s\n", "ML_DENSE_MATCHING_POINT_FILE" );
//
//        DOUBLE dVersion = 1.0;
//        fprintf( pLF, "%lf\n", dVersion );
//        fprintf( pRF, "%lf\n", dVersion );
//
//        ExOriPara tmpLExOri = pStereoSet->imgLInfo.exOri;
//        fprintf( pLF, "%lf %lf %lf %lf %lf %lf\n", tmpLExOri.pos.X, tmpLExOri.pos.Y, tmpLExOri.pos.Z, tmpLExOri.ori.omg, tmpLExOri.ori.phi, tmpLExOri.ori.kap );
//        ExOriPara tmpRExOri = pStereoSet->imgRInfo.exOri;
//        fprintf( pRF, "%lf %lf %lf %lf %lf %lf\n", tmpRExOri.pos.X, tmpRExOri.pos.Y, tmpRExOri.pos.Z, tmpRExOri.ori.omg, tmpRExOri.ori.phi, tmpRExOri.ori.kap );
//
//        fprintf( pLF, "%d %d\n", pStereoSet->imgLInfo.nW, pStereoSet->imgLInfo.nH );
//        fprintf( pRF, "%d %d\n", pStereoSet->imgRInfo.nW, pStereoSet->imgRInfo.nH );
//
//        InOriPara tmpLInOri = pStereoSet->imgLInfo.inOri;
//        InOriPara tmpRInOri = pStereoSet->imgRInfo.inOri;
//        fprintf( pLF, "%lf %lf %lf\n", tmpLInOri.f, tmpLInOri.x, tmpLInOri.y );
//        fprintf( pRF, "%lf %lf %lf\n", tmpRInOri.f, tmpRInOri.x, tmpRInOri.y );
//
//        fprintf( pLF, "%lf %lf %lf\n", tmpLInOri.k1, tmpLInOri.k2, tmpLInOri.k3 );
//        fprintf( pRF, "%lf %lf %lf\n", tmpRInOri.k1, tmpRInOri.k2, tmpRInOri.k3 );
//
//        fprintf( pLF, "%lf %lf\n", tmpLInOri.p1, tmpLInOri.p2 );
//        fprintf( pRF, "%lf %lf\n", tmpRInOri.p1, tmpRInOri.p2 );
//
//        fprintf( pLF, "%lf %lf\n", tmpLInOri.alpha, tmpLInOri.beta );
//        fprintf( pRF, "%lf %lf\n", tmpRInOri.alpha, tmpRInOri.beta );
//
//        fprintf( pLF, "%d\n", pStereoSet->imgLInfo.nImgIndex );
//        fprintf( pRF, "%d\n", pStereoSet->imgRInfo.nImgIndex );
//
//        SINT nPtNum = vecFeatMatchPt.size();
//        fprintf( pLF, "%d\n", nPtNum );
//        fprintf( pRF, "%d\n", nPtNum );
//
//        for( SINT i = 0; i < nPtNum; ++i )
//        {
//            StereoMatchPt* ptTemp = &vecFeatMatchPt.at(i);
//            ULONG nTmpID = pStereoSet->imgLInfo.nImgIndex * 10e11 + pStereoSet->imgRInfo.nImgIndex * 10e7 + i + 1;
//
//            fprintf( pLF, "%llu %lf %lf %d\n", nTmpID, ptTemp->ptLInImg.X, ptTemp->ptLInImg.Y, 0 );
//            fprintf( pRF, "%llu %lf %lf %d\n", nTmpID, ptTemp->ptRInImg.X, ptTemp->ptRInImg.Y, 0 );
//        }
//        fclose(pLF);
//        fclose(pRF);
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//
//bool CmlStereoProc::ReadDmfPts( string strLPath, string strRPath, vector<StereoMatchPt> &vecStereoPt )
//{
//
//    SINT nStrLPos = strLPath.rfind(".");
//    SINT nStrRPos = strRPath.rfind(".");
//
//    string sTempLPath;
//    string sTempRPath;
//    sTempLPath.assign(strLPath, nStrLPos, strLPath.length() );
//    sTempRPath.assign(strRPath, nStrRPos, strRPath.length() );
//    if( ( 0 != strcmp( sTempLPath.c_str(), ".dmf" ))||( 0 != strcmp( sTempRPath.c_str(), ".dmf" ) ) )
//    {
//        return false;
//    }
//
//    FILE* pLF = NULL;
//    FILE* pRF = NULL;
//    pLF = fopen( strLPath.c_str(), "r" );
//    pRF = fopen( strRPath.c_str(), "r" );
//    if( ( pLF != NULL )&&( pRF != NULL ) )
//    {
//        char cLHead[128], cRHead[128];
//        fscanf( pLF, "%s\n", cLHead );
//        fscanf( pRF, "%s\n", cRHead );
//        if( ( 0 != strcmp( cLHead, "ML_DENSE_MATCHING_POINT_FILE" ) )||( 0 != strcmp( cRHead, "ML_DENSE_MATCHING_POINT_FILE" ) ))
//        {
//            return false;
//        }
//
//        DOUBLE dLVersion, dRVersion;
//        fscanf( pLF, "%lf\n", &dLVersion );
//        fscanf( pRF, "%lf\n", &dRVersion );
//
//        StereoSet tmpSSet;
//
//
//        ExOriPara *pTmpLExOri = &tmpSSet.imgLInfo.exOri;
//        fscanf( pLF, "%lf %lf %lf %lf %lf %lf\n", &pTmpLExOri->pos.X, &pTmpLExOri->pos.Y, &pTmpLExOri->pos.Z, &pTmpLExOri->ori.omg, &pTmpLExOri->ori.phi, &pTmpLExOri->ori.kap );
//        ExOriPara *pTmpRExOri = &tmpSSet.imgRInfo.exOri;
//        fscanf( pRF, "%lf %lf %lf %lf %lf %lf\n", &pTmpRExOri->pos.X, &pTmpRExOri->pos.Y, &pTmpRExOri->pos.Z, &pTmpRExOri->ori.omg, &pTmpRExOri->ori.phi, &pTmpRExOri->ori.kap );
//
//        fscanf( pLF, "%d %d\n", &tmpSSet.imgLInfo.nW, &tmpSSet.imgLInfo.nH );
//        fscanf( pRF, "%d %d\n", &tmpSSet.imgRInfo.nW, &tmpSSet.imgRInfo.nH );
//
//        InOriPara *pTmpLInOri = &tmpSSet.imgLInfo.inOri;
//        InOriPara *pTmpRInOri = &tmpSSet.imgRInfo.inOri;
//        fscanf( pLF, "%lf %lf %lf\n", &pTmpLInOri->f, &pTmpLInOri->x, &pTmpLInOri->y );
//        fscanf( pRF, "%lf %lf %lf\n", &pTmpRInOri->f, &pTmpRInOri->x, &pTmpRInOri->y );
//
//        fscanf( pLF, "%lf %lf %lf\n", &pTmpLInOri->k1, &pTmpLInOri->k2, &pTmpLInOri->k3 );
//        fscanf( pRF, "%lf %lf %lf\n", &pTmpRInOri->k1, &pTmpRInOri->k2, &pTmpRInOri->k3 );
//
//        fscanf( pLF, "%lf %lf\n", &pTmpLInOri->p1, &pTmpLInOri->p2 );
//        fscanf( pRF, "%lf %lf\n", &pTmpRInOri->p1, &pTmpRInOri->p2 );
//
//        fscanf( pLF, "%lf %lf\n", &pTmpLInOri->alpha, &pTmpLInOri->beta );
//        fscanf( pRF, "%lf %lf\n", &pTmpRInOri->alpha, &pTmpRInOri->beta );
//
//        fscanf( pLF, "%d\n", &tmpSSet.imgLInfo.nImgIndex );
//        fscanf( pRF, "%d\n", &tmpSSet.imgRInfo.nImgIndex );
//
//        SINT nLPtNum, nRPtNum;
//        fscanf( pLF, "%d\n", &nLPtNum );
//        fscanf( pRF, "%d\n", &nRPtNum );
//
//        map<ULONG, Pt2d> mapLImgPt;
//        for( SINT i = 0; i < nLPtNum; ++i )
//        {
//            ULONG nTID;
//            Pt2d ptTemp;
//            SINT nType;
//            fscanf( pLF, "%llu %lf %lf %d\n", &nTID, &ptTemp.X, &ptTemp.Y, &nType );
//            mapLImgPt.insert( map<ULONG, Pt2d> :: value_type( nTID, ptTemp ));
//        }
//
//        for( SINT i = 0; i < nRPtNum; ++i )
//        {
//            ULONG nTID;
//            Pt2d ptTemp;
//            SINT nType;
//            fscanf( pRF, "%llu %lf %lf %d\n", &nTID, &ptTemp.X, &ptTemp.Y, &nType );
//
//            map<ULONG, Pt2d>::iterator it = mapLImgPt.find( nTID );
//            if( it != mapLImgPt.end() )
//            {
//                StereoMatchPt ptMPt;
//                ptMPt.ptLInImg.X = (it->second).X;
//                ptMPt.ptLInImg.Y = (it->second).Y;
//                ptMPt.ptRInImg.X = ptTemp.X;
//                ptMPt.ptRInImg.Y = ptTemp.Y;
//                vecStereoPt.push_back( ptMPt );
//            }
//            else
//            {
//                continue;
//            }
//        }
//        fclose(pLF);
//        fclose(pRF);
//
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//
//}
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
bool CmlStereoProc::DisparityMap( ImgPtSet& imgPtL, ImgPtSet& imgPtR, char* DisPath)
{
    vector<StereoMatchPt> vecMatchPts;

    //������ƥ����ܼ���ϲ���StereoMatchPt
    CmlPtsManage clsPtsManage;
    clsPtsManage.GetPairPts(imgPtL, imgPtR, vecMatchPts);

    UINT nH=imgPtL.imgInfo.nH;
    UINT nW=imgPtL.imgInfo.nW;
    UINT nCount=vecMatchPts.size();

    Pt2d ptOri;
    ptOri.X=0;
    ptOri.Y=0;

    CmlRasterBlock DisBlock;
    DisBlock.InitialImg(nH, nW, 8);
    DisBlock.SetGDTType( GDT_Float64 );


    for( UINT i = 0; i < DisBlock.GetH(); ++i )
    {
        for( UINT j = 0; j < DisBlock.GetW(); ++j )
        {
            DisBlock.SetDoubleVal( i, j, 0 );
        }
    }

    for( UINT i=0; i<nCount; i++)
    {

        StereoMatchPt ptTemp = vecMatchPts[i];
        UINT nRow=ptTemp.ptLInImg.Y;
        UINT nCol=ptTemp.ptLInImg.X;
        DOUBLE dGray=(-ptTemp.ptRInImg.X+ptTemp.ptLInImg.X);
        DisBlock.SetPtrAt(nRow,nCol,(BYTE*)(&dGray));

    }

    CmlGeoRaster geo;
    geo.CreateGeoFile( DisPath,ptOri,1.0,1.0,nH,nW,1,GDT_Float64,99999);
    geo.SaveBlockToFile(1,0,0,&DisBlock);

    return true;


}

void eraseSamePoints(vector<StereoMatchPt>&dbPts, double dbSigma=1.0)
{
	int nCount=dbPts.size();

	vector<StereoMatchPt> dbDstPts;
	for(int i=0;i<nCount;i++)
	{
		StereoMatchPt pCurrentPt=dbPts[i];
		double dbCurrentLeftX=pCurrentPt.ptLInImg.X;
		double dbCurrentLeftY=pCurrentPt.ptLInImg.Y;
		double dbCurrentRightX=pCurrentPt.ptRInImg.X;
		double dbCurrentRightY=pCurrentPt.ptRInImg.Y;

		if(dbDstPts.size()==0)
		{
			dbDstPts.push_back(pCurrentPt);
			continue;
		}

		bool bFlag=false;
		for(int j=0;j<dbDstPts.size();j++)
		{
			StereoMatchPt ptTmpPt=dbDstPts[j];
			double dbTmpLeftX=ptTmpPt.ptLInImg.X;//dbDstPts[4*j+0];
			double dbTmpLeftY=ptTmpPt.ptLInImg.Y;//dbDstPts[4*j+1];
			double dbTmpRightX=ptTmpPt.ptRInImg.X;//dbDstPts[4*j+2];
			double dbTmpRightY=ptTmpPt.ptRInImg.Y;//dbDstPts[4*j+3];

			double dbLeftDeltaX=dbCurrentLeftX-dbTmpLeftX;
			double dbLeftDeltaY=dbCurrentLeftY-dbTmpLeftY;
			double dbRightDeltaX=dbCurrentRightX-dbTmpRightX;
			double dbRightDeltaY=dbCurrentRightY-dbTmpRightY;

			double dbLeftLength=sqrt(dbLeftDeltaX*dbLeftDeltaX+dbLeftDeltaY*dbLeftDeltaY);
			double dbRightLength=sqrt(dbRightDeltaX*dbRightDeltaX+dbRightDeltaY*dbRightDeltaY);

			if(dbLeftLength<=dbSigma && dbRightLength<=dbSigma)
			{
				bFlag=true;//dbDstPts.push_back(pCurrentPt);
				break;
			}
		}

		if(!bFlag)
		{
			dbDstPts.push_back(pCurrentPt);
		}
	}

	dbPts.clear();
	dbPts=dbDstPts;

	////////
	//FILE* pFile=fopen("D://c.txt", "wt");
	//if(!pFile)return;

	//int nPtSize=dbDstPts.size();
	//for(int i=0;i<nPtSize;i++)
	//{
	//	StereoMatchPt pt=dbDstPts[i];
	//	fprintf(pFile, "%f\t%f\t%f\t%f\t\n", pt.ptLInImg.X, pt.ptLInImg.Y, pt.ptRInImg.X, pt.ptRInImg.Y);
	//}

	//fclose(pFile);
	////
	return;
}

/**
* @fn Match2LargeImg
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Ŵ�Ӱ����ƥ��
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
bool CmlStereoProc::Match2LargeImg( const SCHAR* strL, const SCHAR* strR, vector<StereoMatchPt> &vecMatchPts, SiftMatchPara stuSiftPara, RANSACAffineModPara stuRANSACPara, DOUBLE dRatio, UINT nMaxBlockSize, UINT nMaxOverlap, UINT nTilts, bool bIsSIFTNorASIFT )
{
    CmlGdalDataset clsLImg, clsRImg;
	
    if( dRatio < 10e-2 )
    {
        return false;
    }

    if( ( false == clsLImg.LoadFile( strL ) )||( false == clsRImg.LoadFile( strR ) ) )
    {
        return false;
    }

    CmlBlockCalculation clsBlockCalL( nMaxBlockSize, nMaxBlockSize, nMaxOverlap, nMaxOverlap ), clsBlockCalR( nMaxBlockSize, nMaxBlockSize, nMaxOverlap, nMaxOverlap );
    clsBlockCalL.CalBlockCol( clsLImg.GetWidth(), nMaxBlockSize );
    clsBlockCalL.CalBlockRow( clsLImg.GetHeight(), nMaxBlockSize );

    clsBlockCalR.CalBlockCol( clsRImg.GetWidth(), nMaxBlockSize );
    clsBlockCalR.CalBlockRow( clsRImg.GetHeight(), nMaxBlockSize );

    vector<StereoMatchPt> vecMPts;
	CmlFrameImage clsImg;

    for( UINT i = 0; i < clsBlockCalL.GetRowCount(); ++i )
    {
        for( UINT j = 0; j < clsBlockCalL.GetColCount(); ++j )
        {
            Pt2i ptOrigL;
            UINT nWL, nHL;
            if( true == clsBlockCalL.GetBlockPos( j, i, ptOrigL, nWL, nHL ) )
            {
                CmlRasterBlock blockL;
                if( false == clsLImg.GetRasterGrayBlock( (UINT)1, (UINT)ptOrigL.X, (UINT)ptOrigL.Y, nWL, nHL, dRatio, &blockL ) )
                {
                    continue;
                }
				//////////////////////////////////////////////////////////////////////////		
				//clsImg.RasterGrayStrench(&blockL);//��Ӱ�����лҶ�����
				//////////////////////////////////////////////////////////////////////////
				
                for( UINT k = 0; k < clsBlockCalR.GetRowCount(); ++k )
                {
                    for( UINT h = 0; h < clsBlockCalR.GetColCount(); ++h )
                    {
                        Pt2i ptOrigR;
                        UINT nWR, nHR;
                        if( true == clsBlockCalR.GetBlockPos( h, k, ptOrigR, nWR, nHR ) )
                        {
                            CmlRasterBlock blockR;
                            if( false == clsRImg.GetRasterGrayBlock( (UINT)1, (UINT)ptOrigR.X, (UINT)ptOrigR.Y, nWR, nHR, (UINT)1, &blockR ) )
                            {
                                continue;
                            }
							//////////////////////////////////////////////////////////////////////////							
							//clsImg.RasterGrayStrench(&blockR);//��Ӱ�����лҶ�����
							//////////////////////////////////////////////////////////////////////////
							
                            vector<DOUBLE> vecXL, vecYL, vecXR, vecYR;
                            double *pData = NULL;
							int nPtNum = 0;
							if( true == bIsSIFTNorASIFT )
                            {
                                printf( "Current %d LImg(%d)  Match  %d  RImg(%d) \n", (i*clsBlockCalL.GetRowCount()+j), (clsBlockCalL.GetRowCount()*clsBlockCalL.GetColCount())\
									       , (k*clsBlockCalR.GetRowCount()+h), (clsBlockCalR.GetRowCount()*clsBlockCalR.GetColCount()) );
								
								nPtNum = SiftMatch( (char*)blockL.GetData(), blockL.GetW(), blockL.GetH(), 1, (char*)blockR.GetData(), blockR.GetW(), blockR.GetH(), 1, &pData, stuSiftPara.nMaxCheck, stuSiftPara.dRatio );
																
							}
                            else
                            {
                                double *pXL, *pXR, *pYL, *pYR;
                                pXL = pXR = pYL = pYR = NULL;

                                int nASiftNum = ASiftMatch( (UCHAR*)blockL.GetData(), blockL.GetW(), blockL.GetH(), (UCHAR*)blockR.GetData(), blockR.GetW(), blockR.GetH(), pXL, pYL, pXR, pYR, nTilts );

                                for( UINT i = 0; i < (UINT)nASiftNum; ++i )
                                {
                                    vecXL.push_back( pXL[i]);
                                    vecYL.push_back( pYL[i]);
                                    vecXR.push_back( pXR[i]);
                                    vecYR.push_back( pYR[i]);
                                }
                                freeASiftData( pXL );
                                freeASiftData( pXR );
                                freeASiftData( pYL );
                                freeASiftData( pYR );
                            }
							if (bIsSIFTNorASIFT ==true)
							{
								for( UINT m = 0; m < nPtNum; ++m )
								{
									StereoMatchPt ptTempMatch;
									ptTempMatch.ptLInImg.X = ( pData[4*m] + ptOrigL.X ) / dRatio;
									ptTempMatch.ptLInImg.Y = ( pData[4*m+1] + ptOrigL.Y ) / dRatio;
									ptTempMatch.ptRInImg.X = pData[4*m+2] + ptOrigR.X;
									ptTempMatch.ptRInImg.Y = pData[4*m+3] + ptOrigR.Y;
									vecMPts.push_back( ptTempMatch );
								}
								FreePtr( &pData );
							}
							else
							{
								for( UINT m = 0; m < nPtNum; ++m )
								{
									StereoMatchPt ptTempMatch;
									
									ptTempMatch.ptLInImg.X = ( vecXL[m] + ptOrigL.X ) / dRatio;
									ptTempMatch.ptLInImg.Y = ( vecYL[m] + ptOrigL.Y ) / dRatio;
									ptTempMatch.ptRInImg.X = vecXR[m] + ptOrigR.X;
									ptTempMatch.ptRInImg.Y = vecYR[m] + ptOrigR.Y;
									
									vecMPts.push_back( ptTempMatch );
								}
							}
                        }
                    }
                }
            }
        }
    }

	//�޳��ظ���
	eraseSamePoints(vecMPts, 1.0);
	
    ///////////////////////////////////////////////////////////////////////////////////////
    vector<DOUBLE> vecXLTemp,vecYLTemp,vecXRTemp,vecYRTemp;
    vector<bool> vecbFlags;
	double* pPtData = new double[vecMPts.size()*4];
    for( UINT i = 0; i < vecMPts.size(); ++i )
    {
        StereoMatchPt ptCur = vecMPts[i];
        pPtData[4*i] = ptCur.ptLInImg.X;
       pPtData[4*i+1] =  ptCur.ptLInImg.Y ;
       pPtData[4*i+2] =  ptCur.ptRInImg.X ;
       pPtData[4*i+3] =  ptCur.ptRInImg.Y ;
    }
	//vecMatchPts=vecMPts;

	bool *pbData = NULL;
	//int nPtNum = getRanSacPtsVT( pSrcData, nCount, &pbData, stuRANSACPara.dSigma, stuRANSACPara.dMinItera );
	int nPtNum = getRanSacPtsVT( pPtData, vecMPts.size(), &pbData, stuRANSACPara.dSigma, stuRANSACPara.dMinItera );
	if( 0 != nPtNum )
	{
		for( UINT i = 0; i < nPtNum; ++i )
		{
			if( true ==pbData[i] )
			{
				vecMatchPts.push_back( vecMPts[i] );
			}
		}
		FreeRansacPtr( &pbData );
		return true;
	}
	else
	{
		return false;
	}
}

bool CmlStereoProc::mlFindCorPtsInRegFeatPts( const char* pImgLPath, const char* pImgRPath, Pt2i ptL, Pt2i &ptR, DOUBLE &dCoef, \
                                   ExtractFeatureOpt extFeatOpts, MatchInRegPara matchPara )
{
    CmlFrameImage clsImgL, clsImgR;
    if( ( false == clsImgL.LoadFile( pImgLPath ) )||( false == clsImgR.LoadFile( pImgRPath ) ) )
    {
        return false;
    }
    if( false == clsImgR.ExtractFeatPtByForstner( extFeatOpts.nGridSize, extFeatOpts.nPtMaxNum, extFeatOpts.dThresCoef ) )
    {
        return false;
    }
    return ( mlFindCorPtsInRegFeatPts( &clsImgL.m_DataBlock, &clsImgR.m_DataBlock, clsImgR.m_vecFeaPtsList, ptL, ptR, dCoef, extFeatOpts, matchPara) );
}
bool CmlStereoProc::mlFindCorPtsInRegFeatPts( CmlRasterBlock* pBlockL, CmlRasterBlock* pBlockR, vector<Pt2i> vecPtsInRImg, Pt2i ptL, Pt2i &ptR, DOUBLE &dCoef, \
                                   ExtractFeatureOpt extFeatOpts, MatchInRegPara matchPara )
{
    CmlFrameImage clsImgR;
//    vector<Pt2i> vecFeatPts;
//    if( false == clsImgR.ExtractFeatPtByForstner( *pBlockR, vecFeatPts, extFeatOpts.nGridSize, extFeatOpts.nPtMaxNum, extFeatOpts.dThresCoef ) )
//    {
//        return false;
//    }
    CmlStereoProc clsStereoProc;
    vector<Pt2i> vecPtsL;
    vecPtsL.push_back( ptL );
    vector<StereoMatchPt> vecMatchPts;
    MLRect rect;
    rect.dXMax = matchPara.dXMax;
    rect.dYMax = matchPara.dYMax;
    rect.dXMin = matchPara.dXMin;
    rect.dYMin = matchPara.dYMin;
    if( true == clsStereoProc.mlTemplateMatch( pBlockL, pBlockR, vecPtsL, vecPtsInRImg, vecMatchPts, \
                                              rect, matchPara.nTempSize, matchPara.dCoefThres, SINT(matchPara.dXOff), SINT(matchPara.dYOff ) ) )
    {
        if( 1 == vecMatchPts.size() )
        {
            Pt2d pt = vecMatchPts[0].ptRInImg;
            ptR.X = SINT( pt.X + ML_ZERO );
            ptR.Y = SINT( pt.Y + ML_ZERO );
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
bool CmlStereoProc::AffineSIFTMatch( const SCHAR* strL, const SCHAR* strR, UINT nNumTilts, vector<StereoMatchPt> &vecOutMPts )
{
    CmlFrameImage clsImgL, clsImgR;
    if( ( false == clsImgL.LoadFile( strL ) )||( false == clsImgR.LoadFile( strR ) ) )
    {
        return false;
    }
    DOUBLE *pLx, *pLy, *pRx, *pRy;
    pLx = pLy = pRx = pRy = NULL;
    UINT nNum = ASiftMatch( clsImgL.m_DataBlock.GetData(), clsImgL.GetWidth(), clsImgL.GetHeight(), clsImgR.m_DataBlock.GetData(), clsImgR.GetWidth(), clsImgR.GetHeight(), \
                pLx, pLy, pRx, pRy, nNumTilts );
    for( UINT i = 0; i < nNum; ++i )
    {
        StereoMatchPt ptTemp;
        ptTemp.ptLInImg.X = pLx[i];
        ptTemp.ptLInImg.Y = pLy[i];
        ptTemp.ptRInImg.X = pRx[i];
        ptTemp.ptRInImg.Y = pRy[i];
        vecOutMPts.push_back( ptTemp );
    }
    freeASiftData( pLx );
    freeASiftData( pLy );
    freeASiftData( pRx );
    freeASiftData( pRy );

    return true;
}
bool CmlStereoProc::mlMatchPtPyra(vector<StereoMatchPt> &vecMatchPtIn, vector<StereoMatchPt> &vecMatchPtOut, SINT nSize, SINT nCase)
{
    SINT nTemp = vecMatchPtIn.size();
    if(nTemp==0)
    {
        return false;
    }
    if(nCase==1)
    {
        for(int i=0; i<nTemp; i++)
        {
            StereoMatchPt pt;
            pt.ptLInImg.X = vecMatchPtIn[i].ptLInImg.X/nSize;
            pt.ptLInImg.Y = vecMatchPtIn[i].ptLInImg.Y/nSize;
            pt.ptRInImg.X = vecMatchPtIn[i].ptRInImg.X/nSize;
            pt.ptRInImg.Y = vecMatchPtIn[i].ptRInImg.Y/nSize;
            vecMatchPtOut.push_back(pt);
        }
    }
    else
    {
        for(int i=0; i<nTemp; i++)
        {
            StereoMatchPt pt;
            pt.ptLInImg.X = (vecMatchPtIn[i].ptLInImg.X)*nSize;
            pt.ptLInImg.Y = (vecMatchPtIn[i].ptLInImg.Y)*nSize;
            pt.ptRInImg.X = (vecMatchPtIn[i].ptRInImg.X)*nSize;
            pt.ptRInImg.Y = (vecMatchPtIn[i].ptRInImg.Y)*nSize;
            vecMatchPtOut.push_back(pt);
        }
    }
    return true;

}
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
bool CmlStereoProc::mlDenseMatchPyra(CmlRasterBlock* pBlockL,  CmlRasterBlock* pBlockR,vector<StereoMatchPt> &vecMatchPt, WideOptions WidePara, \
                                     vector<Pt2d> &vecLPts, vector<Pt2d> &vecRPts,SINT nSize)
{
    if(nSize==0)
    {
        return this->mlDenseMatch(pBlockL, pBlockR, vecMatchPt, WidePara, vecLPts, vecRPts);
    }
    else
    {
        CmlFrameImage clsFrameImg;
        //������Ӱ�����ɽ�����Ӱ��
        vector<CmlRasterBlock> pyraBlockL, pyraBlockr;
        clsFrameImg.imgpyramid(pBlockL, pyraBlockL, nSize);
        clsFrameImg.imgpyramid(pBlockR, pyraBlockr, nSize);

        //������һ��Ӱ���ϵ�������
        vector<StereoMatchPt> vecOript;
        vecOript = vecMatchPt;

        //���ϵ��¼����������
        vector<StereoMatchPt> vecPyMatchPt;

        //������Ӱ��ƥ��õ����ܼ���
        vector<StereoMatchPt> vecTempPt;

        for(SINT i = 0; i<= nSize; i++)
        {
            WideOptions Wopts;
            Wopts = WidePara;
            SINT tt = nSize - i;
            SINT nCoef = SINT(pow(2.0,tt));

            if(vecTempPt.size()!=0)
            {
                vecTempPt.clear();
            }
            Wopts.nStep = (SINT)(WidePara.nStep/nCoef);
            if(Wopts.nStep == 0)
            {
                Wopts.nStep = 1;
            }
            Wopts.nRadiusX = (SINT)(WidePara.nRadiusX/nCoef);
            Wopts.nRadiusY = (SINT)(WidePara.nRadiusX/nCoef);
            vector<Pt2d> vecPyPtL, vecPyPtR;

            if(tt==nSize)
            {
                if(vecPyMatchPt.size()!=0)
                    vecPyMatchPt.clear();
                //ԭʼӰ���������������С��������Ľ�����
                if (this->mlMatchPtPyra(vecOript, vecPyMatchPt, nCoef,1)==TRUE)
                {
                    if(vecPyPtL.size()!=0)
                    {
                        vecPyPtL.clear();
                    }
                    if(vecPyPtR.size()!=0)
                    {
                        vecPyPtR.clear();
                    }
                    CmlRasterBlock imgL, imgR;
                    imgL = pyraBlockL[tt];
                    imgR = pyraBlockr[tt];
                    this->mlDenseMatch(&imgL, &imgR, vecPyMatchPt, Wopts, vecPyPtL, vecPyPtR);
                    if(vecTempPt.size()!=0)
                    {
                        vecTempPt.clear();
                    }
                    for(SINT j=0; j<vecPyPtL.size(); j++)
                    {
                        StereoMatchPt pt;
                        pt.ptLInImg.X = vecPyPtL[j].X;
                        pt.ptLInImg.Y = vecPyPtL[j].Y;
                        pt.ptRInImg.X = vecPyPtR[j].X;
                        pt.ptRInImg.Y = vecPyPtR[j].Y;
                        vecTempPt.push_back(pt);
                    }
                    this->mlGetRansacPts(vecTempPt,0, 0.99);
                    this->mlFilterPtsByMedian(vecTempPt);
                    //��ƥ���õ���������ܼ���ϲ�
//                    for( UINT k = 0; k < vecPyMatchPt.size(); ++k )
//                    {
//
//                        vecTempPt.push_back( vecPyMatchPt[k] );
//                    }
                    if(vecOript.size()!=0)
                    {
                        vecOript.clear();
                    }
                    this->mlUniquePt(vecTempPt);
                    vecOript = vecTempPt;
                }
                else
                {
                    return false;
                }

            }
            else
            {
                if(vecPyPtL.size()!=0)
                {
                    vecPyPtL.clear();
                }
                if(vecPyPtR.size()!=0)
                {
                    vecPyPtR.clear();
                }
                if(vecPyMatchPt.size()!=0)
                    vecPyMatchPt.clear();
                //���������������Ӱ���ܼ����������ϲ��Ŵ�����һ��Ӱ��
                if (this->mlMatchPtPyra(vecOript, vecPyMatchPt, 2,2)==TRUE)
                {
                    CmlRasterBlock imgL, imgR;
                    imgL = pyraBlockL[tt];
                    imgR = pyraBlockr[tt];
                    this->mlDenseMatch(&imgL, &imgR, vecPyMatchPt, Wopts, vecPyPtL, vecPyPtR);
                    if(vecTempPt.size()!=0)
                    {
                        vecTempPt.clear();
                    }
                    for(SINT j=0; j<vecPyPtL.size(); j++)
                    {
                        StereoMatchPt pt;
                        pt.ptLInImg.X = vecPyPtL[j].X;
                        pt.ptLInImg.Y = vecPyPtL[j].Y;
                        pt.ptRInImg.X = vecPyPtR[j].X;
                        pt.ptRInImg.Y = vecPyPtR[j].Y;
                        vecTempPt.push_back(pt);
                    }
                    this->mlGetRansacPts(vecTempPt,0,0.99);
                    this->mlFilterPtsByMedian(vecTempPt);
                    //��ƥ���õ���������ܼ���ϲ�
//                    for( UINT k = 0; k < vecPyMatchPt.size(); ++k )
//                    {
//                        vecTempPt.push_back( vecPyMatchPt[k] );
//                    }
                    if(vecOript.size()!=0)
                    {
                        vecOript.clear();
                    }
                    //ȥ���ظ��ĵ�
                    this->mlUniquePt(vecTempPt);
                    vecOript = vecTempPt;
                }
            }

        }
        //���������ܼ�ƥ����
        SINT nNum = vecOript.size();
        for(SINT i=0; i<nNum ; i++)
        {
            Pt2d tempPt;
            tempPt.X = vecOript[i].ptLInImg.X;
            tempPt.Y = vecOript[i].ptLInImg.Y;
            vecLPts.push_back(tempPt);

            tempPt.X = vecOript[i].ptRInImg.X;
            tempPt.Y = vecOript[i].ptRInImg.Y;
            vecRPts.push_back(tempPt);
        }
        return true;
    }
}
