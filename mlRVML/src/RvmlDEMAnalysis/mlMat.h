/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlMat.h
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �����������ͷ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
#ifndef MLMAT_H_INCLUDED
#define MLMAT_H_INCLUDED

#include "../../3rdParty/opencv2.3/opencv.h"
#include "../../include/mlTypes.h"



/**
* @class CmlTemplateMat
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief դ��ģ����
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
//��դ��ṹ���Ե��ɾ��󿴴������д洢
template <typename T>
class CmlTemplateMat
{
public:
    /**
    * @fn CmlTemplateMat
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlTemplateMat��ղι��캯��
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlTemplateMat();
    /**
    * @fn CmlTemplateMat
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlTemplateMat���вι��캯��
    * @param Mat ��ʼ������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    CmlTemplateMat( const CmlTemplateMat<T> &Mat );
    /**
    * @fn ~CmlTemplateMat
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief CmlTemplateMat����������
    * @version 1.0
    * @return �޷���ֵ
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    ~CmlTemplateMat();
public:
    /**
    * @fn Initial
    * @date 2011.11.02
    * @author ���Ļ� whwan@irsa.ac.cn
    * @brief ��ʼ��դ��Ĵ�С
    * @param nH դ���
    * @param nW դ���
    * @retval TRUE �ɹ�
    * @retval FALSE ʧ��
    * @version 1.0
    * @par �޸���ʷ��
    * <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
    */
    bool Initial( const UINT nH, const UINT nW ) ;   //��ʼ��դ��Ĵ�С
    UINT GetW() const;                         //!<�õ�դ��Ŀ�
    UINT GetH() const;                         //!<�õ�դ��ĸ�
    UINT GetTSize() const;                     //!<�õ�դ�������
    T*  GetData() const;                      //!<�õ�դ�����ݵ�ͷָ��
    T   GetAt( const UINT nRow, const UINT nCol ) const ;    //!<�õ�դ���ĳ�����ֵ
    bool   SetAt( const UINT nRow, const UINT nCol, const T val );  //!<����դ���ĳ�����ֵ
    bool Fill( const T val );                 //!<��ĳֵ���դ��
    void DestoryAll();                  //!<ɾ��դ������������
    void DestoryDataBlock();            //!<ɾ��դ���ڵ����ݴ洢�飬������Ӧ�Ŀ�����Ϣ
    //���ö���ƥ��㴦��ʱ����������������ݡ�
    bool IsValid() const;                     //!<�ж��Ƿ�������ݿ�

    CmlTemplateMat<T>& operator=(CmlTemplateMat<T>& tmp); //!<���ƿ�������

protected:
    UINT m_nW;                               //!<���ݿ��
    UINT m_nH;                               //!<���ݿ��
    T* m_pData;                               //!<���ݿ�ͷָ��
    UINT m_nTSize;                               //!<դ������
    bool m_bIsNULL;                               //!<���ݿ��Ƿ�Ϊ��
};

