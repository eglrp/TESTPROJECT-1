/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlCoordTrans.cpp
* @date 2011.11.18
* @author ������
* @brief ����ת���㷨��ʵ���ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#include "mlCoordTrans.h"
/**
 *@fn CmlCoordTrans()
 *@date 2011.11
 *@author ������
 *@brief ����ת���๹�캯��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
*/
CmlCoordTrans::CmlCoordTrans()
{
    //ctor
}


/**
 *@fn CmlCoordTrans()
 *@date 2011.11
 *@author ������
 *@brief ����ת������������
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
*/
CmlCoordTrans::~CmlCoordTrans()
{
    //dtor
}


/**
 *@fn mlCoordTransResult
 *@date 2012.02
 *@author ������
 *@brief ���ݸ�������ת�����ƽ���������ת���������
 *@param pArr ������������ָ��
 *@param nDim ����ά��
 *@param pRotateMat ��ת����ָ��
 *@param pTransVec ƽ������ָ��
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

bool CmlCoordTrans::mlCoordTransResult(DOUBLE* pArr, SINT nDim, CmlMat* pRotateMat, DOUBLE* pTransVec, DOUBLE* pTransResult,SINT nflag)
{
    if(nDim != SINT(pRotateMat->GetH())  && nDim != SINT(pRotateMat->GetW()))          //�жϾ����Ƿ�Ϊ����
    {
//        cout << "coordinates dimension and matrix doesn't match!\n" << endl;
//        SCHAR strErr[] = "mlCamCalib error : iteration fails to converge within the threshhold \t" ;
//        LOGAddErrorMsg(strErr) ;
        SCHAR strErr[] = "coordinates dimension and matrix doesn't match!\n";
        LOGAddErrorMsg(strErr);
        return false;

    }
    else
    {
       // CmlMat cordinateMat, resultMat;
        CmlMat matCoordinates;
        CmlMat matResult;
        matCoordinates.Initial(nDim, 1);
        matResult.Initial(nDim,1);
        for(SINT i = 0; i < nDim; i++)
        {
            matCoordinates.SetAt(i,0,*(pArr + i));

        }
        if(nflag == 0)               // B = R*A + T  ��A��B
        {
            mlMatMul(pRotateMat, &matCoordinates,&matResult);
            for(SINT i = 0; i < nDim; i++)
            {
                *(pTransResult + i) = matResult.GetAt(i,0) + *(pTransVec + i);
            }

        }
        else               // B = R*A + T  ��B��A
        {
            CmlMat matsub,matTransVec,matRInv;
            matTransVec.Initial(nDim,1);
            for(SINT i = 0; i < nDim; i++)
            {
                matTransVec.SetAt(i,0,*(pTransVec+i));

            }
            mlMatSub(&matCoordinates,&matTransVec,&matsub);
            mlMatInv(pRotateMat,&matRInv);      //��������
            mlMatMul(&matRInv,&matsub,&matResult);
            for(SINT j = 0; j < nDim; j++)
            {
                *(pTransResult+j) = matResult.GetAt(j,0);
            }
        }

//        LOGAddSuccessQuitMsg();
        return true;
    }

}


/**
 *@fn mlCalcTransMatrixByXYZ
 *@date 2011.11
 *@author ������
 *@brief ������ʵ���¹�ϵ���ֲ�����ϵת����ϵ���
 *@param pLocResult ��½�����¹�ϵ�µþ�ȷ��λ���
 *@param pTransMat  �洢ת������ת����
 *@param pTransVec  �洢ƽ������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

*/


