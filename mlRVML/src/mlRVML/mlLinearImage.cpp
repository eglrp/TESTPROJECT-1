/**
* @copyright Copyright(C), 2011-2012, PMRS Lab, IRSA, CAS
* @file mlLinearImage.cpp
* @date 2011.11.18
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��������Ӱ����Դ�ļ�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/

#include "mlLinearImage.h"
#define ML_PI   3.1415926535897932384626433832795
#define Moon_Radius 1737400

/**
* @fn CmlLinearImage
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CmlLinearImage��ղι��캯��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlLinearImage::CmlLinearImage()
{
    //ctor
}
/**
* @fn ~CmlLinearImage
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CmlLinearImage����������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlLinearImage::~CmlLinearImage()
{
    //dtor
}
/**
* @fn CmlCE1LinearImage
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CmlCE1LinearImage��ղι��캯��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlCE1LinearImage::CmlCE1LinearImage()
{

}
/**
* @fn ~CmlCE1LinearImage
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CmlCE1LinearImage����������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlCE1LinearImage::~CmlCE1LinearImage()
{

}
/**
* @fn CmlCE2LinearImage
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CmlCE2LinearImage��ղι��캯��
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlCE2LinearImage::CmlCE2LinearImage()
{

}
/**
* @fn ~CmlCE2LinearImage
* @date 2011.12.16
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CmlCE2LinearImage����������
* @version 1.0
* @return �޷���ֵ
* @par �޸���ʷ��
* <����>    <ʱ��>   <�汾���>    <�޸�ԭ��>\n
*/
CmlCE2LinearImage::~CmlCE2LinearImage()
{

}
/**
* @fn mlCE1InOrietation
* @date 2011.11.20
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CE-1����Ӱ���ڶ���
* @param vecPtsList �������
* @param pSatSio �ڶ�������ṹ��
* @param vecXY �ڶ��������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE1LinearImage::mlCE1InOrietation( vector<Pt2d> &vecPtsList, CE1IOPara *pSatSio, vector<Pt2d> &vecXY )
{
    //CE-1����Ӱ���ڶ��򣬽�����Ӱ��ƥ��ͬ�������к�ת��Ϊ��ƽ������
    //vecPtsList ����ʱΪ������к����꣬���ʱΪ��ƽ������
    //vecPtsList��һ�����кţ��ڶ������к�,�����Ͻ�����ϵ��
    /*����x���꣬Ϊһ����*/
    UINT i;
    DOUBLE x_val;
    Pt2d tmpSL, tmpXY;
    x_val = ( pSatSio->l0 - pSatSio->nCCD_line ) * pSatSio->pixsize - pSatSio->x0;
    if ( (pSatSio->nSample == 0) || (pSatSio->pixsize == 0) )
    {
        return false;
    }
    //����y���꣬���������ж���ͬ/
    //����ʱ�������򱱷��У�XΪ���з������ϣ�Y��ֱ��X����
    else if ( false == pSatSio->upflag )
    {
        for( i = 0; i < vecPtsList.size(); i++ )
        {
            tmpSL = vecPtsList.at(i);
            tmpXY.X = x_val;
            tmpXY.Y = ( pSatSio->s0 - tmpSL.X ) * pSatSio->pixsize + pSatSio->y0;
            vecXY.push_back(tmpXY);
        }
    }
    //����ʱ���ɱ����Ϸ��У�XΪ���з������£�Y��ֱ��X����
    else if( true == pSatSio->upflag )
    {
        for( i = 0; i < vecPtsList.size(); i++ )
        {
            tmpSL = vecPtsList.at(i);
            tmpXY.X = x_val;
            tmpXY.Y = ( tmpSL.X - pSatSio->s0 ) * pSatSio->pixsize - pSatSio->y0;
            vecXY.push_back(tmpXY);
        }
    }
    else
    {
        return false;
    }
    return true;
}
/**
* @fn mlCE2InOrietation
* @date 2012.03.01
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CE-2����Ӱ���ڶ���
* @param vecPtsList ����ʱΪ������к����꣬���ʱΪ��ƽ������
* @param pSatSio ����Ӱ���ڶ�������ṹ��
* @param vecXY ������Ľ�ƽ������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE2LinearImage::mlCE2InOrietation( vector<Pt2d> &vecPtsList, CE2IOPara *pSatSio, vector<Pt2d> &vecXY )
{
    //������Ӱ��ƥ��ͬ�������к�ת��Ϊ��ƽ������
    //����x���꣬Ϊһ����
    UINT i;
    DOUBLE x_val;
    Pt2d tmpSL, tmpXY;
    if ( ( pSatSio->AngleDeg == 0 ) || (pSatSio->f == 0) || (pSatSio->nSample == 0) || (pSatSio->pixsize == 0) )
    {
        return false;
    }
    else
    {
        x_val = pSatSio->x0 - tan( pSatSio->AngleDeg * ML_PI / 180.0 ) * pSatSio->f;
    }
    //����y���꣬���������ж���ͬ/
    //����ʱ���ɱ����Ϸ��У�XΪ���з������ϣ�Y��ֱ��X����
    if ( !pSatSio->upflag )
    {
        for( i = 0; i < vecPtsList.size(); i++ )
        {
            tmpSL = vecPtsList.at(i);
            tmpXY.Y = ( tmpSL.X - pSatSio->s0 ) * pSatSio->pixsize - pSatSio->y0;
            tmpXY.X = x_val;
            vecXY.push_back(tmpXY);

        }
    }
    //����ʱ�������򱱷��У�XΪ���з������ϣ�Y��ֱ��X����
    else if( pSatSio->upflag )
    {
        for( i = 0; i < vecPtsList.size(); i++ )
        {
            tmpSL = vecPtsList.at(i);
            //tmpXY.Y = pSatSio->y0 - ( tmpSL.X - pSatSio->s0 ) * pSatSio->pixsize;
            tmpXY.Y = ( pSatSio->s0 - tmpSL.X  ) * pSatSio->pixsize;
            tmpXY.X = x_val;
            vecXY.push_back(tmpXY);
        }
    }
    else
    {
        return false;
    }
    return true;
}
/**
* @fn mlCloseVal
* @date 2011.11.22
* @author ��һ�� ylliu@irsa.ac.cn
* @brief �������ٽ�ֵ
* @param A ����������
* @param trueval ĳ����ֵ
* @return indx ����A����trueval��ӽ�ֵ���±�
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
UINT mlCloseVal( CmlMat *A, DOUBLE trueval )
{
    //������������ĳһ����ֵ���ڽ���ֵ�������ظ�ֵ������A�е��±�
    DOUBLE minval = abs( A->GetAt( 0, 0 ) - trueval );
    UINT indx = 0;
    for( UINT i = 0; i < A->GetH()-1; i++ )
    {
        if( abs( A->GetAt( i + 1, 0 ) - trueval ) < minval )
        {
            minval = abs( A->GetAt( i + 1 ,0) - trueval );
            indx = i + 1;
        }
        else
        {
            continue;
        }
    }
    return indx;
}
/**
* @fn mlPolyA
* @date 2011.11.22
* @author ��һ�� ylliu@irsa.ac.cn
* @brief �������ʱ������ζ���ʽ����
* @param pTemp_time һάʱ������t
* @param MatA ��������ζ���ʽ����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool mlPolyA( CmlMat *pTemp_time, CmlMat* MatA )
{
    //���ݸ�����һά��ʱ�����鹹�����ζ���ʽ����
    for( UINT i = 0; i < pTemp_time->GetH(); i++ )
    {
        MatA->SetAt( i, 0, 1 ); //����ʽ������t0
        MatA->SetAt( i, 1, pTemp_time->GetAt(i,0)); //����ʽһ����t1
        MatA->SetAt( i, 2, MatA->GetAt( i, 1 ) * MatA->GetAt( i, 1 ) ); //����ʽ������t2
        MatA->SetAt( i, 3, MatA->GetAt( i, 2 ) * MatA->GetAt( i, 1 ) );  //����ʽ������t3
    }
    return true;
}
/**
* @fn mlinterEo
* @date 2011.11.22
* @author ��һ�� ylliu@irsa.ac.cn
* @brief �����ⷽλԪ�ؼ����Ӧʱ�䣬����Ӱ��ʱ���ڲ��Ӱ��ÿһ�е��ⷽλ
* @param pImg_time Ӱ��ʱ������
* @param pElement ĳһ���ⷽλԪ������
* @param pTime �ⷽλԪ�����ж�Ӧ��ʱ������
* @param pEo �ڲ���Ӱ���ⷽλԪ��
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool mlinterEo(CmlMat *pTime, CmlMat *pElement, CmlMat *pImg_time, CmlMat *pEo)
{
    UINT nScanline = pImg_time->GetH();
    //������img_time[0]ֵ���ڽ���time��λ��time[start_pos];
    UINT start_pos = mlCloseVal(pTime, pImg_time->GetAt(0,0));
    //������img_time[nscanline-1]ֵ���ڽ���time��λ��time[end_pos];
    UINT end_pos = mlCloseVal( pTime, pImg_time->GetAt(nScanline-1,0));
    UINT length = end_pos-start_pos+1;
    DOUBLE time_offset = (pImg_time->GetAt(0,0) < pImg_time->GetAt(nScanline-1,0))?pImg_time->GetAt(0,0):pImg_time->GetAt(nScanline-1,0);
    CmlMat MatL, Temp_time;
    MatL.Initial( length, 1 );
    Temp_time.Initial(length,1);
    UINT i;
    for( i = 0; i < length; i++ )
    {
        //����ʱ������
        Temp_time.SetAt(i, 0, ( pTime->GetAt(i + start_pos,0)-time_offset ) );
        //����L����
        MatL.SetAt( i, 0, pElement->GetAt(i + start_pos,0) );
    }

    CmlMat MatA, MatAT, MatATA, MatATL, InvATA, MatX;
    MatA.Initial( length, 4 );
    //����A����
    mlPolyA( &Temp_time, &MatA );
    //���inv(ATA)*ATL,�õ�X���󣬼�����ʽ���ϵ��
    mlMatTrans( &MatA, &MatAT );
    mlMatMul( &MatAT, &MatL, &MatATL );
    mlMatMul( &MatAT, &MatA, &MatATA );
    mlMatInv( &MatATA, &InvATA );
    mlMatMul( &InvATA, &MatATL, &MatX );

    //����Ӱ��ʱ�䣬����ÿһ��ɨ�����ⷽλ
    CmlMat MatA1;
    MatA1.Initial( nScanline, 4 );
    CmlMat pImg_temptime;
    pImg_temptime.Initial( pImg_time->GetH(), pImg_time->GetW() );
    for( i = 0; i < pImg_time->GetH(); i++ )
    {
        pImg_temptime.SetAt( i, 0, (pImg_time->GetAt(i,0)-time_offset) );
    }
    //���ɶ���ʽ����
    mlPolyA( &pImg_temptime, &MatA1 );
    //A*X = EO
    mlMatMul( &MatA1, &MatX, pEo );
    return true;
}
/**
* @fn mlGetEop
* @date 2011.11.22
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���������ݶ���ʽ�ڲ��ⷽλԪ��
* @param vecLineEo ԭʼ�����������Ԫ��
* @param vecAngleEo ԭʼ��������н�Ԫ��
* @param vecImg_time ����Ӱ��ɨ���л�ȡʱ��
* @param vecEo �ڲ���ⷽλ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlLinearImage::mlGetEop( vector<LineEo> &vecLineEo, vector<AngleEo> &vecAngleEo, vector<DOUBLE> &vecImg_time, vector<ExOriPara> *vecEo )
{
    //����ɨ����֮�������Թ����ߴζ���ʽ�Թ��������ݽ��в�ֵ���õ�ÿ��ɨ���е��ⷽλԪ��
    //�����ʼ��
    if( (vecLineEo.size()==0)||(vecAngleEo.size()==0)||(vecImg_time.size()==0) )
    {
        SCHAR strErr[] = "There's no exterior orientation parameters!Please check the files!\n" ;
        LOGAddErrorMsg(strErr) ;
        return false;
    }
    CmlMat MatImg_time, MatLine_time,MatOriXs,MatOriYs,MatOriZs,MatAngle_time,MatOriPitch,MatOriRoll,MatOriYaw;
    MatImg_time.Initial(vecImg_time.size(),1);
    MatLine_time.Initial(vecLineEo.size(),1);
    MatOriXs.Initial(vecLineEo.size(),1);
    MatOriYs.Initial(vecLineEo.size(),1);
    MatOriZs.Initial(vecLineEo.size(),1);
    MatAngle_time.Initial(vecAngleEo.size(),1);
    MatOriPitch.Initial(vecAngleEo.size(),1);
    MatOriRoll.Initial(vecAngleEo.size(),1);
    MatOriYaw.Initial(vecAngleEo.size(),1);

    UINT i;
    LineEo tmpLineEo;
    AngleEo tmpAngleEo;
    //��Ӱ��ʱ��
    for(i = 0; i < vecImg_time.size(); i++)
    {
        MatImg_time.SetAt(i,0,vecImg_time[i]);
    }
    //���ⷽλ��Ԫ��
    for(i = 0; i < vecLineEo.size(); i++)
    {
        tmpLineEo = vecLineEo.at(i);
        MatLine_time.SetAt(i,0,tmpLineEo.dEoTime);
        MatOriXs.SetAt(i,0,tmpLineEo.pos.X);
        MatOriYs.SetAt(i,0,tmpLineEo.pos.Y);
        MatOriZs.SetAt(i,0,tmpLineEo.pos.Z);
    }
    //���ⷽλ��Ԫ��
    for(i = 0; i < vecAngleEo.size(); i++)
    {
        tmpAngleEo = vecAngleEo.at(i);
        MatAngle_time.SetAt(i,0,tmpAngleEo.dEoTime);
        MatOriPitch.SetAt(i,0,tmpAngleEo.ori.phi);
        MatOriRoll.SetAt(i,0,tmpAngleEo.ori.omg);
        MatOriYaw.SetAt(i,0,tmpAngleEo.ori.kap);
    }

    CmlMat MatXs, MatYs, MatZs, MatPtich, MatRoll, MatYaw;
    //�ֱ��ڲ������ⷽλ
    mlinterEo(&MatLine_time, &MatOriXs, &MatImg_time,  &MatXs);
    mlinterEo(&MatLine_time, &MatOriYs, &MatImg_time,  &MatYs);
    mlinterEo(&MatLine_time, &MatOriZs, &MatImg_time, &MatZs);
    mlinterEo(&MatAngle_time, &MatOriPitch, &MatImg_time,  &MatPtich);
    mlinterEo(&MatAngle_time, &MatOriRoll, &MatImg_time,  &MatRoll);
    mlinterEo(&MatAngle_time, &MatOriYaw, &MatImg_time,  &MatYaw);
    //д��ExOriPara�ⷽλ�ṹ��
    ExOriPara tmp;
    for(i = 0; i < MatImg_time.GetH(); i++)
    {
        tmp.pos.X = MatXs.GetAt( i, 0 );
        tmp.pos.Y = MatYs.GetAt( i, 0 );
        tmp.pos.Z = MatZs.GetAt( i, 0 );
        tmp.ori.phi = MatPtich.GetAt( i, 0 );
        tmp.ori.omg = MatRoll.GetAt( i, 0 );
        tmp.ori.kap = MatYaw.GetAt( i, 0 );
        vecEo->push_back(tmp);
    }

    return true;
}
/**
* @fn mlBLH2XYZ
* @date 2011.11.29
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���﷽��ά��������������ϵת���¹�����ϵ�µĿռ�ֱ������
* @param blhPts ����������ϵ����
* @param xyzPts �¹�����ϵ�µĿռ�ֱ������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlLinearImage::mlBLH2XYZ(Pt3d& blhPts, Pt3d& xyzPts)
{
    //���﷽��ά��������������ϵ��Latitude,Longitude,Height��ת���¹�����ϵ�µ�XYZ.����Ϊprecision(10)
    xyzPts.Z = ( blhPts.Z + Moon_Radius ) * sin( Deg2Rad(blhPts.Y) );
    xyzPts.X = ( blhPts.Z + Moon_Radius ) * cos( Deg2Rad(blhPts.Y) ) * cos( Deg2Rad(blhPts.X) );
    xyzPts.Y = ( blhPts.Z + Moon_Radius ) * cos( Deg2Rad(blhPts.Y) ) * sin( Deg2Rad(blhPts.X) );
    return true;
}
/**
* @fn mlXYZ2BLH
* @date 2011.11.29
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ���﷽��ά�����¹�����ϵ�µĿռ�ֱ������ת������������ϵ
* @param xyzPts �¹�����ϵ�µ�XYZ����
* @param blhPts ����������ϵ��Longitude,Latitude,Height������
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlLinearImage::mlXYZ2BLH(Pt3d &xyzPts, Pt3d &blhPts)
{
    //���﷽��ά�����¹�����ϵ�µ�XYZת������������ϵ(Latitude,Longitude,Height).����Ϊprecision(10)
    blhPts.X = Rad2Deg(atan2(xyzPts.Y,xyzPts.X));
    blhPts.Y = Rad2Deg(atan2(xyzPts.Z,sqrt(xyzPts.X*xyzPts.X+xyzPts.Y*xyzPts.Y)));
    blhPts.Z = sqrt(xyzPts.X*xyzPts.X+xyzPts.Y*xyzPts.Y+xyzPts.Z*xyzPts.Z)-Moon_Radius;
    return true;
}
/**
* @fn mlCE1OPK2RMat
* @date 2011.11.30
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CE-1����Ӱ���ⷽλ��Ԫ��ת��ת����
* @param pitch ������
* @param roll ������
* @param yaw ��ƫ��
* @param pRMat ��ת����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE1LinearImage::mlCE1OPK2RMat( DOUBLE &pitch, DOUBLE &roll, DOUBLE &yaw, CmlMat* pRMat )
{
    if( false == pRMat->IsValid() )
    {
        pRMat->Initial( 3, 3 );
    }
    if( ( pRMat->GetH() != 3) || ( pRMat->GetW() != 3 ) )
    {
        return false;
    }
    //�������Ǻ���
    DOUBLE dSP = sin( Deg2Rad(pitch) );
    DOUBLE dSR = sin( Deg2Rad(roll) );
    DOUBLE dSY = sin( Deg2Rad(yaw) );

    DOUBLE dCP = cos( Deg2Rad(pitch) );
    DOUBLE dCR = cos( Deg2Rad(roll) );
    DOUBLE dCY = cos( Deg2Rad(yaw) );

    //����ת����ÿһ��Ԫ��ֵ
    pRMat->SetAt( 0, 0, (dCP*dCY - dSP*dSR*dSY) );
    pRMat->SetAt( 0, 1, (-dCP*dSY - dSP*dSR*dCY) );
    pRMat->SetAt( 0, 2, -dSP*dCR );

    pRMat->SetAt( 1, 0, dCR*dSY );
    pRMat->SetAt( 1, 1, dCR*dCY );
    pRMat->SetAt( 1, 2, -dSR );

    pRMat->SetAt( 2, 0, ( dSP*dCY + dCP*dSR*dSY ) );
    pRMat->SetAt( 2, 1, ( -dSP*dSY + dCP*dSR*dCY ) );
    pRMat->SetAt( 2, 2, dCP*dCR );
    return true;

}
/**
* @fn mlCE1OPK2RMat
* @date 2011.11.30
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��CE-1����Ӱ�������ⷽλ��Ԫ��ת����Ԫ�ؼ���ת�������ʽ
* @param vecEo �ⷽλԪ��
* @param vecXsYsZs ��Ԫ��
* @param vecR ��ת����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE1LinearImage::mlCE1OPK2RMat( vector<ExOriPara> &vecEo, vector<Pt3d> & vecXsYsZs, vector<MatrixR> &vecR )
{
    if( vecEo.size() == 0 )
    {
        return false;
    }
    DOUBLE pitch, roll, yaw;
    Pt3d XsYsZs;
    CmlMat mattR;
    mattR.Initial( 3, 3 );
    MatrixR tmpR;
    for ( UINT i = 0; i < vecEo.size(); i++ )
    {
        //��д�ⷽλ��Ԫ��
        XsYsZs.X = vecEo[i].pos.X;
        XsYsZs.Y = vecEo[i].pos.Y;
        XsYsZs.Z = vecEo[i].pos.Z;
        vecXsYsZs.push_back(XsYsZs);
        //���ⷽλ��Ԫ��
        pitch = vecEo[i].ori.phi;
        roll = vecEo[i].ori.omg;
        yaw = vecEo[i].ori.kap;
        //��ŷ����ת��ת����
        mlCE1OPK2RMat( pitch, roll, yaw, &mattR );
        tmpR.matR = mattR;
        vecR.push_back( tmpR );
    }
    return true;
}
/**
* @fn mlCE2OPK2RMat
* @date 2012.3.3
* @author ��һ�� ylliu@irsa.ac.cn
* @brief CE-2����Ӱ���ⷽλ��Ԫ��ת��ת����
* @param angX ��X��н�
* @param angY ��Y��н�
* @param angZ ��Z��н�
* @param pRMat ��ת����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE2LinearImage::mlCE2OPK2RMat( DOUBLE &angX, DOUBLE &angY, DOUBLE &angZ, CmlMat* pRMat )
{
    if( false == pRMat->IsValid() )
    {
        pRMat->Initial( 3, 3 );
    }
    if( ( pRMat->GetH() != 3) || ( pRMat->GetW() != 3 ) )
    {
        return false;
    }
    //�������Ǻ���
    DOUBLE dSX = sin( Deg2Rad(angX) );
    DOUBLE dSY = sin( Deg2Rad(angY) );
    DOUBLE dSZ = sin( Deg2Rad(angZ) );

    DOUBLE dCX = cos( Deg2Rad(angX) );
    DOUBLE dCY = cos( Deg2Rad(angY) );
    DOUBLE dCZ = cos( Deg2Rad(angZ) );

    //����ת����ÿһ��Ԫ��ֵ
//    Ra=[ 1.0000   -0.0008    0.0011;
//    0.0008    1.0000    0.0008;
//   -0.0011   -0.0008    1.0000];
    CmlMat pR;
    pR.Initial(3,3);
    pR.SetAt( 0, 0, (dCY*dCZ - dSY*dSX*dSZ) );
    pR.SetAt( 0, 1, (dCY*dSZ + dSY*dSX*dCZ) );
    pR.SetAt( 0, 2, (-dSY*dCX ) );

    pR.SetAt( 1, 0, (-dCX*dSZ) );
    pR.SetAt( 1, 1, dCX*dCZ ) ;
    pR.SetAt( 1, 2, dSX  );

    pR.SetAt( 2, 0, ( dSY*dCZ + dCY*dSX*dSZ ) );
    pR.SetAt( 2, 1, ( dSY*dSZ - dCY*dSX*dCZ ) );
    pR.SetAt( 2, 2, dCY*dCX );

    CmlMat pRa;//������þ���
    pRa.Initial(3,3);
    pRa.SetAt( 0, 0, 1.0 );
    pRa.SetAt( 0, 1, -0.0008 );
    pRa.SetAt( 0, 2, 0.0011 );

    pRa.SetAt( 1, 0, 0.0008 );
    pRa.SetAt( 1, 1, 1.0 ) ;
    pRa.SetAt( 1, 2, 0.0008  );

    pRa.SetAt( 2, 0, -0.0011 );
    pRa.SetAt( 2, 1, -0.0008 );
    pRa.SetAt( 2, 2, 1.0 );

    mlMatMul(&pR,&pRa,pRMat);
    return true;

}
/**
* @fn mlCE2OPK2RMat
* @date 2011.11.30
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ��CE-2����Ӱ�������ⷽλ��Ԫ��ת����Ԫ�ؼ���ת�������ʽ
* @param vecEo �ⷽλԪ��
* @param vecXsYsZs ��Ԫ��
* @param vecR ��ת����
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE2LinearImage::mlCE2OPK2RMat( vector<ExOriPara> &vecEo, vector<Pt3d> & vecXsYsZs, vector<MatrixR> &vecR )
{
    DOUBLE angX, angY, angZ;
    Pt3d XsYsZs;
    CmlMat mattR;
    mattR.Initial( 3, 3 );
    MatrixR tmpR;
    for ( UINT i = 0; i < vecEo.size(); i++ )
    {
        //��д�ⷽλ��Ԫ��
        XsYsZs.X = vecEo[i].pos.X;
        XsYsZs.Y = vecEo[i].pos.Y;
        XsYsZs.Z = vecEo[i].pos.Z;
        vecXsYsZs.push_back(XsYsZs);
        //���ⷽλ��Ԫ��
        angX = vecEo[i].ori.phi;
        angY = vecEo[i].ori.omg;
        angZ = vecEo[i].ori.kap;
        //��ŷ����ת��ת����
        mlCE2OPK2RMat( angX, angY, angZ, &mattR );
        tmpR.matR = mattR;
        vecR.push_back( tmpR );
    }
    return true;
}
/**
* @fn mlGetCE1DOMCoordinate
* @date 2011.12.07
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����CE-1����Ӱ��DOM������ԭͼ���ϵ�x,y����
* @param OriSatImg ԭʼӰ��
* @param vecR Ӱ���ⷽλ��ת����
* @param vecXsYsZs Ӱ���ⷽλ��Ԫ��
* @param f �������
* @param vecPtXYZ �﷽��ά����
* @param pCE1IOP �ڷ�λԪ��
* @param nWidth ����Ӱ����
* @param nHeight Ӱ��߶�
* @param thresh �������x����������ֵ֮�����ֵ
* @param ImgSL ����Ӱ��DOM������ԭͼ���ϵ�x,y����
* @param trueline Ӱ��������ʵ��
* @param range ������Χ
* @param thresh ��ֵ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE1LinearImage::mlGetCE1DOMCoordinate(CmlRasterBlock &OriSatImg, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, DOUBLE f, vector<Pt3d> &vecPtXYZ, UINT nWidth, UINT nHeight, CRasterPt2D &ImgSL, DOUBLE trueline, UINT range, DOUBLE thresh )
{
    if( (!OriSatImg.IsValid()) || (vecR.size() == 0) || (vecXsYsZs.size() == 0) || (vecPtXYZ.size() == 0) || (nWidth <= 0) || (nHeight <= 0) )
    {
        return false;
    }
    /*���ַ������������,Ĭ��������*/
    UINT nStart, nEnd, nMiddle, nCycle, kStart, kLength, k, indx, nX, nY;
    UINT nScanline = OriSatImg.GetH();
    ExOriPara ExOri;
    Pt3d blhPts,xyzPts;
    Pt2d xyPts,tempXY;
    CmlMat RMat, MatImgX,MatImgY;
    CmlPhgProc PhgProc;
    CmlCE1LinearImage ce1;
    //����ά����������
    for( nY = 0; nY < nHeight; nY++ )
        for( nX = 0; nX < nWidth; nX++ )
        {
            tempXY.X = -1;
            tempXY.Y = -1;
            ImgSL.SetAt( nY, nX, tempXY );
            nEnd = nScanline - 1;
            nStart = 0;
            //���ַ���������
            for ( nCycle = 0; nCycle < log2( DOUBLE(nScanline - 1 )); nCycle++ )
            {
                nMiddle = SINT( ( nStart + nEnd ) / 2 );//ȡ��
                //ȡ���ⷽλԪ��
                ExOri.pos = vecXsYsZs.at( nMiddle );
                RMat = vecR[ nMiddle ].matR;
                //ȡ���﷽��ά��
                xyzPts = vecPtXYZ.at( nY * nWidth + nX );
                //ce1.mlBLH2XYZ( blhPts, xyzPts );//��BLHת��XYZ
                //���ݹ��߷������﷽�������x��y
                PhgProc.mlReproject( &xyPts, &xyzPts, &ExOri, f, f,&RMat );
                //������ʵֵ�ӽ�ʱ��ֹͣ�������������Ը����ⷽλΪ���Ŀ����������ڣ������ⷽλ�����񷽵�x,y
                if( abs( xyPts.X - trueline ) < thresh )
                {
                    //��ǰ���������������䳤��С��range�����
                    if ( nMiddle + range > nScanline - 1 )
                    {
                        MatImgX.Initial( nScanline - nMiddle + range , 1 );
                        MatImgY.Initial( nScanline - nMiddle + range , 1 );
                        kStart = nMiddle - range;
                        kLength = nScanline - nMiddle + range ;
                    }
                    //��ǰ���������������䳤��С��range�����
                    else if ( nMiddle - range < 0 )
                    {
                        MatImgX.Initial( nMiddle + range + 1 , 1 );
                        MatImgY.Initial( nMiddle + range + 1 , 1 );
                        kStart = 0;
                        kLength = nMiddle + range + 1;
                    }
                    //��ǰ�����������������䳤�ȶ���С��range�����
                    else
                    {
                        MatImgX.Initial( 2 * range + 1,1 );
                        MatImgY.Initial( 2 * range + 1,1 );
                        kStart = nMiddle - range ;
                        kLength = 2 * range + 1;
                    }
                    //������������ÿһ���ⷽλ������x��y
                    for( k = kStart; k < ( kStart + kLength ); k++ )
                    {

                        ExOri.pos = vecXsYsZs.at( k );
                        RMat = vecR[ k ].matR;
                        PhgProc.mlReproject( &xyPts, &xyzPts, &ExOri, f, f, &RMat);//���߷��̼���x��y
                        MatImgX.SetAt( k - kStart, 0, abs( xyPts.X - trueline ) ) ;
                        MatImgY.SetAt( k - kStart, 0, xyPts.Y ) ;
                    }
                    //�����������ڼ�������xֵ���бȽϣ��ҵ���ӽ���ʵֵ��ֵ
                    indx = mlCloseVal( &MatImgX, 0 );
                    //�洢��ƽ������yֵ
                    tempXY.X = MatImgY.GetAt( indx, 0 );
                    //�洢ͼ������Yֵ�����к�
                    tempXY.Y = indx + kStart;
                    //ImgSL�洢�������Sample��Line��������x���򣬼�tempXY.Y��ת�����кţ�
                    ImgSL.SetAt( nY, nX, tempXY );
                    break;
                }
                //С����ʵֵʱ������ǰ���
                else if( xyPts.X < trueline )
                {
                    nEnd = nMiddle;
                }
                //������ʵֵʱ����������
                else
                {
                    nStart = nMiddle;
                }
            }//���ַ���������
        }//����ÿ����
    return true;
}
/**
* @fn mlGetCE2DOMCoordinate
* @date 2011.12.07
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����CE-2����Ӱ��DOM������ԭͼ���ϵ�x,y����
* @param OriSatImg ԭʼӰ��
* @param vecR Ӱ���ⷽλ��ת����
* @param vecXsYsZs Ӱ���ⷽλ��Ԫ��
* @param f �������
* @param vecPtXYZ �﷽��ά����
* @param pCE1IOP �ڷ�λԪ��
* @param nWidth ����Ӱ����
* @param nHeight Ӱ��߶�
* @param thresh �������x����������ֵ֮�����ֵ
* @param ImgSL ����Ӱ��DOM������ԭͼ���ϵ�x,y����
* @param trueline Ӱ��������ʵ��
* @param range ������Χ
* @param thresh ��ֵ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE2LinearImage::mlGetCE2DOMCoordinate(CmlRasterBlock &OriSatImg, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, DOUBLE f, vector<Pt3d> &vecPtXYZ, UINT nWidth, UINT nHeight, CRasterPt2D &ImgSL, DOUBLE trueline, UINT range, DOUBLE thresh )
{
    if( (!OriSatImg.IsValid()) || (vecR.size() == 0) || (vecXsYsZs.size() == 0) || (vecPtXYZ.size() == 0) || (nWidth <= 0) || (nHeight <= 0) )
    {
        return false;
    }
    /*���ַ������������,Ĭ��������*/
    UINT nStart, nEnd, nMiddle, nCycle, kStart, kLength, k, indx, nX, nY;
    UINT nScanline = OriSatImg.GetH();
    ExOriPara ExOri;
    Pt3d blhPts,xyzPts;
    Pt2d xyPts,tempXY;
    CmlMat RMat, MatImgX,MatImgY;
    CmlPhgProc PhgProc;
    CmlCE1LinearImage ce1;
    //����ά����������
    for( nY = 0; nY < nHeight; nY++ )
        for( nX = 0; nX < nWidth; nX++ )
        {
            tempXY.X = -1;
            tempXY.Y = -1;
            ImgSL.SetAt( nY, nX, tempXY );
            nEnd = nScanline - 1;
            nStart = 0;
            //���ַ���������
            for ( nCycle = 0; nCycle < log2( DOUBLE(nScanline - 1) ); nCycle++ )
            {
                nMiddle = SINT( ( nStart + nEnd ) / 2 );//ȡ��
                //ȡ���ⷽλԪ��
                ExOri.pos = vecXsYsZs.at( nMiddle );
                RMat = vecR[ nMiddle ].matR;
                //ȡ���﷽��ά��
                xyzPts = vecPtXYZ.at( nY * nWidth + nX );
                //ce1.mlBLH2XYZ( blhPts, xyzPts );//��BLHת��XYZ
                //���ݹ��߷������﷽�������x��y
                PhgProc.mlReproject( &xyPts, &xyzPts, &ExOri, f, f,&RMat );
                //������ʵֵ�ӽ�ʱ��ֹͣ�������������Ը����ⷽλΪ���Ŀ����������ڣ������ⷽλ�����񷽵�x,y
                if( abs( xyPts.X - trueline ) < thresh )
                {
                    //��ǰ���������������䳤��С��range�����
                    if ( nMiddle + range > nScanline - 1 )
                    {
                        MatImgX.Initial( nScanline - nMiddle + range , 1 );
                        MatImgY.Initial( nScanline - nMiddle + range , 1 );
                        kStart = nMiddle - range;
                        kLength = nScanline - nMiddle + range ;
                    }
                    //��ǰ���������������䳤��С��range�����
                    else if ( nMiddle - range < 0 )
                    {
                        MatImgX.Initial( nMiddle + range + 1 , 1 );
                        MatImgY.Initial( nMiddle + range + 1 , 1 );
                        kStart = 0;
                        kLength = nMiddle + range + 1;
                    }
                    //��ǰ�����������������䳤�ȶ���С��range�����
                    else
                    {
                        MatImgX.Initial( 2 * range + 1,1 );
                        MatImgY.Initial( 2 * range + 1,1 );
                        kStart = nMiddle - range ;
                        kLength = 2 * range + 1;
                    }
                    //������������ÿһ���ⷽλ������x��y
                    for( k = kStart; k < ( kStart + kLength ); k++ )
                    {

                        ExOri.pos = vecXsYsZs.at( k );
                        RMat = vecR[ k ].matR;
                        PhgProc.mlReproject( &xyPts, &xyzPts, &ExOri, f, f, &RMat);//���߷��̼���x��y
                        MatImgX.SetAt( k - kStart, 0, abs( xyPts.X - trueline ) ) ;
                        MatImgY.SetAt( k - kStart, 0, xyPts.Y ) ;
                    }
                    //�����������ڼ�������xֵ���бȽϣ��ҵ���ӽ���ʵֵ��ֵ
                    indx = mlCloseVal( &MatImgX, 0 );
                    //�洢��ƽ������yֵ
                    tempXY.X = MatImgY.GetAt( indx, 0 );
                    //�洢ͼ������Yֵ�����к�
                    tempXY.Y = indx + kStart;
                    //ImgSL�洢�������Sample��Line��������x���򣬼�tempXY.Y��ת�����кţ�
                    ImgSL.SetAt( nY, nX, tempXY );
                    break;
                }
                //С����ʵֵʱ������ǰ���
                else if( xyPts.X > trueline )
                {
                    nEnd = nMiddle;
                }
                //������ʵֵʱ����������
                else
                {
                    nStart = nMiddle;
                }
            }//���ַ���������
        }//����ÿ����
    return true;
}
/**
* @fn mlGetCE1DOM
* @date 2011.12.07
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����CE-1����Ӱ��DOM
* @param OriSatImg ԭʼCE-1����Ӱ��
* @param vecR Ӱ���ⷽλ��ת����
* @param vecXsYsZs Ӱ���ⷽλ��Ԫ��
* @param pCE1IOP �ڷ�λԪ��
* @param vecPtXYZ ��ά�﷽��
* @param range �ⷽλ������Χ
* @param thresh �������x����������ֵ֮�����ֵ
* @param SatDom CE-1����Ӱ��DOM
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE1LinearImage::mlGetCE1DOM( CmlRasterBlock &OriSatImg, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, CE1IOPara *pCE1IOP, vector<Pt3d> &vecPtXYZ, CmlRasterBlock &SatDom, UINT range, DOUBLE thresh )
{
    if( ( !OriSatImg.IsValid() ) || ( !SatDom.IsValid() ) || (vecR.size() == 0) || (vecXsYsZs.size() == 0) || (vecPtXYZ.size() == 0)  )
    {
        return false;
    }
    SINT nX, nY;
    CRasterPt2D ImgSL;
    ImgSL.Initial(SatDom.GetH(),SatDom.GetW());
    DOUBLE trueline = ( pCE1IOP->l0 - pCE1IOP->nCCD_line ) * pCE1IOP->pixsize-pCE1IOP->x0;
    /**���ַ������������,Ĭ��������**/
    CmlCE1LinearImage ce;
    ce.mlGetCE1DOMCoordinate( OriSatImg, vecR, vecXsYsZs, pCE1IOP->f, vecPtXYZ, SatDom.GetW(), SatDom.GetH(), ImgSL, trueline, range, thresh );

    /****�����У��кž���*****/
    Pt2d tempXY;
    SINT nDemH = SatDom.GetH();
    SINT nDemW = SatDom.GetW();
    //����ʱ������ƽ������yֵת�����к�
    if ( pCE1IOP->upflag )
    {
        for( nY = 0; nY < nDemH; nY++ )
        {
            for( nX = 0; nX < nDemW; nX++ )
            {
                tempXY = ImgSL.GetAt( nY, nX );
                //���곬��ʱ����ֵ-1
                if( (tempXY.Y < 0) || (tempXY.Y >= OriSatImg.GetH()) )
                {
                    tempXY.X = -1;
                }
                else
                {
                    tempXY.X =  pCE1IOP->s0 + ( tempXY.X + pCE1IOP->y0 ) / pCE1IOP->pixsize ;
                }
                ImgSL.SetAt( nY, nX, tempXY );
            }
        }
    }
    //����ʱ������ƽ������yֵת�����к�
    else
    {
        for( nY = 0; nY < nDemH; nY++ )
        {
            for( nX = 0; nX < nDemW; nX++ )
            {
                tempXY = ImgSL.GetAt( nY, nX );
                //���곬��ʱ����ֵ-1
                if( ( tempXY.Y < 0 ) || ( tempXY.Y >= OriSatImg.GetH() ) )
                {
                    tempXY.X = -1;
                }
                else
                {
                    tempXY.X = pCE1IOP->s0 - ( tempXY.X + pCE1IOP->y0 ) / pCE1IOP->pixsize;
                }
                ImgSL.SetAt( nY, nX, tempXY );
            }
        }
    }
    /***˫�����ڲ�***/
    CmlFrameImage frm;
    frm.mlGrayInterpolation( &OriSatImg , &ImgSL, &SatDom, 0 );
    return true;
}
/**
* @fn mlGetCE2DOM
* @date 2011.12.07
* @author ��һ�� ylliu@irsa.ac.cn
* @brief ����CE-2����Ӱ��DOM
* @param OriSatImg ԭʼCE-1����Ӱ��
* @param vecR Ӱ���ⷽλ��ת����
* @param vecXsYsZs Ӱ���ⷽλ��Ԫ��
* @param pCE2IOP �ڷ�λԪ��
* @param vecPtXYZ ����Ӱ���﷽��
* @param SatDom CE-2����Ӱ��DOM
* @param range �ⷽλ������Χ
* @param thresh �������x����������ֵ֮�����ֵ
* @retval TRUE �ɹ�
* @retval FALSE ʧ��
* @version 1.0
* @par �޸���ʷ:
* <����>  <ʱ��>  <�汾���>  <����>\n
*/
bool CmlCE2LinearImage::mlGetCE2DOM( CmlRasterBlock &OriSatImg, vector<MatrixR> &vecR, vector<Pt3d> &vecXsYsZs, CE2IOPara *pCE2IOP, vector<Pt3d> &vecPtXYZ, CmlRasterBlock &SatDom, UINT range, DOUBLE thresh )
{
    if( ( !OriSatImg.IsValid() ) || ( !SatDom.IsValid() ) || (vecR.size() == 0) || (vecXsYsZs.size() == 0) || (vecPtXYZ.size() == 0)  )
    {
        return false;
    }
    SINT nX, nY;
    CRasterPt2D ImgSL;
    ImgSL.Initial(SatDom.GetH(),SatDom.GetW());
    DOUBLE trueline = pCE2IOP->x0 - tan( pCE2IOP->AngleDeg * ML_PI / 180.0 ) * pCE2IOP->f;

    /**���ַ������������,Ĭ��������**/
    CmlCE2LinearImage ce;
    ce.mlGetCE2DOMCoordinate( OriSatImg, vecR, vecXsYsZs, pCE2IOP->f, vecPtXYZ, SatDom.GetW(), SatDom.GetH(), ImgSL, trueline, range, thresh );

    /****�����У��кž���*****/
    Pt2d tempXY;
    SINT nDemH = SatDom.GetH();
    SINT nDemW = SatDom.GetW();
    //����ʱ������ƽ������yֵת�����к�
    if ( pCE2IOP->upflag )
    {
        for( nY = 0; nY < nDemH; nY++ )
        {
            for( nX = 0; nX < nDemW; nX++ )
            {
                tempXY = ImgSL.GetAt( nY, nX );
                //���곬��ʱ����ֵ-1
                if( (tempXY.Y < 0) || (tempXY.Y >= OriSatImg.GetH()) )
                {
                    tempXY.X = -1;
                }
                else
                {
                    tempXY.X = pCE2IOP->s0 + ( pCE2IOP->y0 - tempXY.X ) / pCE2IOP->pixsize;
                }
                ImgSL.SetAt( nY, nX, tempXY );
            }
        }
    }
    //����ʱ������ƽ������yֵת�����к�
    else
    {
        for( nY = 0; nY < nDemH; nY++ )
        {
            for( nX = 0; nX < nDemW; nX++ )
            {
                tempXY = ImgSL.GetAt( nY, nX );
                //���곬��ʱ����ֵ-1
                if( ( tempXY.Y < 0 ) || ( tempXY.Y >= OriSatImg.GetH() ) )
                {
                    tempXY.X = -1;
                }
                else
                {
                    tempXY.X = pCE2IOP->s0 + ( pCE2IOP->y0 + tempXY.X ) / pCE2IOP->pixsize;
                }
                ImgSL.SetAt( nY, nX, tempXY );
            }
        }
    }
    /***˫�����ڲ�***/
    CmlFrameImage frm;
    frm.mlGrayInterpolation( &OriSatImg , &ImgSL, &SatDom, 0 );
    return true;
}
