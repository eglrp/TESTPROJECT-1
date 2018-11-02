/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestMat.h
* @date 2011.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��������������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#ifndef CTESTMAT_H
#define CTESTMAT_H

#include <cppunit/extensions/HelperMacros.h>
class CTestMat: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestMat);
//    //��Ӳ���������TestSuite
//    CPPUNIT_TEST(TestmlMat2CvMat_ok);
//    CPPUNIT_TEST(TestCvMat2mlMat_ok);
//    CPPUNIT_TEST(TestmlMatTrans_ok);
//    CPPUNIT_TEST(TestmlMatAdd_ok);
//    CPPUNIT_TEST(TestmlMatSub_ok);
//    CPPUNIT_TEST(TestmlMatMul_ok);
//    CPPUNIT_TEST(TestmlMatInv_ok);
//    CPPUNIT_TEST(TestmlMatDet_ok);
//    CPPUNIT_TEST(TestmlMatSolveSVD_ok);
//    CPPUNIT_TEST(TestmlMatSVD_ok);
//    CPPUNIT_TEST(TestmlMatCross3_ok);
    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

public:
    /**
    * @fn CTestMat
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    CTestMat();
    /**
    * @fn ~CTestMat
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    virtual ~CTestMat();

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
    @fn TestmlMat2CvMat_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Խ�CmlMatת����CvMat����
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMat2CvMat_ok();
    /**
    * @fn TestCvMat2mlMat_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Խ�CvMatת����CmlMat����
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestCvMat2mlMat_ok();
    /**
    * @fn TestmlMatTrans_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Ծ���ת�ù���
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMatTrans_ok();
    /**
    * @fn TestmlMatAdd_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Ծ���ӷ�����
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMatAdd_ok();
    /**
    * @fn TestmlMatSub_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Ծ����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMatSub_ok();
    /**
    * @fn TestmlMatMul_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Ծ���˷�����
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMatMul_ok();
    /**
    * @fn TestmlMatInv_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Ծ������湦��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMatInv_ok();
    /**
    * @fn TestmlMatDet_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �������������ʽֵ����
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMatDet_ok();
    /**
    * @fn TestmlMatSolveSVD_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���Խⷽ��A*x=B����
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMatSolveSVD_ok();
    /**
    * @fn TestmlMatSVD_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ����SVD�ֽ⹦��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMatSVD_ok();
    /**
    * @fn TestmlMatCross3_ok
    * @date 2011.12.1
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ������ά������˹���
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void TestmlMatCross3_ok();
protected:
private:
};

#endif // CTESTMAT_H
