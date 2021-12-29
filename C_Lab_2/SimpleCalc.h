#ifndef SIMPLECALC_H
#define SIMPLECALC_H
#include <QMainWindow>
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialog>
#include <QRadioButton>

class Button : public QToolButton
{
    Q_OBJECT

public:
    Button(const QString &text, QWidget *parent = 0);

    QSize sizeHint() const;
};

class SimpleCalculator : public QWidget{
     Q_OBJECT

 public:
     SimpleCalculator(QWidget *parent = 0);

 protected slots:
     void digitClicked();
     void unaryOperatorClicked();
     void additiveOperatorClicked();
     void multiplicativeOperatorClicked();
     void equalClicked();
     void pointClicked();
     void clearAll();
     void clearMemory();
     void readMemory();
     void setMemory();
     void addToMemory();

protected:
//     QWidget* defaultCalcWidget;
//     QWidget* simpleCalcWidget;
//     QWidget* engineeringCalcWidget;
//     QWidget* mainWidget;

     QGridLayout* simpleCalcLayout;
//     QGridLayout* defaultCalcLayout;
//     QGridLayout* engineeringCalcLayout;
//     QGridLayout* mainLayout;

     QRadioButton *simpleCalc;
     QRadioButton *engineeringCalc;

     Button *createButton(const QString &text, const char *member);
     void abortOperation();
     bool calculate(double rightOperand, const QString &pendingOperator);
     double sumInMemory;
     double sumSoFar;
     double factorSoFar;
     QString pendingAdditiveOperator;
     QString pendingMultiplicativeOperator;
     bool waitingForOperand;
     QLineEdit *display;
     enum { NumDigitButtons = 10 };
     Button *digitButtons[NumDigitButtons];
};


#endif // SIMPLECALC_H
