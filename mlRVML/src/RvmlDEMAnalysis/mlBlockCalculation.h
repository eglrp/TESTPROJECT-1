/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlBlockCalculation.h
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief Ӱ��ֿ�ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef _MLBLOCKCALCULATION_H
#define _MLBLOCKCALCULATION_H
#include "mlBase.h"

/**
* @class CmlBlockCalculation
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief Ӱ��ֿ鴦����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlBlockCalculation
{
public :
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
    CmlBlockCalculation();
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
    CmlBlockCalculation( const UINT nColThreshold, const UINT nRowThresold, const UINT nBlockOverlayW, const UINT nBlockOverlayH );
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
    ~CmlBlockCalculation();
private:
    UINT nBlockW;//!<Ӱ���Ŀ�
    UINT nBlockH;//!<Ӱ���ĸ�
    UINT nColCount;//!<Ӱ���з���ķֿ���
    UINT nRowCount;//!<Ӱ���з���ķֿ���
    UINT nColThres;//!<Ӱ���з���ֿ��С��ֵ
    UINT nRowThres;//!<Ӱ���з���ֿ��С��ֵ
    UINT nOverlayW;//!<Ӱ���з����ص�����С
    UINT nOverlayH;//!<Ӱ���з����ص�����С
    UINT nLastBlockW;//!<Ӱ���з������һ��Ӱ����С
    UINT nLastBlockH;//!<Ӱ���з������һ��Ӱ����С
public:
    UINT GetBlockW() const;//!<�õ�Ӱ���Ŀ�
    UINT GetBlockH() const;//!<�õ�Ӱ���ĸ�
    UINT GetLastBlockW() const;//!<�õ�Ӱ��ֿ����һ��Ŀ�
    UINT GetLastBlockH() const;//!<�õ�Ӱ��ֿ����һ��ĸ�
    UINT GetColCount() const;//!<�õ�Ӱ���з���X���򣩵ķֿ���
    UINT GetRowCount() const;//!<�õ�Ӱ���з���Y���򣩵ķֿ���
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
    bool CalBlockCol( const UINT nImgWidth, const UINT nBlockWidth );
    /**
    * @fn CalBlockRow
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����Ӱ�����У�Y������ֿ�Ĵ�С�Ŀ���
    * @param nImgHeight Ӱ���
    * @param nBlockHeight Ӱ���ʼ�ֿ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool CalBlockRow( const UINT nImgHeight, const UINT nBlockHeight );
    /**
    * @fn GetStartCol
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����Ӱ���У�X������ĳһ�ֿ����ʼ�к�
    * @param nColNum ĳ�����з���Ŀ�ţ���0��ʼ��
    * @return Ӱ���У�X������ĳһ�ֿ����ʼ�к�
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    SINT GetStartCol( const UINT nColNum ) const;
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
    SINT GetStartRow( const UINT nRowNum ) const;

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
    bool GetBlockPos( UINT nXIndex, UINT nYIndex, Pt2i &ptOrig, UINT &nW, UINT &nH );
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
    bool  CalBlock( const UINT nImgLength, const UINT nBlockLength, const UINT nThres, const UINT nOverlay, UINT &nBlockL, UINT &nCount, UINT &nLastBlockL );
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
    SINT  GetBlock( const UINT nNum, const UINT nBlockL, const UINT nCount, const UINT nOverlayL ) const ;
private:
};

#endif
