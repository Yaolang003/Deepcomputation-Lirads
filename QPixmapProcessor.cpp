#include "QPixmapProcessor.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QGraphicsSceneDragDropEvent>
#include <QDrag>
#include <math.h>
#include <iostream>

QPixmapProcessor::QPixmapProcessor(){
    setDefaultParameters();
}

QPixmapProcessor::QPixmapProcessor(const QString &fileName){
    setDefaultParameters();
    load(fileName);
}

QPixmapProcessor::QPixmapProcessor(const QPixmap &pixmap){
    setDefaultParameters();
    load(pixmap);
}

QRectF QPixmapProcessor::boundingRect() const{
    return QRectF(-m_pixmap.width() / 2, -m_pixmap.height() / 2,
                  m_pixmap.width(), m_pixmap.height());
}

void QPixmapProcessor::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                    QWidget *){
    painter->drawPixmap(-m_pixmap.width() / 2, -m_pixmap.height() / 2, m_pixmap);
}

void QPixmapProcessor::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(m_moveState){
       m_startPos = event->pos();
    }
}


void QPixmapProcessor::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(m_moveState){
        QPointF point = event->pos() - m_startPos;
        moveBy(point.x(), point.y());

        m_startPos = event->pos();
    }
  //  setTransformOriginPoint(event->pos().x(), event->pos().y());

}
/*
void QPixmapProcessor::dragMoveEvent(QGraphicsSceneDragDropEvent *event){
    if(m_moveState){
        QPointF point = event->pos() - m_startPos;
        moveBy(point.x(), point.y());
        m_startPos = event->pos();
    }
}
*/

//void QPixel

void QPixmapProcessor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){


}


void QPixmapProcessor::wheelEvent(QGraphicsSceneWheelEvent *event){
    int zoomTimes = m_zoomTimes;
    if(event->delta() > 0){
        zoomTimes++;
    }
    else{
        zoomTimes--;
    }
    scale(zoomTimes);
    setTransformOriginPoint(event->pos().x(), event->pos().y());

}

void QPixmapProcessor::load(const QPixmap &pixmap){
    m_pixmap = pixmap;
}

void QPixmapProcessor::load(const QString &fileName){
    m_fileName = fileName;
    m_pixmap.load(fileName);
}

void QPixmapProcessor::scale(const int &zoomTimes){
    m_zoomTimes = zoomTimes;
    scale();
}

void QPixmapProcessor::scale(){
    if (m_zoomTimes > m_maxZoomTimes)
        m_zoomTimes = m_maxZoomTimes;
    if(m_zoomTimes < -m_maxZoomTimes)
        m_zoomTimes = -m_maxZoomTimes;

    qreal s;
    if(m_zoomTimes > 0){
        s = std::pow(m_zoomFactor, m_zoomTimes);
    }
    else{
        s = std::pow(1 / m_zoomFactor, -m_zoomTimes);
    }
    setScale(s);
}

void QPixmapProcessor::setDefaultParameters(){
    setAcceptDrops(true);
    setMaxZoomTimes(20);
    setZoomFactor(1.1);
    setzoomTimes(0);
    setZoomState(false);
    setMoveState(true);
}

void QPixmapProcessor::setMaxZoomTimes(const int &maxZoomTimes){
    m_maxZoomTimes = std::fabs(maxZoomTimes);
    m_maxZoomTimes = m_maxZoomTimes > 1 ? m_maxZoomTimes : 1;
}

void QPixmapProcessor::setZoomFactor(const double &zoomFactor){
    m_zoomFactor = zoomFactor;
}

void QPixmapProcessor::setzoomTimes(const int &zoomTimes){
    m_zoomTimes = zoomTimes;
}

void QPixmapProcessor::setZoomState(const bool &zoomState){
    m_zoomState = zoomState;
    if(m_zoomState)
        m_moveState = false;
}

void QPixmapProcessor::setMoveState(const bool &moveState){
    m_moveState = moveState;
    if(m_moveState)
        m_zoomState = false;
}


int QPixmapProcessor::getMaxZoomTimes() const{
    return m_maxZoomTimes;
}

double QPixmapProcessor::getZoomFactor() const{
    return m_zoomFactor;
}

int QPixmapProcessor::getzoomTimes() const{
    return m_zoomTimes;
}

bool QPixmapProcessor::getZoomState() const{
    return m_zoomState;
}

bool QPixmapProcessor::getMoveSate() const{
    return m_moveState;
}

