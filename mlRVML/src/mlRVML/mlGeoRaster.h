/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlGeoRaster.h
* @date 2011.11.21
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����դ����ʵ��ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#ifndef CMLGEORASTER_H
#define CMLGEORASTER_H

#include "mlGdalDataset.h"
//#define  DEM_BLOCK_SIZE 40000000
#define  DEM_BLOCK_SIZE 20000000

class CmlGeoRaster : public CmlGdalDataset
{
public:
    /**
     *@fn CmlGeoRaster()
     *@date 2011.11
     *@author ���Ļ�
     *@brief CmlGeoRaster�๹�캯��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    CmlGeoRaster();
    /**
     *@fn ��CmlGeoRaster
     *@date 2011.11
     *@author ���Ļ�
     *@brief CmlGeoRaster����������
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    virtual ~CmlGeoRaster();
    double m_dXResolution ; //!<X����ֱ���
    double m_dYResolution ;//!< Y����ֱ���
    //һ����ԣ�Y����ֱ���Ϊ�������Ҿ���ֵ����X����ֱ���
    Pt2d m_PtOrigin ;         //!<���Ͻ�ԭ������
public:
    /**
     *@fn ASCIIDemToGeoTiff()
     *@date 2011.11
     *@author ���Ļ�
     *@brief ASCII��ʽDEMתΪGeoTiff
     *@param strPathASCII ASCII��ʽDEM·��
     *@param strOutPathGeoTiff ת����GeoTiff�ļ�·��
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    bool ASCIIDemToGeoTiff( char* strPathASCII, char* strOutPathGeoTiff );
    /**
     *@fn GeoTiffToASCIIDem()
     *@date 2011.11
     *@author ���Ļ�
     *@brief GeoTiff��ʽDEMתΪASCII��ʽ
     *@param strOutPathGeoTiff GeoTiff�ļ�·��
     *@param strPathASCII ת����ASCII��ʽDEM·��
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    bool GeoTiffToASCIIDem( char* strOutPathGeoTiff, char* strPathASCII );
    /**
     *@fn LoadGeoFile
     *@date 2011.11
     *@author ���Ļ�
     *@brief ��������������դ������
     *@param sPath �����ļ�·��
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    bool LoadGeoFile( const SCHAR* sPath );
    /**
     *@fn CreateGeoFile
     *@date 2011.11
     *@author ���Ļ�
     *@brief ���������������դ������Ӳ���ļ�
     *@param sPath �����ļ�·��
     *@param ptLL ���Ͻ�����
     *@param dXResolution X����ֱ���
     *@param dYResolution Y����ֱ���
     *@param nH ����ͼ���
     *@param nW ����ͼ���
     *@param nBands ������
     *@param GDTType դ������
     *@param dNoData ��ֵ
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    bool CreateGeoFile( const SCHAR* sPath, Pt2d ptLL, DOUBLE dXResolution,DOUBLE dYResolution, SINT nH, SINT nW, SINT nBands, GDALDataType GDTType, double dNoData );
    /**
     *@fn SaveToGeoFile
     *@date 2011.11
     *@author ���Ļ�
     *@brief �����������Gdal�ļ���
     *@param vecZVal ���Ͻǡ���˳��洢��Zֵ����
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    bool SaveToGeoFile( vector<double> &vecZVal );
    /**
     *@fn SaveToGeoFile()
     *@date 2011.11
     *@author ���Ļ�
     *@brief �����������Gdal�ļ��У�Ϊ���ɵ�ֱ������DEM��ע�⣬��д���Ӳ���ļ��ݶ�Ϊdouble��TIFF
     *@param ���Ͻǡ���˳��洢��Zֵ����
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    bool SaveToGeoFile( double* pZVal );
    /**
     *@fn SaveToGeoFile
     *@date 2011.11
     *@author ���Ļ�
     *@brief ��Block���ݴ���Gdal�ļ���.ע�⣬Block����Ӧ��ͬӲ���ļ�������ͬ����������
     *@param nBand д�벨�κ�
     *@param nXOffSet д���ļ���ʼX����
     *@param nYOffSet д���ļ���ʵY����
     *@param pBlock д������
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
     */
    bool SaveToGeoFile( int nBand, int nXOffSet, int nYOffSet, CmlRasterBlock* pBlock );

    bool GetGeoInfo( const SCHAR* strGeoFile, Pt2d &ptOrig, DOUBLE &dXRes, DOUBLE &dYRes, UINT &nW, UINT &nH, DOUBLE &dNoDataVal );

    bool SetGeoInfo( const SCHAR* strGeoFile, Pt2d ptOrig, DOUBLE dXRes, DOUBLE dYRes, DOUBLE dNoDataVal );
protected:
private:
    double m_dGdalTransPara[6];
};

#endif // CMLGEORASTER_H
