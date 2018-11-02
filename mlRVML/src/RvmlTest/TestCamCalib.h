#ifndef CTESTCAMCALIB_H
#define CTESTCAMCALIB_H

#include <cppunit/extensions/HelperMacros.h>

class CTestCamCalib: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestCamCalib);
    //��Ӳ���������TestSuite
    //CPPUNIT_TEST(TestmlCoordTrans);

    //TestSuite�������
//    CPPUNIT_TEST(TestmlSingleCamCalib_OK);
//    CPPUNIT_TEST(TestmlStereoCamCalib_OK);
//    CPPUNIT_TEST(TestbackProjection);
//    CPPUNIT_TEST(TestmlSingleCamCalibcase2);
//    CPPUNIT_TEST(TestmlStereoCamCalibcase2);
    CPPUNIT_TEST_SUITE_END();

    public:
        CTestCamCalib();
        virtual ~CTestCamCalib();
   public:
        void setUp();//cppunit ϵͳĬ�ϵĳ�ʼ��
        void tearDown();//cppunit ϵͳĬ�ϵ����ٺ���
        void TestmlSingleCamCalib_OK();
        void TestmlStereoCamCalib_OK();
        void TestbackProjection();
        void TestmlSingleCamCalibcase2();
        void TestmlStereoCamCalibcase2();
        //���Ժ���

    protected:
    private:
};

#endif // CTESTCAMCALIB_H
