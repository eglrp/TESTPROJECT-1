/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestFileRaster.h
* @date 2011.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief Ӱ���ļ���д����ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#ifndef CTESTFILERASTER_H
#define CTESTFILERASTER_H

#include <cppunit/extensions/HelperMacros.h>
class CTestFileRaster: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestFileRaster);
//    //��Ӳ���������TestSuite
//    CPPUNIT_TEST(TestLoadFile_ok);
//    CPPUNIT_TEST(TestCreateFile_ok);
//    CPPUNIT_TEST(TestSaveBlockToFile_ok);
    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        /**
        * @fn CTestFileRaster
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �ղι��캯��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        CTestFileRaster();
        /**
        * @fn ~CTestFileRaster
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        virtual ~CTestFileRaster();

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
        * @fn TestLoadFile_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Լ���դ��Ӱ���ļ�����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestLoadFile_ok();
        /**
        * @fn TestCreateFile_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Դ���դ��Ӱ���ļ�����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCreateFile_ok();
        /**
        * @fn TestSaveBlockToFile_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Խ�դ��Ӱ�������ļ�����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSaveBlockToFile_ok();
    protected:
    private:
};

#endif // CTESTFILERASTER_H
