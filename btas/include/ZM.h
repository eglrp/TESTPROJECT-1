
/**
\file       ZM.h
\brief      ���Ĵ������
            
            �ṩʹ�õ��Ĵ������ı�̽ӿڡ�
            
\author     ������
\date       2008-03-10
\version    1.0
\note       WINDOWS/C
\par        �޸ļ�¼ 
            - ������ 2008-03-10 ģ�齨��
            
*/


#ifndef _ZM_H__
#define _ZM_H__


/****************************** �������� ************************************/
#define MS_MGC_HOST             "1L2X3C4"   /* ͨ��������                   */
#define MS_MGC_PROC             "4T3Y2Q1"   /* ͨ�������                   */
#define MS_MGC_TASK             0           /* ͨ��������                   */
#define MS_MGC_OBJ              0           /* ͨ��Ŀ����                   */
#define MS_SUB_LOC              0X1U        /* �������ͣ�����               */
#define MS_SUB_MAS              0X2U        /* �������ͣ���������           */
#define MS_SUB_SLA              0X4U        /* �������ͣ����籸��           */
#define MS_PRO_RT               1           /* Э�����ͣ�ʵʱ��ϢЭ��       */
#define MS_PRO_RE               2           /* Э�����ͣ��ɿ���ϢЭ��       */
/****************************************************************************/


/***************************** �ṹ���� *************************************/
/** ������Ϣ */
typedef struct _MS_SubInfo
{
    unsigned int        uiMsgType;          /* ��Ϣ����                     */
    unsigned int        uiTaskCode;         /* ������                       */
    unsigned int        uiObjCode;          /* Ŀ����                       */
    unsigned int        uiSubType;          /* ��������                     */
    char                szHostName[16];     /* ������                       */
    char                szProcName[8];      /* ������                       */
    unsigned int        uiRate;             /* ���ո���                     */
}MS_SubInfo;

/** ��Ϣͷ */
typedef struct _MS_MsgHead
{
    unsigned int        uiMsgType;          /* ��Ϣ����                     */
    unsigned int        uiTaskCode;         /* ������                       */
    unsigned int        uiObjCode;          /* Ŀ����                       */
}MS_MsgHead;

/** ��Ϣ��ַ */
typedef struct _MS_MsgAddr
{
    char                szHostName[16];     /* ������                       */
    char                szProcName[8];      /* ������                       */
}MS_MsgAddr;
/****************************************************************************/


/***************************** �������� *************************************/
#ifdef __cplusplus
extern "C" {
#endif

int ms_init();                              /* �����ʼ��                   */
int ms_open(unsigned int uiSubNum,
            MS_SubInfo   stSubInfo[],
            unsigned int uiQueBufLen);      /* �򿪶���                     */
int ms_close(int siQueID);                  /* �رն���                     */
int ms_send(MS_MsgHead        stMsgHead,
            const void*       pvSndBuf,
            int               siSndLen,
            unsigned int      uiProType,
            const MS_MsgAddr* pstMsgDest);  /* ������Ϣ                     */
int ms_sendex(MS_MsgHead        stMsgHead,
              const void*       pvSndBuf,
              int               siSndLen,
              unsigned int      uiProType,
              const MS_MsgAddr* pstMsgSour,
              const MS_MsgAddr* pstMsgDest);/* ������Ϣ                     */
int ms_recv(int         siQueID,
            MS_MsgHead* pstMsgHead,
            void*       pvBuf,
            int         siBufLen,
            MS_MsgAddr* pstMsgSour);        /* ����������                   */
int ms_recvw(int         siQueID,
             MS_MsgHead* pstMsgHead,
             void*       pvBuf,
             int         siBufLen,
             MS_MsgAddr* pstMsgSour);       /* ��������                    */
int ms_recvm(unsigned int uiQueIDNum,
             int          siQueID[],
             MS_MsgHead*  pstMsgHead,
             void*        pvBuf,
             int          siBufLen,
             MS_MsgAddr*  pstMsgSour);      /* �������������               */
int ms_recva(int         siQueID,
             MS_MsgHead* pstMsgHead,
             void*       pvBuf,
             int         siBufLen,
             MS_MsgAddr* pstMsgSour);       /* �첽����                     */
int ms_setaio(int siQueID, 
              int (*AioFunc)(int));         /* �����첽I/O                  */
int ms_ctlaio(int siHow);                   /* �����첽I/O                  */
int ms_getrate(int          siQueID, 
               unsigned int uiMsgType);     /* ��ȡ���ո���                 */
int ms_setrate(int          siQueID, 
               unsigned int uiMsgType,
               unsigned int uiRate);        /* ���ý��ո���                 */
int ms_gethname(char* pszHName,
                int   siLen);               /* ��ȡ�������                 */
void ms_perror(int        siErrCode,
               const char szErrPre[]);      /* ��ȡ����˵��                 */
char* ms_strerr(int siErrCode);             /* ��ȡ����˵��                 */

#ifdef __cplusplus
}
#endif
/****************************************************************************/


