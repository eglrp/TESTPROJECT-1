/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlPtsManage.h
* @date 2012.02.10
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ƥ������ͷ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#ifndef CMLPTSMANAGE_H
#define CMLPTSMANAGE_H

#include "mlBase.h"
/**
* @class CmlPtsManage
* @date 2012.02.10
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ƥ��������
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlPtsManage
{
public:
    /**
    * @fn CmlPtsManage
    * @date 2012.02.10
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlPtsManage��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlPtsManage();

    /**
    * @fn ~CmlPtsManage
    * @date 2012.02.10
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlPtsManage����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    virtual ~CmlPtsManage();

    /**
    * @fn GetPairPts
    * @date 2012.02.10
    * @author  ���Ļ� whwan@irsa.ac.cn
    * @brief ����Ӱ��ƥ������Ӱ��ƥ���ϲ�
    * @param clsImgLPts ��Ӱ��ƥ���
    * @param clsImgRPts ��Ӱ��ƥ���
    * @param vecMatchPts ����ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool GetPairPts( ImgPtSet &clsImgLPts, ImgPtSet &clsImgRPts, vector<StereoMatchPt> &vecMatchPts );

    /**
    * @fn SplitPairPts
    * @date 2012.02.10
    * @author  ���Ļ� whwan@irsa.ac.cn
    * @brief ���ɶ�ƥ���ֿ�
    * @param frmInfoL ��Ӱ����Ϣ
    * @param frmInfoR ��Ӱ����Ϣ
    * @param vecAutoMatchPts ����ͬ��ƥ���
    * @param clsImgLPts ��Ӱ��ƥ���
    * @param clsImgRPts ��Ӱ��ƥ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool SplitPairPts( FrameImgInfo frmInfoL, FrameImgInfo frmInfoR, vector<StereoMatchPt> &vecAutoMatchPts, ImgPtSet &clsImgLPts, ImgPtSet &clsImgRPts );

    /**
    * @fn GetNewStereoPtID
    * @date 2012.02.10
    * @author  ���Ļ� whwan@irsa.ac.cn
    * @brief ��ȡƥ���ı��
    * @param clsLPts ��Ӱ����Ϣ
    * @param clsRPts ��Ӱ����Ϣ
    * @param lID ƥ���ı��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool GetNewStereoPtID( ImgPtSet &clsLPts, ImgPtSet &clsRPts, ULONG &lID  );

    /**
    * @fn GetNewSinglePtID
    * @date 2012.02.10
    * @author  ���Ļ� whwan@irsa.ac.cn
    * @brief ��ȡ������ı��
    * @param clsImgPts Ӱ����Ϣ
    * @param lID ƥ���ı��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ:
    * <����>  <ʱ��>  <�汾���>  <����>\n
    */
    bool GetNewSinglePtID(  ImgPtSet &clsImgPts, ULONG &lID  );


protected:
private:
};

#endif // CMLPTSMANAGE_H
