// MCard.h
#ifndef MCARD_H
#define MCARD_H

#include <QFrame>
#include <QGraphicsDropShadowEffect>

#if defined(QMATERIALDESIGN_EXPORTS)
#  define QMATERIALDESIGN_API Q_DECL_EXPORT
#else
#  define QMATERIALDESIGN_API Q_DECL_IMPORT
#endif

class QMATERIALDESIGN_API MCard : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int cornerRadius READ cornerRadius WRITE setCornerRadius)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit MCard(QWidget *parent = nullptr);

    int cornerRadius() const;
    void setCornerRadius(int radius);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    void setShadowEnabled(bool enabled);
    bool isShadowEnabled() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

    int m_cornerRadius;
    QColor m_backgroundColor;
    QGraphicsDropShadowEffect *m_shadowEffect;
};

#endif // MCARD_H