#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>
#include <QWidget>
#include <QSize>
#include <QString>

class Button : public QToolButton
{
    Q_OBJECT

public:
    explicit Button(const QString& text, QWidget* parent = 0);
    QSize sizeHint() const override;
};

#endif // BUTTON_H
