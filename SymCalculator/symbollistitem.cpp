#include "symbollistitem.h"

SymbolListItem::SymbolListItem(QWidget *parent) :
    QWidget(parent)
{
    keyLable = new QLabel(tr("I am a key"), parent);
    keyLable->setAlignment(Qt::AlignLeft);
    valueLable = new QLabel(tr("I am a value"), parent);
    valueLable->setAlignment(Qt::AlignLeft);
    layout = new QHBoxLayout;
    //layout = new QVBoxLayout();
    layout->addWidget(keyLable);
    layout->addWidget(valueLable);
    layout->setMargin(0); // set up margin
    layout->setSpacing(0); // set up space
    this->setLayout(layout);
    //this->show();
}

//void SymbolListItem::setKey(const QString &key)
//{

//}
