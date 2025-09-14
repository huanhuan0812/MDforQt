// MCheckBox.cpp
#include "MCheckBox.h"
#include <QPainter>
#include <QPaintEvent>

MCheckBox::MCheckBox(QWidget *parent)
    : QCheckBox(parent)
    , m_checkColor(QColor(33, 150, 243))
{
    init();
}

void MCheckBox::init()
{
    setStyleSheet("QCheckBox { spacing: 8px; }");
}

QColor MCheckBox::checkColor() const
{
    return m_checkColor;
}

void MCheckBox::setCheckColor(const QColor &color)
{
    m_checkColor = color;
    update();
}

void MCheckBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制复选框外框
    QRect boxRect(0, (height() - 18) / 2, 18, 18);

    painter.setPen(QPen(QColor(180, 180, 180), 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(boxRect, 2, 2);

    // 如果选中，绘制对勾
    if (isChecked()) {
        painter.setPen(QPen(m_checkColor, 2));
        painter.setBrush(m_checkColor);

        // 绘制背景
        painter.drawRoundedRect(boxRect, 2, 2);

        // 绘制对勾
        painter.setPen(QPen(Qt::white, 2));
        painter.drawLine(4, height()/2, 7, height()/2 + 4);
        painter.drawLine(7, height()/2 + 4, 14, height()/2 - 4);
    }

    // 绘制文本
    if (!text().isEmpty()) {
        painter.setPen(palette().text().color());
        painter.drawText(26, 0, width() - 26, height(), Qt::AlignLeft | Qt::AlignVCenter, text());
    }
}

MCheckBox::MCheckBox(const QString &text, QWidget *parent)
    : QCheckBox(parent)
{
    setText(text);
    init();
}