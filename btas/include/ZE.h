
/**
\file       ZE.h
\brief      ����״̬����
            
            �������ݴ�������ĸ�������룻
            �ṩͨ���������ȡ����˵���ı�̽ӿڡ�
            
\author     ������
\date       2009-11-18
\version    1.0
\note       WINDOSW/C
\par        �޸ļ�¼ 
            - ������ 2009-11-18 ģ�齨��
            
*/


#ifndef _ZE_H__
#define _ZE_H__


/************************** ������ **********************************/
#define ZE_NOINIT           -1          /* ����δ��ʼ��             */
#define ZE_INITSYN          -2          /* ��ʼ��ͬ������           */
#define ZE_MAPGSEC          -3          /* ӳ��ȫ�ֶδ���           */
#define ZE_INITADDR         -4          /* ��ʼ����ַ����           */
#define ZE_INITDEV          -5          /* ��ʼ���豸����           */
#define ZE_INITQUE          -6          /* ��ʼ�����д���           */
#define ZE_SYN              -7          /* ͬ����������             */
#define ZE_QUEID            -8          /* ����ID����               */
#define ZE_QUENUM           -9          /* ���и�������             */
#define ZE_QUEBUFLEN        -10         /* ���л��泤�ȴ���         */
#define ZE_QUEFULL          -11         /* ������                   */
#define ZE_SUBTYPE          -12         /* �������ʹ���             */
#define ZE_SUBNUM           -13         /* ���ĸ�������             */
#define ZE_SUBINFO          -14         /* ������Ϣ����             */
#define ZE_PROTYPE          -15         /* Э�����ʹ���             */
#define ZE_MSGTYPE          -16         /* ��Ϣ���ʹ���             */
#define ZE_TASKCODE         -17         /* ���������               */
#define ZE_OBJCODE          -18         /* Ŀ�������               */
#define ZE_CRTQUEDEV        -19         /* ���������豸����         */
#define ZE_SNDREQ           -20         /* ���Ϳ��������������     */
#define ZE_RCVRLY           -21         /* ���տ�������Ӧ�����     */
#define ZE_SNDBUF           -22         /* ���ͻ������             */
#define ZE_SNDBUFLEN        -23         /* ���ͻ��泤�ȴ���         */
#define ZE_HIGHSNDFRE       -24         /* ����Ƶ�ʳ���             */
#define ZE_FORBIDSND        -25         /* ��ֹ����                 */
#define ZE_WRITEDEV         -26         /* �豸д�����ݴ���         */
#define ZE_RCVBUF           -27         /* ���ջ������             */
#define ZE_RCVBUFLEN        -28         /* ���ջ��泤�ȴ���         */
#define ZE_READDEV          -29         /* �豸��ȡ���ݴ���         */
#define ZE_NODATA           -30         /* �豸������               */
#define ZE_AIOFUNC          -31         /* �첽I/O��ڴ���          */
#define ZE_SETAIO           -32         /* �����첽I/O����          */
#define ZE_QUECODE          -33         /* ���������               */
#define ZE_HOSTNAME         -34         /* ����������               */
#define ZE_PROCNAME         -35         /* ����������               */
#define ZE_LOCPATHTBLFULL   -36         /* ����·������             */
#define ZE_LOCFREETBLFULL   -37         /* ���ؿ��б���             */
#define ZE_REMPATHTBLFULL   -38         /* ����·������             */
#define ZE_REMFREETBLFULL   -39         /* ������б���             */
#define ZE_INITNET          -40         /* ��ʼ������������       */
#define ZE_PARA             -41         /* ��������                 */
#define ZE_GETUSER          -42         /* ��ȡFTP�˻�����          */
#define ZE_LOGIN            -43         /* ��¼��������             */
#define ZE_SETTYPE          -44         /* ���ô������ʹ���         */
#define ZE_SETPASV          -45         /* ���÷�����Ϊ����ģʽ���� */
#define ZE_DATACON          -46         /* �����������Ӵ���         */
#define ZE_SETRETR          -47         /* ���������ļ�����         */
#define ZE_SETSTOR          -48         /* �����ϴ��ļ�����         */
#define ZE_OPENFILE         -49         /* ���ļ�����             */
#define ZE_READFILE         -50         /* ���ļ�����               */
#define ZE_WRITEFILE        -51         /* д�ļ�����               */
#define ZE_READSOCK         -52         /* ��SOCK����               */
#define ZE_WRITESOCK        -53         /* дSOCK����               */
#define ZE_INITZM           -54         /* ��ʼ����Ϣ�������       */
#define ZE_GETHOSTNAME      -55         /* ��ȡ����������           */
#define ZE_GETPROCNAME      -56         /* ��ȡ����������           */
#define ZE_INDEX            -57         /* ��ȡ����ȫ�ֶ���������   */
#define ZE_ACCESS           -58         /* ԽȨ����                 */
#define ZE_UNLOAD           -59         /* ����δ����               */
#define ZE_PATH             -60         /* ����·������             */
#define ZE_RDCONF           -61         /* ��ȡ�����ļ�����         */
#define ZE_RATE             -62         /* ���ո��ʴ���             */
#define ZE_CMDLEN           -63         /* ����ȴ���             */
#define ZE_FILETYPE         -64         /* �ļ����ʹ���             */
#define ZE_FILENAME         -65         /* �ļ�������               */
#define ZE_DUPSTAT          -66         /* ���������״̬����       */
#define ZE_TRANSTYPE        -67         /* �������ʹ���             */
#define ZE_FILENOEXIST      -68         /* �ļ�������               */
#define ZE_GETROOTPATH      -69         /* ��ȡ�����·������       */
#define ZE_PATHNAME         -70         /* ·��������               */
#define ZE_GETSYSFILENAME   -71         /* ��ȡϵͳ�ļ�������       */
#define ZE_COPYFILE         -72         /* �����ļ�����             */
#define ZE_FILEHEAD         -73         /* �ļ�ͷ����               */
#define ZE_CONSVR           -74         /* ���ӷ���������           */
#define ZE_FILENUM          -75         /* �ļ���������             */
#define ZE_FILELEN          -76         /* �ļ����ȴ���             */
#define ZE_TARFILE          -77         /* ����ļ�����             */
#define ZE_UNTARFILE        -78         /* ����ļ�����             */
#define ZE_ZIPFILE          -79         /* ѹ���ļ�����             */
#define ZE_UNZIPFILE        -80         /* ��ѹ�ļ�����             */
#define ZE_HANDLER          -81         /* �������                 */
#define ZE_QRYCOND          -82         /* ��ѯ��������             */
#define ZE_QRYRSLT          -83         /* ��ѯ�������             */
#define ZE_POSITION         -84         /* ��Ч�α�                 */
#define ZE_NULL             -85         /* ��ֵ                     */
/********************************************************************/


/************************** �������� ********************************/
#ifdef __cplusplus
extern "C" {
#endif

void ze_perror(int        siErrCode,
               const char szErrPre[]);  /* ��ȡ����˵��             */
char* ze_strerr(int siErrCode);         /* ��ȡ����˵��             */

#ifdef __cplusplus
}
#endif
/********************************************************************/


#endif
