/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestBlockCalculation.h
* @date 2011.2.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief Ӱ��ֿ����ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#ifndef CTESTBLOCKCALCULATION_H
#define CTESTBLOCKCALCULATION_H

#include <cppunit/extensions/HelperMacros.h>
class CTestBlockCalculation: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestBlockCalculation);
//    //��Ӳ���������TestSuite
//    CPPUNIT_TEST(TestCalBlockCol_ok);
//    CPPUNIT_TEST(TestCalBlockRow_ok);
//    CPPUNIT_TEST(TestGetStartCol_ok);
//    CPPUNIT_TEST(TestGetStartRow_ok);
//    CPPUNIT_TEST(TestGetBlockPos_ok);
//    CPPUNIT_TEST(TestGetBlockPosLast_ok);
//      CPPUNIT_TEST(TestCalBlock_ok);
//      CPPUNIT_TEST(TestCalBlock2_ok);
//      CPPUNIT_TEST(TestCalBlock3_ok);
      CPPUNIT_TEST(TestCalBlock4_ok);
//    CPPUNIT_TEST(TestGetBlock_ok);

//    CPPUNIT_TEST(TestGetBlockPos_abnormal);
//    CPPUNIT_TEST(TestCalBlock_abnormal1);
//    CPPUNIT_TEST(TestCalBlock_abnormal2);
//    CPPUNIT_TEST(TestGetBlock_abnormal);
    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        /**
        * @fn CTestBlockCalculation
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief �ղι��캯��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        CTestBlockCalculation();
        /**
        * @fn ~CTestBlockCalculation
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        virtual ~CTestBlockCalculation();

   public:
        /**
        * @fn setup
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ϵͳĬ�ϵĳ�ʼ������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void setUp();//cppunit ϵͳĬ�ϵĳ�ʼ��
        /**
        * @fn tearDown
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ϵͳĬ�ϵ����ٺ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        void tearDown();//cppunit ϵͳĬ�ϵ����ٺ���
        //���Ժ���
        /**
        * @fn TestCalBlockCol_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���Ӱ�����У�X������ֿ�Ĵ�С�Ŀ�������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCalBlockCol_ok();
        /**
        * @fn TestCalBlockRow_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���Ӱ�����У�Y������ֿ�Ĵ�С�Ŀ�������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCalBlockRow_ok();
        /**
        * @fn TestGetStartCol_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���Ӱ���У�X������ĳһ�ֿ����ʼ�кŹ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetStartCol_ok();
        /**
        * @fn TestGetStartRow_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���Ӱ���У�Y������ĳһ�ֿ����ʼ�кŹ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetStartRow_ok();
        /**
        * @fn TestGetBlockPos_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���ĳһӰ������ʼλ�úʹ�С����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetBlockPos_ok();
        /**
        * @fn TestGetBlockPosLast_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���ĳһӰ������һ�����ʼλ�úʹ�С����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetBlockPosLast_ok();
        /**
        * @fn TestCalBlock_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���Ӱ�����У��У�����ֿ�Ĵ�С�Ŀ�������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCalBlock_ok();
        /**
        * @fn TestCalBlock2_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���Ӱ�����У��У�����ֿ�Ĵ�С�Ŀ�������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCalBlock2_ok();
        /**
        * @fn TestCalBlock3_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���Ӱ�����У��У�����ֿ�Ĵ�С�Ŀ�������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCalBlock3_ok();
        /**
        * @fn TestCalBlock4_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���Ӱ�����У��У�����ֿ�Ĵ�С�Ŀ�������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCalBlock4_ok();
        /**
        * @fn TestGetBlock_ok
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ���Լ���Ӱ�����У��У�����ĳһ�����ʼλ�ù���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetBlock_ok();
        /**
        * @fn TestGetBlockPos_abnormal
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����GetBlockPos��������������޵��쳣���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetBlockPos_abnormal();
        /**
        * @fn TestCalBlock_abnormal1
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����CalBlock�����������Ϊ����쳣���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCalBlock_abnormal1();
        /**
        * @fn TestCalBlock_abnormal2
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����CalBlock��������������޵��쳣���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCalBlock_abnormal2();
        /**
        * @fn TestGetBlock_abnormal
        * @date 2011.12.1
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����GetBlock��������������޵��쳣���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetBlock_abnormal();
    protected:
    private:
};

#endif // CTESTBLOCKCALCULATION_H
