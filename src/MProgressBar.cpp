// MProgressBar.cpp
#include "MProgressBar.h"
#include <QPainter>
#include <QPaintEvent>

MProgressBar::MProgressBar(QWidget *parent)
    : QProgressBar(parent)
    , m_progressColor(QColor(33, 150, 243))
{
    init();
}

void MProgressBar::init()
{
    setTextVisible(false);
}

QColor MProgressBar::progressColor() const
{
    return m_progressColor;
}

void MProgressBar::setProgressColor(const QColor &color)
{
    m_progressColor = color;
    update();
}

void MProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int progressHeight = 4;
    int borderRadius = progressHeight / 2;

    // 绘制背景
    QRect bgRect(0, (height() - progressHeight) / 2, width(), progressHeight);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(200, 200, 200));
    painter.drawRoundedRect(bgRect, borderRadius, borderRadius);

    // 绘制进度
    qreal progress = value() / static_cast<qreal>(maximum() - minimum());
    int progressWidth = progress * width();
    QRect progressRect(0, (height() - progressHeight) / 2, progressWidth, progressHeight);

    painter.setBrush(m_progressColor);
    painter.drawRoundedRect(progressRect, borderRadius, borderRadius);
}