/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlMat.cpp
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �����������Դ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/

#include "mlBase.h"
#include "mlMat.h"



/**
* @fn mlMatTrans
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ת��
* @param pMatIn �������
* @param pMatOut �������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlMatTrans(  CmlMat* pMatIn, CmlMat* pMatOut )
{
    if(  false == pMatIn->IsValid() )
    {
        return false;
    }
    if( false == pMatOut->IsValid() )
    {
        pMatOut->Initial( pMatIn->GetW(), pMatIn->GetH() );
    }
    else
    {
        if( ( pMatIn->GetH() != pMatOut->GetW() )||( pMatIn->GetW() != pMatOut->GetH() ) )
        {
            return false;
        }
    }


    for( UINT i = 0; i < pMatOut->GetH(); ++i )
    {
        for( UINT j = 0; j < pMatOut->GetW(); ++j )
        {
            pMatOut->SetAt( i, j, pMatIn->GetAt( j, i ) );
        }
    }
    return true;
};
/**
* @fn mlMatAdd
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ӷ�
* @param pMatInA �������A
* @param pMatInB �������B
* @param pMatOutC ����������C
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlMatAdd( CmlMat* pMatInA, CmlMat* pMatInB, CmlMat* pMatOutC )
{
    if( ( false == pMatInA->IsValid() )||( false == pMatInB->IsValid() ) )
    {
        return false;
    }
    if( false == pMatOutC->IsValid() )
    {
        pMatOutC->Initial( pMatInA->GetH(), pMatInA->GetW() );
    }
    else
    {
        if( ( pMatInA->GetH() != pMatOutC->GetH() )||( pMatInA->GetW() != pMatOutC->GetW() ) )
        {
            return false;
        }
    }

    if( ( pMatInA->GetH() != pMatInB->GetH() )||( pMatInA->GetW() != pMatInB->GetW() ) )
    {
        return false;
    };

     for( UINT i = 0; i < pMatOutC->GetH(); ++i )
    {
        for( UINT j = 0; j < pMatOutC->GetW(); ++j )
        {
            pMatOutC->SetAt( i, j, ( pMatInA->GetAt( i, j ) +  pMatInB->GetAt( i, j ) ) );
        }
    }
    return true;
};
/**
* @fn mlMatSub
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������
* @param pMatInA �������A
* @param pMatInB �������B
* @param pMatOutC ����������C
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlMatSub( CmlMat* pMatInA, CmlMat* pMatInB, CmlMat* pMatOutC )
{
    if( ( false == pMatInA->IsValid() )||( false == pMatInB->IsValid() ) )
    {
        return false;
    }
    if( false == pMatOutC->IsValid() )
    {
        pMatOutC->Initial( pMatInA->GetH(), pMatInA->GetW() );
    }
    else
    {
        if( ( pMatInA->GetH() != pMatOutC->GetH() )||( pMatInA->GetW() != pMatOutC->GetW() ) )
        {
            return false;
        }
    }

    for( UINT i = 0; i < pMatOutC->GetH(); ++i )
    {
        for( UINT j = 0; j < pMatOutC->GetW(); ++j )
        {
            pMatOutC->SetAt( i, j, ( pMatInA->GetAt( i, j ) -  pMatInB->GetAt( i, j ) ) );
        }
    }
    return true;
};
/**
* @fn mlMatMul
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����˷�
* @param pMatInA �������A
* @param pMatInB �������B
* @param pMatOutC ����������C
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlMatMul( CmlMat* pMatInA, CmlMat* pMatInB, CmlMat* pMatOutC )
{
    if( ( false == pMatInA->IsValid() )||( false == pMatInB->IsValid() ) )
    {
        return false;
    }
    if( pMatInA->GetW() != pMatInB->GetH() )
    {
        return false;
    };
    if( false == pMatOutC->IsValid() )
    {
        pMatOutC->Initial( pMatInA->GetH(), pMatInB->GetW() );
    }
    else
    {
        if( ( pMatInA->GetH() != pMatOutC->GetH() )||( pMatInB->GetW() != pMatOutC->GetW() ) )
        {
            return false;
        }
    }
    for( UINT i = 0; i < pMatOutC->GetH(); ++i )
    {
        for( UINT j = 0; j < pMatOutC->GetW(); ++j )
        {
            DOUBLE dTmp = 0;
            for( UINT k = 0; k < pMatInA->GetW(); ++k )
            {
                dTmp += ( pMatInA->GetAt( i, k ) * pMatInB->GetAt( k, j ) );
            }
            pMatOutC->SetAt( i, j, dTmp );
        }
    }
    return true;
};
/**
* @fn mlMatInv
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��������
* @param pMatIn �������
* @param pMatOut �������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlMatInv( CmlMat* pMatIn, CmlMat* pMatOut )
{
    //if( ( false == pMatIn->IsValid() ) )
    //{
    //    return false;
    //}
    //if( pMatIn->GetH() != pMatIn->GetW() )
    //{
    //    return false;
    //}

    //if( false == pMatOut->IsValid() )
    //{
    //    pMatOut->Initial( pMatIn->GetH(),pMatIn->GetH() );
    //}
    //else
    //{
    //    if( ( pMatOut->GetH() != pMatIn->GetH() )||( pMatOut->GetW() != pMatIn->GetW() ) )
    //    {
    //        return false;
    //    }
    //}

    //CvMat* pIn = cvCreateMat( pMatIn->GetH(), pMatIn->GetW(), CV_64F );
    //CvMat* pOut = cvCreateMat( pMatIn->GetH(), pMatIn->GetW(), CV_64F );

    //mlMat2CvMat( pMatIn, pIn );
    //cvInv( pIn, pOut, CV_QR );
    //CvMat2mlMat( pOut, pMatOut );

    //cvReleaseMat( &pIn );
    //cvReleaseMat( &pOut );

    return true;
};
/**
* @fn mlMatDet
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���������ʽֵ
* @param pMat �������
* @param dRes ����ʽ��ֵ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlMatDet( CmlMat* pMat, DOUBLE &dRes )
{
    //if( ( false == pMat->IsValid() )||( pMat->GetH() != pMat->GetW() ) )
    //{
    //    return false;
    //}

    //CvMat* pIn = cvCreateMat( pMat->GetH(), pMat->GetW(), CV_64F );

    //mlMat2CvMat( pMat, pIn );
    //dRes = cvmDet(pIn);

    //cvReleaseMat( &pIn );
    return true;

};
/**
* @fn mlMatSolveSVD
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ⷽ��A*x=B
* @param pMatInA �������A
* @param pMatInB �������B
* @param pMatOutX ����������X
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlMatSolveSVD(  CmlMat* pMatInA,  CmlMat* pMatInB, CmlMat* pMatOutX )
{
    //if( ( false == pMatInA->IsValid() )||( false == pMatInB->IsValid() ) )
    //{
    //    return false;
    //}
    //if( ( pMatInA->GetH()!= pMatInB->GetH())||( pMatInB->GetW() != 1 ) )
    //{
    //    return false;
    //}

    //if( false == pMatOutX->IsValid() )
    //{
    //    pMatOutX->Initial( pMatInA->GetW(), 1 );
    //}
    //else
    //{
    //    if( ( pMatOutX->GetH() != pMatInA->GetW() )||( pMatOutX->GetW() != 1 ) )
    //    {
    //        return false;
    //    }
    //}

    //CvMat* pInA = cvCreateMat( pMatInA->GetH(), pMatInA->GetW(), CV_64F );
    //CvMat* pInB = cvCreateMat( pMatInB->GetH(), pMatInB->GetW(), CV_64F );
    //CvMat* pInX = cvCreateMat( pMatInA->GetW(), pMatInB->GetW(), CV_64F );

    //mlMat2CvMat( pMatInA, pInA );
    //mlMat2CvMat( pMatInB, pInB );

    //cvSolve( pInA, pInB, pInX, CV_SVD );

    //CvMat2mlMat( pInX, pMatOutX );

    //cvReleaseMat( &pInA );
    //cvReleaseMat( &pInB );
    //cvReleaseMat( &pInX );

    return true;

};
/**
* @fn mlMatSVD
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief SVD�ֽ⣬A=U*W*V'
* @param pMatA �������A
* @param pMatU �������U
* @param pMatW �������W
* @param pMatV �������V
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlMatSVD( CmlMat* pMatA, CmlMat* pMatU, CmlMat* pMatW, CmlMat* pMatV )
{
 /*   if( ( pMatA == NULL )||( pMatU == NULL ) || ( pMatW == NULL ) ||( pMatV == NULL ) )
    {
        return false;
    }
    if( ( pMatA->IsValid() == false )||( pMatU->IsValid() == true )||( pMatW->IsValid() == true )||( pMatV->IsValid() == true ) )
    {
        return false;
    }

    CvMat* pCvMatA = cvCreateMat( pMatA->GetH(), pMatA->GetW(), CV_64F );

    mlMat2CvMat( pMatA, pCvMatA );

    CvMat* pCvMatU = cvCreateMat( pMatA->GetH(), pMatA->GetH(), CV_64F );
    CvMat* pCvMatW = cvCreateMat( pMatA->GetH(), pMatA->GetW(), CV_64F );
    CvMat* pCvMatV = cvCreateMat( pMatA->GetW(), pMatA->GetW(), CV_64F );

    cvSVD( pCvMatA, pCvMatW, pCvMatU, pCvMatV );

    if( ( pMatU->IsValid() == true )||( pMatW->IsValid() == true )||( pMatV->IsValid() == true ) )
    {
        return false;
    }
    pMatU->Initial( pMatA->GetH(), pMatA->GetH() );
    pMatW->Initial( pMatA->GetH(), pMatA->GetW() );
    pMatV->Initial( pMatA->GetW(), pMatA->GetW() );

    CvMat2mlMat( pCvMatU, pMatU );
    CvMat2mlMat( pCvMatW, pMatW );
    CvMat2mlMat( pCvMatV, pMatV );

    cvReleaseMat( &pCvMatA );
    cvReleaseMat( &pCvMatU );
    cvReleaseMat( &pCvMatW );
    cvReleaseMat( &pCvMatV );*/

    return true;
}
/**
* @fn mlMatCross3
* @date 2011.11.02
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��ά�������
* @param pMatInA ������ά����A
* @param pMatInB ������ά����B
* @param pMatOutC ����������C
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlMatCross3(CmlMat* pMatInA , CmlMat* pMatInB , CmlMat* pMatOutC)
{
     if( ( false == pMatInA->IsValid() )||( false == pMatInB->IsValid() ) )
    {
        return false;
    }
    if( (pMatInA->GetW() != 1) || (pMatInB->GetW() != 1) || (pMatInA->GetH() != 3) || (pMatInB->GetH() != 3) )
    {
        return false;
    }
    if( false == pMatOutC->IsValid() )
    {
        pMatOutC->Initial( 3, 3 );
    }
    else
    {
        if( ( 3 != pMatOutC->GetH() ) || ( 1 != pMatOutC->GetW() ) )
        {
            return false;
        }
    }
    //(b1c2-b2c1,c1a2-a1c2,a1b2-a2b1)
    pMatOutC->SetAt( 0, 0, pMatInA->GetAt(1, 0) * pMatInB->GetAt(2, 0) - pMatInB->GetAt(1, 0) * pMatInA->GetAt(2, 0) );
    pMatOutC->SetAt( 1, 0, pMatInA->GetAt(2, 0) * pMatInB->GetAt(0, 0) - pMatInA->GetAt(0, 0) * pMatInB->GetAt(2, 0) );
    pMatOutC->SetAt( 2, 0, pMatInA->GetAt(0, 0) * pMatInB->GetAt(1, 0) - pMatInB->GetAt(0, 0) * pMatInA->GetAt(1, 0) );

    return true;

}

ML_EXTERN_C bool mlMatMulTrans( CmlMat* pMatA, CmlMat* pMatRes )
{
 /*   if( ( NULL == pMatA )||( NULL == pMatRes) )
    {
        return false;
    }
    if( false == pMatA->IsValid() )
    {
        return false;
    }
    CvMat* pCvMatA = cvCreateMat( pMatA->GetH(), pMatA->GetW(), CV_64F );

    mlMat2CvMat( pMatA, pCvMatA );

    CvMat* pCvMatRes = cvCreateMat( pMatA->GetW(), pMatA->GetW(), CV_64F );

    cvMulTransposed( pCvMatA, pCvMatRes, 1 );

    if( pMatRes->IsValid() == false )
    {
        pMatRes->Initial( pMatA->GetW(), pMatA->GetW() );
    }
    else
    {
        if( ( pMatRes->GetW() != pMatA->GetW() )||( pMatRes->GetH() != pMatA->GetW() ) )
        {
            return false;
        }
    }

    CvMat2mlMat( pCvMatRes, pMatRes );


    cvReleaseMat( &pCvMatA );
    cvReleaseMat( &pCvMatRes );*/

    return true;
}
ML_EXTERN_C bool mlMatMulTransInv( CmlMat* pMatA, CmlMat* pMatRes )
{
 /*   if( ( NULL == pMatA )||( NULL == pMatRes) )
    {
        return false;
    }
    if( false == pMatA->IsValid() )
    {
        return false;
    }
    CvMat* pCvMatA = cvCreateMat( pMatA->GetH(), pMatA->GetW(), CV_64F );

    mlMat2CvMat( pMatA, pCvMatA );

    CvMat* pCvMatATA = cvCreateMat( pMatA->GetW(), pMatA->GetW(), CV_64F );

    CvMat* pCvMatRes = cvCreateMat( pMatA->GetW(), pMatA->GetW(), CV_64F );

    cvMulTransposed( pCvMatA, pCvMatATA, 1 );

    cvReleaseMat( &pCvMatA );

    cvInv( pCvMatATA, pCvMatRes, CV_SVD );

    cvReleaseMat( &pCvMatATA );

    if( pMatRes->IsValid() == false )
    {
        pMatRes->Initial( pMatA->GetW(), pMatA->GetW() );
    }
    else
    {
        if( ( pMatRes->GetW() != pMatA->GetW() )||( pMatRes->GetH() != pMatA->GetW() ) )
        {
            return false;
        }
    }

    CvMat2mlMat( pCvMatRes, pMatRes );

    cvReleaseMat( &pCvMatRes );*/

    return true;
}




