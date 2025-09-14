// MRadioButton.cpp
#include "MRadioButton.h"
#include <QPainter>
#include <QPaintEvent>

MRadioButton::MRadioButton(QWidget *parent)
    : QRadioButton(parent)
    , m_radioColor(QColor(33, 150, 243))
{
    init();
}

void MRadioButton::init()
{
    setStyleSheet("QRadioButton { spacing: 8px; }");
}

QColor MRadioButton::radioColor() const
{
    return m_radioColor;
}

void MRadioButton::setRadioColor(const QColor &color)
{
    m_radioColor = color;
    update();
}

void MRadioButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制外圆
    QRect circleRect(0, (height() - 18) / 2, 18, 18);

    painter.setPen(QPen(QColor(180, 180, 180), 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(circleRect);

    // 如果选中，绘制内圆
    if (isChecked()) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(m_radioColor);
        painter.drawEllipse(circleRect);

        // 绘制中心白点
        painter.setBrush(Qt::white);
        painter.drawEllipse(circleRect.center(), 4, 4);
    }

    // 绘制文本
    if (!text().isEmpty()) {
        painter.setPen(palette().text().color());
        painter.drawText(26, 0, width() - 26, height(), Qt::AlignLeft | Qt::AlignVCenter, text());
    }
}

MRadioButton::MRadioButton(const QString &text, QWidget *parent)
    : QRadioButton(text, parent)
{
    setText(text);
    init();
}
