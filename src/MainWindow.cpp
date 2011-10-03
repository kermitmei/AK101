#include "MainWindow.h"
#include "MemberModel.h"

#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
      m_memberModel(new MemberModel(this))
{
    setupUi(this);
    connect(m_openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(m_saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
}

MainWindow::~MainWindow()
{
    delete m_memberModel;
}

void MainWindow::openFile()
{
    m_fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
					      ".",  tr("XML files (*.xml)"));

    if(m_memberModel->readFromXml(m_fileName))
	m_memberView->setModel(m_memberModel);
}

void MainWindow::saveFile()
{
    if(m_fileName.isEmpty())
	return ;
    if(m_memberModel->writeToXml(m_fileName)) {
	QMessageBox::information(this, tr("Save File"),tr("File saved!"));
    }else {
	QMessageBox::warning(this, tr("Save File"),tr("Save File Error!"));
    }
}
