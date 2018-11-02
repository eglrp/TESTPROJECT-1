/************************************************************
  Copyright (C), 2011-2012, PMRS Lab, IRSA, CAS
  �ļ�����: CmlRasterband.cpp
  ��������: 2011.11.6
  ��    ��: ��Ρ
  ��    ��: CmlRasterband����CmlRasterDataBuffer���ʵ��
  �汾��ţ�1.0
  �޸���ʷ:   <����>   <ʱ��>   <�汾���>   <����>

***********************************************************/
#include "CmlRasterBand.h"



/*
   RasterBand class implement code
*/
/*************************************************
  ��������:    CmlRasterBand
  ��    ��:   ��Ρ
  ����������   CmlRasterBand�Ĺ��캯��
  ��    �룺  GDALRasterBand����
  ��    ����  ��
  �汾��ţ�   1.0
  �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
  *************************************************/
CmlRasterBand::CmlRasterBand(GDALRasterBand* pband)
{
    m_pBand = pband;
    m_DataType = this->GetRasterDataType();
    m_nPixelDataSize = 0;
    switch (m_DataType)
    {
    case GDT_Unknown:
        m_nPixelDataSize = 0;
        break;
    case GDT_Byte:
        m_nPixelDataSize = 1;
        break;
    case GDT_UInt16:
        m_nPixelDataSize = 2;
        break;
    case GDT_Int16:
        m_nPixelDataSize = 2;
        break;
    case GDT_UInt32:
        m_nPixelDataSize = 4;
        break;
    case GDT_Int32:
        m_nPixelDataSize = 4;
        break;
    case GDT_Float32:
        m_nPixelDataSize = 4;
        break;
    case GDT_Float64:
        m_nPixelDataSize = 8;
        break;
    case GDT_CInt16:
        m_nPixelDataSize = 16;
        break;
    case GDT_CInt32:
        m_nPixelDataSize = 32;
        break;
    case GDT_CFloat32:
        m_nPixelDataSize = 32;
        break;
    case GDT_CFloat64:
        m_nPixelDataSize = 64;
        break;
    default:
        m_nPixelDataSize = 0;
        break;
    }
}

/*************************************************
  ��������:    GetRasterDataType
  ��    ��:   ��Ρ
  ����������   ����m_pBand��data����
  ��    �룺  ��
  ��    ����  GDALDataType����
  �汾��ţ�   1.0
  �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
  *************************************************/
GDALDataType CmlRasterBand::GetRasterDataType()
{
    if(m_pBand != NULL)
        return m_pBand->GetRasterDataType();
    else
        return GDT_Unknown;
}

/*************************************************
  ��������:    GetDataset
  ��    ��:   ��Ρ
  ����������   ����m_pBand��GDALDataset����
  ��    �룺  ��
  ��    ����  ����m_pBand��GDALDataset����
  �汾��ţ�   1.0
  �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
  *************************************************/
