#include "mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowOpacity(0.98);
    setMinimumSize(380, 450);
    setMaximumSize(380, 450);

    simpleCalc = new QRadioButton("Simple Calculator");
    simpleCalc->setChecked(true);
    engineeringCalc = new QRadioButton("Engineering Calculator");

    connect(simpleCalc, SIGNAL(toggled(bool)), SLOT(SwitchMode()));

    CreateDefaultCalcWidget();
    CreateSimpleCalcWidget();
    CreateEngineeringCalcWidget();
    mainWidget = new QWidget;
    SpawnSimpleMode();
}

MainWindow::~MainWindow() {}

void MainWindow::CreateSimpleCalcWidget(){
    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    QString StyleSheetNumbers = "QToolButton { color: black; background-color: #FAFAFA; border: none; font: 17pt 'Microsoft YaHei UI'; outline: none;} QToolButton:hover { background-color: #D8D8D8; border-style: solid; border-width: 3px; border-color: #D8D8D8; } QToolButton:pressed { background-color: #A4A4A4; border-style: solid; border-width: 3px; border-color: #A4A4A4; }";
    QString StyleSheetSigns =   "QToolButton { color: black; background-color: #E6E6E6; border: none; font: 19pt 'Microsoft YaHei UI Light'; outline: none; } QToolButton:hover { background-color: #DDA0DD; border-style: solid; border-width: 3px; border-color: #DDA0DD; } QToolButton:pressed { background-color: #DA70D6; border-style: solid; border-width: 3px; border-color: #DA70D6; }";



    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
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


    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 3;
        int column = ((i - 1) % 3);
        simpleCalcLayout->addWidget(digitButtons[i], row, column);
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
    pointButton->setStyleSheet(StyleSheetSigns);

    simpleCalcWidget = new QWidget(this);
    simpleCalcWidget->setLayout(simpleCalcLayout);

}

void MainWindow::CreateEngineeringCalcWidget(){

    Button *sinhButton = createButton(tr("sinh"), SLOT(unaryOperatorClicked()));
    Button *coshAllButton = createButton(tr("cosh"), SLOT(unaryOperatorClicked()));
    Button *tanhButton = createButton(tr("tanh"), SLOT(unaryOperatorClicked()));
    Button *sinButton = createButton(tr("sin"), SLOT(unaryOperatorClicked()));
    Button *cosButton = createButton(tr("cos"), SLOT(unaryOperatorClicked()));
    Button *tanButton = createButton(tr("tan"), SLOT(unaryOperatorClicked()));
    Button *piButton = createButton(QString::fromUtf8("\u03C0"), SLOT(digitClicked()));
    Button *factButton = createButton(tr("n!"), SLOT(unaryOperatorClicked()));
    Button *expButton = createButton(QString::fromUtf8("e\u207F"), SLOT(unaryOperatorClicked()));
    Button *lnButton = createButton(tr("ln"), SLOT(unaryOperatorClicked()));
    Button *logButton = createButton(tr("log"), SLOT(unaryOperatorClicked()));
    Button *kubsqrtButton = createButton(QString::fromUtf8("\u00B3\u221A"), SLOT(unaryOperatorClicked()));
    Button *to2Button = createButton(QString::fromUtf8("x\u00B2"), SLOT(unaryOperatorClicked()));
    Button *to3Button = createButton(QString::fromUtf8("x\u00B3"), SLOT(unaryOperatorClicked()));
    Button *toyButton = createButton(QString::fromUtf8("x\u207F"), SLOT(multiplicativeOperatorClicked()));
    Button *ysqrtButton = createButton(QString::fromUtf8("\u207F\u221A"), SLOT(multiplicativeOperatorClicked()));

    QString StyleSheetSigns =   "QToolButton { color: black; background-color: #E6E6E6; border: none; font: 19pt 'Microsoft YaHei UI Light'; outline: none; } QToolButton:hover { background-color: #DDA0DD; border-style: solid; border-width: 3px; border-color: #DDA0DD; } QToolButton:pressed { background-color: #DA70D6; border-style: solid; border-width: 3px; border-color: #DA70D6; }";

    engineeringCalcLayout = new QGridLayout(this);
    engineeringCalcLayout->setSpacing(0);
    engineeringCalcLayout->setContentsMargins(0, 0, 0, 0);

    engineeringCalcLayout->addWidget(sinhButton, 1, 0, 1, 1);
    engineeringCalcLayout->addWidget(coshAllButton, 2, 0, 1, 1);
    engineeringCalcLayout->addWidget(tanhButton, 3, 0, 1, 1);
    engineeringCalcLayout->addWidget(sinButton, 1, 1, 1, 1);
    engineeringCalcLayout->addWidget(cosButton, 2, 1, 1, 1);
    engineeringCalcLayout->addWidget(tanButton, 3, 1, 1, 1);
    engineeringCalcLayout->addWidget(piButton, 4, 1, 1, 1);
    engineeringCalcLayout->addWidget(factButton, 4, 0, 1, 1);
    engineeringCalcLayout->addWidget(expButton, 1, 2, 1, 1);
    engineeringCalcLayout->addWidget(lnButton, 2, 2, 1, 1);
    engineeringCalcLayout->addWidget(logButton, 3, 2, 1, 1);
    engineeringCalcLayout->addWidget(kubsqrtButton, 4, 2, 1, 1);
    engineeringCalcLayout->addWidget(to2Button, 1, 3, 1, 1);
    engineeringCalcLayout->addWidget(to3Button, 2, 3, 1, 1);
    engineeringCalcLayout->addWidget(toyButton, 3, 3, 1, 1);
    engineeringCalcLayout->addWidget(ysqrtButton, 4, 3, 1, 1);

    sinhButton->setStyleSheet(StyleSheetSigns);
    coshAllButton->setStyleSheet(StyleSheetSigns);
    tanhButton ->setStyleSheet(StyleSheetSigns);
    sinButton->setStyleSheet(StyleSheetSigns);
    cosButton->setStyleSheet(StyleSheetSigns);
    tanButton->setStyleSheet(StyleSheetSigns);
    piButton ->setStyleSheet(StyleSheetSigns);
    factButton ->setStyleSheet(StyleSheetSigns);
    expButton ->setStyleSheet(StyleSheetSigns);
    lnButton  ->setStyleSheet(StyleSheetSigns);
    logButton ->setStyleSheet(StyleSheetSigns);
    kubsqrtButton->setStyleSheet(StyleSheetSigns);
    to2Button->setStyleSheet(StyleSheetSigns);
    to3Button ->setStyleSheet(StyleSheetSigns);
    toyButton  ->setStyleSheet(StyleSheetSigns);
    ysqrtButton ->setStyleSheet(StyleSheetSigns);

    engineeringCalcWidget = new QWidget(this);
    engineeringCalcWidget->setLayout(engineeringCalcLayout);

}

