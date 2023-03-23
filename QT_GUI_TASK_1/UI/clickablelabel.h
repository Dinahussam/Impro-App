#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>




class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();



    float xFactor;
    float yFactor;
    int minX;
    int minY;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // CLICKABLELABEL_H

