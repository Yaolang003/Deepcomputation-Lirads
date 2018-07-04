#include "beziercurve.h"


float bezier3funcX(float uu, cv::Point *controlP){
   float part0 = controlP[0].x * uu * uu * uu;
   float part1 = 3 * controlP[1].x * uu * uu * (1 - uu);
   float part2 = 3 * controlP[2].x * uu * (1 - uu) * (1 - uu);
   float part3 = controlP[3].x * (1 - uu) * (1 - uu) * (1 - uu);
   return part0 + part1 + part2 + part3;
}

float bezier3funcY(float uu, cv::Point *controlP){
   float part0 = controlP[0].y * uu * uu * uu;
   float part1 = 3 * controlP[1].y * uu * uu * (1 - uu);
   float part2 = 3 * controlP[2].y * uu * (1 - uu) * (1 - uu);
   float part3 = controlP[3].y * (1 - uu) * (1 - uu) * (1 - uu);
   return part0 + part1 + part2 + part3;
}

void bezierCurve(const std::vector<cv::Point>& originPoints,
                 std::vector<cv::Point> &curvePoints){
    float scale = 0.6;
    float step = 0.01; //0.005;
    int originCount = originPoints.size();
    std::vector<cv::Point> midpoints(originCount);
    for(int i = 0 ;i < originCount ; i++){
        int nexti = (i + 1) % originCount;
        midpoints[i].x = (originPoints[i].x + originPoints[nexti].x)/2.0;
        midpoints[i].y = (originPoints[i].y + originPoints[nexti].y)/2.0;
    }
    std::vector<cv::Point> extrapoints(2 * originCount);
    for(int i = 0 ;i < originCount ; i++){
         int backi = (i + originCount - 1) % originCount;
         cv::Point midinmid;
         midinmid.x = (midpoints[i].x + midpoints[backi].x)/2.0;
         midinmid.y = (midpoints[i].y + midpoints[backi].y)/2.0;
         int offsetx = originPoints[i].x - midinmid.x;
         int offsety = originPoints[i].y - midinmid.y;
         int extraindex = 2 * i;
         extrapoints[extraindex].x = midpoints[backi].x + offsetx;
         extrapoints[extraindex].y = midpoints[backi].y + offsety;

         //朝 originPoints[i]方向收缩
         int addx = (extrapoints[extraindex].x - originPoints[i].x) * scale;
         int addy = (extrapoints[extraindex].y - originPoints[i].y) * scale;
         extrapoints[extraindex].x = originPoints[i].x + addx;
         extrapoints[extraindex].y = originPoints[i].y + addy;

         int extranexti = (extraindex + 1)%(2 * originCount);
         extrapoints[extranexti].x = midpoints[i].x + offsetx;
         extrapoints[extranexti].y = midpoints[i].y + offsety;
         //朝 originPoints[i]方向收缩
         addx = (extrapoints[extranexti].x - originPoints[i].x) * scale;
         addy = (extrapoints[extranexti].y - originPoints[i].y) * scale;
         extrapoints[extranexti].x = originPoints[i].x + addx;
         extrapoints[extranexti].y = originPoints[i].y + addy;

    }

    cv::Point controlPoint[4];
    //生成4控制点，产生贝塞尔曲线
    for(int i = 0 ;i < originCount ; i++){
           controlPoint[0] = originPoints[i];
           int extraindex = 2 * i;
           controlPoint[1] = extrapoints[extraindex + 1];
           int extranexti = (extraindex + 2) % (2 * originCount);
           controlPoint[2] = extrapoints[extranexti];
           int nexti = (i + 1) % originCount;
           controlPoint[3] = originPoints[nexti];
           float u = 1;
           while(u >= 0){
               int px = bezier3funcX(u,controlPoint);
               int py = bezier3funcY(u,controlPoint);
               //u的步长决定曲线的疏密
               u -= step;
               cv::Point tempP = cv::Point(px,py);
               //存入曲线点
               curvePoints.push_back(tempP);
           }
    }
}

void bezierCurve(QVector<QPoint> &originPoints,
                 QVector<QPoint> &curvePoints){
    std::vector<cv::Point> cv_originPoints;
    std::vector<cv::Point> cv_curvePoints;

    for(QVector<QPoint>::iterator it = originPoints.begin();
        it != originPoints.end(); ++it){
        cv_originPoints.push_back(cv::Point(it->x(), it->y() ));
    }

    bezierCurve(cv_originPoints, cv_curvePoints);

    curvePoints.clear();
    for(std::vector<cv::Point>::iterator it = cv_curvePoints.begin();
        it != cv_curvePoints.end(); ++it){
        curvePoints.push_back(QPoint(it->x, it->y) );
    }
}
