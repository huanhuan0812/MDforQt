#ifndef MPUSHBUTTON_H
#define MPUSHBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QEasingCurve>
#include <QPainterPath>

#if defined(QMATERIALDESIGN_EXPORTS)
#  define QMATERIALDESIGN_API Q_DECL_EXPORT
#else
#  define QMATERIALDESIGN_API Q_DECL_IMPORT
#endif

class QMATERIALDESIGN_API MPushButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor rippleColor READ rippleColor WRITE setRippleColor NOTIFY rippleColorChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(qreal elevation READ elevation WRITE setElevation NOTIFY elevationChanged)
    Q_PROPERTY(qreal rippleRadius READ rippleRadius WRITE setRippleRadius NOTIFY rippleRadiusChanged)

public:
    explicit MPushButton(QWidget *parent = nullptr);
    explicit MPushButton(const QString &text, QWidget *parent = nullptr);
    ~MPushButton();

    // 属性获取和设置
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    QColor rippleColor() const;
    void setRippleColor(const QColor &color);

    QColor textColor() const;
    void setTextColor(const QColor &color);

    qreal elevation() const;
    void setElevation(qreal elevation);

    qreal rippleRadius() const;
    void setRippleRadius(qreal radius);

    // 设置按钮类型
    enum ButtonType {
        Contained,  // 实心按钮
        Outlined,   // 轮廓按钮
        Text        // 文本按钮
    };
    Q_ENUM(ButtonType)

    ButtonType buttonType() const;
    void setButtonType(ButtonType type);

signals:
    void backgroundColorChanged(const QColor &color);
    void rippleColorChanged(const QColor &color);
    void textColorChanged(const QColor &color);
    void elevationChanged(qreal elevation);
    void rippleRadiusChanged(qreal radius);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void updateShadow(); // 移除 animateRipple() 槽函数声明

private:
    void init();
    void drawRipple(QPainter *painter);
    void drawBackground(QPainter *painter);
    void drawText(QPainter *painter);

    QColor m_backgroundColor;
    QColor m_rippleColor;
    QColor m_textColor;
    qreal m_elevation;
    ButtonType m_buttonType;

    // 涟漪效果相关
    QPoint m_rippleCenter;
    qreal m_rippleRadius;
    QPropertyAnimation *m_rippleAnimation;
    bool m_mousePressed;

    // 状态
    bool m_hovered;
};

#endif // MPUSHBUTTON_H