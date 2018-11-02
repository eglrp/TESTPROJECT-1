/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlPhgProc.cpp
* @date 2012.01
* @author ������ zhangchy@irsa.ac.cn
* @brief ��Ӱ�����㷨��ʵ��ͷ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#ifndef CMLPHGPROC_H
#define CMLPHGPROC_H
#include "mlBase.h"
#include "mlMat.h"
#include "mlRasterBlock.h"
DOUBLE DisIn2Pts( Pt3d pt1, Pt3d pt2 );
DOUBLE DisIn2Pts( Pt2d pt1, Pt2d pt2 );

bool getxyFromXYZ( DOUBLE& x, DOUBLE& y, DOUBLE X, DOUBLE Y, DOUBLE Z, DOUBLE *XsYsZs, DOUBLE *R, DOUBLE fx, DOUBLE fy );
bool getxyFromXYZ( Pt2d &ptxy, Pt3d ptXYZ, Pt3d ptXYZOrg, CmlMat matOPK, DOUBLE fx, DOUBLE fy );
bool getxyFromXYZ( Pt2d &ptxy, Pt3d ptXYZ, Pt3d ptXYZOrgL, DOUBLE dBaseLength, CmlMat matOPK, DOUBLE fx, DOUBLE fy );

typedef vector<Pt2d> PTARRAY;
typedef vector<Pt3d> PTARRAY_V;
/**
* @class CmlPhgProc
* @date 2011.11
* @author ������ zhangchy@irsa.ac.cn
* @brief ��Ӱ�����㷨�ඨ��
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*
*/
class CmlPhgProc
{
public :

public:
    /**
    *@fn CmlPhgProc()
    *@date 2011.11
    *@author ������
    *@brief ��Ӱ�����㷨�๹�캯��
    *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
    */
    CmlPhgProc();


    /**
    *@fn ~CmlPhgProc()
    *@date 2011.11
    *@author ������
    *@brief ��Ӱ�����㷨��������
    *@version 1.0
    *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n
    */
    virtual ~CmlPhgProc();


    /**
    *@fn mlReproject(Pt2d* pImgpt, Pt3d* pGroundPt,ExOriPara* pExOri, DOUBLE fx, DOUBLE fy,CmlMat* pRotateMat = NULL)
    *@date 2011.11
    *@author ������
    *@brief ���ݹ��߷��̣����﷽����㷴Ͷ����ƽ����
    *@param pImgpt �����������ָ��
    *@param pGroundPt �﷽��λ������ָ��
    *@param pExOri �ⷽλԪ��ָ��
    *@param fx   ����
    *@param fy   ����
    *@param pRotateMat ��ת����ָ�룬Ĭ��Ϊ��
    *@retval TRUE �ɹ�
    *@retval FALSE ʧ��
    *@version 1.0
    *@par �޸���ʷ��
    *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    //bool mlReproject(Pt2d* pImgpt, Pt3d* pGroundPt,ExOriPara* pExOri, double fx, double fy);
    bool mlReproject(Pt2d* pImgpt, Pt3d* pGroundPt,ExOriPara* pExOri, DOUBLE fx, DOUBLE fy,CmlMat* pRotateMat = NULL);

    /**
     *@fn mlBackForwardinterSection
     *@date 2011.11
     *@author ������
     *@brief �ɿ��Ƶ�����󷽽̻����Ӱ���ⷽ��Ԫ��
     *@param pImgPt ������㼯  �ṹ������
     *@param pGroundPt �﷽��λ������㼯  �ṹ������
     *@param fx  ����
     *@param fy  ����
     *@param pInitExOripara ��ʼ�ⷽλԪ��ָ��
     *@param pExOripara �ⷽΪԪ��ָ��
     *@param nPtNum �ܵ���
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n

    */
    bool mlBackForwardinterSection( Pt2d *pImgPt,Pt3d *pGroundPt, double fx,double fy, SINT nPtNum,ExOriPara *pInitExOripara, ExOriPara *pExOripara );

    bool mlBackForwardinterSection( vector<Pt2d> vecImgPts,vector<Pt3d> vec3ds, double dF, ExOriPara *pInitExOripara, ExOriPara *pExOripara );


    /**
     *@fn mlResectionNoInitalVal
     *@date 2011.11
     *@author ���Ļ�
     *@brief �����ʼֵ�ĺ󷽽���
     * @param[in] vecGCPs ���Ƶ�����
     * @param[in] vecImgPts �������(��ƽ������ϵ)
     * @param[in] dFocalLength �������(����)
     * @param[out] exOriRes ��λ����ⷽλԪ��
     * @param[out] vecRMS �����
     * @param[out] dTotalRMS �����
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��> \n

    */
    bool mlResectionNoInitalVal( vector<Pt3d> vecGCPs, vector<Pt2d> vecImgPts, DOUBLE dFocalLength, ExOriPara &exOriRes );

