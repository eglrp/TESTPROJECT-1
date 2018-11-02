/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlLinearImage.h
* @date 2011.11.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��������Ӱ����ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef MLLINEARIMAGE_H
#define MLLINEARIMAGE_H

#include "mlGdalDataset.h"
#include "mlMat.h"
#include "mlDemProc.h"
#include "mlPhgProc.h"
#include "mlFrameImage.h"
#include "mlRasterBlock.h"

/**
* @struct tagMatrixR
* @date 2011.11.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��ת����ṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagMatrixR
{
    CmlMat matR;//!<��ת����
    tagMatrixR()
    {
        matR.Initial( 3, 3 );
    }
} MatrixR;
/**
* @class CmlLinearImage
* @date 2011.11.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��������Ӱ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlLinearImage : public CmlGdalDataset
{
public:
    /**
    * @fn CmlLinearImage
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CmlLinearImage��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlLinearImage();
    /**
    * @fn ~CmlLinearImage
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CmlLinearImage����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual ~CmlLinearImage();

public:
    //SatImgInfo m_SatImgInfo;//!<Ӱ��ͷ��Ϣ
    vector<ExOriPara> m_vecImgEo;//!<��Ӱ���ⷽλԪ��
    vector<MatrixR> m_vecMatrix;//!<��Ӱ���ⷽλ��ת����
    vector<Pt3d> m_vecPosition;//!<��Ӱ���ⷽλ��Ԫ��
    /**
    * @fn mlGetEop
    * @date 2011.11.22
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ���������ݶ���ʽ�ڲ��ⷽλԪ��
    * @param vecLineEo ԭʼ�����������Ԫ��
    * @param vecAngleEo ԭʼ��������н�Ԫ��
    * @param vecImg_time ����Ӱ��ɨ���л�ȡʱ��
    * @param vecEo �ڲ���ⷽλ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlGetEop( vector<LineEo> &vecLineEo, vector<AngleEo> &vecAngleEo, vector<DOUBLE> &vecImg_time, vector<ExOriPara> *vecEo );
    /**
    * @fn mlBLH2XYZ
    * @date 2011.11.29
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ���﷽��ά��������������ϵת���¹�����ϵ�µĿռ�ֱ������
    * @param blhPts ����������ϵ����
    * @param xyzPts �¹�����ϵ�µĿռ�ֱ������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlBLH2XYZ(Pt3d& blhPts, Pt3d& xyzPts);
    /**
    * @fn mlXYZ2BLH
    * @date 2011.11.29
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ���﷽��ά�����¹�����ϵ�µĿռ�ֱ������ת������������ϵ
    * @param xyzPts �¹�����ϵ�µ�XYZ����
    * @param blhPts ����������ϵ��Longitude,Latitude,Height������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlXYZ2BLH(Pt3d &xyzPts, Pt3d &blhPts);
protected:
private:
};
/**
* @class CmlCE1LinearImage
* @date 2011.11.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CE-1��������Ӱ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlCE1LinearImage : public CmlLinearImage
{
public:
    /**
    * @fn CmlCE1LinearImage
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CmlCE1LinearImage��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlCE1LinearImage();
    /**
    * @fn ~CmlCE1LinearImage
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CmlCE1LinearImage����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual ~CmlCE1LinearImage();
    /**
    * @fn mlGetCE1DOMCoordinate
    * @date 2011.12.07
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����CE-1����Ӱ��DOM������ԭͼ���ϵ�x,y����
    * @param OriSatImg ԭʼӰ��
    * @param vecR Ӱ���ⷽλ��ת����
    * @param vecXsYsZs Ӱ���ⷽλ��Ԫ��
    * @param f �������
    * @param vecPtXYZ �﷽��ά����
    * @param pCE1IOP �ڷ�λԪ��
    * @param nWidth ����Ӱ����
    * @param nHeight Ӱ��߶�
    * @param thresh �������x����������ֵ֮�����ֵ
    * @param ImgSL ����Ӱ��DOM������ԭͼ���ϵ�x,y����
    * @param trueline Ӱ��������ʵ��
    * @param range ������Χ
    * @param thresh ��ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlGetCE1DOMCoordinate(CmlRasterBlock &OriSatImg, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, DOUBLE f, vector<Pt3d> &vecPtXYZ, UINT nWidth, UINT nHeight, CRasterPt2D &ImgSL, DOUBLE trueline, UINT range , DOUBLE thresh );
public:

    CE1IOPara m_CE1IOPara ;//!<CE-1����Ӱ���ڶ������
    /**
    * @fn mlCE1OPK2RMat
    * @date 2011.11.30
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CE-1����Ӱ���ⷽλ��Ԫ��ת��ת����
    * @param pitch ������
    * @param roll ������
    * @param yaw ��ƫ��
    * @param pRMat ��ת����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlCE1OPK2RMat( DOUBLE &pitch, DOUBLE &roll, DOUBLE &yaw, CmlMat* pRMat );
    /**
    * @fn mlCE1OPK2RMat
    * @date 2011.11.30
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ��CE-1����Ӱ�������ⷽλ��Ԫ��ת����Ԫ�ؼ���ת�������ʽ
    * @param vecEo �ⷽλԪ��
    * @param vecXsYsZs ��Ԫ��
    * @param vecR ��ת����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlCE1OPK2RMat( vector<ExOriPara> &vecEo, vector<Pt3d> & vecXsYsZs, vector<MatrixR> &vecR );
    /**
    * @fn mlCE1InOrietation
    * @date 2011.11.20
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CE-1����Ӱ���ڶ���
    * @param vecPtsList �������
    * @param pSatSio �ڶ�������ṹ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlCE1InOrietation( vector<Pt2d> &vecPtsList, CE1IOPara *pSatSio, vector<Pt2d> &vecXY );
    /**
    * @fn mlGetCE1DOM
    * @date 2011.12.07
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����CE-1����Ӱ��DOM
    * @param OriSatImg ԭʼCE-1����Ӱ��
    * @param vecR Ӱ���ⷽλ��ת����
    * @param vecXsYsZs Ӱ���ⷽλ��Ԫ��
    * @param pCE1IOP �ڷ�λԪ��
    * @param vecPtXYZ ��ά�﷽��
    * @param range �ⷽλ������Χ
    * @param thresh �������x����������ֵ֮�����ֵ
    * @param SatDom CE-1����Ӱ��DOM
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlGetCE1DOM( CmlRasterBlock &OriSatImg, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, CE1IOPara *pCE1IOP, vector<Pt3d> &vecPtXYZ, CmlRasterBlock &SatDom, UINT range = 5, DOUBLE thresh = 0.00002 );
};

/**
* @class CmlCE2LinearImage
* @date 2011.11.18
* @author  ��һ�� ylliu@irsa.ac.cn
* @brief CE-2��������Ӱ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlCE2LinearImage : public CmlLinearImage
{
public:
    /**
    * @fn CmlCE2LinearImage
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CmlCE2LinearImage��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlCE2LinearImage();
    /**
    * @fn ~CmlCE2LinearImage
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CmlCE2LinearImage����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual ~CmlCE2LinearImage();
    /**
    * @fn mlGetCE2DOMCoordinate
    * @date 2011.12.07
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����CE-2����Ӱ��DOM������ԭͼ���ϵ�x,y����
    * @param OriSatImg ԭʼӰ��
    * @param vecR Ӱ���ⷽλ��ת����
    * @param vecXsYsZs Ӱ���ⷽλ��Ԫ��
    * @param f �������
    * @param vecPtXYZ �﷽��ά����
    * @param pCE1IOP �ڷ�λԪ��
    * @param nWidth ����Ӱ����
    * @param nHeight Ӱ��߶�
    * @param thresh �������x����������ֵ֮�����ֵ
    * @param ImgSL ����Ӱ��DOM������ԭͼ���ϵ�x,y����
    * @param trueline Ӱ��������ʵ��
    * @param range ������Χ
    * @param thresh ��ֵ
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlGetCE2DOMCoordinate(CmlRasterBlock &OriSatImg, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, DOUBLE f, vector<Pt3d> &vecPtXYZ, UINT nWidth, UINT nHeight, CRasterPt2D &ImgSL, DOUBLE trueline, UINT range , DOUBLE thresh );
public:
    //CE2IOPara m_CE2IOPara ;//!<CE-2����Ӱ���ڶ������
    CE2IOPara m_CE2IOPara ;//!<CE-2����Ӱ���ڶ������
    /**
    * @fn mlCE2InOrietation
    * @date 2011.11.20
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CE-2����Ӱ���ڶ��򣬽�����Ӱ��ƥ��ͬ�������к�ת��Ϊ��ƽ������
    * @param vecPtsList ����ʱΪ������к����꣬���ʱΪ��ƽ������
    * @param pSatSio ����Ӱ���ڶ�������ṹ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlCE2InOrietation( vector<Pt2d> &vecPtsList, CE2IOPara *pSatSio, vector<Pt2d> &vecXY );
    /**
    * @fn mlCE2OPK2RMat
    * @date 2012.3.3
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CE-2����Ӱ���ⷽλ��Ԫ��ת��ת����
    * @param angX ��X��н�
    * @param angY ��Y��н�
    * @param angZ ��Z��н�
    * @param pRMat ��ת����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlCE2OPK2RMat( DOUBLE &angX, DOUBLE &angY, DOUBLE &angZ, CmlMat* pRMat );
    /**
    * @fn mlCE2OPK2RMat
    * @date 2011.11.30
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ��CE-2����Ӱ�������ⷽλ��Ԫ��ת����Ԫ�ؼ���ת�������ʽ
    * @param vecEo �ⷽλԪ��
    * @param vecXsYsZs ��Ԫ��
    * @param vecR ��ת����
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlCE2OPK2RMat( vector<ExOriPara> &vecEo, vector<Pt3d> & vecXsYsZs, vector<MatrixR> &vecR );
    /**
    * @fn mlGetCE2DOM
    * @date 2011.12.07
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����CE-2����Ӱ��DOM
    * @param OriSatImg ԭʼCE-2����Ӱ��
    * @param vecR Ӱ���ⷽλ��ת����
    * @param vecXsYsZs Ӱ���ⷽλ��Ԫ��
    * @param pCE1IOP �ڷ�λԪ��
    * @param pDem  ����Ӱ��DEM�߳�ֵ
    * @param PLL DEM���Ͻ�����X,Y
    * @param res DEM��X��Y����ķֱ���
    * @param range �ⷽλ������Χ
    * @param thresh �������x����������ֵ֮�����ֵ
    * @param SatDom CE-2����Ӱ��DOM
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlGetCE2DOM( CmlRasterBlock &OriSatImg, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, CE2IOPara *pCE2IOP, vector<Pt3d> &vecPtXYZ, CmlRasterBlock &SatDom, UINT range = 5, DOUBLE thresh = 0.00002 );
};


#endif // MLLINEARIMAGE_H
