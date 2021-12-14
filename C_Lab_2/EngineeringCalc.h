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
     void unaryOperatorClickedEng();

private:

};

#endif // ENGINEERINGCALCULATOR_H
