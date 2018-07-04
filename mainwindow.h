#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsView>
#include <QPixmap>
#include <QVector>
#include <QPointF>

#include "patientdatabase.h"
#include "showtableform.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

static QImage Mat2QImage(Mat& image)
{
    QImage img;

    if (image.channels()==3) {
        cvtColor(image, image, CV_BGR2RGB);
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
                image.cols*image.channels(), QImage::Format_RGB888);
    } else if (image.channels()==1) {
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
                image.cols*image.channels(), QImage::Format_ARGB32);
    } else {
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
                image.cols*image.channels(), QImage::Format_RGB888);
    }

    return img;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void paintEvent(QPaintEvent *event);

public:
    void setDefaultParameters();

    bool updatePix();



private slots:
    void on_quickSearch_clicked();

    void on_saveImage_toolButton_clicked();

    void on_zoom_toolButton_clicked();

    void on_move_toolButton_clicked();

    void on_anticlockwise_toolButton_clicked();

    void on_clockwise_toolButton_clicked();

    void on_reset_toolButton_clicked();

    void on_unmarked_toolButton_clicked();

    void on_mark_toolButton_clicked();

    void on_marked_toolButton_clicked();

    void on_batchButton_clicked();

    void on_cutimage_toolButton_clicked();

   // void generateOriginPoints(const QPointF& pos);

    void on_caseManage_toolButton_clicked();




private:
    Ui::MainWindow *m_ui;

    QPixmap  *m_pix0;
    QPixmap  *m_pix;


    // Actions on mark tab
    int      m_action;
    QRect    m_paintRect;
    QRect    m_pixRect;
    QPoint   m_pixPos;
    QPoint   m_offset;

    int      m_rotate;

    float    m_ratio;

    QPoint   m_prePos;
    bool     m_press;

    QVector<QPoint> m_originPoints;
    QVector<QPoint> m_curvePoints;

    enum Type{
        None = 0,
        Zoom,
        Move,
        Rotation,
        Mark,
        Marked
    };

    /// list information
    QString  m_imageFileName;

    PatientDatabase *m_patientDatabase;
};

#endif // MAINWINDOW_H
