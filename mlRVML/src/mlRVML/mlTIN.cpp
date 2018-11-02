/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlTIN.cpp
* @date 2012.01
* @author ������ zhangchy@irsa.ac.cn
* @brief ��������������ʵ���ļ�
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*/
#include "mlTIN.h"
#include "Triangle.h"
#include "stdio.h"
#include <vector>
#include "mlGdalDataset.h"
using std::vector;


/**
 *@fn ~CmlTIN
 *@date 2011.11
 *@author ������
 *@brief TIN�๹�캯��
 *@version 1.1
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
CmlTIN::CmlTIN()
{
    m_pt2List = NULL;
    m_ptZList = NULL;
    //ctor
}


/**
 *@fn ~CmlTIN
 *@date 2011.11
 *@author ������
 *@brief TIN����������
 *@version 1.1
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
CmlTIN::~CmlTIN()
{
    //   dtor
    if(m_tri.edgeList != NULL)
    {
        free(m_tri.edgeList);
        m_tri.edgeList = NULL;
    }
    if(m_tri.edgeMarkList != NULL)
    {
        //delete []m_tri.edgeMarkList;
        free(m_tri.edgeMarkList);
        m_tri.edgeMarkList = NULL;

    }
    if(m_tri.holeList != NULL)
    {
        //delete [] m_tri.holeList;
        free(m_tri.holeList);
        m_tri.holeList = NULL;
    }
    if(m_tri.neighborList != NULL)
    {
        // delete [] m_tri.neighborList;
        free(m_tri.neighborList);
        m_tri.neighborList = NULL;
    }
    if(m_tri.normList != NULL)
    {
        //delete [] m_tri.normList;
        free(m_tri.normList);
        m_tri.normList = NULL;
    }
    if(m_tri.pointAttrList != NULL)
    {
        // delete [] m_tri.pointAttrList;
        free(m_tri.pointAttrList);
        m_tri.pointAttrList = NULL;
    }
//    if( m_tri.pointList != NULL)
//    {
//        //delete[] m_tri.pointList;
//        free(m_tri.pointList);
//        m_tri.pointList = NULL;
//    }
    if(m_tri.pointMarkList != NULL)
    {
        //delete []m_tri.pointMarkList;
        free(m_tri.pointMarkList);
        m_tri.pointMarkList = NULL;
    }
    if(m_tri.regionList != NULL)
    {
        //delete []m_tri.regionList;
        free(m_tri.regionList);
        m_tri.regionList = NULL;
    }
    if(m_tri.segMarkList != NULL)
    {
        //delete [] m_tri.segMarkList;
        free(m_tri.segMarkList);
        m_tri.segMarkList = NULL;
    }
    if(m_tri.segmentList != NULL)
    {
        //delete[] m_tri.segmentList;
        free(m_tri.segmentList);
        m_tri.segmentList = NULL;
    }
    if(m_tri.triAreaList != NULL)
    {
        //delete[] m_tri.triAreaList;
        free(m_tri.triAreaList);
        m_tri.triAreaList = NULL;
    }
    if(m_tri.triAttrList != NULL)
    {
        //delete[] m_tri.triAreaList;
        free(m_tri.triAreaList);
        m_tri.triAreaList = NULL;
    }
    if(m_tri.triList != NULL)
    {
        //delete[] m_tri.triList;
        free(m_tri.triList);
        m_tri.triList = NULL;
    }

    if(m_pt2List != NULL)
    {
        delete[] m_pt2List;
        m_pt2List = NULL;
    }

    if(m_ptZList != NULL)
    {
        delete[] m_ptZList;
        m_ptZList = NULL;
    }

}
/** @brief Build2By2DPt
  *
  * @todo: document this function
  */


