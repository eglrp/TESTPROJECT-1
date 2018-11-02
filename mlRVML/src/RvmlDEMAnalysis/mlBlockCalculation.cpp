/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlBlockCalculation.cpp
* @date 2011.12.23
* @author ��һ�� ylliu@irsa.ac.cn
* @brief Ӱ��ֿ�Դ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/

#include "mlBlockCalculation.h"

/**
* @fn CmlBlockCalculation
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CmlBlockCalculation��ղι��캯��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/

CmlBlockCalculation::CmlBlockCalculation()
{
    nBlockW = 0;
    nBlockH = 0;
    nColCount = 0;
    nRowCount = 0;
    nColThres = 3300;
    nRowThres = 3300;
    nOverlayW = 200;
    nOverlayH = 200;
    nLastBlockW = 0;
    nLastBlockH = 0;
}
/**
* @fn CmlBlockCalculation
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CmlBlockCalculation���вι��캯��
* @param nColThreshold Ӱ���з���ֿ��С��ֵ
* @param nRowThresold Ӱ���з���ֿ��С��ֵ
* @param nBlockOverlayW Ӱ���з����ʼ�ֿ��С
* @param nBlockOverlayH Ӱ���з����ʼ�ֿ��С
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlBlockCalculation::CmlBlockCalculation( const UINT nColThreshold, const UINT nRowThresold, const UINT nBlockOverlayW, const UINT nBlockOverlayH)
{
    nBlockW = 0;
    nBlockH = 0;
    nColCount = 0;
    nRowCount = 0;
    nColThres = nColThreshold;
    nRowThres = nRowThresold;
    nOverlayW = nBlockOverlayW;
    nOverlayH = nBlockOverlayH;
    nLastBlockW = 0;
    nLastBlockH = 0;
}
/**
* @fn ~CmlBlockCalculation
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CmlBlockCalculation����������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlBlockCalculation::~CmlBlockCalculation()
{

}

UINT CmlBlockCalculation::GetBlockW() const //!<�õ�Ӱ���Ŀ�
{
    return this->nBlockW;
}

UINT CmlBlockCalculation::GetBlockH() const //!<�õ�Ӱ���ĸ�
{
    return this->nBlockH;
}

UINT CmlBlockCalculation::GetLastBlockW() const//!<�õ�Ӱ��ֿ����һ��Ŀ�
{
    return this->nLastBlockW;
}

UINT CmlBlockCalculation::GetLastBlockH() const//!<�õ�Ӱ��ֿ����һ��ĸ�
{
    return this->nLastBlockH;
}

UINT CmlBlockCalculation::GetColCount() const//!<�õ�Ӱ���з���X���򣩵ķֿ���
{
    return this->nColCount;
}

UINT CmlBlockCalculation::GetRowCount() const//!<�õ�Ӱ���з���Y���򣩵ķֿ���
{
    return this->nRowCount;
}

/**
* @fn CalBlock
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ�����У��У�����ֿ�Ĵ�С�Ŀ���
* @param nImgLength Ӱ���У��У�����ĳ���
* @param nBlockLength Ӱ���У��У������ʼ�ֿ��С
* @param nThres Ӱ���У��У�����ֿ���ֵ
* @param nOverlay ����Ӱ���֮����ص�����С
* @param nBlockL Ӱ���У��У�����ֿ�ʵ�ʴ�С�����ص�����
* @param nCount Ӱ���л��з���ֿ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlBlockCalculation::CalBlock( const UINT nImgLength, const UINT nBlockLength ,const UINT nThres,const UINT nOverlay, UINT &nBlockL, UINT &nCount, UINT &nLastBlockL)//
{
    if( ( nImgLength == 0 ) || ( nBlockLength == 0 ) || ( nThres == 0 ) )
    {
        SCHAR strErr[] = "Error:Parameters' value less than zero!\n" ;
        LOGAddErrorMsg(strErr) ;
        return false;
    }
    if( (nBlockLength > nThres) || (nOverlay >= nBlockLength) )
    {
        SCHAR strErr[] = "Error:Block size or Overlay is incorrect!\n" ;
        LOGAddErrorMsg(strErr) ;
        return false;
    }
    DOUBLE dCount = 1.0 * ( nImgLength - nOverlay ) / ( nBlockLength - nOverlay );
    //������ķֿ���С��1�����
    if (dCount <= 1)
    {
        nCount = 1;
        nBlockL = nImgLength;
        nLastBlockL = nBlockL;
        return true;
    }
    //������ķֿ�ʣ���Сһ������
    else if( ( dCount - floor( dCount ) ) <= 0.15 )
    {
        nCount = floor( dCount );
    }
    else
    {
        nCount = ceil( dCount );
    }

    nBlockL = ceil( 1.0 * ( nImgLength - nOverlay ) / nCount + nOverlay ) ;
    if( nBlockL > nThres )
    {
        nCount = nCount + 1;
        nBlockL = ceil( 1.0 * ( nImgLength - nOverlay ) / nCount + nOverlay ) ;

    }
    nLastBlockL = nImgLength - ( nBlockL - nOverlay ) * ( nCount - 1 );
    return true;
}

/**
* @fn CalBlockCol
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ�����У�X������ֿ�Ĵ�С�Ŀ���
* @param nImgWidth Ӱ���
* @param nBlockWidth Ӱ���ʼ�ֿ��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool  CmlBlockCalculation::CalBlockCol( const UINT nImgWidth, const UINT nBlockWidth )
{
    return CmlBlockCalculation::CalBlock( nImgWidth, nBlockWidth, this->nColThres,this->nOverlayW,this->nBlockW, this->nColCount, this->nLastBlockW);
}

/**
* @fn CalBlockRow
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ�����У�X������ֿ�Ĵ�С�Ŀ���
* @param nImgHeight Ӱ���
* @param nBlockHeight Ӱ���ʼ�ֿ��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool  CmlBlockCalculation::CalBlockRow( const UINT nImgHeight, const UINT nBlockHeight )
{
    return CmlBlockCalculation::CalBlock( nImgHeight, nBlockHeight, this->nRowThres, this->nOverlayH, this->nBlockH, this->nRowCount, this->nLastBlockH );
}

/**
* @fn GetBlock
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ�����У��У�����ĳһ�����ʼλ��
* @param nNum ĳ��Ŀ�ţ���0��ʼ��
* @param nBlockL Ӱ�����У��У������Ӱ����С
* @param nCount Ӱ���л��з���ֿ����
* @param nOverlayL Ӱ�����У��У�������ص�����С
* @return  Ӱ�����У��У�����ĳ�����ʼλ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
SINT CmlBlockCalculation::GetBlock( const UINT nNum, const UINT nBlockL, const UINT nCount, const UINT nOverlayL ) const
{
    if ( nNum >= nCount )
    {
        SCHAR strErr[] = "Error : Block Start Row/Col  Out of Bounds!\n" ;
        LOGAddErrorMsg(strErr) ;
        return -1;
    }
    else
    {
        return nNum * ( nBlockL - nOverlayL );
    }
}

/**
* @fn GetStartCol
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ���У�X������ĳһ�ֿ����ʼ�к�
* @param nColNum ĳ�����з���Ŀ�ţ���0��ʼ��
* @return  Ӱ���У�X������ĳһ�ֿ����ʼ�к�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
SINT CmlBlockCalculation::GetStartCol( const UINT nColNum ) const
{
    return CmlBlockCalculation::GetBlock( nColNum, this->nBlockW, this->nColCount, this->nOverlayW );
}

/**
* @fn GetStartRow
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ���У�Y������ĳһ�ֿ����ʼ�к�
* @param nColNum ĳ�����з���Ŀ�ţ���0��ʼ��
* @return  Ӱ���У�Y������ĳһ�ֿ����ʼ�к�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
SINT CmlBlockCalculation::GetStartRow( const UINT nRowNum ) const
{
    return CmlBlockCalculation::GetBlock( nRowNum, this->nBlockH, this->nRowCount, this->nOverlayH );
}
/**
* @fn GetBlockPos
* @date 2011.12.16
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ĳһӰ������ʼλ�úʹ�С
* @param nXIndex Ӱ����з�������
* @param nYIndex Ӱ����з�������
* @param ptOrig Ӱ�����ʼ��λ��
* @param nW  Ӱ����
* @param nH  Ӱ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlBlockCalculation::GetBlockPos( UINT nXIndex, UINT nYIndex, Pt2i &ptOrig, UINT &nW, UINT &nH  )
{
    if( ( nXIndex >= nColCount )||( nYIndex >= nRowCount ) )
    {
        return false;
    }
    //�����Ӱ����ʼ������
    ptOrig.X = GetStartCol(nXIndex);
    ptOrig.Y = GetStartRow(nYIndex);

    if( nXIndex == GetColCount() - 1 )//�з������һ������
    {
        nW = GetLastBlockW();
    }
    else
    {
        nW = GetBlockW();
    }
    if( nYIndex == GetRowCount() - 1 )//�з������һ������
    {
        nH = GetLastBlockH();
    }
    else
    {
        nH = GetBlockH();
    }
    return true;
}
