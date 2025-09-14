// MSwitch.cpp
#include "MSwitch.h"
#include <QPainter>
#include <QPaintEvent>

MSwitch::MSwitch(QWidget *parent)
    : QCheckBox(parent)
    , m_switchColor(QColor(76, 175, 80))
    , m_animation(new QPropertyAnimation(this, "geometry"))
{
    init();
}

void MSwitch::init()
{
    setFixedSize(36, 20);
}

QColor MSwitch::switchColor() const
{
    return m_switchColor;
}

void MSwitch::setSwitchColor(const QColor &color)
{
    m_switchColor = color;
    update();
}

void MSwitch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景轨道
    QRect trackRect(2, 6, width() - 4, 8);
    painter.setPen(Qt::NoPen);

    if (isChecked()) {
        painter.setBrush(m_switchColor);
    } else {
        painter.setBrush(QColor(180, 180, 180));
    }

    painter.drawRoundedRect(trackRect, 4, 4);

    // 绘制开关按钮
    int thumbPos = isChecked() ? width() - 10 : 10;
    QPoint thumbCenter(thumbPos, height()/2);

    painter.setBrush(isChecked() ? m_switchColor : QColor(250, 250, 250));
    painter.setPen(QPen(QColor(180, 180, 180), 1));
    painter.drawEllipse(thumbCenter, 8, 8);
}