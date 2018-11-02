/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlTypeConvert.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ת��ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef _ML_TYPECONVERT_H_
#define _ML_TYPECONVERT_H_

#include "mlBase.h"
#include "mlRasterBlock.h"
#include "opencv.h"

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
bool IplImage2CmlRBlock( const IplImage* pIplImg, CmlRasterBlock* pSBlock );
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
bool CmlRBlock2IplImg( const CmlRasterBlock* pSBlock, IplImage* &pIplImg  );

#endif
