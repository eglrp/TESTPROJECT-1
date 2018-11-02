/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlKinging.h
* @date 2012.01
* @author �⿭ wukai@irsa.ac.cn
* @brief Kringing��ֵ����ģ����ͷ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#ifndef MLKRINGING_H_INCLUDED
#define MLKRINGING_H_INCLUDED

#include "mlBase.h"
#include "mlMat.h"
#include "mlTIN.h"

enum KRIGING_MODEL
{
	POLYNOMIANL,
	SPHERICAL,
	EXPONENTIAL,
	SPHERICAL_EXPONENTIAL
};

enum KRIGING_State
{
    KRIGING_OFF,
    KRIGING_ON,
};

/**
* @class CmlKringing
* @date 2011.11
* @author �⿭ wukai@irsa.ac.cn
* @brief CmlKringing�ඨ��
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*
*/

class CmlKringing
{
public:
public:
    /**
     *@fn CmlKringing
     *@date 2011.11
     *@author �⿭
     *@brief Kring�๹�캯��
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    CmlKringing() ;
    /**
     *@fn ~CmlKringing
     *@date 2011.11
     *@author �⿭
     *@brief Kring����������
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    ~CmlKringing() ;
    /**
     *@fn InitVariogram
     *@date 2012.02
     *@author �⿭
     *@brief Kring�������ʼ������
     *@param dRange Kringģ�;������
     *@param dShort Kring����ʽģ�Ͷ̾������
     *@param dLong  Kring����ʽģ�ͳ��������
     *@param dDisShort ѡ��Kring����ʽ���̾���ģ�Ͳ�������ֵ
     *@param dGraceStart Kring����ģ�Ͷ̾������
     *@param dGraceEnd Kring����ģ�ͳ��������
     *@param dSphericalPara Kring����ģ�Ͷ̾������
     *@param dExponentialPara Kring����ģ�ͳ��������
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void InitVariogram(DOUBLE *dShort=NULL,DOUBLE *dLong=NULL , DOUBLE dRange = 50 , DOUBLE dDisShort = 5.0 , DOUBLE dGraceStart = 5.0 ,
                       DOUBLE dGraceEnd = 20.0 , DOUBLE dSphericalPara = 0.00001738 , DOUBLE dExponentialPara= 0.00001738);
    /**
     *@fn GetValueFromTins
     *@date 2012.02
     *@author �⿭
     *@brief ͨ����������ֵ�߳�����
     *@param vec3DPts �����������3ά����
     *@param tri ���ƹ������Ǹ�������
     *@param pNeigh ��ֵ����Χ���ڽӵ�
     *@param outNewPt ��ֵ��
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool GetValueFromTins(const vector<Pt3d>& vec3DPts,triangulateio *tri,
                                  SINT *pNeigh , Pt3d& outNewPt) ;

    /**
     *@fn GetValueFromTins
     *@date 2012.02
     *@author �⿭
     *@brief ͨ����������ֵ�߳�����
     *@param vec3DPts �����������3ά����
     *@param tri ���ƹ������Ǹ�������
     *@param pNeigh ��ֵ����Χ���ڽӵ�
     *@param outNewPt ��ֵ��
     *@param bFlag ���ÿ�����ֵ�����ַ�ʽ
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

    bool GetValueFromTin(const vector<Pt3d>& vec3DPts,triangulateio *tri,SINT *pNeigh ,
                         Pt3d& outNewPt , KRIGING_State bFlag = KRIGING_ON);
private:
    DOUBLE m_dDisMin ; // �ж��Ƿ���������ֵ�������ֵ
    KRIGING_MODEL m_eKrigingModel;//Krigingģ��
	DOUBLE m_dShortPara[4],m_dLongPara[4];//Kring����ʽģ�ͳ��̾���Ĳ���
	DOUBLE m_dDisShort;//ѡ�����ʽ���̾���ģ�Ͳ�������ֵ
	DOUBLE m_dRange ; // ������ֵ�������
	DOUBLE m_dSphericalPara ; // ������ֵ����ģ�Ͳ���
	DOUBLE m_dExponentialPara; // ������ֵָ��ģ�Ͳ���
	DOUBLE m_dGraceStart,m_dGraceEnd; // Kring ����ģ�ͳ��̾������
private:
    /**
     *@fn GetNeighborVertexInMinDis
     *@date 2012.02
     *@author �⿭
     *@brief  ��������Χ���ڽӵ�
     *@param inPt Ŀ���
     *@param vec3DPts ��ά����
     *@param tri ��������������
     *@param pNeigh Ŀ�����Χ���ڽӵ�
     *@param nCount �ڽӵ���Ŀ
     *@param vecNeighborPts ���������ֵ���ڽӵ�
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

    bool GetNeighborVertexInMinDis( Pt3d& inPt,const vector<Pt3d>& vec3DPts ,triangulateio *tri,SINT *pNeigh,SINT nCount, vector<Pt3d>& vecNeighborPts);
    /**
     *@fn VertexNotInTriangle
     *@date 2012.02
     *@author �⿭
     *@brief �жϵ��Ƿ�����������
     *@param nVt ���жϵ�������
     *@param Vertexs ��������������������
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool VertexNotInTriangle(SINT nVt,SINT *Vertexs) ;
    /**
     *@fn semivariogram()
     *@date 2012.02
     *@author �⿭
     *@brief ���������ֵ��������ϵ��
     *@param *p1 ��1�ĵ�������
     *@param *p2 ��2�ĵ�������
     *@param m_eKrigingModel ������ֵģ��
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    double semivariogram(Pt3d *p1, Pt3d *p2 , KRIGING_MODEL m_eKrigingModel = POLYNOMIANL) ;
};


#endif // MLKRINGING_H_INCLUDED
