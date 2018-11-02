
/**
\file       mcde_public.h
\brief      MCDE���̵�ȫ�ֱ�������ģ��

\author     xyh
\date       2012-09-26
\version    1.0
\note       UNIX/C
\par        �޸ļ�¼
- zzl    2012-09-06  ģ�齨��
*/

#ifndef  _MC_PUBLIC_H
#define  _MC_PUBLIC_H


// #define  DELAYTIME_STATION           10            /** ��վ����ʱ��                         */

// #define  CJTIMEDiF_GRAY              15            /** �Ҷ�ͼ�����������ϣ�����Ŀ�ɼ�ʱ��� ������ 20121023ԭ���� 5s */
// #define  CJTIMEDiF_FULL              10            /** ȫɫͼ����Ŀ�ɼ�ʱ��� ������ 20121023ԭ���� 8s               */
// #define  CJTIMEDiF_RGB               30            /** ��ɫͼ����Ŀ�ɼ�ʱ��� ������ 20121023ԭ���� 17s ---20s       */
//
// #define  FRAMESUM_GRAY               1192          /** �Ҷ�ͼ�����������ϣ�����ͼ����֡��   */
// #define  FRAMESUM_FULL               1450          /** ȫ��ȫɫͼ ����ͼ����֡��            */
// #define  FRAMESUM_RGB                5791          /** ȫ����ɫͼ ����ͼ����֡��            */

#define  ERROR_RTFRAMES              0.1           /** ����Ƕ�ң����ȡ��֡���������       */

#define  ICNI_CAMERALABEL_LEN        4             /** �����ʶ����                         */
#define  ICNI_REFFRAMELABEL_LEN      6             /** ����ϵ��ʶ����                       */




///*------------�ṹ����------------------*/

/**Ѳ����ͼ��ѡ��ƥ����Ϣ�ṹ */
typedef  struct  _ST_IMSI_TMIMGSTAT
{
    ST_MsgHead	stMsgHead;		                              /** ��Ϣͷ                                     */
    Uint32		  uiStandID;		                              /** վ�����                                   */
    Uint32    	uiFileType;		                              /** ͼ���ļ�����                               */
    Uint32		  uiIMGIndex;		                              /** ͼ�����                                   */
    Float64		  dA;		                                      /** ���ָ��չ���Ƕ�                           */
    Float64		  dH;		                                      /** ���ָ��ƫ����                             */
    Float64		  dP;		                                      /** ���ָ������                             */
    Uint8		    ucMatchType;		                            /** ƥ���־(0���ѳɹ�ƥ��;1������Ŀ;2������Ŀ)*/
    Sint8 		  szIMGFileName_Z[ICNI_MAX_FILENAME_LEN];	    /** ��Ŀͼ������                               */
    Uint32		  uiLostFrames_Z;		                          /** ��Ŀͼ��֡��                             */
    ST_Time		  stTakePhoTime_Z;		                        /** ��Ŀ����ʱ��                               */
    Uint32		  uiTakePhoTimeLJ_Z;		                      /** ��Ŀ����ʱ�䣨�ۼ��룩                     */
    Sint8		    szIMGFileName_Y[ICNI_MAX_FILENAME_LEN];	    /** ��Ŀͼ������                               */
    Uint32		  uiLostFrames_Y;		                          /** ��Ŀ����֡��                             */
    ST_Time		  stTakePhoTime_Y;		                        /** ��Ŀ����ʱ��                               */
    Uint32		  uiTakePhoTimeLJ_Y;		                      /** ��Ŀ����ʱ�䣨�ۼ��룩                     */

}ST_IMSI_TMIMGSTAT;



/**ң������ϵͳ�ļ�ͷ������Ϣ�ṹ*/
typedef  struct  _ST_YCZFILEHEAD
{
    Sint8		             szTaskName[ICNI_MISSNAME_LEN];               /**	��������                                   */
	  Sint8		             szObjName[ICNI_OBJNAME_LEN];                 /**	Ŀ�����                                   */
	  Uint32		           uiTaskCode;                                  /**	������                                     */
	  Uint32		           uiObjCode;          		                      /**	Ŀ����                                     */
	  Uint32		           uiFileType;                                  /**	��Ʒ������                                 */
	  Uint32		           uiStandID;					                          /**	վ�����                                $  */
	  ST_Time		           stBJTime;					                          /** ��������ʱ��                               */
	  ST_Time		           stTaskTime;					                        /**	��������ʱ��                               */
	  Sint8		             szPrtFileName[ICNI_MAX_FILENAME_LEN];        /** ��Ʒ��ʶ���ļ�����                         */
	  Uint32		           uiPrtSeqID;					                        /**	��Ʒ��ˮ��Ŀǰ����Դ��������ͷֱ��Ŷ� ??? */
	  Sint8 		           szRemark[12]; 				                        /**	��ע[��ѡ]                                 */

}ST_YCZFILEHEAD;


