#include "calculator.h"
#include <QFont>
#include <QGridLayout>
#include <iostream>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    //result = 0.0;

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(20);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for(int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i));
        connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(digitClicked()));
    }

    Button* pointButton = createButton(tr("."));
    connect(pointButton, SIGNAL(clicked()), this, SLOT(pointClicked()));

    Button* changeSignButton = createButton(tr("\302\261"));
    connect(changeSignButton, SIGNAL(clicked()), this, SLOT(changeSignClicked()));

    Button *backspaceButton = createButton(tr("Backspace"));
    connect(backspaceButton, SIGNAL(clicked()), this, SLOT(backspaceClicked()));

    Button *clearButton = createButton(tr("Clear"));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));

    Button *clearAllButton = createButton(tr("Clear All"));
    connect(clearAllButton, SIGNAL(clicked()), this, SLOT(clearAll()));

    Button *divisionButton = createButton(tr("/"));
    connect(divisionButton, SIGNAL(clicked()), this, SLOT(binaryOperatorClicked()));

    Button *timesButton = createButton(tr("*"));
    connect(timesButton, SIGNAL(clicked()), this, SLOT(binaryOperatorClicked()));

    Button *minusButton = createButton(tr("-"));
    connect(minusButton, SIGNAL(clicked()), this, SLOT(binaryOperatorClicked()));

    Button *plusButton = createButton(tr("+"));
    connect(plusButton, SIGNAL(clicked()), this, SLOT(binaryOperatorClicked()));

    Button *squareRootButton = createButton(tr("sqrt"));
    connect(squareRootButton, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));

    Button *powerButton = createButton(tr("x\302\262"));
    connect(powerButton, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));

    Button *reciprocalButton = createButton(tr("1/x"));
    connect(reciprocalButton, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));

    Button *equalButton = createButton(tr("="));
    connect(equalButton, SIGNAL(clicked()), this, SLOT(equalClicked()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 5);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 1);
    mainLayout->addWidget(clearAllButton, 1, 3, 1, 2);


    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3);
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 0);
    mainLayout->addWidget(pointButton, 5, 1);
    mainLayout->addWidget(changeSignButton, 5, 2);

    mainLayout->addWidget(divisionButton, 2, 3);
    mainLayout->addWidget(timesButton, 3, 3);
    mainLayout->addWidget(minusButton, 4, 3);
    mainLayout->addWidget(plusButton, 5, 3);

    mainLayout->addWidget(squareRootButton, 2, 4);
    mainLayout->addWidget(powerButton, 3, 4);
    mainLayout->addWidget(reciprocalButton, 4, 4);
    mainLayout->addWidget(equalButton, 5, 4);
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));

    state = start;
}

void Calculator::digitClicked()
{
    if (state == start || state == operand) {
        QString text = display->text();
        int digitValue = text.toInt();
        Button* clickedButton = qobject_cast<Button *>(sender());
        if (digitValue == 0 && text.size() == 1) {
            text = clickedButton->text();
            display->setText(text);
        } else {
            text = text.append(clickedButton->text());
            display->setText(text);
        }
        state = operand;
        return;
    } else if (state == unary_operator || equal_operator || error || binary_operator) {
        QString text = display->text();
        text.clear();
        Button* clickedButton = qobject_cast<Button *>(sender());
        text.append(clickedButton->text());
        display->setText(text);
        state = operand;
        return;
    } else if (binary_operator) {
        QString text = display->text();
        //stack.push(text);
        text.clear();
        Button* clickedButton = qobject_cast<Button *>(sender());
        text.append(clickedButton->text());
        display->setText(text);
        state = operand;
        return;
    }
}

