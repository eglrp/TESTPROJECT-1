/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlCamCalib.h
* @date 2012.01
* @author �⿭ wukai@irsa.ac.cn
* @brief ����������궨ģ��ͷ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#include "mlCamCalib.h"

/**
 *@fn CmlCamCalib()
 *@date 2011.11
 *@author �⿭
 *@brief ����궨�๹�캯��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
*/
CmlCamCalib::CmlCamCalib()
{
    bInParaInitFlag = false ;
    pLPara = NULL ; //��ʼ״ָ̬���ֵ
    camModel = Affine ; // Ĭ��10����ģ��
    dltTerm.nIterMax = 30 ;
    dltTerm.dThreshValue = 0.05 ;
    colinearityTerm.nIterMax = 50 ;
    colinearityTerm.dThreshValue = 0.00001 ;
    nGcp = 0 ;
}

/**
 *@fn CmlCamCalib()
 *@date 2011.11
 *@author �⿭
 *@brief ����궨����������
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
*/
CmlCamCalib::~CmlCamCalib()
{
    if(pLPara)
    {
        delete [] pLPara ;
    }
}

/**
 *@fn mlSingleCamCalib
 *@date 2012.02
 *@author �⿭
 *@brief ������궨����
 *@param vecImgPts  ���Ƶ�����������
 *@param vecObjPts ���Ƶ��﷽��������
 *@param nW  Ӱ����
 *@param nH  Ӱ��߶�
 *@param inPara ����ڲ���
 *@param exPara  ��������
 *@param vecErrorPts  ���Ƶ��񷽲в�����
 *@param bFlag �жϸ��������ʼ�����ٱ궨���Ǽ��㾫�ȼ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool  CmlCamCalib::mlSingleCamCalib(vector<Pt2d>& vecImgPts , const vector<Pt3d>& vecObjPts ,SINT nW , SINT nH ,
                                    InOriPara& inCamPara , ExOriPara& exCamPara ,vector<Pt3d>& vecErrorPts , bool bFlag)
{
    // ������ʼ��������ٱ궨
    if( bFlag )
    {
        // ����궨������ʼ��
        if(!homographPtsInit( vecImgPts , vecObjPts , inCamPara , nW , nH))
        {
            return false ;
        }
        else
        {
            // ֱ�����Ա任�����ʼ�������
            if(!dltCalib())
            {
                SCHAR strErr[] = "single camera calibration fail : dlt method returns error \t" ;
                LOGAddErrorMsg(strErr) ;
                return false ;
            }
            // �����Ե������㾫�����������
            else if(!colinearityCalib())
            {
                SCHAR strErr[] = "single camera calibration fail : colinearity method returns error \t" ;
                LOGAddErrorMsg(strErr) ;
                return false ;
            }
            inCamPara = inPara ;
            exCamPara = exPara ;
            // ���Ƶ��񷽲в�ȼ��
            if(!imgErrorCheck(imgPtsList , objPtsList , inPara , exPara , vecErrorPts))
            {
                SCHAR strErr[] = "single camera calibration fail : accuracy analysis returns error \t" ;
                LOGAddErrorMsg(strErr) ;
                return false ;
            }
            vecImgPts.clear() ;
            vecImgPts = imgPtsList ;
            return true ;
        }
    }
    else // ���㾫������
    {
        // ����궨������ʼ��
        if(!homographPtsInit( vecImgPts , vecObjPts , inCamPara , nW , nH))
        {
            return false ;
        }
        // �����񷽾��ȼ��
        if(!imgErrorCheck(imgPtsList , objPtsList , inPara , exCamPara , vecErrorPts))
        {
            SCHAR strErr[] = "single camera calibration fail : accuracy analysis returns error \t" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        vecImgPts.clear() ;
        vecImgPts = imgPtsList ;
        return true ;
    }
}

/**
 *@fn mlStereoCamCalib()
 *@date 2012.02
 *@author �⿭
 *@brief ˫����궨����
 *@param vecLImgPts  ���Ƶ����������������
 *@param vecRImgPts  ���Ƶ����������������
 *@param vecObjPts  ���Ƶ��﷽��������
 *@param nW  Ӱ����
 *@param nH Ӱ��߶�
 *@param inLPara  ������ڲ���
 *@param inRPara  ������ڲ���
 *@param exLPara  ����������
 *@param exRPara ����������
 *@param exStereoPara  ���������Է�λ����
 *@param vecErrorPts  ���Ƶ��﷽�в�����
 *@param bFlag �жϸ��������ʼ�����ٱ궨���Ǽ��㾫�ȼ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool  CmlCamCalib::mlStereoCamCalib(const vector<Pt2d>& vecLImgPts , const vector<Pt2d>& vecRImgPts , vector<Pt3d>& vecObjPts ,
                                    SINT nW , SINT nH , InOriPara& inLPara , InOriPara& inRPara , ExOriPara& exLPara , ExOriPara& exRPara , ExOriPara& exStereoPara, vector<Pt3d>& vecErrorPts , bool bFlag)
{
    // ������ʼ��������ٱ궨
    if(bFlag)
    {
        // ������궨������ʼ��
        if(!homographPtsInit( vecLImgPts , vecObjPts , inLPara , nW , nH))
        {
            return false ;
        }
        else
        {
            // ֱ�����Ա任�����ʼ�������
            if(!dltCalib())
            {
                SCHAR strErr[] = "single camera calibration fail : left camera dlt method returns error \t" ;
                LOGAddErrorMsg(strErr) ;
                return false ;
            }
            // �����Ե������㾫�����������
            else if(!colinearityCalib())
            {
                SCHAR strErr[] = "single camera calibration fail : left camera colinearity method returns error \t" ;
                LOGAddErrorMsg(strErr) ;
                return false ;
            }
            // �ڸ�������ڲ��������ϣ���һ���󷽽��ᾫ���ⷽλԪ��
            if(!backProjection(imgPtsList , objPtsList , inPara ,exPara))
            {
                SCHAR strErr[] = "mlStereoCalib  fail :  left camera backProjection failed \t" ;
                LOGAddErrorMsg(strErr) ;
                return false ;
            }
            inLPara = inPara ;
            exLPara = exPara ;
        }
        // ������Ӱ����������
        vector<Pt2d> vecLImgPtsList(imgPtsList) ;
        // ������궨������ʼ��
        if(!homographPtsInit( vecRImgPts , vecObjPts , inRPara , nW , nH))
        {
            return false ;
        }
        else
        {
            // ֱ�����Ա任�����ʼ�������
            if(!dltCalib())
            {
                SCHAR strErr[] = "single camera calibration fail : right camera dlt method returns error \t" ;
                LOGAddErrorMsg(strErr) ;
                return false ;
            }
            // �����Ե������㾫�����������
            else if(!colinearityCalib())
            {
                SCHAR strErr[] = "single camera calibration fail : right camera colinearity method returns error \t" ;
                LOGAddErrorMsg(strErr) ;
                return false ;
            }
            // �ڸ�������ڲ��������ϣ���һ���󷽽��ᾫ���ⷽλԪ��
            if(!backProjection(imgPtsList , objPtsList , inPara ,exPara))
            {
                SCHAR strErr[] = "mlStereoCalib  fail : right camera backProjection failed \t" ;
                LOGAddErrorMsg(strErr) ;
                return false ;
            }
            inRPara = inPara ;
            exRPara = exPara ;
        }
        // ���������������ⷽλԪ��
        if(!stereoParaSolve(exLPara , exRPara , exStereoPara))
        {
            SCHAR strErr[] = "mlStereoCalib  fail : stereo orientation failed \t" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        // ���Ƶ��﷽�в������
        if(!objErrorCheck(vecLImgPtsList , imgPtsList , objPtsList , inLPara , inRPara , exLPara ,exRPara , vecErrorPts))
        {
            SCHAR strErr[] = "mlStereoCalib  fail : accuracy analysis failed \t" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        vecObjPts.clear() ;
        vecObjPts = objPtsList ;
        return true ;
    }
    else
    {
        // �﷽���ȼ��
        // ��������ļ���ʼ��
        if(!homographPtsInit( vecLImgPts , vecObjPts , inLPara , nW , nH))
        {
            return false ;
        }
        vector<Pt2d> vecLImgPtsList(imgPtsList) ;
        // ��������ļ���ʼ��
        if(!homographPtsInit( vecRImgPts , vecObjPts , inLPara , nW , nH))
        {
            return false ;
        }
        // �����﷽���ȼ��
        if(!objErrorCheck(vecLImgPts , imgPtsList , objPtsList , inLPara , inRPara , exLPara ,exRPara , vecErrorPts))
        {
            SCHAR strErr[] = "mlStereoCalib  fail : accuracy analysis failed \t" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        vecObjPts.clear() ;
        vecObjPts = objPtsList ;
        return true ;
    }
}

/**
 *@fn homographPtsInit()
 *@date 2012.02
 *@author �⿭
 *@brief ����궨������ʼ��
 *@param vecImgPts  ���Ƶ�����������
 *@param vecObjPts  ���Ƶ��﷽��������
 *@param inCamPara �����ʼ����
 *@param nW  ������
 *@param nH  ����߶�
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlCamCalib::homographPtsInit(const vector<Pt2d>& vecImgPts, const vector<Pt3d>& vecObjPts, InOriPara& inCamPara ,SINT nW , SINT nH)
{
    int nSize1 , nSize2 ;
    nSize1 = vecObjPts.size() ;
    nSize2 = vecImgPts.size() ;
    nGcp = 0 ;
    if(!nSize1 || !nSize2 )
    {
        return false ;
    }
    else
    {
        if(imgPtsList.size())
        {
            imgPtsList.clear() ;
        }
        if(objPtsList.size())
        {
            objPtsList.clear() ;
        }
        m_nW = nW ;
        m_nH = nH ;
        inPara = inCamPara ;
        // �������ڲ����Ƿ��г�ֵ �� �����ڲ�����
        if((inPara.x > 0) && (inPara.x < (m_nW-1)) && (inPara.y > 0) && (inPara.y < (m_nH - 1)))
        {
            bInParaInitFlag = true ;
        }
        else
        {
            bInParaInitFlag = false ;
        }
        // ������ŵõ���Ӧ��ƥ����
        for( int i = 0 ; i < nSize2 ; i++)
        {
            Pt2d ptImg = vecImgPts[i] ;
            for( int j = 0 ; j < nSize1 ; j++)
            {
                Pt3d ptObj = vecObjPts[j] ;
                if( ptImg.lID == ptObj.lID)
                {
                    imgPtsList.push_back(ptImg) ;
                    objPtsList.push_back(ptObj) ;
                    nGcp++ ;
                    break ;
                }
            }
        }
        // ������Ƶ�����С��7 �������������㣬����
        if(nGcp < 7)
        {
            SCHAR strErr[] = "camera calibration initialization failed : not enough control points \t" ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        else
        {
            // sort , ǰ4������·ֲ����ȼ��� , ������ȼ���
            if(!bInParaInitFlag)
            {
                Pt2d ptRec[4] ; // ˳��left , top , right , bottom
                SINT nIndex[4] ;
                ptRec[0].X = MAX_THRESH ;
                ptRec[1].Y = MIN_THRESH ;
                ptRec[2].X = MIN_THRESH ;
                ptRec[3].Y = MAX_THRESH ;
                for(SINT i = 0 ; i < nGcp ; i++)
                {
                    Pt2d ptTemp ;
                    ptTemp = imgPtsList[i] ;
                    if(ptTemp.X < ptRec[0].X)
                    {
                        ptRec[0] = ptTemp ;
                        nIndex[0] = i ;
                    }
                    else if(ptTemp.X > ptRec[2].X)
                    {
                        ptRec[2] = ptTemp ;
                        nIndex[2] = i ;
                    }
                    if(ptTemp.Y > ptRec[1].Y)
                    {
                        ptRec[1] = ptTemp ;
                        nIndex[1] = i ;
                    }
                    else if(ptTemp.Y < ptRec[3].Y)
                    {
                        ptRec[3] = ptTemp ;
                        nIndex[3] = i ;
                    }
                }
                // ��֤ǰ4�����¾��ȷֲ�
                for( SINT i = 0 ;i < 4 ; i++)
                {
                    if(nIndex[i] != i)
                    {
                        Pt2d pt2dTemp ;
                        Pt3d pt3dTemp ;
                        pt2dTemp = imgPtsList[i] ;
                        pt3dTemp = objPtsList[i] ;
                        imgPtsList[i] = imgPtsList[nIndex[i]] ;
                        objPtsList[i] = objPtsList[nIndex[i]] ;
                        imgPtsList[nIndex[i]] = pt2dTemp ;
                        objPtsList[nIndex[i]] = pt3dTemp ;
                    }
                }
            }
            return true ;
        }
    }
}


/**
 *@fn dltCalib()
 *@date 2012.02
 *@author �⿭
 *@brief ���ֱ�����Ա任�궨
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::dltCalib()
{
    // dlt������ʼ��
    if(!dltParaInit())
    {
        SCHAR strErr[] = "mlDLTCal error : DLT para initialization fail \t" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    // �����������ֵ
    if(!bInParaInitFlag)
    {
        dltPara2InPara(inPara) ;
    }
    // ֱ�����Ա任�����Ե���
    dltParaIterSolve() ;
    dltPara2ExPara() ;
    return true ;
}

/**
 *@fn colinearityCalib()
 *@date 2012.02
 *@author �⿭
 *@brief ����ϸ���ģ�ͱ궨
 *@param �������ģ��ѡ�Ĭ��Ϊ10����ģ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::colinearityCalib(camModelType camType)
{
    SINT nInteriors = 0;
    // ����ѡ�������������ģ��ȷ����Ӧ��λ������ڲ���
    if(camType == Affine)
    {
        nInteriors = 10 ;
    }
    else if(camType == NonAffine)
    {
        nInteriors = 8 ;
    }
    SINT nUnknowns = nInteriors + 6 ;
    // ����ϸ�ģ�Ͳ���������ʼ��
    SINT i , j , k , h ;
    SINT nSize = nGcp;
    CmlMat Bdot1_i_j ;
    CmlMat Epsilon_i_j ;
    CmlMat Deltadot1 ;
    CmlMat Deltadot0 ;
    CmlMat N ;
    CmlMat NInv ;
    CmlMat L ;
    CmlMat P1 ;
    Bdot1_i_j.Initial(2 , nUnknowns) ;
    Epsilon_i_j.Initial(2,1) ;
    Deltadot0.Initial(nUnknowns , 1) ;
    N.Initial(nUnknowns , nUnknowns) ;
    L.Initial(nUnknowns , 1) ;
    P1.Initial(2 , 1);
    P1.SetAt(0 , 0 , 1) ;
    P1.SetAt(1 , 0 , 1) ;
    for( i = 0 ; i < nUnknowns ; i++)
    {
        Deltadot0.SetAt(i , 0 , 0);
    }
    // ���δ֪����
    DOUBLE dx , dy , ddx , ddy , r ;
    InOriPara inParaNew ;
    SINT nLoop ;
    DOUBLE Nx ,Ny ,Nz ;
    DOUBLE a1 , a2 , a3 , b1 , b2 , b3 , c1 , c2 ,c3 ;
    DOUBLE Xs , Ys , Zs , phi , omg , klf ;
    DOUBLE x0 , y0 , f , k1 ,k2 ,k3 ,p1 ,p2 ,alf ,bet ;
    Xs =  exPara.pos.X ;
    Ys = exPara.pos.Y ;
    Zs = exPara.pos.Z ;
    phi = exPara.ori.phi ;
    omg = exPara.ori.omg ;
    klf = exPara.ori.kap ;
    x0 = inPara.x ;
    y0 = inPara.y ;
    f = inPara.f ;
    k1 = inPara.k1 ;
    k2 = inPara.k2 ;
    k3 = inPara.k3 ;
    p1 = inPara.p1 ;
    p2 = inPara.p2 ;
    alf = inPara.alpha ;
    bet = inPara.beta ;
    // �����Ե����������δ֪����
    for(nLoop = 0 ; nLoop < colinearityTerm.nIterMax ; nLoop ++)
    {
        for( i = 0 ; i < nUnknowns ; i++ )
        {
            for( j = 0 ; j < nUnknowns ; j++ )
            {
                N.SetAt(i , j , 0) ;
            }
        }
        for( i = 0 ; i < nUnknowns ; i++)
        {
            L.SetAt(i , 0 , 0);
        }
        // ��ת�����������
        a1 = cos(phi)*cos(klf) - sin(phi)*sin(omg)*sin(klf);
        a2 = -sin(phi)*cos(omg);
        a3 = cos(phi)*sin(klf) + sin(phi)*sin(omg)*cos(klf);
        b1 = sin(phi)*cos(klf) + cos(phi)*sin(omg)*sin(klf);
        b2 = cos(phi)*cos(omg);
        b3 = sin(phi)*sin(klf) - cos(phi)*sin(omg)*cos(klf);
        c1 = -cos(omg)*sin(klf);
        c2 = sin(omg);
        c3 = cos(omg)*cos(klf);
        // ���μ�����Ƶ㣬��ɽ���ķ�����
        for( i = 0 ; i < nSize ; i++ )
        {
            Pt2d imgPt2d = imgPtsList[i] ;
            Pt3d objPt3d = objPtsList[i] ;
            ddx = imgPt2d.X - x0 ;
            ddy = imgPt2d.Y - y0 ;
            r = ddx * ddx + ddy * ddy ;
            // �����Ļ�����
            dx = ddx * (r * (k1 + k2 * r + k3 * r * r) + alf) + bet * ddy +
                 p1*(r + 2.0 * ddx * ddx) + 2.0 * p2 * ddx * ddy;
            dy = ddy * (r * (k1 + k2 * r + k3 * r * r)) + 2.0 * p1 * ddx * ddy + p2 * (r + 2.0 * ddy * ddy);
            Nx = a1*(objPt3d.X - Xs) + b1*(objPt3d.Y - Ys) + c1*(objPt3d.Z - Zs) ;
            Ny = a2*(objPt3d.X - Xs) + b2*(objPt3d.Y - Ys) + c2*(objPt3d.Z - Zs) ;
            Nz = a3*(objPt3d.X - Xs) + b3*(objPt3d.Y - Ys) + c3*(objPt3d.Z - Zs) ;
            // �����̸�δ֪����ϵ������
            //For Xs
            Bdot1_i_j.SetAt(0 , 0 , ((a2 * (ddx+dx) - a1 * f) / Ny)) ;
            Bdot1_i_j.SetAt(1 , 0 , ((a2 * (ddy+dy) - a3 * f) / Ny)) ;
            //For Ys
            Bdot1_i_j.SetAt(0 , 1 , ((b2 * (ddx+dx) - b1 * f) / Ny)) ;
            Bdot1_i_j.SetAt(1 , 1 , ((b2 * (ddy+dy) - b3 * f) / Ny)) ;
            //For Zs
            Bdot1_i_j.SetAt(0 , 2 , ((c2 * (ddx+dx) - c1 * f) / Ny)) ;
            Bdot1_i_j.SetAt(1 , 2 , ((c2 * (ddy+dy) - c3 * f) / Ny)) ;
            //For phi
            Bdot1_i_j.SetAt(0 , 3 , (c3 * f - c2 * (ddy+dy) - (ddx+dx) * (c1 * (ddy+dy) - c3 * (ddx+dx)) / f)) ;
            Bdot1_i_j.SetAt(1 , 3 , (c2 * (ddx+dx) - c1 * f - (ddy+dy) * (c1 * (ddy+dy) - c3 * (ddx+dx)) / f)) ;
            //For omg
            Bdot1_i_j.SetAt(0 , 4 , (f * sin(klf) + (ddx+dx) * ((ddx+dx) * sin(klf) - (ddy+dy) * cos(klf)) / f)) ;
            Bdot1_i_j.SetAt(1 , 4 , (-f * cos(klf) + (ddy+dy) * ((ddx+dx) * sin(klf) - (ddy+dy) * cos(klf)) / f)) ;
            //For klf
            Bdot1_i_j.SetAt(0 , 5 , (-ddy - dy)) ;
            Bdot1_i_j.SetAt(1 , 5 , (ddx + dx)) ;
            //For x0
            Bdot1_i_j.SetAt(0 , 6 , 1.0) ;
            Bdot1_i_j.SetAt(1 , 6 , 0.0) ;
            //For y0
            Bdot1_i_j.SetAt(0 , 7 , 0.0) ;
            Bdot1_i_j.SetAt(1 , 7 , 1.0) ;
            //For f
            Bdot1_i_j.SetAt(0 , 8 , ((ddx + dx) / f)) ;
            Bdot1_i_j.SetAt(1 , 8 , ((ddy + dy) / f)) ;
            //For k1
            Bdot1_i_j.SetAt(0 , 9 , (-ddx * r)) ;
            Bdot1_i_j.SetAt(1 , 9 , (-ddy * r)) ;
            //For k2
            Bdot1_i_j.SetAt(0 , 10 , (-ddx * r * r)) ;
            Bdot1_i_j.SetAt(1 , 10 , (-ddy * r * r)) ;
            //For k3
            Bdot1_i_j.SetAt(0 , 11 , (-ddx * r * r * r)) ;
            Bdot1_i_j.SetAt(1 , 11 , (-ddy * r * r * r)) ;
            // For p1
            Bdot1_i_j.SetAt(0 , 12 , (-(r + 2.0 * ddx * ddx))) ;
            Bdot1_i_j.SetAt(1 , 12 , (-2.0 * ddx * ddy)) ;
            // For p2
            Bdot1_i_j.SetAt(0 , 13 , (-2.0 * ddx * ddy)) ;
            Bdot1_i_j.SetAt(1 , 13 , (-(r + 2.0 * ddy * ddy))) ;
            // For alf, betDeg2Rad
            if(camType == Affine)
            {
                // For alf
                Bdot1_i_j.SetAt(0 , nUnknowns-2 , -ddx) ;
                Bdot1_i_j.SetAt(1 , nUnknowns-2 , 0.0) ;
                // For bet
                Bdot1_i_j.SetAt(0 , nUnknowns-1 , -ddy) ;
                Bdot1_i_j.SetAt(1 , nUnknowns-1 , 0.0) ;
            }
            // constant
            Epsilon_i_j.SetAt(0 , 0 , (ddx + dx - f * Nx / Ny)) ;
            Epsilon_i_j.SetAt(1 , 0 , (ddy + dy - f * Nz / Ny)) ;
            // �з�����
            for (j = 0; j < nUnknowns ; j++)
            {
                for (k = 0; k < nUnknowns ; k++)
                {
                    DOUBLE dTemp  = 0 ;
                    for (h = 0; h < 2; h++)
                    {
                        DOUBLE dTemp1 = Bdot1_i_j.GetAt(h , j) ;
                        DOUBLE dTemp2 = Bdot1_i_j.GetAt(h , k) ;
                        dTemp += dTemp1 * dTemp2 * P1.GetAt(h , 0) ;
                    }
                    dTemp += N.GetAt(j , k);
                    N.SetAt(j , k , dTemp) ;
                }
                DOUBLE dTemp = 0 ;
                for (h = 0; h < 2; h++)
                {
                    DOUBLE dTemp1 = Bdot1_i_j.GetAt(h , j) ;
                    DOUBLE dTemp2 = Epsilon_i_j.GetAt(h , 0) ;
                    dTemp += dTemp1 * dTemp2 * P1.GetAt(h , 0) ;
                }
                dTemp += L.GetAt(j , 0) ;
                L.SetAt(j , 0 , dTemp) ;
            }
        }
        // δ֪��������ֵ����
        if(!mlMatInv(&N , &NInv) || !mlMatMul(&NInv , &L , &Deltadot1))
        {
            SCHAR strErr[] = "mlCamCalib error : equation matrix fails to work \t" ;
            LOGAddErrorMsg(strErr) ;
            return 0 ;
        }
        Xs += Deltadot1.GetAt(0 , 0) ;
        Ys += Deltadot1.GetAt(1 , 0) ;
        Zs += Deltadot1.GetAt(2 , 0) ;
        phi += Deltadot1.GetAt(3 , 0) ;
        omg += Deltadot1.GetAt(4 , 0) ;
        klf += Deltadot1.GetAt(5 , 0) ;
        x0 += Deltadot1.GetAt(6 , 0) ;
        y0 += Deltadot1.GetAt(7 , 0) ;
        f += Deltadot1.GetAt(8 , 0) ;
        k1 += Deltadot1.GetAt(9 , 0) ;
        k2 += Deltadot1.GetAt(10 , 0) ;
        k3 += Deltadot1.GetAt(11 , 0) ;
        p1 += Deltadot1.GetAt(12 , 0) ;
        p2 += Deltadot1.GetAt(13 , 0) ;
        if(camType == Affine)
        {
            alf += Deltadot1.GetAt(nUnknowns-2 , 0) ;
            bet += Deltadot1.GetAt(nUnknowns-1 , 0) ;
        }
        DOUBLE dDeltaMax = 0.0 ;
        // �ж��Ƿ����������ֵ�������������
        for(i = 0 ; i < nUnknowns ; i++)
        {
            dDeltaMax = dDeltaMax > fabs(Deltadot0.GetAt(i , 0) - Deltadot1.GetAt(i , 0)) ? dDeltaMax : fabs(Deltadot0.GetAt(i , 0) - Deltadot1.GetAt(i , 0));
            Deltadot0.SetAt(i , 0 , Deltadot1.GetAt(i , 0)) ;
        }
        if(dDeltaMax > colinearityTerm.dThreshValue)
        {
            continue ;
        }
        else
        {
            break ;
        }
    }
    // �õ����վ��������ⷽλ����
    exPara.pos.X = Xs ;
    exPara.pos.Y = Ys ;
    exPara.pos.Z = Zs ;
    exPara.ori.phi = phi ;
    exPara.ori.omg = omg ;
    exPara.ori.kap = klf ;
    inPara.x = x0 ;
    inPara.y = y0 ;
    inPara.f = f ;
    inPara.k1 = k1 ;
    inPara.k2 = k2 ;
    inPara.k3 = k3 ;
    inPara.p1 = p1 ;
    inPara.p2 = p2 ;
    inPara.alpha = alf ;
    inPara.beta = bet ;
    // �ﵽ�������������˳� �����ش���
    if(nLoop == colinearityTerm.nIterMax)
    {
        SCHAR strErr[] = "mlCamCalib error : iteration fails to converge within the threshhold \t" ;
        LOGAddErrorMsg(strErr) ;
        return 0 ;
    }
    else
    {
        LOGAddSuccessQuitMsg() ;
        return true ;
    }
}

/**
 *@fn imgErrorCheck()
 *@date 2012.02
 *@author �⿭
 *@brief ����궨�񷽾��ȼ��
 *@param vecImgPts  ��������������
 *@param vecObjPts  �����﷽��������
 *@param inPara  ����ڲ���
 *@param exPara  ��������
 *@param vecErrorPts �����񷽲в�����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::imgErrorCheck(const vector<Pt2d>& vecImgPts, const vector<Pt3d>& vecObjPts, InOriPara inPara , ExOriPara exPara , vector<Pt3d>& vecErrorPts)
{
    Pt2d pt2dTemp ;
    Pt3d pt3dTemp ;
    CmlMat pokMat ;
    // �Ƕ�ת��Ϊ��ת����
    POK2RMat(&exPara.ori , &pokMat) ;
    if(vecErrorPts.size())
    {
        vecErrorPts.clear() ;
    }
    Pt3d ptError ;
    for(int i = 0 ; i < nGcp ; i++)
    {
        pt2dTemp = vecImgPts[i] ;
        pt3dTemp = vecObjPts[i] ;
        ULONG nNo = pt2dTemp.lID;
        Pt2d pt2dRectify ;  //  ����У������������
        imgPtRectify(pt2dTemp ,inPara , pt2dRectify) ;
        // �﷽��ͶӰ���������� , ע������궨���Ƶ��ļ�������ϵ��Ҫת��
        Pt2d pt2dProject ;
        objPOKPtReproject(pt3dTemp , exPara.pos, pokMat , inPara , pt2dProject) ;
        // �Ƚϼ�¼�����
        DOUBLE dx = pt2dRectify.X - pt2dProject.X ;
        DOUBLE dy = pt2dRectify.Y - pt2dProject.Y ;
        ptError.lID = nNo ;
        ptError.X = dx ;
        ptError.Y = dy ;
        // ���뵽�񷽵�в�����
        vecErrorPts.push_back(ptError) ;
    }
    return true ;
}

/**
 *@fn objErrorCheck()
 *@date 2012.02
 *@author �⿭
 *@brief  ����궨�﷽���ȼ��
 *@param vecLImgPts �������������������
 *@param vecRImgPts �������������������
 *@param vecObjPts  �����﷽��������
 *@param inLPara  ������ڲ���
 *@param inRPara  ������ڲ���
 *@param exLPara  ����������
 *@param exRPara  ����������
 *@param vecErrorPts  �����﷽�в�����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::objErrorCheck(const vector<Pt2d>& vecLImgPts , const vector<Pt2d>& vecRImgPts ,const vector<Pt3d>& vecObjPts ,
                                InOriPara inLPara , InOriPara inRPara , ExOriPara exLPara , ExOriPara exRPara , vector<Pt3d>& vecErrorPts)
{
    Pt2d imgLPt , imgRPt ;
    Pt3d objRefPt , objCalPt , ptTemp ;
    SINT nLGcp = vecLImgPts.size() ;
    SINT nRGcp = vecRImgPts.size() ;
    for(SINT i = 0 ; i < nLGcp ; i++)
    {
        imgLPt = vecLImgPts[i] ;
        for(SINT j = 0; j < nRGcp ; j++)
        {
            imgRPt = vecRImgPts[j];
            if(imgLPt.lID == imgRPt.lID) //Ϊͬ�����,ǰ���������
            {
                // ע������ϵ��ת�����ⷽλԪ������Ժ󷽽������ģ���ʱ������궨������ϵ��������궨���Ƴ�����Ҫ����ת��
                objRefPt = vecObjPts[j] ;
                DOUBLE dTemp = objRefPt.Y ;
                objRefPt.Y = objRefPt.Z ;
                objRefPt.Z = -dTemp ;
                ptTemp.lID = imgLPt.lID;
                // ǰ������
                if(!forwardIntersection(imgLPt , imgRPt , exLPara , inLPara , exRPara , inRPara , objCalPt))
                {
                    SCHAR strErr[] = "forward intersection failed  \t" ;
                    LOGAddErrorMsg(strErr) ;
                    return false ;
                }
                // �������﷽���
                DOUBLE dx = objRefPt.X - objCalPt.X ;
                DOUBLE dy = objRefPt.Y - objCalPt.Y ;
                DOUBLE dz = objRefPt.Z - objCalPt.Z ;
                ptTemp.X = dx ;
                ptTemp.Y = dy ;
                ptTemp.Z = dz ;
                ptTemp.lID = objRefPt.lID ;
                // ���뵽�﷽��в�����
                vecErrorPts.push_back(ptTemp) ;
            }
        }
    }
    return true ;
}

/**
 *@fn stereoParaSolve()
 *@date 2012.02
 *@author �⿭
 *@brief ˫�����Է�λ��������
 *@param exLPara  ����������
 *@param exRPara  ����������
 *@param exStereoPara  ˫�����Բ���
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::stereoParaSolve(ExOriPara exLPara , ExOriPara exRPara , ExOriPara& exStereoPara)
{
    CmlMat opkLMat ;
    CmlMat opkRMat ;
    // �������Ԫ��ת��Ϊ��ת����
    OPK2RMat(&exLPara.ori , &opkLMat) ;
    // �������Ԫ��ת��Ϊ��ת����
    OPK2RMat(&exRPara.ori , &opkRMat) ;
    DOUBLE R1[9] = {opkLMat.GetAt(0 , 0) , opkLMat.GetAt(0 , 1) , opkLMat.GetAt(0 , 2) ,
                    opkLMat.GetAt(1 , 0) , opkLMat.GetAt(1 , 1) , opkLMat.GetAt(1 , 2) ,
                    opkLMat.GetAt(2 , 0) , opkLMat.GetAt(2 , 1) , opkLMat.GetAt(2 , 2)
                   } ;
    DOUBLE R2[9] = {opkRMat.GetAt(0 , 0) , opkRMat.GetAt(0 , 1) , opkRMat.GetAt(0 , 2) ,
                    opkRMat.GetAt(1 , 0) , opkRMat.GetAt(1 , 1) , opkRMat.GetAt(1 , 2) ,
                    opkRMat.GetAt(2 , 0) , opkRMat.GetAt(2 , 1) , opkRMat.GetAt(2 , 2)
                   } ;
    CmlMat LOriMat , ROriMat ;
    CmlMat LPosMat , RPosMat ;
    LOriMat.Initial(3 , 3) ;
    ROriMat.Initial(3 , 3) ;
    LPosMat.Initial(3 , 1) ;
    RPosMat.Initial(3 , 1) ;
    for(SINT i = 0 ; i < 3 ; i++)
    {
        for(SINT j = 0 ; j < 3 ; j++)
        {
            LOriMat.SetAt( i , j , R1[3*i + j]) ;
            ROriMat.SetAt( i , j , R2[3*i + j]) ;
        }
    }
    LPosMat.SetAt( 0 , 0 , exLPara.pos.X) ;
    LPosMat.SetAt( 1 , 0 , exLPara.pos.Y) ;
    LPosMat.SetAt( 2 , 0 , exLPara.pos.Z) ;
    RPosMat.SetAt( 0 , 0 , exRPara.pos.X) ;
    RPosMat.SetAt( 1 , 0 , exRPara.pos.Y) ;
    RPosMat.SetAt( 2 , 0 , exRPara.pos.Z) ;
    // ���������������ⷽλԪ��
    CmlMat LOriTranMat , LOriTranRMat , RelativeOriMat , RelativePosMat , SubPosMat;
    if(!mlMatTrans(&LOriMat , &LOriTranMat) || !mlMatMul(&LOriTranMat , &ROriMat , &RelativeOriMat))
    {
        return false ;
    }
    if(!mlMatSub(&RPosMat , &LPosMat , &SubPosMat) || !mlMatMul(&LOriTranMat , &SubPosMat , &RelativePosMat))
    {
        return false ;
    }
    // ��������������ⷽλԪ��
    RMat2OPK(&RelativeOriMat , &exStereoPara.ori) ;
    exStereoPara.pos.X = RelativePosMat.GetAt(0 , 0) ;
    exStereoPara.pos.Y = RelativePosMat.GetAt(1 , 0) ;
    exStereoPara.pos.Z = RelativePosMat.GetAt(2 , 0) ;
    return true ;
}

/**
 *@fn forwardIntersection()
 *@date 2012.02
 *@author �⿭
 *@brief ǰ�����ắ��
 *@param imgLPt �����ͼ������
 *@param imgRPt �����ͼ������
 *@param exLPara ��Ƭ�ⷽλԪ��
 *@param inLPara ��Ƭ�ڷ�λԪ��
 *@param exRPara ��Ƭ�ⷽλԪ��
 *@param inRPara ��Ƭ�ڷ�λԪ��
 *@param objPt ǰ�������﷽������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::forwardIntersection(Pt2d imgLPt , Pt2d imgRPt , ExOriPara exLPara , InOriPara inLPara ,
                                      ExOriPara exRPara , InOriPara inRPara , Pt3d& objPt )
{
    // ��ʼ���л������
    Pt2d imgLNewPt , imgRNewPt ;
    imgPtRectify(imgLPt , inLPara , imgLNewPt) ;
    imgPtRectify(imgRPt , inRPara , imgRNewPt) ;
    // ����ϵ����ֵ
    DOUBLE x1 , y1 , x2 , y2 ,f1x , f1y , f2x , f2y;
    CmlMat opkLMat ;
    CmlMat opkRMat ;
    OPK2RMat(&exLPara.ori , &opkLMat) ;
    OPK2RMat(&exRPara.ori , &opkRMat) ;
    DOUBLE R1[9] = {opkLMat.GetAt(0 , 0) , opkLMat.GetAt(0 , 1) , opkLMat.GetAt(0 , 2) ,
                    opkLMat.GetAt(1 , 0) , opkLMat.GetAt(1 , 1) , opkLMat.GetAt(1 , 2) ,
                    opkLMat.GetAt(2 , 0) , opkLMat.GetAt(2 , 1) , opkLMat.GetAt(2 , 2)
                   } ;
    DOUBLE R2[9] = {opkRMat.GetAt(0 , 0) , opkRMat.GetAt(0 , 1) , opkRMat.GetAt(0 , 2) ,
                    opkRMat.GetAt(1 , 0) , opkRMat.GetAt(1 , 1) , opkRMat.GetAt(1 , 2) ,
                    opkRMat.GetAt(2 , 0) , opkRMat.GetAt(2 , 1) , opkRMat.GetAt(2 , 2)
                   } ;
    DOUBLE XsYsZs1[3] = {exLPara.pos.X , exLPara.pos.Y , exLPara.pos.Z} ;
    DOUBLE XsYsZs2[3] = {exRPara.pos.X , exRPara.pos.Y , exRPara.pos.Z} ;
    Pt3d pt3dLOrigin , pt3dROrigin ;
    pt3dLOrigin.X = XsYsZs1[0] ;
    pt3dLOrigin.Y = XsYsZs1[1] ;
    pt3dLOrigin.Z = XsYsZs1[2] ;
    pt3dROrigin.X = XsYsZs2[0] ;
    pt3dROrigin.Y = XsYsZs2[1] ;
    pt3dROrigin.Z = XsYsZs2[2] ;
    x1 = imgLNewPt.X ;
    y1 = imgLNewPt.Y ;
    x2 = imgRNewPt.X ;
    y2 = imgRNewPt.Y ;
    f1x = f1y = inLPara.f ;
    f2x = f2y = inRPara.f ;
    DOUBLE dCoef[4][3];
    dCoef[0][0] = f1x * R1[0] + x1 * R1[2];
    dCoef[0][1] = f1x * R1[3] + x1 * R1[5];
    dCoef[0][2] = f1x * R1[6] + x1 * R1[8];
    dCoef[1][0] = f1y * R1[1] + y1 * R1[2];
    dCoef[1][1] = f1y * R1[4] + y1 * R1[5];
    dCoef[1][2] = f1y * R1[7] + y1 * R1[8];
    dCoef[2][0] = f2x * R2[0] + x2 * R2[2];
    dCoef[2][1] = f2x * R2[3] + x2 * R2[5];
    dCoef[2][2] = f2x * R2[6] + x2 * R2[8];
    dCoef[3][0] = f2y * R2[1] + y2 * R2[2];
    dCoef[3][1] = f2y * R2[4] + y2 * R2[5];
    dCoef[3][2] = f2y * R2[7] + y2 * R2[8];
    CmlMat AMat , BMat ;
    AMat.Initial(4,3) ;
    for ( SINT i = 0; i < 4; ++i )
    {
        for ( SINT j = 0; j < 3; ++j )
        {
            AMat.SetAt( i, j, dCoef[i][j] );
        }
    }
    BMat.Initial(4 , 1);
    DOUBLE dTemp ;
    dTemp = f1x * R1[0] * XsYsZs1[0] + f1x * R1[3] * XsYsZs1[1] + f1x * R1[6] * XsYsZs1[2] +
            x1 * R1[2] * XsYsZs1[0] + x1 * R1[5] * XsYsZs1[1] + x1 * R1[8] * XsYsZs1[2];;
    BMat.SetAt(0 , 0 , dTemp) ;
    dTemp = f1y * R1[1] * XsYsZs1[0] + f1y * R1[4] * XsYsZs1[1] + f1y * R1[7] * XsYsZs1[2] +
            y1 * R1[2] * XsYsZs1[0] + y1 * R1[5] * XsYsZs1[1] + y1 * R1[8] * XsYsZs1[2];
    BMat.SetAt(1 , 0 , dTemp) ;
    dTemp = f2x * R2[0] * XsYsZs2[0] + f2x * R2[3] * XsYsZs2[1] + f2x * R2[6] * XsYsZs2[2] +
            x2 * R2[2] * XsYsZs2[0] + x2 * R2[5] * XsYsZs2[1] + x2 * R2[8] * XsYsZs2[2];
    BMat.SetAt(2 , 0 , dTemp) ;
    dTemp = f2y * R2[1] * XsYsZs2[0] + f2y * R2[4] * XsYsZs2[1] + f2y * R2[7] * XsYsZs2[2] +
            y2 * R2[2] * XsYsZs2[0] + y2 * R2[5] * XsYsZs2[1] + y2 * R2[8] * XsYsZs2[2];
    BMat.SetAt(3 , 0 , dTemp) ;
    // �����ֵ
    CmlMat ATranMat , APlusMat , APlusInvMat , APlusInvATran , CMat;
    if(!mlMatTrans(&AMat , &ATranMat) || !mlMatMul(&ATranMat , &AMat , &APlusMat) || !mlMatInv(&APlusMat , &APlusInvMat))
    {
        return false ;
    }
    else if(!mlMatMul(&APlusInvMat , &ATranMat , &APlusInvATran) || !mlMatMul(&APlusInvATran , &BMat , &CMat))
    {
        return false ;
    }
    DOUBLE XYZ[3] ;
    XYZ[0] = CMat.GetAt(0 , 0) ;
    XYZ[1] = CMat.GetAt(1 , 0) ;
    XYZ[2] = CMat.GetAt(2 , 0) ;
    // �����������ս�����
    SINT nLoop ;
    for(nLoop = 0 ; nLoop < colinearityTerm.nIterMax ; ++nLoop)
    {
        DOUBLE dZCoef1 = R1[2] * ( XYZ[0] - XsYsZs1[0] ) + R1[5] * ( XYZ[1] - XsYsZs1[1] ) + R1[8] * ( XYZ[2] - XsYsZs1[2] );
        DOUBLE dZCoef2 = R2[2] * ( XYZ[0] - XsYsZs2[0] ) + R2[5] * ( XYZ[1] - XsYsZs2[1] ) + R2[8] * ( XYZ[2] - XsYsZs2[2] );
        DOUBLE dTemp  = -1.0 / dZCoef1 * ( R1[0] * f1x + R1[2] * x1 ) ;
        AMat.SetAt(0 , 0 , dTemp) ;
        dTemp = -1.0 / dZCoef1 * ( R1[3] * f1x + R1[5] * x1 );
        AMat.SetAt(0 , 1 , dTemp) ;
        dTemp = -1.0 / dZCoef1 * ( R1[6] * f1x + R1[8] * x1 );
        AMat.SetAt(0 , 2 , dTemp) ;
        dTemp = -1.0 / dZCoef1 * ( R1[1] * f1y + R1[2] * y1 );
        AMat.SetAt(1 , 0 , dTemp) ;
        dTemp = -1.0 / dZCoef1 * ( R1[4] * f1y + R1[5] * y1 );
        AMat.SetAt(1 , 1 , dTemp) ;
        dTemp = -1.0 / dZCoef1 * ( R1[7] * f1y + R1[8] * y1 );
        AMat.SetAt(1 , 2 , dTemp) ;

        dTemp = -1.0 / dZCoef2 * ( R2[0] * f2x + R2[2] * x2 ) ;
        AMat.SetAt(2 , 0 , dTemp) ;
        dTemp = -1.0 / dZCoef2 * ( R2[3] * f2x + R2[5] * x2 );
        AMat.SetAt(2 , 1 , dTemp) ;
        dTemp = -1.0 / dZCoef2 * ( R2[6] * f2x + R2[8] * x2 );
        AMat.SetAt(2 , 2 , dTemp) ;
        dTemp = -1.0 / dZCoef2 * ( R2[1] * f2y + R2[2] * y2 ) ;
        AMat.SetAt(3 , 0 , dTemp) ;
        dTemp = -1.0 / dZCoef2 * ( R2[4] * f2y + R2[5] * y2 );
        AMat.SetAt(3 , 1 , dTemp) ;
        dTemp = -1.0 / dZCoef2 * ( R2[7] * f2y + R2[8] * y2 );
        AMat.SetAt(3 , 2 , dTemp) ;

        Pt2d imgL2dPt , imgR2dPt;
        Pt3d pt3dTemp ;
        pt3dTemp.X = XYZ[0] ;
        pt3dTemp.Y = XYZ[1] ;
        pt3dTemp.Z = XYZ[2] ;
        // ��ƬͶӰ���
        objPtReproject(pt3dTemp , pt3dLOrigin , opkLMat , inLPara , imgL2dPt) ;
        // ��ƬͶӰ���
        objPtReproject(pt3dTemp , pt3dROrigin , opkRMat , inRPara , imgR2dPt) ;
        BMat.SetAt(0 , 0 , (imgL2dPt.X - x1)) ;
        BMat.SetAt(1 , 0 , (imgL2dPt.Y - y1)) ;
        BMat.SetAt(2 , 0 , (imgR2dPt.X - x2)) ;
        BMat.SetAt(3 , 0 , (imgR2dPt.Y - y2)) ;
        if(!mlMatTrans(&AMat , &ATranMat) || !mlMatMul(&ATranMat , &AMat , &APlusMat) || !mlMatInv(&APlusMat , &APlusInvMat))
        {
            return false ;
        }
        else if(!mlMatMul(&APlusInvMat , &ATranMat , &APlusInvATran) || !mlMatMul(&APlusInvATran , &BMat , &CMat))
        {
            return false ;
        }
        for( SINT j = 0 ; j < 3 ; j++)
        {
            XYZ[j] += CMat.GetAt(j , 0) ;
        }

        // �ж��Ƿ��������
        DOUBLE dDeltaMax = 0.0 ;
        for(SINT i = 0 ; i < 3 ; i++)
        {
            dDeltaMax = dDeltaMax > fabs(CMat.GetAt(i , 0)) ? dDeltaMax : fabs(CMat.GetAt(i , 0));
        }
        if(dDeltaMax > colinearityTerm.dThreshValue)
        {
            continue ;
        }
        else
        {
            break ;
        }
    }
    if(nLoop == colinearityTerm.nIterMax)
    {
        SCHAR strErr[] = "mlBackProjection error : iteration fails to converge within the threshhold \t" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    else
    {
        objPt.X = XYZ[0] ;
        objPt.Y = XYZ[1] ;
        objPt.Z = XYZ[2] ;
        LOGAddSuccessQuitMsg() ;
        return true ;
    }
}


/**
 *@fn dltParaInit()
 *@date 2012.02
 *@author �⿭
 *@brief ֱ�����Ա궨��ʼ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::dltParaInit()
{
    // ֱ�����Ա任ģ�Ͳ���������ʼ��
    SINT i , j , k , h ;
    SINT nUnknowns = 11 ;
    SINT nSize = 6 ;
    CmlMat Bdot1_i_j ;
    CmlMat Epsilon_i_j ;
    CmlMat Deltadot1 ;
    CmlMat N ;
    CmlMat NInv ;
    CmlMat L ;
    CmlMat P1 ;
    Bdot1_i_j.Initial(2 , nUnknowns) ;
    Epsilon_i_j.Initial(2 , 1) ;
    N.Initial(nUnknowns , nUnknowns) ;
    L.Initial(nUnknowns , 1) ;
    P1.Initial(2 , 1);
    P1.SetAt(0 , 0 , 1) ;
    P1.SetAt(1 , 0 , 1) ;
    for( i = 0 ; i < nUnknowns ; i++ )
        for( j = 0 ; j < nUnknowns ; j++ )
        {
            N.SetAt(i , j , 0) ;
        }
    for( i = 0 ; i < nUnknowns ; i++)
    {
        L.SetAt(i , 0 , 0);
    }
    // ֱ�����Ա任ģ�Ͳ������̽���
    for( i = 0 ; i < nSize ; i++ )
    {
        Pt2d imgPt2d = imgPtsList[i] ;
        Pt3d objPt3d = objPtsList[i] ;
        Bdot1_i_j.SetAt(0 , 0 , objPt3d.X) ;
        Bdot1_i_j.SetAt(0 , 1 , objPt3d.Y) ;
        Bdot1_i_j.SetAt(0 , 2 , objPt3d.Z) ;
        Bdot1_i_j.SetAt(0 , 3 , 1) ;
        Bdot1_i_j.SetAt(0 , 4 , 0) ;
        Bdot1_i_j.SetAt(0 , 5 , 0) ;
        Bdot1_i_j.SetAt(0 , 6 , 0) ;
        Bdot1_i_j.SetAt(0 , 7 , 0) ;
        Bdot1_i_j.SetAt(0 , 8 , -imgPt2d.X*objPt3d.X) ;
        Bdot1_i_j.SetAt(0 , 9 , -imgPt2d.X*objPt3d.Y) ;
        Bdot1_i_j.SetAt(0 , 10 , -imgPt2d.X*objPt3d.Z) ;
        Bdot1_i_j.SetAt(1 , 0 , 0) ;
        Bdot1_i_j.SetAt(1 , 1 , 0) ;
        Bdot1_i_j.SetAt(1 , 2 , 0) ;
        Bdot1_i_j.SetAt(1 , 3 , 0) ;
        Bdot1_i_j.SetAt(1 , 4 , objPt3d.X) ;
        Bdot1_i_j.SetAt(1 , 5 , objPt3d.Y) ;
        Bdot1_i_j.SetAt(1 , 6 , objPt3d.Z) ;
        Bdot1_i_j.SetAt(1 , 7 , 1) ;
        Bdot1_i_j.SetAt(1 , 8 , -imgPt2d.Y*objPt3d.X) ;
        Bdot1_i_j.SetAt(1 , 9 , -imgPt2d.Y*objPt3d.Y) ;
        Bdot1_i_j.SetAt(1 , 10 , -imgPt2d.Y*objPt3d.Z) ;
        Epsilon_i_j.SetAt(0 , 0 , imgPt2d.X);
        Epsilon_i_j.SetAt(1 , 0 , imgPt2d.Y);
        // ֱ�����Ա任ģ�ͷ����̽���
        for (j = 0; j < nUnknowns ; j++)
        {
            for (k = 0; k < nUnknowns ; k++)
            {
                DOUBLE dTemp  = 0 ;
                for (h = 0; h < 2; h++)
                {
                    DOUBLE dTemp1 = Bdot1_i_j.GetAt(h , j) ;
                    DOUBLE dTemp2 = Bdot1_i_j.GetAt(h , k) ;
                    dTemp += dTemp1 * dTemp2 * P1.GetAt(h , 0) ;
                }
                dTemp += N.GetAt(j , k);
                N.SetAt(j , k , dTemp) ;
            }
            DOUBLE dTemp = 0 ;
            for (h = 0; h < 2; h++)
            {
                DOUBLE dTemp1 = Bdot1_i_j.GetAt(h , j) ;
                DOUBLE dTemp2 = Epsilon_i_j.GetAt(h , 0) ;
                dTemp += dTemp1 * dTemp2 * P1.GetAt(h , 0) ;
            }
            dTemp += L.GetAt(j , 0) ;
            L.SetAt(j , 0 , dTemp) ;
        }
    }
    // ֱ�����Ա任ģ��δ֪��������ֵ����
    if(!mlMatInv(&N , &NInv) || !mlMatMul(&NInv , &L , &Deltadot1))
    {
        SCHAR strErr[] = "mlDLTParaInit error : equation matrix fails to work \t" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    if(!pLPara)
    {
        pLPara = new DOUBLE[11];
    }
    for(i = 0 ; i < nUnknowns ; i++)
    {
        pLPara[i] = Deltadot1.GetAt(i , 0);
    }
    LOGAddSuccessQuitMsg() ;
    return true ;
}

/**
 *@fn dltParaIterSolve
 *@date 2012.02
 *@author �⿭
 *@brief ֱ����������궨��������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::dltParaIterSolve()
{
    // ֱ�����Ա任ģ�Ͳ���������ʼ��
    SINT i , j , k , h ;
    SINT nUnknowns = 12 ;
    SINT nSize = nGcp;
    CmlMat Bdot1_i_j ;
    CmlMat Epsilon_i_j ;
    CmlMat Deltadot1 ;
    CmlMat N ;
    CmlMat NInv ;
    CmlMat L ;
    CmlMat P1 ;
    Bdot1_i_j.Initial(2 , nUnknowns) ;
    Epsilon_i_j.Initial(2,1) ;
    N.Initial(nUnknowns , nUnknowns) ;
    L.Initial(nUnknowns , 1) ;
    P1.Initial(2 , 1);
    P1.SetAt(0 , 0 , 1) ;
    P1.SetAt(1 , 0 , 1) ;
    DOUBLE dx , dy , ddx , ddy , r , A ;
    InOriPara inParaNew ;
    SINT nLoop ;
    DOUBLE dx0 ,dy0 , df0 , dx0New ,dy0New , df0New , dk ;
    dx0 = inPara.x ;
    dy0 = inPara.y ;
    df0 = inPara.f ;
    dk = 0 ;
    // ֱ�����Ա任ģ�Ͳ������̽���
    for(nLoop = 0 ; nLoop < dltTerm.nIterMax ; nLoop ++)
    {
        for( i = 0 ; i < nUnknowns ; i++ )
            for( j = 0 ; j < nUnknowns ; j++ )
            {
                N.SetAt(i , j , 0) ;
            }
        for( i = 0 ; i < nUnknowns ; i++)
        {
            L.SetAt(i , 0 , 0);
        }
        for( i = 0 ; i < nSize ; i++ )
        {
            Pt2d imgPt2d = imgPtsList[i] ;
            Pt3d objPt3d = objPtsList[i] ;
            dx = imgPt2d.X - inPara.x;
            dy = imgPt2d.Y - inPara.y;
            r = dx * dx + dy * dy ;
            ddx = dx * r * dk ;
            ddy = dy * r * dk ;
            if(nLoop == 0)
            {
                A = 1 ;
            }
            else
            {
                A = pLPara[8] * objPt3d.X + pLPara[9] * objPt3d.Y + pLPara[10] * objPt3d.Z + 1.0;
            }
            Bdot1_i_j.SetAt(0 , 0 , objPt3d.X/A) ;
            Bdot1_i_j.SetAt(0 , 1 , objPt3d.Y/A) ;
            Bdot1_i_j.SetAt(0 , 2 , objPt3d.Z/A) ;
            Bdot1_i_j.SetAt(0 , 3 , 1.0/A) ;
            Bdot1_i_j.SetAt(0 , 4 , 0) ;
            Bdot1_i_j.SetAt(0 , 5 , 0) ;
            Bdot1_i_j.SetAt(0 , 6 , 0) ;
            Bdot1_i_j.SetAt(0 , 7 , 0) ;
            Bdot1_i_j.SetAt(0 , 8 , -(dx + ddx)*objPt3d.X/A) ;
            Bdot1_i_j.SetAt(0 , 9 , -(dx + ddx)*objPt3d.Y/A) ;
            Bdot1_i_j.SetAt(0 , 10 , -(dx + ddx)*objPt3d.Z/A) ;
            Bdot1_i_j.SetAt(0 , 11 , -dx*r) ;
            Bdot1_i_j.SetAt(1 , 0 , 0) ;
            Bdot1_i_j.SetAt(1 , 1 , 0) ;
            Bdot1_i_j.SetAt(1 , 2 , 0) ;
            Bdot1_i_j.SetAt(1 , 3 , 0) ;
            Bdot1_i_j.SetAt(1 , 4 , objPt3d.X/A) ;
            Bdot1_i_j.SetAt(1 , 5 , objPt3d.Y/A) ;
            Bdot1_i_j.SetAt(1 , 6 , objPt3d.Z/A) ;
            Bdot1_i_j.SetAt(1 , 7 , 1.0/A) ;
            Bdot1_i_j.SetAt(1 , 8 , -(dy + ddy)*objPt3d.X/A) ;
            Bdot1_i_j.SetAt(1 , 9 , -(dy + ddy)*objPt3d.Y/A) ;
            Bdot1_i_j.SetAt(1 , 10 , -(dy + ddy)*objPt3d.Z/A) ;
            Bdot1_i_j.SetAt(1 , 11 , -dy*r) ;
            Epsilon_i_j.SetAt(0 , 0 , dx/A);
            Epsilon_i_j.SetAt(1 , 0 , dy/A);
            // ֱ�����Ա任ģ�ͷ����̽���
            for (j = 0; j < nUnknowns ; j++)
            {
                for (k = 0; k < nUnknowns ; k++)
                {
                    DOUBLE dTemp  = 0 ;
                    for (h = 0; h < 2; h++)
                    {
                        DOUBLE dTemp1 = Bdot1_i_j.GetAt(h , j) ;
                        DOUBLE dTemp2 = Bdot1_i_j.GetAt(h , k) ;
                        dTemp += dTemp1 * dTemp2 * P1.GetAt(h , 0) ;
                    }
                    dTemp += N.GetAt(j , k);
                    N.SetAt(j , k , dTemp) ;
                }
                DOUBLE dTemp = 0 ;
                for (h = 0; h < 2; h++)
                {
                    DOUBLE dTemp1 = Bdot1_i_j.GetAt(h , j) ;
                    DOUBLE dTemp2 = Epsilon_i_j.GetAt(h , 0) ;
                    dTemp += dTemp1 * dTemp2 * P1.GetAt(h , 0) ;
                }
                dTemp += L.GetAt(j , 0) ;
                L.SetAt(j , 0 , dTemp) ;
            }
        }
        // ֱ�����Ա任ģ��δ֪��������ֵ����
        if(!mlMatInv(&N , &NInv) || !mlMatMul(&NInv , &L , &Deltadot1))
        {
            SCHAR strErr[] = "mlDLTParaIterSolve failed : equation matrix fails to work \t " ;
            LOGAddErrorMsg(strErr) ;
            return false ;
        }
        for(i=0 ; i < nUnknowns-1 ; i++)
        {
            pLPara[i] = Deltadot1.GetAt(i , 0);
        }
        dk += Deltadot1.GetAt(nUnknowns-1 , 0) ;
        // dltģ�Ͳ���ת��Ϊ����ڲ���
        dltPara2InPara(inParaNew) ;
        dx0New = inParaNew.x ;
        dy0New = inParaNew.y ;
        df0New = inParaNew.f ;
        // �ж��Ƿ�ﵽ������ֹ��ֵ�������������
        if(fabs(df0New - df0) > dltTerm.dThreshValue)
        {
            dx0 = dx0New ;
            dy0 = dy0New ;
            df0 = df0New ;
            inPara.x += dx0 ;
            inPara.y += dy0 ;
            inPara.f = df0 ;
            continue ;
        }
        else
        {
            dx0 = dx0New ;
            dy0 = dy0New ;
            df0 = df0New ;
            inPara.x += dx0 ;
            inPara.y += dy0 ;
            inPara.f = df0 ;
            break ;
        }
    }
    inPara.k1 = dk ;
    // ���������ﵽ������ֵ�����ش���
    if(nLoop == dltTerm.nIterMax)
    {
        SCHAR strErr[] = "mlDLTParaIterSolve error : iteration fails to converge within the threshhold \t" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    LOGAddSuccessQuitMsg() ;
    return true ;
}


/**
 *@fn dltPara2InPara
 *@date 2012.02
 *@author �⿭
 *@brief ֱ�����Ա任���������ڷ�λ����
 *@param inPara
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CmlCamCalib::dltPara2InPara(InOriPara& inPara)
{
    // ֱ�����Ա任11���������ڷ�λ����
    DOUBLE ll = 1.0/(pLPara[8] * pLPara[8] + pLPara[9] * pLPara[9] + pLPara[10] * pLPara[10]) ;
    DOUBLE x0 = (pLPara[0] * pLPara[8] + pLPara[1] * pLPara[9] + pLPara[2] * pLPara[10]) * ll ;
    DOUBLE y0 = (pLPara[4] * pLPara[8] + pLPara[5] * pLPara[9] + pLPara[6] * pLPara[10]) * ll ;
    DOUBLE A = (pLPara[0] * pLPara[0] + pLPara[1] * pLPara[1] + pLPara[2] * pLPara[2]) * ll - x0 * x0 ;
    DOUBLE B = (pLPara[4] * pLPara[4] + pLPara[5] * pLPara[5] + pLPara[6] * pLPara[6]) * ll - y0 * y0 ;
    DOUBLE C = (pLPara[0] * pLPara[4] + pLPara[1] * pLPara[5] + pLPara[2] * pLPara[6]) * ll - x0 * y0 ;
    DOUBLE Bet = asinf(C/sqrtf(fabs(A * B))) ;
    DOUBLE f0 = sqrt(fabs(A)) * fabs(cos(Bet)) ;
    inPara.f = f0 ;
    inPara.x = x0 ;
    inPara.y = y0 ;
}


/**
 *@fn dltPara2ExPara
 *@date 2012.02
 *@author �⿭
 *@brief ֱ�����Ա任���������ⷽλ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::dltPara2ExPara()
{
    // ֱ�����Ա任11���������ⷽλ����
    DOUBLE ll = 1.0/(pLPara[8] * pLPara[8] + pLPara[9] * pLPara[9] + pLPara[10] * pLPara[10]) ;
    DOUBLE x0 = inPara.x ;
    DOUBLE y0 = inPara.y ;
    DOUBLE A = (pLPara[0] * pLPara[0] + pLPara[1] * pLPara[1] + pLPara[2] * pLPara[2]) * ll - x0 * x0 ;
    DOUBLE B = (pLPara[4] * pLPara[4] + pLPara[5] * pLPara[5] + pLPara[6] * pLPara[6]) * ll - y0 * y0 ;
    DOUBLE Fx = sqrt(fabs(A)) ;
    DOUBLE Fy = sqrt(fabs(B)) ;
    DOUBLE r = sqrtf(ll) ;
    DOUBLE a2 = pLPara[8] * r ;
    DOUBLE b2 = pLPara[9] * r ;
    DOUBLE c2 = pLPara[10] * r ;
    // �õ�����ĽǷ�λԪ��
    exPara.ori.phi = atanl(-a2/b2) ;
    exPara.ori.omg = asin(c2) ;
    // ���������̽�������ⷽλԪ��
    DOUBLE c1 = (pLPara[2] * r - c2 * x0) / Fx ;
    DOUBLE c3 = (pLPara[6] * r - c2 * y0) / Fy ;
    exPara.ori.kap = atan(-c1/c3) ;
    CmlMat N , NT , NTN , NTL;
    CmlMat NInv ;
    CmlMat L ;
    CmlMat Deltadot1 ;
    L.Initial(3 , 1) ;
    N.Initial(3 , 3) ;
    N.SetAt(0 , 0 , pLPara[0]) ;
    N.SetAt(0 , 1 , pLPara[1]) ;
    N.SetAt(0 , 2 , pLPara[2]) ;
    N.SetAt(1 , 0 , pLPara[8]) ;
    N.SetAt(1 , 1 , pLPara[9]) ;
    N.SetAt(1 , 2 , pLPara[10]) ;
    N.SetAt(2 , 0 , pLPara[4]) ;
    N.SetAt(2 , 1 , pLPara[5]) ;
    N.SetAt(2 , 2 , pLPara[6]) ;
    L.SetAt(0 , 0 , -pLPara[3]) ;
    L.SetAt(1 , 0 , -1) ;
    L.SetAt(2 , 0 , -pLPara[7]) ;
    // �ⷽλ��Ԫ�ؽ���
    if(!mlMatTrans(&N , &NT) || !mlMatMul(&NT , &N , &NTN) || !mlMatMul(&NT , &L , &NTL))
    {
        return false ;
    }
    else if(!mlMatInv(&NTN , &NInv) || !mlMatMul(&NInv , &NTL , &Deltadot1))
    {
        return false ;
    }
    else
    {
        exPara.pos.X = Deltadot1.GetAt(0 , 0) ;
        exPara.pos.Y = Deltadot1.GetAt(1 , 0) ;
        exPara.pos.Z = Deltadot1.GetAt(2 ,0) ;
        LOGAddSuccessQuitMsg() ;
        return true ;
    }
}

/**
 *@fn POK2RMat()
 *@date 2012.02
 *@author �⿭
 *@brief �Ƕ�ת��Ϊ��ת���� (���ڿ��Ƴ��궨����ϵ����ת��������ڹ��̻�����omg-phi-kap(x,y,z),������ϵͳ���omg,phi������ͬ��kap�����෴)
 *@param pOri ��Ԫ��ָ��   ת��phi-omg-kapת��ϵͳ����ʱphi���z�ᣬomg���x�ᣬkap���y��
 *@param pRMat ��ת����ָ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::POK2RMat( OriAngle* pOri, CmlMat* pRMat )
{
    // �жϾ���״̬�������˳�
    if( false == pRMat->IsValid() )
    {
        pRMat->Initial( 3, 3 );
    }
    if( ( pRMat->GetH() != 3) || ( pRMat->GetW() != 3 ) )
    {
        return false;
    }

    DOUBLE dSOmg = sin( (pOri->omg) );
    DOUBLE dSPhi = sin( (pOri->phi) );
    DOUBLE dSKap = sin( (pOri->kap) );

    DOUBLE dCOmg = cos( (pOri->omg) );
    DOUBLE dCPhi = cos( (pOri->phi) );
    DOUBLE dCKap = cos( (pOri->kap) );

    // ��ת�����Ԫ�ظ�ֵ
    pRMat->SetAt( 0, 0, (dCPhi*dCKap - dSKap*dSOmg*dSPhi) );
    pRMat->SetAt( 0, 1, (-dSPhi*dCOmg) );
    pRMat->SetAt( 0, 2, (dCPhi*dSKap + dSPhi*dSOmg*dCKap) );

    pRMat->SetAt( 1, 0, ( dSPhi*dCKap + dCPhi*dSOmg*dSKap) );
    pRMat->SetAt( 1, 1, ( dCOmg*dCPhi ) );
    pRMat->SetAt( 1, 2, (dSPhi*dSKap - dCPhi*dSOmg*dCKap));

    pRMat->SetAt( 2, 0, ( -dCOmg*dSKap) );
    pRMat->SetAt( 2, 1, dSOmg );
    pRMat->SetAt( 2, 2, dCOmg*dCKap);

    return true;
}

/**
 *@fn imgPtRectify()
 *@date 2012.02
 *@author �⿭
 *@brief ͼ������У��
 *@param ptXY У��ǰ��
 *@param inPara ����ڲ���
 *@param ptNewXY У�����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CmlCamCalib::imgPtRectify(Pt2d ptXY , InOriPara inPara , Pt2d& ptNewXY)
{
    // �õ�ͼ������ϵ�µ�����
    DOUBLE ddx = ptXY.X - inPara.x ;
    DOUBLE ddy = ptXY.Y - inPara.y ;
    DOUBLE r = ddx * ddx + ddy * ddy ;
    // �õ����������ͼ������ϵ�µ�����
    ptNewXY.X = ddx + ddx * (r * (inPara.k1 + inPara.k2 * r + inPara.k3 * r * r) + inPara.alpha) + inPara.beta * ddy +
                inPara.p1*(r + 2.0 * ddx * ddx) + 2.0 * inPara.p2 * ddx * ddy;
    ptNewXY.Y = ddy + ddy * (r * (inPara.k1 + inPara.k2 * r + inPara.k3 * r * r)) + 2.0 * inPara.p1 * ddx * ddy + inPara.p2 * (r + 2.0 * ddy * ddy);
    return  ;
}

/**
 *@fn objPOKPtReproject()
 *@date 2012.02
 *@author �⿭
 *@brief pok����ϵͳ������﷽�㷴ͶӰ���񷽵�
 *@param ptXYZ �﷽��
 *@param ptS ����ⷽλ��Ԫ��
 *@param pPokMat �����Ԫ�ر任����
 *@param inPara ����ڲ���
 *@param ptNewXYZ �﷽���Ӧ����ͶӰ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CmlCamCalib::objPOKPtReproject(Pt3d ptXYZ , Pt3d ptS , CmlMat pPokMat ,InOriPara inPara , Pt2d& ptNewXYZ )
{
    DOUBLE dX = ptXYZ.X - ptS.X ;
    DOUBLE dY = ptXYZ.Y - ptS.Y ;
    DOUBLE dZ = ptXYZ.Z - ptS.Z ;

    DOUBLE dCoefX = pPokMat.GetAt(0 , 0) * dX + pPokMat.GetAt(1 , 0) * dY + pPokMat.GetAt(2 , 0) * dZ;
    DOUBLE dCoefY = pPokMat.GetAt(0 , 1) * dX + pPokMat.GetAt(1 , 1) * dY + pPokMat.GetAt(2 , 1) * dZ;
    DOUBLE dCoefZ = pPokMat.GetAt(0 , 2) * dX + pPokMat.GetAt(1 , 2) * dY + pPokMat.GetAt(2 , 2) * dZ;

    ptNewXYZ.X = inPara.f * dCoefX / dCoefY;
    ptNewXYZ.Y = inPara.f * dCoefZ / dCoefY;
}

/**
 *@fn objPtReproject()
 *@date 2012.02
 *@author �⿭
 *@brief opk����ϵͳ������﷽�㷴ͶӰ���񷽵�
 *@param ptXYZ �﷽��
 *@param ptS ����ⷽλ��Ԫ��
 *@param pOpkMat �����Ԫ�ر任����
 *@param inPara ����ڲ���
 *@param ptNewXYZ �﷽���Ӧ����ͶӰ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CmlCamCalib::objPtReproject(Pt3d ptXYZ , Pt3d ptS , CmlMat pOpkMat ,InOriPara inPara , Pt2d& ptNewXYZ )
{
    DOUBLE dX = ptXYZ.X - ptS.X ;
    DOUBLE dY = ptXYZ.Y - ptS.Y ;
    DOUBLE dZ = ptXYZ.Z - ptS.Z ;

    DOUBLE dCoefX = pOpkMat.GetAt(0 , 0) * dX + pOpkMat.GetAt(1 , 0) * dY + pOpkMat.GetAt(2 , 0) * dZ;
    DOUBLE dCoefY = pOpkMat.GetAt(0 , 1) * dX + pOpkMat.GetAt(1 , 1) * dY + pOpkMat.GetAt(2 , 1) * dZ;
    DOUBLE dCoefZ = pOpkMat.GetAt(0 , 2) * dX + pOpkMat.GetAt(1 , 2) * dY + pOpkMat.GetAt(2 , 2) * dZ;

    ptNewXYZ.X = -inPara.f * dCoefX / dCoefZ;
    ptNewXYZ.Y = -inPara.f * dCoefY / dCoefZ;
    return  ;
}

/**
 *@fn backProjection
 *@date 2012.02
 *@author �⿭
 *@brief �󷽽��ᣨ����ϵͳת�����ٽ��㣩
 *@param imgPtsList ���Ƶ�����������
 *@param objPtsList ���Ƶ��﷽��������
 *@param inPara ����ڲ���
 *@param exPara ��������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CmlCamCalib::backProjection(const vector<Pt2d>& imgPtsList , const vector<Pt3d>& objPtsList ,
                                 InOriPara& inPara , ExOriPara& exPara)
{
    SINT nTotal = imgPtsList.size() ;
    CmlMat pAMat ;
    CmlMat pAMatT ;
    CmlMat PAMatTAMat ;
    CmlMat PAMatTAMatInv ;
    CmlMat pLMat ;
    CmlMat pAMatTLMat ;
    CmlMat pXMat ;
    CmlMat pXMatOld ;
    vector<Pt2d> imgProjPtsList ;
    vector<Pt3d> objProjPtsList ;
    SINT nLoop ;
    SINT nUnknowns = 6 ;
    pAMat.Initial(nTotal*2 , nUnknowns) ;
    pLMat.Initial(nTotal*2 , 1) ;
    pXMatOld.Initial(nUnknowns ,1) ;
    DOUBLE dTemp = exPara.pos.Y ;
    exPara.pos.Y = exPara.pos.Z ;
    exPara.pos.Z = -dTemp ;
    exPara.ori.kap = -exPara.ori.kap ;
    for( SINT i = 0 ; i < nUnknowns ; i++)
    {
        pXMatOld.SetAt(i,0 ,0) ;
    }
    for( SINT i = 0 ; i < nTotal ; i++)
    {
        Pt2d pt2dTemp ;
        Pt3d pt3dTemp ;
        pt2dTemp = imgPtsList[i] ;
        pt3dTemp = objPtsList[i] ;
        Pt2d pt2dRectify ; // �񷽵����У������������
        imgPtRectify(pt2dTemp , inPara , pt2dRectify) ;
        imgProjPtsList.push_back(pt2dRectify) ;
        Pt3d pt3dNew ;
        pt3dNew.X = pt3dTemp.X;
        pt3dNew.Y = pt3dTemp.Z;
        pt3dNew.Z = -pt3dTemp.Y;
        objProjPtsList.push_back(pt3dNew) ;
    }
    DOUBLE fx ;
    DOUBLE fy ;
    CmlMat opkMat ;
    ofstream stmTest ;
    for(nLoop = 0 ; nLoop < colinearityTerm.nIterMax ; nLoop ++)
    {
        fx = fy = inPara.f ;
        OPK2RMat(&exPara.ori , &opkMat) ;
        DOUBLE a1 = opkMat.GetAt(0,0);
        DOUBLE a2 = opkMat.GetAt(0,1);
        DOUBLE a3 = opkMat.GetAt(0,2);

        DOUBLE b1 = opkMat.GetAt(1,0);
        DOUBLE b2 = opkMat.GetAt(1,1);
        DOUBLE b3 = opkMat.GetAt(1,2);

        DOUBLE c1 = opkMat.GetAt(2,0);
        DOUBLE c2 = opkMat.GetAt(2,1);
        DOUBLE c3 = opkMat.GetAt(2,2);
        for(SINT i = 0 ; i < nTotal ; i++)
        {
            //���Ƶ���ά����
            Pt2d pt2dTemp ;
            Pt3d pt3dTemp ;
            pt2dTemp = imgProjPtsList[i] ;
            pt3dTemp = objProjPtsList[i] ;

            Pt2d pt2dProject ; // �﷽��ͶӰ����������
            objPtReproject(pt3dTemp , exPara.pos , opkMat , inPara , pt2dProject) ;

            // L ϵ��
            pLMat.SetAt(2 * i, 0,(pt2dTemp.X - pt2dProject.X));
            pLMat.SetAt(2 * i + 1, 0, (pt2dTemp.Y - pt2dProject.Y));
            // ע��ת������
            DOUBLE dXt = pt3dTemp.X - exPara.pos.X;
            DOUBLE dYt = pt3dTemp.Y - exPara.pos.Y;
            DOUBLE dZt = pt3dTemp.Z - exPara.pos.Z;

            DOUBLE dXCoef = a1 * dXt + b1 * dYt + c1 * dZt;
            DOUBLE dYCoef = a2 * dXt + b2 * dYt + c2 * dZt;
            DOUBLE dZCoef = a3 * dXt + b3 * dYt + c3 * dZt;
            DOUBLE dZCoefRev = 1.0 / dZCoef;

            DOUBLE dTempCoef = 0.0;
            dTempCoef = fx * dZCoefRev * dZCoefRev * (dXCoef * (-c3 * dYt + b3 * dZt)- dZCoef * (-c1 * dYt + b1 * dZt));
            pAMat.SetAt(2*i, 0, dTempCoef);


            DOUBLE dAngle[3] = {exPara.ori.omg, exPara.ori.phi, exPara.ori.kap};
            DOUBLE dR[9] = {a1,a2,a3,b1,b2,b3,c1,c2,c3};

            dTempCoef = fx * dZCoefRev * dZCoefRev * ( dXCoef*( cos(dAngle[1])*dXt + sin(dAngle[0])*sin(dAngle[1])*dYt - cos(dAngle[0])*sin(dAngle[1])*dZt)
                        -dZCoef*( -sin(dAngle[1])*cos(dAngle[2])*dXt + sin(dAngle[0])*cos(dAngle[1])*cos(dAngle[2])*dYt - cos(dAngle[0])*cos(dAngle[1])*cos(dAngle[2])*dZt));
            pAMat.SetAt(2*i, 1, dTempCoef);

            dTempCoef = -fx * dZCoefRev *( dR[1]*dXt + dR[4]*dYt + dR[7]*dZt );
            pAMat.SetAt(2*i, 2,dTempCoef);

            dTempCoef = fx * dZCoefRev * dZCoefRev * ( dXCoef*dR[2] - dZCoef*dR[0] );
            dTempCoef *= -1.0;
            pAMat.SetAt(2*i,3,dTempCoef);

            dTempCoef = fx * dZCoefRev * dZCoefRev * ( dXCoef*dR[5] - dZCoef*dR[3] );
            dTempCoef *= -1.0;
            pAMat.SetAt(2*i,4,dTempCoef);

            dTempCoef = fx * dZCoefRev * dZCoefRev * ( dXCoef*dR[8] - dZCoef*dR[6] );
            dTempCoef *= -1.0;
            pAMat.SetAt(2*i,5,dTempCoef);

            dTempCoef = fy * dZCoefRev * dZCoefRev * ( dYCoef*( -dR[8]*dYt + dR[5]*dZt ) - dZCoef*(-dR[7]*dYt + dR[4]*dZt) );
            pAMat.SetAt(2*i+1,0,dTempCoef);

            dTempCoef = fy * dZCoefRev * dZCoefRev * ( dYCoef*( cos(dAngle[1])*dXt + sin(dAngle[0])*sin(dAngle[1])*dYt - cos(dAngle[0])*sin(dAngle[1])*dZt) -
                        dZCoef*( sin(dAngle[1])*sin(dAngle[2])*dXt - sin(dAngle[0])*cos(dAngle[1])*sin(dAngle[2])*dYt + cos(dAngle[0])*cos(dAngle[1])*sin(dAngle[2])*dZt));
            pAMat.SetAt(2 * i + 1, 1, dTempCoef);

            dTempCoef = fy * dZCoefRev *( dR[0]*dXt + dR[3]*dYt + dR[6]*dZt );
            pAMat.SetAt(2*i+1,2,dTempCoef);

            dTempCoef = fy * dZCoefRev * dZCoefRev * ( dYCoef*dR[2] - dZCoef*dR[1] );
            dTempCoef *= -1.0;
            pAMat.SetAt(2*i+1, 3, dTempCoef);

            dTempCoef = fy * dZCoefRev * dZCoefRev * ( dYCoef*dR[5] - dZCoef*dR[4] );
            dTempCoef *= -1.0;
            pAMat.SetAt(2*i + 1,4, dTempCoef);

            dTempCoef = fy * dZCoefRev * dZCoefRev * ( dYCoef*dR[8] - dZCoef*dR[7] );
            dTempCoef *= -1.0;
            pAMat.SetAt(2*i+1,5,dTempCoef);
        }
        mlMatSolveSVD(&pAMat, &pLMat, &pXMat);
        exPara.ori.omg += pXMat.GetAt(0,0);
        exPara.ori.phi += pXMat.GetAt(1,0);
        exPara.ori.kap += pXMat.GetAt(2,0);
        exPara.pos.X += pXMat.GetAt(3,0);
        exPara.pos.Y += pXMat.GetAt(4,0);
        exPara.pos.Z += pXMat.GetAt(5,0);

        // �ж��Ƿ��������
        DOUBLE dDeltaMax = 0.0 ;
        for(SINT i = 0 ; i < nUnknowns ; i++)
        {
            dDeltaMax = dDeltaMax > fabs(pXMat.GetAt(i , 0) - pXMatOld.GetAt(i , 0)) ? dDeltaMax : fabs(pXMat.GetAt(i , 0) - pXMatOld.GetAt(i , 0));
            pXMatOld.SetAt(i , 0 , pXMat.GetAt(i , 0)) ;
        }
        if(dDeltaMax > colinearityTerm.dThreshValue)
        {
            continue ;
        }
        else
        {
            break ;
        }
    }
    if(nLoop == colinearityTerm.nIterMax)
    {
        SCHAR strErr[] = "mlBackProjection error : iteration fails to converge within the threshhold \t" ;
        LOGAddErrorMsg(strErr) ;
        return false ;
    }
    else
    {
        LOGAddSuccessQuitMsg() ;
        return true ;
    }
}
