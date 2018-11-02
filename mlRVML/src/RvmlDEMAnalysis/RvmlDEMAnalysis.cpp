/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlRVML.cpp
* @date 2011.2.1
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ӿں���Դ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#include "mlRVML.h"

#include "mlDemAnalyse.h"


/**
* @fn mlComputeSlopeMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݣ��ͼ��㴰�ڴ�С������¶�
* @param sInputDEM,  ����DEM�ļ�·��
* @param nWindowSize, ���㴰�ڴ�С
* @param sDestDEM, ����ļ�·��
* @param dZfactor�� �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
* @retval 1 �ɹ�
* @retval ���� ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlComputeSlopeMap (SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor )
{
    CmlDemAnalyse cal;
    if(cal.ComputeSlopeInterface(sInputDEM, sDestDEM, nWindowSize, dZfactor) < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
/**
* @fn mlComputeSlopeAspectMap
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief �����ӿڣ� ����DEM���ݣ��ͼ��㴰�ڴ�С���������
* @param sInputDEM,  ����DEM�ļ�·��
* @param nWindowSize, ���㴰�ڴ�С
* @param sDestDEM, ����ļ�·��
* @param dZfactor�� �߳��������ӣ�����DEMȡ������ֵ���� dZfactor Ϊ��ʵ�߳�ֵ
* @retval 1 �ɹ�
* @retval ���� ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlComputeSlopeAspectMap(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor )
{
    CmlDemAnalyse cal;
    if(cal.ComputeSlopeAspectInterface(sInputDEM, sDestDEM, nWindowSize, dZfactor) < 0)
    {
        return false;
    }
    else
    {
        return true;
    }

}
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
* @retval 1 �ɹ�
* @retval ���� ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlComputeBarrierMap(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor,ObstacleMapPara ObPara)
{
    CmlDemAnalyse cal;
    if(cal.ComputeObstacleMapInterface(sInputDEM, sDestDEM, nWindowSize, dZfactor, ObPara) < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
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
* @retval 1 �ɹ�
* @retval ���� ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlComputeInsightMap( const SCHAR * sInputDEM, SINT nxLocation ,SINT nyLocation, DOUBLE dViewHight, const SCHAR * sDestDEM, bool InversHeight)
{
    CmlDemAnalyse cal;
    if(cal.ComputeViewShedInterface(sInputDEM, nxLocation,nyLocation, dViewHight, sDestDEM,InversHeight)< 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
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
* @retval 1 �ɹ�
* @retval -1 ʧ�ܣ�gdal�汾����
* @retval -2 ʧ�ܣ��ȸ߾���������
* @retval -3 ʧ�ܣ������ļ�����
* @retval -4 ʧ�ܣ�����ļ�����
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
ML_EXTERN_C bool mlComputeContourMap(DOUBLE dHinterval, SCHAR* strSrcfilename, SCHAR* strDstfilename ,bool bCNodata , DOUBLE dNodata ,SCHAR* strAttrib )
{
    CmlDemAnalyse cal;
    if(cal.ComputeContourInterface(dHinterval, strSrcfilename, strDstfilename, bCNodata, dNodata, strAttrib)<0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
