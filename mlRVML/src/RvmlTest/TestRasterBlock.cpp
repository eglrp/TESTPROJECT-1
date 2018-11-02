/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestRasterBlock.cpp
* @date 2012.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief դ�����ݿ鴦�����Դ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#include "TestRasterBlock.h"
#include "../mlRVML/mlRasterBlock.h"
#include "../mlRVML/mlGeoRaster.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CTestRasterBlock,"alltest" );
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
CTestRasterBlock::CTestRasterBlock()
{
    //ctor
}
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
CTestRasterBlock::~CTestRasterBlock()
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
void CTestRasterBlock::setUp()
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
void CTestRasterBlock::tearDown()
{

}

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
void CTestRasterBlock::TestInitialImg_ok()
{
    CmlRasterBlock cls;
    bool result = cls.InitialImg( 3,3,8);
    CPPUNIT_ASSERT(result == true);
}
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
void CTestRasterBlock::TestInitialImg_ReturnFalse()
{
    CmlRasterBlock cls;
    bool result = cls.InitialImg( 1,1,8);
    result = cls.InitialImg(1,1,8);
    CPPUNIT_ASSERT(result == false);
}
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
void CTestRasterBlock::TestReSet_ok()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    cls.SetAt(0,0,250);
    bool result = cls.ReSet();
    CPPUNIT_ASSERT(result == true);
}
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
void CTestRasterBlock::TestClear_ok()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    cls.SetAt(0,0,250);
    bool result = cls.Clear();
    CPPUNIT_ASSERT(result == true);
}
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
void CTestRasterBlock::TestGetPtrAt_ok()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    cls.SetAt(0,0,5);
    BYTE* result = cls.GetPtrAt(0,0);
    CPPUNIT_ASSERT(*result == 5);
}
/**
* @fn TestGetPtrAt_ReturnFalse
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Եõ�ĳ��������ֵ��ͷָ�빦���ݴ���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestRasterBlock::TestGetPtrAt_ReturnFalse()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    cls.SetAt(0,0,5);
    BYTE* result = cls.GetPtrAt(9999,9999);
    CPPUNIT_ASSERT(result == NULL);
}
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
void CTestRasterBlock::TestSetPtrAt_ok()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    DOUBLE res = 5;
    bool result = cls.SetPtrAt(0,0,(BYTE*)(&res));
    CPPUNIT_ASSERT(result == true);
}
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
void CTestRasterBlock::TestSetPtrAt_ReturnFalse()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    DOUBLE res = 5;
    bool result = cls.SetPtrAt(9999,9999,(BYTE*)(&res));
    CPPUNIT_ASSERT(result == false);
}
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
void CTestRasterBlock::TestGetAt_ok()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    cls.SetAt(0,0,250);
    BYTE result = cls.GetAt(0,0);
    CPPUNIT_ASSERT(result == 250);
}
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
void CTestRasterBlock::TestSetAt_ok()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    bool result = cls.SetAt(0,0,250);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestSetAt_ReturnFalse
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��������դ���ĳ�����������һ���ֽ�ֵ����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestRasterBlock::TestSetAt_ReturnFalse()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    bool result = cls.SetAt(-1,-1,250);
    CPPUNIT_ASSERT(result == false);
}
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
void CTestRasterBlock::TestGetDoubleVal_ok()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    cls.SetAt(0,0,250);
    cls.SetGDTType(GDT_Byte);
    DOUBLE res;
    bool result = cls.GetDoubleVal(0,0,res);
    CPPUNIT_ASSERT(result == true);
}
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
void CTestRasterBlock::TestGetDoubleVal_ReturnFalse()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    cls.SetAt(0,0,250);
    cls.SetGDTType(GDT_Byte);
    DOUBLE res;
    bool result = cls.GetDoubleVal(-1,-1,res);
    CPPUNIT_ASSERT(result == false);
}
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
void CTestRasterBlock::TestSetDoubleVal_ok()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    bool result = cls.SetDoubleVal(0,0,250);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestSetDoubleVal_ReturnFalse
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �����������ݿ������ص�ֵ����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestRasterBlock::TestSetDoubleVal_ReturnFalse()
{
    CmlRasterBlock cls;
    cls.InitialImg(3,3,8);
    bool result = cls.SetDoubleVal(-1,-1,250);
    CPPUNIT_ASSERT(result == false);
}
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
void CTestRasterBlock::TestGetGeoXYZ_ok()
{
    CmlGeoRaster GeoRas;
    GeoRas.LoadGeoFile( "../../../UnitTestData/TestRasterBlock/test_dem.tif" );
    CmlRasterBlock DemBlock;
    GeoRas.GetRasterOriginBlock( GeoRas.GetBands(), (UINT)0, (UINT)0, GeoRas.GetWidth(), GeoRas.GetHeight(),(UINT)1, &DemBlock);
    Pt3d tmpXYZ;
    bool result = DemBlock.GetGeoXYZ( 100, 100, tmpXYZ );
    CPPUNIT_ASSERT(result == true);
}
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
void CTestRasterBlock::TestGetGeoXYZ_ReturnFalse()
{
    CmlGeoRaster GeoRas;
    GeoRas.LoadGeoFile( "../../../UnitTestData/TestRasterBlock/test_dem.tif" );
    CmlRasterBlock DemBlock;
    GeoRas.GetRasterOriginBlock( GeoRas.GetBands(), (UINT)0, (UINT)0, GeoRas.GetWidth(), GeoRas.GetHeight(),(UINT)1, &DemBlock);
    Pt3d tmpXYZ;
    bool result = DemBlock.GetGeoXYZ( -1, 1, tmpXYZ );
    CPPUNIT_ASSERT(result == false);
}
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
void CTestRasterBlock::TestGetGeoZ_ok()
{
    CmlGeoRaster GeoRas;
    GeoRas.LoadGeoFile( "../../../UnitTestData/TestRasterBlock/test_dem.tif" );
    CmlRasterBlock DemBlock;
    GeoRas.GetRasterOriginBlock( GeoRas.GetBands(), (UINT)0, (UINT)0, GeoRas.GetWidth(), GeoRas.GetHeight(),(UINT)1, &DemBlock);
    DOUBLE dZ;
    bool result = DemBlock.GetGeoZ( -30.5, 48.5, dZ );
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestGetGeoZ_ReturnFalse
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Եõ���������Ϣ�����ݿ��ڵ���ά�߳�ֵ����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestRasterBlock::TestGetGeoZ_ReturnFalse()
{
    CmlGeoRaster GeoRas;
    GeoRas.LoadGeoFile( "../../../UnitTestData/TestRasterBlock/test_dem.tif" );
    CmlRasterBlock DemBlock;
    GeoRas.GetRasterOriginBlock( GeoRas.GetBands(), (UINT)0, (UINT)0, GeoRas.GetWidth(), GeoRas.GetHeight(),(UINT)1, &DemBlock);
    DOUBLE dZ;
    bool result = DemBlock.GetGeoZ( -99999, -99999, dZ );
    CPPUNIT_ASSERT(result == false);
}
