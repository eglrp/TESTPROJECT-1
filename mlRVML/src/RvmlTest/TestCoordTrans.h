#ifndef CTESTCOORDTRANS_H
#define CTESTCOORDTRANS_H

#include <cppunit/extensions/HelperMacros.h>

class CTestCoordTrans: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestCoordTrans);
    //��Ӳ���������TestSuite
    //CPPUNIT_TEST(TestmlCoordTrans);
//    CPPUNIT_TEST(TestmlCoordTrans_OK);
//    CPPUNIT_TEST(TestmlCoordTransResult1_OK);
//    CPPUNIT_TEST(TestmlCoordTransResult2_OK);
//    CPPUNIT_TEST(TestmlCalcTransMatrix_case2);
//    CPPUNIT_TEST(TestmlCalcTransMatrix_case3);
//    CPPUNIT_TEST(TestmlCalcTransMatrix_case4);
//    CPPUNIT_TEST(TestmlCoordTransResult1_abnormal1);
//
//    CPPUNIT_TEST(TestmlCalcTransMatrixByLatLong);
       //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        CTestCoordTrans();
        virtual ~CTestCoordTrans();

    public:
        void setUp();//cppunit ϵͳĬ�ϵĳ�ʼ��
        void tearDown();//cppunit ϵͳĬ�ϵ����ٺ���
        //���Ժ���
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
        void TestmlCoordTrans_OK();

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

        void TestmlCalcTransMatrix_case2();
        void TestmlCalcTransMatrix_case3();
        void TestmlCalcTransMatrix_case4();

        void TestmlCoordTransResult1_OK();



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
        void TestmlCoordTransResult2_OK();

        void TestmlCoordTransResult1_abnormal1();
        //��ת����ά��������ά�������

        void TestmlCalcTransMatrixByLatLong();

    protected:
    private:
};

#endif // CTESTCOORDTRANS_H
