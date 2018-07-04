#ifndef QPIXMAPPROCESSOR_H
#define QPIXMAPPROCESSOR_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
#include <QMouseEvent>
#include <QPointF>
#include <QDragEnterEvent>
#include <QGraphicsSceneWheelEvent>
#include <QString>


class QPixmapProcessor : public QGraphicsItem
{
public:
    QPixmapProcessor();
    QPixmapProcessor(const QString &fileName);
    QPixmapProcessor(const QPixmap &pixmap);

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void wheelEvent(QGraphicsSceneWheelEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
 //   void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
public:
    void load(const QString& fileName);
    void load(const QPixmap &pixmap);
    void scale(const int &zoomTimes);
    void scale();


    void setDefaultParameters();

    void setMaxZoomTimes(const int &maxZoomTimes);
    void setZoomFactor(const double &zoomFactor);
    void setzoomTimes(const int &zoomTimes);
    void setZoomState(const bool  &zoomState);
    void setMoveState(const bool &moveState);

    int getMaxZoomTimes() const;
    double  getZoomFactor() const;
    int  getzoomTimes() const;
    bool getZoomState() const;
    bool getMoveSate() const;

public:
    int m_maxZoomTimes;

    QString m_fileName;
    QPixmap m_pixmap;

    double  m_zoomFactor;
    qreal   m_zoomTimes;
    bool    m_zoomState;
    bool    m_moveState;


    QPointF m_startPos;

};

#endif // QPIXMAPPROCESSOR_H
