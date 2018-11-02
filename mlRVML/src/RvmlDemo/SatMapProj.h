#ifndef CSATMAPPROJ_H
#define CSATMAPPROJ_H
#include "imageviewer.h"
#include "../../include/mlTypes.h"

class CmlSatMapProj
{
public:
    CmlSatMapProj( );
    CmlSatMapProj( string strPath );
    virtual ~CmlSatMapProj();
    bool LoadProj( SatProj &pro, SatOptions &ops, string projPath, string demPath, string domPath, DOUBLE dRes, bool bBaseFlag );
    bool SatMapping( string projPath, string demPath, string domPath, DOUBLE dRes, bool bBaseFlag, bool bUsePts );
    /**
        * @fn ReadCE1InOri
        * @date 2011.12.16
        * @author ��һ�� ylliu@irsa.ac.cn
        * @brief ����CE-1����Ӱ���ڶ�������ļ�
        * @param path �ļ�·��
        * @param CE1img CE-1����Ӱ��
        * @param CE1imgIO CE-1����Ӱ���ڶ������
        * @retval TRUE �ɹ�
        * @retval FALSE ʧ��
        * @version 1.0
        * @par �޸���ʷ:
        * <����>  <ʱ��>  <�汾���>  <����>\n
        */
    bool ReadCE1InOri( const SCHAR *path, CE1IOPara &CE1imgIO );
    /**
    * @fn ReadCE2InOri
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ����CE-2����Ӱ���ڶ�������ļ�
    * @param path �ļ�·��
    * @param CE2img CE-2����Ӱ��
    * @param CE2imgIO CE-2����Ӱ���ڶ������
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool ReadCE2InOri( const SCHAR *path, CE2IOPara &CE2imgIO );
    /**
    * @fn ReadImgScanTime
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ��������Ӱ��ɨ����ʱ���ļ�
    * @param path �ļ�·��
    * @param pImgTime ����Ӱ��ɨ����ʱ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool ReadImgScanTime( const SCHAR *path, vector<DOUBLE> &vecImgTime );
//    /**
//    * @fn ReadEo
//    * @date 2011.12.16
//    * @author ��һ�� ylliu@irsa.ac.cn
//    * @brief ��������Ӱ��ԭʼ��������ļ�
//    * @param path �ļ�·��
//    * @param pEo ����Ӱ��ԭʼ�������
//    * @retval TRUE �ɹ�
//    * @retval FALSE ʧ��
//    * @version 1.0
//    * @par �޸���ʷ:
//    * <����>  <ʱ��>  <�汾���>  <����>\n
//    */
//    bool ReadEo( const SCHAR *path, CmlMat *pEo );
    /**
    * @fn ReadLineEo
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ��������Ӱ��ԭʼ��������ļ��ⷽλ��Ԫ��
    * @param path �ļ�·��
    * @param pEo �ⷽλ��Ԫ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool ReadLineEo( const SCHAR *path, vector<LineEo> &vecLineEo );
    /**
    * @fn ReadAngleEo
    * @date 2011.12.16
    * @author ��һ�� ylliu@irsa.ac.cn
    * @brief ��������Ӱ��ԭʼ��������ļ��ⷽλ��Ԫ��
    * @param path �ļ�·��
    * @param pEo ����Ӱ��ԭʼ��������ⷽλ��Ԫ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool ReadAngleEo( const SCHAR *path, vector<AngleEo> &vecAngleEo );
    bool ReadPts( const SCHAR *path, vector<StereoMatchPt> &vecPts );

protected:
private:
};
#endif //CSATMAPPROJ_H
