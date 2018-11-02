#ifndef CTESTDEMANALYSE_H
#define CTESTDEMANALYSE_H

#include <cppunit/extensions/HelperMacros.h>
class CTestDemAnalyse: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestDemAnalyse);
    //��Ӳ���������TestSuite
    //CPPUNIT_TEST(TestmlCoordTrans);
//    CPPUNIT_TEST(ComputeViewShedInterface_OK);
//    // ����-1��������Ҫ��ͼ��
//    // ����-3������ʱ����blockʱ�����쳣��Ӧ����ͼƬ����ʱ����
//    CPPUNIT_TEST(ComputeViewShedInterface_ReturnM2);
//    CPPUNIT_TEST(ComputeViewShedInterface_ReturnM4);
//
//    CPPUNIT_TEST(ComputeSlopeInterface_OK);
//    CPPUNIT_TEST(ComputeSlopeInterface_ReturnM1);
//    CPPUNIT_TEST(ComputeSlopeInterface_ReturnM2);
//
//    CPPUNIT_TEST(ComputeSlopeAspectInterface_OK);
//    CPPUNIT_TEST(ComputeSlopeAspectInterface_ReturnM1);
//    CPPUNIT_TEST(ComputeSlopeAspectInterface_ReturnM2);
//
//    CPPUNIT_TEST(ComputeObstacleMapInterface_OK);
//    CPPUNIT_TEST(ComputeObstacleMapInterface_ReturnM1);
//    CPPUNIT_TEST(ComputeObstacleMapInterface_ReturnM2);
//
//
//    CPPUNIT_TEST(ComputeContourInterface_OK);
//    // ����-1ʱ��gdal�汾����
//    CPPUNIT_TEST(ComputeContourInterface_ReturnM2);
//    CPPUNIT_TEST(ComputeContourInterface_ReturnM3);
//    CPPUNIT_TEST(ComputeContourInterface_ReturnM4);


    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

    public:
        CTestDemAnalyse();
        virtual ~CTestDemAnalyse();
   public:
        void setUp();//cppunit ϵͳĬ�ϵĳ�ʼ��
        void tearDown();//cppunit ϵͳĬ�ϵ����ٺ���
        //���Ժ���
    /**
    * @fn ComputeViewShedInterface_OK()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������������ʱ����ͨ��ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeViewShedInterface_OK();

    /**
    * @fn ComputeViewShedInterface_ReturnM2()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ��������DEMԴ�ļ������쳣ʱ����ͨ��ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeViewShedInterface_ReturnM2();

    /**
    * @fn ComputeViewShedInterface_ReturnM4()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������ӵ�λ�ò����쳣ʱ����ͨ��ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeViewShedInterface_ReturnM4();



    /**
    * @fn ComputeSlopeInterface_OK()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������������ʱ�����¶�ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeSlopeInterface_OK();

    /**
    * @fn ComputeSlopeInterface_ReturnM1()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������ļ�·������ʱ�����¶�ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeSlopeInterface_ReturnM1();

    /**
    * @fn ComputeSlopeInterface_ReturnM2()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief �����¶�ʧ��ʱ�����¶�ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeSlopeInterface_ReturnM2();

    /**
    * @fn ComputeSlopeAspectInterface_OK()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������������ʱ��������ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeSlopeAspectInterface_OK();

    /**
    * @fn ComputeSlopeAspectInterface_ReturnM1()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������ļ�·������ʱ��������ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeSlopeAspectInterface_ReturnM1();

    /**
    * @fn ComputeSlopeInterface_ReturnM2()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ��������ʧ��ʱ��������ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeSlopeAspectInterface_ReturnM2();

    /**
    * @fn ComputeObstacleMapInterface_OK()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������������ʱ�����ϰ�ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeObstacleMapInterface_OK();

    /**
    * @fn ComputeObstacleMapInterface_ReturmM1()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������ļ�·������ʱ�����ϰ�ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeObstacleMapInterface_ReturnM1();

    /**
    * @fn ComputeObstacleMapInterface_ReturmM2()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������ϰ�����ʱ�����ϰ�ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeObstacleMapInterface_ReturnM2();

     /**
    * @fn ComputeContourInterface_OK()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������������ʱ���ɵȸ���ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeContourInterface_OK();

    /**
    * @fn ComputeContourInterface_ReturnM2()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ������������ȸ߾�Ϊ0ʱ���ɵȸ���ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeContourInterface_ReturnM2();

    /**
    * @fn ComputeContourInterface_ReturnM3()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ���������ļ�������ʱ���ɵȸ���ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeContourInterface_ReturnM3();

    /**
    * @fn ComputeContourInterface_ReturnM4()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief ��������ļ�������ʱ���ɵȸ���ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void ComputeContourInterface_ReturnM4();

    protected:
    private:
};

#endif // CTESTDEMANALYSE_H
