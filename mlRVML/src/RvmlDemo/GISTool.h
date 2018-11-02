/************************************************************
  Copyright (C), 2011-2012, PMRS Lab, IRSA, CAS
  �ļ�����: GISTool.h
  ��������: 2011.11.6
  ��    ��: ��Ρ
  ��    ��: ���η�������
  �汾��ţ�1.0
  �޸���ʷ:   <����>   <ʱ��>   <�汾���>   <����>

***********************************************************/
#ifndef GISTOOL_H
#define GISTOOL_H
#include "gdal_header.h"
#include "gdal/gdal.h"
#include "gdal/gdal_alg.h"
#include "gdal/cpl_conv.h"
#include "gdal/cpl_string.h"
#include "gdal/ogr_api.h"
#include "gdal/ogr_srs_api.h"

/*************************************************
  ��������:    mlComeputeContour
  ��    ��:   ��Ρ
  ����������   �ȸ�������
  ��    �룺
  ����1���ȸ߾�
  ����2��DEM�ļ�·��
  ����3�������shape�ļ�·��
  ����4���Ƿ��Զ���Nodata
  ����5�����bCNodata����Ϊtrue����dNodata ��ֵ�ڼ���ʱ��������Чֵ�Դ�
  ����6������shape�ļ��̵߳��������ƣ�Ĭ��Ϊelev
  ��    ���� ����ֵ��1������ִ�У�-1��gdal�汾���ͣ�-2���ȸ߾���������-3�������ļ�������-4 ������ļ�������
  �汾��ţ�   1.0
  �޸���ʷ��   <����>   <ʱ��>   <�汾��>   <����>
  *************************************************/
int mlComeputeContour(double dHinterval,   char* strSrcfilename,   char* strDstfilename ,bool bCNodata = FALSE, double dNodata = 0.0,  char* cAttrib = "elev");
#endif // GISTOOL_H
