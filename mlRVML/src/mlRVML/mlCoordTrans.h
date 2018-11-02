/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlCoordTrans.h
* @date 2011.11.18
* @author ������ zhangchy@irsa.ac.cn
* @brief ����ת���㷨��ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#ifndef CMLCOORDTRANS_H
#define CMLCOORDTRANS_H

#include "mlBase.h"

/**
* @class CmlCoordTrans
* @date 2011.11
* @author ������ zhangchy@irsa.ac.cn
* @brief ����ת���㷨�ඨ��
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*
*/

class CmlCoordTrans
{
public:
    /**
     *@fn CmlCoordTrans()
     *@date 2011.11
     *@author ������
     *@brief ����ת������������
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
    */
    CmlCoordTrans();

    /**
     *@fn CmlCoordTrans()
     *@date 2011.11
     *@author ������
     *@brief ����ת������������
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    virtual ~CmlCoordTrans();

    /**
     *@fn mlCoordTransResult
     *@date 2012.02
     *@author ������
     *@brief ���ݸ�������ת�����ƽ���������ת���������
     *@param pArr ������������ָ��
     *@param nDim ����ά��
     *@param pRotateMat ��ת����ָ��
     *@param pTransVec ƽ������ָ��
     *@param fx��fy ����
     *@param pTransResult ����ת������
     *@param nflag ת��״̬���� Ĭ��Ϊ0
             ����ת����ϵ B = R*A + T (RΪ��ת����TΪƽ������)
             ��nflag=0ʱ����ʾ��A��B��
             ��nflagΪ����ֵ����ʾ��B��A
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

     */
    bool mlCoordTransResult(DOUBLE* pArr, SINT nDim, CmlMat* pRotateMat, DOUBLE* pTransVec, DOUBLE* pTransResult,SINT nflag);

    /**
     *@fn mlCalcTransMatrixByXYZ
     *@date 2011.11
     *@author ������
     *@brief ������ʵ���¹�ϵ���ֲ�����ϵת����ϵ���
     *@param pLocResult ��½�����¹�ϵ�µþ�ȷ��λ���
     *@param pTransMat  �洢ת������ת����
     *@param pTransVec  �洢ƽ������
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

     */
    bool mlCalcTransMatrixByXYZ(Pt3d* pLocResult,CmlMat* pTransMat, DOUBLE* pTransVec);
    /**
     *@fn mlCalcTransMatrixByLatLong
     *@date 2011.11
     *@author ������
     *@brief ���������ݶ�λ�ľ�γ��ʵ���¹�ϵ���ֲ�����ϵת����ϵ���
     *@param dLat ��λ��γ��  ��λΪ��   ��ΧΪ-90�ȡ�90��  ��γΪ�� ��γΪ��
     *@param dLong ��λ�ľ��� ��λΪ��   ��ΧΪ-180-180��  ����Ϊ�� ����Ϊ��
     *@param pTransMat  �洢ת������ת����
     *@param pTransVec  �洢ƽ������
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

    */
    bool mlCalcTransMatrixByLatLong(double dLat,double dLong,CmlMat* pTransMat, DOUBLE* pTransVec);

protected:
private:
};

#endif // CMLCOORDTRANS_H