/**
 *@fn Build2By2DPt
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


bool CmlTIN::Build2By2DPt(DOUBLE* ptList, SLONG lPtNum)
{
    if( m_pt2List != NULL )
    {
        return false;
    }

    m_pt2List = new double[2*lPtNum];

    m_nPtNum = lPtNum;

    memcpy( m_pt2List, ptList, sizeof(double)*2*lPtNum );

    triangulateio in, mid;
    in.numOfPoints = lPtNum;
    in.pointList = m_pt2List;

    in.pointAttrList = NULL;
    in.pointMarkList = NULL;
    in.numOfPointAttrs = 0;

    in.triList = NULL;
    in.triAttrList = NULL;
    in.triAreaList = NULL;

    in.neighborList = NULL;
    in.numOfTriangles = 0;
    in.numOfCorners = 0;
    in.numOfTriAttributes = 0;

    in.segmentList = NULL;
    in.segMarkList = NULL;
    in.numOfSegments = 0;

    in.holeList = NULL;
    in.numOfHoles = 0;

    in.regionList = NULL;
    in.numOfRegions = 0;

    in.edgeList = NULL;
    in.edgeMarkList = NULL;

    in.normList = NULL;         //used only with Voronoi diagram; out only
    in.numOfEdges = 0;

    memcpy(&mid,&in,sizeof(triangulateio));
    memcpy(&m_tri,&in,sizeof(triangulateio));
    triangulate("pczAenVQ",&in,&m_tri,&mid);


    return true;
}

/** @brief Build2By3DPt
  *
  * @todo: document this function
  */

/**
 *@fn Build2By3DPt
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

bool CmlTIN::Build2By3DPt(DOUBLE* ptList, SLONG lPtNum)
{
    if( ( m_pt2List != NULL ) || ( m_ptZList != NULL ) )
    {
        return false;
    }

    double *pt2dList = new double[lPtNum*2];
    m_ptZList = new double[lPtNum];

    for(UINT i=0; i<lPtNum; i++)
    {
        pt2dList[2*i] = *(ptList+3*i);
        pt2dList[2*i+1] = *(ptList+3*i+1);
    }

    Build2By2DPt(pt2dList,lPtNum);

    delete[] pt2dList;

    return true;
}

/**
 *@fn Build2By3DPt()
 *@date 2011.11
 *@author ������
 *@brief ������ά�㹹TIN ������������������TIN˽�г�Ա����m_tri��
 *@param vecPt ��ά������
 *@param lPtNum ����
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
bool CmlTIN::Build2By3DPt( vector<Pt3d> &vecPt )
{
    if( ( m_pt2List != NULL )||( m_ptZList != NULL) )
    {
        return false;
    }

    m_ptZList = new double[vecPt.size()];
    double *pPt2List = new double[vecPt.size()*2];

    for( UINT i = 0; i < vecPt.size(); ++i )
    {
        Pt3d ptTemp = vecPt[i];
        pPt2List[2*i] = ptTemp.X;
        pPt2List[2*i+1] = ptTemp.Y;
        m_ptZList[i] = ptTemp.Z;
    }
    Build2By2DPt( pPt2List, vecPt.size() );
    delete[] pPt2List;
    return true ;
}

    /**
     *@fn GetGridTriIndex()
     *@date 2011.11
     *@author �⿭
     *@brief ������������������ȡ����������
     *@param *pIndex ����ͼ���ַ
     *@param &vecAddPts ���������ܵ�㼯
     *@param rect DEM��Χ
     *@param dResolution �ֱ���
     *@param *pVecPtHole ��
     *@retval TRUE �ɹ�
     *@retval FALSE ʧ��
     *@version 1.1
     *@par �޸���ʷ��
     *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
     */
