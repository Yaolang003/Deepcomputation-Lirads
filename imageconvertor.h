#ifndef IMAGECONVERTOR_H
#define IMAGECONVERTOR_H



#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QtGlobal>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>



/*
      Little Endian
         QImage::Format_ARGB32 the bytes are ordered:    B G R A
         QImage::Format_RGB32 the bytes are ordered:     B G R (255)
         QImage::Format_RGB888 the bytes are ordered:    R G B

      Big Endian
         QImage::Format_ARGB32 the bytes are ordered:    A R G B
         QImage::Format_RGB32 the bytes are ordered:     (255) R G B
         QImage::Format_RGB888 the bytes are ordered:    R G B

   Notice that Format_RGB888 is the same regardless of endianness. Since OpenCV
   expects (B G R) we need to swap the channels for this format.

*/

#if Q_BYTE_ORDER == Q_BIG_ENDIAN
#error Some of QImage's formats are endian-dependant. This file assumes little endian. See comment at top of header.
#endif


QImage  cvMatToQImage( const cv::Mat &inMat );
QPixmap cvMatToQPixmap( const cv::Mat &inMat );

// If inImage exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inImage's
// data with the cv::Mat directly
//    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
//    NOTE: This does not cover all cases - it should be easy to add new ones as required.
cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true );
// If inPixmap exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inPixmap's data
// with the cv::Mat directly
//    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData = true );


#endif // IMAGECONVERTOR_H
