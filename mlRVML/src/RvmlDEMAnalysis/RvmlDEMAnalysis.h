#ifndef _MLRVML_H_
#define _MLRVML_H_

#include "mlTypes.h"

/**
* @fn mlComputeInsightMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ���������DEM���ݺ��ӵ����꣬����ͨ��ͼ
* @param sInputDEM,  ����DEM�ļ�·��
* @param nxLocation, �ӵ�x����
* @param nyLocation, �ӵ�y����
* @param ViewHight��  �ӵ�������ĸ߶�
* @param sDestDEM��   ����ļ�·��
* @param InverseHeight�� �Ƿ񽫸̷߳�ת
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeInsightMap( const SCHAR * sInputDEM, SINT nxLocation ,SINT nyLocation, DOUBLE dViewHight, const SCHAR * sDestDEM, bool InverseHeight );

/**
* @fn mlComputeSlopeMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݣ��ͼ��㴰�ڴ�С������¶�
* @param sInputDEM,  ����DEM�ļ�·��
* @param nWindowSize, ���㴰�ڴ�С
* @param sDestDEM, ����ļ�·��
* @param dZfactor�� �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeSlopeMap(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor);
/**
* @fn mlComputeSlopeAspectMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݣ��ͼ��㴰�ڴ�С���������
* @param sInputDEM,  ����DEM�ļ�·��
* @param nWindowSize, ���㴰�ڴ�С
* @param sDestDEM, ����ļ�·��
* @param dZfactor�� �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeSlopeAspectMap(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor );
/**
* @fn mlComputeBarrierMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݣ��ͼ��㴰�ڴ�С���ϰ�ͼ���������ϰ�ͼ
* @param sInputDEM,  ����DEM�ļ�·��
* @param nWindowSize, ���㴰�ڴ�С
* @param sDestDEM, ����ļ�·��
* @param dZfactor�� �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
* @param ObPara: �ϰ�ͼ�����ṹ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeBarrierMap(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor,ObstacleMapPara ObPara);
/**
* @fn mlComputeContourMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݺ͵ȸ߾࣬����ȸ���ͼ
* @param dHinterval,  �ȸ߾�
* @param strSrcfilename, �����DEM�ļ�·��
* @param strDstfilename, �����shape�ļ�·��
* @param bCNodata�� ��ʾ�Ƿ��Զ���Nodataֵ
* @param dNodata�� ���bCNodata����Ϊtrue����dNodata ��ֵ�ڼ���ʱ��������Чֵ�Դ�
* @param cAttrib������shape�ļ��̵߳��������ƣ�Ĭ��Ϊelev
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool )  mlComputeContourMap(DOUBLE dHinterval, SCHAR* strSrcfilename, SCHAR* strDstfilename ,bool bCNodata = false , DOUBLE dNodata = 0.0 ,SCHAR* strAttrib = "elev" );

#endif


