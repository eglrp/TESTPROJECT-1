/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlBase.cpp
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���̹�������ʵ��Դ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/

#include "mlBase.h"

CmlLogRecord g_clsLog ;
/************************************************************
*************************************************************/
CmlLogRecord::CmlLogRecord()
{
    m_bIsNeedPrSINTOnScreen = true;
    m_bIsValid = false;

    m_pOutPutFile = NULL;

}
CmlLogRecord::~CmlLogRecord()
{

}
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
bool CmlLogRecord::Open( const SCHAR*  strFilePath, bool bIsNeedPrSINTOnScreen )
{
    if( m_bIsValid == true )
    {
        return false;
    }

    m_bIsNeedPrSINTOnScreen = bIsNeedPrSINTOnScreen;

    m_pOutPutFile = fopen( strFilePath, "w");

    if( m_pOutPutFile != NULL )
    {
        m_bIsValid = true;
        return true;
    }
    else
    {
        return false;
    }

}//��ʼ������ļ���·�������Ƿ���Ҫ��ӡ����Ļ��.ͬʱ����˴���־��ͷ��Ϣ
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
bool CmlLogRecord::Close()
{
    m_strFilePath.clear();
    m_strTotalMsg.clear();
    if( m_pOutPutFile != NULL )
    {
        fclose( m_pOutPutFile );
    }
    m_bIsValid = false;
    return true;
}
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
void CmlLogRecord::AddSuccessQuitMsg( const SCHAR* cFuncName, const SCHAR* cFileName, UINT nLineNum )
{
    string strMsg = "Success  ;";

    string strFileName(cFileName);
    string strFuncName(cFuncName);
    string strStatus( "Quit Function" );
    SCHAR strLine[10];
    sprintf( strLine, "%d", nLineNum );

    strMsg.append( strStatus );
    strMsg += ";  ";
    strMsg.append( strFuncName );
    strMsg += ";  ";
    strMsg.append( strFileName );
    strMsg +="; Line  ";
    strMsg.append( strLine );
    strMsg += '\n';

    if( m_bIsNeedPrSINTOnScreen )
    {
        cout << strMsg;
    }
    if( m_bIsValid )
    {
        fprintf( m_pOutPutFile, "%s", strMsg.c_str() );
    }

    m_strTotalMsg.append( strMsg );
    return;
}
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
void CmlLogRecord::AddErrorMsg( SCHAR* cMsg, const SCHAR* cFuncName, const SCHAR* cFileName, UINT nLineNum )
{
    string strTmpMsg = "Error    ;";

    string strFileName(cFileName);
    string strFuncName(cFuncName);
    string strStatus( cMsg );
    SCHAR strLine[10];
    sprintf( strLine, "%d", nLineNum );

    strTmpMsg.append( strStatus );
    strTmpMsg += ";  ";
    strTmpMsg.append( strFuncName );
    strTmpMsg += ";  ";
    strTmpMsg.append( strFileName );
    strTmpMsg +="; Line  ";
    strTmpMsg.append( strLine );
    strTmpMsg += '\n';

    if( m_bIsNeedPrSINTOnScreen )
    {
        cout << strTmpMsg;
    }

    if( m_bIsValid )
    {
        fprintf( m_pOutPutFile, "%s", strTmpMsg.c_str() );
    }

    m_strTotalMsg.append( strTmpMsg );
    return;
}
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
void CmlLogRecord::AddExceptionMsg( SCHAR* cMsg, const SCHAR* cFuncName, const SCHAR* cFileName, UINT nLineNum )
{
    string strTmpMsg = "Exception; ";

    string strFileName(cFileName);
    string strFuncName(cFuncName);
    string strStatus( cMsg );
    SCHAR strLine[10];
    sprintf( strLine, "%d", nLineNum );

    strTmpMsg.append( strStatus );
    strTmpMsg += ";  ";
    strTmpMsg.append( strFuncName );
    strTmpMsg += ";  ";
    strTmpMsg.append( strFileName );
    strTmpMsg +="; Line  ";
    strTmpMsg.append( strLine );
    strTmpMsg += '\n';

    if( m_bIsNeedPrSINTOnScreen )
    {
        cout << strTmpMsg;
    }

    if( m_bIsValid )
    {
        fprintf( m_pOutPutFile, "%s", strTmpMsg.c_str() );
    }

    m_strTotalMsg.append( strTmpMsg );
    return;
}
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
void CmlLogRecord::AddNoticeMsg( SCHAR* cMsg, const SCHAR* cFuncName, const SCHAR* cFileName, UINT nLineNum )
{
    string strTmpMsg = "Notice   ; ";

    string strFileName(cFileName);
    string strFuncName(cFuncName);
    string strStatus( cMsg );
    SCHAR strLine[10];
    sprintf( strLine, "%d", nLineNum );

    strTmpMsg.append( strStatus );
    strTmpMsg += ";  ";
    strTmpMsg.append( strFuncName );
    strTmpMsg += ";  ";
    strTmpMsg.append( strFileName );
    strTmpMsg +="; Line  ";
    strTmpMsg.append( strLine );
    strTmpMsg += '\n';

    if( m_bIsNeedPrSINTOnScreen )
    {
        cout << strTmpMsg;
    }

    if( m_bIsValid )
    {
        fprintf( m_pOutPutFile, "%s", strTmpMsg.c_str() );
    }

    m_strTotalMsg.append( strTmpMsg );
    return;
}
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
bool PtInRect( Pt2i pt, MLRect rect )
{
    if( ( pt.X < rect.dXMin )||( pt.X > rect.dXMax )||( pt.Y < rect.dYMin )||( pt.Y > rect.dYMax ) )
    {
        return false;
    }
    else
    {
        return true;
    }
}
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
bool PtInRect( Pt2d pt, MLRect rect )
{
    if( ( pt.X < rect.dXMin )||( pt.X > rect.dXMax )||( pt.Y < rect.dYMin )||( pt.Y > rect.dYMax ) )
    {
        return false;
    }
    else
    {
        return true;
    }
}
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
bool OPK2RMat( OriAngle* pOri, CmlMat* pRMat )
{
    if( false == pRMat->IsValid() )
    {
        pRMat->Initial( 3, 3 );
    }
    if( ( pRMat->GetH() != 3) || ( pRMat->GetW() != 3 ) )
    {
        return false;
    }

    DOUBLE dSOmg = sin( (pOri->omg) );
    DOUBLE dSPhi = sin( (pOri->phi) );
    DOUBLE dSKap = sin( (pOri->kap) );

    DOUBLE dCOmg = cos( (pOri->omg) );
    DOUBLE dCPhi = cos( (pOri->phi) );
    DOUBLE dCKap = cos( (pOri->kap) );

    pRMat->SetAt( 0, 0, dCPhi*dCKap );
    pRMat->SetAt( 0, 1, -dCPhi*dSKap );
    pRMat->SetAt( 0, 2, dSPhi );

    pRMat->SetAt( 1, 0, ( dCOmg*dSKap + dSOmg*dSPhi*dCKap ) );
    pRMat->SetAt( 1, 1, ( dCOmg*dCKap - dSOmg*dSPhi*dSKap ) );
    pRMat->SetAt( 1, 2, -dSOmg*dCPhi );

    pRMat->SetAt( 2, 0, ( dSOmg*dSKap - dCOmg*dSPhi*dCKap ) );
    pRMat->SetAt( 2, 1, ( dSOmg*dCKap + dCOmg*dSPhi*dSKap ) );
    pRMat->SetAt( 2, 2, dCOmg*dCPhi );

    return true;

}

/**
* @fn RMat2OPK
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
bool RMat2OPK( CmlMat* pRMat, OriAngle* pOri )
{
    pOri->omg = ( atan2( -pRMat->GetAt(1, 2), pRMat->GetAt(2,2) ) );
    pOri->phi = ( atan2( pRMat->GetAt(0, 2), sqrt(pRMat->GetAt(1, 2)*pRMat->GetAt(1, 2)+ pRMat->GetAt(2, 2)*pRMat->GetAt(2, 2)) ) );
    pOri->kap = ( atan2( -pRMat->GetAt(0,1), pRMat->GetAt(0,0) ) );

    return true;
};

















