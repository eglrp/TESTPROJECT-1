/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtGui>
#include <QMainWindow>
#include<QDialog>
#include <QPrinter>
#include"gdal_priv.h"

#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSplitter>
#include<QLayout>
#include<QTableView>
#include<QtSql/QSqlTableModel>
#include <QLabel>


//#include"../../../src/mlRVML/mlGdalDataset.h"
//#include"../../../src/mlRVML/mlGeoRaster.h"
//#include"../../../src/mlRVML/mlRasterBlock.h"
//#include"../../../src/mlRVML/mlDemAnalyse.h"

#include"DrawLabel.h"
#include"CustomScroll.h"

#include"GISTool.h"
#include"contourdialog.h"

//#include"../../../src/mlRVML/mlDemAnalyse.h"
//#include"../../../src/mlRVML/mlStereoProc.h"
#include"viewsheddialog.h"
#include"slopedialog.h"
#include"obstacledialog.h"
#include"dialogvisualimage.h"
#include"dialogdemdomprocess.h"
#include"dialogtinsimplify.h"
#include"dialogwidebaseanalysis.h"
#include"dialogwidebaselinemap.h"
#include"dialogmultsitedemmosaic.h"
#include"dialogsitedemmosaic.h"
#include"dialogpersimagecreate.h"
#include"dialogpanomosaic.h"
#include"dialogcamera.h"
#include"dialogorbitimagedem.h"
#include"dialogdensematch.h"
#include"dialogcoordtrans.h"
#include"dialoglandlocate.h"
#include"dialoglandlocatematch.h"
#include"dialoglandlocateinter.h"
#include"dialogroverlocatelander.h"
#include"dialogroverlocate.h"
#include"dialogopenmatchpts.h"
#include"dialogdemmosaic.h"
#include"dialogdisparitymap.h"
#include"dialogpointcoord.h"
#include"dialogcamerasurvey.h"
#include"dialogsavepttofile.h"
#include"dialogepipolarimage.h"
#include"dialogrelativeorientation.h"


#include "SatMapProj.h"
#include "Sitemapproj.h"

#include "ImgPtDataSet.h"

//#include "mlGeoRaster.h";
//#include "ogr_spatialref.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE


//! [0]
class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer();
    ~ImageViewer();
    QProgressBar *m_ProgressBar;
    QLabel * m_ProgressBarLable;
    QLabel * LeftImgCoordLable;
    QLabel * RightImgCoordLable;
    // ��ӵ�Բ������
    int AddFeatPointStep;
    // �����������Ƭ������������Ƭ���
    int AddLeftOrRight;
    ULONG NewID;
    DialogPointCoord dlgPointCoord;

    string LeftPtPath;
    string RightPtPath;

    string strLeftOpenedImg, strRightOpenedImg;


private slots:
    void Contour();
    void open();

    void about();
    void rightopen();
    void OpenMatchPts();
    void OpenDenseMatchPts();
    void SavePtToFile();
    void SavePt();

    void CameraCalibration();
    void CameraSurvey();
    void SeriesImageDem();
    void OrbitImageDem();
    void PanoMosaic();
    void PersImageCreate();
    void SiteDemMosaic();
    void MultSiteDemMosaic();
    void WideBaselineMap();
    void WidebaseAnalysis();
    void TinSimplify();
    void DemDomProcess();
    void VisualImage();
    void ContourLine();
    void Slope();
    void SlopeAspect();
    void Barrier();
    void Insight();
    void DenseMatch();
    void DEMMosaic();
    void DisParityMap();
    void EpipolarImage();
    void RelOrientation();
    void LandLocate();
    void LandLocateMatch();
    void LandLocateInter();
    void CoordTransform();
    void RoverLocateLander();
    void RoverLocate();
    void ToolActEditMatchPointTooltriggered( );
    void ToolActPanTooltriggered( );
    void ToolActAddFeatPointTooltriggered( );
    void ToolActEditFeatPointTooltriggered( );
    void ToolActAddStereFeatPointtriggerd();
    void ToolActSemiAutoAddFeatPointtriggerd();
    void ToolActShowRegionPlanVecttriggerd();
    //����ͼ�������ƶ���,x��yΪscrollarea��imagelable���Ͻǵ�����
    void LeftImgMouseMove(int x, int y);
    void RightImgMouseMove(int x, int y);
    //����ͼƬ�������
    void LeftScrollAreaMousePress(QMouseEvent* mouseEvent);
    void RightScrollAreaMousePress(QMouseEvent* mouseEvent);
    void LeftScrollAreaMouseRealease(QMouseEvent* mouseEvent);
    void RightScrollAreaMouseRealease(QMouseEvent* mouseEvent);

    void on_PointTableView_doubleClicked(QModelIndex index);
    void on_LeftFeatPtTableView_doubleClicked(QModelIndex index);
    void on_RightFeatPtTableView_doubleClicked(QModelIndex index);

    void  On_LeftScrollAreaDelPts();
    void  On_RightScrollAreaDelPts();


public:


    //��Ρ���
    void SelectRightPtsByLeftSelection();
    void SelectLeftPtsByRightSelection();
    void UpdateFeatPtTableView();

    void AddLeftMatchPoints();
    void AddRightMatchPoints();
