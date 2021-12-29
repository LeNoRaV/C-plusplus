#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialog>
#include <QRadioButton>
#include "SimpleCalc.h"
#include "EngineeringCalc.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
//        QWidget* defaultCalcWidget;
//        QWidget* simpleCalcWidget;
//        QWidget* engineeringWidget;
//        QWidget* mainWidget;

//        QGridLayout* defaultCalcLayout;
//        QGridLayout* simpleCalcLayout;
//        QGridLayout* engineeringLayout;
//        QGridLayout* mainLayout;

//        void CreateDefaultCalcWidget();
       void CreateSimpleCalcWidget();
       void CreateEngineeringWidget();

//        void SpawnSimpleMode();
//        void SpawnEngineeringMode();

//             Button *createButton(const QString &text, const char *member);
//             void abortOperation();
//             bool calculate(double rightOperand, const QString &pendingOperator);
//             double sumInMemory;
//             double sumSoFar;
//             double factorSoFar;
//             QString pendingAdditiveOperator;
//             QString pendingMultiplicativeOperator;
//             bool waitingForOperand;
//             QLineEdit *display;
//             enum { NumDigitButtons = 10 };
//             Button *digitButtons[NumDigitButtons];

//             QRadioButton *simpleCalc;
//             QRadioButton *engineeringCalc;

public slots:
    //void SwitchMode();

};
#endif // MAINWINDOW_H