void MainWindow::CreateDefaultCalcWidget() {
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    QString StyleSheetRadioButton = "QRadioButton {background-color: #E6E6E6; font: 10pt 'Microsoft YaHei UI Light'; padding: 0px 0px 0px 20px;} QRadioButton::indicator { width: 15px; height: 15px;}";
    QString StyleSheetLine = "QLineEdit {font: 26pt 'Microsoft YaHei UI'; qproperty-alignment: AlignRight; padding: 5px; border: none; }";
    QString StyleSheetSigns =   "QToolButton { color: black; background-color: #E6E6E6; border: none; font: 19pt 'Microsoft YaHei UI Light'; outline: none; } QToolButton:hover { background-color: #DDA0DD; border-style: solid; border-width: 3px; border-color: #DDA0DD; } QToolButton:pressed { background-color: #DA70D6; border-style: solid; border-width: 3px; border-color: #DA70D6; }";

    Button *clearAllButton = createButton(tr("C"), SLOT(clearAll()));

    display->setStyleSheet(StyleSheetLine);
    simpleCalc->setStyleSheet(StyleSheetRadioButton);
    engineeringCalc->setStyleSheet(StyleSheetRadioButton);
    clearAllButton->setStyleSheet(StyleSheetSigns);

    defaultCalcLayout = new QGridLayout(this);
    defaultCalcLayout->setSpacing(0);
    defaultCalcLayout->setContentsMargins(0, 0, 0, 0);

    defaultCalcLayout->addWidget(display,  0, 0, 2, 5);
    defaultCalcLayout->addWidget(clearAllButton, 2, 4, 2, 1);
    defaultCalcLayout->addWidget(simpleCalc, 2, 0, 1, 4);
    defaultCalcLayout->addWidget(engineeringCalc, 3, 0, 1, 4);

    defaultCalcWidget = new QWidget(this);
    defaultCalcWidget->setLayout(defaultCalcLayout);
}

void MainWindow::SwitchMode() {
    mainWidget->setParent(this);
    simpleCalcWidget->setParent(this);
    engineeringCalcWidget->setParent(this);
    if (!simpleCalc->isChecked()) {
        delete mainLayout;
        setWindowTitle(tr("Engineering Calculator"));
        setMinimumSize(685, 450);
        setMaximumSize(685, 450);
        SpawnComplMode();
    }
    else {
        delete mainLayout;
        setWindowTitle(tr("Simple Calculator"));
        setMinimumSize(380, 450);
        setMaximumSize(380, 450);
        SpawnSimpleMode();
    }
}

