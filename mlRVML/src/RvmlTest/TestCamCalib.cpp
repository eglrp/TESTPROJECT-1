#include "TestCamCalib.h"
#include "../../../src/mlRVML/mlCamCalib.h"
#include "../../../src/RvmlDemo/camCalibIO.h"


CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CTestCamCalib,"alltest" );

CTestCamCalib::CTestCamCalib()
{
    //ctor
}

CTestCamCalib::~CTestCamCalib()
{
    //dtor
}

/** @brief tearDown
  *
  * @todo: document this function
  */
void CTestCamCalib::tearDown()
{

}

/** @brief setUp
  *
  * @todo: document this function
  */
void CTestCamCalib::setUp()
{

}

/**
* @fn TestmlSingleCamCalib_OK()
* @date 2012.02
* @author �⿭
* @brief ���Ե�����궨��������
* @version 1.1
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestCamCalib::TestmlSingleCamCalib_OK()
{
    CCamCalibIO camIO;
    char* strInputPath = "../../../UnitTestData/TestCamCalib/IFLI_SINGLELEFTCAMPOINTS.txt" ; //��������ļ�·��
    camIO.readCamSignPts(strInputPath);
    CmlCamCalib cal;
    bool result = cal.mlSingleCamCalib(camIO.vecLImg2DPts , camIO.vecObj3DPts , camIO.m_nW , camIO.m_nH , camIO.inLCamPara , camIO.exLCamPara , camIO.vecErrorPts) ;
    CPPUNIT_ASSERT(result == true);

}

/**
* @fn TestmlSingleCamCalibcase2()
* @date 2012.02
* @author �⿭
* @brief ���Ե�����궨�������� flag=0
* @version 1.1
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/

void CTestCamCalib::TestmlSingleCamCalibcase2()  //flag = 0
{
    CCamCalibIO camIO;
    char* strInputPath = "../../../UnitTestData/TestCamCalib/IFLI_SINGLELEFTCAMPOINTS.txt" ; //��������ļ�·��
    camIO.readCamSignPts(strInputPath);
    CmlCamCalib cal;
    bool result = cal.mlSingleCamCalib(camIO.vecLImg2DPts , camIO.vecObj3DPts , camIO.m_nW , camIO.m_nH , camIO.inLCamPara , camIO.exLCamPara , camIO.vecErrorPts,0) ;
    CPPUNIT_ASSERT(result == true);

}


/**
* @fn TestmlStereoCamCalib_OK()
* @date 2012.02
* @author �⿭
* @brief ����˫����궨��������
* @version 1.1
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestCamCalib::TestmlStereoCamCalib_OK()
{
    CCamCalibIO camIO;
    char* strInputPath = "../../../UnitTestData/TestCamCalib/IFLI_STEREOCAMPOINTS.txt" ; //��������ļ�·��
    camIO.readCamSignPts(strInputPath);
    CmlCamCalib cal;
    bool result = cal.mlStereoCamCalib(camIO.vecLImg2DPts , camIO.vecRImg2DPts , camIO.vecObj3DPts , camIO.m_nW , camIO.m_nH ,
                                          camIO.inLCamPara , camIO.inRCamPara , camIO.exLCamPara , camIO.exRCamPara , camIO.exStereoPara ,camIO.vecErrorPts);
    CPPUNIT_ASSERT(result == true);

}

/**
* @fn TestmlStereoCamCalibcase2()
* @date 2012.02
* @author �⿭
* @brief ����˫����궨�������� flag=0
* @version 1.1
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestCamCalib::TestmlStereoCamCalibcase2()  //flag = 0
{
    CCamCalibIO camIO;
    char* strInputPath = "../../../UnitTestData/TestCamCalib/IFLI_STEREOCAMPOINTS.txt" ; //��������ļ�·��
    camIO.readCamSignPts(strInputPath);
    CmlCamCalib cal;
    bool result = cal.mlStereoCamCalib(camIO.vecLImg2DPts , camIO.vecRImg2DPts , camIO.vecObj3DPts , camIO.m_nW , camIO.m_nH ,
                                          camIO.inLCamPara , camIO.inRCamPara , camIO.exLCamPara , camIO.exRCamPara , camIO.exStereoPara ,camIO.vecErrorPts,0);
    CPPUNIT_ASSERT(result == true);

}

/**
* @fn TestmlStereoCamCalibcase2()
* @date 2012.02
* @author �⿭
* @brief ���Ժ󷽽��ắ��
* @version 1.1
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestCamCalib::TestbackProjection()
{
    CCamCalibIO camIO;
    char* strInputPath = "../../../UnitTestData/TestCamCalib/IFLI_SINGLELEFTCAMPOINTS.txt";
    camIO.readCamSignPts(strInputPath);
    CmlCamCalib cal;
    bool result = cal.backProjection(camIO.vecLImg2DPts,camIO.vecObj3DPts,camIO.inLCamPara,camIO.exLCamPara);
    CPPUNIT_ASSERT(result == true);

}
