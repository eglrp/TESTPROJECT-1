/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlTypes.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ml�����й�������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef _MLTYPES_H
#define _MLTYPES_H

#include "assert.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "float.h"
#include "math.h"
#include <string>
#include "string.h"
#include <vector>
using namespace std;

#if defined _WIN32|| defined _WIN64
#include "targetver.h"
#include <windows.h>

#define log2(d) ( log10(d) / log10(2.0) ) 

#endif 

#if(_MSC_VER >= 1400 && defined _M_X64) || (__GNUC__ >= 4 && defined __x86_64__)
#if defined WIN64
#include <intrin.h>
#endif
#include <emmintrin.h>  /*SSE2ָ�ͷ�ļ�*/
#endif


/*�����ƽ̨��ֲ�����嵼������*/
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
#define ML_CDECL __cdecl
#define ML_STDCALL __stdcall
#else
#define ML_CDECL
#define ML_STDCALL
#endif

#ifndef ML_EXTERN_C
#ifdef __cplusplus
#define ML_EXTERN_C extern "C"
#define ML_DEFAULT(val) = val
#else
#define ML_EXTERN_C
#define ML_DEFAULT(val)
#endif
#endif

#if ( defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64 ) && defined MLRVML_EXPORTS
#define ML_EXPORTS __declspec(dllexport)
#else
#define ML_EXPORTS
#endif

#ifndef MLAPI
#define MLAPI(rettype) ML_EXTERN_C ML_EXPORTS rettype ML_CDECL
#endif


typedef unsigned char                UCHAR; //!<�޷���8λ����
typedef char                            SCHAR;    //!<�з���8λ����
typedef unsigned short int          USHORT;  //!<�޷���16λ����
typedef signed short int            SSHORT;   //!<�з���16λ����

typedef unsigned int                 UINT;     //!<�޷���32λ����
typedef signed int                   SINT;      //!<�з���32λ����

#if !defined _WIN32 && !defined _WIN64
typedef unsigned long long int    ULONG;     //!<�޷���64λ����
#endif

typedef signed long long int       SLONG;     //!<�з���64λ����

typedef float                         FLOAT;     //!<32λ������
typedef double                        DOUBLE;    //!<64λ������

typedef UCHAR                           BYTE;   //!<�޷���8λ�ַ���

enum camModelType {Affine = 0 , NonAffine = 1} ;//!<�����������ģ�����
enum camProjection {backProjOff = 0 , backProjOn = 1} ;//!<��������궨ģʽ
enum delErrorType {delOff = 0 , delOn = 1} ;//!<�����Ƿ����ֲ��޳�ģʽ

#define BUFFER_RADIUS 2 //!>���建�����뾶


typedef enum enImgType
{
    /*! Unknown or unspecified type */ 		    T_Unknown = 0,
    /*! Eight bit unsigned integer */           T_Byte = 1,
    /*! Sixteen bit unsigned integer */         T_UInt16 = 2,
    /*! Sixteen bit signed integer */           T_Int16 = 3,
    /*! Thirty two bit unsigned integer */      T_UInt32 = 4,
    /*! Thirty two bit signed integer */        T_Int32 = 5,
    /*! Thirty two bit floating point */        T_Float32 = 6,
    /*! Sixty four bit floating point */        T_Float64 = 7,
    T_TypeCount = 12          /* maximum type # + 1 */
}ImgDotType;
/**
* @struct tagRECT
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���νṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagMLRECT
{
    DOUBLE    left;//!<���Ͻ�X����
    DOUBLE    top;//!<���Ͻ�Y����
    DOUBLE    right;//!<���½�X����
    DOUBLE    bottom;//!<���½�Y����
    tagMLRECT()
    {
        left = top = right = bottom = 0.0;
    }
} DbRect;
/**
* @struct tagmlRect
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �����๫���ṹ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagmlRect
{
    DOUBLE dXMin;//!<���Ͻ�X����
    DOUBLE dYMin;//!<���Ͻ�Y����
    DOUBLE dXMax;//!<���½�X����
    DOUBLE dYMax;//!<���½�Y����
    tagmlRect()
    {
        dXMin = dYMin = dXMax = dYMax = 0.0;
    }
} MLRect;
/*���幫������*/
#define ML_PI   3.1415926535897932384626433832795
#define ML_E    2.7182818284590452353602874713526
#define ML_LOG2 0.69314718055994530941723212145818
#define ML_DOUBLEMIN 1.0e-300
#define ML_ZERO 1.0e-7
#define ML_MoonRadius 1738000
/*���峣�ú���*/
#define ML_SWAP(a,b,t) ( (t) = (a), (a) = (b), (b) = (t) )

