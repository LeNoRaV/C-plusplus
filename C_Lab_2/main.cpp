#include "mainwindow.h"
#include "EngineeringCalc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    SimpleCalculator ECalc;
//    ECalc.show();

   EngineeringCalculator ECalc;
   ECalc.show();

    return a.exec();
}

