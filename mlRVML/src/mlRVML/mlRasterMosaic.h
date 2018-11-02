/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlRasterMosaic.h
* @date 2011.11.18
* @author ���� liangjian@irsa.ac.cn
* @brief ��ƴ��ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/

#ifndef CMLRASTERMOSAIC_H
#define CMLRASTERMOSAIC_H

#include "mlGdalDataset.h"
#include "gdal_header.h"
#include "gdal/gdal_priv.h"
#include "gdal/gdal.h"
#include "gdal/gdalwarper.h"
#include "gdal/ogr_spatialref.h"
#include "gdal/ogr_api.h"
#include "gdal/cpl_string.h"
//#include "opencv.hpp"
#include "Panorama.h"

/**
* @class CmlRasterMosaic
* @date 2011.11.18
* @author ���� liangjian@irsa.ac.cn
* @brief ��ƴ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlRasterMosaic
{

public:

    vector<string> files;
    string out_file;
    int bTargetAlignedPixels;
    int nForcePixels, nForceLines, bQuiet;
    int bEnableDstAlpha, bEnableSrcAlpha;
    int bVRT;
    int bCreateOutput;
    int i;
    int bHasGotErr;
    int bCropToCutline;
    int bOverwrite;
    int bMulti;

    const char *cFormat;
    char **cInputFiles;
    char *cOutputFile;

    void *hTransformArg, *hGenImgProjArg, *hApproxArg;
    char **cWarpOptions;
    double dErrorThreshold;
    double dWarpMemoryLimit;
    double m_dMinX, m_dMinY, m_dMaxX, m_dMaxY;
    double m_dXRes, m_dYRes;
    char **cCreateOptions;

    const char *cSrcNodata;
    const char *cDstNodata;

    char **cTO;
    char *pszCutlineDSName;
    char *cCLayer, *pszCWHERE, *pszCSQL;
    void *hCutline;
    GDALDataType eOutputType, eWorkingType;
    GDALResampleAlg eResampleAlg;
    GDALTransformerFunc pfnTransformer;
    GDALDatasetH hDstDS;


public:

    /**
    * @fn CmlRasterMosaic
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ƴ�ӹ��캯��
    * @param inputFiles �����ļ�·��
    * @param outputFile ����ļ�·��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    CmlRasterMosaic(vector<string> inputFiles, string outputFile)
    {
        files = inputFiles;
        out_file = outputFile;
    }

    /**
    * @fn CmlRasterMosaic
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ƴ�ӿղι��캯��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    CmlRasterMosaic()
    {
    }

    /**
    * @fn ~CmlRasterMosaic
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ƴ����������
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    virtual ~CmlRasterMosaic()
    {

    }

    /**
    * @fn mlDEMMosaic
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief DEMƴ�Ӻ��������������ļ��ĵ�����Ϣ
    * @param cInputFiles ����DEM
    * @param cOutputFile ���DEM
    * @param dXRes X����ֱ���
    * @param dYRes Y����ֱ���
    * @param nResample  ����������Ӧ��ֵ
    * @param nDisCultLine  ������ֵ
    * @retval 1 �ɹ�
    * @retval 0 ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    int mlDEMMosaic(vector<string> cInputFiles, const SCHAR* cOutputFile, DOUBLE dXRes, DOUBLE dYRes, SINT nResample, SINT nDisCultLine);


private:

    /**
    * @fn mlInitCoordSys
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ��ʼ������DEM����
    * @param cInputCoordSys ��������ϵͳ
    * @return ����ϵͳ��ʶ
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    char *mlInitCoordSys( const char *cInputCoordSys );

    /**
    * @fn mlCreateOutputFile
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ��������ļ�
    * @param cSrcFiles ����Դ�ļ�
    * @param cFilename ����ļ�
    * @param cFormat ���ͼ���ʽ
    * @param papszTO ����ļ�����ϵ
    * @param cCreateOptions ����ͼ��ѡ��
    * @param eDT ����ÿ�����ص��ֽ�
    * @param nInputFileNum �����ļ�����
    * @retval GDALDatasetH ����
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    GDALDatasetH mlCreateOutputFile(char **cSrcFiles, const char *cFilename, const char *cFormat, char **papszTO, char ***cCreateOptions, GDALDataType eDT, int nInputFileNum);


    void LoadCutline( const char *pszCutlineDSName, const char *pszCLayer, const char *pszCWHERE, const char *pszCSQL, void **phCutlineRet );


    void TransformCutlineToSource( GDALDatasetH hSrcDS, void *hCutline, char ***ppapszWarpOptions, char **papszTO_In );
    //bool mlDeSeam();
};

/**
* @struct GeoTransformStruct
* @date 2011.11.18
* @author ���� liangjian@irsa.ac.cn
* @brief ����任����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
struct GeoTransformStruct
{
    char* cFileName;//!<�����ļ���
    int nID;//!<����DEM��ID
    double dTopLeftX;//!<���Ͻ�X����
    double dTopLeftY;//!<���Ͻ�Y����
    double dXRes;//!<X����ֱ���
    double dYRes;//!<Y����ֱ���
    int nXSize;//!<ԭʼ����
    int nYSize;//!<ԭʼ���
    double dLowRightX;//!<���½�X����
    double dLowRightY;//!<���½�X����
};

/**
* @struct OverlapStruct
* @date 2011.11.18
* @author ���� liangjian@irsa.ac.cn
* @brief �ص������η�Χ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
struct OverlapStruct
{
    pair<int, int> pirID;//!<���ID��
    double dTopLeftX;//!<���Ͻ�X����
    double dTopLeftY;//!<���Ͻ�Y����
    double dLowRightX;//!<���½�X����
    double dLowRightY;//!<���½�X����
};


/**
* @class CmlInvCyilindricalProject
* @date 2011.11.18
* @author ���� liangjian@irsa.ac.cn
* @brief ��Բ��ͶӰ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlInvCyilindricalProject
{
public:
    cv::Size size;
    double focal;
    double r[9];
    double rinv[9];
    double scale;
public:
    /**
    * @fn mlSetTransformation
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ͸�ӱ任
    * @param ͸�ӱ任����
    * @retval ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    void mlSetTransformation(const cv::Mat& R);

    /**
    * @fn mlMapForward
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ����Բ��ͶӰ
    * @param x ͶӰǰX����
    * @param y ͶӰǰY����
    * @param u ͶӰ��X����
    * @param v ͶӰ��Y����
    * @retval ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    void mlMapForward(double x, double y, double &u, double &v)
    {
        x -= size.width * 0.5f;
        y -= size.height * 0.5f;

        float x_ = r[0] * x + r[1] * y + r[2] * focal;
        float y_ = r[3] * x + r[4] * y + r[5] * focal;
        float z_ = r[6] * x + r[7] * y + r[8] * focal;

        u = scale * atan2f(x_, z_);
        v = scale * y_ / sqrtf(x_ * x_ + z_ * z_);
    }

    /**
    * @fn mlMapBackward
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ����Բ��ͶӰ
    * @param u ����ͶӰǰX����
    * @param v ����ͶӰǰY����
    * @param x ����ͶӰ��X����
    * @param y ����ͶӰ��Y����
    * @retval ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    void mlMapBackward(double u, double v, double &x, double &y)
    {
        float x_ = sinf(u / scale);
        float y_ = v / scale;
        float z_ = cosf(u / scale);

        float z;
        x = rinv[0] * x_ + rinv[1] * y_ + rinv[2] * z_;
        y = rinv[3] * x_ + rinv[4] * y_ + rinv[5] * z_;
        z = rinv[6] * x_ + rinv[7] * y_ + rinv[8] * z_;

        x = focal * x / z + size.width * 0.5f;
        y = focal * y / z + size.height * 0.5f;
    }
};


/**
* @class CmlPano2Prespective
* @date 2011.11.18
* @author ���� liangjian@irsa.ac.cn
* @brief ȫ��Ӱ������͸��Ӱ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlPano2Prespective
{
public:
    /**
    * @fn CmlPano2Prespective
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ȫ��Ӱ������͸��Ӱ���캯��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    CmlPano2Prespective()
    {

    }

    /**
    * @fn ~CmlPano2Prespective
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ȫ��Ӱ������͸��Ӱ���캯��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    virtual ~CmlPano2Prespective()
    {

    }

public:
    int m_nPanoW;
    int m_nPanoH;
    cv::Size src_size_;
    CmlInvCyilindricalProject projector_;
public:
    /**
    * @fn mlPano2Prespective
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ����Բ��ͶӰ
    * @param cInputPanoFile ����ȫ��ͼ��
    * @param cOutputImage ���͸��ͼ��
    * @param ptOriginal ȫ��ͼ���д�����͸��ͼ������Ͻ�����
    * @param nPanoW ȫ��ͼ��Ŀ��
    * @param nPanoH ȫ��ͼ��ĸ߶�
    * @param dFocus �������
    * @retval ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlPano2Prespective( const SCHAR *cInputPanoFile, const SCHAR * cOutputImage, Pt2i ptOriginal, SINT nPanoW, SINT nPanoH, DOUBLE dFocus);

};

/**
* @struct struImageFeatures
* @date 2011.01.18
* @author ���� liangjian@irsa.ac.cn
* @brief ȫ��ƴ�ӿⶨ���������ṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
//struct ImageFeatures
//{
//    int img_idx;
//    cv::Size img_size;
//    std::vector<cv::KeyPoint> keypoints;
//    cv::Mat descriptors;
//};

/**
* @struct struMatchesInfo
* @date 2011.01.18
* @author ���� liangjian@irsa.ac.cn
* @brief ȫ��ƴ�ӿⶨ���������ṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
//struct MatchesInfo
//{
//    MatchesInfo();
//    MatchesInfo(const MatchesInfo &other);
//    const MatchesInfo& operator =(const MatchesInfo &other);
//
//    int src_img_idx, dst_img_idx;       // Images indices (optional)
//    std::vector<cv::DMatch> matches;
//    std::vector<uchar> inliers_mask;    // Geometrically consistent matches mask
//    int num_inliers;                    // Number of geometrically consistent matches
//    cv::Mat H;                          // Estimated homography
//    double confidence;                  // Confidence two images are from the same panorama
//
//    std::vector<cv::KeyPoint> vecSrcPt;  // src_img_idxͼ���ϵ�ƥ���
//
//};


/**
* @class CmlPanoInterface
* @date 2011.01.18
* @author ���� liangjian@irsa.ac.cn
* @brief ��ȫ��ƴ�ӿ�Ľӿ�ת����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlPanoInterface
{
public:
    //bool mlFirstRun(vector<char*> &cParamList, vector<ImgPtSet> &vecOriImage, vector<double> &dExtParam, char* cOutputFile, vector<PanoMatchInfo> &vecPanoMatchInfo);
    /**
    * @fn mlExportMatchPts
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief �������ͼ����ƥ���
    * @param vecParam ����ȫ��ͼ��Ĳ���
    * @param vecFrmInfo ԭʼͼ����Ϣ
    * @param vecImgPtSets �������Ϣ
    * @param strOutPath ������ļ�·��
    * @retval ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlExportMatchPts(vector<char*> vecParam, vector<FrameImgInfo> vecFrmInfo, vector<ImgPtSet> &vecImgPtSets, char* strOutPath, bool &bNeedAddPts);

    /**
    * @fn mlImportMatchPts
    * @date 2011.11.22
    * @author ���� liangjian@irsa.ac.cn
    * @brief ��������ͼ����ƥ���
    * @param vecParam ����ȫ��ͼ��Ĳ���
    * @param vecFrmInfo ԭʼͼ����Ϣ
    * @param vecImgPtSets �������Ϣ
    * @param strOutPath ����ȫ��ͼ��·��
    * @retval ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool mlImportMatchPts(vector<char*> vecParam, vector<FrameImgInfo> vecFrmInfo, vector<ImgPtSet> &vecImgPtSets, char* strOutPath);

public:
    CmlPanoInterface()
    {
    }
    virtual ~CmlPanoInterface()
    {
    }

private:
    bool mlLoadPrjFile(string sPrjPath);



};

////class DjSets
////{
////public:
////    DjSets(int n = 0)
////    {
////        create(n);
////    }
////
////    void create(int n);
////    int find(int elem);
////    int merge(int set1, int set2);
////
////    std::vector<int> parent;
////    std::vector<int> size;
////
////private:
////    std::vector<int> rank_;
////};
////
////
////class FeaturesMatcher
////{
////public:
////    virtual ~FeaturesMatcher() {}
////
////    void operator ()(const struImageFeatures &features1, const struImageFeatures &features2, struMatchesInfo& matches_info)
////    {
////        match(features1, features2, matches_info);
////    }
////
////    void operator ()(const std::vector<struImageFeatures> &features, std::vector<struMatchesInfo> &pairwise_matches);
////
////    bool isThreadSafe() const
////    {
////        return is_thread_safe_;
////    }
////
////protected:
////    FeaturesMatcher(bool is_thread_safe = false) : is_thread_safe_(is_thread_safe) {}
////
////    virtual void match(const struImageFeatures &features1, const struImageFeatures &features2,
////                       struMatchesInfo& matches_info) = 0;
////
////    bool is_thread_safe_;
////};
////
////
////class BestOf2NearestMatcher : public FeaturesMatcher
////{
////public:
////    BestOf2NearestMatcher(bool try_use_gpu = true, float match_conf = 0.55f, int num_matches_thresh1 = 6, int num_matches_thresh2 = 6);
////
////protected:
////    void match(const struImageFeatures &features1, const struImageFeatures &features2, struMatchesInfo &matches_info);
////    int num_matches_thresh1_;
////    int num_matches_thresh2_;
////    cv::Ptr<FeaturesMatcher> impl_;
////};
////

























#endif // CMLRASTERMOSAIC_H

