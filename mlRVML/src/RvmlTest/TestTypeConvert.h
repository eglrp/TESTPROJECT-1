/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestTypeConvert.h
* @date 2011.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ת������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#ifndef CTESTTYPECONVERT_H
#define CTESTTYPECONVERT_H

#include <cppunit/extensions/HelperMacros.h>
class CTestTypeConvert: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestTypeConvert);
//    //��Ӳ���������TestSuite
//    CPPUNIT_TEST(TestIplImage2CmlRBlock_ok);
//    CPPUNIT_TEST(TestCmlRBlock2IplImg_ok);
    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        /**
        * @fn CTestTypeConvert
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �ղι��캯��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        CTestTypeConvert();
        /**
        * @fn ~CTestTypeConvert
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        virtual ~CTestTypeConvert();

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
        * @fn TestIplImage2CmlRBlock_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Խ�IplImage�ͱ���ת����CmlSBlock�ͱ�������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestIplImage2CmlRBlock_ok();
        /**
        * @fn TestCmlRBlock2IplImg_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Խ�CmlSBlock�ͱ���ת����IplImage�ͱ�������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCmlRBlock2IplImg_ok();
    protected:
    private:
};

#endif // CTESTTYPECONVERT_H
