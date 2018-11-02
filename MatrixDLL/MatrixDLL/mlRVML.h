#ifndef _MLRVML_H_
#define _MLRVML_H_

#include "mlTypes.h"

//����ľ����зֱ�Ϊ������λ�ã����ף��������������
/**
* @fn mlDealSiteImgSelection
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����չ���ǡ�ƫ���ǡ������Ǻͱ궨�İ��þ����������ڱ�������ϵ�µ���̬��λ�ã����뵥λΪ������ף������������
* @param[in] dExpAngle չ����
* @param[in] dYawAngle ƫ����
* @param[in] dPitchAngle ������
* @param[in] matMastExp2Body չ������ڱ���İ�װ����
* @param[in] matMastYaw2Exp ƫ�������չ���İ�װ����
* @param[in] matMastPitch2Yaw ���������ƫ���İ�װ����
* @param[in] matLCamBase2Pitch �������׼����ڸ����İ�װ����
* @param[in] matRCamBase2LCamBase �������׼������������׼�İ�װ����
* @param[in] matLCamCap2Base �������������ڻ�׼�İ�װ����
* @param[in] matRCamCap2Base �������������ڻ�׼�İ�װ����
* @param[out] exOriCamL ������ⷽλ
* @param[out] exOriCamR ������ⷽλ

* @version 1.0
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI( bool ) mlCalcCamOriByGivenInstallMatrix( DOUBLE dExpAngle, DOUBLE dYawAngle, DOUBLE dPitchAngle, stuInsMat matMastExp2Body, stuInsMat matMastYaw2Exp, stuInsMat matMastPitch2Yaw, \
                                         stuInsMat matLCamBase2Pitch, stuInsMat matRCamBase2LCamBase, stuInsMat matLCamCap2Base, stuInsMat matRCamCap2Base, \
                                         ExOriPara &exOriCamL, ExOriPara &exOriCamR );

MLAPI( bool ) mlCalcCamOriInWorldByGivenInsMatPosX( stuInsMat matBase, DOUBLE dExpAngle, DOUBLE dYawAngle, DOUBLE dPitchAngle, stuInsMat matMastExp2Body, stuInsMat matMastYaw2Exp, stuInsMat matMastPitch2Yaw, \
	                                                  stuInsMat matLCamBase2Pitch, stuInsMat matRCamBase2LCamBase, stuInsMat matLCamCap2Base, stuInsMat matRCamCap2Base, \
	                                                  ExOriPara *pExOriCamL, ExOriPara *pEOriCamR);



MLAPI( bool ) mlCalcHazCamInWorld( stuInsMat matLCamBase2Body, stuInsMat matRCamBase2LCamBase, stuInsMat matLCamCap2Base, stuInsMat matRCamCap2Base, \
                                    ExOriPara &exOriCamL, ExOriPara &exOriCamR);

MLAPI( bool ) mlCalcHazCamInBodyVT( stuInsMat matLCamCap2Body, stuInsMat matLCamCap2RCamCap, ExOriPara &exOriCamL, ExOriPara &exOriCamR );


MLAPI( bool ) mlCalcMonitorPicXY( DOUBLE dAngle1, DOUBLE dAngle2, DOUBLE dAngle3, DOUBLE dPitchAngle, DOUBLE dCamX, DOUBLE dCamY, DOUBLE dCamZ, DOUBLE dPlaneGround,\
	                                DOUBLE dFocal, DOUBLE dObjX, DOUBLE  dObjY, DOUBLE dObjZ, DOUBLE *pPicX, DOUBLE *pPicY );

MLAPI( bool ) mlCalcObjXY( DOUBLE dAngle1, DOUBLE dAngle2, DOUBLE dAngle3, DOUBLE dPitchAngle, DOUBLE dCamX, DOUBLE dCamY, DOUBLE dCamZ, DOUBLE dPlaneGround,\
									DOUBLE dFocal, DOUBLE dPicX, DOUBLE dPicY ,  DOUBLE *pObjX, DOUBLE *pObjY, DOUBLE *pObjZ);

MLAPI( bool ) mlTest();














#endif


