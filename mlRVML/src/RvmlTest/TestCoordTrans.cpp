#include "TestCoordTrans.h"
#include "../mlRVML/mlCoordTrans.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CTestCoordTrans,"alltest" );

CTestCoordTrans::CTestCoordTrans()
{
    //ctor
}

CTestCoordTrans::~CTestCoordTrans()
{
    //dtor
}
/** @brief TestmlCoordTrans
  *
  * @todo: document this function
  */

/**
* @fn TestmlCoordTrans_OK()
* @date 2011.12.1
* @author ������
* @brief �������������ȷʱ�¹�ϵ���ֲ�����ϵת������
* @version 1.1
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestCoordTrans::TestmlCoordTrans_OK()
{
    CmlCoordTrans cls;
    //bool result = cls.mlCoordTrans("","");
    //mlCalcTransMatrixByXYZ(Pt3d* pLocResult,CmlMat* pTransMat, DOUBLE* pTransVec)
    Pt3d LocResult;
    LocResult.X = 1737.4;
    LocResult.Y = 0;
    LocResult.Z = 0;
    CmlMat transMat;
    DOUBLE transVec[3];

    bool result = cls.mlCalcTransMatrixByXYZ(&LocResult,&transMat,transVec);
    CPPUNIT_ASSERT(result == true);


}

void CTestCoordTrans::TestmlCalcTransMatrix_case2()
{
    Pt3d LocResult;
    LocResult.X = 0;
    LocResult.Y = -1737.4;
    LocResult.Z = 0;

    CmlMat transMat;
    DOUBLE transVec[3];
    CmlCoordTrans cls;

    bool result = cls.mlCalcTransMatrixByXYZ(&LocResult,&transMat,transVec);
    CPPUNIT_ASSERT(result == true);


}


void CTestCoordTrans::TestmlCalcTransMatrix_case3()
{
    Pt3d LocResult;
    LocResult.X = 0;
    LocResult.Y = 1737.4;
    LocResult.Z = 0;

    CmlMat transMat;
    DOUBLE transVec[3];
    CmlCoordTrans cls;

    bool result = cls.mlCalcTransMatrixByXYZ(&LocResult,&transMat,transVec);
    CPPUNIT_ASSERT(result == true);

}


void CTestCoordTrans::TestmlCalcTransMatrix_case4()
{
    Pt3d LocResult;
    LocResult.X = 265;
    LocResult.Y = 352;
    LocResult.Z = 652;

    CmlMat transMat;
    DOUBLE transVec[3];
    CmlCoordTrans cls;

    bool result = cls.mlCalcTransMatrixByXYZ(&LocResult,&transMat,transVec);
    CPPUNIT_ASSERT(result == true);

}

void CTestCoordTrans::TestmlCalcTransMatrixByLatLong()
{
    DOUBLE dLat = 45;
    DOUBLE dLong = 60;
    CmlMat transMat;
    DOUBLE transVec[3];
    CmlCoordTrans cls;
    bool result = cls.mlCalcTransMatrixByLatLong(dLat,dLong,&transMat,transVec);
    CPPUNIT_ASSERT(result == true);

}


/**
* @fn TestmlCoordTransResult1_OK()
* @date 2011.12.1
* @author ������
* @brief �������������ȷʱ����ת�����ܣ����㣩
* @version 1.1
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/

void CTestCoordTrans::TestmlCoordTransResult1_OK()
{
    CmlCoordTrans cls;
    double dArr[3] = {2,3,1};
    SINT nDim = 3;
    double transVec[3] = {1,1,3};
    CmlMat rotateMat;
    rotateMat.Initial(3,3);
    double transrst[3];
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        rotateMat.SetAt(i,j,i+j);
    }
    SINT nflag = 1;
    bool result = cls.mlCoordTransResult(dArr,nDim,&rotateMat,transVec,transrst,nflag);
    CPPUNIT_ASSERT(result == true);

}

/**
* @fn TestmlCoordTransResult2_OK()
* @date 2011.12.1
* @author ������
* @brief �������������ȷʱ����ת�����ܣ����㣩
* @version 1.1
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestCoordTrans::TestmlCoordTransResult2_OK()
{
    CmlCoordTrans cls;
    double dArr[3] = {2,3,1};
    SINT nDim = 3;
    double transVec[3] = {1,1,3};
    CmlMat rotateMat;
    rotateMat.Initial(3,3);
    double transrst[3];
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        rotateMat.SetAt(i,j,i+j);
    }
    SINT nflag = 2;
    bool result = cls.mlCoordTransResult(dArr,nDim,&rotateMat,transVec,transrst,nflag);
    CPPUNIT_ASSERT(result == true);

}

void CTestCoordTrans::TestmlCoordTransResult1_abnormal1()
//��ת����ά��������ά�������
{
    CmlCoordTrans cls;
    double dArr[3] = {2,3,1};
    SINT nDim = 4;
    double transVec[3] = {1,1,3};
    CmlMat rotateMat;
    rotateMat.Initial(3,3);
    double transrst[3];
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        rotateMat.SetAt(i,j,i+j);
    }
    SINT nflag = 2;
    bool result = cls.mlCoordTransResult(dArr,nDim,&rotateMat,transVec,transrst,nflag);
    CPPUNIT_ASSERT(result == false);


}

/** @brief TearDown
  *
  * @todo: document this function
  */
void CTestCoordTrans::tearDown()
{

}

/** @brief SetUp
  *
  * @todo: document this function
  */
void CTestCoordTrans::setUp()
{

}

