/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestFrameImage.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ�������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#include "TestFrameImage.h"
#include "../mlRVML/mlFrameImage.h"
#include "../mlRVML/mlStereoProc.h"
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CTestFrameImage,"alltest" );

CTestFrameImage::CTestFrameImage()
{
    //ctor
}

CTestFrameImage::~CTestFrameImage()
{
    //dtor
}

/** @brief tearDown
  *
  * @todo: document this function
  */
void CTestFrameImage::tearDown()
{

}

/** @brief setUp
  *
  * @todo: document this function
  */
void CTestFrameImage::setUp()
{

}

/** @brief TestLoadFile
  *
  * @todo: document this function
  */
void CTestFrameImage::TestLoadFile_ok()
{
    printf( "TestLoadFile ok!" );
}

/**
* @fn TestGetUnDistortImg_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief �����������Ӱ�����У������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestGetUnDistortImg_ok()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlStereoProc cls;
    //��Ƭ
    LImg.m_InOriPara.x = 684.565648;
    LImg.m_InOriPara.y = LImg.GetHeight() - 1 - 513.464857;// Img.GetH()-1-
    LImg.m_InOriPara.f = 1864.761157;
    LImg.m_InOriPara.k1=0.000000003701370547;
    LImg.m_InOriPara.k2=  0.000000000000015758;
    LImg.m_InOriPara.p1 = -0.000000425948117210;
    LImg.m_InOriPara.p2 = -0.000001116050338642;
    LImg.m_InOriPara.alpha = 0.000469724979289230;
    LImg.m_InOriPara.beta = -0.000337221522638987;
    cls.m_pDataL = &LImg;
    bool result = LImg.GetUnDistortImg();
    CPPUNIT_ASSERT(result == true);

}
/**
* @fn TestGetUnDistortImg2_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief �����������Ӱ�����У������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestGetUnDistortImg2_ok()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlStereoProc cls;
    //��Ƭ
    LImg.m_InOriPara.x = 684.565648;
    LImg.m_InOriPara.y = LImg.GetHeight() - 1 - 513.464857;
    LImg.m_InOriPara.f = 1864.761157;
    LImg.m_InOriPara.k1=0.000000003701370547;
    LImg.m_InOriPara.k2=  0.000000000000015758;
    LImg.m_InOriPara.p1 = -0.000000425948117210;
    LImg.m_InOriPara.p2 = -0.000001116050338642;
    LImg.m_InOriPara.alpha = 0.000469724979289230;
    LImg.m_InOriPara.beta = -0.000337221522638987;
    cls.m_pDataL = &LImg;
    CmlRasterBlock tmpBlock;
    tmpBlock.InitialImg( LImg.GetHeight(), LImg.GetWidth() );
    bool result = LImg.GetUnDistortImg( &LImg.m_DataBlock, &tmpBlock );

    CPPUNIT_ASSERT(result == true);
}
/**
* @fn UnDisCorToPlaneFrame_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ��������������겢ת������ƽ������ϵ����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::UnDisCorToPlaneFrame_ok()
{
    CmlFrameImage cls;
    cls.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    vector<Pt2d> imgInList,imgOutList;
    Pt2d tmp;
    tmp.X = 216.864746;	tmp.Y = cls.GetHeight() -1 - 881.929291;
    imgInList.push_back(tmp);
    tmp.X = 398.622620;	tmp.Y = cls.GetHeight() -1 - 691.070984;
    imgInList.push_back(tmp);
    tmp.X = 650.237000;	tmp.Y = cls.GetHeight() -1 - 234.621033;
    imgInList.push_back(tmp);
    tmp.X = 1214.718262;tmp.Y = cls.GetHeight() -1 - 523.570374;
    imgInList.push_back(tmp);
    tmp.X = 912.011230;	tmp.Y = cls.GetHeight() -1 - 413.146851;
    imgInList.push_back(tmp);
    InOriPara inPara;
    inPara.x = 736.149;
    inPara.y = 519.348;
    inPara.k1 = 9.71074e-09;
    inPara.k2 = -1.2148e-14;
    inPara.k3 = 2.84341e-20;
    inPara.p1 = 3.45027e-06;
    inPara.p2 = 3.23775e-06;
    inPara.alpha = -0.00211251;
    inPara.beta = -0.00211332;
    inPara.f = 5287.2;
    bool result = cls.UnDisCorToPlaneFrame(imgInList, inPara, imgOutList );
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn UnDisCorToPicCoord_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���������������.ת����ͼ������ϵ����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::UnDisCorToPicCoord_ok()
{
CmlFrameImage cls;
    vector<Pt2d> imgInList,imgOutList;
    imgInList.clear();
    imgOutList.clear();
    cls.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    Pt2d tmp;
    tmp.X = 216.864746;	tmp.Y = cls.GetHeight() -1 - 881.929291;
    imgInList.push_back(tmp);
    tmp.X = 398.622620;	tmp.Y = cls.GetHeight() -1 - 691.070984;
    imgInList.push_back(tmp);
    tmp.X = 650.237000;	tmp.Y = cls.GetHeight() -1 - 234.621033;
    imgInList.push_back(tmp);
    tmp.X = 1214.718262;tmp.Y = cls.GetHeight() -1 - 523.570374;
    imgInList.push_back(tmp);
    tmp.X = 912.011230;	tmp.Y = cls.GetHeight() -1 - 413.146851;
    imgInList.push_back(tmp);
    InOriPara inPara;
    inPara.x = 736.149;
    inPara.y = cls.GetHeight() -1 - 519.348;
    inPara.k1 = 9.71074e-09;
    inPara.k2 = -1.2148e-14;
    inPara.k3 = 2.84341e-20;
    inPara.p1 = 3.45027e-06;
    inPara.p2 = 3.23775e-06;
    inPara.alpha = -0.00211251;
    inPara.beta = -0.00211332;
    inPara.f = 5287.2;
    bool result = cls.UnDisCorToPicCoord(imgInList, inPara, imgOutList );
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn BilinearInterpolation_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����˫�����ڲ幦��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestBilinearInterpolation_ok()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlStereoProc cls;
    //��Ƭ
    LImg.m_InOriPara.x = 684.565648;
    LImg.m_InOriPara.y = LImg.GetHeight() - 1 - 513.464857;// Img.GetH()-1-
    LImg.m_InOriPara.f = 1864.761157;
    LImg.m_InOriPara.k1=0.000000003701370547;
    LImg.m_InOriPara.k2=  0.000000000000015758;
    LImg.m_InOriPara.p1 = -0.000000425948117210;
    LImg.m_InOriPara.p2 = -0.000001116050338642;
    LImg.m_InOriPara.alpha = 0.000469724979289230;
    LImg.m_InOriPara.beta = -0.000337221522638987;
    cls.m_pDataL = &LImg;
    CmlRasterBlock tmpBlock;
    tmpBlock.InitialImg( LImg.GetHeight(), LImg.GetWidth() );
    //LImg.GetUnDistortImg( &m_DataBlock, &tmpBlock );
    bool H = LImg.GetRasterGrayBlock(LImg.GetBands(),0, 0,  LImg.GetWidth(), LImg.GetHeight(),(UINT)1, &tmpBlock);
    CRasterPt2D Coordinate;
    Coordinate.Initial(tmpBlock.GetH(),tmpBlock.GetW());
    bool H1,H2;
    CmlRasterBlock pOutImg;
    H1 = LImg.mlGetDistortionCoordinate( &tmpBlock , &Coordinate);
    bool result = LImg.mlBilinearInterpolation( &tmpBlock,&Coordinate,&pOutImg);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn GetDistortionCoordinate_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���������������깦��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestGetDistortionCoordinate_ok()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlStereoProc cls;
    //��Ƭ
    LImg.m_InOriPara.x = 684.565648;
    LImg.m_InOriPara.y = LImg.GetHeight() - 1 - 513.464857;
    LImg.m_InOriPara.f = 1864.761157;
    LImg.m_InOriPara.k1=0.000000003701370547;
    LImg.m_InOriPara.k2=  0.000000000000015758;
    LImg.m_InOriPara.p1 = -0.000000425948117210;
    LImg.m_InOriPara.p2 = -0.000001116050338642;
    LImg.m_InOriPara.alpha = 0.000469724979289230;
    LImg.m_InOriPara.beta = -0.000337221522638987;
    cls.m_pDataL = &LImg;
    CmlRasterBlock tmpBlock;
    tmpBlock.InitialImg( LImg.GetHeight(), LImg.GetWidth() );
    bool H = LImg.GetRasterGrayBlock(LImg.GetBands(),0, 0,  LImg.GetWidth(), LImg.GetHeight(),(UINT)1, &tmpBlock);
    CRasterPt2D Coordinate;
    Coordinate.Initial(tmpBlock.GetH(),tmpBlock.GetW());
    CmlRasterBlock pOutImg;
    bool result = LImg.mlGetDistortionCoordinate( &tmpBlock , &Coordinate);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn GetDistortionCoordinate_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����ͼ��Ҷ��ڲ幦��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestGrayInterpolation_ok()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlStereoProc cls;
    //��Ƭ
    LImg.m_InOriPara.x = 684.565648;
    LImg.m_InOriPara.y = LImg.GetHeight() - 1 - 513.464857;// Img.GetH()-1-
    LImg.m_InOriPara.f = 1864.761157;
    LImg.m_InOriPara.k1=0.000000003701370547;
    LImg.m_InOriPara.k2=  0.000000000000015758;
    LImg.m_InOriPara.p1 = -0.000000425948117210;
    LImg.m_InOriPara.p2 = -0.000001116050338642;
    LImg.m_InOriPara.alpha = 0.000469724979289230;
    LImg.m_InOriPara.beta = -0.000337221522638987;
    cls.m_pDataL = &LImg;
    CmlRasterBlock tmpBlock;
    tmpBlock.InitialImg( LImg.GetHeight(), LImg.GetWidth() );
    //LImg.GetUnDistortImg( &m_DataBlock, &tmpBlock );
    bool H = LImg.GetRasterGrayBlock(LImg.GetBands(),0, 0,  LImg.GetWidth(), LImg.GetHeight(),(UINT)1, &tmpBlock);
    CRasterPt2D Coordinate;
    Coordinate.Initial(tmpBlock.GetH(),tmpBlock.GetW());
    bool H1,H2;
    CmlRasterBlock pOutImg;
    H1 = LImg.mlGetDistortionCoordinate( &tmpBlock , &Coordinate);
    bool result = LImg.mlGrayInterpolation( &tmpBlock,&Coordinate,&pOutImg,0);
    CPPUNIT_ASSERT(result == true);
}

/**
* @fn GetBilinearValue_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ��Ҷ�ֵ��˫�����ڲ幦��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestGetBilinearValue_ok()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlRasterBlock LimgBlock;
    LImg.GetRasterGrayBlock(LImg.GetBands(),0, 0, 1000, 1000, (UINT)1, &LimgBlock);
    Pt2d tmpXY;
    tmpXY.X = 200.7;
    tmpXY.Y = 500.1;
    BYTE result = LImg.mlGetBilinearValue(&LimgBlock,tmpXY);
    CPPUNIT_ASSERT(result != false );
}

/**
* @fn TestCleanDeadPix_ok
* @date 2011.12.1
* @author ������ zhangchy@irsa.ac.cn
* @brief ��������ͼ��ȥ�����㹦��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestCleanDeadPix_ok()
{
    CmlFrameImage frImg;
    char* in = "../../../UnitTestData/TestFrameImage/deadPix.tif";
    char* out = "../../../UnitTestData/TestFrameImage/aaFrame.tif";
    Pt2i pt2i;
    pt2i.X = 1;
    pt2i.Y = 2;
    vector<Pt2i> vecPt2i;
    ifstream infile("../../../UnitTestData/TestFrameImage/deadpix.txt");
    char x,y;
    infile >> x >> y;
    while(!infile.eof())
    {
        infile >> pt2i.X  >> pt2i.Y;
        vecPt2i.push_back(pt2i);

    }

    bool result = frImg.mlCleanDeadPix(in,out,vecPt2i);
    CPPUNIT_ASSERT(result == true);

}
/**
* @fn TestCleanDeadPix_abnormal
* @date 2011.12.1
* @author ������ zhangchy@irsa.ac.cn
* @brief ����mlCleanDeadPix��������Ӱ��Ϊ�յ��쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestCleanDeadPix_abnormal()
{
    CmlFrameImage frImg;
    char* in = "../../../UnitTestData/TestFrameImage/deadPix.tif";
    char* out = "../../../UnitTestData/TestFrameImage/aaFrame.tif";
    Pt2i pt2i;
    pt2i.X = 1;
    pt2i.Y = 2;
    vector<Pt2i> vecPt2i;
    bool result = frImg.mlCleanDeadPix(in,out,vecPt2i);
    CPPUNIT_ASSERT(result == false);

}
/**
* @fn GetBilinearValue_abnormal
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����mlGetBilinearValue��������Ӱ���Ϊ�յ��쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestGetBilinearValue_abnormal()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlRasterBlock LimgBlock;
    //LImg.GetRasterGrayBlock(LImg.GetBands(),0, 0, 1000, 1000, (UINT)1, &LimgBlock);
    Pt2d tmpXY;
    tmpXY.X = 200.7;
    tmpXY.Y = 500.1;
    BYTE result = LImg.mlGetBilinearValue(&LimgBlock,tmpXY);
    CPPUNIT_ASSERT(result == false);
}

/**
* @fn TestGrayInterpolation_abnormal
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����mlGrayInterpolation��������Ӱ��Ϊ�յ��쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestGrayInterpolation_abnormal()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlStereoProc cls;
    //��Ƭ
    LImg.m_InOriPara.x = 684.565648;
    LImg.m_InOriPara.y = LImg.GetHeight() - 1 - 513.464857;// Img.GetH()-1-
    LImg.m_InOriPara.f = 1864.761157;
    LImg.m_InOriPara.k1=0.000000003701370547;
    LImg.m_InOriPara.k2=  0.000000000000015758;
    LImg.m_InOriPara.p1 = -0.000000425948117210;
    LImg.m_InOriPara.p2 = -0.000001116050338642;
    LImg.m_InOriPara.alpha = 0.000469724979289230;
    LImg.m_InOriPara.beta = -0.000337221522638987;
    cls.m_pDataL = &LImg;
    CmlRasterBlock tmpBlock;
    CRasterPt2D Coordinate;
    Coordinate.Initial(tmpBlock.GetH(),tmpBlock.GetW());
    bool H1,H2;
    CmlRasterBlock pOutImg;
    H1 = LImg.mlGetDistortionCoordinate( &tmpBlock , &Coordinate);
    bool result = LImg.mlGrayInterpolation( &tmpBlock,&Coordinate,&pOutImg,0);
    CPPUNIT_ASSERT(result == false);
}

/**
* @fn TestBilinearInterpolation_abnormal
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����mlBilinearInterpolation��������Ӱ��Ϊ�յ��쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestBilinearInterpolation_abnormal()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlStereoProc cls;
    //��Ƭ
    LImg.m_InOriPara.x = 684.565648;
    LImg.m_InOriPara.y = LImg.GetHeight() - 1 - 513.464857;// Img.GetH()-1-
    LImg.m_InOriPara.f = 1864.761157;
    LImg.m_InOriPara.k1=0.000000003701370547;
    LImg.m_InOriPara.k2=  0.000000000000015758;
    LImg.m_InOriPara.p1 = -0.000000425948117210;
    LImg.m_InOriPara.p2 = -0.000001116050338642;
    LImg.m_InOriPara.alpha = 0.000469724979289230;
    LImg.m_InOriPara.beta = -0.000337221522638987;
    cls.m_pDataL = &LImg;
    CmlRasterBlock tmpBlock;
    CRasterPt2D Coordinate;
    Coordinate.Initial(tmpBlock.GetH(),tmpBlock.GetW());
    bool H1,H2;
    CmlRasterBlock pOutImg;
    H1 = LImg.mlGetDistortionCoordinate( &tmpBlock , &Coordinate);
    bool result = LImg.mlBilinearInterpolation( &tmpBlock,&Coordinate,&pOutImg);
    CPPUNIT_ASSERT(result == false);
}

/**
* @fn TestGetDistortionCoordinate_abnormal
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����mlGetDistortionCoordinate��������Ӱ��Ϊ�յ��쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestGetDistortionCoordinate_abnormal()
{
    CmlFrameImage LImg;
    LImg.LoadFile("../../../UnitTestData/TestFrameImage/L_1.bmp");
    CmlStereoProc cls;
    //��Ƭ
    LImg.m_InOriPara.x = 684.565648;
    LImg.m_InOriPara.y = LImg.GetHeight() - 1 - 513.464857;
    LImg.m_InOriPara.f = 1864.761157;
    LImg.m_InOriPara.k1=0.000000003701370547;
    LImg.m_InOriPara.k2=  0.000000000000015758;
    LImg.m_InOriPara.p1 = -0.000000425948117210;
    LImg.m_InOriPara.p2 = -0.000001116050338642;
    LImg.m_InOriPara.alpha = 0.000469724979289230;
    LImg.m_InOriPara.beta = -0.000337221522638987;
    cls.m_pDataL = &LImg;
    CmlRasterBlock tmpBlock;
    CRasterPt2D Coordinate;
    CmlRasterBlock pOutImg;
    bool result = LImg.mlGetDistortionCoordinate( &tmpBlock , &Coordinate);
    CPPUNIT_ASSERT(result == false);
}

/**
* @fn TestExtractFeatPtByForstner_abnormal
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����ExtractFeatPtByForstner��������Ӱ����޷�ת����IplImg���쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestExtractFeatPtByForstner_abnormal()
{
    CmlFrameImage clsImgL;
    clsImgL.SmoothByGuassian(  7, 0.6 );
    bool result = clsImgL.ExtractFeatPtByForstner( 5 );
    CPPUNIT_ASSERT(result == false);
}
/**
* @fn TestExtractFeatPtByForstner_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief �����������Ӱ��Forstner������ȡ�����㹦��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestFrameImage::TestExtractFeatPtByForstner_ok()
{
    CmlFrameImage clsImgL;
    clsImgL.LoadFile( "../../../UnitTestData/TestFrameImage/L_1.bmp" );
    clsImgL.SmoothByGuassian(  7, 0.6 );
    bool result = clsImgL.ExtractFeatPtByForstner( 5 );
    CPPUNIT_ASSERT(result == true);
}


