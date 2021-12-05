#ifndef ENGINEERINGCALCULATOR_H
#define ENGINEERINGCALCULATOR_H

#include <QMainWindow>
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialog>
#include <QRadioButton>
#include "SimpleCalc.h"

class EngineeringCalculator : public SimpleCalculator
 {
     Q_OBJECT

 public:
     EngineeringCalculator(QWidget *parent = 0);

 private slots:
     /*
     void sinhClicked();
     void coshOperatorClicked();
     void tanhClicked();
     void factClicked();
     void sinClicked();
     void cosClicked();
     void tanClicked();
     void piClicked();
     void expClicked();
     void lnClicked();
     void logClicked();
     void kubsqrtClicked();
     void to2Clicked();
     void to3Clicked();
     void toyClicked();
     void ysqrtClicked();
     */
private:

};

#endif // ENGINEERINGCALCULATOR_H
