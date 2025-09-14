// MSwitch.h
#ifndef MSWITCH_H
#define MSWITCH_H

#include <QCheckBox>
#include <QPropertyAnimation>
#if defined(QMATERIALDESIGN_EXPORTS)
#  define QMATERIALDESIGN_API Q_DECL_EXPORT
#else
#  define QMATERIALDESIGN_API Q_DECL_IMPORT
#endif

class QMATERIALDESIGN_API MSwitch : public QCheckBox
{
    Q_OBJECT
    Q_PROPERTY(QColor switchColor READ switchColor WRITE setSwitchColor)

public:
    explicit MSwitch(QWidget *parent = nullptr);

    QColor switchColor() const;
    void setSwitchColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

    QColor m_switchColor;
    QPropertyAnimation *m_animation;
};

#endif // MSWITCH_H