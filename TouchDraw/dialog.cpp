#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QPushButton>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent, Qt::FramelessWindowHint)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_QImage = new QImage(QSize(1024, 600), QImage::Format_RGB32);
    m_QImage->fill(Qt::white);
    m_QPushButton = new QPushButton("exit", this);
    m_QPushButton->setGeometry(800, 300, 50, 30);
    connect(m_QPushButton, SIGNAL(clicked()), this, SLOT(accept()));
}

Dialog::~Dialog()
{
    delete m_QImage;
    delete m_QPushButton;
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawImage(rect(), *m_QImage, m_QImage->rect());
    p.drawText(QRect(0,502, 1024,98),Qt::AlignCenter,
               QString::number(m_pointPosPrev.x()) + ", " + QString::number(m_pointPosPrev.y()));
}
void Dialog::mousePressEvent(QMouseEvent *e)
{
    m_bDraw = true;
    m_pointPosPrev = e->pos();
}
void Dialog::mouseReleaseEvent(QMouseEvent *e)
{
    m_bDraw = false;
}
void Dialog::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bDraw)
    {
        QPainter p(m_QImage);
        p.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(m_pointPosPrev, e->pos());
        m_pointPosPrev = e->pos();
        update();
    }
}
