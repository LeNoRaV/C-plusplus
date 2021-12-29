#include "EngineeringCalc.h"

#include <QtGui>
#include <math.h>

EngineeringCalculator::EngineeringCalculator(QWidget *parent)
    : SimpleCalculator(parent)
{

    connect(simpleCalc,SIGNAL(toggled(bool)),this,SLOT(mode_usual(bool)));
    connect(engineeringCalc,SIGNAL(toggled(bool)),this,SLOT(mode_engineering(bool)));
//    switch(mode_engineering)
//    case 0:
    engineeringCalc->setChecked(true);

    Button *sinhButton = createButton(tr("sinh"), SLOT(unaryOperatorClickedEng()));
    Button *coshAllButton = createButton(tr("cosh"), SLOT(unaryOperatorClickedEng()));
    Button *tanhButton = createButton(tr("tanh"), SLOT(unaryOperatorClickedEng()));
    /*
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

    //delete simpleCalcLayout;

    EngCalcLayout = new QGridLayout(this);
    //EngCalcLayout->addLayout(simpleCalcLayout);
    EngCalcLayout->setSpacing(0);
    EngCalcLayout->setContentsMargins(0, 0, 0, 0);

    EngCalcLayout->addWidget(sinhButton, 1, 0, 1, 1);
    EngCalcLayout->addWidget(coshAllButton, 2, 0, 1, 1);
    EngCalcLayout->addWidget(tanhButton, 3, 0, 1, 1);


    setLayout(EngCalcLayout);
*/
    simpleCalcLayout->removeWidget(display);
    simpleCalcLayout->addWidget(display, 0, 0, 1, 9);

    simpleCalcLayout->addWidget(sinhButton, 1, 0, 1, 1);
    simpleCalcLayout->addWidget(coshAllButton, 2, 0, 1, 1);
    simpleCalcLayout->addWidget(tanhButton, 3, 0, 1, 1);
}


double fact (double A)
{
     if (A == 0) {
         return 1;
     }
     return A*fact(A-1);
}

void EngineeringCalculator::unaryOperatorClickedEng()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("sinh")) {
        result = sinh(operand);
    }
    else if (clickedOperator == tr("cosh")) {
        result = cosh(operand);
    }
    else if (clickedOperator == tr("tanh")) {
        result = tanh(operand);
    }
    else if (clickedOperator == tr("fact")) {
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
    else if (clickedOperator == tr("exp")) {
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
    else if (clickedOperator == tr("kubsqrt")) {
        result = pow(operand, 1.0 / 3.0);
    }
    else if (clickedOperator == tr("to2")) {
        result = operand*operand;
    }
    else if (clickedOperator == tr("to3")) {
        result = operand*operand*operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}
/*
void EngineeringCalculator::SwitchMode() {
    if (engineeringCalc->isChecked()) {
//        delete mainLayout;
//        setWindowTitle(tr("Engineering Calculator"));
//        setMinimumSize(685, 450);
//        setMaximumSize(685, 450);
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

void EngineeringCalculator::SpawnSimpleMode() {
    mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    engineeringCalcWidget->hide();
    mainLayout->addWidget(defaultCalcWidget, 0, 0, 1, 3);
    mainLayout->addWidget(simpleCalcWidget,  1, 0, 2, 3);

    mainWidget->setLayout(mainLayout);
    //setCentralWidget(mainWidget);
    //centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
}

void EngineeringCalculator::SpawnComplMode() {
    mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    mainLayout->addWidget(defaultCalcWidget, 0, 0, 1, 9);
    mainLayout->addWidget(engineeringCalcWidget,   1, 0, 2, 4);
    mainLayout->addWidget(simpleCalcWidget,  1, 4, 2, 5);
    engineeringCalcWidget->show();

    mainWidget->setLayout(mainLayout);
    //setCentralWidget(mainWidget);
    //centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
}
*/
