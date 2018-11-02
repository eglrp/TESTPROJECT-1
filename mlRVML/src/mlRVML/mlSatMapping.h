/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlSatMapping.h
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��������Ӱ����ͼͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/

#ifndef CMLSATMAPPING_H
#define CMLSATMAPPING_H
#include "mlMat.h"
#include "mlBase.h"
#include "mlTypes.h"
#include "mlGdalDataset.h"
#include "mlRasterBlock.h"
#include "mlBlockCalculation.h"
#include "mlLinearImage.h"
#include "mlStereoProc.h"
#include "mlSiteMapping.h"
#include "mlCoordTrans.h"
#include "SiftMatch.h"
#include "ASift.h"

/**
* @class CmlSatMapping
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��������Ӱ����ͼ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlSatMapping
{
public:
    /**
    * @fn CmlSatMapping
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CmlSatMapping��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlSatMapping();
    /**
    * @fn ~CmlSatMapping
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief CmlSatMapping����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual ~CmlSatMapping();
public:
    /**
    * @fn mlSatMatch
    * @date 2012.2.21
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����Ӱ��������ƥ��
    * @param sLimgPath ��Ӱ��·��
    * @param sRimgPath ��Ӱ��·��
    * @param satPara ƥ�����
    * @param vecRanPts ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlSatMatch( const string sLimgPath, const string sRimgPath, SatOptions &satPara, vector<StereoMatchPt> &vecRanPts, SINT nMethod = 0);
    /**
    * @fn mlSatMappingByPts
    * @date 2012.2.21
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ������Ӱ��ƥ��������ܼ�ƥ��㼰�﷽��ά�㣬����DEM��DOM
    * @param satproj ����Ӱ��DEM��DOM���ɹ��̲���
    * @param satPara ����Ӱ��DEM��DOM���ɲ���
    * @param vecRanPts ƥ���
    * @param vecDensePts �ܼ�ƥ��㼰�﷽��ά��
    * @param vecPres  �﷽��ά�㾫��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlSatMappingByPts( SatProj &satproj, SatOptions &satPara, vector<StereoMatchPt> &vecRanPts, vector<StereoMatchPt> &vecDensePts, vector<Pt3d> &vecPres );
    /**
    * @fn mlCE1MappingByPts
    * @date 2012.2.21
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ��CE-1����Ӱ��ƥ��������ܼ�ƥ��㼰�﷽��ά�㣬����DEM��DOM
    * @param satproj ����Ӱ��DEM��DOM���ɹ��̲���
    * @param satPara ����Ӱ��DEM��DOM���ɲ���
    * @param vecRanPts ƥ���
    * @param vecDensePts �ܼ�ƥ��㼰�﷽��ά��
    * @param vecPres  �﷽��ά�㾫��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlCE1MappingByPts( SatProj &satproj, SatOptions &satPara, vector<StereoMatchPt> &vecRanPts, vector<StereoMatchPt> &vecDensePts, vector<Pt3d> &vecPres );
    /**
    * @fn mlCE2MappingByPts
    * @date 2012.2.21
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ��CE-2����Ӱ��ƥ��������ܼ�ƥ��㼰�﷽��ά�㣬����DEM��DOM
    * @param satproj ����Ӱ��DEM��DOM���ɹ��̲���
    * @param satPara ����Ӱ��DEM��DOM���ɲ���
    * @param vecRanPts ƥ���
    * @param vecDensePts �ܼ�ƥ��㼰�﷽��ά��
    * @param vecPres  �﷽��ά�㾫��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlCE2MappingByPts( SatProj &satproj, SatOptions &satPara, vector<StereoMatchPt> &vecRanPts, vector<StereoMatchPt> &vecDensePts, vector<Pt3d> &vecPres );
    /**
    * @fn WriteBLH
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����ά�����������ɹ������DEM������GeoTiff��ʽ�洢
    * @param path �ļ�·��
    * @param vecBLH ��ά��������
    * @param XResolution X����ֱ���
    * @param YResolution Y����ֱ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool WriteBLH( const SCHAR *path, vector<Pt3d> &vecBLH, DOUBLE XResolution, DOUBLE YResolution );
    /**
    * @fn GenerateDOM
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����CE-1����Ӱ��DOM����GeoTiff��ʽ�洢
    * @param dempath DEM·��
    * @param path DOM�洢·��
    * @param CE1IO �϶�һ���ڷ�λ����
    * @param ImgBlock ԭʼӰ��
    * @param vecR ��ת����
    * @param vecXsYsZs �ⷽλ��Ԫ��
    * @param domBlock ���ɵ�DOM
    * @param nBands Ӱ�񲨶���
    * @param nodata ��������ֵ
    * @param B0 ī����ͶӰ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool GenerateDOM( const SCHAR *dempath, const SCHAR *path, CE1IOPara &CE1IO, CmlRasterBlock &ImgBlock, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, CmlRasterBlock &domBlock, DOUBLE B0, UINT nBands, DOUBLE nodata );
    /**
    * @fn GenerateCE2DOM
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����DOM����GeoTiff��ʽ�洢
    * @param dempath DEM·��
    * @param path DOM�洢·��
    * @param CE2IO �϶�һ���ڷ�λ����
    * @param ImgBlock ԭʼӰ��
    * @param vecR ��ת����
    * @param vecXsYsZs �ⷽλ��Ԫ��
    * @param domBlock ���ɵ�DOM
    * @param nBands Ӱ�񲨶���
    * @param nodata ��������ֵ
    * @param B0 ī����ͶӰ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool GenerateCE2DOM( const SCHAR *dempath, const SCHAR *path, CE2IOPara &CE2IO, CmlRasterBlock &ImgBlock, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, CmlRasterBlock &domBlock, DOUBLE B0, UINT nBands, DOUBLE nodata );
    /**
    * @fn InterSection
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ǰ������������ά�﷽��
    * @param ptSubDenseL ��Ӱ����������ܼ�ƥ���
    * @param ptSubDenseR ��Ӱ����������ܼ�ƥ���
    * @param vecXYL ��Ӱ��齹ƽ������
    * @param vecXYR ��Ӱ��齹ƽ������
    * @param vecLXsYsZs ��Ӱ����ⷽλ��Ԫ��
    * @param vecRXsYsZs ��Ӱ����ⷽλ��Ԫ��
    * @param vecRL ��Ӱ�����ת����
    * @param vecRR ��Ӱ�����ת����
    * @param lf ��Ӱ�񽹾�
    * @param rf ��Ӱ�񽹾�
    * @param vecBLH ��ά�﷽��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool InterSection(vector<Pt2d> &ptSubDenseL, vector<Pt2d> &ptSubDenseR, vector<Pt2d> &vecXYL, vector<Pt2d> &vecXYR, \
                                 vector<Pt3d> &vecLXsYsZs, vector<Pt3d> &vecRXsYsZs,vector<MatrixR> &vecRL, vector<MatrixR> &vecRR, DOUBLE lf, DOUBLE rf,vector<Pt3d> &vecBLH );
    /**
    * @fn ConstractAdjust
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief Ӱ���Զ��Աȶ���ǿ
    * @param Img Ӱ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool ConstractAdjust(CmlRasterBlock &Img);
protected:
private:
};

#endif // CMLSATMAPPING_H
