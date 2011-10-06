#include "MainWindow.h"
#include "MemberModel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

#define  QSS_FILE  "./style.qss"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
      m_memberModel(new MemberModel(this))
{
    QFile file(QSS_FILE);
    if(file.open(QFile::ReadOnly))
	qApp->setStyleSheet(file.readAll());

    setupUi(this);
    connect(m_openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(m_openBtn,    SIGNAL(clicked()), this, SLOT(openFile()));

    connect(m_saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(m_saveBtn,    SIGNAL(clicked()), this, SLOT(saveFile()));

    connect(m_submitAction, SIGNAL(triggered()), m_memberModel,  SLOT(submitMember()));
    connect(m_submitBtn,    SIGNAL(clicked()), m_memberModel,  SLOT(submitMember()));

    connect(m_addAction, SIGNAL(triggered()), this, SLOT(addMember()));
    connect(m_addBtn,    SIGNAL(clicked()), this, SLOT(addMember()));

    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(m_exitBtn,    SIGNAL(clicked()), this, SLOT(close()));
    m_memberView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    m_memberModel->readFromXml();
    m_memberView->setModel(m_memberModel);
    adjustHeaderWidth();
}

MainWindow::~MainWindow()
{
    delete m_memberModel;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
						    ".",  tr("XML files (*.xml)"));
    if(m_memberModel->readFromXml(fileName)) {
	m_memberView->setModel(m_memberModel);
	adjustHeaderWidth();
    }else {
	QMessageBox::warning(this, 
			     tr("Open File"),
			     tr("Can't open file %1!\n"
				"If you really want to do it, please restart this program.")
			     .arg(fileName));
	return ;
    }
}

void MainWindow::adjustHeaderWidth()
{
    int width = m_memberView->width() / m_memberModel->columnCount();
    qDebug("view width = %d, cc=%d mywidth = %d",
	   m_memberView->width(),
	   m_memberModel->columnCount(),width);
    for(int i = 0; i < m_memberModel->columnCount(); ++i) {
	m_memberView->setColumnWidth(i,width-2);
    }
}

void MainWindow::saveFile()
{
    if(m_memberModel->writeToXml()) {
	QMessageBox::information(this, tr("Save File"),tr("File saved!"));
    }else {
	QMessageBox::warning(this, tr("Save File"),tr("Save File Error!"));
    }
}

void MainWindow::addMember()
{
    if(m_memberView->model())
	m_memberModel->appendMember();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    adjustHeaderWidth();
}