bool CmlTIN::GetCenterTriIndex(SINT *pIndex, vector<Pt3d> &vecAddPts , DbRect *rect,DOUBLE dResolution,vector<Pt2d> *pVecPtHole )
{
    UINT nTri = m_tri.numOfTriangles;
    if(nTri < 1)
    {
        return false;
    }
    //��ʼ����������
    for(UINT i = 0 ; i < nTri ;i++)
    {
        *(pIndex+i) = NULL_INDEX;
    }
    UINT vt[3];
    DOUBLE x[3],y[3];
    DbRect rectTri;
    // ������ֵ�����������ε�����
    for(UINT k = 0; k < nTri; k++)
    {
        double dCenterX , dCenterY;
        dCenterX = dCenterY = 0 ;
        // ȡ�����������ĵ�ƽ������
        for(ULONG i = 0; i < 3; i++)
        {
            vt[i] = m_tri.triList[3*k+i];
            x[i] = m_tri.pointList[2*vt[i]];
            dCenterX += x[i] ;
            y[i] = m_tri.pointList[2*vt[i]+1];
            dCenterY += y[i] ;
        }
        dCenterX /= 3 ;
        dCenterY /= 3 ;
        Pt3d ptTemp ;
        ptTemp.X = dCenterX ;
        ptTemp.Y = dCenterY ;
        //���������ε���Ӿ���
        ComputeTriangleRect(x,y,&rectTri);

        //��������β�������DEM��Χ�ڣ���ʼ��һѭ��
        if( ( rectTri.left > rect->right ) || ( rectTri.right < rect->left ) || ( rectTri.top < rect->bottom )
                || ( rectTri.bottom > rect->top ) )
        {
            continue;
        }
        // �жϵ��Ƿ�����ն���
        if( PointInPoly(dCenterX,dCenterY, pVecPtHole) )
        {
            continue;
        }
        // �жϵ��Ƿ����������ڣ�����������ֵ�����ĵ����
        if(PointInTriangle(dCenterX,dCenterY,x,y) != OUTER)
        {
            double dMinDis = MinVertexDis(dCenterX,dCenterY,x,y) ;
            if(dMinDis > (0.2*dResolution))
            {
                * (pIndex + k) = k;
                vecAddPts.push_back(ptTemp) ;
            }
        }
    }
    return true;
}
bool CmlTIN::GetCenterTriIndex(SINT *pIndex, vector<Pt3d> &vecAddPts , DbRect *rect,DOUBLE dResolution,vector<Polygon3d> *pVecPoly, vector<Pt2d> *pVecPtHole  )
{
    UINT nTri = m_tri.numOfTriangles;
    if(nTri < 1)
    {
        return false;
    }
    //��ʼ����������
    for(UINT i = 0 ; i < nTri ;i++)
    {
        *(pIndex+i) = NULL_INDEX;
    }
    UINT vt[3];
    DOUBLE x[3],y[3];
    DbRect rectTri;
    // ������ֵ�����������ε�����
    for(UINT k = 0; k < nTri; k++)
    {
        double dCenterX , dCenterY;
        dCenterX = dCenterY = 0 ;
        // ȡ�����������ĵ�ƽ������
        for(ULONG i = 0; i < 3; i++)
        {
            vt[i] = m_tri.triList[3*k+i];
            x[i] = m_tri.pointList[2*vt[i]];
            dCenterX += x[i] ;
            y[i] = m_tri.pointList[2*vt[i]+1];
            dCenterY += y[i] ;
        }
        dCenterX /= 3 ;
        dCenterY /= 3 ;
        Pt3d ptTemp ;
        ptTemp.X = dCenterX ;
        ptTemp.Y = dCenterY ;
        //���������ε���Ӿ���
        ComputeTriangleRect(x,y,&rectTri);

        //��������β�������DEM��Χ�ڣ���ʼ��һѭ��
        if( ( rectTri.left > rect->right ) || ( rectTri.right < rect->left ) || ( rectTri.top < rect->bottom )
                || ( rectTri.bottom > rect->top ) )
        {
            continue;
        }
        // �жϵ��Ƿ�����ն���
        if( PointInPoly(dCenterX,dCenterY, pVecPtHole) )
        {
            continue;
        }
        if( !PointInRegion( dCenterX, dCenterY, pVecPoly ) )
        {
            continue;
        }
        // �жϵ��Ƿ����������ڣ�����������ֵ�����ĵ����
        if(PointInTriangle(dCenterX,dCenterY,x,y) != OUTER)
        {
            double dMinDis = MinVertexDis(dCenterX,dCenterY,x,y) ;
            if(dMinDis > (0.2*dResolution))
            {
                * (pIndex + k) = k;
                vecAddPts.push_back(ptTemp) ;
            }
        }
    }
    return true;
}
//bool CmlTIN::GetGridTriIndex(SINT *pIndex, DOUBLE *pDisIndex , UINT nW,UINT nH, DbRect *rect,DOUBLE dResolution,vector<Pt2d> *pVecPtHole )
//{
//    UINT nTri = m_tri.numOfTriangles;
//    if(nTri < 1)
//    {
//        return false;
//    }
//
//    //��ʼ����������
//    for (UINT i = 0; i < nH; i++)
//    {
//        for(UINT j = 0 ; j < nW; j++)
//        {
//            *(pIndex+nW*i+j) = NULL_INDEX;
//        }
//    }
//
//    for (UINT i = 0; i < nH; i++)
//    {
//        for(UINT j = 0 ; j < nW; j++)
//        {
//            *(pDisIndex+nW*i+j) = NULL_INDEX;
//        }
//    }
//
//    UINT vt[3]; //������
//    DOUBLE x[3],y[3];
//    DbRect rectTri;
//
//    for(ULONG k = 0; k < nTri; k++)
//    {
//        for(ULONG i = 0; i < 3; i++)
//        {
//            vt[i] = m_tri.triList[3*k+i];
//            x[i] = m_tri.pointList[2*vt[i]];
//            y[i] = m_tri.pointList[2*vt[i]+1];
//
//        }
//        //���������ε���Ӿ���
//        ComputeTriangleRect(x,y,&rectTri);
//
//        //��������β�������DEM��Χ�ڣ���ʼ��һѭ��
//        if( ( rectTri.left > rect->right ) || ( rectTri.right < rect->left ) || ( rectTri.top < rect->bottom )
//                || ( rectTri.bottom > rect->top ) )
//        {
//            continue;
//        }
//
//        //��ʶ����
//        //������������Ӿ����������к�
//
//        SINT nMinX = SINT((rectTri.left - rect->left) / dResolution);
//        SINT nMinY = SINT((rectTri.bottom - rect->bottom) / dResolution);
//
//        //���������θ���DEM������
//        SINT nRows = ceil((rectTri.top - rectTri.bottom) / dResolution) + 1;
//        SINT nCols = ceil((rectTri.right - rectTri.left) / dResolution) + 1;
//
//         for(SINT i = nMinY + nRows - 1 ; i >= nMinY ; i--)
//        {
//            if( i < 0 || i > (nH-1) )
//            {
//                continue;
//            }
//            for(SINT j = nMinX; j < nMinX + nCols; j++)
//            {
//                if( j < 0 || j > (nW-1))
//                {
//                    continue;
//                }
//                //�ж��������Ƿ����ڶ��ڣ�
//                if( PointInPoly(rect->left + j*dResolution,rect->bottom + i*dResolution, pVecPtHole) )
//                {
//                    continue;
//                }
//
//                if(PointInTriangle(rect->left + j*dResolution,rect->bottom+i*dResolution,x,y) != OUTER)
//                {
//                    * (pIndex + nW*i + j) = k;
//                    * (pDisIndex + nW*i + j) = MinVertexDis(rect->left + j*dResolution,rect->bottom+i*dResolution,x,y) ;
//                }
//            }
//        }
//    }
//    return true;
//}