/****************************************************************************/
/****************************************************************************/
/****************************** �������� ************************************/
#define ZM_LOC                  0           /* �������ͣ����ض���           */
#define ZM_REM_MAS              1           /* �������ͣ��������(ֻ������) */
#define ZM_REM_SLA              2           /* �������ͣ��������(ֻ�ձ���) */
#define ZM_REM_DUP              3           /* �������ͣ��������(��������) */
#define ZM_TASK_CODE_WILDCARD   0           /* ͨ��������                   */
#define ZM_OBJ_CODE_WILDCARD    0           /* ͨ��Ŀ����                   */
/****************************************************************************/


/***************************** �ṹ���� *************************************/
/* ZM��ַ */
typedef struct _ZM_Addr
{
    unsigned int        uiHostIP;           /* ����IP                       */
    unsigned int        uiProcID;           /* ����ID                       */
    char                szProcName[8];      /* ������                       */
}ZM_Addr;

/* ����ͷ */
typedef MS_MsgHead      ZM_MsgHead;
/****************************************************************************/


/***************************** �������� *************************************/
#ifdef __cplusplus
extern "C" {
#endif

int zm_init();                              /* �����ʼ��                   */
int zm_open(unsigned int uiMsgTypeNum,
            unsigned int uiMsgType[],
            unsigned int uiQueType,
            unsigned int uiTaskCode,
            unsigned int uiObjCode,
            unsigned int uiQueBufLen);      /* �򿪶���                     */
int zm_close(int siQueID);                  /* �رն���                     */
int zm_send(ZM_MsgHead  stMsgHead,
            const void* pvSndBuf,
            int         siSndLen);          /* ���͵���                     */
int zm_recv(int         siQueID,
            ZM_MsgHead* pstMsgHead,
            void*       pvBuf,
            int         siBufLen,
            ZM_Addr*    pstAddr);           /* ����������                   */
int zm_recvw(int         siQueID,
             ZM_MsgHead* pstMsgHead,
             void*       pvBuf,
             int         siBufLen,
             ZM_Addr*    pstAddr);          /* ��������                     */
int zm_recvm(unsigned int uiQueIDNum,
             int          siQueID[],
             ZM_MsgHead*  pstMsgHead,
             void*        pvBuf,
             int          siBufLen,
             ZM_Addr*     pstAddr);         /* �������������               */
int zm_recva(int          siQueID,
             ZM_MsgHead*  pstMsgHead,
             void*        pvBuf,
             int          siBufLen,
             ZM_Addr*     pstAddr);         /* �첽����                     */
int zm_setaio(int siQueID, 
              int (*AioFunc)(int));         /* �����첽I/O                  */
int zm_ctlaio(int siHow);                   /* �����첽I/O                  */
int zm_gethname_(char* pszHName,
                 int   siLen);              /* ��ȡ�������                 */
void zm_perror(int        siErrCode,
               const char szErrPre[]);      /* ��ȡ����˵��                 */
char* zm_strerr(int siErrCode);             /* ��ȡ����˵��                 */

#ifdef __cplusplus
}
#endif
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/


#endif
