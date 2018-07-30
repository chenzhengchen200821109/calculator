#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QStringList>
#include <QString>
#include "../Calculator.h"
#include "../parser.h"

class calculator : public QWidget
{
    Q_OBJECT
public:
    explicit calculator(QWidget *parent = 0);
    void clearMemory();
    void saveMemory();
    void loadToMemory();

signals:

public slots:
    void onReturnPressed();

private:
    QLineEdit* inputLine;
    QLineEdit* outputLine;
    QVBoxLayout* leftLayout;
    QVBoxLayout* rightLayout;
    QHBoxLayout* mainLayout;

    QListView* inListView;
    QListView* outListView;
    QStringListModel* model;
    QStringList* list;

    // calculate
    QString calculate(const QString& text);

    // internal objects
    Status status;
    Calculator calc;
};

#endif // CALCULATOR_H
