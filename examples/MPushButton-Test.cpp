#include "MPushButton.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QSlider>
#include <QColorDialog>
#include <QRandomGenerator>

class MaterialDesignDemo : public QWidget
{
    Q_OBJECT

public:
    MaterialDesignDemo(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setupUI();
        setupConnections();
    }

private:
    void setupUI()
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // 标题
        QLabel *titleLabel = new QLabel("Material Design 按钮示例");
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont titleFont;
        titleFont.setPointSize(18);
        titleFont.setWeight(QFont::Bold);
        titleLabel->setFont(titleFont);
        mainLayout->addWidget(titleLabel);

        // 按钮示例区域
        QGroupBox *buttonGroup = new QGroupBox("按钮类型示例");
        QVBoxLayout *buttonLayout = new QVBoxLayout(buttonGroup);

        // 实心按钮
        MPushButton *containedButton = new MPushButton("实心按钮 (Contained)");
        containedButton->setButtonType(MPushButton::Contained);
        containedButton->setBackgroundColor(QColor(33, 150, 243)); // 蓝色
        buttonLayout->addWidget(containedButton);

        // 轮廓按钮
        MPushButton *outlinedButton = new MPushButton("轮廓按钮 (Outlined)");
        outlinedButton->setButtonType(MPushButton::Outlined);
        outlinedButton->setBackgroundColor(QColor(156, 39, 176)); // 紫色
        buttonLayout->addWidget(outlinedButton);

        // 文本按钮
        MPushButton *textButton = new MPushButton("文本按钮 (Text)");
        textButton->setButtonType(MPushButton::Text);
        textButton->setBackgroundColor(QColor(255, 87, 34)); // 橙色
        buttonLayout->addWidget(textButton);

        mainLayout->addWidget(buttonGroup);

        // 颜色控制区域
        QGroupBox *controlGroup = new QGroupBox("颜色控制");
        QVBoxLayout *controlLayout = new QVBoxLayout(controlGroup);

        // 背景色选择
        QHBoxLayout *bgColorLayout = new QHBoxLayout();
        bgColorLayout->addWidget(new QLabel("背景色:"));
        m_bgColorButton = new MPushButton("选择颜色");
        m_bgColorButton->setButtonType(MPushButton::Outlined);
        bgColorLayout->addWidget(m_bgColorButton);
        bgColorLayout->addStretch();
        controlLayout->addLayout(bgColorLayout);

        // 涟漪颜色选择
        QHBoxLayout *rippleColorLayout = new QHBoxLayout();
        rippleColorLayout->addWidget(new QLabel("涟漪色:"));
        m_rippleColorButton = new MPushButton("选择颜色");
        m_rippleColorButton->setButtonType(MPushButton::Outlined);
        rippleColorLayout->addWidget(m_rippleColorButton);
        rippleColorLayout->addStretch();
        controlLayout->addLayout(rippleColorLayout);

        // 文字颜色选择
        QHBoxLayout *textColorLayout = new QHBoxLayout();
        textColorLayout->addWidget(new QLabel("文字色:"));
        m_textColorButton = new MPushButton("选择颜色");
        m_textColorButton->setButtonType(MPushButton::Outlined);
        textColorLayout->addWidget(m_textColorButton);
        textColorLayout->addStretch();
        controlLayout->addLayout(textColorLayout);

        // 高度控制
        QHBoxLayout *elevationLayout = new QHBoxLayout();
        elevationLayout->addWidget(new QLabel("高度:"));
        QSlider *elevationSlider = new QSlider(Qt::Horizontal);
        elevationSlider->setRange(0, 10);
        elevationSlider->setValue(2);
        elevationLayout->addWidget(elevationSlider);
        controlLayout->addLayout(elevationLayout);

        mainLayout->addWidget(controlGroup);

        // 动态按钮区域
        QGroupBox *dynamicGroup = new QGroupBox("动态按钮");
        QVBoxLayout *dynamicLayout = new QVBoxLayout(dynamicGroup);

        // 动态改变颜色的按钮
        m_dynamicButton = new MPushButton("点击我改变颜色!");
        m_dynamicButton->setButtonType(MPushButton::Contained);
        dynamicLayout->addWidget(m_dynamicButton);