/**
 *@fn GetGridTriIndex()
 *@date 2011.11
 *@author �⿭
 *@brief ��������������
 *@param *pIndex ����ͼ���ַ
 *@param nW DEM���
 *@param nH DEM�߶�
 *@param rect DEM��Χ
 *@param dResolution �ֱ���
 *@param *pVecPtHole ��
 *@retval TRUE �ɹ�
 *@retval FALSE ʧ��
 *@version 1.1
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
bool CmlTIN::GetGridTriIndex(SINT *pIndex, UINT nW,UINT nH, DbRect *rect,DOUBLE dResolution,vector<Pt2d> *pVecPtHole )
{
    UINT nTri = m_tri.numOfTriangles;
    if(nTri < 1)
    {
        return false;
    }
    //��ʼ����������
    for (UINT i = 0; i < nH; i++)
    {
        for(UINT j = 0 ; j < nW; j++)
        {
            *(pIndex+nW*i+j) = NULL_INDEX;
        }
    }

    UINT vt[3]; //������
    DOUBLE x[3],y[3];
    DbRect rectTri;
    // ������ֵ�����������ε�����
    for(ULONG k = 0; k < nTri; k++)
    {
        for(ULONG i = 0; i < 3; i++)
        {
            vt[i] = m_tri.triList[3*k+i];
            x[i] = m_tri.pointList[2*vt[i]];
            y[i] = m_tri.pointList[2*vt[i]+1];

        }
        //���������ε���Ӿ���
        ComputeTriangleRect(x,y,&rectTri);

        //��������β�������DEM��Χ�ڣ���ʼ��һѭ��
        if( ( rectTri.left > rect->right ) || ( rectTri.right < rect->left ) || ( rectTri.top < rect->bottom )
                || ( rectTri.bottom > rect->top ) )
        {
            continue;
        }

        //��ʶ����
        //������������Ӿ����������к�

        SINT nMinX = SINT((rectTri.left - rect->left) / dResolution);
        SINT nMinY = SINT((rectTri.bottom - rect->bottom) / dResolution);

        //���������θ���DEM������
        SINT nRows = ceil((rectTri.top - rectTri.bottom) / dResolution) + 1;
        SINT nCols = ceil((rectTri.right - rectTri.left) / dResolution) + 1;

         for(SINT i = nMinY + nRows - 1 ; i >= nMinY ; i--)
        {
            if( i < 0 || i > (nH-1) )
            {
                continue;
            }
            for(SINT j = nMinX; j < nMinX + nCols; j++)
            {
                if( j < 0 || j > (nW-1))
                {
                    continue;
                }
                //�ж��������Ƿ����ڶ��ڣ�
                if( PointInPoly(rect->left + j*dResolution,rect->bottom + i*dResolution, pVecPtHole) )
                {
                    continue;
                }

                if(PointInTriangle(rect->left + j*dResolution,rect->bottom+i*dResolution,x,y) != OUTER)
                {
                    * (pIndex + nW*i + j) = k;
                }
            }
        }
    }
    return true;
}
bool CmlTIN::GetGridTriIndex(SINT *pIndex, UINT nW,UINT nH, DbRect *rect,DOUBLE dResolution,vector<Polygon3d> *pVecPoly, vector<Pt2d> *pVecPtHole)
{
    UINT nTri = m_tri.numOfTriangles;
    if(nTri < 1)
    {
        return false;
    }
    //��ʼ����������
    for (UINT i = 0; i < nH; i++)
    {
        for(UINT j = 0 ; j < nW; j++)
        {
            *(pIndex+nW*i+j) = NULL_INDEX;
        }
    }

    UINT vt[3]; //������
    DOUBLE x[3],y[3];
    DbRect rectTri;
    // ������ֵ�����������ε�����
    for(ULONG k = 0; k < nTri; k++)
    {
        for(ULONG i = 0; i < 3; i++)
        {
            vt[i] = m_tri.triList[3*k+i];
            x[i] = m_tri.pointList[2*vt[i]];
            y[i] = m_tri.pointList[2*vt[i]+1];

        }
        //���������ε���Ӿ���
        ComputeTriangleRect(x,y,&rectTri);

        //��������β�������DEM��Χ�ڣ���ʼ��һѭ��
        if( ( rectTri.left > rect->right ) || ( rectTri.right < rect->left ) || ( rectTri.top < rect->bottom )
                || ( rectTri.bottom > rect->top ) )
        {
            continue;
        }

        //��ʶ����
        //������������Ӿ����������к�

        SINT nMinX = SINT((rectTri.left - rect->left) / dResolution);
        SINT nMinY = SINT((rectTri.bottom - rect->bottom) / dResolution);

        //���������θ���DEM������
        SINT nRows = ceil((rectTri.top - rectTri.bottom) / dResolution) + 1;
        SINT nCols = ceil((rectTri.right - rectTri.left) / dResolution) + 1;

         for(SINT i = nMinY + nRows - 1 ; i >= nMinY ; i--)
        {
            if( i < 0 || i > (nH-1) )
            {
                continue;
            }
            for(SINT j = nMinX; j < nMinX + nCols; j++)
            {
                if( j < 0 || j > (nW-1))
                {
                    continue;
                }
                //�ж��������Ƿ����ڶ��ڣ�
                if( PointInPoly(rect->left + j*dResolution,rect->bottom + i*dResolution, pVecPtHole) )
                {
                    continue;
                }
                if( !PointInRegion(rect->left + j*dResolution,rect->bottom + i*dResolution, pVecPoly) )
                {
                    continue;
                }
                if(PointInTriangle(rect->left + j*dResolution,rect->bottom+i*dResolution,x,y) != OUTER)
                {
                    * (pIndex + nW*i + j) = k;
                }
            }
        }
    }
}
DOUBLE CmlTIN::MIN3(DOUBLE x1,DOUBLE x2,DOUBLE x3)
{
    DOUBLE min = MAX_DEM;
    if(x1 < min) min = x1;
    if(x2 < min) min = x2;
    if(x3 < min) min = x3;

    return min;
}

DOUBLE CmlTIN::MAX3(DOUBLE x1,DOUBLE x2,DOUBLE x3)
{
    DOUBLE max = MIN_DEM;
    if(x1 > max) max = x1;
    if(x2 > max) max = x2;
    if(x3 > max) max = x3;

    return max;

}

/**
 *@fn ComputeTriangleRect
 *@date 2011.11
 *@author ������
 *@brief ���������ε���Ӿ��� ע���˾��ε�left top right bottom���������½�Ϊԭ��
 *@param x ���������������x����
 *@param y ���������������y����
 *@retval *rect ��Ӿ���
 *@version 1.1
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
void CmlTIN::ComputeTriangleRect(DOUBLE *x,DOUBLE *y, DbRect *rect)
{
    rect->left =   MIN3(x[0],x[1],x[2]);
    rect->bottom = MIN3(y[0],y[1],y[2]);

    rect->right =  MAX3(x[0],x[1],x[2]);
    rect->top =    MAX3(y[0],y[1],y[2]);

    return;

}

/**
 *@fn MinVertexDis
 *@date 2011.11
 *@author �⿭
 *@brief ����㵽�����ε���С����
 *@param x ���������������x����
 *@param y ���������������y����
 *@param x0 ���x����
 *@param y0 ���y����
 *@retval dMinDis �㵽�����ε���С����
 *@version 1.1
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */

