/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlKinging.cpp
* @date 2012.01
* @author �⿭ wukai@irsa.ac.cn
* @brief Kringing��ֵ����ģ����Դ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#include "mlKringing.h"
/**
 *@fn CmlKringing
 *@date 2012.02
 *@author �⿭
 *@brief CmlKringing���캯��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlKringing::CmlKringing()
{

}

/**
 *@fn ~CmlKringing
 *@date 2012.02
 *@author �⿭
 *@brief CmlKringing��������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlKringing::~CmlKringing()
{

}
/**
 *@fn InitVariogram
 *@date 2012.02
 *@author �⿭
 *@brief Kring�������ʼ������
 *@param dRange Kringģ�;������
 *@param dShort Kring����ʽģ�Ͷ̾������
 *@param dLong  Kring����ʽģ�ͳ��������
 *@param dDisShort ѡ��Kring����ʽ���̾���ģ�Ͳ�������ֵ
 *@param dGraceStart Kring����ģ�Ͷ̾������
 *@param dGraceEnd Kring����ģ�ͳ��������
 *@param dSphericalPara Kring����ģ�Ͷ̾������
 *@param dExponentialPara Kring����ģ�ͳ��������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CmlKringing::InitVariogram(DOUBLE *dShort,DOUBLE *dLong, DOUBLE dRange , DOUBLE dDisShort , DOUBLE dGraceStart , DOUBLE dGraceEnd ,
                                DOUBLE dSphericalPara , DOUBLE dExponentialPara)
{
    // ������ֵģ�Ͳ�����ֵ
    if (dShort==NULL)
    {
        DOUBLE dShortNew[] = {0.00001738, 0.00005993, 0.00053967, 0.00001876};
        memcpy(m_dShortPara,dShortNew,sizeof(DOUBLE)*4);
        DOUBLE dLongNew[] = {-0.00000189, 0.00027033, -0.00109061, 0.00526723};
        memcpy(m_dLongPara,dLongNew,sizeof(DOUBLE)*4);
    }
    else
    {
        memcpy(m_dShortPara,dShort,sizeof(DOUBLE)*4);
        memcpy(m_dLongPara,dLong,sizeof(DOUBLE)*4);
    }
    m_dRange = dRange ;
    m_dDisShort = dDisShort ;
    m_dGraceStart =  dGraceStart ;
    m_dGraceEnd = dGraceEnd ;
    m_dSphericalPara = dSphericalPara ;
    m_dExponentialPara = dExponentialPara ;
}

/**
 *@fn GetValueFromTins
 *@date 2012.02
 *@author �⿭
 *@brief ͨ����������ֵ�߳�����
 *@param vec3DPts �����������3ά����
 *@param tri ���ƹ������Ǹ�������
 *@param pNeigh ��ֵ����Χ���ڽӵ�
 *@param outNewPt ��ֵ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlKringing::GetValueFromTins(const vector<Pt3d>& vec3DPts,triangulateio *tri,
                                   SINT *pNeigh , Pt3d& outNewPt)
{
    // �õ���ֵ�㸽���Ĳ��������ֵ�ĵ�
    vector<Pt3d> vecNeighborPts;
    GetNeighborVertexInMinDis(outNewPt , vec3DPts , tri , pNeigh , 4 ,vecNeighborPts) ;
    SINT nVertex = vecNeighborPts.size() ;
    // �����ֵ�ĵ㲻�㣬�˳�
    if (nVertex < 4)
    {
        return false;
    }
    CmlMat A, B ,W ;
    A.Initial(nVertex+1 , nVertex+1) ;
    B.Initial(nVertex+1 , 1) ;
    // ��ֵ��Ȩ��������
    for (SINT i=0; i<nVertex; i++)
    {
        A.SetAt(i, i , 0) ;
        A.SetAt(i, nVertex , 1) ;
        A.SetAt(nVertex, i, 1) ;
        B.SetAt(i , 0 , semivariogram(&(vecNeighborPts[i]), &outNewPt)) ;
    }

    A.SetAt(nVertex, nVertex , 0) ;
    B.SetAt(nVertex, 0 ,1) ;
    // Э���Ȩ�����������
    for(SINT i=0 ; i<nVertex-1 ; i++)
    {
        for(SINT j=i+1 ; j<nVertex ; j++)
        {
            A.SetAt(i , j , semivariogram(&(vecNeighborPts[i]), &(vecNeighborPts[j]))) ;
            A.SetAt(j , i , A.GetAt(i ,j)) ;
        }
    }
    // ��ֵ��Ȩ����
    CmlMat ATran , ATranA , ATranAInv , ATranB ;
    if(!mlMatTrans(&A , &ATran) || !mlMatMul(&ATran , &A , &ATranA) || !mlMatInv(&ATranA , &ATranAInv)
            ||!mlMatMul(&ATran , &B , &ATranB) || !mlMatMul(&ATranAInv , &ATranB , &W) )
    {
        SCHAR strErr[] = "GetValueFromTin error : correlation plus method fails" ;
        LOGAddErrorMsg(strErr) ;
        return false;
    }
    double dWeightSum = 0 ;
    double dEstimateZ= 0;
    double dWeightMax = -1000;
    // �������ո߳�ֵ
    for(SINT i=0 ; i<nVertex ; i++)
    {
        dWeightSum += W.GetAt(i,0);
        dWeightMax = max(dWeightMax, fabs(W.GetAt(i,0)));
    }
    if(dWeightMax == 0)
    {
        return false ;
    }
    for(SINT i=0 ; i<nVertex ; i++)
    {
        dEstimateZ += (W.GetAt(i,0) * vecNeighborPts[i].Z)/dWeightSum ;
    }
    vecNeighborPts.clear() ;
    outNewPt.Z = dEstimateZ;
    LOGAddSuccessQuitMsg() ;
    return true ;
}


/**
 *@fn GetValueFromTins
 *@date 2012.02
 *@author �⿭
 *@brief ͨ����������ֵ�߳�����
 *@param vec3DPts �����������3ά����
 *@param tri ���ƹ������Ǹ�������
 *@param pNeigh ��ֵ����Χ���ڽӵ�
 *@param outNewPt ��ֵ��
 *@param bFlag ���ÿ�����ֵ�����ַ�ʽ
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlKringing::GetValueFromTin(const vector<Pt3d>& vec3DPts,triangulateio *tri,
                                  SINT *pNeigh , Pt3d& outNewPt , KRIGING_State bFlag)
{
    // �õ���ֵ�㸽���Ĳ��������ֵ�ĵ�
    vector<Pt3d> vecNeighborPts;
    GetNeighborVertexInMinDis(outNewPt , vec3DPts , tri , pNeigh , 4 ,vecNeighborPts) ;
    SINT nVertex = vecNeighborPts.size() ;
    // �жϿ�����ֵ�ķ�ʽ
    if(bFlag)
    {
        // �����ֵ�ĵ㲻�㣬�˳�
        if (nVertex < 4)
        {
            SCHAR strErr[] = "GetValueFromTin error : not enough neighboring points" ;
            LOGAddErrorMsg(strErr) ;
            return false;
        }
        CmlMat A, B ,W ;
        A.Initial(nVertex+1 , nVertex+1) ;
        B.Initial(nVertex+1 , 1) ;
        // ��ֵ��Ȩ��������
        for (SINT i=0; i<nVertex; i++)
        {
            A.SetAt(i, i , 0) ;
            A.SetAt(i, nVertex , 1) ;
            A.SetAt(nVertex, i, 1) ;
            B.SetAt(i , 0 , semivariogram(&(vecNeighborPts[i]), &outNewPt)) ;
        }

        A.SetAt(nVertex, nVertex , 0) ;
        B.SetAt(nVertex, 0 ,1) ;
        // Э���Ȩ�����������
        for(SINT i=0 ; i<nVertex-1 ; i++)
        {
            for(SINT j=i+1 ; j<nVertex ; j++)
            {
                A.SetAt(i , j , semivariogram(&(vecNeighborPts[i]), &(vecNeighborPts[j]))) ;
                A.SetAt(j , i , A.GetAt(i ,j)) ;
            }
        }
        // ��ֵ��Ȩ����
        CmlMat ATran , ATranA , ATranAInv , ATranB ;
        if(!mlMatTrans(&A , &ATran) || !mlMatMul(&ATran , &A , &ATranA) || !mlMatInv(&ATranA , &ATranAInv)
                ||!mlMatMul(&ATran , &B , &ATranB) || !mlMatMul(&ATranAInv , &ATranB , &W) )
        {
            SCHAR strErr[] = "GetValueFromTin error : correlation plus method fails" ;
            LOGAddErrorMsg(strErr) ;
            return false;
        }
        double dWeightSum = 0 ;
        double dEstimateZ= 0;
        double dWeightMax = -1000;
        // �������ո߳�ֵ
        for(SINT i=0 ; i<nVertex ; i++)
        {
            dWeightSum += W.GetAt(i,0);
            dWeightMax = max(dWeightMax, fabs(W.GetAt(i,0)));
        }
        if(dWeightMax == 0)
        {
            return false ;
        }
        for(SINT i=0 ; i<nVertex ; i++)
        {
            dEstimateZ += (W.GetAt(i,0) * vecNeighborPts[i].Z)/dWeightSum ;
        }
        vecNeighborPts.clear() ;
        outNewPt.Z = dEstimateZ;
//        LOGAddSuccessQuitMsg() ;
        return true ;
    }
    // ʧЧʱʹ���������
    else
    {
        CmlMat A, B ,W ;
        A.Initial(3,3) ;
        B.Initial(3,1) ;
        SINT vt[3];//�����ζ�����
        Pt3d dbPoint;
        // Э���Ȩ�����������
        for (SINT i=0; i<3; i++)
        {
            vt[i]=tri->triList[3*pNeigh[0]+i];
            dbPoint=vec3DPts[vt[i]];
            A.SetAt(i , 0 , dbPoint.X) ;
            A.SetAt(i , 1 , dbPoint.Y) ;
            A.SetAt(i , 2 , dbPoint.Z) ;
            B.SetAt(i , 0 , 1.0) ;
        }
        // ��ֵ��Ȩ����
        CmlMat ATran , ATranA , ATranAInv , ATranB ;
        if(!mlMatTrans(&A , &ATran) || !mlMatMul(&ATran , &A , &ATranA) || !mlMatInv(&ATranA , &ATranAInv)
                ||!mlMatMul(&ATran , &B , &ATranB) || !mlMatMul(&ATranAInv , &ATranB , &W) )
        {
            SCHAR strErr[] = "GetValueFromTin error : correlation method fails" ;
            LOGAddErrorMsg(strErr) ;
            return false;
        }
        if (W.GetAt(2,0) == 0)
        {
            return false;
        }
        // �������ո߳�ֵ
        double dEstimateZ= 0;
        dEstimateZ = (1 - W.GetAt(0,0) * outNewPt.X - W.GetAt(1,0) * outNewPt.Y )/ W.GetAt(2,0);
        vecNeighborPts.clear() ;
        outNewPt.Z = dEstimateZ;
//        LOGAddSuccessQuitMsg() ;
        return true ;
    }
}

/**
 *@fn GetNeighborVertexInMinDis
 *@date 2012.02
 *@author �⿭
 *@brief  ��������Χ���ڽӵ�
 *@param inPt Ŀ���
 *@param vec3DPts ��ά����
 *@param tri ��������������
 *@param pNeigh Ŀ�����Χ���ڽӵ�
 *@param nCount �ڽӵ���Ŀ
 *@param vecNeighborPts ���������ֵ���ڽӵ�
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlKringing::GetNeighborVertexInMinDis( Pt3d& inPt,const vector<Pt3d>& vec3DPts ,triangulateio *tri,
        SINT *pNeigh,SINT nCount,vector<Pt3d>& vecNeighborPts)
{
//    DOUBLE dDis ;
    DOUBLE x , y ;
    SINT vt[4][3];//�����ζ�����,�洢�����μ��������ڵ����������εĶ���
    x = inPt.X ;
    y = inPt.Y ;
    //�õ����������ε���������
    for (SINT j=0; j<3; j++)
    {
        vt[0][j] = tri->triList[3*pNeigh[0]+j];
        vecNeighborPts.push_back(vec3DPts[vt[0][j]]) ;
    }
//    //�õ����������εĶ���
    for (SINT i=1; i<nCount; i++)
    {
        if (pNeigh[i]<0)
        {
            continue;
        }
        for (SINT j=0; j<3; j++)
        {
            vt[i][j] = tri->triList[3*pNeigh[i]+j];
            if (VertexNotInTriangle(vt[i][j],vt[0]))
            {
                vecNeighborPts.push_back(vec3DPts[vt[i][j]]) ;
            }
        }
    }
    return true ;
}

/**
 *@fn VertexNotInTriangle
 *@date 2012.02
 *@author �⿭
 *@brief �жϵ��Ƿ�����������
 *@param nVt ���жϵ�������
 *@param Vertexs ��������������������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

bool CmlKringing::VertexNotInTriangle(SINT nVt,SINT *Vertexs)
{
    bool bIn=true;
    for (SINT i=0; i<3; i++)
    {
        if (Vertexs[i]==nVt)
        {
            bIn=false;
            break;
        }
    }
    return bIn;
}


/**
 *@fn semivariogram()
 *@date 2012.02
 *@author �⿭
 *@brief ���������ֵ��������ϵ��
 *@param *p1 ��1�ĵ�������
 *@param *p2 ��2�ĵ�������
 *@param m_eKrigingModel ������ֵģ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
double CmlKringing::semivariogram(Pt3d *p1, Pt3d *p2 , KRIGING_MODEL m_eKrigingModel)
{
    // ���ݲ��õĶ���ʽģ�ͼ���Ȩ����
    double dSemiVariogram = 0.0;
    double dDistance = sqrt((p1->X - p2->X) * (p1->X - p2->X) + (p1->Y - p2->Y) * (p1->Y - p2->Y) );
    // ����ʽģ��
    if(m_eKrigingModel == POLYNOMIANL)
    {
        if(dDistance < m_dDisShort)
        {
            dSemiVariogram = ((m_dShortPara[0] * dDistance + m_dShortPara[1]) * dDistance + m_dShortPara[2]) * dDistance + m_dShortPara[3];
        }
        else
        {
            dSemiVariogram = ((m_dLongPara[0] * dDistance + m_dLongPara[1]) * dDistance + m_dLongPara[2]) * dDistance + m_dLongPara[3];
        }
    }
    // ���������ģ��
    else if(m_eKrigingModel == SPHERICAL)
    {
        dSemiVariogram = m_dSphericalPara * (3 * dDistance / 2 / m_dRange - pow(dDistance, 3) / 2 / pow(m_dRange, 3));
    }
    // ���������ָ��ģ��
    else if(m_eKrigingModel == SPHERICAL_EXPONENTIAL)
    {
        double	dSemiVariogramSpherical = m_dSphericalPara * (3 * dDistance / 2 / m_dRange - pow(dDistance, 3) / 2 / pow(m_dRange, 3)),
                                          dSemiVariogramExponential = (1 - exp(dDistance/m_dRange)) * m_dExponentialPara ;
        double dRatio;
        if(dDistance < m_dGraceStart)
            dSemiVariogram = dSemiVariogramSpherical;
        else if(dDistance > m_dGraceEnd)
            dSemiVariogram = dSemiVariogramExponential;
        else
        {
            dRatio = (dDistance - m_dGraceStart) / (m_dGraceEnd - m_dGraceStart);
            dSemiVariogram = (1 - dRatio) * dSemiVariogramSpherical + dRatio * dSemiVariogramExponential;
        }
    }
    return dSemiVariogram;
}



