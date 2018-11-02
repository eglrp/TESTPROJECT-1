/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestGdalDataset.cpp
* @date 2012.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief GDALͼ�������������Դ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#include "TestGdalDataset.h"
#include "../mlRVML/mlGdalDataset.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CTestGdalDataset,"alltest" );
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
CTestGdalDataset::CTestGdalDataset()
{
    //ctor
}
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
CTestGdalDataset::~CTestGdalDataset()
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
void CTestGdalDataset::setUp()
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
void CTestGdalDataset::tearDown()
{

}
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
void CTestGdalDataset::TestLoadFile_ok()
{
    CmlGdalDataset cls;
    bool result = cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    CPPUNIT_ASSERT(result == true);
}
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
void CTestGdalDataset::TestLoadFile_ReturnFalse()
{
    CmlGdalDataset cls;
    bool result = cls.LoadFile(" ",1);
    CPPUNIT_ASSERT(result == false);
}
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
void CTestGdalDataset::TestCreateFile_ok()
{
    CmlGdalDataset cls;
    bool result = cls.CreateFile( "../../../UnitTestData/TestGdalDataset/a.tif", 100,100, 1, GDT_Byte,"GTIFF");
    CPPUNIT_ASSERT(result == true);
}
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
void CTestGdalDataset::TestCreateFile_ReturnFalse()
{
    CmlGdalDataset cls;
    bool result = cls.CreateFile( "d:/dd", 100,100, 1, GDT_Byte,"GTIFF");
    CPPUNIT_ASSERT(result == false);
}
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
void CTestGdalDataset::TestSaveBlockToFile_ok()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls,cls1;
    bool cc = cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    bool cc1 = cls.GetRasterOriginBlock((UINT)1,0,0,cls.GetWidth(),cls.GetHeight(),(UINT)1,&ImgBlock);
    DOUBLE tt,tt1,tt2;
    ImgBlock.GetDoubleVal(100,200,tt);
    ImgBlock.GetDoubleVal(615,387,tt1);
    ImgBlock.GetDoubleVal(700,200,tt2);
    bool cc2 = cls1.CreateFile( "../../../UnitTestData/TestGdalDataset/a.bmp", cls.GetWidth(),cls.GetHeight(), (UINT)1, GDT_Byte,"BMP");
    bool result = cls1.SaveBlockToFile( (UINT)1, 0, 0, &ImgBlock, (UINT)1 );
    CPPUNIT_ASSERT(result == true);
}
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
void CTestGdalDataset::TestSaveBlockToFile2_ok()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls,cls1;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
     cls.GetRasterOriginBlock((UINT)1,0,0,cls.GetWidth(),cls.GetHeight(),(UINT)1,&ImgBlock);
    cls1.CreateFile( "../../../UnitTestData/TestGdalDataset/b.tif", cls.GetWidth(),cls.GetHeight(), (UINT)1, GDT_Byte,"BMP");
    bool result = cls1.SaveBlockToFile( (UINT)1, 0, 0, &ImgBlock,0,0,cls.GetWidth(),cls.GetHeight(), (UINT)1 );
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestSaveBlockToFile_ReturnFalse
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Խ�դ��Ӱ�������ļ�����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestGdalDataset::TestSaveBlockToFile_ReturnFalse()
{
    CmlRasterBlock ImgBlock;

    CmlGdalDataset cls,cls1;
    //bool cc2 = cls1.CreateFile( "../../../UnitTestData/TestGdalDataset/a.bmp", cls.GetWidth(),cls.GetHeight(), (UINT)1, GDT_Byte,"BMP");
    bool result = cls1.SaveBlockToFile( (UINT)1, -1, -1, &ImgBlock, (UINT)1 );
    CPPUNIT_ASSERT(result == false);
}
/**
* @fn TestSaveBlockToFile2_ReturnFalse
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���Խ�դ��Ӱ�������ļ�����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestGdalDataset::TestSaveBlockToFile2_ReturnFalse()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls,cls1;
//    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
//     cls.GetRasterOriginBlock((UINT)1,0,0,cls.GetWidth(),cls.GetHeight(),(UINT)1,&ImgBlock);
//    cls1.CreateFile( "../../../UnitTestData/TestGdalDataset/b.tif", cls.GetWidth(),cls.GetHeight(), (UINT)1, GDT_Byte,"BMP");
    bool result = cls1.SaveBlockToFile( (UINT)1, -1, -1, &ImgBlock,0,0,cls.GetWidth(),cls.GetHeight(), (UINT)1 );
    CPPUNIT_ASSERT(result == false);
}
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
void CTestGdalDataset::TestGetRasterGrayBlock_ok()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    bool result = cls.GetRasterGrayBlock((UINT)1,0,0,cls.GetWidth(),cls.GetHeight(),(UINT)1,&ImgBlock);
    CPPUNIT_ASSERT(result == true);
}
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
void CTestGdalDataset::TestGetRasterGrayBlock2_ok()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    bool result = cls.GetRasterGrayBlock((UINT)1,0,0,cls.GetWidth(),cls.GetHeight(),1.5,&ImgBlock);
    CPPUNIT_ASSERT(result == true);
}
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
void CTestGdalDataset::TestGetRasterGrayBlock3_ok()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/029.PNG",1);
    bool result = cls.GetRasterGrayBlock((UINT)1,(UINT)2,(UINT)3,(UINT)0,(UINT)0,cls.GetWidth(),cls.GetHeight(),(UINT)1,&ImgBlock);
    CPPUNIT_ASSERT(result == true);
}
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
void CTestGdalDataset::TestGetRasterGrayBlock_ReturnFalse()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    bool result = cls.GetRasterGrayBlock((UINT)1,-1,-1,cls.GetWidth(),cls.GetHeight(),(UINT)1,&ImgBlock);
    CPPUNIT_ASSERT(result == false);
}
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
void CTestGdalDataset::TestGetRasterGrayBlock2_ReturnFalse()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    bool result = cls.GetRasterGrayBlock((UINT)1,-1,-1,cls.GetWidth(),cls.GetHeight(),1.5,&ImgBlock);
    CPPUNIT_ASSERT(result == false);
}
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
void CTestGdalDataset::TestGetRasterGrayBlock3_ReturnFalse()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/029.PNG",1);
    bool result = cls.GetRasterGrayBlock((UINT)1,(UINT)2,(UINT)3,(UINT)-1,(UINT)-1,cls.GetWidth(),cls.GetHeight(),(UINT)1,&ImgBlock);
    CPPUNIT_ASSERT(result == false);
}
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
void CTestGdalDataset::TestGetRasterOriginBlock_ok()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    bool result = cls.GetRasterOriginBlock((UINT)1,0,0,100,100,(UINT)1,&ImgBlock);
    CPPUNIT_ASSERT(result == true);
}
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
void CTestGdalDataset::TestGetRasterOriginBlock2_ok()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    bool result = cls.GetRasterOriginBlock((UINT)1,0,0,100,100,1.5,&ImgBlock);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestGetRasterOriginBlock_ReturnFalse
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ������GdalDataSet�еõ������Σ�����ԭʼ���ݵ���block�й���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestGdalDataset::TestGetRasterOriginBlock_ReturnFalse()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    bool result = cls.GetRasterOriginBlock((UINT)1,0,0,cls.GetWidth() *2 ,cls.GetHeight() *2 ,(UINT)1,&ImgBlock);
    CPPUNIT_ASSERT(result == false);
}
/**
* @fn TestGetRasterOriginBlock2_ReturnFalse
* @date 2011.12.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ������GdalDataSet�еõ������Σ�����ԭʼ���ݵ���block�й���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestGdalDataset::TestGetRasterOriginBlock2_ReturnFalse()
{
    CmlRasterBlock ImgBlock;
    CmlGdalDataset cls;
    cls.LoadFile( "../../../UnitTestData/TestGdalDataset/HCE1_B_0562.bmp",1);
    bool result = cls.GetRasterOriginBlock((UINT)1,0,0,cls.GetWidth() * 2 ,cls.GetHeight() * 2,1.5,&ImgBlock);
    CPPUNIT_ASSERT(result == false);
}
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
void CTestGdalDataset::TestSetNoDataVal_ok()
{
    CmlGdalDataset cls;
    bool result = cls.SetNoDataVal(-9999 );
    CPPUNIT_ASSERT(result == true);
}