bool CmlCoordTrans::mlCalcTransMatrixByXYZ(Pt3d* pLocResult,CmlMat* pTransMat, DOUBLE* pTransVec)
{
	if ( false == pTransMat->IsValid())
	{
      //�ռ�����ת������γ��
        DOUBLE dfai = 0.0;         //γ��
        DOUBLE dL = 0.0;
        pTransMat->Initial(3,3);
        DOUBLE dR = sqrt( (pLocResult->X) * (pLocResult->X)
                + (pLocResult->Y)*(pLocResult->Y) + (pLocResult->Z)*(pLocResult->Z) );

        if (pLocResult->X == 0 && pLocResult->Z ==0 )    //��½��X=0ʱ���������  pTransMat��ʾ��֪�ֲ���������¹�ϵ������ľ���
        {
            if(pLocResult->Y > 0)    //����90��
            {
                dfai = Deg2Rad(0);
                dL = Deg2Rad(90.0);
            }
            else                       //pLocResult->Y < 0 ����
            {
                dfai = Deg2Rad(0.0);
                dL = Deg2Rad(-90.0);
            }
        }
        else
        {
          //�ռ�����ת������γ��
             dfai = asin(pLocResult->Z/dR);          //γ��
             dL = atan(pLocResult->Y / pLocResult->X);  //����
        }

        //��ת�������
        pTransMat->SetAt(0,0,-cos(dL) * sin(dfai));
        pTransMat->SetAt(0,1,-sin(dL));
        pTransMat->SetAt(0,2,-cos(dL) * cos(dfai));
        pTransMat->SetAt(1,0,-sin(dL) * sin(dfai));
        pTransMat->SetAt(1,1,cos(dL));
        pTransMat->SetAt(1,2,-sin(dL) * cos(dfai));
        pTransMat->SetAt(2,0,cos(dfai));
        pTransMat->SetAt(2,1,0);
        pTransMat->SetAt(2,2,-sin(dfai));

        //ƽ��������
        *pTransVec = pLocResult->X;
        *(pTransVec + 1) = pLocResult->Y;
        *(pTransVec + 2) = pLocResult->Z;

        LOGAddSuccessQuitMsg();
        return true;
    }
	else
	{
	  //  LOGAddNoticeMsg( pLog, "s" );
        SCHAR strMsg[] = "Error in pTransMat!\n";
        LOGAddErrorMsg(strMsg);
        return false;
	}
}

/**
 *@fn mlCalcTransMatrixByLatLong
 *@date 2011.11
 *@author ������
 *@brief ���������ݶ�λ�ľ�γ��ʵ���¹�ϵ���ֲ�����ϵת����ϵ���
 *@param dLat ��λ��γ��  ��λΪ��   ��ΧΪ-90�ȡ�90��  ��γΪ�� ��γΪ��
 *@param dLong ��λ�ľ��� ��λΪ��   ��ΧΪ-180-180��  ����Ϊ�� ����Ϊ��
 *@param pTransMat  �洢ת������ת����
 *@param pTransVec  �洢ƽ������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.0
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

*/
bool CmlCoordTrans::mlCalcTransMatrixByLatLong(double dLat,double dLong,CmlMat* pTransMat, DOUBLE* pTransVec)
{
    double dfai = Deg2Rad(dLat);  //γ�Ȼ��ȣ�
    double dL = Deg2Rad(dLong);   //���Ȼ���
    pTransMat->Initial(3,3);

    pTransMat->SetAt(0,0,-cos(dL) * sin(dfai));
    pTransMat->SetAt(0,1,-sin(dL));
    pTransMat->SetAt(0,2,-cos(dL) * cos(dfai));
    pTransMat->SetAt(1,0,-sin(dL) * sin(dfai));
    pTransMat->SetAt(1,1,cos(dL));
    pTransMat->SetAt(1,2,-sin(dL) * cos(dfai));
    pTransMat->SetAt(2,0,cos(dfai));
    pTransMat->SetAt(2,1,0);
    pTransMat->SetAt(2,2,-sin(dfai));

    double X,Y,Z;           //���ݾ�γ�ȼ���X Y Z
    X = ML_MoonRadius*cos(dfai)*cos(dL);
    Y = ML_MoonRadius*cos(dfai)*sin(dL);
    Z = ML_MoonRadius*sin(dfai);

    *pTransVec = X;
    *(pTransVec+1) = Y;
    *(pTransVec+2) = Z;

    LOGAddSuccessQuitMsg();
    return true;


}