GDALDataset* CmlRasterBand::GetDataset()
{
    if(m_pBand == NULL)
    {
        return NULL;
    }
    try
    {
        GDALDataset* pDataset = m_pBand->GetDataset();
        return pDataset;
    }
    catch(...)
    {
        return NULL;
    }
}

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
int CmlRasterBand::GetPixelValue(int xLocation, int yLocation, double &Data)
{
    try
    {
        char *pData= new char[1*m_nPixelDataSize];
        CPLErr err ;
        err = m_pBand->RasterIO(GF_Read,xLocation,yLocation,1,1, &pData,1,1,m_pBand->GetRasterDataType(),0,0);
        switch (m_DataType)
        {
        case GDT_Unknown:
        {
            return -1;
            break;
        }
        case GDT_Byte:
        {
            CmlRasterDataBuffer<char> bf(pData);
            // bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_UInt16:
        {
            CmlRasterDataBuffer<unsigned short> bf(pData);
            //  bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_Int16:
        {
            CmlRasterDataBuffer<short> bf(pData);
            //  bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_UInt32:
        {
            CmlRasterDataBuffer<int32_t> bf(pData);
            //    bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_Int32:
        {
            CmlRasterDataBuffer<unsigned int> bf(pData);
            //    bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_Float32:
        {
            CmlRasterDataBuffer<float> bf(pData);
            //  bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_Float64:
        {
            CmlRasterDataBuffer<double> bf(pData);
            //   bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_CInt16:
        {
            CmlRasterDataBuffer<int16_t> bf(pData);
            //    bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_CInt32:
        {
            CmlRasterDataBuffer<int32_t> bf(pData);
            //    bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_CFloat32:
        {
            CmlRasterDataBuffer<float> bf(pData);
            //   bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        case GDT_CFloat64:
        {
            CmlRasterDataBuffer<double> bf(pData);
            //   bf.Buffer = pData;
            Data = bf.Buffer[1];
            break;
        }
        default:
            m_nPixelDataSize = 0;
            break;
        }
        delete []pData;
        if(err == CE_Failure)
            return -1;
        else
            return err;

    }
    catch(...)
    {
        return -1;
    }
}

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
int CmlRasterBand::SetPixelValue(int xLocation, int yLocation, double Data)
{
    try
    {
        void *pData= new char[1*m_nPixelDataSize];
        switch (m_DataType)
        {
        case GDT_Unknown:
        {
            return -1;
            break;
        }
        case GDT_Byte:
        {
            CmlRasterDataBuffer<char> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_UInt16:
        {
            CmlRasterDataBuffer<unsigned short> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_Int16:
        {
            CmlRasterDataBuffer<short> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_UInt32:
        {
            CmlRasterDataBuffer<int32_t> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_Int32:
        {
            CmlRasterDataBuffer<unsigned int> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_Float32:
        {
            CmlRasterDataBuffer<float> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_Float64:
        {
            CmlRasterDataBuffer<double> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_CInt16:
        {
            CmlRasterDataBuffer<int16_t> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_CInt32:
        {
            CmlRasterDataBuffer<int32_t> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_CFloat32:
        {
            CmlRasterDataBuffer<float> bf(pData);
            bf.Buffer[1] = Data ;
            break;
        }
        case GDT_CFloat64:
        {
            CmlRasterDataBuffer<double> bf(pData);
            bf.Buffer[1] = Data  ;
            break;
        }
        default:
        {
            return -1;
            break;
        }
        }

        CPLErr err ;
        err = m_pBand->RasterIO(GF_Write,xLocation,yLocation,1,1,pData,1,1,m_pBand->GetRasterDataType(),0,0);
        m_pBand->FlushCache();
        if(err == CE_Failure)
            return -1;
        else
            return err;
    }
    catch(...)
    {
        return -1;
    }

}

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
int CmlRasterBand::ReadRasterBlock(int xLocation,int yLocation,int xSize,int ySize,void* pData)
{
    try
    {
        CPLErr err ;
        err = m_pBand->RasterIO(GF_Read,xLocation,yLocation,xSize,ySize,pData,xSize,ySize,m_pBand->GetRasterDataType(),0,0);

        if(err == CE_Failure)
            return -1;
        else
            return err;
    }
    catch(...)
    {
        return -1;
    }
}

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
int CmlRasterBand:: WriteRasterBlock(int xLocation,int yLocation,int xSize,int ySize,void* pData)
{
    try
    {
        CPLErr err ;
        err = m_pBand->RasterIO(GF_Write,xLocation,yLocation,xSize,ySize,pData,xSize,ySize,m_pBand->GetRasterDataType(),0,0);
        if(err == CE_Failure)
            return -1;
        else
            return err;
    }
    catch(...)
    {
        return -1;
    }
}

/*************************************************
  ��������:    GetDataset
  ��    ��:   ��Ρ
  ����������   ����m_pBand��GDALDataset����
  ��    �룺  ��
  ��    ����  ����m_pBand��GDALDataset����
  �汾��ţ�   1.0
  �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
  *************************************************/
GDALRasterBand* CmlRasterBand::GetGDALRasterBand()
{
    return m_pBand;
}
