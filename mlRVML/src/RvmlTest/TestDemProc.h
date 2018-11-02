#ifndef CTESTDEMPROC_H
#define CTESTDEMPROC_H

#include <cppunit/extensions/HelperMacros.h>
class CTestDemProc: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestDemProc);
    //��Ӳ���������TestSuite
   // CPPUNIT_TEST(TestmlCoordTrans);
//    CPPUNIT_TEST(TestDemProc_OK_ByPix);
//    CPPUNIT_TEST(TestDemProc_OK_ByGeoPos);
//    CPPUNIT_TEST(TestImgReprj_OK);
//    CPPUNIT_TEST(TestmlTinSimply_OK);
//    CPPUNIT_TEST(TestBackfordinterSection_OK);
//    CPPUNIT_TEST(TestBuild2By2DPt_OK);
//    CPPUNIT_TEST(TestBackfordinterSection_abnormal);
//    CPPUNIT_TEST(TestBuild2By2DPt_OK);
//    CPPUNIT_TEST(TestBuild2By3DPt_OK);
//    CPPUNIT_TEST(TestBuild2Byvec3dPt_OK);
//    CPPUNIT_TEST(TestmlReproject_OK2);
    CPPUNIT_TEST(TestmlWriteToGeoFile_case1);
    CPPUNIT_TEST(TestmlWriteToGeoFile_case1);
//    CPPUNIT_TEST(TestGetValueFromTin);
//    CPPUNIT_TEST(TestGetCenterTriIndex_OK);
//    CPPUNIT_TEST(TestGetGridTriIndex_OK);
//    CPPUNIT_TEST(TestmlInitVariogram);


    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        CTestDemProc();
        virtual ~CTestDemProc();
   public:
        void setUp();//cppunit ϵͳĬ�ϵĳ�ʼ��
        void tearDown();//cppunit ϵͳĬ�ϵ����ٺ���
        //���Ժ���

        /**
        * @fn TestDemProc_OK_ByPix()
        * @date 2011.12.1
        * @author ������
        * @brief �������������ȷʱDEMDOM�������زü�����
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestDemProc_OK_ByPix();


        /**
        * @fn TestDemProc_OK_ByGeoPos()
        * @date 2011.12.1
        * @author ������
        * @brief �������������ȷʱDEMDOM���ݵ�������ü�����
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestDemProc_OK_ByGeoPos();


        /**
        * @fn TestImgReprj_OK()
        * @date 2011.12.1
        * @author ������
        * @brief �������������ȷʱָ���ӽ�ͼ�����ɹ���
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestImgReprj_OK();


        /**
        * @fn TestmlTinSimply_OK()
        * @date 2011.12.1
        * @author ������
        * @brief �������������ȷʱTIN�򻯹���
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestmlTinSimply_OK();

        /**
        * @fn TestBackfordinterSection_OK()
        * @date 2011.12.1
        * @author ������
        * @brief �������������ȷʱ�󷽽��Ṧ��
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestBackfordinterSection_OK();

        /**
        * @fn TestBackfordinterSection_abnormal()
        * @date 2011.12.1
        * @author ������
        * @brief �������������֪��С��3ʱ�󷽽��Ṧ��
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestBackfordinterSection_abnormal();

        /**
        * @fn TestImgReprj_OK()
        * @date 2011.12.1
        * @author ������
        * @brief �������������ȷʱָ���ӽ�ͼ�����ɹ���
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */

        void TestmlReproject_OK();

        void TestmlReproject_OK2();


        /**
        * @fn TestBuild2By2DPt_OK()
        * @date 2011.12.1
        * @author ������
        * @brief �����ɶ�ά�����й�TIN����
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */

        void TestBuild2By2DPt_OK();

       /**
        * @fn TestBuild2By3DPt_OK()
        * @date 2011.12.1
        * @author ������
        * @brief ��������ά�����й�TIN����
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestBuild2By3DPt_OK();

        /**
        * @fn TestBuild2Byvec3dPt_OK()
        * @date 2011.12.1
        * @author ������
        * @brief ������vector��ά�㹹TIN����
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestBuild2Byvec3dPt_OK();


        /**
        * @fn TestmlWriteToGeoFile_case1()
        * @date 2011.12.1
        * @author �⿭
        * @brief ����д��geo�ļ�����
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestmlWriteToGeoFile_case1();
        /**
        * @fn TestmlWriteToGeoFile_case2()
        * @date 2011.12.1
        * @author �⿭
        * @brief ����д��geo�ļ�����
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestmlWriteToGeoFile_case2();
        /**
        * @fn TestGetValueFromTin()
        * @date 2011.12.1
        * @author �⿭
        * @brief ����TIN�ڲ幦��
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestGetValueFromTin();

        /**
        * @fn TestGetCenterTriIndex_OK()
        * @date 2011.12.1
        * @author ������
        * @brief ���Ի�ȡ��������������
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestGetCenterTriIndex_OK();


        /**
        * @fn TestmlInitVariogram()
        * @date 2011.12.1
        * @author �⿭
        * @brief ���Գ�ʼ��variogram
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestmlInitVariogram();


        /**
        * @fn TestGetGridTriIndex_OK()
        * @date 2011.12.1
        * @author ������
        * @brief ���Ի�ȡ��������������
        * @version 1.1
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void TestGetGridTriIndex_OK();



    protected:
    private:
};

#endif // CTESTDEMPROC_H