//---------------------------------------------------------------------------
//��֧��ģ����ķ�����룬��ʵ����.h��
/**
* @fn CmlTemplateMat
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief CmlTemplateMat��ղι��캯��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
template <typename T>
CmlTemplateMat<T>::CmlTemplateMat()
{
    m_nH = 0;
    m_nW = 0;
    m_bIsNULL = true;
    m_pData = NULL;
    m_nTSize = 0;
};
/**
* @fn CmlTemplateMat
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief CmlTemplateMat���вι��캯��
* @param Mat ��ʼ������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
template <typename T>
CmlTemplateMat<T>::CmlTemplateMat( const CmlTemplateMat<T> &tmpMat )
{
    m_nH = 0;
    m_nW = 0;
    m_bIsNULL = true;
    m_pData = NULL;
    m_nTSize = 0;
    if( false == this->Initial( tmpMat.GetH(), tmpMat.GetW() ) )
    {
        return;
    }
    memcpy( this->GetData(), tmpMat.GetData(), this->GetTSize()*sizeof(T) );
};
/**
* @fn ~CmlTemplateMat
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief CmlTemplateMat����������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
template <typename T>
CmlTemplateMat<T>::~CmlTemplateMat()
{
    this->DestoryAll();
};
/**
* @fn Initial
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��ʼ��դ��Ĵ�С
* @param nH դ���
* @param nW դ���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
template <typename T>
bool CmlTemplateMat<T>::Initial( const UINT nH, const UINT nW )
{
    if( true != this->m_bIsNULL )
    {
        return false;
    }

    if( NULL == m_pData )
    {
        UINT nTSize = nW * nH;
        try
        {
            m_pData = new T[nTSize];
        }
        catch( const bad_alloc& e)
        {
            m_pData = NULL;
            return false;
        }
        m_nW = nW;
        m_nH = nH;
        m_nTSize = nTSize;
        m_bIsNULL = false;
        memset( m_pData, 0, m_nTSize );
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
UINT CmlTemplateMat<T>::GetH() const//!<�õ�դ��ĸ�
{
    return m_nH;
}

template <typename T>
UINT CmlTemplateMat<T>::GetW() const//!<�õ�դ��Ŀ�
{
    return m_nW;
}

template <typename T>
UINT CmlTemplateMat<T>::GetTSize() const//!<�õ�դ�������
{
    return m_nTSize;
}

template <typename T>
T* CmlTemplateMat<T>::GetData() const//!<�õ�դ�����ݵ�ͷָ��
{
    return m_pData;
}

template <typename T>
T CmlTemplateMat<T>::GetAt( const UINT nRow, const UINT nCol ) const//!<�õ�դ���ĳ�����ֵ
{
    assert( ( nRow < m_nH)&&( nCol < m_nW) );
    return m_pData[nRow * m_nW + nCol];
}

template <typename T>
bool CmlTemplateMat<T>::SetAt( const UINT nRow, const UINT nCol, const T val )//!<����դ���ĳ�����ֵ
{
    if( (nRow >= m_nH) || ( nCol >= m_nW ) )
    {
        return false;
    }

    T* pTmp = m_pData + nRow * m_nW + nCol;
    *pTmp = val;
    return true;
}

template <typename T>
bool CmlTemplateMat<T>::Fill( const T val )//!<��ĳֵ���դ��
{
    if( true == m_bIsNULL )
    {
        return false;
    }
    for( SINT i = 0; i < m_nH; ++i )
    {
        for( SINT k = 0; k < m_nW; ++i )
        {
            SetAt( i, k, val );
        }
    }
    return true;
}

template <typename T>
void CmlTemplateMat<T>::DestoryAll()//!<ɾ��դ������������
{
    DestoryDataBlock();
    m_nW = 0;
    m_nH = 0;
    m_nTSize = 0;
}

template <typename T>
void CmlTemplateMat<T>::DestoryDataBlock()//!<ɾ��դ���ڵ����ݴ洢�飬������Ӧ�Ŀ�����Ϣ
{
    if( NULL == m_pData )
    {
        return;
    }

    delete[] m_pData;
    m_pData = NULL;

    m_bIsNULL = true;
}

template <typename T>
bool CmlTemplateMat<T>::IsValid() const//!<�ж��Ƿ�������ݿ�
{
    return (!m_bIsNULL);
}

template <typename T>
CmlTemplateMat<T>& CmlTemplateMat<T>::operator=( CmlTemplateMat<T>& tmp )//!<���ƿ�������
{
    if( true != m_bIsNULL )
    {
        this->DestoryAll();
    }
    if( true == this->Initial( tmp.GetH(), tmp.GetW() ) )
    {
        memcpy( this->GetData(), tmp.GetData(), sizeof(T)*tmp.GetTSize() );
    }
    return *this;
};

//�������㹫�����������������Ͻ�Ϊԭ��
typedef CmlTemplateMat<DOUBLE> CmlMat;    //!<���󣨸����ͣ�

//ʹ�þ�����ǰ�Դ���ľ���---����----����ά�ȳ�ʼ��������
/**
* @fn mlMatTrans
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ת��
* @param pMatIn �������
* @param pMatOut �������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI(bool) mlMatTrans( CmlMat* pMatIn, CmlMat* pMatOut );
/**
* @fn mlMatAdd
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����ӷ�
* @param pMatInA �������A
* @param pMatInB �������B
* @param pMatOutC ����������C
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI(bool) mlMatAdd( CmlMat* pMatInA, CmlMat* pMatInB, CmlMat* pMatOutC );
/**
* @fn mlMatSub
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �������
* @param pMatInA �������A
* @param pMatInB �������B
* @param pMatOutC ����������C
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI(bool) mlMatSub( CmlMat* pMatInA, CmlMat* pMatInB, CmlMat* pMatOutC );
/**
* @fn mlMatMul
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ����˷�
* @param pMatInA �������A
* @param pMatInB �������B
* @param pMatOutC ����������C
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI(bool) mlMatMul( CmlMat* pMatInA, CmlMat* pMatInB, CmlMat* pMatOutC );
/**
* @fn mlMatInv
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��������
* @param pMatIn �������
* @param pMatOut �������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI(bool) mlMatInv( CmlMat* pMatIn,  CmlMat* pMatOut );
/**
* @fn mlMatDet
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ���������ʽֵ
* @param pMat �������
* @param dRes ����ʽ��ֵ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI(bool) mlMatDet( CmlMat* pMat, DOUBLE &dRes );
/**
* @fn mlMatSolveSVD
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief �ⷽ��A*x=B
* @param pMatInA �������A
* @param pMatInB �������B
* @param pMatOutX ����������X
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI(bool) mlMatCross3( CmlMat* pMatInA, CmlMat* pMatInB, CmlMat* pMatOutC );
/**
* @fn mlMatSVD
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief SVD�ֽ⣬A=U*W*V'
* @param pMatA �������A
* @param pMatU �������U
* @param pMatW �������W
* @param pMatV �������V
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI(bool) mlMatSolveSVD( CmlMat* pMatInA, CmlMat* pMatInB, CmlMat* pMatOutX );
/**
* @fn mlMatCross3
* @date 2011.11.02
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��ά�������
* @param pMatInA ������ά����A
* @param pMatInB ������ά����B
* @param pMatOutC ����������C
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
MLAPI(bool) mlMatSVD( CmlMat* pMatA, CmlMat* pMatU, CmlMat* pMatW, CmlMat* pMatV );
/**
* @fn CmlMat2CvMat
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��CmlMatת����CvMat
* @param pmlMat CmlMat�;���
* @param pcvMat CvMat�;���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool mlMat2CvMat( CmlMat* pmlMat, CvMat* &pcvMat);
/**
* @fn CvMat2mlMat
* @date 2011.11.02
* @author ���Ļ� whwan@irsa.ac.cn
* @brief ��CvMatת����CmlMat
* @param pcvMat CvMat�;���
* @param pmlMat CmlMat�;���
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
bool CvMat2mlMat( CvMat* pcvMat, CmlMat* pmlMat );

#endif // MLMAT_H_INCLUDED
