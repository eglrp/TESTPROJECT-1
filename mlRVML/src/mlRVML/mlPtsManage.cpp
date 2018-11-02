/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlPtsManage.cpp
* @date 2012.02.10
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ƥ������Դ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#include "mlPtsManage.h"

/**
* @fn CmlPtsManage
* @date 2012.02.10
* @author ���Ļ� whwan@irsa.ac.cn
* @brief CmlPtsManage��ղι��캯��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlPtsManage::CmlPtsManage()
{
    //ctor
}

/**
* @fn ~CmlPtsManage
* @date 2012.02.10
* @author ���Ļ� whwan@irsa.ac.cn
* @brief CmlPtsManage����������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlPtsManage::~CmlPtsManage()
{
    //dtor
}

/**
* @fn GetPairPts
* @date 2012.02.10
* @author  ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ��ƥ������Ӱ��ƥ���ϲ�
* @param clsImgLPts ��Ӱ��ƥ���
* @param clsImgRPts ��Ӱ��ƥ���
* @param vecMatchPts ����ƥ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlPtsManage::GetPairPts( ImgPtSet &clsImgLPts, ImgPtSet &clsImgRPts, vector<StereoMatchPt> &vecMatchPts )
{
    map< ULONG, Pt2d > mapRPts;
    for( UINT i = 0; i < clsImgRPts.vecPts.size(); ++i )
    {
        Pt2d ptCur = clsImgRPts.vecPts[i];
        mapRPts.insert( map<ULONG, Pt2d>::value_type( ptCur.lID, ptCur ) );
    }


    for( UINT i = 0; i < clsImgLPts.vecPts.size(); ++i )
    {
        Pt2d ptCur = clsImgLPts.vecPts[i];
        map<ULONG, Pt2d>::iterator it = mapRPts.find( ptCur.lID );
        if( it != mapRPts.end() )
        {
            StereoMatchPt ptMatch;
            ptMatch.ptLInImg = ptCur;
            ptMatch.ptRInImg = it->second;
            ptMatch.lID = ptCur.lID;
            vecMatchPts.push_back( ptMatch );
        }
    }

    bool bFlag = true;
    if( vecMatchPts.size() == 0 )
    {
        bFlag = false;
    }

    for( UINT i = 0; i < clsImgLPts.vecAddPts.size(); ++i )
    {
        Pt2d ptLCur = clsImgLPts.vecAddPts[i];
        for( UINT j = 0; j < clsImgRPts.vecAddPts.size(); ++j )
        {
            Pt2d ptRCur = clsImgRPts.vecAddPts[j];
            if( ptLCur.lID == ptRCur.lID )
            {
                StereoMatchPt ptMatch;
                ptMatch.ptLInImg = ptLCur;
                ptMatch.ptRInImg = ptRCur;
                ptMatch.lID = ptLCur.lID;
                vecMatchPts.push_back( ptMatch );
            }
        }
    }
    return bFlag;
}

/**
* @fn SplitPairPts
* @date 2012.02.10
* @author  ���Ļ� whwan@irsa.ac.cn
* @brief ���ɶ�ƥ���ֿ�
* @param frmInfoL ��Ӱ����Ϣ
* @param frmInfoR ��Ӱ����Ϣ
* @param vecAutoMatchPts ����ͬ��ƥ���
* @param clsImgLPts ��Ӱ��ƥ���
* @param clsImgRPts ��Ӱ��ƥ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlPtsManage::SplitPairPts( FrameImgInfo frmInfoL, FrameImgInfo frmInfoR, vector<StereoMatchPt> &vecAutoMatchPts, ImgPtSet &clsImgLPts, ImgPtSet &clsImgRPts )
{

    UINT nLIndex = frmInfoL.nImgIndex;
    UINT nRIndex = frmInfoR.nImgIndex;

    if( clsImgLPts.imgInfo.nCamID == 0 )
    {
        clsImgLPts.imgInfo = frmInfoL;
    }
    if( clsImgRPts.imgInfo.nCamID == 0 )
    {
        clsImgRPts.imgInfo = frmInfoR;
    }


    for( UINT i = 0; i < vecAutoMatchPts.size(); ++i )
    {
        StereoMatchPt* pt = &vecAutoMatchPts[i];
        ULONG nTmpID = nLIndex * 10e11 + nRIndex * 10e7 + i + 1;;
        Pt2d ptL, ptR;
        ptL = pt->ptLInImg;
        ptL.byType = 1;
        ptL.lID = nTmpID;

        ptR = pt->ptRInImg;
        ptR.byType = 1;
        ptR.lID = nTmpID;

        clsImgLPts.vecPts.push_back( ptL );
        clsImgRPts.vecPts.push_back( ptR );
    }
    return true;
}

bool getFindRes( vector<Pt2d> &vecPts, ULONG lID )
{
    for( UINT i = 0; i < vecPts.size(); ++i )
    {
        ULONG lCurID = vecPts[i].lID;
        if( lCurID == lID )
        {
            return true;
        }
    }
    return false;
}

/**
* @fn GetNewStereoPtID
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
bool CmlPtsManage::GetNewStereoPtID(  ImgPtSet &clsLPts, ImgPtSet &clsRPts, ULONG &lID  )
{
    if( ( clsLPts.imgInfo.nImgIndex == 0 )||( clsRPts.imgInfo.nImgIndex == 0 ) )
    {
        return false;
    }
    ULONG lHeadID = clsLPts.imgInfo.nImgIndex * 10e11 + clsRPts.imgInfo.nImgIndex * 10e7 +  9 * 10e6 + 1;
    for( UINT i = 0; i < 10e5; ++i )
    {
        ULONG lCurID = lHeadID + i;

        if( ( false == getFindRes( clsLPts.vecAddPts, lCurID ) )&&( false == getFindRes( clsLPts.vecAddPts, lCurID ) ) )
        {
            lID = lCurID;
            return true;
        }
    }
    return false;
}

/**
* @fn GetNewSinglePtID
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
bool CmlPtsManage::GetNewSinglePtID(  ImgPtSet &clsImgPts, ULONG &lID  )
{
    if( ( clsImgPts.imgInfo.nImgIndex == 0 ) )
    {
        return false;
    }
    ULONG lHeadID = clsImgPts.imgInfo.nImgIndex * 10e11 + clsImgPts.imgInfo.nImgIndex * 10e7 +  9 * 10e6 + 1;
    for( UINT i = 0; i < 10e5; ++i )
    {
        ULONG lCurID = lHeadID + i;

        if( false == getFindRes( clsImgPts.vecAddPts, lCurID ) )
        {
            lID = lCurID;
            return true;
        }
    }
    return false;
}


