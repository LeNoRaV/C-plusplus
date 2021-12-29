#include "SimpleCalc.h"

#include <QtGui>
#include <math.h>


SimpleCalculator::SimpleCalculator(QWidget *parent)
     : QWidget(parent)
 {
     sumInMemory = 0.0;
     sumSoFar = 0.0;
     factorSoFar = 0.0;
     waitingForOperand = true;
     display = new QLineEdit("0");
     display->setReadOnly(true);
     display->setAlignment(Qt::AlignRight);
     //display->setMaxLength(15);

     QFont font = display->font();
     font.setPointSize(font.pointSize() + 8);
     display->setFont(font);
     for (int i = 0; i < NumDigitButtons; ++i) {
         digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
     }

     QString StyleSheetRadioButton = "QRadioButton {background-color: #E6E6E6; font: 10pt 'Microsoft YaHei UI Light'; padding: 0px 0px 0px 20px;} QRadioButton::indicator { width: 15px; height: 15px;}";
     QString StyleSheetLine = "QLineEdit {font: 26pt 'Microsoft YaHei UI'; qproperty-alignment: AlignRight; padding: 5px; border: none; background-color: #F2F2F2;}";
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

     simpleCalcLayout->addWidget(simpleCalc, 1, 0, 1, 4);
     simpleCalcLayout->addWidget(engineeringCalc, 2, 0, 1, 4);
     simpleCalcLayout->addWidget(display, 0, 0, 1, 5);
     simpleCalcLayout->addWidget(clearAllButton, 1, 4, 2, 1);

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

     display->setStyleSheet(StyleSheetLine);
     digitButtons[0] -> setStyleSheet(StyleSheetNumbers);
     simpleCalc->setStyleSheet(StyleSheetRadioButton);
     engineeringCalc->setStyleSheet(StyleSheetRadioButton);
     squareRootButton->setStyleSheet(StyleSheetSigns);
     reciprocalButton->setStyleSheet(StyleSheetSigns);
     equalButton->setStyleSheet(StyleSheetSigns);
     divisionButton->setStyleSheet(StyleSheetSigns);
     timesButton->setStyleSheet(StyleSheetSigns);
     minusButton->setStyleSheet(StyleSheetSigns);
     plusButton->setStyleSheet(StyleSheetSigns);
     clearAllButton->setStyleSheet(StyleSheetSigns);
     pointButton->setStyleSheet(StyleSheetSigns);

     setLayout(simpleCalcLayout);

     setWindowTitle(tr("Simple Calculator"));
 }

void SimpleCalculator::digitClicked()
 {
     Button *clickedButton = qobject_cast<Button *>(sender());
     int digitValue = clickedButton->text().toInt();
     if (display->text() == "0" && digitValue == 0.0)
         return;

     if (waitingForOperand) {
         //if (display->text() == "0") display->clear();
         display->clear();
         waitingForOperand = false;
     }
     display->setText(display->text() + QString::number(digitValue));
 }

void SimpleCalculator::unaryOperatorClicked()
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
     display->setText(QString::number(result));
     waitingForOperand = true;
 }

void SimpleCalculator::additiveOperatorClicked()
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
     //display->setText(display->text() + QString(clickedOperator));
 }

void SimpleCalculator::multiplicativeOperatorClicked()
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
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
    //display->setText(display->text() + QString(clickedOperator));
}

void SimpleCalculator::equalClicked()
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

void SimpleCalculator::pointClicked()
 {
     if (waitingForOperand)
         display->setText("0");
     if (!display->text().contains("."))
         display->setText(display->text() + tr("."));
     waitingForOperand = false;
 }

void SimpleCalculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void SimpleCalculator::clearMemory()
{
    sumInMemory = 0.0;
}

void SimpleCalculator::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void SimpleCalculator::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void SimpleCalculator::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}

Button *SimpleCalculator::createButton(const QString &text, const char *member)
 {
     Button *button = new Button(text);
     connect(button, SIGNAL(clicked()), this, member);
     return button;
 }
void SimpleCalculator::abortOperation()
 {
     clearAll();
     display->setText(tr("Error"));
 }

bool SimpleCalculator::calculate(double rightOperand, const QString &pendingOperator)
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
