#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    setWindowTitle(tr("Symbol Calculator"));
    calc = new calculator(this);
    setCentralWidget(calc);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{

}

void MainWindow::onExit()
{
    close();
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, tr("About Application"), tr("This is a symbolic calculator"));
}

void MainWindow::onClear()
{
    calc->clearMemory();
}

void MainWindow::onSave()
{
    if (saveOrNot())
        saveFile(tr("hello"));
    else
        close();
}

void MainWindow::onLoad()
{
    loadFile("hello");
}

void MainWindow::createActions()
{
    aboutAction = new QAction(tr("About"), this);
    aboutAction->setStatusTip(tr("About this application"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAbout()));

    exitAction = new QAction(tr("Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit!"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExit()));

    clearAction = new QAction(tr("Clear"), this);
    clearAction->setStatusTip(tr("Clear all results"));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(onClear()));

    saveAction = new QAction(tr("Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save all results"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(onSave()));

    loadAction = new QAction(tr("Load"), this);
    loadAction->setStatusTip(tr("Load recent results"));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(onLoad()));
}

void MainWindow::createMenus()
{
    programMenu = menuBar()->addMenu(tr("&Program"));
    programMenu->addAction(aboutAction);
    programMenu->addSeparator();
    programMenu->addAction(exitAction);

    menuBar()->addSeparator();

    memoryMenu = menuBar()->addMenu(tr("&Memory"));
    memoryMenu->addAction(clearAction);
    memoryMenu->addAction(saveAction);
    memoryMenu->addAction(loadAction);
}

void MainWindow::createToolBars()
{
    programBar = addToolBar(tr("Program"));
    programBar->addAction(aboutAction);
    programBar->addAction(exitAction);

    memoryBar = addToolBar(tr("Memory"));
    memoryBar->addAction(clearAction);
    memoryBar->addAction(saveAction);
    memoryBar->addAction(loadAction);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::loadFile(const QString &fileName)
{
    calc->loadToMemory();
}

bool MainWindow::saveFile(const QString &fileName)
{
    calc->saveMemory();
}

bool MainWindow::saveOrNot()
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("SymCalculator"), tr("Do you want to save your results"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    return (ret == QMessageBox::Save ? true : false);
}
