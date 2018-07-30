#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QMessageBox>
#include "calculator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent* event);

private slots:
    void onExit();
    void onAbout();
    void onClear();
    void onSave();
    void onLoad();

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);
    bool saveOrNot();

    QMenu* programMenu;
    QMenu* memoryMenu;
    QToolBar* programBar;
    QToolBar* memoryBar;
    // Program menu
    QAction* aboutAction;
    QAction* exitAction;
    // Memory menu
    QAction* clearAction;
    QAction* saveAction;
    QAction* loadAction;
    calculator* calc;
};

#endif // MAINWINDOW_H
