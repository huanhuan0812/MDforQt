// MProgressBar.h
#ifndef MPROGRESSBAR_H
#define MPROGRESSBAR_H

#include <QProgressBar>
#include <QPropertyAnimation>

#if defined(QMATERIALDESIGN_EXPORTS)
#  define QMATERIALDESIGN_API Q_DECL_EXPORT
#else
#  define QMATERIALDESIGN_API Q_DECL_IMPORT
#endif

class QMATERIALDESIGN_API MProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor)

public:
    explicit MProgressBar(QWidget *parent = nullptr);

    QColor progressColor() const;
    void setProgressColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

    QColor m_progressColor;
};

#endif // MPROGRESSBAR_H