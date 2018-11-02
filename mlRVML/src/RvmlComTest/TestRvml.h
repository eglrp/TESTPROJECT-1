/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TesRvml.h
* @date 2012.3.18
* @author
* @brief
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#ifndef CTESTRVML_H
#define CTESTRVML_H

#include <cppunit/extensions/HelperMacros.h>

/**
* @class CTestRvml
* @date 2012.3.18
* @author
* @brief
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*
*/

class CTestRvml: public CppUnit::TestFixture
{
    //����һ��TestSuite(��������������)
    CPPUNIT_TEST_SUITE(CTestRvml);
    //��Ӳ���������TestSuite
//    CPPUNIT_TEST(TestCameraCalibration_ok1);
//    CPPUNIT_TEST(TestCameraCalibration_ok2);
//    CPPUNIT_TEST(TestMonoSurvey_ok);
//    CPPUNIT_TEST(TestWideBaseAnalysis_ok);
//    CPPUNIT_TEST(TestWideBaseMapping_ok);
//    CPPUNIT_TEST(TestDenseMatch_ok);
//    CPPUNIT_TEST(TestDisparityMap_ok);
//    CPPUNIT_TEST(TestCoordTrans_ok);
//    CPPUNIT_TEST(TestCoordTransXYZ_ok);

//    CPPUNIT_TEST(TestSatMapping_ok);
      CPPUNIT_TEST(TestMapByInteBlock_ok);
//      CPPUNIT_TEST(TestPanoMosic_ok);
//     CPPUNIT_TEST(TestTinSimply_ok);
//     CPPUNIT_TEST(TestVisualImage_ok);
//
//    CPPUNIT_TEST(TestPano2Prespective_ok);
//    CPPUNIT_TEST(TestDemMosaic_ok);
//    CPPUNIT_TEST(TestComputeInsightMap_ok);
//    CPPUNIT_TEST(TestComputeSlopeAspectMap_ok);
//    CPPUNIT_TEST(TestComputeBarrierMap_ok);
//    CPPUNIT_TEST(TestComputeContourMap_ok);
//    CPPUNIT_TEST(TestGeoRasterCut_GeoCoo_ok);
//    CPPUNIT_TEST(TestGeoRasterCut_Pixel_ok);
//    CPPUNIT_TEST(TestLocalByMatch_ok);
//    CPPUNIT_TEST(TestLocalByIntersection_ok);
//
//    CPPUNIT_TEST(TestLocalIn2Site_ok);
//    CPPUNIT_TEST(TestLocalBySeqence_ok);
//    CPPUNIT_TEST(TestLocalByLander_ok);
    //TestSuite�������
    CPPUNIT_TEST_SUITE_END();

public:
    /**
    * @fn CTestRvml()
    * @date 2012.3.18
    * @author
    * @brief �ղι��캯��
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    CTestRvml();

    /**
    * @fn ~CTestRvml()
    * @date 2012.3.18
    * @author
    * @brief ��������
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    virtual ~CTestRvml();

public:
    /**
    * @fn setup()
    * @date 2012.3.18
    * @author
    * @brief ϵͳĬ�ϵĳ�ʼ������
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void setUp();//cppunit ϵͳĬ�ϵĳ�ʼ��

    /**
    * @fn tearDown()
    * @date 2012.3.18
    * @author
    * @brief ϵͳĬ�ϵ����ٺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void tearDown();//cppunit ϵͳĬ�ϵ����ٺ���

    /**
    * @fn TestSingleCamCalib_ok()
    * @date 2012.3.18
    * @author
    * @brief ���Ե�����궨����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestCameraCalibration_ok1();

    /**
    * @fn TestStereoCamCalib_ok()
    * @date 2012.3.18
    * @author
    * @brief ����˫����궨����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestCameraCalibration_ok2();

    /**
    * @fn TestMonoSurvey_ok()
    * @date 2012.3.18
    * @author
    * @brief ���Ե�Ŀ���⺯��
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestMonoSurvey_ok();

    /**
    * @fn TestWideBaseAnalysis_ok()
    * @date 2012.3.18
    * @author
    * @brief �������Ż��߼��㺯��
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestWideBaseAnalysis_ok();

    /**
    * @fn TestWideBaseMapping_ok()
    * @date 2012.3.18
    * @author
    * @brief ���Գ����߲�ͼ����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestWideBaseMapping_ok();

    /**
    * @fn TestDenseMatch_ok()
    * @date 2012.3.18
    * @author
    * @brief �����ܼ�ƥ�亯��
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestDenseMatch_ok();

    /**
    * @fn TestDisparityMap_ok()
    * @date 2012.3.18
    * @author
    * @brief �����Ӳ�ͼ���ɺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestDisparityMap_ok();

    /**
    * @fn TestCoordTransLat_ok()
    * @date 2012.3.18
    * @author
    * @brief ��������ת������
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestCoordTransLat_ok();

    /**
    * @fn TestCoordTransXYZ_ok()
    * @date 2012.3.18
    * @author
    * @brief ��������ת������
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestCoordTransXYZ_ok();

    /**
    * @fn TestSatMapping_ok()
    * @date 2012.3.18
    * @author
    * @brief �����϶�����Ӱ���ͼ����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestSatMapping_ok();

    /**
    * @fn TestMapByInteBlock_ok()
    * @date 2012.3.18
    * @author
    * @brief ���Ե�վ���ͼ����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestMapByInteBlock_ok();



    /**
    * @fn TestPanoMosic_ok()
    * @date 2012.3.18
    * @author
    * @brief ����ȫ��ƴ�Ӻ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestPanoMosic_ok();

    /**
    * @fn TestTinSimply_ok()
    * @date 2012.3.18
    * @author
    * @brief �����������򻯺���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestTinSimply_ok();



    /**
    * @fn TestVisualImage_ok()
    * @date 2012.3.18
    * @author
    * @brief ���Է���ͼ�����ɺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestVisualImage_ok();

    /**
    * @fn TestPano2Prespective_ok()
    * @date 2012.3.18
    * @author
    * @brief ����ȫ��ͼ������͸��ͼ����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestPano2Prespective_ok();

    /**
    * @fn TestDemMosaic_ok()
    * @date 2012.3.18
    * @author
    * @brief ����DEMƴ�Ӻ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestDemMosaic_ok();

    /**
    * @fn TestDemMosaic_ok()
    * @date 2012.3.18
    * @author
    * @brief ����ͨ��ͼ���㺯��
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestComputeInsightMap_ok();

    /**
    * @fn TestComputeSlopeAspectMap_ok()
    * @date 2012.3.18
    * @author
    * @brief ��������ͼ���ɺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestComputeSlopeAspectMap_ok();

    /**
    * @fn TestComputeBarrierMap_ok()
    * @date 2012.3.18
    * @author
    * @brief �����ϰ�ͼ���ɺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestComputeBarrierMap_ok();

    /**
    * @fn TestComputeContourMap_ok()
    * @date 2012.3.18
    * @author
    * @brief ���Եȸ���ͼ���ɺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestComputeContourMap_ok();

    /**
    * @fn TestGeoRasterCut_GeoCoo_ok()
    * @date 2012.3.18
    * @author
    * @brief ����DEM��DOM���к���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestGeoRasterCut_GeoCoo_ok();

    /**
    * @fn TestGeoRasterCut_Pixel_ok()
    * @date 2012.3.18
    * @author
    * @brief ����DEM��DOM���к���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestGeoRasterCut_Pixel_ok();

    /**
    * @fn TestLocalByMatch_ok()
    * @date 2012.3.18
    * @author
    * @brief ��������Ӱ��͵���Ӱ���ƥ��ʵ�ֶ�λ����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestLocalByMatch_ok();

    /**
    * @fn TestLocalByIntersection_ok()
    * @date 2012.3.18
    * @author
    * @brief ���Ժ󷽽��ᶨλ����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestLocalByIntersection_ok();

    /**
    * @fn TestLocalIn2Site_ok()
    * @date 2012.3.18
    * @author
    * @brief ����վ��䶨λ����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestLocalIn2Site_ok();

    /**
    * @fn TestLocalBySeqence_ok()
    * @date 2012.3.18
    * @author
    * @brief ��������Ӱ��λ����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestLocalBySeqence_ok();

    /**
    * @fn TestLocalByLander_ok()
    * @date 2012.3.18
    * @author
    * @brief ������½����λ����
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void TestLocalByLander_ok();




protected:
private:
};

#endif // CTESTKRINGING_H
