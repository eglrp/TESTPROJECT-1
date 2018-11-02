/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlTypeConvert.cpp
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ת��Դ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#include "mlTypeConvert.h"
/**
* @fn IplImage2CmlRBlock
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��IplImage�ͱ���ת����CmlSBlock�ͱ���
* @param pIplImg  IplImage�ͱ���
* @param pSBlock  CmlSBlock�ͱ���
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool IplImage2CmlRBlock( const IplImage* pIplImg, CmlRasterBlock* pSBlock )
{
    if(( pIplImg == NULL)||( pSBlock == NULL ) )
    {
        return false;
    }
    if( pSBlock->IsValid() == true )
    {
        if( ( SINT(pSBlock->GetH()) != pIplImg->height ) || ( SINT(pSBlock->GetW()) != pIplImg->width ) )
        {
            return false;
        }
    }
    else
    {
        pSBlock->InitialImg( pIplImg->height, pIplImg->width );
    }

    if( 0 == (pIplImg->width % 4 ) ) //Ϊ�п��ĵı�������ͼ���в���Ҫ�ֽڲ���
    {
        if( pIplImg->origin == 0 )//Ϊ����ṹ��ͬpSBlock ��ͬ
        {
            memcpy(  (void*)(pSBlock->GetData()), (void*)(pIplImg->imageData ), sizeof(BYTE)*pSBlock->GetTPixelSize() );

        }
        else//Ϊ����ṹ��ͬpSBlock ��ͬ
        {
            for( UINT i = 0; i < pSBlock->GetH(); ++i )
            {
                for( UINT j = 0; j < pSBlock->GetW(); ++j )
                {
                    memcpy( (void*)(pSBlock->GetData() + i*pSBlock->GetW()), (void*)(pIplImg->imageData + ( pIplImg->height - 1 - i )*pIplImg->widthStep ), sizeof(uchar)*pSBlock->GetW() );
                }
            }
        }
    }
    else//��Ϊ�п��ĵı�������ͼ���д����ֽڲ��룬ת��ʱ��Ҫȥ��
    {
        if( pIplImg->origin == 0 )//Ϊ����ṹ��ͬpSBlock ������ͬ
        {
            for( UINT i = 0; i < pSBlock->GetH(); ++i )
            {
                for( UINT j = 0; j < pSBlock->GetW(); ++j )
                {
                    memcpy( (void*)(pSBlock->GetData() + i*pSBlock->GetW()), (void*)(pIplImg->imageData + i*pIplImg->widthStep ), sizeof(uchar)*pSBlock->GetW() );
                }
            }

        }
        else//Ϊ����ṹ��ͬpSBlock ��������ͬ
        {
            for( UINT i = 0; i < pSBlock->GetH(); ++i )
            {
                for( UINT j = 0; j < pSBlock->GetW(); ++j )
                {
                    memcpy( (void*)(pSBlock->GetData() + i*pSBlock->GetW()), (void*)(pIplImg->imageData + ( pSBlock->GetH() - 1 - i )*pIplImg->widthStep ), sizeof(uchar)*pSBlock->GetW() );
                }
            }
        }
    }
    return true;

}

/**
* @fn CmlSBlock2IplImg
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��CmlSBlock�ͱ���ת����IplImage�ͱ���
* @param pSBlock  CmlSBlock�ͱ���
* @param pIplImg  IplImage�ͱ���
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlRBlock2IplImg( const CmlRasterBlock* pSBlock, IplImage* &pIplImg  )
{
    if(( pIplImg != NULL)||( pSBlock == NULL ) )
    {
        return false;
    }
    if( ( pSBlock->IsValid() == false ) )
    {
        return false;
    };

    CvSize s;
    s.height = pSBlock->GetH();
    s.width = pSBlock->GetW();

    pIplImg = cvCreateImage( s, IPL_DEPTH_8U, 1 );
    pIplImg->origin = 0; //����Ϊ����ṹ

    if( 0 == (pIplImg->width % 4 ) ) //Ϊ�п��ĵı�������ͼ���в���Ҫ�ֽڲ���
    {
        memcpy(  (void*)(pIplImg->imageData ), (void*)(pSBlock->GetData()), sizeof(uchar)*pSBlock->GetTPixelSize() );
    }
    else//��Ϊ�п��ĵı�������ͼ���д����ֽڲ��룬ת��ʱ��Ҫȥ��
    {
        for( UINT i = 0; i < pSBlock->GetH(); ++i )
        {
            for( UINT j = 0; j < pSBlock->GetW(); ++j )
            {
                memcpy( (void*)(pIplImg->imageData + i*pIplImg->widthStep ), (void*)(pSBlock->GetData() + i*pSBlock->GetW()), sizeof(uchar)*pSBlock->GetW() );
            }
        }
    }
    return true;

}




