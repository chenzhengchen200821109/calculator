#include "calculator.h"
#include <QString>
#include <iostream>
#include "../parser.h"
#include "../Calculator.h"
#include "../commandParser.h"
#include <cstring>
#include "symbollistitem.h"

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

    // =========================================
    //outListView = new QListView(this);
    outListWidget = new QListWidget(this);
    QListWidgetItem* item1 = new QListWidgetItem(outListWidget);
    QListWidgetItem* item2 = new QListWidgetItem(outListWidget);
    outListWidget->addItem(item1);
    outListWidget->addItem(item2);

    SymbolListItem* myWidget = new SymbolListItem(outListWidget);
    SymbolListItem* hisWidget = new SymbolListItem(outListWidget);
    myWidget->show();

    outListWidget->setItemWidget(item1, myWidget);
    outListWidget->setItemWidget(item2, hisWidget);

    item1->setSizeHint(QSize(myWidget->rect().width(), myWidget->rect().height()));
    item2->setSizeHint(QSize(myWidget->rect().width(), myWidget->rect().height()));

    //myWidget->show();

    // =========================================
    leftLayout = new QVBoxLayout;
    leftLayout->addWidget(inputLine);
    leftLayout->addWidget(inListView);

    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(outputLine);
    //rightLayout->addWidget(outListView);
    rightLayout->addWidget(outListWidget);

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
    QString result = calculate(text);
    outputLine->setText(result);

    //if (text.contains("="))
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
    }
    return text;
}

void calculator::displayListWidget()
{
    //QWidget* wid;
}
