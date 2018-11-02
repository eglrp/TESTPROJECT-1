/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestFrameImage.cpp
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ�������Դ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef CTESTFRAMEIMAGE_H
#define CTESTFRAMEIMAGE_H

#include <cppunit/extensions/HelperMacros.h>
class CTestFrameImage: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestFrameImage);
    //��Ӳ���������TestSuite
    //CPPUNIT_TEST(TestLoadFile_ok);
    //CPPUNIT_TEST(TestGetUnDistortImg_ok);
    //CPPUNIT_TEST(TestGetUnDistortImg2_ok);
    //CPPUNIT_TEST(UnDisCorToPlaneFrame_ok);
    //CPPUNIT_TEST(UnDisCorToPicCoord_ok);
    //CPPUNIT_TEST(TestBilinearInterpolation_ok);
    //CPPUNIT_TEST(TestGetDistortionCoordinate_ok);
    //CPPUNIT_TEST(TestGrayInterpolation_ok);
    //CPPUNIT_TEST(TestGetBilinearValue_ok);
    // CPPUNIT_TEST(TestCleanDeadPix_ok);
 //    CPPUNIT_TEST(TestCleanDeadPix_abnormal);
    // CPPUNIT_TEST(TestExtractFeatPtByForstner_ok);
    // CPPUNIT_TEST(TestExtractFeatPtByForstner_abnormal);
    //CPPUNIT_TEST(TestGetBilinearValue_abnormal);
    //CPPUNIT_TEST(TestGrayInterpolation_abnormal);
    //CPPUNIT_TEST(TestBilinearInterpolation_abnormal);
    //CPPUNIT_TEST(TestGetDistortionCoordinate_abnormal);
    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        CTestFrameImage();
        virtual ~CTestFrameImage();
   public:
        void setUp();//cppunit ϵͳĬ�ϵĳ�ʼ��
        void tearDown();//cppunit ϵͳĬ�ϵ����ٺ���
        //���Ժ���

        void TestLoadFile_ok();
        /**
        * @fn TestGetUnDistortImg_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief �����������Ӱ�����У������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetUnDistortImg_ok();
        /**
        * @fn TestGetUnDistortImg2_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief �����������Ӱ�����У������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetUnDistortImg2_ok();
        /**
        * @fn UnDisCorToPlaneFrame_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ��������������겢ת������ƽ������ϵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void UnDisCorToPlaneFrame_ok();
        /**
        * @fn UnDisCorToPicCoord_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���������������.ת����ͼ������ϵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void UnDisCorToPicCoord_ok();
        /**
        * @fn BilinearInterpolation_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����˫�����ڲ幦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestBilinearInterpolation_ok();
        /**
        * @fn TestGetDistortionCoordinate_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���������������깦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetDistortionCoordinate_ok();
        /**
        * @fn GetDistortionCoordinate_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����ͼ��Ҷ��ڲ幦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGrayInterpolation_ok();
        /**
        * @fn GetBilinearValue_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����Ӱ��Ҷ�ֵ��˫�����ڲ幦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetBilinearValue_ok();
        /**
        * @fn TestCleanDeadPix_ok
        * @date 2011.12.1
        * @author ������ zhangchy@irsa.ac.cn
        * @brief ��������ͼ��ȥ�����㹦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCleanDeadPix_ok();
        /**
        * @fn TestCleanDeadPix_abnormal
        * @date 2011.12.1
        * @author ������ zhangchy@irsa.ac.cn
        * @brief ��������ͼ��ȥ�����㹦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCleanDeadPix_abnormal();
        /**
        * @fn GetBilinearValue_abnormal
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����mlGetBilinearValue��������Ӱ���Ϊ�յ��쳣���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetBilinearValue_abnormal();
        /**
        * @fn TestGrayInterpolation_abnormal
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����mlGrayInterpolation��������Ӱ��Ϊ�յ��쳣���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGrayInterpolation_abnormal();
        /**
        * @fn TestBilinearInterpolation_abnormal
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����mlBilinearInterpolation��������Ӱ��Ϊ�յ��쳣���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestBilinearInterpolation_abnormal();
        /**
        * @fn TestGetDistortionCoordinate_abnormal
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����mlGetDistortionCoordinate��������Ӱ��Ϊ�յ��쳣���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetDistortionCoordinate_abnormal();
        /**
        * @fn TestExtractFeatPtByForstner_abnormal
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����ExtractFeatPtByForstner��������Ӱ����޷�ת����IplImg���쳣���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestExtractFeatPtByForstner_abnormal();
        /**
        * @fn TestExtractFeatPtByForstner_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief �����������Ӱ��Forstner������ȡ�����㹦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestExtractFeatPtByForstner_ok();
    protected:
    private:
};

#endif // CTESTFRAMEIMAGE_H