    bool mlCalcResidualError( Pt3d ptXYZ, Pt2d ptOrig2d, ExOriPara exOri, DOUBLE fx, DOUBLE fy, RMS2d &rmsError );
    /**
     *@fn mlGeoRasterCut
     *@date 2011.11
     *@author ������
     *@brief �������ض�DEM��DOM���вü�
     *@param strFileIn ���ü��������ļ�
     *@param strFileOut �ü�������ļ�
     *@param pttl �ü��������ص�λ��X Y
     *@param ptbr �ü����½����ص�����
     *@param nflag ָ���ü���ʽ 1Ϊ�����زü� 2Ϊ����������ü�
     *@param nCutBands ָ���ü����� Ϊ����ʱ��ʾ���в��ζ��ü� Ϊ��ʱ�ƶ��ü��ض��Ĳ���
     *@param dZoom ����ϵ�� Ĭ��Ϊ1
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

    */
    bool mlGeoRasterCut( const SCHAR* strFileIn, const SCHAR* strFileOut,Pt2d pttl,Pt2d ptbr,SINT nflag,SINT nCutBands,DOUBLE dZoom);

//        /**
//         *@fn mlGeoRasterCutByGeopos
//         *@date 2011.11
//         *@author ������
//         *@brief ���ݵ��������DEM��DOM���вü�
//         *@param strFileIn ���ü��������ļ�
//         *@param strFileOut �ü�������ļ�
//         *@param pttl �ü���ʼ����������
//         *@param ptbr �ü����½ǵ��������
//         *@retval TRUE �ɹ�
//         *@retval FALSE ʧ��
//         *@version 1.0
//         *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
//
//        */
    //  bool mlGeoRasterCutByGeopos(char* strFileIn,char* strFileOut,Pt2d pttl, Pt2d ptbr);



    /**
     *@fn mlImageReprj
     *@date 2012.02
     *@author ������
     *@brief ����DEM��DOM����ָ���ӽ��µķ���ͼ��
     *@param strDem DEM·�����ļ�����geotiff�ļ���ʽ��������������
     *@param strDom DOM·�����ļ�����geotiff�ļ���ʽ��������������
     *@param outImg ����ļ�����
     *@param exori ָ���ӽ��ⷽλԪ��
     *@param fx ����
     *@param fy ����
     *@param nImgWid ����ͼ��Ŀ�
     *@param nImgHei ����ͼ��ĸ�
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

    */
    bool mlImageReprj( const SCHAR* strDem, const SCHAR* strDom, const SCHAR* outImg,ExOriPara exori, DOUBLE fx,DOUBLE fy, SINT nImgWid, SINT nImgHei);

    /**
     *@fn mlTinSimply
     *@date 2012.02
     *@author ������
     *@brief ��������������
     *@param vecPt3dIn ��Ҫ�򻯵�������������
     *@param vecPt3dOut �򻯺��������������
     *@param simpleIndex ��ϵ�� ȡֵΪ0��1֮��
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.0
     *@par �޸���ʷ��<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n

    */
    bool mlTinSimply(vector<Pt3d> &vecPt3dIn,vector<Pt3d> &vecPt3dOut,double simpleIndex);

    bool mlTinSimplyDemoFile(vector<Pt3d> &vecPt3dIn,char* dst);


    bool ml4OnceQuationSolve( DOUBLE da, DOUBLE db, DOUBLE dc, DOUBLE dd, DOUBLE de, vector<DOUBLE> &vecRes  );

    bool mlGetDisBy3Pts(  vector<Pt3d> vecGCPs, vector<Pt2d> vecImgPts, DOUBLE dFocalLength, vector<Pt3d> &vecDisXYZ, Pt3d &dDisBLine, Pt3d &dAngle );

    bool mlGetXYZCoordBy3DisVal( vector<Pt3d> vecGCPs, Pt3d dDis, Pt3d dAngle, Pt3d &ptXYZ );

    bool mlGetRotateMatByXYZ(  vector<Pt3d> vecGCPs, vector<Pt2d> vecImgPts, Pt3d ptXYZ, DOUBLE dF, OriAngle &oriA );

    bool mlSolvePts( vector<Pt3d> vecOldPts, vector<Pt3d> vecNewPts, UINT nTimes, ExOriPara* pInitialOri );


    bool CalcConvexHull(vector<Pt2d> vecSrc, vector<Pt2d> &vecDst);

    bool CalcConvexHull(vector<Pt3d> vecSrc, vector<Pt3d> &vecDst);

    bool GetPolygonUnion2D( Polygon2d poly1, Polygon2d poly2, Polygon2d &polyNew );

    bool GetPolygonUnion3D( Polygon3d poly1, Polygon3d poly2, Polygon3d &polyNew );

    bool ExOriTrans( ExOriPara* pExOriL, ExOriPara* pExOriRela, ExOriPara* pExOriR );

    bool GetRelaOri( ExOriPara* pExOriL, ExOriPara* pExOriR, ExOriPara* pExOriRela );

    bool GetFitPlaneNormal( vector<Pt3d> vecXYZ, Pt3d &pPlaneNormal1, Pt3d &pPlaneNormal2 );

    bool GetAffineTCoef( vector<StereoMatchPt> vecMPts, DOUBLE &dA, DOUBLE &dB, DOUBLE &dC, DOUBLE &dD, DOUBLE &dXAccu, DOUBLE &dYAccu );

