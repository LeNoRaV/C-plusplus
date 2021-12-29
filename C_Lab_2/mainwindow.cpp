#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    CreateDefaultCalcWidget();
    CreateSimpleCalcWidget();
    CreateEngineeringWidget();

//    mainWidget = new QWidget;
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::CreateSimpleCalcWidget(){
    SimpleCalculator calc;
}

void MainWindow::CreateEngineeringWidget(){
    EngineeringCalculator calc;
}
/*

void MainWindow::SpawnSimpleMode(){
    mainLayout = new QGridLayout;
        mainLayout->setSpacing(0);
        engineeringWidget->hide();
        mainLayout->addWidget(defaultCalcWidget, 0, 0, 1, 3);
        mainLayout->addWidget(simpleCalcWidget,  1, 0, 2, 3);

        mainWidget->setLayout(mainLayout);
        setCentralWidget(mainWidget);
        centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
}
void MainWindow::SpawnEngineeringMode(){
    mainLayout = new QGridLayout;
        mainLayout->setSpacing(0);
        mainLayout->addWidget(defaultCalcWidget, 0, 0, 1, 9);
        mainLayout->addWidget(engineeringWidget,   1, 0, 2, 4);
        mainLayout->addWidget(simpleCalcWidget,  1, 4, 2, 5);
        engineeringWidget->show();

        mainWidget->setLayout(mainLayout);
        setCentralWidget(mainWidget);
        centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::SwitchMode(){
    mainWidget->setParent(this);
        simpleCalcWidget->setParent(this);
        engineeringWidget->setParent(this);
        if (simpleCalc->isChecked()) {
            delete mainLayout;
            setMinimumSize(685, 450);
            setMaximumSize(685, 450);
            SpawnEngineeringMode();
        }
        else {
            delete mainLayout;
            setMinimumSize(380, 450);
            setMaximumSize(380, 450);
            SpawnSimpleMode();
        }
}

void MainWindow::digitClicked()
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
     //display->setText(display->text() + QString(clickedOperator));
 }

void MainWindow::multiplicativeOperatorClicked()
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
*/
