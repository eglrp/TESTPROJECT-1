/*
  Detects SIFT features in two images and finds matches between them.

  Copyright (C) 2006-2010  Rob Hess <hess@eecs.oregonstate.edu>

  @version 1.1.2-20100521
*/
#include <stdio.h>
//#include <vector>
#include "../SiftMatch.h"
#include "sift.h"
#include "imgfeatures.h"
#include "kdtree.h"
#include "utils.h"
#include "xform.h"

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

//#include <stdio.h>

using namespace std;
/* the maximum number of keypoint NN candidates to check during BBF search */
#define KDTREE_BBF_MAX_NN_CHKS 200

/* threshold on squared ratio of distances between NN and 2nd NN */
#define NN_SQ_DIST_RATIO_THR 0.49


//int main( int argc, char** argv )
int SiftMatch(uchar* pLeft,int nWL,int nHL,int nByteL,uchar* pRight,int nWR,int nHR,int nByteR,vector<double> &vXL,vector<double> &vYL,vector<double> &vXR,vector<double> &vYR)
{
    //���ڴ��ת��IplImage
    IplImage* img1, * img2;

    CvSize sl;
    sl.height = nHL;
    sl.width = nWL;

    img1 = cvCreateImage( sl, IPL_DEPTH_8U, 1 );
    img1->origin = 0; //����Ϊ����ṹ

    if( 0 == (img1->width % 4 ) ) //Ϊ�п��ĵı�������ͼ���в���Ҫ�ֽڲ���
    {
        memcpy(  (void*)(img1->imageData ), (void*)(pLeft), nWL*nHL);
    }
    else//��Ϊ�п��ĵı�������ͼ���д����ֽڲ��룬ת��ʱ��Ҫȥ��
    {
        for( int i = 0; i < nHL; ++i )
        {
            for( int j = 0; j < nWL; ++j )
            {
                memcpy( (void*)(img1->imageData + i*img1->widthStep ), (void*)(pLeft+ i*nWL), nWL);
            }
        }
    }

    CvSize sr;
    sr.height = nHR;
    sr.width = nWR;

    img2 = cvCreateImage( sr, IPL_DEPTH_8U, 1 );
    img2->origin = 0; //����Ϊ����ṹ

    if( 0 == (img2->width % 4 ) ) //Ϊ�п��ĵı�������ͼ���в���Ҫ�ֽڲ���
    {
        memcpy(  (void*)(img2->imageData ), (void*)(pLeft), nWL*nHL);
    }
    else//��Ϊ�п��ĵı�������ͼ���д����ֽڲ��룬ת��ʱ��Ҫȥ��
    {
        for( int i = 0; i < nHR; ++i )
        {
            for( int j = 0; j < nWR; ++j )
            {
                memcpy( (void*)(img2->imageData + i*img2->widthStep ), (void*)(pRight+ i*nWL), nWL);
            }
        }
    }

  struct feature* feat1, * feat2, * feat;
  struct feature** nbrs;
  struct kd_node* kd_root;
  CvPoint pt1, pt2;
  double d0, d1;
  int n1, n2, k, i, m = 0;


  n1 = sift_features( img1, &feat1 );
  n2 = sift_features( img2, &feat2 );
  kd_root = kdtree_build( feat2, n2 );

  for( i = 0; i < n1; i++ )
    {
      feat = feat1 + i;
      k = kdtree_bbf_knn( kd_root, feat, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS );
      if( k == 2 )
	{
	  d0 = descr_dist_sq( feat, nbrs[0] );
	  d1 = descr_dist_sq( feat, nbrs[1] );
	  if( d0 < d1 * NN_SQ_DIST_RATIO_THR )
	    {
	      pt1 = cvPoint( cvRound( feat->x ), cvRound( feat->y ) );
	      pt2 = cvPoint( cvRound( nbrs[0]->x ), cvRound( nbrs[0]->y ) );
          vXL.push_back(pt1.x);
          vYL.push_back(pt1.y);
          vXR.push_back(pt2.x);
          vYR.push_back(pt2.y);
	      m++;
	      feat1[i].fwd_match = nbrs[0];
	    }
	}
      free( nbrs );
    }


  cvReleaseImage( &img1 );
  cvReleaseImage( &img2 );
  kdtree_release( kd_root );
  free( feat1 );
  free( feat2 );
  return m;
}
