/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlBase.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���̹�����������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef _MLBASE_H
#define _MLBASE_H

#include "../../include/mlTypes.h"
#include "mlMat.h"


/*******************************************************
�������ƣ�դ�񹫹���,��2d��ΪԪ�صľ���
��    �ߣ����Ļ�
��������������դ��������Ͻǽ�Ϊԭ�㣬����Ϊx������Ϊy
��    ��:
��    ��:
�汾���:   1.0
�޸���ʷ:    <����>    <ʱ��>   <�汾���>    <����>
********************************************************/

typedef CmlTemplateMat<Pt2d> CRasterPt2D;//!<Pt2d�;���ṹ��

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

/**
* @fn PtInRect
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ж�ĳ���Ƿ��ھ��ο���
* @param pt ĳPt2i�͵�
* @param rect ���ο�
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool PtInRect( Pt2i pt, MLRect rect );
/**
* @fn PtInRect
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ж�ĳ���Ƿ��ھ��ο���
* @param pt ĳPt2d�͵�
* @param rect ���ο�
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool PtInRect( Pt2d pt, MLRect rect );


/**
* @fn OPK2RMat
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��ת��OPKת������ת����
* @param pOri ��ת��OPK
* @param pRMat ��ת����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool OPK2RMat( OriAngle* pOri, CmlMat* pRMat );
/**
* @fn OPK2RMat
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��ת����ת������ת��OPK
* @param pRMat ��ת����
* @param pOri ��ת��OPK
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool RMat2OPK( CmlMat* pRMat, OriAngle* pOri );

/**
* @class CmlLogRecord
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief LOG��Ϣ��¼��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
class CmlLogRecord
{
public:
    /**
    * @fn CmlLogRecord
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlLogRecord��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlLogRecord();
    /**
    * @fn ~CmlLogRecord
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlLogRecord����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    ~CmlLogRecord();

public:
    /**
    * @fn Open
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��ʼ������ļ���·�������Ƿ���Ҫ��ӡ����Ļ��.ͬʱ����˴���־��ͷ��Ϣ
    * @param strFilePath �ļ�·��
    * @param bIsNeedPrSINTOnScreen ��Ļ��ӡѡ��
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool Open( const SCHAR*  strFilePath, bool bIsNeedPrSINTOnScreen = true );
    /**
    * @fn Close
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �ر��ļ�
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool Close();
    /**
    * @fn AddSuccessQuitMsg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ���������������˳���Ϣ����
    * @param cFuncName ������
    * @param cFileName �ļ���
    * @param nLineNum �������ļ��е�λ��
    * @return �޷���ֵ
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void AddSuccessQuitMsg( const SCHAR* cFuncName, const SCHAR* cFileName, UINT nLineNum );
    /**
    * @fn AddErrorMsg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ������������Ԥ֪������Ϣ����
    * @param cMsg ��Ϣ
    * @param cFuncName ������
    * @param cFileName �ļ���
    * @param nLineNum �������ļ��е�λ��
    * @return �޷���ֵ
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void AddErrorMsg( SCHAR* cMsg, const SCHAR* cFuncName, const SCHAR* cFileName, UINT nLineNum );
    /**
    * @fn AddExceptionMsg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �������г����쳣��Ϣ����
    * @param cMsg ��Ϣ
    * @param cFuncName ������
    * @param cFileName �ļ���
    * @param nLineNum �������ļ��е�λ��
    * @return �޷���ֵ
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void AddExceptionMsg( SCHAR* cMsg, const SCHAR* cFuncName, const SCHAR* cFileName, UINT nLineNum );
    /**
    * @fn AddNoticeMsg
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief �������г�����ʾ��Ϣ����
    * @param cMsg ��Ϣ
    * @param cFuncName ������
    * @param cFileName �ļ���
    * @param nLineNum �������ļ��е�λ��
    * @return �޷���ֵ
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    void AddNoticeMsg( SCHAR* cMsg, const SCHAR* cFuncName, const SCHAR* cFileName, UINT nLineNum );

    bool   m_bIsValid;//!<�ж��Ƿ���Ч
private:
    string m_strTotalMsg;//!<ȫ����Ϣ
    string m_strFilePath;//!<�ļ�·��

    bool   m_bIsNeedPrSINTOnScreen;//!<�Ƿ������Ļ��ӡ

    FILE*  m_pOutPutFile;//!<����ļ�·��

};

extern CmlLogRecord  g_clsLog;//!<LOG��Ϣ��¼


#define LOGAddSuccessQuitMsg( )         if( g_clsLog.m_bIsValid == true ){ g_clsLog.AddSuccessQuitMsg( __PRETTY_FUNCTION__, __FILE__, __LINE__ );};
#define LOGAddErrorMsg( strMsg )        if( g_clsLog.m_bIsValid == true ){ g_clsLog.AddErrorMsg( strMsg, __PRETTY_FUNCTION__, __FILE__, __LINE__ );};
#define LOGAddExceptionMsg( strMsg )    if( g_clsLog.m_bIsValid == true ){ g_clsLog.AddExceptionMsg( strMsg, __PRETTY_FUNCTION__, __FILE__, __LINE__ );};
#define LOGAddNoticeMsg( strMsg )       if( g_clsLog.m_bIsValid == true ){ g_clsLog.AddNoticeMsg( strMsg, __PRETTY_FUNCTION__, __FILE__, __LINE__ );};






#endif
