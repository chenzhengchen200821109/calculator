#include "calculator.h"
#include <QString>
#include <iostream>
#include "../parser.h"
#include "../Calculator.h"
#include "../commandParser.h"
#include <cstring>

calculator::calculator(QWidget *parent) :
    QWidget(parent)
{
    // input line
    inputLine = new QLineEdit(this);
    inputLine->setPlaceholderText(tr("input here"));
    inputLine->setAlignment(Qt::AlignRight);
    inputLine->setMaxLength(50);

    QFont font = inputLine->font();
    font.setPointSize(font.pointSize() + 8);
    inputLine->setFont(font);

    // output line
    outputLine = new QLineEdit(this);
    outputLine->setPlaceholderText(tr("output here"));
    outputLine->setAlignment(Qt::AlignRight);
    outputLine->setMaxLength(50);
    outputLine->setReadOnly(true);

    font = outputLine->font();
    font.setPointSize(font.pointSize() + 8);
    outputLine->setFont(font);

    inListView = new QListView(this);

    outListView = new QListView(this);

    leftLayout = new QVBoxLayout;
    leftLayout->addWidget(inputLine);
    leftLayout->addWidget(inListView);

    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(outputLine);
    rightLayout->addWidget(outListView);

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    // set up list view model
    model = new QStringListModel;
    list = new QStringList;

    connect(inputLine, SIGNAL(returnPressed()), this, SLOT(onReturnPressed()));
}

void calculator::onReturnPressed()
{
    QString text = inputLine->text();
    //text += "\n";
    QString result = calculate(text);
    outputLine->setText(result);

    text += " = ";
    text += result;
    list->append(text);
    model->setStringList(*list);
    inListView->setModel(model);
    inputLine->clear();
}

void calculator::saveMemory()
{
    std::cout << "Save Memory" << std::endl;
}

void calculator::clearMemory()
{
    std::cout << "Clear Memory" << std::endl;
    inputLine->clear();
    list->clear();
    model->setStringList(*list);
    inListView->setModel(model);
    outputLine->clear();
}

void calculator::loadToMemory()
{
    std::cout << "Load Data To Memory" << std::endl;
}

QString calculator::calculate(const QString &text)
{
    std::string str = text.toStdString();
    Status status;
    Calculator calc;

    //do {
        Scanner scanner(str);
        if (!scanner.IsEmpty()) {
            if (scanner.IsCommand()) {
                CommandParser parser(scanner, calc);
                status = parser.Execute();
            } else {
                Parser parser(scanner, calc);
                status = parser.Parse();
                if (status == stOk) {
                    double result = parser.Calculate();
                    return QString::number(result);
                } else {
                    return QString("###");
                }
            }
        } else {
            //break;
            return text;
        }
    //} while (status != stQuit);
}
