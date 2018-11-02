#ifndef CUSTOMSCROLL_H
#define CUSTOMSCROLL_H
#include <QScrollArea>
//#include"../../3rdParty/gdal1.8.1/gdal_header.h"
#include <QPrinter>
#include"DrawLabel.h"
#include "CmlRasterBand.h"
#include"CmlRasterBand.h"
#include"computecontourline.h"

#include"ImgPtDataSet.h"
#include"qaction.h"
class ImageViewer;
typedef struct tagRRECT
{
        double    left;
        double    top;
        double    right;
        double    bottom;
} _mlRECT;

typedef struct _tagPOINT
{
        double  x;
        double  y;
} _mlPOINT;
enum ToolType
{
    Tool_None,
    Tool_pan,
    //�༭��
    Tool_EditMatchPoint,
    //���һ����
    Tool_AddFeatPoint,
    // ���һ�Ե�
    Tool_AddStereFeatPoint,
    Tool_EditFeatPoint,
    Tool_Draw,
    Tool_ToolActSemiAutoAddFeatPoint,
    //��ʾ����ƽ������
    Tool_ToolActShowRegionPlanVect
}  ;

class CustomScroll : public QScrollArea
{
    Q_OBJECT
public:
    CustomScroll( );
    QList<int>  FeatManualSelectedIdx;
    QList<int>  FeatAutoSelectedIdx;
    ImageViewer* MainFrame;
    CImgPtDataSet* FeatPtDataSet;
public:
    DrawLabel *imageLabel;

    ulong RasterWidth;// raster source width
    ulong RasterHeight;// raster source length
    _mlRECT RasterRect;// Raster source envlop rect
    // ��ͼʱ����դ���������Ͻ��ڻ����е�λ��
    _mlPOINT RasterTopLeftInCanvas;//
    // ��ͼʱͼƬ���Ͻ���raster�е�λ��
    _mlPOINT ImageLeftTopInRaster;
    // ��ͼʱͼƬ���Ͻ��ڻ����е�λ��
    _mlPOINT ImageLeftTopInCanvas;
    GDALDataset *poDataset; //  RasterDataset
    QVector<QRgb> ByteMapColorTable;  // ���ֽ�ͼƬ��ɫ��

     double scaleFactor ;
     ToolType CurrentToolType;
     // �ж����������Ƿ�ס�ı���
     bool MouseDown ;
     bool MouseLeftButtonDown;
     // �жϰ�ס������ʱ����ڻ����е�λ��
     _mlPOINT DownPoint;
     //�Ƿ�׽����
      bool PickedAPoint  ;

     bool ComputeImageSizeAndLocation(_mlRECT RasterSourceRect,
                                      double Scale,
                                      double &ImageWidth,
                                      double &ImageHeight ,
                                      _mlPOINT & LeftTopInRaster,
                                      _mlPOINT & LeftTopInCavas,
                                      _mlPOINT &RightBottomInRaster);

     bool ComputeRasterRect(_mlRECT &rasterRect,double Scale,_mlPOINT topleftincanvas);
     void LoadImage(char* fileName);

     bool CreatCopiedImage();
     void writeimage();
     // �����������Ϊ��imagelabel�е����꣬����scrollarea��viewport�е����겻ͬ
     void RasterLocationToCanvasLocation(double rx,double ry, double& cx,double &cy);
     // ���ڼ��������Ϊ����scrollarea��viewport�е�����
     void CanvasLocationToRasterLocation(double cx,double cy, double& rx,double &ry);
     void ProduceContourLine();
     // ��ָ��դ�����ݵ����
     void CenterRasterPoint(double pointx,double pointy);
     //���ŵ�ָ�������ݷ�Χ
     void ZoomToRect(_mlRECT rasterscoperect);

protected:
     void mousePressEvent(QMouseEvent *event);
     void wheelEvent(QWheelEvent *event) ;
     void mouseMoveEvent ( QMouseEvent * event ) ;
     void mouseReleaseEvent(QMouseEvent *event);
     void paintEvent ( QPaintEvent * event ) ;
     void resizeEvent ( QResizeEvent * event ) ;
     void keyPressEvent ( QKeyEvent * event );
     //void keyReleaseEvent ( QKeyEvent * event ) ;
     void DrawPicture();
     void scrollContentsBy(int dx,int dy);
     //����Ҽ������˵��¼�
     // �˺�������к���������ε�����Ҽ���mousepress�¼�
     void contextMenuEvent(QContextMenuEvent *event);


private:
     // ָ�����ָ��
     CustomScroll* scrollArea;

     QImage *image;
     //�����ε� cimage������image
     QImage timage;
     // δ���ε�image
     QImage cimage;
// �ж�srcrollbar����ʾ��Χ�����仯ʱ��Drawpicture���������û�������������𣬵������������ʱ��Ҫ����drawpicture
     bool ScopeChangedByClickScrollBar;
     double MinMaxValue[2];
     //ɾ�����Action
     QAction * ActDeleteSelectedPts;

     // �ڱ༭��Ĺ����У��ж��Ƿ����������˵�

 private slots:
     void DrawLabelMouseMoveSlot(int x, int y);
     void DeleteSelectedFeatPt();

signals:
     // ����ź�Ϊ������Imagelable���϶������Ļ����,Rasterrect��top��left������ʱ��֮�в��
     void DrawLabelMouseMoveSignal(int x, int y);

     // ����ź�Ϊ���scrollarea�Ӵ����ϽǶ������Ļ����
     void MousePressSignal(QMouseEvent* mouseEvent);
     void MouseReleaseSignal(QMouseEvent* mouseEvent);


     // ɾ���ź�
     void DelSelectedPts();

};

#endif // CUSTOMSCROLL_H