#ifndef MIN
#define MIN(a,b) ( (a) > (b) ? (b) : (a) )
#endif

#ifndef MAX
#define MAX(a,b) ( (a) < (b) ? (b) : (a) )
#endif

#ifndef UINT_MAX
#define UINT_MAX 4294967295
#endif

#ifndef DOUBLE_MAX
#define DOUBLE_MAX 1.0e308
#endif

#ifndef DOUBLE_MIN
#define DOUBLE_MIN -1.0e308
#endif

#define RGB2GRAY( r,g,b ) (((b)*117 + (g)*601 + (r)*306 ) >> 10 )

/**
* @brief �Ƕ�ת����
*/
#define Deg2Rad(d) ( d / 180.0 * ML_PI ) //!<�Ƕ�ת����

/**
* @brief ����ת�Ƕ�
*/
#define Rad2Deg(d) ( d * 180.0 / ML_PI ) //!<����ת�Ƕ�

/*****************************************************************
�������ƣ�ͼ����Ϣ�����ṹ���������ⷽλԪ��
��    �ߣ����Ļ�
��������������ͼ��������½�Ϊԭ�㣬����Ϊx������Ϊy���ⷽλԪ�ؽ�Ԫ�ص�λΪ����
��    �룺
��    ����
�汾���:   1.0
�޸���ʷ:    <����>    <ʱ��>   <�汾���>    <����>
******************************************************************/
/**
* @struct OriAngle
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ⷽλ��Ԫ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
struct OriAngle
{
    DOUBLE omg;//!<��X��ת��
    DOUBLE phi;//!<��Y��ת��
    DOUBLE kap;//!<��Z��ת��
    OriAngle()
    {
        omg = phi = kap = 0.0;
    }
};

/**
* @struct PT2
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��ά��ṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
template <typename T>
struct PT2
{
    T X, Y;//!<��X,Y����
    ULONG lID;//!<�����
    BYTE byType;
    BYTE byIsMatch;
    PT2()
    {
        memset(this, 0, 2*sizeof(T));
        lID = 0;
        byType = 0;
        byIsMatch = 0;
    }
};
/**
* @struct PT3
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��ά��ṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
template <typename T>
struct PT3
{
    T X, Y, Z;//!<��X,Y,Z����
    ULONG lID;//!<�����

    PT3()
    {
        memset(this, 0, 3*sizeof(T));
        lID = 0;
    }
};

typedef PT2<DOUBLE> Pt2d;//!<��άDOUBLE�ͽṹ��
typedef PT2<FLOAT> Pt2f;//!<��άFLOAT�ͽṹ��
typedef PT2<SLONG> Pt2l;//!<��άSLONG�ͽṹ��
typedef PT2<SINT> Pt2i;//!<��άSINT�ͽṹ��

typedef PT3<BYTE>  Pt3b;//!<��άBYTE�ͽṹ��
typedef PT3<FLOAT> Pt3f;//!<��άFLOAT�ͽṹ��
typedef PT3<DOUBLE> Pt3d;//!<��άFLOAT�ͽṹ��




/**
* @struct struExteriorOrientation
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ⷽλԪ�ؽṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct struExteriorOrientation
{
    Pt3d pos;//!<�ⷽλ��Ԫ��
    OriAngle ori;//!<�ⷽλ��Ԫ��
} ExOriPara;
/**
* @struct enCamType
* @date 2011.11.02
* @author �⿭ wukai@irsa.ac.cn
* @brief �������
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef enum enCamType
{
    NULL_Cam = 0,//!<������
    Pan_Cam = 1, //!<ȫ�����
    Nav_Cam = 2, //!<�������
    Haz_Cam = 3  //!<�������

} CAMTYPE;
/**
* @struct struSINTeriorOrientation
* @date 2011.11.02
* @author �⿭ wukai@irsa.ac.cn
* @brief ����ڲ���
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/


typedef struct struSINTeriorOrientation
{
    DOUBLE f;//!<����
    DOUBLE f2;//!<����
    DOUBLE x;//!<����������x
    DOUBLE y;//!<����������y
    DOUBLE k1;//!<�������ϵ��k1
    DOUBLE k2;//!<�������ϵ��k2
    DOUBLE k3;//!<�������ϵ��k3
    DOUBLE p1;//!<�������ϵ��p1
    DOUBLE p2;//!<�������ϵ��p2
    DOUBLE alpha;//!<��������ϵ��alpha
    DOUBLE beta;//!<��������ϵ��beta
    DOUBLE dPixelS;//!<���ش�С����λΪ����
    UINT   nType;//!<����ģ�����ͣ����У�1��ʾΪ��ͨ�Ļ���ģ�ͣ���������估������䣬��ģ��������λ�þ�������Ϊ��λ
    DOUBLE dSkew;
    CAMTYPE camType;//!<�������
    struSINTeriorOrientation()
    {
        f = x = y = k1 = k2 = k3 = p1 = p2 = alpha = beta = dSkew = 0.0;
        dPixelS = 1.0;
        nType = 1;
    }

} InOriPara;


/**
* @struct tagStruFrameImageInfo
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief  ����Ӱ����Ϣ�ṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagStruFrameImageInfo
{
    SINT nSiteID;//!<վ�����
    SINT nRollID;//!<Ӱ��Ȧ��
    SINT nImgID;//!<Ӱ�����
    UINT nCamID;//!<�������
    UINT nW;//!<Ӱ���
    UINT nH;//!<Ӱ���
    string strName;//!<Ӱ����
    string strImgPath;//!<Ӱ��·��
    InOriPara inOri;//!<Ӱ���ڷ�λ
    ExOriPara exOri;//!<Ӱ���ⷽλ
    UINT nImgType; //!<Ӱ�����ͣ�1ΪԭʼӰ��2Ϊ����У��Ӱ��
    UINT nImgIndex;
    tagStruFrameImageInfo()
    {
        nSiteID = -1;
        nRollID = -1;
        nCamID = 0;
        nImgID = -1;
        strImgPath = "";
        nImgType = 0;
        nImgIndex = 0;
        nW = nH = 0;
    }

} FrameImgInfo;

/**
* @struct tagStruStereoImageInfo
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ����Ϣ�ṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagStruStereoImageInfo
{
    SINT nSiteID;//!<վ�����
    SINT nRollID;//!<Ӱ��Ȧ��
    SINT nImgID;//!<Ӱ�����
    UINT nCamID;//!<�������

    FrameImgInfo imgLInfo;
    FrameImgInfo imgRInfo;
    SINT nStereoLevel;
    tagStruStereoImageInfo()
    {
        nSiteID = -1;
        nRollID = -1;
        nImgID = -1;
        nStereoLevel = 0;//!<��ʾӰ�����ͣ�1ΪԭʼӰ��2Ϊ����Ӱ���
    }
} StereoSet;
/**
* @struct tagImgPtSe
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����Ӱ���ƥ���ṹ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagImgPtSet
{
    FrameImgInfo imgInfo;
    vector< Pt2d > vecPts;
    vector< Pt2d > vecAddPts;
} ImgPtSet;

/**
* @struct struStereoMatch
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ƥ���ṹ
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct struStereoMatch: public Pt3d
{
    //����ά��ṹ��������������Ӱ��㣬��Ӱ��㣨���ߵ�ṹ��
    Pt2d ptLInImg;//!<��Ӱ�������
    Pt2d ptRInImg;//!<��Ӱ�������
    DOUBLE dRelaCoef;//!<ƥ��ϵ��
    struStereoMatch()
    {
        dRelaCoef = 0.0;
    }
} StereoMatchPt;

/**
* @struct ObstacleMapPara
* @date 2011.12.18
* @author ��Ρ
* @brief �����ϰ��ֲ�ͼ��������ṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
struct ObstacleMapPara
{
    DOUBLE dSlopeCoef;    //!<�¶ȶ��ϰ�ͼ��ϵ��
    DOUBLE dMaxSlope;    //!<����¶�����
    // dSlopCoef * SlopeValue / dMaxSlope Ϊ�ϰ����ۺ�������ֵ����������
    DOUBLE dRoughnessCoef;    //!<�ֲڶ�ϵ��
    DOUBLE dMaxRoughness;    //!<���ֲڶ�����
    DOUBLE dStepCoef;    //!<����ϵ��
    DOUBLE dMaxStep;    //!<������ϵ��
    DOUBLE dMaxObstacleValue;    //!<����ϰ���������
    //�ϰ����ۺ���������ֵ����֮Ϊ�ϰ�
};


/**
* @struct struLineEo
* @date 2011.11.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ��ԭʼ���������Ԫ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct struLineEo
{
    DOUBLE dEoTime;//!<�ⷽλԪ��ʱ��
    Pt3d pos;//!<�ⷽλ��Ԫ��
} LineEo;

/**
* @struct tagCE1IOPara
* @date 2011.11.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ��ԭʼ������ݽ�Ԫ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct struAngleEo
{
    DOUBLE dEoTime;//!<�ⷽλԪ��ʱ��
    OriAngle ori;//!<�ⷽλ��Ԫ��
} AngleEo;

/**
* @struct tagCE1IOPara
* @date 2011.11.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CE-1����Ӱ���ڶ������
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagCE1IOPara
{
    DOUBLE f;//!<����
    DOUBLE s0;//!<��Ӱ�����к�
    DOUBLE l0;//!<��Ӱ�����к�
    DOUBLE pixsize;//!<���ش�С���ף�
    DOUBLE x0;//!<��ƽ��x���꣨�ף�
    DOUBLE y0;//!<��ƽ��y���꣨�ף�
    UINT nCCD_line;//!<ǰ�ӡ����ӻ����Ӱ�����ʱ���õ�CCD��
    bool upflag;//!<�����б�־������Ϊtrue������Ϊflase
    UINT nSample;//!<Ӱ���
    UINT nLine;//!<Ӱ���

    tagCE1IOPara()
    {
        x0 = 0.0000113;
        y0 = -0.0000112;
        s0 = 255.5;
        l0 = 511.5;
        pixsize = 0.000014;
        f = 0.023334;
        nSample = 512;
    }
} CE1IOPara;
/**
* @struct tagCE2IOPara
* @date 2011.11.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CE-2����Ӱ���ڶ������
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagCE2IOPara
{
    DOUBLE f;//!<����
    DOUBLE s0;//!<��Ӱ���ĵ��к�
    DOUBLE pixsize;//!<���ش�С���ף�
    DOUBLE x0;//!<��ƽ��x���꣨�ף�
    DOUBLE y0;//!<��ƽ��y���꣨�ף�
    DOUBLE AngleDeg;//!<ǰ�ӻ�������������ļн�(�Ƕ�)
    bool upflag;//!<Ӱ��������б�־������Ϊtrue������Ϊfalse
    UINT nSample;//!<Ӱ���
    UINT nLine;//!<Ӱ���
    tagCE2IOPara()
    {
        AngleDeg = 0;
        s0 = 3071.5;
        x0 = 0.0000093;
        y0 = 0.0000000;
        pixsize = 0.0000101;
        f = 0.1443;
        nSample = 6144;
    }
} CE2IOPara;
/**
* @struct tagStruSatProj
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ��DEM��DOM���ɹ��̲���
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagStruSatProj
{
    string sLimgPath;//!<��Ӱ��·��
    string sRimgPath;//!<��Ӱ��·��
    CE1IOPara CE1LimgIO;//!<CE-1������Ӱ���ڶ������
    CE1IOPara CE1RimgIO;//!<CE-1������Ӱ���ڶ������
    CE2IOPara CE2LimgIO;//!<CE-2������Ӱ���ڶ������
    CE2IOPara CE2RimgIO;//!<CE-2������Ӱ���ڶ������
    vector<ExOriPara> LimgEo;//!<��Ӱ���ⷽλԪ��
    vector<ExOriPara> RimgEo;//!<��Ӱ���ⷽλԪ��
    string sDemPath;//!<DEM����·��
    string sDomPath;//!<DEM����·��
    //vector<StereoMatchPtt> vecPts;//!<ƥ��㼰�﷽����
    vector<Pt3d> XYZRms;//!<�﷽���꾫��
} SatProj;

/**
* @struct tagBlockOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ��ֿ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagBlockOptions
{
    UINT nColThres;//!<Ӱ���з���ֿ��С��ֵ
    UINT nRowThres;//!<Ӱ���з���ֿ��С��ֵ
    UINT nOverlayW;//!<Ӱ���з����ص�����С
    UINT nOverlayH;//!<Ӱ���з����ص�����С
    UINT nBlockWidth;//!<Ӱ���ʼ�ֿ��
    UINT nBlockHeight;//!<Ӱ���ʼ�ֿ��
    tagBlockOptions()
    {
        nColThres = 2000;
        nRowThres = 2000;
        nOverlayW = 200;
        nOverlayH = 200;
        nBlockWidth = 512;
        nBlockHeight = 512;
    }

} BlockOptions;

/**
* @struct tagSatOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ����ͼ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagSatOptions
{
    string sMissionName;//!<��������
    UINT nMaxCheck;//!<Siftƥ������������
    DOUBLE dRatio;//!<Siftƥ�����
    DOUBLE dSigma;//!<Ransac����任�㷨�޲�
    UINT nMinItera;//!<Ransac����任�㷨��С��������
    DOUBLE dThresh;//!<Ransac��Ӧ�����㷨��ֵ
    DOUBLE dConfidence;//!<Ransac��Ӧ�����㷨���Ŷ�
    UINT nStep;//!<�ܼ�ƥ�䲽��
    SINT nRadiusX;//!<�ܼ�ƥ�䷶ΧX����뾶��С
    SINT nRadiusY;//!<�ܼ�ƥ�䷶ΧY����뾶��С
    SINT nTemplateSize;//!<�ܼ�ƥ��ģ���С
    DOUBLE dCoef;//!< ���ϵ����ֵ
    SINT nXOffSet;//!<�ܼ�ƥ��X����ƫ����
    SINT nYOffSet;//!<�ܼ�ƥ��Y����ƫ����
    UINT nBands;//!<Ӱ�񲨶���
    DOUBLE nodata;//!<DEM��DOM����������ֵ
    BlockOptions BlockOps;//!<Ӱ��ֿ����
    DOUBLE XResolution;//!<DEM��DOM��X����ֱ���
    DOUBLE YResolution;//!<DEM��DOM��Y����ֱ���
    bool bLeftBaseFlag;//!<DOM���ɲ���ͼ��
    DOUBLE B0;//!<ͶӰ���
    tagSatOptions()
    {
        nMaxCheck = 200;
        dRatio = 0.5;
        dSigma = 5.5;
        nMinItera = 2000;
        dThresh = 1.0;
        dConfidence = 0.99;
        nStep = 5;
        nRadiusX = nRadiusY = 5;
        nTemplateSize = 5;
        dCoef = 0.75;
        nXOffSet = nYOffSet = 0;
        nBands = 1;
        nodata = 999999;
        XResolution = 150;
        YResolution = 150;
        bLeftBaseFlag = true;
        B0 = 35;
    }
} SatOptions;

/**
* @struct tagSiftMatchParaOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief Siftƥ�����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagSiftMatchParaOptions
{
    UINT nMaxCheck;//!<Siftƥ������������
    DOUBLE dRatio;//!<Siftƥ�����
    tagSiftMatchParaOptions()
    {
        nMaxCheck = 200;
        dRatio = 0.5;
    }
} SiftMatchPara;
/**
* @struct tagASiftMatchParaOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief Siftƥ�����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagASiftMatchParaOptions
{
    SINT  nNumTilts ;//!<ASiftƥ�����任�Ƕȱ任����
    tagASiftMatchParaOptions()
    {
        nNumTilts = 8;
    }
} ASiftMatchPara;
/**
* @struct tagRanSACAffineParaOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief RANSAC������任ģ�ͣ�����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagRanSACAffineParaOptions
{
    DOUBLE dSigma;//!<RANSAC��ֵ
    DOUBLE dMinItera;//!<RANSAC��С��������
    tagRanSACAffineParaOptions()
    {
        dSigma = 1.0;
        dMinItera = 1000;
    }
} RANSACAffineModPara;
/**
* @struct tagRanSACHomeParaOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief RANSAC����Ӧ����ģ�ͣ�����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagRanSACHomeParaOptions
{
    DOUBLE dConfidence;//!<RANSAC���ŶȲ���
    DOUBLE dThres;//!<RANSAC��ֵ
    tagRanSACHomeParaOptions()
    {
        dConfidence = 0.99;
        dThres = 3;
    }
} RANSACHomePara;
/**
* @struct tagLocalByMatchOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����ƥ��Ķ�λ�㷨����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagLocalByMatchOptions
{
    SiftMatchPara stuSiftPara;//!<Siftƥ�����
    RANSACAffineModPara stuRANSACPara;//!<RANSAC����
} LocalByMatchOpts;

/**
* @struct tagMatchInRegPara
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����ģ��ƥ�����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagMatchInRegPara
{
    DOUBLE dXMin;//!<X����������С�Ӳ�
    DOUBLE dYMin;//!<Y������������Ӳ�
    DOUBLE dXMax;//!<X����������С�Ӳ�
    DOUBLE dYMax;//!<Y������������Ӳ�
    DOUBLE dXOff;//!<X��������ƫ��ֵ
    DOUBLE dYOff;//!<X��������ƫ��ֵ
    UINT nTempSize;//!<ģ���С
    DOUBLE dCoefThres;//!<���ϵ����ֵ

    tagMatchInRegPara()
    {
        dXMin = -200.0;
        dXMax = 0.0;
        dYMin = -2;
        dYMax = 2;
        dXOff = dYOff = 0.0;
        nTempSize = 15;
        dCoefThres = 0.75;
    }
} MatchInRegPara;
/**
* @struct tagLocalBy2SitesOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ����ͼ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagLocalBy2SitesOptions
{
    DOUBLE dCamH;//!<����߶�
    ASiftMatchPara stuASiftPara;//!<ASiftƥ�����
    DOUBLE dFSiteDis;//!<ǰվ�������
    DOUBLE dESiteDis;//!<��վ�������
    MatchInRegPara stuMatchPara;//!<����ƥ�����
    tagLocalBy2SitesOptions()
    {
        dCamH = 1.5;
        dFSiteDis = 12.0;
        dESiteDis = 4.0;
    }
}
LocalBy2SitesOpts;

/**
* @struct tagLocalBySequenceImgOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ����ͼ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagLocalBySequenceImgOptions
{
    DOUBLE dZoomCoef;//!<����ƥ�������ϵ��
    SiftMatchPara stuSiftPara;//!<Siftƥ�����
    RANSACAffineModPara stuRANSACPara;//!<Ransac����
}
LocalBySeqImgOpts;
/**
* @struct tagLocalBySequenceImgOptions
* @date 2011.12.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����Ӱ����ͼ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagLocalByLanderOpts
{
    MatchInRegPara stuMatchPara;//!<����ƥ�����
    SiftMatchPara stuASiftPara;//!<ASiftƥ�����
    RANSACAffineModPara stuRANSACPara;//!<RANSAC�ֲ��޳�����
}
LocalByLanderOpts;

/**
* @struct tagBaseOptions
* @date 2011.12.18
* @author �틠
* @brief �����߷�������
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagBaseOptions
{
    DOUBLE dFixBase;//!<ȫ������̶����߳�
    DOUBLE dPixel;//!<����ƥ�����
    DOUBLE dTarget;//!<Ŀ�����
    UINT nWidth;//!<ȫ�����������
    DOUBLE dThresHold;//!<ţ�ٵ�������ֵ
    UINT nIterTime;//!<ţ�ٵ�������������
    tagBaseOptions()
    {
        dThresHold=0.000001;
        nIterTime=60;
    }
} BaseOptions;


/**
* @struct tagWideOptions
* @date 2011.12.18
* @author �틠
* @brief ������Ӱ����ͼ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct  tagWideOptions
{
    UINT nMaxCheck;//!<Siftƥ������������
    DOUBLE dRatio;//!<Siftƥ�����
    DOUBLE dThresh;//!<Ransac�㷨��ֵ
    DOUBLE dConfidence;//!<Ransac�㷨���Ŷȶ�
    SINT nStep;//!<�ܼ�ƥ�������С
    SINT nRadiusX;//!<�ܼ�ƥ�䷶ΧX����뾶��С
    SINT nRadiusY;//!<�ܼ�ƥ�䷶ΧY����뾶��С
    SINT nTemplateSize;//!<�ܼ�ƥ��ģ���С
    DOUBLE dCoef;//!< ���ϵ����ֵ
    bool bIsUsingFeatPt;//!< ʹ����������ܼ������ɵ���
    bool bIsUsingPartion;//!< ����������DEM����������������������DEM
    SINT nXOffSet;//!<�ܼ�ƥ��X����ƫ����
    SINT nYOffSet;//!<�ܼ�ƥ��Y����ƫ����
    UINT nBands;//!<Ӱ�񲨶���
    DOUBLE nodata;//!<DEM��DOM����������ֵ
    DOUBLE XResolution;//!<DEM��DOM��X����ֱ���
    DOUBLE YResolution;//!<DEM��DOM��Y����ֱ���
    tagWideOptions()
    {
        nMaxCheck = 200;
        dRatio = 0.6;
        dThresh = 0.05;
        dConfidence = 0.99;
        nStep = 5;
        nRadiusX = 5;
        nRadiusY = 2;
        nTemplateSize = 13;
        dCoef = 0;
        bIsUsingFeatPt = false;
        bIsUsingPartion = false;
        nXOffSet = nYOffSet = 0;
        nBands = 1;
        nodata = 999999;
        XResolution = 0.1;
        YResolution = 0.1;
    }
} WideOptions;


/**
* @struct tagTransMat
* @date 2011.12.18
* @author ������ zhangchy@irsa.ac.cn
* @brief ����ת����ϵ���� ������ת�����ƽ������
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagTransMat
{

    SINT nDim;         //!<����ת��ά�� Ĭ��Ϊ3 ���������ֵ��
    DOUBLE dMat[9];   //!<��ת����3*3  ��������
    DOUBLE dVec[3];   //!<ƽ������
    tagTransMat()
    {
        nDim = 3;
        dMat[0] = 0.0;
        dMat[1] = 0.0;
        dMat[2] = 0.0;
        dMat[3] = 0.0;
        dMat[4] = 0.0;
        dMat[5] = 0.0;
        dMat[6] = 0.0;
        dMat[7] = 0.0;
        dMat[8] = 0.0;

        dVec[0] = 0.0;
        dVec[1] = 0.0;
        dVec[2] = 0.0;
    }


} TransMat;

/**
* @struct tagExtractFeature
* @date 2011.12.18
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��������ȡ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagExtractFeature
{
    SINT nGridSize;//!<��������ȡʱӰ�񻮷ָ�����С
    SINT nPtMaxNum;//!<��������ȡ�������Ŀ
    DOUBLE dThresCoef;
    tagExtractFeature()
    {
        nGridSize = 10;
        nPtMaxNum = 0;
        dThresCoef = 1.0;
    }
} ExtractFeatureOpt;


typedef struct tagGaussianFilter
{
    SINT nTemplateSize;//!<�˲�ģ���С
    DOUBLE dCoef;//!<�˲��˲���
    tagGaussianFilter()
    {
        nTemplateSize = 7;
        dCoef = 0.8;
    }
} GaussianFilterOpt;

typedef struct tagmlRectSearch
{
    DOUBLE dXMin;//!<���Ͻ�X����
    DOUBLE dYMin;//!<���Ͻ�Y����
    DOUBLE dXMax;//!<���½�X����
    DOUBLE dYMax;//!<���½�Y����
    tagmlRectSearch()
    {
        dXMin = dYMin = dXMax = dYMax = 0.0;
    }
} MLRectSearch;

/**
* @struct RMS2d
* @date 2011.12.18
* @author ���Ļ� whwan@irsa.ac.cn
* @brief 2ά�����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
typedef struct tagStu2dRMS
{
    ULONG lID;
    DOUBLE rmsX;
    DOUBLE rmsY;
    DOUBLE rmsAll;
    tagStu2dRMS()
    {
        lID = 0;//!<���
        rmsX = 0;//!<��X�������
        rmsY = 0;//!<��Y�������
        rmsAll = 0;//!<�������
    }
} RMS2d;

typedef struct tagFilterPara
{
    UINT nFilterSize;
    DOUBLE dThresCoef;
    SINT nThres;
    tagFilterPara()
    {
        nFilterSize = 5;
        dThresCoef = 0.1;
        nThres = 5;
    }
}MedFilterOpts;
typedef struct tagWallisFilterPara
{
    UINT nTemplateSize;
    DOUBLE dExpectMean;
    DOUBLE dExpectVar;
    DOUBLE dCoefA;
    DOUBLE dCoefAlpha;
    tagWallisFilterPara()
    {
        nTemplateSize = 43;
        dExpectMean = 128;
        dExpectVar = 200;
        dCoefA = 60;
        dCoefAlpha = 0.4;
    }
}WallisFPara;

typedef struct tagInstallMatrix
{
    DOUBLE dOriMatrix[9];
    DOUBLE dPosMatrix[3];
    tagInstallMatrix()
    {
        for(UINT i = 0; i < 3; ++i )
        {
            dPosMatrix[i] = 0;
            dOriMatrix[3*i] = 0;
            dOriMatrix[3*i+1] = 0;
            dOriMatrix[3*i+2] = 0;
        }
    }
}stuInsMat;


typedef struct stuPolygon2d
{
    ULONG nID;
    vector<Pt2d> vecVectex;
}Polygon2d;

typedef struct stuPolygon3d
{
    ULONG nID;
    vector<Pt3d> vecVectex;
}Polygon3d;
typedef struct stuBlockDeal
{
    UINT nBlockH;
    vector<UINT> vecnDisp;
}stuBlockDeal;





#endif


