DOUBLE CmlTIN::MinVertexDis(DOUBLE x0,DOUBLE y0,DOUBLE *x,DOUBLE *y)
{
    double dMinDis = sqrt((x0 - x[0])*(x0 - x[0]) + (y0 - y[0])*(y0 - y[0]));
    for(SINT i = 1 ; i < 3 ; i++)
    {
        double dTemp = sqrt((x0 - x[i])*(x0 - x[i]) + (y0 - y[i])*(y0 - y[i]));
        if(dTemp < dMinDis)
        {
            dMinDis = dTemp ;
        }
    }
    return dMinDis ;
}

/**
 *@fn PointInTriangle
 *@date 2011.11
 *@author ������
 *@brief �жϵ��Ƿ�����������
 *@param x ���������������x����
 *@param y ���������������y����
 *@param x0 ���x����
 *@param y0 ���y����
 *@retval VERTEX ���������ε�һ������
 *@retval EDGE ���������εı���
 *@retval OUTER ������������
 *@retval INNER ������������
 *@version 1.1
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
POINT_TRIANGLE CmlTIN::PointInTriangle(DOUBLE x0,DOUBLE y0,DOUBLE *x,DOUBLE *y)
{
    // ����Ƿ��Ƕ���
    for(UINT i = 0; i < 3; i++)
    {
//        if((abs(x[0]- x[0]) < ZERO) && (abs(y0 - y[i]) < ZERO))  // change ,luoji error
        if((abs(x[0]- x[i]) < ZERO) && (abs(y0 - y[i]) < ZERO))
        {
            return VERTEX;
        }

    }

    //����Ƿ��ڱ���
    for(UINT i = 0; i < 3; i++)
    {
        if(abs((y0 - y[i]) * (x[(i+1)%3] - x[i]) - (x0 - x[i]) * (y[(i+1)%3] - y[i])) < ZERO)
        {
            return EDGE;
        }
    }

    for(UINT i = 0; i < 3; i++)
    {
        if(((y0 - y[i]) * (x[(i+1)%3] - x[i]) - (x0 - x[i]) * (y[(i+1)%3] - y[i])) < 0)
        {
            return OUTER;
        }

    }
    return INNER;
}


/**
 *@fn PointInPoly����
 *@date 2011.11
 *@author ������
 *@brief �жϵ��Ƿ��ڶ������
 *@param *vecPoly ����θ���������
 *@param x ���������������x����
 *@param y ���������������y����
 *@retval VERTEX ���������ε�һ������
 *@retval 0 �㲻�ڶ������
 *@retval ��0 ���ڶ������
 *@version 1.1
 *@par �޸���ʷ��
 *<����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
 */