void MainWindow::SpawnSimpleMode() {
    mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    engineeringCalcWidget->hide();
    mainLayout->addWidget(defaultCalcWidget, 0, 0, 1, 5);
    mainLayout->addWidget(simpleCalcWidget,  1, 0, 4, 5);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::SpawnComplMode() {
    mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    mainLayout->addWidget(defaultCalcWidget, 0, 0, 1, 8);
    mainLayout->addWidget(engineeringCalcWidget,   1, 0, 4, 4);
    mainLayout->addWidget(simpleCalcWidget,  1, 4, 4, 4);

    engineeringCalcWidget->show();

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::digitClicked()
 {
     Button *clickedButton = qobject_cast<Button *>(sender());
     int digitValue = clickedButton->text().toInt();
     QString clickedOperator = clickedButton->text();
     if (clickedOperator == "\u03C0") {
              double pi = 3.1415926535897932384626433832795;
              display->clear();
              waitingForOperand = false;
              display->setText( QString::number(pi));
     }

     if (display->text() == "0" && digitValue == 0.0)
         return;

          if (waitingForOperand) {
              display->clear();
              waitingForOperand = false;
          }
          display->setText(display->text() + QString::number(digitValue));
 }

double fact (double A)
{
     if (A == 0) {
         return 1;
     }
     return A*fact(A-1);
}

void MainWindow::unaryOperatorClicked()
 {
     Button *clickedButton = qobject_cast<Button *>(sender());
     QString clickedOperator = clickedButton->text();
     double operand = display->text().toDouble();
     double result = 0.0;

     if (clickedOperator == tr("Sqrt")) {
         if (operand < 0.0) {
             abortOperation();
             return;
         }
         result = sqrt(operand);
     }
     else if (clickedOperator == tr("1/x")) {
         if (operand == 0.0) {
             abortOperation();
             return;
         }
         result = 1.0 / operand;
     }

    else if (clickedOperator == tr("sinh")) {
        result = sinh(operand);
    }
    else if (clickedOperator == tr("cosh")) {
        result = cosh(operand);
    }
    else if (clickedOperator == tr("tanh")) {
        result = tanh(operand);
    }
    else if (clickedOperator == tr("n!")) {
        if (operand < 0.0 | operand != round(operand)) {
            abortOperation();
            return;
        }
        result = fact(operand);
    }
    else if (clickedOperator == tr("sin")) {
        result = sin(operand);
    }
    else if (clickedOperator == tr("cos")) {
        result = cos(operand);
    }
    else if (clickedOperator == tr("tan")) {
        result = tan(operand);
    }
    else if (clickedOperator == tr("e\u207F")) {
        result = exp(operand);
    }
    else if (clickedOperator == tr("ln")) {
        if (operand < 0.0 | operand == 1) {
            abortOperation();
            return;
        }
        result = log(operand);
    }
    else if (clickedOperator == tr("log")) {
        if (operand < 0.0 | operand == 1) {
            abortOperation();
            return;
        }
        result = log10(operand);
    }
    else if (clickedOperator == tr("\u00B3\u221A")) {
        result = pow(operand, 1.0 / 3.0);
    }
    else if (clickedOperator == tr("x\u00B2")) {
        result = operand*operand;
    }
    else if (clickedOperator == tr("x\u00B3")) {
        result = operand*operand*operand;
    }
     display->setText(QString::number(result));
     waitingForOperand = true;
 }

void MainWindow::additiveOperatorClicked()
 {
     Button *clickedButton = qobject_cast<Button *>(sender());
     QString clickedOperator = clickedButton->text();
     double operand = display->text().toDouble();
     if (!pendingMultiplicativeOperator.isEmpty()) {
         if (!calculate(operand, pendingMultiplicativeOperator)) {
             abortOperation();
             return;
         }
         display->setText(QString::number(factorSoFar));
         operand = factorSoFar;
         factorSoFar = 0.0;
         pendingMultiplicativeOperator.clear();
     }
     if (!pendingAdditiveOperator.isEmpty()) {
         if (!calculate(operand, pendingAdditiveOperator)) {
             abortOperation();
             return;
         }
         display->setText(QString::number(sumSoFar));
     } else {
         sumSoFar = operand;
     }
     pendingAdditiveOperator = clickedOperator;
     waitingForOperand = true;
 }

void MainWindow::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    //double result = 0.0;

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));


    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void MainWindow::equalClicked()
{
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void MainWindow::pointClicked()
 {
     if (waitingForOperand)
         display->setText("0");
     if (!display->text().contains("."))
         display->setText(display->text() + tr("."));
     waitingForOperand = false;
 }

void MainWindow::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void MainWindow::clearMemory()
{
    sumInMemory = 0.0;
}

void MainWindow::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void MainWindow::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void MainWindow::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}

Button *MainWindow::createButton(const QString &text, const char *member)
 {
     Button *button = new Button(text);
     connect(button, SIGNAL(clicked()), this, member);
     return button;
 }
void MainWindow::abortOperation()
 {
     clearAll();
     display->setText(tr("Error"));
 }

bool MainWindow::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("*")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("/")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    } else if (pendingOperator == tr("x\u207F")) {
        factorSoFar = pow(factorSoFar, rightOperand);
    } else if (pendingOperator == tr("\u207F\u221A")) {
        factorSoFar = pow(factorSoFar, 1.0/(rightOperand));
    }
    return true;
}

Button::Button(const QString &text, QWidget *parent)
     : QToolButton(parent)
 {
     setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
     setText(text);
 }

QSize Button::sizeHint() const
 {
     QSize size = QToolButton::sizeHint();
     size.rheight() += 20;
     size.rwidth() = qMax(size.width(), size.height());
     return size;
 }