    bool GetTargetPtPos( Pt2d ptCent, DOUBLE dA, DOUBLE dB, DOUBLE dC, DOUBLE dD, Pt2d &ptOutRes);

    bool CalcCamOriByGivenInstallMatrix( DOUBLE dExpAngle, DOUBLE dYawAngle, DOUBLE dPitchAngle, stuInsMat matMastExp2Body, stuInsMat matMastYaw2Exp, stuInsMat matMastPitch2Yaw, \
                                         stuInsMat matLCamBase2Pitch, stuInsMat matRCamBase2LCamBase, stuInsMat matLCamCap2Base, stuInsMat matRCamCap2Base, \
                                         ExOriPara &exOriCamL, ExOriPara &exOriCamR );

    bool CalcCamOriByGivenInstallMatrixVT( DOUBLE dExpAngle, DOUBLE dYawAngle, DOUBLE dPitchAngle, stuInsMat matMastExp2Body, stuInsMat matMastYaw2Exp, stuInsMat matMastPitch2Yaw, \
                                         stuInsMat matLCamBase2Pitch, stuInsMat matLCamBase2LCamCap, stuInsMat matRCamCap2LCamCap, \
                                         ExOriPara &exOriCamL, ExOriPara &exOriCamR );


    bool CalcCamOriInWorldByGivenInsMat( stuInsMat matBase, DOUBLE dExpAngle, DOUBLE dYawAngle, DOUBLE dPitchAngle, stuInsMat matMastExp2Body, stuInsMat matMastYaw2Exp, stuInsMat matMastPitch2Yaw, \
                                         stuInsMat matLCamBase2Pitch, stuInsMat matRCamBase2LCamBase, stuInsMat matLCamCap2Base, stuInsMat matRCamCap2Base, \
                                         ExOriPara &exOriCamL, ExOriPara &exOriCamR );

    bool CalcCamOriInWorldByGivenInsMatVT( stuInsMat matBase, DOUBLE dExpAngle, DOUBLE dYawAngle, DOUBLE dPitchAngle, stuInsMat matMastExp2Body, stuInsMat matMastYaw2Exp, stuInsMat matMastPitch2Yaw, \
                                         stuInsMat matLCamBase2Pitch, stuInsMat matLCamBase2LCamCap, stuInsMat matRCamCap2LCamCap, \
                                         ExOriPara &exOriCamL, ExOriPara &exOriCamR  );

    bool mlCalcHazCamInWorld( stuInsMat matLCamBase2Body, stuInsMat matRCamBase2LCamBase, stuInsMat matLCamCap2Base, stuInsMat matRCamCap2Base, \
                                    ExOriPara &exOriCamL, ExOriPara &exOriCamR );

    bool mlCalcHazCamInWorldVT( stuInsMat matBase, stuInsMat matLCamCap2Body, stuInsMat matLCamCap2RCamCap, ExOriPara &exOriCamL, ExOriPara &exOriCamR );

    bool mlCalcHazCamInBodyVT( stuInsMat matLCamCap2Body, stuInsMat matLCamCap2RCamCap, ExOriPara &exOriCamL, ExOriPara &exOriCamR );

    bool GetOPKAngle( DOUBLE *pRMat, DOUBLE *pOPK );

    bool GetRMatByOPK( DOUBLE *pOPK, DOUBLE *pRMat );

    bool Polygon3dUnion( Polygon3d poly1, Polygon3d poly2, Polygon3d polyRes );

    bool PersProjInFlat( const SCHAR* strImg, InOriPara inOri, ExOriPara exOri, DOUBLE dRes, DOUBLE dRange, DOUBLE dCamH, const SCHAR* strPers );

    bool PersProjInFlat( const SCHAR* strImg, InOriPara inOri, ExOriPara exOri, DOUBLE dRes, DOUBLE dRange, DOUBLE dCamH, Pt2d &ptOrig, CmlRasterBlock &clsRB );

	bool RelaOriCalcWithOrigPts( vector<StereoMatchPt> vecMatchPts, InOriPara inOriL, UINT nHL, InOriPara inOriR, UINT nHR, ExOriPara &exOriRela );

	bool FindMatchHoleInImg( vector<Pt2i> vecMatchedPts, UINT nW, UINT nH, UINT nHoleRange, vector<Polygon2d> &vecHolePolys );

	bool Find3DCoordBy2DPos( InOriPara inOri, ExOriPara exOri, Pt2d ptPos, GeoRasBlock *pclsGeoRasterB, Pt3d &ptRes );

	bool ResectionInMultiImg( vector<Pt3d> vecGCPs, vector<vector<Pt2d>> vecMultiImgPts, vector<DOUBLE> vecFocals, vector<ExOriPara> vecExInOri, vector<ExOriPara> &vecImgOutExOris );
protected:
private:
	bool getCoef( Pt2d ptXY, Pt3d ptObjXYZ, DOUBLE df, ExOriPara exOri, ExOriPara exOriRela, DOUBLE *pCoef );
};

#endif // CMLPHGPROC_H
