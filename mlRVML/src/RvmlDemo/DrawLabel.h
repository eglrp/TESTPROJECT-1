#ifndef DRAWLABEL_H
#define DRAWLABEL_H
#include <QLabel>
#include <QPrinter>
#include <QPen>
#include "computecontourline.h"

class CustomScroll;

class DrawLabel : public QLabel
{
    Q_OBJECT
public:
    DrawLabel( );
public:
    QImage* image;
    QPoint DrawPoint;
    vector<ContourLine*> * Lineset;
    CustomScroll* FatherScroll ;
    QColor colorRed/*(255,0,0)*/;
    QColor colorGreen/*(0,255,0)*/;
    QColor colorlightRed;
    QColor colorYellow;
    QColor colorlightYellow;
    QPen pen;
    //�����Ƿ���Ҫ���ƾ���
    bool DrawRect;

    struct MouseRect
    {
        double ltx;
        double lty;
        double rbx;
        double rby;
    } rect;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent ( QKeyEvent * event );
    void mouseMoveEvent(QMouseEvent * event);
    void DrawFeatPoints(QPainter* painter);
    void DrawSelectedFeatPoints(QPainter* painter);
    // ��ѡ����ʱ��ľ��ο�
    void DrawSelectRect(QPainter* painter,MouseRect mrect);


signals:
    // ����ź��е�x��yΪ��� drawpoint�Ĳ�
    void mouseMoveSignal(int x, int y);



};

#endif // DRAWLABEL_H