/**ͼ����TIFF��ʽ�����ļ�������Ϣ�ṹ*/
typedef  struct  _ST_IMGFILEHEAD
{
    Sint8                szStation[ICNI_MAX_DESTNAME_LEN];            /**  ��Ʒ��Դ����վ��ʶ��                  */
    Sint8			           szCameraMark[ICNI_CAMERALABEL_LEN];          /**  �����ʶ                              */
    Uint8		  	         ucLeftRightID;		                            /**  ����Ŀ��ʶ��0����Ŀ��1����Ŀ��2����Ŀ */
    Uint8		             ucOpt;                             		      /**  ѡ�ű�ʶ                          @   */
    Sint8		             szSSMatchFile[ICNI_MAX_FILENAME_LEN];		    /**  ͬվ����ļ�����ѡ��              @   */
    Sint8		             szOptMatchFile[ICNI_MAX_FILENAME_LEN];		    /**  ѡ������ļ�����ѡ��              @   */
    Uint8		  	         ucModel;		                                  /**  ����ģʽ                              */
    Sint8                szModel[15];
    ST_Time		           stTakePhoTime;		                            /**  ����ʱ��                              */
    Uint32		           uiTakePhoTimeLJ;		                          /**  ����ʱ�䣨�ۼ��룩����ʱ              */
    Float64		           dCamBGZY;		                                /**  ����ع������ͼ�����棩          $   */
    Float64	  	         dCamImgTime;			                            /**  ����ع�������ع�ʱ�䣩          $   */
    Uint8		  	         ucPixBit;	                                  /**  ����λ��                              */
    Uint32		           uiWidth;	                                    /**  ͼ��ֱ��ʣ���                      */
    Uint32		           uiHeight;	       	                          /**  ͼ��ֱ��ʣ��ߣ�                      */
    Sint8		  	         szRefFrame[ICNI_REFFRAMELABEL_LEN];	        /**  ����ϵ��ʶ                        $   */
    Float64		           dLog;		                                    /**  ����ʱ������λ�þ���              $   */
    Float64		           dLat;		                                    /**  ����ʱ������λ��ά��              $   */
    Float64		           dHeight;	                                    /**  ����ʱ������λ�ø߶�              $   */
    Float64		           dPosX;		                                    /**  ����ʱ������λ��X                 $   */
    Float64		           dPosY;		                                    /**  ����ʱ������λ��Y                 $   */
    Float64		           dPosZ;		                                    /**  ����ʱ������λ��Z                 $   */
    Float64		           dRoll;	                                      /**  -180~180	����ʱ��������̬�������� $   */
    Float64		           dPitch;	                                    /**  -180~180	����ʱ��������̬�������� $   */
    Float64		           dAzimuth;	                                  /**  -180~180	����ʱ��������̬��ƫ���� $   */
    Float64		           dSunAL;		                                  /**  ����̫���߶Ƚ�                    $   */
    Float64		           dSunEL;		                                  /**  ����̫����λ��                    $   */
    Float64		           dSunAB;		                                  /**  ����̫���߶Ƚ�                    $   */
    Float64		           dSunEB;		                                  /**  ����̫����λ��                    $   */
    Float64		           dA;		                                      /**  ���ָ��չ���Ƕȣ���ѡ��          $   */
    Sint8                szAFlag[10];                                 /**  ���ָ��չ���Ƕ�������Դ��ʶ      $   */
    Float64		           dH;		                                      /**  ���ָ��ƫ����                    $   */
    Sint8                szHFlag[10];                                 /**  ���ָ��ƫ����������Դ��ʶ        $   */
    Float64		           dP;		                                      /**  ���ָ������                    $   */
    Sint8                szPFlag[10];                                 /**  ���ָ������������Դ��ʶ        $   */
    Uint32		           uiLostFrames;                                /**  ��֡��                                */

}ST_IMGFILEHEAD;


