// MCheckBox.h
#ifndef MCHECKBOX_H
#define MCHECKBOX_H

#include <QCheckBox>
#include <QPropertyAnimation>

#if defined(QMATERIALDESIGN_EXPORTS)
#  define QMATERIALDESIGN_API Q_DECL_EXPORT
#else
#  define QMATERIALDESIGN_API Q_DECL_IMPORT
#endif

class QMATERIALDESIGN_API MCheckBox : public QCheckBox
{
    Q_OBJECT
    Q_PROPERTY(QColor checkColor READ checkColor WRITE setCheckColor)

public:
    explicit MCheckBox(QWidget *parent = nullptr);
    explicit MCheckBox(const QString &text, QWidget *parent = nullptr);

    QColor checkColor() const;
    void setCheckColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

    QColor m_checkColor;
};

#endif // MCHECKBOX_H