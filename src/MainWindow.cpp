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
    connect(m_submitAction, SIGNAL(triggered()), 
	    m_memberModel,  SLOT(submitMember()));
    m_memberView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
}

MainWindow::~MainWindow()
{
    delete m_memberModel;
}

void MainWindow::openFile()
{
    m_fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
					      ".",  tr("XML files (*.xml)"));

    if(m_memberModel->readFromXml(m_fileName)) {
	m_memberView->setModel(m_memberModel);
	int width = m_memberView->width() / m_memberModel->columnCount();
	for(int i = 0; i < m_memberModel->columnCount(); ++i) {
	    m_memberView->setColumnWidth(i,width-3);
	}
    }
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

