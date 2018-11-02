/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestGdalDataset.h
* @date 2011.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief GDALͼ�������������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#ifndef CTESTGDALDATASET_H
#define CTESTGDALDATASET_H

#include <cppunit/extensions/HelperMacros.h>
class CTestGdalDataset: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestGdalDataset);
//    //��Ӳ���������TestSuite
//    CPPUNIT_TEST(TestLoadFile_ok);
 //   CPPUNIT_TEST(TestLoadFile_ReturnFalse);
//    CPPUNIT_TEST(TestCreateFile_ok);
   // CPPUNIT_TEST(TestCreateFile_ReturnFalse);
     // CPPUNIT_TEST(TestSaveBlockToFile_ok);
    //  CPPUNIT_TEST(TestSaveBlockToFile2_ok);
   // CPPUNIT_TEST(TestSaveBlockToFile_ReturnFalse);
  //  CPPUNIT_TEST(TestSaveBlockToFile2_ReturnFalse);
//    CPPUNIT_TEST(TestGetRasterGrayBlock_ok);
//    CPPUNIT_TEST(TestGetRasterGrayBlock2_ok);
//    CPPUNIT_TEST(TestGetRasterGrayBlock3_ok);
 //   CPPUNIT_TEST(TestGetRasterGrayBlock_ReturnFalse);
 //   CPPUNIT_TEST(TestGetRasterGrayBlock2_ReturnFalse);
 //   CPPUNIT_TEST(TestGetRasterGrayBlock3_ReturnFalse);
//    CPPUNIT_TEST(TestGetRasterOriginBlock_ok);
//    CPPUNIT_TEST(TestGetRasterOriginBlock2_ok);
//    CPPUNIT_TEST(TestGetRasterOriginBlock_ReturnFalse);
//    CPPUNIT_TEST(TestGetRasterOriginBlock2_ReturnFalse);
//    CPPUNIT_TEST(TestSetNoDataVal_ok);
    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        /**
        * @fn CTestGdalDataset
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �ղι��캯��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        CTestGdalDataset();
        /**
        * @fn ~CTestGdalDataset
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        *
        */
        virtual ~CTestGdalDataset();
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
        * @fn TestLoadFile_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Լ���դ��Ӱ���ļ������ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestLoadFile_ReturnFalse();
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
        * @fn TestCreateFile_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Դ���դ��Ӱ���ļ������ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestCreateFile_ReturnFalse();
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
        void TestSaveBlockToFile2_ok();
        /**
        * @fn TestSaveBlockToFile_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Խ�դ��Ӱ�������ļ������ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSaveBlockToFile_ReturnFalse();
        /**
        * @fn TestSaveBlockToFile2_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ���Խ�դ��Ӱ�������ļ������ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSaveBlockToFile2_ReturnFalse();
        /**
        * @fn TestGetRasterGrayBlock_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ�ĳ������ĳ��λ��������ǿ��GDT_BYTE���͵�Ӱ��鹦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterGrayBlock_ok();
        /**
        * @fn TestGetRasterGrayBlock2_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ�ĳ������ĳ��λ��������ǿ��GDT_BYTE���͵�Ӱ��鹦��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterGrayBlock2_ok();
        /**
        * @fn TestGetRasterGrayBlock3_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ�ĳ�������Σ�ǿ��GDT_BYTE�������䵱��R��G��B���κ�ϳ�block����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterGrayBlock3_ok();
        /**
        * @fn TestGetRasterGrayBlock_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ�ĳ������ĳ��λ��������ǿ��GDT_BYTE���͵�Ӱ��鹦���ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterGrayBlock_ReturnFalse();
        /**
        * @fn TestGetRasterGrayBlock2_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ�ĳ������ĳ��λ��������ǿ��GDT_BYTE���͵�Ӱ��鹦���ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterGrayBlock2_ReturnFalse();
        /**
        * @fn TestGetRasterGrayBlock3_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ�ĳ�������Σ�ǿ��GDT_BYTE�������䵱��R��G��B���κ�ϳ�block�����ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterGrayBlock3_ReturnFalse();
        /**
        * @fn TestGetRasterOriginBlock_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ������Σ�����ԭʼ���ݵ���block�й���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterOriginBlock_ok();
        /**
        * @fn TestGetRasterOriginBlock2_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ������Σ�����ԭʼ���ݵ���block�й���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterOriginBlock_ReturnFalse();
         /**
        * @fn TestGetRasterOriginBlock_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ������Σ�����ԭʼ���ݵ���block�й����ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterOriginBlock2_ReturnFalse();
        /**
        * @fn TestGetRasterOriginBlock2_ReturnFalse
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ������GdalDataSet�еõ������Σ�����ԭʼ���ݵ���block�й����ݴ���
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestGetRasterOriginBlock2_ok();
        /**
        * @fn TestSetNoDataVal_ok
        * @date 2011.12.1
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��������DataSet�п�ֵ�Ĵ���ֵ����
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        void TestSetNoDataVal_ok();
    protected:
    private:
};

#endif // CTESTGDALDATASET_H
