#include "TestDemAnalyse.h"
#include "../mlRVML/mlDemAnalyse.h"
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CTestDemAnalyse,"alltest" );

CTestDemAnalyse::CTestDemAnalyse()
{
    //ctor
}

CTestDemAnalyse::~CTestDemAnalyse()
{
    //dtor
}

/** @brief tearDown
  *
  * @todo: document this function
  */
void CTestDemAnalyse::tearDown()
{

}

/** @brief setUp
  *
  * @todo: document this function
  */
void CTestDemAnalyse::setUp()
{

}
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
    void CTestDemAnalyse::ComputeViewShedInterface_OK()
    {
        //SINT ComputeViewShedInterface(SCHAR * sInputDEM, SINT nxLocation ,SINT nyLocation, DOUBLE dViewHight, SCHAR * sDestDEM);
        char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/ViewShed/ViewShed.tif";
        int x = 0;
        int y = 0;
        double h = 2;
        CmlDemAnalyse cda;
        int result = cda.ComputeViewShedInterface(srcfilename,x,y,h,dstfilename,true);
        CPPUNIT_ASSERT(result == 1);
    }
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
    void CTestDemAnalyse::ComputeViewShedInterface_ReturnM2()
    {
        char* srcfilename = " ";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/ViewShed/ViewShed.tif";
        int x = 0;
        int y = 0;
        double h = 2;
        CmlDemAnalyse cda;
        int result = cda.ComputeViewShedInterface(srcfilename,x,y,h,dstfilename);
        CPPUNIT_ASSERT(result == -2);
    }

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
    void CTestDemAnalyse::ComputeViewShedInterface_ReturnM4()
    {
        char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/ViewShed/ViewShed.tif";
        int x = -10;
        int y = -1;
        double h = 2;
        CmlDemAnalyse cda;
        int result = cda.ComputeViewShedInterface(srcfilename,x,y,h,dstfilename);
        CPPUNIT_ASSERT(result == -4);
    }


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
    void CTestDemAnalyse::ComputeSlopeInterface_OK()
    {
        //SINT ComputeSlopeInterface(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor );
         char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
         char* dstfilename = "../../../UnitTestData/DEMAnalyse/Slope/Slope.tif";
         int nWindowSize = 3;
         double dzfactor = 1;
         CmlDemAnalyse cda;
         int result = cda.ComputeSlopeInterface(srcfilename,dstfilename,nWindowSize,dzfactor);
         CPPUNIT_ASSERT(result == 1);
    }
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
    void CTestDemAnalyse::ComputeSlopeInterface_ReturnM1()
    {
        char* srcfilename = "../";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/Slope/Slope.tif";
        int nWindowSize = 3;
        double dzfactor = 1;
        CmlDemAnalyse cda;
        int result = cda.ComputeSlopeInterface(srcfilename,dstfilename,nWindowSize,dzfactor);
        CPPUNIT_ASSERT(result == -1);
    }

    /**
    * @fn ComputeSlopeAspectInterface_ReturnM2()
    * @date 2012.2.8
    * @author ��Ρ
    * @brief �����¶�ʧ��ʱ��������ͼ�Ĺ���
    * @version 1.1
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    *
    */
    void CTestDemAnalyse::ComputeSlopeInterface_ReturnM2()
    {
        char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/Slope/Slope.tif";
        int nWindowSize = 4;
        double dzfactor = 1;
        CmlDemAnalyse cda;
        int result = cda.ComputeSlopeInterface(srcfilename,dstfilename,nWindowSize,dzfactor);
        CPPUNIT_ASSERT(result == -2);
    }

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
    void CTestDemAnalyse::ComputeSlopeAspectInterface_OK()
    {
     //SINT ComputeSlopeAspectInterface(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor);
          char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
          char* dstfilename = "../../../UnitTestData/DEMAnalyse/SlopeAspect/SlopeAspect.tif";
          int nWindowSize = 3;
          double dZfactor = 1;
          CmlDemAnalyse cda;
          int result = cda.ComputeSlopeAspectInterface(srcfilename, dstfilename, nWindowSize, dZfactor);
          CPPUNIT_ASSERT(result == 1);
    }
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
    void CTestDemAnalyse::ComputeSlopeAspectInterface_ReturnM1()
    {
          char* srcfilename = "../../..h";
          char* dstfilename = "../../../UnitTestData/DEMAnalyse/SlopeAspect/SlopeAspect.tif";
          int nWindowSize = 3;
          double dZfactor = 1;
          CmlDemAnalyse cda;
          int result = cda.ComputeSlopeAspectInterface(srcfilename, dstfilename, nWindowSize, dZfactor);
          CPPUNIT_ASSERT(result == -1);
    }
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
    void CTestDemAnalyse::ComputeSlopeAspectInterface_ReturnM2()
    {
          char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
          char* dstfilename = "../../../UnitTestData/DEMAnalyse/SlopeAspect/SlopeAspect.tif";
          int nWindowSize = 2;
          double dZfactor = 1;
          CmlDemAnalyse cda;
          int result = cda.ComputeSlopeAspectInterface(srcfilename, dstfilename, nWindowSize, dZfactor);
          CPPUNIT_ASSERT(result == -2);
    }

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
    void CTestDemAnalyse::ComputeObstacleMapInterface_OK()
    {
        //SINT ComputeObstacleMapInterface(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor,ObstacleMapPara ObPara);
        char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/Obstacle/Obstacle.tif";
        int nWindowSize = 3;
        double dZfactor = 1;
        CmlDemAnalyse cda;
        ObstacleMapPara obpara;
        obpara.dMaxObstacleValue = 2;
        obpara.dMaxRoughness = 0.1;
        obpara.dMaxSlope = 25;
        obpara.dMaxStep = 0.1;
        obpara.dRoughnessCoef = 100;
        obpara.dSlopeCoef = 100;
        obpara.dStepCoef = 100;
        int result = cda.ComputeObstacleMapInterface(srcfilename,dstfilename,nWindowSize,dZfactor,obpara);
        CPPUNIT_ASSERT(result == 1);

    }

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
    void CTestDemAnalyse::ComputeObstacleMapInterface_ReturnM1()
    {
         //SINT ComputeObstacleMapInterface(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor,ObstacleMapPara ObPara);
        char* srcfilename = "";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/Obstacle/Obstacle.tif";
        int nWindowSize = 3;
        double dZfactor = 1;
        CmlDemAnalyse cda;
        ObstacleMapPara obpara;
        obpara.dMaxObstacleValue = 100;
        obpara.dMaxRoughness = 0.5;
        obpara.dMaxSlope = 25;
        obpara.dMaxStep = 0.6;
        obpara.dRoughnessCoef = 100;
        obpara.dSlopeCoef = 100;
        obpara.dStepCoef = 100;
        int result = cda.ComputeObstacleMapInterface(srcfilename,dstfilename,nWindowSize,dZfactor,obpara);
        CPPUNIT_ASSERT(result == -1);
    }

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
    void CTestDemAnalyse::ComputeObstacleMapInterface_ReturnM2()
    {
         //SINT ComputeObstacleMapInterface(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor,ObstacleMapPara ObPara);
        char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/Obstacle/Obstacle.tif";
        int nWindowSize = 3;
        double dZfactor = 1;
        CmlDemAnalyse cda;
        ObstacleMapPara obpara;
        obpara.dMaxObstacleValue = 0.00000001;
        obpara.dMaxRoughness = 0.5;
        obpara.dMaxSlope = 25;
        obpara.dMaxStep = 0.6;
        obpara.dRoughnessCoef = 100;
        obpara.dSlopeCoef = 100;
        obpara.dStepCoef = 100;
        int result = cda.ComputeObstacleMapInterface(srcfilename,dstfilename,nWindowSize,dZfactor,obpara);
        CPPUNIT_ASSERT(result == 1);
    }


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
    void CTestDemAnalyse::ComputeContourInterface_OK()
    {
        //SINT ComputeContourInterface(DOUBLE dHinterval,   SCHAR* strSrcfilename,   SCHAR* strDstfilename ,bool bCNodata = FALSE, DOUBLE dNodata = 0.0,  SCHAR* cAttrib = "elev");
        char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/Contour/ddd.shp";
        int nWindowSize = 3;
        double dzfactor = 1;
        double dhinterval = 0.4;
        CmlDemAnalyse cda;
        int result = cda.ComputeContourInterface(dhinterval,srcfilename,dstfilename);
        CPPUNIT_ASSERT(result == 1);
    }

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
     void CTestDemAnalyse::ComputeContourInterface_ReturnM2()
     {
          //SINT ComputeContourInterface(DOUBLE dHinterval,   SCHAR* strSrcfilename,   SCHAR* strDstfilename ,bool bCNodata = FALSE, DOUBLE dNodata = 0.0,  SCHAR* cAttrib = "elev");
        char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/Contour/ddd.shp";
        int nWindowSize = 3;
        double dzfactor = 1;
        double dhinterval = 0;
        CmlDemAnalyse cda;
        int result = cda.ComputeContourInterface(dhinterval,srcfilename,dstfilename);
        CPPUNIT_ASSERT(result == -2);
     }

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
    void CTestDemAnalyse::ComputeContourInterface_ReturnM3()
    {
        //SINT ComputeContourInterface(DOUBLE dHinterval,   SCHAR* strSrcfilename,   SCHAR* strDstfilename ,bool bCNodata = FALSE, DOUBLE dNodata = 0.0,  SCHAR* cAttrib = "elev");
        char* srcfilename = "../../../UnitTestDa";
        char* dstfilename = "../../../UnitTestData/DEMAnalyse/Contour/ddd.shp";
        int nWindowSize = 3;
        double dzfactor = 1;
        double dhinterval = 0.4;
        CmlDemAnalyse cda;
        int result = cda.ComputeContourInterface(dhinterval,srcfilename,dstfilename);
        CPPUNIT_ASSERT(result == -3);
    }

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
    void CTestDemAnalyse::ComputeContourInterface_ReturnM4()
    {
         //SINT ComputeContourInterface(DOUBLE dHinterval,   SCHAR* strSrcfilename,   SCHAR* strDstfilename ,bool bCNodata = FALSE, DOUBLE dNodata = 0.0,  SCHAR* cAttrib = "elev");
        char* srcfilename = "../../../UnitTestData/DEMAnalyse/SiteDem1.tif";
        char* dstfilename = "";
        int nWindowSize = 3;
        double dzfactor = 1;
        double dhinterval = 0.4;
        CmlDemAnalyse cda;
        int result = cda.ComputeContourInterface(dhinterval,srcfilename,dstfilename);
        CPPUNIT_ASSERT(result == -4);
    }
