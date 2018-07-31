#ifndef SYMBOLLISTITEM_H
#define SYMBOLLISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>

class SymbolListItem : public QWidget
{
    Q_OBJECT
public:
    explicit SymbolListItem(QWidget *parent = 0);
    //void setKey(QString const& key);
    //void setValue(QString const& value);

signals:

public slots:

private:
    QLabel* keyLable;
    QLabel* valueLable;
    QHBoxLayout* layout;
    //QVBoxLayout* layout;
};

#endif // SYMBOLLISTITEM_H
