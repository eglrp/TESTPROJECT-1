/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlDemAnalyse.h
* @date 2011.11.18
* @author ��Ρ liwei@irsa.ac.cn
* @brief  ���η���ģ����ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef CMLDEMANALYSE_H
#define CMLDEMANALYSE_H
#include "mlGdalDataset.h"
#include "mlRasterBlock.h"
#include "mlGeoRaster.h"
#include "mlBlockCalculation.h"

#include "gdal_header.h"
#include "gdal/gdal.h"
#include "gdal/gdal_alg.h"
#include "gdal/cpl_conv.h"
#include "gdal/cpl_string.h"
#include "gdal/ogr_api.h"
#include "gdal/ogr_srs_api.h"

/**
* @struct POINTRASTER
* @date 2011.11.18
* @author ��Ρ liwei@irsa.ac.cn
* @brief ��ȡ�������ݵ�ṹ
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*
*/
struct POINTRASTER
{
        SLONG lx;
        SLONG ly;
        DOUBLE dz;
};

/**
* @class CmlDemAnalyse
* @date 2011.11.02
* @author ��Ρ liwei@irsa.ac.cn
* @brief ���η���������
* @version 1.1
* @par �޸���ʷ��
* <����>  <�޸�����>  <�汾��>  <��ϸ����>\n
*
*/
class CmlDemAnalyse
{
    public:
    /**
    * @fn CmlDemAnalyse
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief CmlDemAnalyse��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        CmlDemAnalyse();
        //CmlDemAnalyse(CmlGdalDataset* pSrcDataset);
       //CmlDemAnalyse(CmlRasterBlock* pSreRasterBlock);
    /**
    * @fn ~CmlDemAnalyse
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief CmlDemAnalyse����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        virtual ~CmlDemAnalyse();

    /**
    * @fn ComputeViewShedInterface
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief �����ӿ� ��������DEM���ݺ��ӵ����꣬����ͨ��ͼ
    * @param sInputDEM ����DEM�ļ�·��
    * @param nxLocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param ViewHight �ӵ�������ĸ߶�
    * @param sDestDEM ����ļ�·��
    * @param InverseHeight �Ƿ񽫸̷߳�ת
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeViewShedInterface( const SCHAR * sInputDEM, SINT nxLocation ,SINT nyLocation, DOUBLE dViewHight, const SCHAR * sDestDEM , bool InverseHeight = false);

    /**
    * @fn ComputeSlopeInterface
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief �����ӿ� ����DEM���ݣ��ͼ��㴰�ڴ�С������¶�
    * @param sInputDEM ����DEM�ļ�·��
    * @param nWindowSize ���㴰�ڴ�С
    * @param sDestDEM ����ļ�·��
    * @param dZfactor �߳��������ӣ�����DEMȡ������ֵ����dZfactorΪ��ʵ�߳�ֵ
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

        SINT ComputeSlopeInterface(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor );

    /**
    * @fn ComputeSlopeAspectInterface
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief �����ӿ� ����DEM���ݣ��ͼ��㴰�ڴ�С���������
    * @param sInputDEM  ����DEM�ļ�·��
    * @param nWindowSize ���㴰�ڴ�С
    * @param sDestDEM ����ļ�·��
    * @param dZfactor �߳��������ӣ�����DEMȡ������ֵ����dZfactorΪ��ʵ�߳�ֵ
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeSlopeAspectInterface(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor);

    /**
    * @fn ComputeObstacleMapInterface
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief �����ӿ� ����DEM���ݣ��ͼ��㴰�ڴ�С���ϰ�ͼ���������ϰ�ͼ
    * @param sInputDEM  ����DEM�ļ�·��
    * @param nWindowSize ���㴰�ڴ�С
    * @param sDestDEM ����ļ�·��
    * @param dZfactor �߳��������ӣ�����DEMȡ������ֵ����dZfactorΪ��ʵ�߳�ֵ
    * @param ObPara �ϰ�ͼ�����ṹ��
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeObstacleMapInterface(SCHAR * sInputDEM, SCHAR * sDestDEM, SINT nWindowSize ,DOUBLE dZfactor,ObstacleMapPara ObPara);

    /**
    * @fn ComputeContourInterface
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief �����ӿڣ� ����DEM���ݺ͵ȸ߾࣬����ȸ���ͼ
    * @param dHinterval  �ȸ߾�
    * @param strSrcfilename �����DEM�ļ�·��
    * @param strDstfilename �����shape�ļ�·��
    * @param bCNodata ��ʾ�Ƿ��Զ���Nodataֵ
    * @param dNodata ���bCNodata����Ϊtrue����dNodata ��ֵ�ڼ���ʱ��������Чֵ�Դ�
    * @param cAttrib����shape�ļ��̵߳��������ƣ�Ĭ��Ϊelev
    * @retval 1 �ɹ�
    * @retval -1 ʧ�ܣ�gdal�汾����
    * @retval -2 ʧ�ܣ��ȸ߾���������
    * @retval -3 ʧ�ܣ������ļ�����
    * @retval -4 ʧ�ܣ�����ļ�����
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeContourInterface(DOUBLE dHinterval,   SCHAR* strSrcfilename,   SCHAR* strDstfilename ,bool bCNodata = FALSE, DOUBLE dNodata = 0.0,  SCHAR* cAttrib = "elev");

    protected:
    private:
    // ����ֱ�߷���ͨ��
    /**
    * @fn ComputeNorthViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ��㱱�����ϵ�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight  �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeNorthViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn ComputeSouthViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ����Ϸ����ϵ�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight  �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeSouthViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn ComputeEastViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ��㶫�����ϵ�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeEastViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn ComputeWestViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ����������ϵ�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeWestViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn ComputeNorthEastViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ��㶫�������ϵ�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeNorthEastViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn ComputeSouthEastViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ��㶫�Ϸ����ϵ�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight  �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeSouthEastViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn ComputeNorthWestViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ������������ϵ�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight  �ӵ������������
    * @param pBlockOut ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeNorthWestViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn ComputeSouthWestViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ������Ϸ����ϵ�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeSouthWestViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn ComputeEightDirectionViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���˸������ϵ�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeEightDirectionViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);

     //��������ͨ��
    /**
    * @fn Compute1stQuadrantViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ����һ���޵�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT Compute1stQuadrantViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn Compute2ndQuadrantViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���ڶ����޵�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight  �ӵ������������
    * @param pBlockOut ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT Compute2ndQuadrantViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn Compute3rdQuadrantViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���������޵�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight  �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT Compute3rdQuadrantViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn Compute4thQuadrantViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���������޵�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT Compute4thQuadrantViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn Compute5thQuadrantViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���������޵�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT Compute5thQuadrantViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn Compute6thQuadrantViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���������޵�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT Compute6thQuadrantViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn Compute7thQuadrantViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���������޵�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

        SINT Compute7thQuadrantViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn Compute8thQuadrantViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���ڰ����޵�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight  �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT Compute8thQuadrantViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);
    /**
    * @fn ComputeEightQuadrantViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���˸����޵�ͨ����
    * @param nxlocation �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight  �ӵ������������
    * @param pBlockOut  ����Ŀ��Ӿ��󣬴�����������ΪGDT_Byte;
    * @param VisibleHeightBloc ����Ŀ��Ӳο��߶ȣ�������������ΪGDT_Float32
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeEightQuadrantViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight ,CmlRasterBlock* pBlockOut , CmlRasterBlock* pVisibleHeightBloc);

    /**
    * @fn ComputeZValueInReferencePlan
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ���������ο���ȷ����ƽ�棬����ˮƽλ����ƽ��ͶӰ�ϵĸ߳�ֵ
    * @param nx1 ��1���x����
    * @param ny1 ��1���y����
    * @param dz1 ��1���z����
    * @param nx2 ��2���x����
    * @param ny2 ��2���y����
    * @param dz2 ��2���z����
    * @param nx3 ��3���x����
    * @param ny3 ��3���y����
    * @param dz3 ��3���z����
    * @param nx ������x����
    * @param ny ������y����
    * @param dz ������z����
    * @retval true �ɹ�
    * @retval false ʧ�ܣ����㹲��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        bool ComputeZValueInReferencePlan(SINT nx1, SINT ny1, DOUBLE dz1,
                                            SINT nx2, SINT ny2, DOUBLE dz2,
                                            SINT nx3, SINT ny3, DOUBLE dz3,
                                            SINT nx, SINT ny, DOUBLE &dz);
    /**
    * @fn ComputeViewShed
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ��������Ĵ���rasterblock�ϵ������Լ��ӵ�ĸ߶ȼ���ͨ����
    * @param nxlocation  �ӵ�x����
    * @param nyLocation �ӵ�y����
    * @param dViewHight �ӵ������������
    * @param pBlockOut ������Ŀ��Ӿ���
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeViewShed(SINT nxlocation,SINT nyLocation, DOUBLE dViewHight, CmlRasterBlock* &pBlockOut);

    /**
    * @fn ComputeSlopeBlock
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ����DEM���ݿ�,�ͼ��㴰�ڴ�С������¶����ݿ�
    * @param pDEMBlock ����DEM���ݿ�
    * @param nWindowSize ���㴰�ڴ�С
    * @param pResultBlock ��������¶����ݿ�
    * @param dGridResolution �����ֱ���
    * @param dZfactor �߳��������ӣ��� ��DEMȡ������ֵ ���� dZfactor Ϊ��ʵ�߳�ֵ
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

        SINT ComputeSlopeBlock(CmlRasterBlock* pDEMBlock, SINT nWindowSize, CmlRasterBlock* pResultBlock,DOUBLE dGridResolution, DOUBLE dZfactor);

    /**
    * @fn FitPlaneByMatrix
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ������󣬼������ƽ��Ĳ���
    * @param matrix ����ľ���ֵ
    * @param Acoef ��ʾ ƽ�� Ax + By + C = z��Xϵ����������ԭ��Ϊ�������ĵ�
    * @param Bcoef ��ʾ ƽ�� Ax + By + C = z��Yϵ����������ԭ��Ϊ�������ĵ�
    * @param Ccoef ��ʾ ƽ�� Ax + By + C = z��C��������ԭ��Ϊ�������ĵ�
    * @param dGridResolution �����ֱ���
    * @param dZfactor �߳��������ӣ��� ��DEMȡ������ֵ ���� dZfactor Ϊ��ʵ�߳�ֵ
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT FitPlaneByMatrix(CmlMat* pMatrix, DOUBLE& dAcoef, DOUBLE& dBcoef , DOUBLE& dCcoef ,DOUBLE dGridResolution,DOUBLE dZfactor);


    /**
    * @fn ComputeRoughnessValue
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ����������ƽ��Ĳ���,�������ĵ��roughnessֵ
    * @param matrix ����ľ���ֵ
    * @param Acoef ��ʾ ƽ�� Ax + By + C = z��Xϵ����������ԭ��Ϊ�������ĵ�
    * @param Bcoef ��ʾ ƽ�� Ax + By + C = z��Yϵ����������ԭ��Ϊ�������ĵ�
    * @param Ccoef ��ʾ ƽ�� Ax + By + C = z��C��������ԭ��Ϊ�������ĵ�
    * @param dGridResolution �����ֱ���
    * @param dRoughnessValue ����õ��Ĵֲڶ�ֵ
    * @param dZfactor �߳��������ӣ��� ��DEMȡ������ֵ ���� dZfactor Ϊ��ʵ�߳�ֵ
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
        SINT ComputeRoughnessValue(CmlMat* pMatrix, DOUBLE dAcoef, DOUBLE dBcoef, DOUBLE dCcoef ,DOUBLE dGridResolution, DOUBLE& dRoughnessValue, DOUBLE dZfactor);



    /**
    * @fn ComputeStepValue
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief  ������󣬼������ֵ����Сֵ֮��
    * @param matrix ����ľ���ֵ
    * @param dDiffZ ����õ��ĸ̲߳�
    * @param dZfactor �߳��������ӣ��� ��DEMȡ������ֵ ���� dZfactor Ϊ��ʵ�߳�ֵ
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

        SINT ComputeStepValue(CmlMat* pMatrix, DOUBLE& dDiffZ, DOUBLE dZfactor);


    /**
    * @fn ComputeSlope
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ����DEM���ݣ��ͼ��㴰�ڴ�С������¶�
    * @param pSrcDataset ����dem����
    * @param nWindowSize ���㴰�ڴ�С
    * @param pDestDataset ��������¶�����
    * @param dGridResolution �����ֱ���
    * @param dZfactor �߳��������ӣ��� ��DEMȡ������ֵ ���� dZfactor Ϊ��ʵ�߳�ֵ
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

        SINT ComputeSlope(CmlGdalDataset* pSrcDataset, SINT nWindowSize, CmlGdalDataset* pDestDataset,DOUBLE dGridResolution, DOUBLE dZfactor);


    /**
    * @fn ComputeSlopeAspectBlock
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief   ����DEM���ݿ飬�ͼ��㴰�ڴ�С������������ݿ�
    * @param pDEMBlock ����DEM���ݿ�
    * @param nWindowSize ���㴰�ڴ�С
    * @param pResultBlock ��������������ݿ�
    * @param dGridResolution �����ֱ���
    * @param dZfactor �߳��������ӣ��� ��DEMȡ������ֵ ���� dZfactor Ϊ��ʵ�߳�ֵ
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

        SINT ComputeSlopeAspectBlock(CmlRasterBlock* pDEMBlock, SINT nWindowSize, CmlRasterBlock* pResultBlock,DOUBLE dGridResolution, DOUBLE dZfactor);

    /**
    * @fn ComputeSlopeAspect
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief ����DEM���ݣ��ͼ��㴰�ڴ�С���������
    * @param pSrcDataset ����dem����
    * @param nWindowSize ���㴰�ڴ�С
    * @param pDestDataset �����������
    * @param dGridResolution �����ֱ���
    * @param dZfactor  �߳��������ӣ��� ��DEMȡ������ֵ ���� dZfactor Ϊ��ʵ�߳�ֵ
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

        SINT ComputeSlopeAspect(CmlGdalDataset* pSrcDataset, SINT nWindowSize, CmlGdalDataset* pDestDataset, DOUBLE dGridResolution, DOUBLE dZfactor);

    /**
    * @fn ComputeObstacleMapBlock
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief  ����DEM���ݿ飬�ͼ��㴰�ڴ�С������ϰ�ͼ���ݿ�
    * @param pDEMBlock ����DEM���ݿ�
    * @param nWindowSize ���㴰�ڴ�С
    * @param pResultBlock �ϰ�ͼ���ݿ�
    * @param dGridResolution �����ֱ���
    * @param dZfactor �߳��������ӣ��� ��DEMȡ������ֵ ���� dZfactor Ϊ��ʵ�߳�ֵ
    * @param ObPara���ϰ�ͼ�����ṹ��
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

        SINT ComputeObstacleMapBlock(CmlRasterBlock* pDEMBlock, SINT nWindowSize, CmlRasterBlock* pResultBlock, DOUBLE dGridResolution, DOUBLE dZfactor,
                                     ObstacleMapPara ObPara);

    /**
    * @fn ComputeObstacleMap
    * @date 2011.11.02
    * @author ��Ρ liwei@irsa.ac.cn
    * @brief  ����DEM���ݣ��ͼ��㴰�ڴ�С������ϰ�ͼ
    * @param pSrcDataset ����dem����
    * @param nWindowSize ���㴰�ڴ�С
    * @param pDestDataset ����ϰ�ͼ����
    * @param dGridResolution �����ֱ���
    * @param dZfactor �߳��������ӣ��� ��DEMȡ������ֵ ���� dZfactor Ϊ��ʵ�߳�ֵ
    * @param ObPara���ϰ�ͼ�����ṹ��
    * @retval 1 �ɹ�
    * @retval ���� ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */

        SINT ComputeObstacleMap(CmlGdalDataset* pSrcDataset, SINT nWindowSize, CmlGdalDataset* pDestDataset, DOUBLE dGridResolution, DOUBLE dZfactor,
                                               ObstacleMapPara ObPara);

        //���ڼ���ͨ�ӷ��������դ�����ݿ�
        CmlRasterBlock* m_pSrcRasterBlock;

        //�����¶����򼰴ֲڶȵļ����դ�����ݿ�
        CmlGdalDataset* m_pSrcDataset;


};

#endif // CMLDEMANALYSE_H
