#include "clickablelabel.h"
#include <algorithm>
#include "qevent.h"
#include "ui_mainwindow.h"
#include <mainwindow.h>
#include <ActiveContour/activecontour.h>

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {



}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {

    MainWindow *Obj;

    xFactor = ClickableLabel::width() / 512.0;
    yFactor = ClickableLabel::height() / 512.0;

    QPoint point = event->pos();   

    if(Obj->inputImage.isNull()) return;

    Obj->xCoordinate = qCeil(point.x() / xFactor);
    Obj->yCoordinate = qCeil(point.y() / yFactor);

//    cout << " xFactor = " << xFactor << " yFactor = " << yFactor << endl;

//    cout << " x = " << Obj->xCoordinate << " y = " << Obj->yCoordinate << endl;

    // Get minimum distance between center and image boundaries
    minX = min(512 - Obj->xCoordinate, Obj->xCoordinate);
    minY = min(512 - Obj->yCoordinate, Obj->yCoordinate);

    Obj->ui->contourRadiusSlider->setMaximum( min(minX,minY) );


    active_Contour_Model(Obj->inputMat, Obj->activeContourOutputMat, Point(Obj->xCoordinate, Obj->yCoordinate), Obj->radius, Obj->numIterations, Obj->alpha, Obj->beta, Obj->gamma);
    Obj->updateImage(Obj->activeContourOutputMat, Obj->ui->activeContourOutputImage, 1);

    emit clicked();
}
