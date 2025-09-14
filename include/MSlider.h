// MSlider.h
#ifndef MSLIDER_H
#define MSLIDER_H

#include <QSlider>
#include <QPropertyAnimation>
#if defined(QMATERIALDESIGN_EXPORTS)
#  define QMATERIALDESIGN_API Q_DECL_EXPORT
#else
#  define QMATERIALDESIGN_API Q_DECL_IMPORT
#endif

class QMATERIALDESIGN_API MSlider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(QColor sliderColor READ sliderColor WRITE setSliderColor)

public:
    explicit MSlider(QWidget *parent = nullptr);
    explicit MSlider(Qt::Orientation orientation, QWidget *parent = nullptr);

    QColor sliderColor() const;
    void setSliderColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void init();
    void drawSlider(QPainter &painter);
    void drawHandle(QPainter &painter);

    QColor m_sliderColor;
    bool m_pressed;
};

#endif // MSLIDER_H