        mainLayout->addWidget(dynamicGroup);

        // 状态显示
        QGroupBox *statusGroup = new QGroupBox("按钮状态");
        QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
        m_statusLabel = new QLabel("等待按钮点击...");
        statusLayout->addWidget(m_statusLabel);
        mainLayout->addWidget(statusGroup);

        mainLayout->addStretch();

        // 存储示例按钮用于颜色控制
        m_exampleButtons.append(containedButton);
        m_exampleButtons.append(outlinedButton);
        m_exampleButtons.append(textButton);

        // 设置初始颜色
        m_currentBgColor = QColor(33, 150, 243);
        m_currentRippleColor = QColor(255, 255, 255, 100);
        m_currentTextColor = Qt::white;
    }

    void setupConnections()
    {
        // 连接颜色选择按钮
        connect(m_bgColorButton, &MPushButton::clicked, this, [this]() {
            QColor color = QColorDialog::getColor(m_currentBgColor, this, "选择背景色");
            if (color.isValid()) {
                m_currentBgColor = color;
                updateButtonColors();
            }
        });

        connect(m_rippleColorButton, &MPushButton::clicked, this, [this]() {
            QColor color = QColorDialog::getColor(m_currentRippleColor, this, "选择涟漪颜色");
            if (color.isValid()) {
                m_currentRippleColor = color;
                updateButtonColors();
            }
        });

        connect(m_textColorButton, &MPushButton::clicked, this, [this]() {
            QColor color = QColorDialog::getColor(m_currentTextColor, this, "选择文字颜色");
            if (color.isValid()) {
                m_currentTextColor = color;
                updateButtonColors();
            }
        });

        // 连接高度滑块
        QSlider *elevationSlider = findChild<QSlider*>();
        if (elevationSlider) {
            connect(elevationSlider, &QSlider::valueChanged, this, [this](int value) {
                for (MPushButton *button : m_exampleButtons) {
                    button->setElevation(value);
                }
                m_dynamicButton->setElevation(value);
            });
        }

        // 连接动态按钮
        connect(m_dynamicButton, &MPushButton::clicked, this, [this]() {
            // 随机生成新颜色
            QColor newColor(QRandomGenerator::global()->bounded(256),
                           QRandomGenerator::global()->bounded(256),
                           QRandomGenerator::global()->bounded(256));
            
            m_dynamicButton->setBackgroundColor(newColor);
            m_dynamicButton->setText(QString("新颜色: %1").arg(newColor.name()));
            
            m_statusLabel->setText(QString("动态按钮颜色已改为: %1").arg(newColor.name()));
        });

        // 连接所有示例按钮的点击信号
        for (MPushButton *button : m_exampleButtons) {
            connect(button, &MPushButton::clicked, this, [this, button]() {
                QString type;
                switch (button->buttonType()) {
                case MPushButton::Contained: type = "实心按钮"; break;
                case MPushButton::Outlined: type = "轮廓按钮"; break;
                case MPushButton::Text: type = "文本按钮"; break;
                }
                m_statusLabel->setText(QString("点击了: %1 (%2)").arg(button->text()).arg(type));
            });
        }
    }

    void updateButtonColors()
    {
        for (MPushButton *button : m_exampleButtons) {
            button->setBackgroundColor(m_currentBgColor);
            button->setRippleColor(m_currentRippleColor);
            button->setTextColor(m_currentTextColor);
        }
    }

private:
    QList<MPushButton*> m_exampleButtons;
    MPushButton *m_bgColorButton;
    MPushButton *m_rippleColorButton;
    MPushButton *m_textColorButton;
    MPushButton *m_dynamicButton;
    QLabel *m_statusLabel;
    
    QColor m_currentBgColor;
    QColor m_currentRippleColor;
    QColor m_currentTextColor;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用程序样式
    app.setStyle("Fusion");
    
    MaterialDesignDemo demo;
    demo.setWindowTitle("Material Design 按钮示例");
    demo.resize(500, 600);
    demo.show();
    
    return app.exec();
}

#include "MPushButton-Test.moc"