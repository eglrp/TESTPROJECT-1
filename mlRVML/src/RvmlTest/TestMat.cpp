/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestMat.cpp
* @date 2012.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��������������Դ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#include "TestMat.h"
#include "../mlRVML/mlMat.h"
#include "../mlRVML/mlBase.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CTestMat,"alltest" );
/**
* @fn CTestMat
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ղι��캯��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
CTestMat::CTestMat()
{
    //ctor
}
/**
* @fn ~CTestMat
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
CTestMat::~CTestMat()
{
    //dtor
}

/**
* @fn setup()
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ϵͳĬ�ϵĳ�ʼ������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestMat::setUp()
{

}
/**
* @fn tearDown()
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ϵͳĬ�ϵ����ٺ���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestMat::tearDown()
{

}
/**
@fn TestmlMat2CvMat_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Խ�CmlMatת����CvMat����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMat2CvMat_ok()
{
    OriAngle Ori;
    Ori.omg = 0.3;
    Ori.phi = 0.5;
    Ori.kap = 0.8;
    CmlMat RMat;
    OPK2RMat(  &Ori, &RMat );
    CvMat* pcvMat = cvCreateMat( 3, 3, CV_64F );
    bool result = mlMat2CvMat( &RMat, pcvMat);
    cvReleaseMat(&pcvMat);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestCvMat2mlMat_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Խ�CvMatת����CmlMat����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestCvMat2mlMat_ok()
{
    OriAngle Ori;
    Ori.omg = 0.3;
    Ori.phi = 0.5;
    Ori.kap = 0.8;
    CmlMat RMat,mlMat;
    OPK2RMat(  &Ori, &RMat );
    CvMat* pcvMat = cvCreateMat( 3, 3, CV_64F );
    mlMat2CvMat( &RMat, pcvMat);
    mlMat.Initial(3,3);
    bool result = CvMat2mlMat(pcvMat,&mlMat);
    cvReleaseMat(&pcvMat);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestmlMatTrans_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Ծ���ת�ù���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMatTrans_ok()
{
    OriAngle Ori;
    Ori.omg = 0.3;
    Ori.phi = 0.5;
    Ori.kap = 0.8;
    CmlMat RMat,TransMat;
    OPK2RMat(  &Ori, &RMat );
    bool result = mlMatTrans(&RMat,&TransMat);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestmlMatAdd_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Ծ���ӷ�����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMatAdd_ok()
{
    OriAngle Ori1, Ori2;
    Ori1.omg = 0.3;    Ori1.phi = 0.5;    Ori1.kap = 0.8;
    Ori2.omg = 0.4;    Ori2.phi = 0.6;    Ori2.kap = 0.9;
    CmlMat RMat1,RMat2,RMatOut;
    OPK2RMat(  &Ori1, &RMat1 );
    OPK2RMat(  &Ori2, &RMat2 );
    bool result = mlMatAdd(&RMat1,&RMat2,&RMatOut);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestmlMatSub_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Ծ����������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMatSub_ok()
{
    OriAngle Ori1, Ori2;
    Ori1.omg = 0.3;    Ori1.phi = 0.5;    Ori1.kap = 0.8;
    Ori2.omg = 0.4;    Ori2.phi = 0.6;    Ori2.kap = 0.9;
    CmlMat RMat1,RMat2,RMatOut;
    OPK2RMat(  &Ori1, &RMat1 );
    OPK2RMat(  &Ori2, &RMat2 );
    bool result = mlMatSub(&RMat1,&RMat2,&RMatOut);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestmlMatMul_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Ծ���˷�����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMatMul_ok()
{
    OriAngle Ori1, Ori2;
    Ori1.omg = 0.3;    Ori1.phi = 0.5;    Ori1.kap = 0.8;
    Ori2.omg = 0.4;    Ori2.phi = 0.6;    Ori2.kap = 0.9;
    CmlMat RMat1,RMat2,RMatOut;
    OPK2RMat(  &Ori1, &RMat1 );
    OPK2RMat(  &Ori2, &RMat2 );
    bool result = mlMatMul(&RMat1,&RMat2,&RMatOut);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestmlMatInv_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Ծ������湦��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMatInv_ok()
{
    OriAngle Ori;
    Ori.omg = 0.3;
    Ori.phi = 0.5;
    Ori.kap = 0.8;
    CmlMat RMat,InvMat;
    OPK2RMat(  &Ori, &RMat );
    bool result = mlMatInv(&RMat,&InvMat);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestmlMatDet_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������������ʽֵ����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMatDet_ok()
{
    OriAngle Ori;
    Ori.omg = 0.3;
    Ori.phi = 0.5;
    Ori.kap = 0.8;
    CmlMat RMat;
    DOUBLE res;
    OPK2RMat(  &Ori, &RMat );
    bool result = mlMatDet(&RMat,res);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestmlMatSolveSVD_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Խⷽ��A*x=B����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMatSolveSVD_ok()
{
    CmlMat RMat1,RMat2,RMatOut;
    OriAngle Ori1;
    Ori1.omg = 0.3;    Ori1.phi = 0.5;    Ori1.kap = 0.8;
    OPK2RMat(  &Ori1, &RMat1 );
    RMat2.Initial(3,1);
    RMat2.SetAt(0,0,4);    RMat2.SetAt(1,0,5);    RMat2.SetAt(2,0,6);
    bool result = mlMatSolveSVD(&RMat1,&RMat2,&RMatOut);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestmlMatSVD_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����SVD�ֽ⹦��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMatSVD_ok()
{
    OriAngle Ori;
    Ori.omg = 0.3;
    Ori.phi = 0.5;
    Ori.kap = 0.8;
    CmlMat RMat,MatU,MatW,MatV;
    DOUBLE res;
    OPK2RMat(  &Ori, &RMat );
    bool result = mlMatSVD( &RMat,&MatU, &MatW, &MatV );
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestmlMatCross3_ok
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ������ά������˹���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestMat::TestmlMatCross3_ok()
{
    CmlMat RMat1,RMat2,RMatOut;
    RMat1.Initial(3,1);
    RMat1.SetAt(0,0,1);    RMat1.SetAt(1,0,2);    RMat1.SetAt(2,0,3);
    RMat2.Initial(3,1);
    RMat2.SetAt(0,0,4);    RMat2.SetAt(1,0,5);    RMat2.SetAt(2,0,6);
    bool result = mlMatCross3( &RMat1,&RMat2, &RMatOut );
    CPPUNIT_ASSERT(result == true);
}




