/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestRasterBlock.h
* @date 2011.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief դ�����ݿ鴦�����ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#ifndef CTESTRSTERBLOCK_H
#define CTESTRSTERBLOCK_H

#include <cppunit/extensions/HelperMacros.h>
class CTestRasterBlock: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestRasterBlock);
//    //��Ӳ���������TestSuite
//    CPPUNIT_TEST(TestInitialImg_ok);
 //   CPPUNIT_TEST(TestInitialImg_ReturnFalse);
//    CPPUNIT_TEST(TestReSet_ok);
//    CPPUNIT_TEST(TestClear_ok);
//    CPPUNIT_TEST(TestGetPtrAt_ok);
 //   CPPUNIT_TEST(TestGetPtrAt_ReturnFalse);
//    CPPUNIT_TEST(TestSetPtrAt_ok);
 //   CPPUNIT_TEST(TestSetPtrAt_ReturnFalse);
//    CPPUNIT_TEST(TestGetAt_ok);
//    CPPUNIT_TEST(TestSetAt_ok);
 //   CPPUNIT_TEST(TestSetAt_ReturnFalse);

//    CPPUNIT_TEST(TestGetDoubleVal_ok);
 //   CPPUNIT_TEST(TestGetDoubleVal_ReturnFalse) ;
//    CPPUNIT_TEST(TestSetDoubleVal_ok);
 //   CPPUNIT_TEST(TestSetDoubleVal_ReturnFalse);
//    CPPUNIT_TEST(TestGetGeoXYZ_ok);
 //   CPPUNIT_TEST(TestGetGeoXYZ_ReturnFalse);
//    CPPUNIT_TEST(TestGetGeoZ_ok);
//    CPPUNIT_TEST(TestGetGeoZ_ReturnFalse);
    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        /**
        * @fn CTestRasterBlock
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �ղι��캯��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        CTestRasterBlock();
        /**
        * @fn ~CTestRasterBlock
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        virtual ~CTestRasterBlock();

   public:
        /**
        * @fn setup
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
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
        * @author ���Ļ� whwan@irsa.ac.cn
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
        * @fn TestInitialImg_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Գ�ʼ��դ���ڴ溯������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestInitialImg_ReturnFalse();
         /**
        * @fn TestInitialImg_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Գ�ʼ��դ���ڴ溯�������ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestInitialImg_ok();
        /**
        * @fn TestReSet_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ����������ݣ���ɾ���ڴ湦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestReSet_ok();
        /**
        * @fn TestClear_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �������ýṹ��������ݣ�������Ϣ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestClear_ok();
        /**
        * @fn TestGetPtrAt_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Եõ�ĳ��������ֵ��ͷָ�빦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetPtrAt_ok();
        /**
        * @fn TestGetPtrAt_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Եõ�ĳ��������ֵ��ͷָ�빦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetPtrAt_ReturnFalse();
        /**
        * @fn TestSetPtrAt_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������ĳ��������ֵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSetPtrAt_ok();
        /**
        * @fn TestSetPtrAt_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������ĳ��������ֵ�����ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSetPtrAt_ReturnFalse();
        /**
        * @fn TestGetAt_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Եõ�դ���ĳ�����������һ���ֽ�ֵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetAt_ok();
        /**
        * @fn TestSetAt_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������դ���ĳ�����������һ���ֽ�ֵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSetAt_ok();
         /**
        * @fn TestSetAt_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������դ���ĳ�����������һ���ֽ�ֵ�����ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSetAt_ReturnFalse();
        /**
        * @fn TestGetDoubleVal_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Եõ����ݿ������ص�ֵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetDoubleVal_ok();
         /**
        * @fn TestGetDoubleVal_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Եõ����ݿ������ص�ֵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetDoubleVal_ReturnFalse();
        /**
        * @fn TestSetDoubleVal_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �����������ݿ������ص�ֵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSetDoubleVal_ok();
         /**
        * @fn TestSetDoubleVal_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �����������ݿ������ص�ֵ�����ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSetDoubleVal_ReturnFalse();
        /**
        * @fn TestGetGeoXYZ_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Եõ���������Ϣ�����ݿ��ڵ���ά����ֵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetGeoXYZ_ok();
        /**
        * @fn TestGetGeoXYZ_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Եõ���������Ϣ�����ݿ��ڵ���ά����ֵ�����ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetGeoXYZ_ReturnFalse();
        /**
        * @fn TestGetGeoZ_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Եõ���������Ϣ�����ݿ��ڵ���ά�߳�ֵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetGeoZ_ok();
        /**
        * @fn TestGetGeoZ_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Եõ���������Ϣ�����ݿ��ڵ���ά�߳�ֵ�����ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetGeoZ_ReturnFalse();
    protected:
    private:
};

#endif // CTESTRSTERBLOCK_H
