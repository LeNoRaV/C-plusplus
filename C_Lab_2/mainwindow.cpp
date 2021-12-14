#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CreateDefaultCalcWidget();
    CreateSimpleCalcWidget();
    CreateEngineeringWidget();

    mainWidget = new QWidget;
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::CreateDefaultCalcWidget(){
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    QString StyleSheetLine = "QLineEdit {font: 26pt 'Microsoft YaHei UI'; qproperty-alignment: AlignRight; padding: 5px; border: none; background-color: #F2F2F2;}";
    QString StyleSheetRadioButton = "QRadioButton {background-color: #E6E6E6; font: 10pt 'Microsoft YaHei UI Light'; padding: 0px 0px 0px 20px;} QRadioButton::indicator { width: 15px; height: 15px;}";

    simpleCalc = new QRadioButton("Simple Calculator");
    simpleCalc->setChecked(true);
    engineeringCalc = new QRadioButton("Engineering Calculator");

    defaultCalcLayout = new QGridLayout(this);
    defaultCalcLayout->setSpacing(0);
    defaultCalcLayout->setContentsMargins(0, 0, 0, 0);

    defaultCalcLayout->addWidget(simpleCalc, 1, 0, 1, 4);
    defaultCalcLayout->addWidget(engineeringCalc, 2, 0, 1, 4);
    defaultCalcLayout->addWidget(display, 0, 0, 1, 5);

    defaultCalcWidget = new QWidget(this);
    defaultCalcWidget->setLayout(defaultCalcLayout);

    display->setStyleSheet(StyleSheetLine);
    simpleCalc->setStyleSheet(StyleSheetRadioButton);
    engineeringCalc->setStyleSheet(StyleSheetRadioButton);

}
void MainWindow::CreateSimpleCalcWidget(){
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    QString StyleSheetNumbers = "QToolButton { color: black; background-color: #FAFAFA; border: none; font: 17pt 'Microsoft YaHei UI'; outline: none;} QToolButton:hover { background-color: #D8D8D8; border-style: solid; border-width: 3px; border-color: #F2F2F2; } QToolButton:pressed { background-color: #A4A4A4; border-style: solid; border-width: 3px; border-color: #E6E6E6; }";
    QString StyleSheetSigns =   "QToolButton { color: black; background-color: #E6E6E6; border: none; font: 19pt 'Microsoft YaHei UI Light'; outline: none; } QToolButton:hover { background-color: #2ECCFA; border-style: solid; border-width: 3px; border-color: #58D3F7; } QToolButton:pressed { background-color: #81DAF5; border-style: solid; border-width: 3px; border-color: #A9E2F3; }";

    simpleCalc = new QRadioButton("Simple Calculator");
    simpleCalc->setChecked(true);
    engineeringCalc = new QRadioButton("Engineering Calculator");


    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
    Button *clearAllButton = createButton(tr("C"), SLOT(clearAll()));
    Button *divisionButton = createButton(tr("/"), SLOT(multiplicativeOperatorClicked()));
    Button *timesButton = createButton(tr("*"), SLOT(multiplicativeOperatorClicked()));
    Button *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    Button *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));
    Button *squareRootButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClicked()));
    Button *reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClicked()));
    Button *equalButton = createButton(tr("="), SLOT(equalClicked()));

    simpleCalcLayout = new QGridLayout(this);
    simpleCalcLayout->setSpacing(0);
    simpleCalcLayout->setContentsMargins(0, 0, 0, 0);

    simpleCalcLayout->addWidget(clearAllButton, 1, 4, 2, 1);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 3;
        int column = ((i - 1) % 3);
        mainLayout->addWidget(digitButtons[i], row, column);
        digitButtons[i] -> setStyleSheet(StyleSheetNumbers);
    }

    simpleCalcLayout->addWidget(digitButtons[0], 6, 0, 1, 2);
    simpleCalcLayout->addWidget(pointButton, 6, 2);
    simpleCalcLayout->addWidget(divisionButton, 3, 3);
    simpleCalcLayout->addWidget(timesButton, 4, 3);
    simpleCalcLayout->addWidget(minusButton, 5, 3);
    simpleCalcLayout->addWidget(plusButton, 6, 3);
    simpleCalcLayout->addWidget(squareRootButton, 3, 4);
    simpleCalcLayout->addWidget(reciprocalButton, 4, 4);
    simpleCalcLayout->addWidget(equalButton, 5, 4, 2, 1);

    digitButtons[0] -> setStyleSheet(StyleSheetNumbers);
    squareRootButton->setStyleSheet(StyleSheetSigns);
    reciprocalButton->setStyleSheet(StyleSheetSigns);
    equalButton->setStyleSheet(StyleSheetSigns);
    divisionButton->setStyleSheet(StyleSheetSigns);
    timesButton->setStyleSheet(StyleSheetSigns);
    minusButton->setStyleSheet(StyleSheetSigns);
    plusButton->setStyleSheet(StyleSheetSigns);
    clearAllButton->setStyleSheet(StyleSheetSigns);
    pointButton->setStyleSheet(StyleSheetSigns);

    simpleCalcWidget = new QWidget(this);
    simpleCalcWidget->setLayout(simpleCalcLayout);

    setWindowTitle(tr("Simple Calculator"));
}
void MainWindow::CreateEngineeringWidget(){

    engineeringCalc->setChecked(true);

    QString StyleSheetSigns = "QToolButton { color: black; background-color: #E6E6E6; border: none; font: 19pt 'Microsoft YaHei UI Light'; outline: none; } QToolButton:hover { background-color: #2ECCFA; border-style: solid; border-width: 3px; border-color: #58D3F7; } QToolButton:pressed { background-color: #81DAF5; border-style: solid; border-width: 3px; border-color: #A9E2F3; }";

    Button *sinhButton = createButton(tr("sinh"), SLOT(unaryOperatorClickedEng()));
    Button *coshAllButton = createButton(tr("cosh"), SLOT(unaryOperatorClickedEng()));
    Button *tanhButton = createButton(tr("tanh"), SLOT(unaryOperatorClickedEng()));
    Button *sinButton = createButton(tr("sin"), SLOT(unaryOperatorClickedEng()));
    Button *cosButton = createButton(tr("cos"), SLOT(unaryOperatorClickedEng()));
    Button *tanButton = createButton(tr("tan"), SLOT(unaryOperatorClickedEng()));
    Button *piButton = createButton(QString::fromUtf8("\u03C0"), SLOT(unaryOperatorClickedEng()));
    Button *factButton = createButton(tr("n!"), SLOT(unaryOperatorClickedEng()));
    Button *expButton = createButton(QString::fromUtf8("e\u207F"), SLOT(unaryOperatorClickedEng()));
    Button *lnButton = createButton(tr("ln"), SLOT(unaryOperatorClickedEng()));
    Button *logButton = createButton(tr("log"), SLOT(unaryOperatorClickedEng()));
    Button *kubsqrtButton = createButton(QString::fromUtf8("\u00B3\u221A"), SLOT(unaryOperatorClickedEng()));
    Button *to2Button = createButton(QString::fromUtf8("x\u00B2"), SLOT(unaryOperatorClickedEng()));
    Button *to3Button = createButton(QString::fromUtf8("x\u00B3"), SLOT(unaryOperatorClickedEng()));
    Button *toyButton = createButton(QString::fromUtf8("x\u207F"), SLOT(unaryOperatorClickedEng()));
    Button *ysqrtButton = createButton(QString::fromUtf8("\u207F\u221A"), SLOT(unaryOperatorClickedEng()));


    engineeringLayout = new QGridLayout(this);
    engineeringLayout->setSpacing(0);
    engineeringLayout->setContentsMargins(0, 0, 0, 0);

    engineeringLayout->addWidget(sinhButton, 1, 0, 1, 4);
    engineeringLayout->addWidget(coshAllButton, 2, 0, 1, 4);
    engineeringLayout->addWidget(tanhButton, 0, 0, 1, 5);

    engineeringWidget = new QWidget(this);
    engineeringWidget->setLayout(engineeringLayout);

    setWindowTitle(tr("Engineering Calculator"));
}

void MainWindow::SpawnSimpleMode();
void MainWindow::SpawnEngineeringMode();

void MainWindow::SwitchMode();