/** ����ָ��ṹ */
typedef struct _ST_LINK
{
	  ST_YCZFILEHEAD*			 pstYCZFileHead;                              /** ң������ϵͳ�ļ�ͷ������Ϣ�ṹ_ָ��     */
    ST_IMGFILEHEAD*			 pstImgFileHead;                              /** ͼ����TIFF��ʽ�����ļ�������Ϣ�ṹ_ָ�� */
    Uint32		           uiSysTime;		                                /** ϵͳʱ��(�ۻ���)                        */
    Uint8                ucQueryDB;                                   /** ����д���ݿ��ѯ���� 0:δ��, 1:����     */
	  struct _ST_LINK*	   pre;
	  struct _ST_LINK*	   next;

}ST_LINK;


/** ������нṹ */
typedef struct _ST_QUE
{
	  pthread_mutex_t		   Mutex;
	  ST_LINK*			       head;
	  ST_LINK*			       tail;
	  ST_LINK*			       find;

}ST_QUE;


/** Ѳ������Զ�λ����ļ��ṹ */
typedef struct  _ST_IFLIRAPAST
{
	  ST_YCZFILEHEAD		   stFileHead;						                      /** �ļ�ͷ                                 */
    Sint8		             szMacroNum[ICNI_TKPLANNUM_LEN];	            /** ����滮���                           */
    Sint8		             szCyNum[ICNI_CYPLANNUM_LEN];  	              /** ���ڹ滮���                           */
    Sint8		             szUnNum[ICNI_UNPLANNUM_LEN];  	              /** ��Ԫ�滮���                           */
    Sint8		             szPosRefFrame[ICNI_REFFRAMELABEL_LEN];       /** λ���������ϵ��ʶ                     */
    Float64		           dCurWorkCSX;		                              /** ��������ϵԭ��������ȫ������ϵ�µ�X    */
    Float64		           dCurWorkCSY;		                              /** ��������ϵԭ��������ȫ������ϵ�µ�Y    */
    Float64		           dCurWorkCSZ;		                              /** ��������ϵԭ��������ȫ������ϵ�µ�Z    */
    Uint8		             ucLocateModel;	                              /** ��λģʽ                               */
    Uint8		             ucLocateOpt;		                              /** ѡ�Ž����ʶ                           */
    Sint8		             szDataTime[25];     	                        /** ��λ��Ԫʱ�䣨����ʱ����ʽ��xxxx-xx-xxTxx:xx:xx.xxxx */
    Float64		           dX;		                                      /** ��������ϵ��Xλ��                      */
    Float64		           dY;		                                      /** ��������ϵ��Yλ��                      */
    Float64		           dZ;		                                      /** ��������ϵ��Zλ��                      */
    Float64		           dLog;	                                      /** -180-180	����                         */
    Float64		           dLat;	                                      /** -90-90	γ��                           */
    Float64		           dHeight;		                                  /** �߶�                                   */
    Float64		           dRoll;		                                    /** X����ת�Ƕ�(����)                      */
    Float64		           dPitch;		                                  /** Y����ת�Ƕȣ�������                    */
    Float64		           dYaw;		                                    /** Z����ת�Ƕȣ�ƫ����                    */
    Float64		           dRMSX;		                                    /** Xλ�÷���                              */
    Float64		           dRMSY;		                                    /** Yλ�÷���                              */
    Float64		           dRMSZ;		                                    /** Zλ�÷���                              */
    Float64		           dRMS;		                                    /** �ܵ�λ�÷���                           */
    Float64		           dRMSRoll;	                                  /** �����Ƿ���                             */
    Float64		           dRMSPitch;	                                  /** �����Ƿ���                             */
    Float64		           dRMSYaw;		                                  /** ƫ���Ƿ���                             */
    Float64		           dRMSAtt;		                                  /** ��̬����                               */
    Float64		           dSunAL;	                                    /** ����̫����λ��                         */
    Float64		           dSunEL;		                                  /** ����̫���߶Ƚ�                         */
    Float64		           dSunAB;		                                  /** ����̫����λ��                         */
    Float64		           dSunEB;		                                  /** ����̫���߶Ƚ�                         */

}ST_IFLIRAPAST;


