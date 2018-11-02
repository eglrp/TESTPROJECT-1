/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file TestBlockCalculation.cpp
* @date 2012.2.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief Ӱ��ֿ����Դ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#include "TestBlockCalculation.h"
#include "../mlRVML/mlBlockCalculation.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CTestBlockCalculation,"alltest" );
/**
* @fn CTestBlockCalculation
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief �ղι��캯��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
CTestBlockCalculation::CTestBlockCalculation()
{
    //ctor
}
/**
* @fn ~CTestBlockCalculation
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
CTestBlockCalculation::~CTestBlockCalculation()
{
    //dtor
}

/**
* @fn setup()
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ϵͳĬ�ϵĳ�ʼ������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestBlockCalculation::setUp()
{

}
/**
* @fn tearDown()
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ϵͳĬ�ϵ����ٺ���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*
*/
void CTestBlockCalculation::tearDown()
{

}

/**
* @fn TestCalBlockCol_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���Ӱ�����У�X������ֿ�Ĵ�С�Ŀ�������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestCalBlockCol_ok()
{
    CmlBlockCalculation cls;
    bool result = cls.CalBlockCol(5000,2000);
    CPPUNIT_ASSERT(result == true);

}
/**
* @fn TestCalBlockRow_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���Ӱ�����У�Y������ֿ�Ĵ�С�Ŀ�������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestCalBlockRow_ok()
{
    CmlBlockCalculation cls;
    bool result = cls.CalBlockRow(5000,2000);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestGetStartCol_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���Ӱ���У�X������ĳһ�ֿ����ʼ�кŹ���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestGetStartCol_ok()
{
    CmlBlockCalculation cls;
    cls.CalBlockCol(5000,2000);
    SINT result = cls.GetStartCol(1);
    CPPUNIT_ASSERT(result == 1600);
}
/**
* @fn TestGetStartRow_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���Ӱ���У�Y������ĳһ�ֿ����ʼ�кŹ���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestGetStartRow_ok()
{
    CmlBlockCalculation cls;
    cls.CalBlockRow(5000,2000);
    SINT result = cls.GetStartRow(1);
    CPPUNIT_ASSERT(result == 1600);
}
/**
* @fn TestGetBlockPos_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���ĳһӰ������ʼλ�úʹ�С����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestGetBlockPos_ok()
{
    CmlBlockCalculation BlockData(3000,3000,200,200);
    BlockData.CalBlockCol( 1000, 512 );
    BlockData.CalBlockRow( 2000, 512 );
    Pt2i ptOrg;
    UINT nW,nH;
    bool result = BlockData.GetBlockPos( 0, 0, ptOrg, nW, nH );
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestGetBlockPosLast_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���ĳһӰ������һ�����ʼλ�úʹ�С����
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestGetBlockPosLast_ok()
{
    CmlBlockCalculation BlockData(3000,3000,200,200);
    BlockData.CalBlockCol( 1000, 512 );
    BlockData.CalBlockRow( 1000, 512 );
    Pt2i ptOrg;
    UINT nW,nH;
    bool result = BlockData.GetBlockPos( 2, 2, ptOrg, nW, nH );
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestCalBlock_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���Ӱ�����У��У�����ֿ�Ĵ�С�Ŀ�������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestCalBlock_ok()
{
    UINT nBlockL;
    UINT nCount;
    UINT nLastBlockL;
    CmlBlockCalculation cls;
    bool result = cls.CalBlock(5000,2000,3000,200,nBlockL,nCount,nLastBlockL);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestCalBlock2_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���Ӱ�����У��У�����ֿ�Ĵ�С�Ŀ�������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestCalBlock2_ok()
{
    UINT nBlockL;
    UINT nCount;
    UINT nLastBlockL;
    CmlBlockCalculation cls;
    bool result = cls.CalBlock(4001,2000,3000,0,nBlockL,nCount,nLastBlockL);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestCalBlock3_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���Ӱ�����У��У�����ֿ�Ĵ�С�Ŀ�������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestCalBlock3_ok()
{
    UINT nBlockL;
    UINT nCount;
    UINT nLastBlockL;
    CmlBlockCalculation cls;
    bool result = cls.CalBlock(500,2000,3000,0,nBlockL,nCount,nLastBlockL);
    CPPUNIT_ASSERT(result == true);
}
/**
* @fn TestCalBlock4_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���Ӱ�����У��У�����ֿ�Ĵ�С�Ŀ�������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestCalBlock4_ok()
{
    UINT nBlockL;
    UINT nCount;
    UINT nLastBlockL;
    CmlBlockCalculation cls;
    bool result = cls.CalBlock(4001,2000,2000,0,nBlockL,nCount,nLastBlockL);
    CPPUNIT_ASSERT(result == true);
}

/**
* @fn TestGetBlock_ok
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���Լ���Ӱ�����У��У�����ĳһ�����ʼλ�ù���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestGetBlock_ok()
{
    CmlBlockCalculation cls;
    SINT result = cls.GetBlock(0,2000,4,200);
    CPPUNIT_ASSERT(result == 0);
}
/**
* @fn TestGetBlockPos_abnormal
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����GetBlockPos��������������޵��쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestGetBlockPos_abnormal()
{
    CmlBlockCalculation BlockData(3000,3000,200,200);
    BlockData.CalBlockCol( 1000, 512 );
    BlockData.CalBlockRow( 2000, 512 );
    Pt2i ptOrg;
    UINT nW,nH;
    bool result = BlockData.GetBlockPos( 7, 7, ptOrg, nW, nH );
    CPPUNIT_ASSERT(result == false);
}
/**
* @fn TestCalBlock_abnormal1
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����CalBlock�����������Ϊ����쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestCalBlock_abnormal1()
{
    UINT nBlockL;
    UINT nCount;
    UINT nLastBlockL;
    CmlBlockCalculation cls;
    bool result = cls.CalBlock(0,0,0,0,nBlockL,nCount,nLastBlockL);
    CPPUNIT_ASSERT(result == false);
}
/**
* @fn TestCalBlock_abnormal2
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����CalBlock��������������޵��쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestCalBlock_abnormal2()
{
    UINT nBlockL;
    UINT nCount;
    UINT nLastBlockL;
    CmlBlockCalculation cls;
    bool result = cls.CalBlock(100,200,100,500,nBlockL,nCount,nLastBlockL);
    CPPUNIT_ASSERT(result == false);
}
/**
* @fn TestGetBlock_abnormal
* @date 2011.12.1
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����GetBlock��������������޵��쳣���
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
void CTestBlockCalculation::TestGetBlock_abnormal()
{
    CmlBlockCalculation cls;
    SINT result = cls.GetBlock(7,2000,4,200);
    CPPUNIT_ASSERT(result == -1);
}

