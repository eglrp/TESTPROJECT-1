
/**
\file       ZF2.h
            �ļ��������
            
            �ṩʹ�û��ڶ��ķ���ģʽ�ļ��������ı�̽ӿڡ�
            
\author     ������
\date       2012-07-27
\version    1.0
\note       WINDOWS/C
\par        �޸ļ�¼ 
            - ������ 2012-07-27 ģ�齨��
            
*/


#ifndef _ZF2_H__
#define _ZF2_H__


/****************************** �������� ********************************************/
#define FS_MGC_HOST             "1L2X3C4"           /* ͨ��������                   */
#define FS_MGC_PROC             "4T3Y2Q1"           /* ͨ�������                   */
#define FS_MGC_TASK             0                   /* ͨ��������                   */
#define FS_MGC_OBJ              0                   /* ͨ��Ŀ����                   */
/************************************************************************************/


/***************************** �ṹ���� *********************************************/
/** �ļ�ͷ */
typedef struct _FS_FileHead
{
    unsigned int        uiFileType;                 /* �ļ�����                     */
    unsigned int        uiTaskCode;                 /* ������                       */
    unsigned int        uiObjCode;                  /* Ŀ����                       */
}FS_FileHead;

/** �ļ���ַ */
typedef struct _FS_FileAddr
{
    char               szHostName[16];              /* ������                       */
    char               szProcName[8];               /* ������                       */
}FS_FileAddr;
/************************************************************************************/


/***************************** �������� *********************************************/
#ifdef __cplusplus
extern "C" {
#endif

int fs_init();                                      /* �����ʼ��                   */
int fs_putone(const FS_FileHead* pstFileHead,
              const char         szFileName[],
              char               scType,
              const void*        pvSndBuf,
              int                siSndLen,
              const FS_FileAddr* pstFileDest);      /* ����һ���ļ�                 */
int fs_puttwo(const FS_FileHead* pstFileHead,
              const char         szFileNameF[],
              char               scTypeF,
              const char         szFileNameS[],
              char               scTypeS,
              const void*        pvSndBuf,
              int                siSndLen,
              const FS_FileAddr* pstFileDest);      /* ���������ļ�                 */
int fs_putmulti(const FS_FileHead* pstFileHead,
                int                siFileNum,
                const char*        szFileName[],
                char               scType[],
                const void*        pvSndBuf,
                int                siSndLen,
                const FS_FileAddr* pstFileDest);    /* ���Ͷ���ļ�                 */
int fs_getone(const FS_FileHead* pstFileHead,
              const char         szFileName[],
              const char         szFileNameS[]);    /* ��ȡ�����ļ�                 */
int fs_getmulti(const FS_FileHead* pstFileHead,
                int                siFileNum,
                const char*        szFileName[],
                const char         szFileNameS[]);  /* ��ȡ����ļ�                 */
void fs_perror(int        siErrCode,
               const char szErrPre[]);              /* ��ȡ����˵��                 */
char* fs_strerr(int siErrCode);                     /* ��ȡ����˵��                 */

#ifdef __cplusplus
}
#endif
/************************************************************************************/



/****************************** �������� ********************************************/
#define ZF_TASK_CODE_WILDCARD   0                   /* ͨ��������                   */
#define ZF_OBJ_CODE_WILDCARD    0                   /* ͨ��Ŀ����                   */
/************************************************************************************/


/***************************** �ṹ���� *********************************************/
/** �ļ�ͷ */
typedef FS_FileHead     ZF_FileHead;

/** �ļ���ַ */
typedef FS_FileAddr     ZF_FileAddr;
/************************************************************************************/


/***************************** �������� *********************************************/
#ifdef __cplusplus
extern "C" {
#endif

int zf2_init();                                     /* �����ʼ��                   */
int zf2_putone(const ZF_FileHead* pstFileHead,
               const char         szFileName[],
               char               scType);          /* ����һ���ļ�                 */
int zf2_puttwo(const ZF_FileHead* pstFileHead,
               const char         szFileNameF[],
               char               scTypeF,
               const char         szFileNameS[],
               char               scTypeS);         /* ���������ļ�                 */
int zf2_putmulti(const ZF_FileHead* pstFileHead,
                 int                siFileNum,
                 const char*        szFileName[],
                 char               scType[]);      /* ���Ͷ���ļ�                 */
int zf2_getone(const ZF_FileHead* pstFileHead,
               const char         szFileName[],
               const char         szFileNameS[]);   /* ��ȡ�����ļ�                 */
int zf2_getmulti(const ZF_FileHead* pstFileHead,
                 int                siFileNum,
                 const char*        szFileName[],
                 const char         szFileNameS[]); /* ��ȡ����ļ�                 */
void zf2_perror(int         siErrCode,
                const char  szErrPre[]);            /* ��ȡ����˵��                 */
char* zf2_strerr(int siErrCode);                    /* ��ȡ����˵��                 */

int zf2_init_();                                    /* �����ʼ��                   */
int zf2_putone_(const ZF_FileHead* pstFileHead,
                const char         szFileName[],
                char               scType);         /* ����һ���ļ�                 */
int zf2_puttwo_(const ZF_FileHead* pstFileHead,
                const char         szFileNameF[],
                char               scTypeF,
                const char         szFileNameS[],
                char               scTypeS);        /* ���������ļ�                 */
int zf2_putmulti_(const ZF_FileHead* pstFileHead,
                  int                siFileNum,
                  const char*        szFileName[],
                  char               scType[]);     /* ���Ͷ���ļ�                 */
int zf2_getone_(const ZF_FileHead* pstFileHead,
                const char         szFileName[],
                const char         szFileNameS[]);  /* ��ȡ�����ļ�                 */
int zf2_getmulti_(const ZF_FileHead* pstFileHead,
                  int                siFileNum,
                  const char*        szFileName[],
                  const char         szFileNameS[]);/* ��ȡ����ļ�                 */
void zf2_perror_(int         siErrCode,
                 const char  szErrPre[]);           /* ��ȡ����˵��                 */
char* zf2_strerr_(int siErrCode);                   /* ��ȡ����˵��                 */

#ifdef __cplusplus
}
#endif
/************************************************************************************/


#endif