UINT CmlTIN::PointInPoly(DOUBLE x,DOUBLE y,vector<Pt2d> *vecPoly)
{
    if(vecPoly == NULL)
    {
        return 0;
    }

    UINT i,j,c=0;
    UINT nvert = vecPoly->size();
    if(nvert > 1)
    {
        for(i=0,j = nvert-1; i < nvert; j = i++)
        {
            if ( ((vecPoly->at(i).Y>y) != (vecPoly->at(j).Y>y)) &&
                    (x < (vecPoly->at(j).X-vecPoly->at(i).X) * (y-vecPoly->at(i).Y) / (vecPoly->at(j).Y-vecPoly->at(i).Y) + vecPoly->at(i).X) )
            {
                c = !c;
            }

        }
    }
    return c;
}
UINT CmlTIN::PointInRegion(DOUBLE x,DOUBLE y,vector<Polygon3d> *pVecPoly)
{
    if(pVecPoly == NULL)
    {
        return 0;
    }

    for( UINT kk = 0; kk < pVecPoly->size(); ++kk )
    {
        vector<Pt3d> *vecPoly = &(pVecPoly->at(kk).vecVectex);
        UINT i,j, c = 0;
        UINT nvert = vecPoly->size();
        if(nvert > 1)
        {
            for(i=0,j = nvert-1; i < nvert; j = i++)
            {
                if ( ((vecPoly->at(i).Y>y) != (vecPoly->at(j).Y>y)) &&
                        (x < (vecPoly->at(j).X-vecPoly->at(i).X) * (y-vecPoly->at(i).Y) / (vecPoly->at(j).Y-vecPoly->at(i).Y) + vecPoly->at(i).X) )
                {
                    c = !c;
                }

            }
        }
        if( c > 0 )
        {
            return c;
        }
    }
    return 0;
}


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
UINT CmlTIN::GetNumOfCorners()
{
    return m_tri.numOfCorners;
}

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
UINT CmlTIN::GetNumOfTriangles()
{
    return m_tri.numOfTriangles;
}



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
bool CmlTIN::GetCornersByTriIndex(UINT tri_index,Pt3d* pPt3ds)
{

    if(SINT(tri_index) > m_tri.numOfTriangles)
    {
        return false;
    }

    for(UINT i=0; i<3; i++)
    {
        UINT nVtIndex = m_tri.triList[3*tri_index+i];
        /*pPt3ds[i].X = m_tri.pointList[3*nVtIndex];
        pPt3ds[i].Y = m_tri.pointList[3*nVtIndex+1];
        pPt3ds[i].Z = m_tri.pointList[3*nVtIndex+2];*/
        pPt3ds[i].X = m_pt2List[2*nVtIndex];
        pPt3ds[i].Y = m_pt2List[2*nVtIndex+1];
        pPt3ds[i].Z = m_ptZList[nVtIndex];

    }

    return true;
}


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
UINT* CmlTIN::GetTriList()
{
    return (UINT*)m_tri.triList;
}



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
bool CmlTIN::VertexNotInTriangle(SINT nVt,SINT *Vertexs)
{
    bool bIn = true;
    for(SINT i =0; i<3; i++)
    {
        if(Vertexs[i] == nVt)
        {
            bIn = false;
            break;
        }
    }

    return bIn;
}

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
DOUBLE* CmlTIN::GetPt2List()
{
    return m_pt2List;
}

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
DOUBLE* CmlTIN::GetPtZList()
{
    return m_ptZList;
}
bool CmlTIN::WriteToFiles( const SCHAR* strOutPath, DOUBLE dScale )
{
    FILE* pF = NULL;
    pF = fopen( strOutPath, "w" );
    if( pF == NULL )
    {
        return false;
    }
    fprintf( pF, "Number of Pts: %d\n", m_tri.numOfPoints );
    for( UINT i = 0; i < m_tri.numOfPoints; ++i )
    {
        Pt3d ptCur;
        ptCur.X = m_tri.pointList[2*i];
        ptCur.Y = m_tri.pointList[2*i+1];
        ptCur.Z = m_ptZList[i];
        fprintf( pF, "%d  %lf  %lf  %lf\n", i, ptCur.X*dScale, ptCur.Y*dScale, ptCur.Z );
    }
    fprintf( pF, "Number of Tri:  %d\n", m_tri.numOfTriangles );
    for( UINT i = 0; i < m_tri.numOfTriangles; ++i )
    {
        fprintf( pF, "%d  %d  %d  %d\n", i, m_tri.triList[3*i], m_tri.triList[3*i+1], m_tri.triList[3*i+2] );
    }
    fclose( pF );
    return  true;
}




