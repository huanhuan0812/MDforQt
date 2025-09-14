// MLineEdit.cpp
#include "MLineEdit.h"
#include <QPainter>
#include <QPaintEvent>

MLineEdit::MLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , m_lineColor(QColor(33, 150, 243))
    , m_lineWidth(1.0f)
    , m_animation(new QPropertyAnimation(this, "lineWidth"))
{
    init();
}

MLineEdit::MLineEdit(const QString &text, QWidget *parent)
    : QLineEdit(text, parent)
    , m_lineColor(QColor(33, 150, 243))
    , m_lineWidth(1.0f)
    , m_animation(new QPropertyAnimation(this, "lineWidth"))
{
    init();
}

void MLineEdit::init()
{
    setStyleSheet("QLineEdit { border: none; background: transparent; padding: 8px 0; }");
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::OutQuad);
}

QColor MLineEdit::lineColor() const
{
    return m_lineColor;
}

void MLineEdit::setLineColor(const QColor &color)
{
    m_lineColor = color;
    update();
}

float MLineEdit::lineWidth() const
{
    return m_lineWidth;
}

void MLineEdit::setLineWidth(float width)
{
    m_lineWidth = width;
    update();
}

void MLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制底线
    QPen pen(m_lineColor);
    pen.setWidthF(m_lineWidth);
    painter.setPen(pen);

    int y = height() - 1;
    painter.drawLine(0, y, width(), y);
}

void MLineEdit::focusInEvent(QFocusEvent *event)
{
    animateLine(true);
    QLineEdit::focusInEvent(event);
}

void MLineEdit::focusOutEvent(QFocusEvent *event)
{
    animateLine(false);
    QLineEdit::focusOutEvent(event);
}

void MLineEdit::animateLine(bool focused)
{
    m_animation->stop();
    m_animation->setStartValue(m_lineWidth);
    m_animation->setEndValue(focused ? 2.0f : 1.0f);
    m_animation->start();
}