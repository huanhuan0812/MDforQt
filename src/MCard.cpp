// MCard.cpp
#include "MCard.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

MCard::MCard(QWidget *parent)
    : QFrame(parent)
    , m_cornerRadius(4)
    , m_backgroundColor(Qt::white)
    , m_shadowEffect(new QGraphicsDropShadowEffect(this))
{
    init();
}

void MCard::init()
{
    setAttribute(Qt::WA_StyledBackground);

    m_shadowEffect->setBlurRadius(10);
    m_shadowEffect->setOffset(0, 2);
    m_shadowEffect->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(m_shadowEffect);
}

int MCard::cornerRadius() const
{
    return m_cornerRadius;
}

void MCard::setCornerRadius(int radius)
{
    m_cornerRadius = radius;
    update();
}

QColor MCard::backgroundColor() const
{
    return m_backgroundColor;
}

void MCard::setBackgroundColor(const QColor &color)
{
    m_backgroundColor = color;
    update();
}

void MCard::setShadowEnabled(bool enabled)
{
    m_shadowEffect->setEnabled(enabled);
}

bool MCard::isShadowEnabled() const
{
    return m_shadowEffect->isEnabled();
}

void MCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), m_cornerRadius, m_cornerRadius);

    painter.fillPath(path, m_backgroundColor);
}