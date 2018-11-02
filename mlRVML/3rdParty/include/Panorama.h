/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file Panorama.h
* @date 2012.1.21
* @author ����
* @brief ȫ��ͼ��ƴ�ӵ���ͷ�ļ�
* @version 1.0
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#ifndef PANORAMA_H_INCLUDED
#define PANORAMA_H_INCLUDED

#include <string.h>
#include <vector>
using namespace std;

#if defined _WIN32 || defined _WIN64
#include "targetver.h"
#endif
//--------------------------------------
////////////////////////
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
#define PANOMOSAIC_CDECL __cdecl
#define PANOMOSAIC_STDCALL __stdcall
#else
#define PANOMOSAIC_CDECL
#define PANOMOSAIC_STDCALL
#endif

#ifndef PANOMOSAIC_EXTERN_C
#ifdef __cplusplus
#define PANOMOSAIC_EXTERN_C extern "C"
#define PANOMOSAIC_DEFAULT(val) = val
#else
#define PANOMOSAIC_EXTERN_C
#define PANOMOSAIC_DEFAULT(val)
#endif
#endif

#if ( defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64 ) && (defined MLPANOMOSAIC_EXPORTS)
#define PANOMOSAIC_EXPORTS __declspec(dllexport)
#else
#define PANOMOSAIC_EXPORTS
#endif

#ifndef PANOMOSAIC_API
#define PANOMOSAIC_API(rettype) PANOMOSAIC_EXTERN_C PANOMOSAIC_EXPORTS rettype PANOMOSAIC_CDECL
#endif

//--------------------------------------
/**
* @strut MatchPt
* @date 2012.1.21
* @author ����
* @brief ƥ���ṹ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
struct MatchPt
{
	float x, y;//���Ƶ�x��y����
	unsigned int ptImgIdxL;//���Ƶ�srcͼ����ţ���λ����1001��NNNN
	unsigned int ptImgIdxR;//���Ƶ�dstͼ����ţ���λ����1001��NNNN
	unsigned long long int ptIdx;//���Ƶ�ID��ʮ��λ���磺1001100200000001
};


/**
* @strut PanoMatchInfo
* @date 2012.1.21
* @author ����
* @brief ȫ��ƥ��ṹ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
struct PanoMatchInfo
{
	//PanoMatchInfo(){}
	int nInIdxSrc;//�ڲ�src��ţ���0��N
	int nInIdxDst;//�ڲ�dst��ţ���0��N����ɾ��
	unsigned int nSrcImgIdx;//�ⲿsrc��ţ���λ����1001��NNNN
	unsigned int nDstImgIdx;//�ⲿdst��ţ���λ����1001��NNNN
	int nMatchPtNum;//ƥ������
	string sImgPathSrc;//srcͼ��·��
	string sImgPathDst;//dstͼ��·��
	vector<MatchPt> vecMatchPtsSrc;//srcƥ���ṹ����
	vector<MatchPt> vecMatchPtsDst;//dstƥ���ṹ����
	int nLoopID;//Ӱ��Ȧ��
	int nLoopImgID;//Ӱ�����
	vector<int> vecInIdxDst;//�뱾��ͼ��ƥ�������ͼ���ڲ���ţ���0��N��ȡ��nInIdxDst��

};

/**
* @fn PanoMatchSurf(vector<char*> &cParamList, vector<string> &cImageList, vector<double> &dExtParam, char* cOutputFile, vector<PanoMatchInfo> &vecPanoMatchInfo, bool &bNeedAddPts)
* @date 2012.1.21
* @author ����
* @brief ����ԭʼͼ�������ƥ����ļ�
* @param cParamList ȫ��ƴ�Ӳ���
* @param cImageList ԭʼͼ��·��
* @param dExtParam ԭʼͼ���ⷽλԪ��
* @param cOutputFile ���ƥ����ļ�·��
* @param vecPanoMatchInfo ������ƥ��ṹ
* @param bNeedAddPts �Ƿ���Ҫ�˹���ӵ�
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
PANOMOSAIC_API(bool) PanoMatchSurf(vector<char*> &cParamList, vector<string> &cImageList, vector<double> &dExtParam, char* cOutputFile, vector<PanoMatchInfo> &vecPanoMatchInfo, bool &bNeedAddPts);

PANOMOSAIC_API(bool) PanoMatchSift(vector<char*> &cParamList, vector<string> &cImageList, vector<double> &dExtParam, char* cOutputFile, vector<PanoMatchInfo> &vecPanoMatchInfo, bool &bNeedAddPts);

PANOMOSAIC_API( bool ) PanoMatchPoint(vector<char*> &cParamList, vector<string> &cImageList, vector<double> &dExtParam, char* cOutputFile, vector<PanoMatchInfo> &vecPanoMatchInfo, bool &bNeedAddPts);

/**
* @fn PanoMosaic(vector<char*> &cParamList, vector<string> &sImageList, vector<double> &dExtParam, vector<PanoMatchInfo> vecPanoMatchPts, char* cOutputFile)
* @date 2012.1.21
* @author ����
* @brief ȫ��ƴ�Ӻ���
* @param cParamList ȫ��ƴ�Ӳ���
* @param sImageList ԭʼͼ��·��
* @param dExtParam ԭʼͼ���ⷽλԪ��
* @param vecPanoMatchPts ԭʼͼ����ƥ��㣨��Ϊ�Ѿ�����������
* @param cOutputFile ���ȫ��ͼ��·��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
PANOMOSAIC_API(bool) PanoMosaic(vector<char*> &cParamList, vector<string> &sImageList, vector<double> &dExtParam, vector<PanoMatchInfo> vecPanoMatchPts, char* cOutputFile);

#endif // PANORAMA_H_INCLUDED


