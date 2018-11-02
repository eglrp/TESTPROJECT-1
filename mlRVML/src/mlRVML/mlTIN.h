/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlTIN.cpp
* @date 2012.01
* @author ������ zhangchy@irsa.ac.cn
* @brief ��������������ʵ��ͷ�ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/

#ifndef CMLTIN_H
#define CMLTIN_H

#include "mlBase.h"
#include "Triangle.h"


/**
* @class CmlTIN
* @date 2011.11
* @author ������ zhangchy@irsa.ac.cn
* @brief �������������ඨ��
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*
*/
#define  MAX_DEM  1.0E+38
#define  MIN_DEM -1.0E+38
#define  EPSILON  0.0001
#define  MAX_TRI  65535
#define  ZERO 0.000001
#define  NULL_INDEX -10000

enum  POINT_TRIANGLE
{
	INNER =0,
	OUTER =1,
	EDGE =2,
	VERTEX =3
};

class CmlTIN
{
public:
    /**
     *@fn ~CmlTIN()
     *@date 2011.11
     *@author ������
     *@brief TIN�๹�캯��
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    CmlTIN();


    /**
     *@fn ~CmlTIN()
     *@date 2011.11
     *@author ������
     *@brief TIN����������
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    ~CmlTIN();
public:
    //2ά������
 //   bool Build2By2DPt( Pt2d* ptList, int64 lPtNum );
    /**
     *@fn Build2By2DPt()
     *@date 2011.11
     *@author ������
     *@brief ���ݶ�ά���꣨x��y������������ ������������������TIN˽�г�Ա����m_tri��
     *@param ptList ������ָ��
     *@param lPtNum ����
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    bool Build2By2DPt( DOUBLE* ptList, SLONG lPtNum); //2ά������ָ�룬��XY�洢

 //   bool Build2By3DPt( Pt3d* ptList, int64 lPtNum );

    /**
     *@fn Build2By3DPt()
     *@date 2011.11
     *@author ������
     *@brief ������ά�㹹TIN ������������������TIN˽�г�Ա����m_tri��
     *@param ptList ������ָ��,ÿ�������갴��x��y��z˳������
     *@param lPtNum ����
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    bool Build2By3DPt( DOUBLE* ptList, SLONG lPtNum ); //3ά������ָ�룬��XYZ�洢

    /**
     *@fn Build2By3DPt()
     *@date 2011.11
     *@author ������
     *@brief ������ά�㹹TIN ������������������TIN˽�г�Ա����m_tri��
     *@param vector<Pt3d> ��ά������
     *@param lPtNum ����
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    bool Build2By3DPt( vector<Pt3d> &vecPt ); //3ά������ָ�룬��XYZ�洢

   /**
     *@fn GetNumOfCorners()
     *@date 2011.11
     *@author ������
     *@brief ��ȡ�ǵ���Ŀ
     *@retval �ǵ���Ŀ
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    UINT GetNumOfCorners();

    /**
     *@fn GetNumOfTriangles()
     *@date 2011.11
     *@author ������
     *@brief ��ȡ��������Ŀ
     *@retval ��������Ŀ
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    UINT GetNumOfTriangles();

    /**
     *@fn GetCornersByTriIndex()
     *@date 2011.11
     *@author ������
     *@brief ���������������ŵõ������ǵ����λ����ֵ
     *@param tri_index ������������
     *@param pPt3ds ������������������
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    bool GetCornersByTriIndex(UINT tri_index,Pt3d* pPt3ds);

    /**
     *@fn GetTriList()
     *@date 2011.11
     *@author ������
     *@brief �õ�����������������
     *@retval ����������
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    UINT* GetTriList();

    /**
     *@fn GetPt2List()
     *@date 2011.11
     *@author ������
     *@brief �õ�������������2ά������
     *@retval 2ά������
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    DOUBLE* GetPt2List();

    /**
     *@fn GetPt2List()
     *@date 2011.11
     *@author ������
     *@brief �õ�������������Zֵ����
     *@retval Zֵ����
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    DOUBLE* GetPtZList();

    triangulateio* GetTri(){return &m_tri;};

    triangulateio m_tri;

    /**
     *@fn GetGridTriIndex()
     *@date 2011.11
     *@author ������
     *@brief ��������������
     *@param *pIndex ����ͼ���ַ
     *@param nW DEM���
     *@param nH DEM�߶�
     *@param tri ������ָ��
     *@param rect DEM��Χ
     *@param dResolution �ֱ���
     *@param *pVecPtHole ��
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    bool GetGridTriIndex(SINT *pIndex, UINT nW,UINT nH, DbRect *rect,DOUBLE dResolution,vector<Pt2d> *pVecPtHole = NULL );

    bool GetGridTriIndex(SINT *pIndex, UINT nW,UINT nH, DbRect *rect,DOUBLE dResolution,vector<Polygon3d> *pVecPoly = NULL, vector<Pt2d> *pVecPtHole = NULL );

//    bool GetGridTriIndex(SINT *pIndex, DOUBLE *pDisIndex , UINT nW , UINT nH, DbRect *rect,DOUBLE dResolution,vector<Pt2d> *pVecPtHole ) ;

        /**
     *@fn GetGridTriIndex()
     *@date 2011.11
     *@author �⿭
     *@brief ������������������ȡ����������
     *@param *pIndex ����ͼ���ַ
     *@param &vecAddPts ���������ܵ�㼯
     *@param *rect DEM��Χ
     *@param dResolution �ֱ���
     *@param *pVecPtHole ��
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    bool GetCenterTriIndex(SINT *pIndex, vector<Pt3d> &vecAddPts , DbRect *rect,DOUBLE dResolution,vector<Pt2d> *pVecPtHole) ;

    bool GetCenterTriIndex(SINT *pIndex, vector<Pt3d> &vecAddPts , DbRect *rect,DOUBLE dResolution,vector<Polygon3d> *pVecPoly = NULL, vector<Pt2d> *pVecPtHole = NULL ) ;

    /**
     *@fn PointInPoly����
     *@date 2011.11
     *@author ������
     *@brief �жϵ��Ƿ��ڶ������
     *@param *vecPoly ����θ���������
     *@param x,y,���x��y����
     *@retval VERTEX ���������ε�һ������
     *@retval 0 �㲻�ڶ������
     *@retval ��0 ���ڶ������
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    UINT PointInPoly(DOUBLE x,DOUBLE y,vector<Pt2d> *vecPoly);

    UINT PointInRegion(DOUBLE x,DOUBLE y,vector<Polygon3d> *pVecPoly);

    bool WriteToFiles( const SCHAR* strOutPath, DOUBLE dScale = 1.0 );
private:

    /**
     *@fn MIN3()
     *@date 2011.11
     *@author ������
     *@brief �����������Сֵ
     *@param x1,x2,x3 �������������
     *@retval ��������Сֵ
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    DOUBLE MIN3(DOUBLE x1,DOUBLE x2,DOUBLE x3);

    /**
     *@fn MAX3()
     *@date 2011.11
     *@author ������
     *@brief ������������ֵ
     *@param x1,x2,x3 �������������
     *@retval ��������Сֵ
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    DOUBLE MAX3(DOUBLE x1,DOUBLE x2,DOUBLE x3);
    /**
     *@fn ComputeTriangleRect()
     *@date 2011.11
     *@author ������
     *@brief ���������ε���Ӿ��� ע���˾��ε�left top right bottom���������½�Ϊԭ��
     *@param DOUBLE *x��DOUBLE *y ���������������x��y����
     *@retval *rect ��Ӿ���
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    void ComputeTriangleRect(DOUBLE *x, DOUBLE *y,DbRect *rect);

    /**
     *@fn PointInTriangle
     *@date 2011.11
     *@author ������
     *@brief �жϵ��Ƿ�����������
     *@param DOUBLE *x��DOUBLE *y ���������������x��y����
     *@param x0,y0,���x��y����
     *@retval VERTEX ���������ε�һ������
     *@retval EDGE ���������εı���
     *@retval OUTER ������������
     *@retval INNER ������������
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    POINT_TRIANGLE PointInTriangle(DOUBLE x0,DOUBLE y0,DOUBLE *x,DOUBLE *y);



    /**
     *@fn VertexNotInTriangle()
     *@date 2011.11
     *@author ������
     *@brief �жϵ��Ƿ��������εĶ���
     *@param nVt ���жϵ�������
     *@param Vertexs ��������������������
     *@retval TRUE ���������εĶ���
     *@retval FALSE �㲻�������ζ���
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    bool VertexNotInTriangle(SINT nVt,SINT *Vertexs);
    /**
     *@fn MinVertexDis
     *@date 2011.11
     *@author �⿭
     *@brief ����㵽�����ε���С����
     *@param DOUBLE *x��DOUBLE *y ���������������x��y����
     *@param x0,y0,���x��y����
     *@retval dMinDis �㵽�����ε���С����
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
    double MinVertexDis(DOUBLE x0,DOUBLE y0,DOUBLE *x,DOUBLE *y) ;
private:

    DOUBLE *m_pt2List;
    DOUBLE *m_ptZList;
    SLONG m_nPtNum;

};
#endif // CMLTIN_H
