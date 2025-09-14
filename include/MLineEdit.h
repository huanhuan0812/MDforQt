// MLineEdit.h
#ifndef MLINEEDIT_H
#define MLINEEDIT_H

#include <QLineEdit>
#include <QPropertyAnimation>

#if defined(QMATERIALDESIGN_EXPORTS)
#  define QMATERIALDESIGN_API Q_DECL_EXPORT
#else
#  define QMATERIALDESIGN_API Q_DECL_IMPORT
#endif

class QMATERIALDESIGN_API MLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(float lineWidth READ lineWidth WRITE setLineWidth)

public:
    explicit MLineEdit(QWidget *parent = nullptr);
    explicit MLineEdit(const QString &text, QWidget *parent = nullptr);

    QColor lineColor() const;
    void setLineColor(const QColor &color);

    float lineWidth() const;
    void setLineWidth(float width);

protected:
    void paintEvent(QPaintEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    void init();
    void animateLine(bool focused);

    QColor m_lineColor;
    float m_lineWidth;
    QPropertyAnimation *m_animation;
};

#endif // MLINEEDIT_H