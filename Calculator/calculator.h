#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include "button.h"
#include <QStack>
#include <cmath>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);
    ~Calculator();

private slots:
    void digitClicked();
    void changeSignClicked();
    void unaryOperatorClicked();
    void binaryOperatorClicked();
    void equalClicked();
    void pointClicked();
    void backspaceClicked();
    void clear();
    void clearAll();

private:
    Button* createButton(const QString& text);
    void abortOperation();
    bool calculate(double left, double right, const QString& op);
    bool calculate(double left, const QString &op);
    QLineEdit* display;

    double leftOperand;
    double rightOperand;

    bool waitForOperator;
    bool waitForOperand;
    QString op;
    //QString operand;
    QStack<QString> stack;
    int value;

    enum { NumDigitButtons = 10 };

    enum { start = 0, operand, unary_operator, binary_operator, equal_operator, error } state;
    Button* digitButtons[NumDigitButtons];
};

#endif // CALCULATOR_H
