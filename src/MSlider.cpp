// MSlider.cpp
#include "MSlider.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

MSlider::MSlider(QWidget *parent)
    : QSlider(parent)
    , m_sliderColor(QColor(33, 150, 243))
    , m_pressed(false)
{
    init();
}

MSlider::MSlider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent)
    , m_sliderColor(QColor(33, 150, 243))
    , m_pressed(false)
{
    init();
}

void MSlider::init()
{
    setStyleSheet("QSlider { background: transparent; }");
}

QColor MSlider::sliderColor() const
{
    return m_sliderColor;
}

void MSlider::setSliderColor(const QColor &color)
{
    m_sliderColor = color;
    update();
}

void MSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawSlider(painter);
    drawHandle(painter);
}

void MSlider::drawSlider(QPainter &painter)
{
    int sliderHeight = 4;
    int handleRadius = 8;

    QRect sliderRect;
    if (orientation() == Qt::Horizontal) {
        sliderRect = QRect(handleRadius, height()/2 - sliderHeight/2,
                          width() - 2*handleRadius, sliderHeight);
    } else {
        sliderRect = QRect(width()/2 - sliderHeight/2, handleRadius,
                          sliderHeight, height() - 2*handleRadius);
    }

    // 绘制背景轨道
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(200, 200, 200));
    painter.drawRoundedRect(sliderRect, sliderHeight/2, sliderHeight/2);

    // 绘制进度轨道
    qreal progress = (value() - minimum()) / static_cast<qreal>(maximum() - minimum());
    QRect progressRect;

    if (orientation() == Qt::Horizontal) {
        int progressWidth = progress * sliderRect.width();
        progressRect = QRect(sliderRect.x(), sliderRect.y(), progressWidth, sliderRect.height());
    } else {
        int progressHeight = progress * sliderRect.height();
        progressRect = QRect(sliderRect.x(), sliderRect.bottom() - progressHeight,
                            sliderRect.width(), progressHeight);
    }

    painter.setBrush(m_sliderColor);
    painter.drawRoundedRect(progressRect, sliderHeight/2, sliderHeight/2);
}

void MSlider::drawHandle(QPainter &painter)
{
    int handleRadius = m_pressed ? 10 : 8;
    qreal progress = (value() - minimum()) / static_cast<qreal>(maximum() - minimum());

    QPoint handleCenter;
    if (orientation() == Qt::Horizontal) {
        int x = handleRadius + progress * (width() - 2 * handleRadius);
        handleCenter = QPoint(x, height()/2);
    } else {
        int y = height() - handleRadius - progress * (height() - 2 * handleRadius);
        handleCenter = QPoint(width()/2, y);
    }

    // 绘制手柄
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_sliderColor);
    painter.drawEllipse(handleCenter, handleRadius, handleRadius);

    // 绘制内圈
    if (m_pressed) {
        painter.setBrush(QColor(255, 255, 255, 100));
        painter.drawEllipse(handleCenter, handleRadius + 5, handleRadius + 5);
    }
}

void MSlider::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    update();
    QSlider::mousePressEvent(event);
}

void MSlider::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    update();
    QSlider::mouseReleaseEvent(event);
}