void Calculator::unaryOperatorClicked()
{
    if (state == start)
        return;
    else if (state == operand || equal_operator || binary_operator) {
        QString text = display->text();
        Button* clickedButton = qobject_cast<Button *>(sender());
        QString clickedOp = clickedButton->text();

        if (calculate(text.toDouble(), clickedOp)) {
            //stack.push(QString::number(leftOperand, 'f', 2));
            state = operand;
            display->setText(QString::number(leftOperand, 'f', 2));
            return;
        } else {
            abortOperation();
            return;
        }
    }
    else {
        return;
    }
}

void Calculator::binaryOperatorClicked()
{
    QString text = display->text();
    Button* clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();

    std::cout << clickedOperator.toStdString() << std::endl;

    //if (state == binary_operator) {
    //    std::cout << "got here" << std::endl;
    //    return;
    //}

    if (state == operand || state == equal_operator) { // operand ---> binary operator
        stack.push(text);
        if (stack.size() == 1) {
            op = clickedOperator;
            state = binary_operator;
            display->setText(text);
        } else if (stack.size() == 2){
            std::cout << stack.size() << std::endl;
            rightOperand = stack.pop().toDouble();
            leftOperand = stack.pop().toDouble();
            //std::cout << rightOperand << std::endl;
            //std::cout << leftOperand << std::endl;
            //std::cout << op.toStdString() << std::endl;
            calculate(leftOperand, rightOperand, op);
            stack.push(QString::number(leftOperand, 'f', 2));
            display->setText(QString::number(leftOperand, 'f', 2));
            op = clickedOperator;
            state = binary_operator;
        }
        return;
    } else if (state == binary_operator) {
        //op = clickedOperator;
        //std::cout << "got here" << std::endl;
        return;
    }

}

void Calculator::equalClicked()
{
    if (state == operand) {
        QString text = display->text();
        stack.push(text);
        if (stack.size() == 1) {
            stack.pop();
            state = equal_operator;
            return;
        }
        else if (stack.size() == 2) {
            rightOperand = stack.pop().toDouble();
            leftOperand = stack.pop().toDouble();
            if (calculate(leftOperand, rightOperand, op)) {
                //stack.push(QString::number(leftOperand, 'f', 2));
                display->setText(QString::number(leftOperand, 'f', 2));
                state = equal_operator;
            } else {
                abortOperation();
            }
        }
    } else {
        return;
    }
}


void Calculator::pointClicked()
{
    if (state == start || state == operand) {
        QString text = display->text();
        if (text.contains('.')) {
            return;
        } else {
            display->setText(text + QString("."));
            return;
        }
    } else {
        return;
    }
}

void Calculator::changeSignClicked()
{
    QString text = display->text();
    if (text.toInt() == 0 && text.size() == 1) {
        return;
    }
    if (text.contains('-')) {
        display->setText(text.remove(0, 1));
    } else {
        display->setText(text.prepend('-'));
    }
    stack.push(display->text());
}

void Calculator::backspaceClicked()
{

}

void Calculator::clear()
{
    display->setText("0");
    stack.clear();
    state = start;
}

void Calculator::clearAll()
{
    display->setText("0");
    stack.clear();
}

bool Calculator::calculate(double left, double right, const QString& op)
{
    if (op == tr("+"))
        leftOperand = left + right;
    else if (op == tr("-"))
        leftOperand = left - right;
    else if (op == tr("*"))
        leftOperand = left * right;
    else if (op == tr("%")) {
        if (right == 0.0)
            return false;
        leftOperand = left / right;
    }
    return true;
}

bool Calculator::calculate(double left, const QString &op)
{
    if (op == tr("sqrt")) {
        if (left < 0.0) {
            return false;
        }
        leftOperand = std::sqrt(left);
    } else if (op == tr("1/x")) {
        if (left == 0.0)
            return false;
        leftOperand = (1.0 / left);
    } else if (op == tr("x\302\262"))
        leftOperand = std::pow(left, 2.0);
    return true;
}

Button *Calculator::createButton(const QString &text)
{
    Button *button = new Button(text);
    return button;
}

void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
    state = error;
}

Calculator::~Calculator()
{

}
