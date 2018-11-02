/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlCamCalib.h
* @date 2012.01
* @author �⿭ wukai@irsa.ac.cn
* @brief ����������궨ģ��ͷ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#ifndef _MLCAMCALIB_H
#define _MLCAMCALIB_H
#include "mlBase.h"
#include "mlMat.h"

#define MAX_THRESH 999999
#define MIN_THRESH -999999

// �����Ե�����ֵ�ṹ��
typedef struct structTermCriteria
{
    SINT nIterMax ; // ��������
    DOUBLE dThreshValue ; // ������ֵ
    structTermCriteria()
    {
        nIterMax = 30 ;
        dThreshValue = 0.05 ;
    }
} TermCriteria ;

/**
* @class CmlCamCalib
* @date 2011.11
* @author �⿭ wukai@irsa.ac.cn
* @brief ����궨�ඨ��
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*
*/

class CmlCamCalib
{
public :
    camModelType camModel ;// ����У��ģ�ͣ�8���� ,10������
    TermCriteria dltTerm ; // dlt������ֵ
    TermCriteria colinearityTerm ; // �ϸ�ģ�͵�����ֵ
private :
    vector<Pt2d> imgPtsList ; // ��־������������
    vector<Pt3d> objPtsList ; // ��ʶ���﷽��������
    ExOriPara exPara ;  // ����ⷽ��Ԫ��(�����)
    InOriPara inPara ;  // ����ڷ�λԪ��(�����)
    SINT m_nW ; // Ӱ����
    SINT m_nH ; // Ӱ��߶�
    SINT nGcp ; // Ӱ���־������
    bool bInParaInitFlag ; // ��ʶ��������Ƿ��ʼ��
    DOUBLE* pLPara ;   // DLT ��11�����Ա任����
// �ӿں���
public :
/**
 *@fn CmlCamCalib()
 *@date 2011.11
 *@author �⿭
 *@brief ����궨�๹�캯��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
*/
    CmlCamCalib() ;
    /**
 *@fn CmlCamCalib()
 *@date 2011.11
 *@author �⿭
 *@brief ����궨����������
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
*/
    ~CmlCamCalib() ;
/**
 *@fn mlSingleCamCalib
 *@date 2012.02
 *@author �⿭
 *@brief ������궨����
 *@param vecImgPts  ���Ƶ�����������
 *@param vecObjPts ���Ƶ��﷽��������
 *@param nW  Ӱ����
 *@param nH  Ӱ��߶�
 *@param inPara ����ڲ���
 *@param exPara  ��������
 *@param vecErrorPts  ���Ƶ��񷽲в�����
 *@param bFlag �жϸ��������ʼ�����ٱ궨���Ǽ��㾫�ȼ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool  mlSingleCamCalib(vector<Pt2d>& vecImgPts , const vector<Pt3d>& vecObjPts ,  SINT nW , SINT nH ,
                           InOriPara& inPara , ExOriPara& exPara , vector<Pt3d>& vecErrorPts , bool bFlag = 1);
/**
 *@fn mlStereoCamCalib()
 *@date 2012.02
 *@author �⿭
 *@brief ˫����궨����
 *@param vecLImgPts  ���Ƶ����������������
 *@param vecRImgPts  ���Ƶ����������������
 *@param vecObjPts  ���Ƶ��﷽��������
 *@param nW  Ӱ����
 *@param nH Ӱ��߶�
 *@param inLPara  ������ڲ���
 *@param inRPara  ������ڲ���
 *@param exLPara  ����������
 *@param exRPara ����������
 *@param exStereoPara  ���������Է�λ����
 *@param vecErrorPts  ���Ƶ��﷽�в�����
 *@param bFlag �жϸ��������ʼ�����ٱ궨���Ǽ��㾫�ȼ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool  mlStereoCamCalib(const vector<Pt2d>& vecLImgPts ,const vector<Pt2d>& vecRImgPts , vector<Pt3d>& vecObjPts ,
                            SINT nW , SINT nH , InOriPara& inLPara , InOriPara& inRPara , ExOriPara& exLPara ,
                            ExOriPara& exRPara , ExOriPara& exStereoPara, vector<Pt3d>& vecErrorPts , bool bFlag = 1);
/**
 *@fn backProjection
 *@date 2012.02
 *@author �⿭
 *@brief �󷽽��ᣨ����ϵͳת�����ٽ��㣩
 *@param imgPtsList ���Ƶ�����������
 *@param objPtsList ���Ƶ��﷽��������
 *@param inPara ����ڲ���
 *@param exPara ��������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool backProjection(const vector<Pt2d>& imgPtsList , const vector<Pt3d>& objPtsList ,
                                   InOriPara& inPara , ExOriPara& exPara) ;
private :
/**
 *@fn homographPtsInit()
 *@date 2012.02
 *@author �⿭
 *@brief ����궨������ʼ��
 *@param vecImgPts  ���Ƶ�����������
 *@param vecObjPts  ���Ƶ��﷽��������
 *@param inCamPara �����ʼ����
 *@param nW  ������
 *@param nH  ����߶�
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool homographPtsInit(const vector<Pt2d>& vecImgPts, const vector<Pt3d>& vecObjPts, InOriPara& inCamPara ,SINT nW , SINT nH) ;
/**
 *@fn dltCalib()
 *@date 2012.02
 *@author �⿭
 *@brief ���ֱ�����Ա任�궨
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool dltCalib() ;
/**
 *@fn colinearityCalib()
 *@date 2012.02
 *@author �⿭
 *@brief ����ϸ���ģ�ͱ궨
 *@param camType �������ģ��ѡ�� Ĭ��Ϊ10����ģ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool colinearityCalib(camModelType camType = Affine) ;
/**
 *@fn imgErrorCheck()
 *@date 2012.02
 *@author �⿭
 *@brief ����궨�񷽾��ȼ��
 *@param vecImgPts  ��������������
 *@param vecObjPts  �����﷽��������
 *@param inPara  ����ڲ���
 *@param exPara  ��������
 *@param vecErrorPts �����񷽲в�����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool imgErrorCheck(const vector<Pt2d>& vecImgPts, const vector<Pt3d>& vecObjPts, InOriPara inPara ,
                       ExOriPara exPara , vector<Pt3d>& vecErrorPts);
/**
 *@fn objErrorCheck()
 *@date 2012.02
 *@author �⿭
 *@brief  ����궨�﷽���ȼ��
 *@param vecLImgPts �������������������
 *@param vecRImgPts �������������������
 *@param vecObjPts  �����﷽��������
 *@param inLPara  ������ڲ���
 *@param inRPara  ������ڲ���
 *@param exLPara  ����������
 *@param exRPara  ����������
 *@param vecErrorPts  �����﷽�в�����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool objErrorCheck(const vector<Pt2d>& vecLImgPts , const vector<Pt2d>& vecRImgPts ,const vector<Pt3d>& vecObjPts ,
                        InOriPara inLPara , InOriPara inRPara , ExOriPara exLPara , ExOriPara exRPara , vector<Pt3d>& vecErrorPts) ;
/**
 *@fn dltParaInit()
 *@date 2012.02
 *@author �⿭
 *@brief ֱ�����Ա궨��ʼ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool dltParaInit() ;
/**
 *@fn dltParaIterSolve
 *@date 2012.02
 *@author �⿭
 *@brief ֱ����������궨��������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool dltParaIterSolve();
/**
 *@fn dltPara2InPara
 *@date 2012.02
 *@author �⿭
 *@brief ֱ�����Ա任���������ڷ�λ����
 *@param inPara
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    void dltPara2InPara(InOriPara& inPara) ;
/**
 *@fn dltPara2ExPara
 *@date 2012.02
 *@author �⿭
 *@brief ֱ�����Ա任���������ⷽλ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool dltPara2ExPara() ;
/**
 *@fn POK2RMat()
 *@date 2012.02
 *@author �⿭
 *@brief �Ƕ�ת��Ϊ��ת���� (���ڿ��Ƴ��궨����ϵ����ת��������ڹ��̻�����omg-phi-kap(x,y,z),������ϵͳ���omg,phi������ͬ��kap�����෴)
 *@param pOri ��Ԫ��ָ��   ת��phi-omg-kapת��ϵͳ����ʱphi���z�ᣬomg���x�ᣬkap���y��
 *@param pRMat ��ת����ָ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool POK2RMat( OriAngle* pOri, CmlMat* pRMat ) ;
/**
 *@fn imgPtRectify()
 *@date 2012.02
 *@author �⿭
 *@brief ͼ������У��
 *@param ptXY У��ǰ��
 *@param inPara ����ڲ���
 *@param ptNewXY У�����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    void imgPtRectify(Pt2d ptXY , InOriPara inPara , Pt2d& ptNewXY) ;
/**
 *@fn objPOKPtReproject()
 *@date 2012.02
 *@author �⿭
 *@brief pok����ϵͳ������﷽�㷴ͶӰ���񷽵�
 *@param ptXYZ �﷽��
 *@param ptS ����ⷽλ��Ԫ��
 *@param pOpkMat �����Ԫ�ر任����
 *@param inPara ����ڲ���
 *@param ptNewXYZ �﷽���Ӧ����ͶӰ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    void objPOKPtReproject(Pt3d ptXYZ , Pt3d ptS , CmlMat pOpkMat ,InOriPara inPara , Pt2d& ptNewXYZ ) ;
/**
 *@fn objPtReproject()
 *@date 2012.02
 *@author �⿭
 *@brief opk����ϵͳ������﷽�㷴ͶӰ���񷽵�
 *@param ptXYZ �﷽��
 *@param ptS ����ⷽλ��Ԫ��
 *@param pOpkMat �����Ԫ�ر任����
 *@param inPara ����ڲ���
 *@param ptNewXYZ �﷽���Ӧ����ͶӰ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    void objPtReproject(Pt3d ptXYZ , Pt3d ptS , CmlMat pOpkMat ,InOriPara inPara , Pt2d& ptNewXYZ ) ;
/**
 *@fn forwardIntersection()
 *@date 2012.02
 *@author �⿭
 *@brief ǰ�����ắ��
 *@param imgLPt �����ͼ������
 *@param imgRPt �����ͼ������
 *@param exLPara ��Ƭ�ⷽλԪ��
 *@param inLPara ��Ƭ�ڷ�λԪ��
 *@param exRPara ��Ƭ�ⷽλԪ��
 *@param inRPara ��Ƭ�ڷ�λԪ��
 *@param objPt ǰ�������﷽������
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool forwardIntersection(Pt2d imgLPt , Pt2d imgRPt , ExOriPara exLPara , InOriPara inLPara ,
                                ExOriPara exRPara , InOriPara inRPara , Pt3d& objPt ) ;
/**
 *@fn stereoParaSolve()
 *@date 2012.02
 *@author �⿭
 *@brief ˫�����Է�λ��������
 *@param exLPara  ����������
 *@param exRPara  ����������
 *@param exStereoPara  ˫�����Բ���
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
    bool stereoParaSolve(ExOriPara exLPara , ExOriPara exRPara , ExOriPara& exStereoPara) ;
} ;

#endif
