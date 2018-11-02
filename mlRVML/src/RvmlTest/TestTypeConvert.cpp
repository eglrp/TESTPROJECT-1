/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestTypeConvert.cpp
* @date 2012.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ת������Դ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#include "TestTypeConvert.h"
#include "../mlRVML/mlTypeConvert.h"
#include "../mlRVML/mlGeoRaster.h"
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CTestTypeConvert,"alltest" );
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
CTestTypeConvert::CTestTypeConvert()
{
    //ctor
}
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
CTestTypeConvert::~CTestTypeConvert()
{
    //dtor
}

/**
* @fn setup()
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ϵͳĬ�ϵĳ�ʼ������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestTypeConvert::setUp()
{

}
/**
* @fn tearDown()
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ϵͳĬ�ϵ����ٺ���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestTypeConvert::tearDown()
{

}
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
void CTestTypeConvert::TestIplImage2CmlRBlock_ok()
{
    CmlGeoRaster GeoRas;
    GeoRas.LoadGeoFile( "../../../UnitTestData/TestTypeConvert/test_dem.tif" );
    CmlRasterBlock DemBlock,Block;
    Block.InitialImg(GeoRas.GetHeight(),GeoRas.GetWidth(), 1);
    IplImage* pIplImg = NULL;
    GeoRas.GetRasterOriginBlock( GeoRas.GetBands(), (UINT)0, (UINT)0, GeoRas.GetWidth(), GeoRas.GetHeight(),(UINT)1, &DemBlock);
    CmlRBlock2IplImg(&DemBlock,pIplImg);
    bool result = IplImage2CmlRBlock(pIplImg,&Block);
    CPPUNIT_ASSERT(result == true);
}
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
void CTestTypeConvert::TestCmlRBlock2IplImg_ok()
{

    CmlGeoRaster GeoRas;
    GeoRas.LoadGeoFile( "../../../UnitTestData/TestTypeConvert/test_dem.tif" );
    CmlRasterBlock DemBlock;
    IplImage* pIplImg = NULL;
    GeoRas.GetRasterOriginBlock( GeoRas.GetBands(), (UINT)0, (UINT)0, GeoRas.GetWidth(), GeoRas.GetHeight(),(UINT)1, &DemBlock);
    bool result = CmlRBlock2IplImg(&DemBlock,pIplImg);
    CPPUNIT_ASSERT(result == true);

}
