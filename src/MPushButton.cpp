#include "MPushButton.h"
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QTimer>

MPushButton::MPushButton(QWidget *parent)
    : QPushButton(parent)
    , m_backgroundColor(QColor(33, 150, 243))  // 默认蓝色
    , m_rippleColor(QColor(255, 255, 255, 100))
    , m_textColor(Qt::white)
    , m_elevation(2.0)
    , m_buttonType(Contained)
    , m_rippleRadius(0)
    , m_mousePressed(false)
    , m_hovered(false)
{
    init();
}

MPushButton::MPushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
    , m_backgroundColor(QColor(33, 150, 243))
    , m_rippleColor(QColor(255, 255, 255, 100))
    , m_textColor(Qt::white)
    , m_elevation(2.0)
    , m_buttonType(Contained)
    , m_rippleRadius(0)
    , m_mousePressed(false)
    , m_hovered(false)
{
    init();
}

MPushButton::~MPushButton()
{
    delete m_rippleAnimation;
}

void MPushButton::init()
{
    // 设置按钮样式
    setCursor(Qt::PointingHandCursor);

    // 初始化涟漪动画
    m_rippleAnimation = new QPropertyAnimation(this, "rippleRadius");
    m_rippleAnimation->setEasingCurve(QEasingCurve::OutQuad);
    m_rippleAnimation->setDuration(500);

    // 连接动画结束信号，用于清除涟漪效果
    // connect(m_rippleAnimation, &QPropertyAnimation::finished, this, [this]() {
    //     // 使用单次定时器延迟清除涟漪，让效果完全显示
    //     QTimer::singleShot(100, this, [this]() {
    //         m_rippleRadius = 0;
    //         update();
    //     });
    // });

    // 在 init() 函数中修改连接
    connect(m_rippleAnimation, &QPropertyAnimation::finished, this, [this]() {
        m_rippleRadius = 0;
        update();
    });

    // 设置阴影效果
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(0, 3);
    shadowEffect->setColor(QColor(0, 0, 0, 80));
    setGraphicsEffect(shadowEffect);

    updateShadow();
}

QColor MPushButton::backgroundColor() const
{
    return m_backgroundColor;
}

void MPushButton::setBackgroundColor(const QColor &color)
{
    if (m_backgroundColor != color) {
        m_backgroundColor = color;
        emit backgroundColorChanged(color);
        update();
    }
}

QColor MPushButton::rippleColor() const
{
    return m_rippleColor;
}

void MPushButton::setRippleColor(const QColor &color)
{
    if (m_rippleColor != color) {
        m_rippleColor = color;
        emit rippleColorChanged(color);
        update();
    }
}

QColor MPushButton::textColor() const
{
    return m_textColor;
}

void MPushButton::setTextColor(const QColor &color)
{
    if (m_textColor != color) {
        m_textColor = color;
        emit textColorChanged(color);
        update();
    }
}

qreal MPushButton::elevation() const
{
    return m_elevation;
}

void MPushButton::setElevation(qreal elevation)
{
    if (!qFuzzyCompare(m_elevation, elevation)) {
        m_elevation = elevation;
        emit elevationChanged(elevation);
        updateShadow();
        update();
    }
}

qreal MPushButton::rippleRadius() const
{
    return m_rippleRadius;
}

void MPushButton::setRippleRadius(qreal radius)
{
    if (!qFuzzyCompare(m_rippleRadius, radius)) {
        m_rippleRadius = radius;
        emit rippleRadiusChanged(radius);
        update();
    }
}

MPushButton::ButtonType MPushButton::buttonType() const
{
    return m_buttonType;
}

void MPushButton::setButtonType(ButtonType type)
{
    if (m_buttonType != type) {
        m_buttonType = type;
        update();
    }
}

void MPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    drawBackground(&painter);

    // 绘制文本
    drawText(&painter);

    // 绘制涟漪效果（只在半径大于0时绘制）
    if (m_rippleRadius > 0) {
        drawRipple(&painter);
    }
}

void MPushButton::drawBackground(QPainter *painter)
{
    painter->save();

    QRect rect = this->rect();
    QPainterPath path;
    path.addRoundedRect(rect, 4, 4);

    switch (m_buttonType) {
    case Contained:
        painter->fillPath(path, m_backgroundColor);
        break;
    case Outlined:
        painter->setPen(QPen(m_backgroundColor, 1));
        painter->drawPath(path);
        break;
    case Text:
        // 文本按钮没有背景
        break;
    }

    painter->restore();
}

void MPushButton::drawText(QPainter *painter)
{
    painter->save();

    QColor color = m_textColor;
    if (m_buttonType != Contained) {
        color = m_backgroundColor;
    }

    painter->setPen(color);
    QFont font = this->font();
    font.setWeight(QFont::Medium);
    painter->setFont(font);
    painter->drawText(rect(), Qt::AlignCenter, text());

    painter->restore();
}

void MPushButton::drawRipple(QPainter *painter)
{
    painter->save();

    // 设置组合模式，让涟漪效果更加自然
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);

    // 创建涟漪路径
    QPainterPath ripplePath;
    ripplePath.addEllipse(m_rippleCenter, m_rippleRadius, m_rippleRadius);

    // 使用渐变填充涟漪效果，让边缘更加柔和
    QRadialGradient gradient(m_rippleCenter, m_rippleRadius);
    gradient.setColorAt(0, m_rippleColor);
    gradient.setColorAt(1, QColor(m_rippleColor.red(),
                                 m_rippleColor.green(),
                                 m_rippleColor.blue(), 0));

    painter->fillPath(ripplePath, gradient);

    painter->restore();
}

void MPushButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePressed = true;
        m_rippleCenter = event->position().toPoint();

        // 开始涟漪动画
        qreal maxRadius = qSqrt(qPow(width(), 2) + qPow(height(), 2));
        m_rippleAnimation->stop();
        m_rippleAnimation->setStartValue(0);
        m_rippleAnimation->setEndValue(maxRadius);
        m_rippleAnimation->start();
    }

    QPushButton::mousePressEvent(event);
}

void MPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_mousePressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void MPushButton::enterEvent(QEnterEvent *event)
{
    m_hovered = true;
    setElevation(4.0);  // 悬停时提升高度
    QPushButton::enterEvent(event);
}

void MPushButton::leaveEvent(QEvent *event)
{
    m_hovered = false;
    setElevation(2.0);  // 离开时恢复高度
    QPushButton::leaveEvent(event);
}

void MPushButton::updateShadow()
{
    auto shadowEffect = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
    if (shadowEffect) {
        shadowEffect->setBlurRadius(m_elevation * 5);
        shadowEffect->setOffset(0, m_elevation);
    }
}