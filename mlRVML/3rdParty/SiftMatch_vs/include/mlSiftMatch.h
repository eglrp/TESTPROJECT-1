/*****************************************************************
�����ƣ�SIFTƥ�亯����
��    �ߣ�������ͼ��ң���о���(PMRS_LAB)
��������������ͼ��SIFTƥ�䣬���ƥ�����������꣬����ͼ��������Ͻ�Ϊԭ�㣬����Ϊx������Ϊy
��    �룺
��    ����
�汾���:   1.0
�޸���ʷ:    <����>    <ʱ��>   <�汾���>    <����>
******************************************************************/

#ifndef __MLSIFTMATCH_H
#define __MLSIFTMATCH_H

#include <vector>
using namespace std;


int mlSiftMatch(char* pLeft,int nWL,int nHL,int nByteL,char* pRight,int nWR,int nHR,int nByteR,int &nPtNum, double* &pXL,double* &pYL,double* &pXR,double* &pYR,int nMaxCheck=200, double dRatio=0.49);

/*****************************************************************
�������ƣ�mlSiftMatch
��    �ߣ�������ͼ��ң���о���(PMRS_LAB)
����������SIFTƥ�䣬Ŀǰֻ֧��8bitͼ����������������Ͻ�Ϊԭ�㣬����Ϊx������Ϊy
��    �룺   
			pLeft:    ��ͼ��ָ��
			nWL:      ��ͼ���
			nHL:      ��ͼ���
			nByteL;   ��ͼ��λ����8��16��24
			pRight:   ��ͼ��ָ��
			nWR:      ��ͼ���
			nHR:      ��ͼ���
			nByteR:   ��ͼ��λ����8��16��24
            nMaxCheck:SIFTƥ�����
            dRatio:   SIFTƥ�����
��    ����
			vXL:      ƥ�����ͼ��x����
			vYL:      ƥ�����ͼ��y����
			vXR:      ƥ�����ͼ��x����
			vYR:      ƥ�����ͼ��y��
����ֵ��    int       ƥ�������
�汾���:   1.0
�޸���ʷ:    �틠   2011.12.17  1.0    8bitͼ��SIFTƥ��
******************************************************************/



bool freeData( double* pData);

#endif
