/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlGdalDataset.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief GDALͼ���������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/

#ifndef CGDALDATASET_H
#define CGDALDATASET_H

#include "mlFileRaster.h"
/**
* @struct ImageSqlTYPE
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ͼ�񲨶����з�ʽ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef enum  {
	BSQ = 0,//!<BSQ���з�ʽ
	BIP = 1,//!<BIP���з�ʽ
	BIL = 2//!<BIL���з�ʽ
}ImageSqlTYPE;
/**
* @struct geoImgTransTYPE
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����任��Ϣ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
enum geoImgTransTYPE	{
	geoImgTranNONE,//!<������任
	geoImgTranOFFSETSCALE,//!<ƽ����������任
	geoImgTranMATRIX//!<��ת��������任
};
/**
* @struct geoImgCacheINFO
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief դ����ͷ��Ϣ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
struct geoImgCacheINFO	{
	SINT tile_wid;
	SINT tile_hei;

	SLONG imgWid;//!<Ӱ���
	SLONG imgHei;//!<Ӱ���
	// same as raw image
	SSHORT samplesPerPixel;//!<ÿ���ز�����
	// for DEM, 2 per sample
	// maybe different with raw, eg. 11 bit to 8 bit
	SSHORT bytesPerPixel;//!<ÿ���ر�����
	// DPI
	SSHORT xResolution;//!<X����ֱ���
	// DPO
	SSHORT yResolution;//!<Y����ֱ���
    // use trfMatrix or tie point
	geoImgTransTYPE	transType;//!<Ӱ��任����

	/////// TIFFTAG_GEOTIEPOSINTS ///////
	DOUBLE i0;//!<Ӱ���
	DOUBLE j0;//!<Ӱ���
	DOUBLE k0;//!<Ӱ���
	DOUBLE x0;//!<ģ�Ϳռ��
	DOUBLE y0;//!<ģ�Ϳռ��
	DOUBLE z0;//!<ģ�Ϳռ��
	// for dem
	DOUBLE xScale;//!<x��������ϵ��
	DOUBLE yScale;//!<y��������ϵ��
	DOUBLE zScale;//!<z��������ϵ��

	/////////// ModelTransformationTag /////////
	DOUBLE trfMatrix[4][4];	//!<��ת����

    // if tranformed to 8 bit from 11 bit, this value also tranfromed
	DOUBLE	minSampleValue;
	// if tranformed to 8 bit from 11 bit, this value also tranfromed
	DOUBLE	maxSampleValue;
	DOUBLE	max_min;

	DOUBLE	noDataValue;//!<��������ֵ
};
/**
* @class CmlGdalDataset
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��GDALΪ������դ������
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlGdalDataset : public CmlFileRaster
{
    public:
        /**
        * @fn CmlGdalDataset
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief CmlGdalDataset��ղι��캯��
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        CmlGdalDataset();
        /**
        * @fn ~CmlGdalDataset
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief CmlGdalDataset����������
        * @version 1.0
        * @return �޷���ֵ
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        virtual ~CmlGdalDataset();

    public:

    public:
        virtual UINT GetBands() const {return m_nBands;};//!<�õ�Ӱ�񲨶���
        virtual UINT GetBytes() const {return m_nBytes;};//!<�õ�Ӱ�������
        virtual UINT GetWidth() const {return m_nWidth;};//!<�õ�Ӱ���
        virtual UINT GetHeight() const {return m_nHeight;};//!<�õ�Ӱ���
        GDALDataset* GetGdalDataSet() {return m_pDataset;};//!<�õ�Ӱ������ͷָ��

        /**
        * @fn LoadFile
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ����դ���ļ�ͷ��Ϣ
        * @param FileName �ļ�·��
        * @param nType �ļ�����
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        virtual bool LoadFile( const SCHAR *FileName, const SINT nType=0) ;
        /**
        * @fn CreateFile
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief �ڴ����д���դ���ļ�
        * @param FileName �ļ�����
        * @param nW դ��Ӱ���
        * @param nH դ��Ӱ���
        * @param nBands դ��Ӱ�񲨶���
        * @param GDTType դ��Ӱ����������
        * @param BitsOut ����ͼ������
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        virtual bool CreateFile( const SCHAR *FileName, const UINT nW,const UINT nH, const UINT nBands, const GDALDataType GDTType, const SCHAR *BitsOut);
        /**
        * @fn SaveBlockToFile
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��block���ݴ����Ӧ�Ĵ����ļ�
        * @param nBand դ��Ӱ�񲨶κ�
        * @param nXOffSet դ��Ӱ��X����ƫ����
        * @param nYOffSet դ��Ӱ��Y����ƫ����
        * @param pImgBlock դ��Ӱ���
        * @param nBlockBand Ŀ���ļ����κ�
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        virtual bool SaveBlockToFile( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, CmlRasterBlock* pImgBlock, const UINT nBlockBand = 1);
        /**
        * @fn SaveBlockToFile
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��block���ݴ����Ӧ�Ĵ����ļ�
        * @param nBand դ��Ӱ�񲨶κ�
        * @param nXOffSet դ��Ӱ��X����ƫ����
        * @param nYOffSet դ��Ӱ��Y����ƫ����
        * @param pImgBlock դ��Ӱ���
        * @param nBlockXOffSet ���洢���ݿ���block��X����ƫ����
        * @param nBlockYOffSet ���洢���ݿ���block��Y����ƫ����
        * @param nW ���洢���ݿ��
        * @param nH ���洢���ݿ��
        * @param nBlockBand Ŀ���ļ����κ�
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        bool SaveBlockToFile( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, CmlRasterBlock* pImgBlock, const UINT nBlockXOffSet, \
                                             const UINT nBlockYOffSet, const UINT nW, const UINT nH, const UINT nBlockBand = 1 );
        /**
        * @fn GetRasterGrayBlock
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��GdalDataSet�еõ�ĳ������ĳ��λ��������ǿ��GDT_BYTE���͵�Ӱ���
        * @param nBand Ӱ�񲨶κ�(��1��ʼ)
        * @param nXOffSet Ӱ���X�������
        * @param nYOffSet Ӱ���Y�������
        * @param nW Ӱ����
        * @param nH Ӱ����
        * @param nZoom Ӱ�������ϵ��
        * @param pImgBlock դ��Ӱ���
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        bool GetRasterGrayBlock( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const UINT nZoom,CmlRasterBlock* pImgBlock );
        /**
        * @fn GetRasterGrayBlock
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��GdalDataSet�еõ�ĳ������ĳ��λ��������ǿ��GDT_BYTE���͵�Ӱ���
        * @param nBand Ӱ�񲨶κ�(��1��ʼ)
        * @param nXOffSet Ӱ���X�������
        * @param nYOffSet Ӱ���Y�������
        * @param nW Ӱ����
        * @param nH Ӱ����
        * @param nZoom Ӱ�������ϵ��
        * @param pImgBlock դ��Ӱ���
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        bool GetRasterGrayBlock( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const DOUBLE dZoom,CmlRasterBlock* pImgBlock );
        /**
        * @fn GetRasterGrayBlock
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��GdalDataSet�еõ�ĳ�������Σ�ǿ��GDT_BYTE�������䵱��R��G��B���κ�ϳ�block��block����ǿ��ΪGDT_BYTE��1����
        * @param nBandR Ӱ���R������ȡӰ�񲨶κ�
        * @param nBandG Ӱ���G������ȡӰ�񲨶κ�
        * @param nBandB Ӱ���B������ȡӰ�񲨶κ�
        * @param nXOffSet Ӱ���X�������
        * @param nYOffSet Ӱ���Y�������
        * @param nW Ӱ����
        * @param nH Ӱ����
        * @param nZoom Ӱ�������ϵ��
        * @param pImgBlock դ��Ӱ���
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        bool GetRasterGrayBlock( const UINT nBandR, const UINT nBandG, const UINT nBandB, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const UINT nZoom,CmlRasterBlock* pImgBlock );
        /**
        * @fn GetRasterRGBBlock
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��GdalDataSet�еõ�ĳ��������
        * @param nBandR Ӱ���R������ȡӰ�񲨶κ�
        * @param nBandG Ӱ���G������ȡӰ�񲨶κ�
        * @param nBandB Ӱ���B������ȡӰ�񲨶κ�
        * @param nXOffSet Ӱ���X�������
        * @param nYOffSet Ӱ���Y�������
        * @param nW Ӱ����
        * @param nH Ӱ����
        * @param nZoom Ӱ�������ϵ��
        * @param pImgBlock դ��Ӱ���
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        bool GetRasterRGBBlock( const UINT nBandR, const UINT nBandG, const UINT nBandB, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const UINT nZoom,CmlRasterBlock* pImgBlock );
        /**
        * @fn GetRasterOriginBlock
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��GdalDataSet�еõ������Σ�����ԭʼ���ݵ���block�У�block����ͬDataSet��ͬ
        * @param nBand Ӱ�񲨶κ�(��1��ʼ)
        * @param nXOffSet Ӱ���X�������
        * @param nYOffSet Ӱ���Y�������
        * @param nW Ӱ����
        * @param nH Ӱ����
        * @param nZoom Ӱ���SINT������ϵ��
        * @param pImgBlock դ��Ӱ���
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        bool GetRasterOriginBlock( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const UINT nZoom,CmlRasterBlock* pImgBlock );
        /**
        * @fn GetRasterOriginBlock
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��GdalDataSet�еõ������Σ�����ԭʼ���ݵ���block�У�block����ͬDataSet��ͬ
        * @param nBand Ӱ�񲨶κ�(��1��ʼ)
        * @param nXOffSet Ӱ���X�������
        * @param nYOffSet Ӱ���Y�������
        * @param nW Ӱ����
        * @param nH Ӱ����
        * @param dZoom Ӱ���DOUBLE������ϵ��
        * @param pImgBlock դ��Ӱ���
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        bool GetRasterOriginBlock( const UINT nBand, const UINT nXOffSet, const UINT nYOffSet, const UINT nW, const UINT nH, const DOUBLE dZoom,CmlRasterBlock* pImgBlock );
        /**
        * @fn GetNoDataVal
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ��ȡDataSet�еĿ�ֵ
        * @retval m_dNoDataValue ��ֵ
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        DOUBLE GetNoDataVal() const { return m_dNoDataValue;};//!<�õ�DataSet�п�ֵ�Ĵ���ֵ
        /**
        * @fn SetNoDataVal
        * @date 2011.11.02
        * @author ���Ļ� whwan@irsa.ac.cn
        * @brief ����DataSet�п�ֵ�Ĵ���ֵ
        * @param dNoData �����趨��ֵ����ֵ
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ��
        * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
        */
        bool  SetNoDataVal( DOUBLE dNoData ) ;

        GDALDataType GetGDTType( ) const { return  m_dataType;};//!<�õ���������

        bool m_bIsGeoFile;//!<�ж��Ƿ�Ϊ���е���������ļ�
    protected:


    private:
        UINT m_nBands;//!<Ӱ�񲨶���
        UINT m_nBytes;//!<Ӱ��洢λ��
        UINT m_nWidth;//!<Ӱ����
        UINT m_nHeight;//!<Ӱ��߶�
        USHORT	m_bitsPerSample;//!<ÿ���ε�ÿ����ռ�ֽ�����=m_dataType
        USHORT	*m_minSampleValues;
	    USHORT	*m_maxSampleValues;
        USHORT	*m_max_mins;
	    DOUBLE	m_dNoDataValue;//!<��ֵ

        UINT m_tile_wid;
        UINT m_tile_hei;
        bool  m_isTiled;

        //8bit=1,16bit=2;
        GDALDataType	m_dataType;//!<����������ռBit��
        GDALColorInterp m_colorInterp;//!<��ɫ�洢����
        geoImgCacheINFO	m_cacheInfo;//!<m_cacheInfo.samplesPerPixelΪÿ���ز�����
        GDALDataset		*m_pDataset;//!<���ݿ�ͷָ��
        GDALRasterBand	**m_ppBands;//!<GDAL����ͷָ��

};
/**
* @struct ImgPt
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief Ӱ���ƥ��ṹ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
struct ImgPt: public Pt2d
{
    //Ӱ���ƥ��ṹ,�洢�˵�š���Ķ�ά������ͼ��ָ��
    CmlGdalDataset* pImg;  //!<Ӱ�������Ӱ��ָ��
    ImgPt()
    {
        pImg = NULL;
    }
};


#endif // CGDALDATASET_H
