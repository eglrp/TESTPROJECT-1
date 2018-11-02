#ifndef __PANODATA__
#define __PANODATA__

using namespace std;

typedef unsigned char           UCHAR;  //!>�޷���8λ����
typedef char                    SCHAR;  //!>�з���8λ����
typedef unsigned short int      USHORT; //!>�޷���16λ����
typedef signed short int        SSHORT; //!>�з���16λ����
typedef unsigned int            UINT;   //!>�޷���32λ����
typedef signed int              SINT;   //!>�з���32λ����
#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64 

#else
typedef unsigned long long int  ULONG;  //!>�޷���64λ����
#endif

typedef signed long long int    SLONG;  //!>�з���64λ����
typedef float                   FLOAT;  //!>32λ������
typedef double                  DOUBLE; //!>64λ������
typedef UCHAR                   BYTE;   //!>�޷���8λ�ַ���

/**
* @struct PT2
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��ά��ṹ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
//template <typename T>
//struct PT2
//{
//    T X, Y;//!>��X,Y����
//    ULONG lID;//!>�����
//    BYTE byType;
//    PT2()
//    {
//        memset(this, 0, 2*sizeof(T));
//        lID = 0;
//        byType = 0;
//    }
//};

//typedef PT2<DOUBLE> Pt2d;//!>��άDOUBLE�ͽṹ��
//
//typedef struct tagPanoPt3d
//{
//    double X, Y, Z;//!>��ά��ṹ
//    string ID;//!>��ά����
//
//    tagPanoPt3d()
//    {
//        memset(this, 0, 3*sizeof(double));
//    }
//} PanoPt3d;

//typedef enum enPanoCamType
//{
//    NULL_Cam = 0,//!>������
//    Pan_Cam = 1, //!>ȫ�����
//    Nav_Cam = 2  //!>�������
//
//} PANOCAMTYPE;
//
//
//struct PanoOriAngle
//{
//    DOUBLE omg;//!>��X��ת��
//    DOUBLE phi;//!>��Y��ת��
//    DOUBLE kap;//!>��Z��ת��
//    PanoOriAngle()
//    {
//        omg = phi = kap = 0.0;
//    }
//};
//
//typedef struct struPanoExteriorOrientation
//{
//    PanoPt3d pos;//!>�ⷽλ��Ԫ��
//    PanoOriAngle ori;//!>�ⷽλ��Ԫ��
//} PanoExOriPara;
//
//typedef struct struPanoSINTeriorOrientation
//{
//    DOUBLE f;//!>����
//    DOUBLE x;//!>����������x
//    DOUBLE y;//!>����������y
//    DOUBLE k1;//!>�������ϵ��k1
//    DOUBLE k2;//!>�������ϵ��k2
//    DOUBLE k3;//!>�������ϵ��k3
//    DOUBLE p1;//!>�������ϵ��p1
//    DOUBLE p2;//!>�������ϵ��p2
//    DOUBLE alpha;//!>��������ϵ��alpha
//    DOUBLE beta;//!>��������ϵ��beta
//    struPanoSINTeriorOrientation()
//    {
//        f = x = y = k1 = k2 = k3 = p1 = p2 = alpha = beta = 0.0;
//    }
//
//} PanoInOriPara;
//
//typedef struct tagPanoCamInfo
//{
//    PANOCAMTYPE CamType;
//    PanoInOriPara inOriL;
//    PanoInOriPara inOriR;
//    SINT nLW;
//    SINT nLH;
//    SINT nRW;
//    SINT nRH;
//}PANOCAMINFO;
//
//
//typedef struct tagPanoStruOriImageInfo
//{
//    SINT nSiteID;//!>վ�����
//    PANOCAMTYPE CamType;//!>�������
//    UINT nW;//!>Ӱ���
//    UINT nH;//!>Ӱ���
//    SINT nRollID;//!>Ӱ��Ȧ��
//    SINT nImgID;//!>Ӱ�����
//    string strName;//!>Ӱ����
//    string strImgPath;//!>Ӱ��·��
//    PanoInOriPara inOri;//!>Ӱ���ڷ�λ
//    PanoExOriPara exOri;//!>Ӱ���ⷽλ
//    SINT nImgLevel; //!>Ӱ�����ͣ�1ΪԭʼӰ��2Ϊ����Ӱ��
//    UINT nImgIndex;//!>Ӱ��index
//    tagPanoStruOriImageInfo()
//    {
//        nSiteID = -1;
//        CamType = NULL_Cam;
//        nRollID = -1;
//        nImgID = -1;
//        strImgPath = "";
//        nImgLevel = -1;
//        nImgIndex = 0;
//    }
//
//} OriImgInfo;

//typedef struct tagImgPtSet
//{
//    OriImgInfo imgInfo;
//    vector< Pt2d > vecPts;
//}panoImgPtSet;

#endif
