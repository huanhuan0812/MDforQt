// main.cpp 示例
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include "MPushButton.h"
#include "MLineEdit.h"
#include "MCard.h"
#include "MSlider.h"
#include "MSwitch.h"
#include "MCheckBox.h"
#include "MRadioButton.h"
#include "MProgressBar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);

    // 创建卡片容器
    MCard *card = new MCard();
    card->setFixedSize(400, 600);
    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setAlignment(Qt::AlignTop);
    cardLayout->setSpacing(20);
    cardLayout->setContentsMargins(20, 20, 20, 20);

    // 标题
    QLabel *title = new QLabel("Material Design Controls");
    title->setStyleSheet("font-size: 20px; font-weight: bold;");
    cardLayout->addWidget(title);

    // 输入框
    MLineEdit *lineEdit = new MLineEdit();
    lineEdit->setPlaceholderText("Enter text here...");
    cardLayout->addWidget(lineEdit);

    // 按钮
    MPushButton *button = new MPushButton("Click Me");
    button->setButtonType(MPushButton::Contained);
    cardLayout->addWidget(button);

    // 滑块
    MSlider *slider = new MSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(50);
    cardLayout->addWidget(slider);

    // 开关
    QHBoxLayout *switchLayout = new QHBoxLayout();
    switchLayout->addWidget(new QLabel("Toggle Switch:"));
    MSwitch *mswitch = new MSwitch();
    mswitch->setChecked(true);
    switchLayout->addWidget(mswitch);
    switchLayout->addStretch();
    cardLayout->addLayout(switchLayout);

    // 复选框
    MCheckBox *checkbox = new MCheckBox("Checkbox Option");
    checkbox->setChecked(true);
    cardLayout->addWidget(checkbox);

    // 单选按钮
    MRadioButton *radio1 = new MRadioButton("Option 1");
    MRadioButton *radio2 = new MRadioButton("Option 2");
    radio1->setChecked(true);
    cardLayout->addWidget(radio1);
    cardLayout->addWidget(radio2);

    // 进度条
    MProgressBar *progressBar = new MProgressBar();
    progressBar->setRange(0, 100);
    progressBar->setValue(75);
    cardLayout->addWidget(progressBar);

    // 添加到主布局
    mainLayout->addWidget(card, 0, Qt::AlignCenter);

    window.resize(800, 700);
    window.show();

    return a.exec();
}