/** ��ѯ���ݿ�����Ϣ�ṹ */
typedef  struct  _ST_QUERYDBINFOR
{
    Uint32		           uiTakePhoTimeLJ;		                         /**  ����ʱ�䣨�ۼ��룩����ʱ              */
    Uint32		           uiFileType;                                 /**	��Ʒ������                            */
    Uint32		           uiStandID;					                         /**	վ�����                              */
    Uint8		  	         ucLeftRightID;		                           /**  ����Ŀ��ʶ��0����Ŀ��1����Ŀ��2����Ŀ */
    Float64		           dCamBGZY;		                               /**  ����ع������ͼ�����棩              */
    Float64	  	         dCamImgTime;			                           /**  ����ع�������ع�ʱ�䣩              */
    Sint8		  	         szRefFrame[ICNI_REFFRAMELABEL_LEN];	       /**  ����ϵ��ʶ                            */
    Float64		           dLog;		                                   /**  ����ʱ������λ�þ���                  */
    Float64		           dLat;		                                   /**  ����ʱ������λ��ά��                  */
    Float64		           dHeight;	                                   /**  ����ʱ������λ�ø߶�                  */
    Float64		           dPosX;		                                   /**  ����ʱ������λ��                      */
    Float64		           dPosY;		                                   /**  ����ʱ������λ��                      */
    Float64		           dPosZ;		                                   /**  ����ʱ������λ��                      */
    Float64		           dRoll;	                                     /**  -180~180	����ʱ��������̬��������    */
    Float64		           dPitch;	                                   /**  -180~180	����ʱ��������̬��������    */
    Float64		           dAzimuth;	                                 /**  -180~180	����ʱ��������̬��ƫ����    */
    Float64		           dSunAL;		                                 /**  ����̫���߶Ƚ�                        */
    Float64		           dSunEL;		                                 /**  ����̫����λ��                        */
    Float64		           dSunAB;		                                 /**  ����̫���߶Ƚ�                        */
    Float64		           dSunEB;		                                 /**  ����̫����λ��                        */
    Float64		           dA;		                                     /**  ���ָ��չ���Ƕȣ���ѡ��              */
    Sint8                szAFlag[10];                                /**  ���ָ��չ���Ƕ�������Դ��ʶ          */
    Float64		           dH;		                                     /**  ���ָ��ƫ����                        */
    Sint8                szHFlag[10];                                /**  ���ָ��ƫ����������Դ��ʶ            */
    Float64		           dP;		                                     /**  ���ָ������                        */
    Sint8                szPFlag[10];                                /**  ���ָ������������Դ��ʶ            */

}ST_QUERYDBINFOR;


/** ͼ�������Ϣ�ṹ */
typedef  struct  _ST_BASEINFOR
{
	  Uint32		           uiTakePhoTimeLJ;		                         /**  ����ʱ�䣨�ۼ��룩����ʱ              */
	  ST_Time		           stTakePhoTime;		                           /**  ����ʱ��                              */
    Uint32		           uiLostFrames;                               /**  ��֡��                                */

}ST_BASEINFOR;




/**--------------------------ȫ�ֱ���-----------------------------------**/

extern    Uint32              g_uiTaskCode;                           /**  ������                  */
extern    Uint32              g_uiObjCode;                            /**  Ŀ����                  */
extern    Sint32              g_siRunLp;                              /**  ���б�־                */
extern    Sint32              g_siQueID;                              /**  ���Ķ���ID              */


extern    ST_QUE              g_queMatch[3];                          /**  ƥ����Ϣ����[0]����;[1]ȫ��;[2]����*/
extern    Uint8               g_ucMatchFlag[3];                       /**  ƥ���־([0]����;[1]ȫ��;[2]����)----- 0:�ȴ�ƥ�䣻1������ƥ��  */

extern    Sint8               g_szHostName[256];                      /**  ������                  */
extern    Sint8               g_szFileRsltName[128];                  /**	 дͼ���ļ���·��        */
extern    Sint8               g_strLoadPath[128];                     /**  ͼ�����ļ��洢�����ַ*/


extern    Uint32              g_uiIMGIndex[3];                        /**  ͼ��ͳ�Ƽ��� [0]����;[1]ȫ��;[2]����  */
extern    Uint32              g_uiFrameRate;                          /** ����֡Ƶ */


extern    Uint32              g_uiMatchTimeGray;                      /**  8λ�Ҷ�ͼ�񣨵��������ϣ�����Ŀ�ɼ�ʱ���   */
extern    Uint32              g_uiMatchTimeFull;                      /**  ȫ��ȫɫͼ������Ŀ�ɼ�ʱ���   */
extern    Uint32              g_uiMatchTimeColor;                     /**  ȫ����ɫͼ������Ŀ�ɼ�ʱ���   */
extern    Uint32              g_uiWaitTimeGray;                       /**  8λ�Ҷ�ͼ�����������ϣ�ƥ��ȴ�ʱ��   */
extern    Uint32              g_uiWaitTimeFull;                       /**  ȫ��ȫɫͼ��ƥ��ȴ�ʱ��   */
extern    Uint32              g_uiWaitTimeColor;                      /**  ȫ��ȫɫͼ��ƥ��ȴ�ʱ��   */

#endif