// ��ʼ�����������㼰ƥ�����
    void CheckIsMatch();

private:
    void createActions();
    void createMenus();
    void creatToolBar();

    void SetCurrentToolActionCheckStatus(QAction* act);
    void InitializeTableview();


    CmlSiteMapProj m_site;
    GaussianFilterOpt m_GauPara;
    MatchInRegPara m_MatchPara;
    RANSACHomePara m_RanPara;
    MLRectSearch m_RectSearch;
    WideOptions m_WidePara;
    ExtractFeatureOpt m_ExtractPara;
    SINT   m_nColRange, m_nRowRange;
    vector<StereoSet> m_vecStereoSet;

    ////////// LW  added

    int iwidth;          //ͼ����
    int iheight;         //ͼ��߶�

    //  ulong RasterWidth;// raster source width
    // ulong RasterHeight;// raster source length
    // RECT RasterRect;// Raster source envlop rect
    // RECT ImageRect;
    // POINT RasterTopLeftInCanvas;//
    // GDALDataset *poDataset; //  RasterDataset
    //������tablemodel
    QStandardItemModel* pMatchPtsTableModel;
    QStandardItemModel* LeftFeatPtTableModel;
    QStandardItemModel* RightFeatPtTableModel;

    //����ͼƬ�ĵ㼯
    CImgPtDataSet LeftFeatPtDataset;
    CImgPtDataSet RightFeatPtDataset;

    bool SetProgressBar( string strCaption, int nStart, int nEnd );
    bool SetValToProgressBar( int nPos );
    bool StepIn();

    int m_nCurPos;
public:
    CustomScroll *scrollArea;
    CustomScroll *RightScrollArea;
protected:

    //  DrawLabel *imageLabel;

    //double scaleFactor ;
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);




#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif
    //��������
    QAction *openAct;
    //QAction *printAct;
    QAction *exitAct;
    //QAction *zoomInAct;
    //QAction *zoomOutAct;
    //QAction *normalSizeAct;
    //QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QAction *ContourAct;
    QAction *RightopenAct;
    QAction *OpenMatchPtsAct;
    QAction *OpenDenseMatchPtsAct;
    QAction *SavePtToFileAct;
    QAction *SavePtAct;

    //���ν�����������
    QAction *actCameraCalibration;//����궨
    QAction *actCameraSurvey;//��Ŀ�������
    QAction *actSeriesImageDem;//����ͼ����½����ά�ع�
    QAction *actOrbitImageDem;//����Ӱ����½����ά�ع�
    QAction *actPanoMosaic;//ȫ��ͼ��ƴ��
    QAction *actPersImageCreate;//ԭ�ӵ���͸��ͼ������
    QAction *actSiteDemMosaic;//��վ�����ƴ��
    QAction *actMultSiteDemMosaic;//��վ�����ƴ��
    QAction *actWideBaselineMap;//�����߲�ͼ
    QAction *actWidebaseAnalysis;//�����߷���
    QAction *actTinSimplify;//TIN��
    QAction *actDemDomProcess;//DEM��DOM����
    QAction *actVisualImage;//ָ���ӽ�ͼ������
    QAction *actContourLine;//�ȸ�������
    QAction *actSlope;//�¶�����
    QAction *actSlopeAspect;//����ͼ����
    QAction *actBarrier;//�ϰ���ֲ�
    QAction *actInsight;//ͨ�ӷ���
    QAction *actDenseMatch;//�ܼ�ƥ��
    QAction *actDEMMosaic;// DEM pingjie
    QAction *actDisParityMap;//
    QAction *actEpipolarImage;//����Ӱ��
    QAction *actRelOrientation;//��Զ���


    //�Ӿ���λ��������
    QAction *actLandLocate;//��½����Զ�λ
    QAction *actLandLocateMatch;//����ͼ��ƥ�����½�㶨λ
    QAction *actLandLocateInter;//����ͼ��ƥ�����½�㶨λ
    QAction *actCoordTransform;//����ת��
    QAction *actRoverLocateLander;//Ѳ����ͬ��½����Զ�λ
    QAction *actRoverLocate;//Ѳ������λ

    //һ���˵�����
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *menuMo;
    QMenu *menuMc;
    QMenu *helpMenu;


    QVBoxLayout *LeftLayout;
    QVBoxLayout *RightLayout;
    QHBoxLayout * MainLayout;
    QSplitter * Splitter;
    QSplitter* MainSplitter;


    //�����ͼ
    //QTableView* TableView;
    QTableView* FileTableView;
    QTableView* PointTableView;
    QTableView* CustomTableView;
    QTableView* LeftFeatPtTableView;
    QTableView* RightFeatPtTableView;

    //���οؼ�
    QTreeView* ProjectTreeView;

    //������
    QToolBar* BasicToolBar;
    QAction* ToolActPanTool;
    QAction* ToolActEditMatchPoint;
    QAction* ToolActAddFeatPoint;
    QAction* ToolActAddStereFeatPoint;
    QAction* ToolActEditFeatPoint;
    QAction* ToolActSemiAutoAddFeatPoint;
    QAction* ToolActShowRegionPlanVect;
    QList<QAction*> MutexToolList;
    //״̬��
    QStatusBar* MainStatusBar;

private:
};


///////////////////////////////////////////////////////////////////////////




#endif
