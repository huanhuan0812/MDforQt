// MRadioButton.h
#ifndef MRADIOBUTTON_H
#define MRADIOBUTTON_H

#include <QRadioButton>
#include <QPropertyAnimation>
#if defined(QMATERIALDESIGN_EXPORTS)
#  define QMATERIALDESIGN_API Q_DECL_EXPORT
#else
#  define QMATERIALDESIGN_API Q_DECL_IMPORT
#endif

class QMATERIALDESIGN_API MRadioButton : public QRadioButton
{
    Q_OBJECT
    Q_PROPERTY(QColor radioColor READ radioColor WRITE setRadioColor)

public:
    explicit MRadioButton(QWidget *parent = nullptr);
    explicit MRadioButton(const QString &text, QWidget *parent = nullptr);

    QColor radioColor() const;
    void setRadioColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

    QColor m_radioColor;
};

#endif // MRADIOBUTTON_H