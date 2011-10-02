#include "MainWindow.h"
#include "MemberModel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    m_memberModel = new MemberModel(this);
    m_memberView->setModel(m_memberModel);
}

MainWindow::~MainWindow()
{
    delete m_memberModel;
}
