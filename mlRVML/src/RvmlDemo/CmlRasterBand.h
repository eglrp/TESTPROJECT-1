/************************************************************
  Copyright (C), 2011-2012, PMRS Lab, IRSA, CAS
  �ļ�����: CmlRasterBand.h
  ��������: 2011.11.6
  ��    ��: ��Ρ
  ��    ��: CmlRasterband����CmlRasterDataBuffer�������
  �汾��ţ�1.0
  �޸���ʷ:   <����>   <ʱ��>   <�汾���>   <����>

***********************************************************/
#ifndef RASTERBAND_H
#define RASTERBAND_H
#include"gdal_header.h"
#include"CmlRasterDataset.h"

// CmlRasterBand�࣬��GDALRasterBandΪ�������򵥷�װ��д���ݵĹ���
class CmlRasterBand
{
public:
    /*************************************************
      ��������:    CmlRasterBand
      ��    ��:   ��Ρ
      ����������   CmlRasterBand�Ĺ��캯��
      ��    �룺  GDALRasterBand����
      ��    ����  ��
      �汾��ţ�   1.0
      �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
      *************************************************/
    CmlRasterBand(GDALRasterBand * pband);

    // raster��������ֵ�Ĵ�С�����ֽ�Ϊ��λ
    int m_nPixelDataSize;

    // GDAL�������ͽṹ
    GDALDataType m_DataType;
public:
    /*************************************************
      ��������:    GetRasterDataType
      ��    ��:   ��Ρ
      ����������   ����m_pBand��data����
      ��    �룺  ��
      ��    ����  GDALDataType����
      �汾��ţ�   1.0
      �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
      *************************************************/
    GDALDataType GetRasterDataType();

    /*************************************************
      ��������:    GetPixelValue
      ��    ��:   ��Ρ
      ����������   �ڲ����϶�ȡָ��λ�õ�����ֵ
      ��    �룺  x�� �кţ�
                 y�� �кţ�   �������Ͻ�λ��Ϊ��0��0��
      ��    ����  ����ֵ�� ������ʾִ��ʧ�ܣ�����ɹ���
                 Data����ȡ��������
      �汾��ţ�   1.0
      �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
      *************************************************/
    int GetPixelValue(int x, int y, double &Data);

    /*************************************************
      ��������:    SetPixelValue
      ��    ��:   ��Ρ
      ����������   �ڲ�����д��ָ��λ�õ�����ֵ
      ��    �룺  x�� �кţ�
                 y�� �кţ��������Ͻ�λ��Ϊ��0��0����
                 Data��д�������
      ��    ����  ����ֵ�� ������ʾִ��ʧ�ܣ�����ɹ�
      �汾��ţ�   1.0
      �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
      *************************************************/
    int SetPixelValue(int x, int y, double Data);

    /*************************************************
      ��������:    ReadRasterBlock
      ��    ��:   ��Ρ
      ����������   �ڲ����϶�ȡָ��λ��ָ����С������ֵ����
      ��    �룺  xLocation�� �кţ�
                 yLocation�� �кţ� �������Ͻ�λ��Ϊ��0��0����
                 xSize��x�����С��
                 ySize�� y�����С��
                 pData��������ݵ��ڴ��ַ
      ��    ����  ����ֵ�� ������ʾִ��ʧ�ܣ�����ɹ�
      �汾��ţ�   1.0
      �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
      *************************************************/
    int ReadRasterBlock(int xLocation,int yLocation,int xSize,int ySize,void* pData);

    /*************************************************
      ��������:    WriteRasterBlock
      ��    ��:   ��Ρ
      ����������   �ڲ�����д��ָ��λ��ָ����С������ֵ����
      ��    �룺  xLocation�� �кţ�
                 yLocation�� �кţ��������Ͻ�λ��Ϊ��0��0����
                 xSize��x�����С��
                 ySize�� y�����С��
                 pData��д�����ݵ��ڴ��ַ
      ��    ����  ����ֵ�� ������ʾִ��ʧ�ܣ�����ɹ�
      �汾��ţ�   1.0
      �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
      *************************************************/
    int WriteRasterBlock(int xLocation,int yLocation,int xSize,int ySize,void* pData);

    /*************************************************
      ��������:    GetDataset
      ��    ��:   ��Ρ
      ����������   ����m_pBand��GDALDataset����
      ��    �룺  ��
      ��    ����  ����m_pBand��GDALDataset����
      �汾��ţ�   1.0
      �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
      *************************************************/
    GDALDataset* GetDataset();

    /*************************************************
      ��������:    GetDataset
      ��    ��:   ��Ρ
      ����������   ����m_pBand��GDALDataset����
      ��    �룺  ��
      ��    ����  ����m_pBand��GDALDataset����
      �汾��ţ�   1.0
      �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
      *************************************************/
    GDALRasterBand* GetGDALRasterBand();

private:
    // GDAL������
    GDALRasterBand *m_pBand;

};

template  <typename T>
class CmlRasterDataBuffer
{
public:
    CmlRasterDataBuffer(void * pdata ,long Row = 0, long Col = 0);

    CmlRasterDataBuffer();
    ~CmlRasterDataBuffer();
    long m_row;
    long m_col;

public:
    T* Buffer;
};
template  <typename T> CmlRasterDataBuffer<T>::CmlRasterDataBuffer( )
{
    Buffer = NULL;
}
template  <typename T> CmlRasterDataBuffer<T>::CmlRasterDataBuffer(void *pdata,long Row,long Col)
{
    Buffer = (T*)pdata;
    m_row = Row;
    m_col = Col;
}

template  <typename T>CmlRasterDataBuffer<T>::~CmlRasterDataBuffer()
{

}

#endif // RASTERBAND_H
