/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlFrameImage.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ����ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef CMLFRAMEIMAGE_H
#define CMLFRAMEIMAGE_H

#include "mlGdalDataset.h"
#include "mlBase.h"

/**
* @class CmlFrameImage
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������Ӱ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlFrameImage : public CmlGdalDataset
{
public:
    /**
    * @fn CmlFrameImage
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlFrameImage��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlFrameImage();
    /**
    * @fn ~CmlFrameImage
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlFrameImage����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual ~CmlFrameImage();
    /**
    * @fn LoadFile
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��ȡͼ��ֱ�Ӵ����Ӧ��block��
    * @param FileName �ļ�·��
    * @param nType �ļ�����
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool LoadFile( const SCHAR *FileName, SINT nType=0);
    /**
    * @fn
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �������Ӱ�����У��
    * @param pInImg ����ͼ��
    * @param pOutImg ���ͼ��
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool GetUnDistortImg( CmlRasterBlock* pInImg,  CmlRasterBlock* pOutImg, CAMTYPE nCamType = Nav_Cam, DOUBLE dZoomCoef = 1.0 );
    /**
    * @fn
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �������Ӱ�����У��
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool GetUnDistortImg( CAMTYPE nCamType = Nav_Cam, DOUBLE dZoomCoef = 1.0 );

    /**
    * @fn SmoothByGuassian
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �������Ӱ��ȥ���˹�˲�
    * @param nTemplateSize �˲�ģ���С
    * @param dCoef �˲��˲���,һ����0.8Ϊ��
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool SmoothByGuassian( SINT nTemplateSize, DOUBLE dCoef );

    /**
    * @fn SmoothByGuassian
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �������Ӱ��ȥ���˹�˲�
    * @param nTemplateSize �˲�ģ���С
    * @param dCoef �˲��˲���,һ����0.8Ϊ��
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool SmoothByGuassian( CmlRasterBlock &clsBlock, SINT nTemplateSize, DOUBLE dCoef );
    /**
    * @fn ExtractFeatPtByForstner
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �������Ӱ��Forstner������ȡ������
    * @param nGridSize ������С
    * @param nPtNum ����ȡ�ĵ���
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool ExtractFeatPtByForstner( SINT nGridSize, SINT nPtNum = 0, DOUBLE dThresCoef = 1.0, bool bIsRemoveAbPixel = false );
    /**
    * @fn UnDisCorToPlaneFrame
    * @date 2011.11.20
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ���������������겢ת������ƽ������ϵ
    * @param imgInList ͼ������꣨���Ͻ�����ϵ��
    * @param inPara �ڶ������
    * @param imgOutList ��ƽ������x,y
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool UnDisCorToPlaneFrame(vector<Pt2d>& imgInList, InOriPara& inPara, vector<Pt2d>& imgOutList, CAMTYPE nCamType = Nav_Cam );

    bool UnDisCorToPlaneFrame( Pt2d pt, InOriPara inPara, Pt2d &ptRes, CAMTYPE nCamType = Nav_Cam );

    bool UnDisCorToPlaneFrame(vector<Pt2d>& imgInList, InOriPara& inPara, UINT nHeight, vector<Pt2d>& imgOutList, CAMTYPE nCamType = Nav_Cam );

    bool UnDisCorToPlaneFrame( Pt2d pt, InOriPara inPara, UINT nHeight, Pt2d &ptRes, CAMTYPE nCamType = Nav_Cam );

//    bool CalcObjPtsInFrame( Pt3d ptXYZ, UINT nHeight, InOriPara inPara, ExOriPara exPara, CAMTYPE nCamType, Pt2d &ptRes );

    bool AddDisCorToPlaneFrame( Pt2d ptxyOrig, UINT nHeight, InOriPara inPara, ExOriPara exPara, CAMTYPE nCamType, Pt2d &ptRes );
    /**
    * @fn UnDisCorToPicCoord
    * @date 2011.11.20
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����������������.ת����ͼ������ϵ
    * @param imgInList ͼ������꣨���Ͻ�����ϵ��
    * @param inPara �ڶ������
    * @param imgOutList ���������ͼ������꣨���Ͻ�����ϵ��
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool UnDisCorToPicCoord(vector<Pt2d>& imgPtsList, InOriPara& inPara, vector<Pt2d>& imgOutList, CAMTYPE nCamType = Nav_Cam );



    CmlRasterBlock m_DataBlock;//!<���ݿ�
    vector<Pt2i> m_vecFeaPtsList ;//!<���Forstner������

    InOriPara m_InOriPara;//!<�ڶ������
    ExOriPara m_ExOriPara;//!<�ⶨ�����
    /**
    * @fn mlGetBilinearValue
    * @date 2012.01.08
    * @author �⿭ wukai@irsa.ac.cn
    * @brief ����Ӱ��Ҷ�ֵ��˫�����ڲ�.�����Ͻ�����ϵ��
    * @param pImg ԭʼӰ��
    * @param tempXY �������
    * @version 1.0
    * @return �Ҷ��ڲ���Ӧ��Ӱ��Ҷ�ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    BYTE mlGetBilinearValue(CmlRasterBlock *pImg , Pt2d tempXY) ;
    /**
    * @fn mlGetNearValue
    * @date 2012.01.08
    * @author �⿭ wukai@irsa.ac.cn
    * @brief ����ĳ����Ӱ���ϵ����ٽ����ص��ֵ
    * @param pImg ԭʼӰ��
    * @param tempXY �������
    * @version 1.0
    * @return ���ٽ����ص��ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    BYTE mlGetNearValue(CmlRasterBlock *pImg , Pt2d tempXY) ;
    /**
    * @fn mlBilinearInterpolation
    * @date 2011.11.20
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ˫�����ڲ�
    * @param pImg ԭʼӰ��
    * @param pCoordinate �ڲ�ǰ�����������
    * @param pDisImg �ڲ��Ӱ��
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlBilinearInterpolation( CmlRasterBlock *pImg , CRasterPt2D *pCoordinate, CmlRasterBlock *pDisImg );
    /**
    * @fn mlGetDistortionCoordinate
    * @date 2011.11.20
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief �����������������
    * @param pDisImg ԭʼ����Ӱ��
    * @param pCoordinate ��������������
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlGetDistortionCoordinate( CmlRasterBlock *pDisImg , CRasterPt2D * pCoordinate, CAMTYPE nCamType = Nav_Cam, DOUBLE dZoomCoef = 1.0 );
    /**
    * @fn mlGrayInterpolation
    * @date 2011.11.20
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ͼ��Ҷ��ڲ�
    * @param pImg ԭʼӰ��
    * @param pCoordinate �ڲ�ǰ�����������
    * @param pDisImg �ڲ��Ӱ��
    * @param nOptions �Ҷ��ڲ�����
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlGrayInterpolation( CmlRasterBlock *pImg , CRasterPt2D *pCoordinate, CmlRasterBlock *pDisImg, int nOptions );

    /**
    * @fn mlCleanDeadPixel
    * @date 2012.02
    * @author ������ zhangchy@irsa.ac.cn
    * @brief ����Ӱ�񻵵�ȥ��
    * @param strImgPathIn ����ͼ��·��
    * @param strImgPathOut ���ͼ��·��
    * @param vecDeadPix ����λ��
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool mlCleanDeadPix( const char* strImgPathIn, const char* strImgPathOut, vector<Pt2i> vecDeadPix );

    bool ExtractFeatPtByForstner(CmlRasterBlock &InputImg, vector<Pt2i> &vecFeaPts, SINT nGridSize,  SINT nPtNum = 0, DOUBLE dThresCoef = 1.0, bool bIsRemoveAbPixel = false );

    bool GrayTensile( CmlRasterBlock* pBlock, UINT nMin = 0, UINT nMax = 255 );

    bool GrayTensile( UINT nMin = 0, UINT nMax = 255 );

    bool SaveFile( const char* strOutPath );

    bool HistogramEqualize();
	bool RasterGrayStrench(CmlRasterBlock *rasterBlock,double dThresh =0.0015);//դ��Ӱ�����죬����ƥ�����ƥ�����

    bool DrawCrossMark( vector<Pt2i> vecPts, UINT nLineLength = 10, UINT nLineWidth = 2 );

    bool WallisFilter( UINT nTemplateSize, DOUBLE dExpectMean, DOUBLE dExpectVar, DOUBLE dCoefA, DOUBLE dCoefAlpha );

    bool PtSelectionByGrid( vector<Pt2d> vecPts, UINT nImgW, UINT nImgH, UINT nGridW, UINT nGridH, vector<Pt2d> &vecOutRes );
    bool PtSelectionByGrid( vector<Pt2d> vecPts, UINT nImgW, UINT nImgH, UINT nGridW, UINT nGridH, vector<bool> &vecFlags );

    bool EdgeDetectionByCanny( void* pImg, vector<Pt2i> &vecPts, DOUBLE dThresHold1, DOUBLE dThresHold2, UINT nMaxPts = 10000 );

    bool EdgeDetectionByCanny( const SCHAR* strInPath, vector<Pt2i> &vecPts, DOUBLE dThresHold1, DOUBLE dThresHold2, UINT nMaxPts = 10000 );
    /**
    * @fn imgpyramid
    * @date 2012.02
    * @author pengman@irsa.ac.cn
    * @brief Ӱ�����������
    * @param InputImg ԭʼӰ��
    * @param OutputImg ���ͼ��
    * @param nSize ������Ӱ�������ϵ��
    * @version 1.0
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool imgpyramid( CmlRasterBlock *InputImg, vector<CmlRasterBlock> &OutputImg,SINT nSize);


protected:
private:


};

#endif // CMLFRAMEIMAGE_H
