#ifndef CALC_H
#define CALC_H
#include <QMainWindow>
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>

class Button : public QToolButton
{
    Q_OBJECT

public:
    Button(const QString &text, QWidget *parent = 0);

    QSize sizeHint() const;
};

class Calculator : public QMainWindow
 {
     Q_OBJECT

 public:
     Calculator(QWidget *parent = 0);

 private slots:
     void digitClicked();
     void unaryOperatorClicked();
     void additiveOperatorClicked();
     void multiplicativeOperatorClicked();
     void equalClicked();
     void pointClicked();
     void changeSignClicked();
     void backspaceClicked();
     void clear();
     void clearAll();
     void clearMemory();
     void readMemory();
     void setMemory();
     void addToMemory();
private:
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

#endif // CALC_H
