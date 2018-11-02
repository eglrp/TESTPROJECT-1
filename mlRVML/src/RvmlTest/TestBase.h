/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestBase.h
* @date 2011.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���̹�����������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#ifndef CTESTBASE_H
#define CTESTBASE_H

#include <cppunit/extensions/HelperMacros.h>
class CTestBase: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestBase);
//    //��Ӳ���������TestSuite
//    CPPUNIT_TEST(TestPtInRect_ok);
//    CPPUNIT_TEST(TestPtInRect2_ok);
 //   CPPUNIT_TEST(TestPtInRect_ReturnFalse);
 //   CPPUNIT_TEST(TestPtInRect2_ReturnFalse);
//     CPPUNIT_TEST(TestOPK2RMat_ok);
 //   CPPUNIT_TEST(TestOPK2RMat_ReturnFalse);
//     CPPUNIT_TEST(TestRMat2OPK_ok);
//    CPPUNIT_TEST(TestOpen_ok);
 //  CPPUNIT_TEST(TestOpen_ReturnFalse);
//    CPPUNIT_TEST(TestClose_ok);
 //   CPPUNIT_TEST(TestAddSuccessQuitMsg_ok);
//   CPPUNIT_TEST(TestAddErrorMsg_ok);
//    CPPUNIT_TEST(TestAddExceptionMsg_ok);
//    CPPUNIT_TEST(TestAddNoticeMsg_ok);
   //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        /**
        * @fn CTestBase
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �ղι��캯��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        CTestBase();
        /**
        * @fn ~CTestBase
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        virtual ~CTestBase();

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
        * @fn TestPtInRect_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �����ж�ĳ���Ƿ��ھ��ο��ڹ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestPtInRect_ok();
        /**
        * @fn TestPtInRect2_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �����ж�ĳ���Ƿ��ھ��ο��ڹ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestPtInRect2_ok();
        /**
        * @fn TestPtInRect_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �����ж�ĳ���Ƿ��ھ��ο���׼ȷ��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
         void TestPtInRect_ReturnFalse();
        /**
        * @fn TestPtInRect2_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �����ж�ĳ���Ƿ��ھ��ο���׼ȷ��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestPtInRect2_ReturnFalse();
        /**
        * @fn TestOPK2RMat_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������ת��OPKת������ת������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestOPK2RMat_ok();
        /**
        * @fn TestOPK2RMat_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������ת��OPKת������ת�����ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestOPK2RMat_ReturnFalse();

            /**
        * @fn TestRMat2OPK_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������ת����ת������ת��OPK����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestRMat2OPK_ok();
        /**
        * @fn TestOpen_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Գ�ʼ������ļ���·�������Ƿ���Ҫ��ӡ����Ļ��.ͬʱ����˴���־��ͷ��Ϣ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestOpen_ok();
        /**
        * @fn TestOpen_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Գ�ʼ������ļ���·�������Ƿ���Ҫ��ӡ����Ļ��.ͬʱ����˴���־��ͷ��Ϣ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestOpen_ReturnFalse();
        /**
        * @fn TestClose_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Թر��ļ�����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestClose_ok();
        /**
        * @fn TestAddSuccessQuitMsg_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Ժ��������������˳���Ϣ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestAddSuccessQuitMsg_ok();
        /**
        * @fn TestAddErrorMsg_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Ժ�����������Ԥ֪������Ϣ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestAddErrorMsg_ok();
        /**
        * @fn TestAddExceptionMsg_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Ժ������г����쳣��Ϣ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestAddExceptionMsg_ok();
        /**
        * @fn TestAddNoticeMsg_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Ժ������г�����ʾ��Ϣ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestAddNoticeMsg_ok();

    protected:
    private:
};

#endif // CTESTBASE_H
