#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <QVector>
#include <QPoint>
#include <math.h>


float bezier3funcX(float uu, cv::Point *controlP);
float bezier3funcY(float uu, cv::Point *controlP);
void  bezierCurve(const std::vector<cv::Point>& originPoints,
                  std::vector<cv::Point> &curvePoints);

void  bezierCurve(QVector<QPoint> &originPoints,
                  QVector<QPoint> &curvePoints);
//void drawBezierCurve(const std::vector<cv::Point>& originPoint);


#endif // BEZIERCURVE_H
