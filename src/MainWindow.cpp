#include "MainWindow.h"
#include "MemberModel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

#define  QSS_FILE  "./style.qss"

MainWindow *g_MainWindow(0);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
      m_memberModel(new MemberModel(this))
{
    if(g_MainWindow == 0) {
	g_MainWindow = this;
    } else {
	qDebug("You created more the one MainWindow object, EXIT!");
	exit(22);
    }
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

    updateAmount();
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
    for(int i = 0; i < m_memberModel->columnCount(); ++i) {
	m_memberView->setColumnWidth(i,width-2);
    }
}

void MainWindow::showMessage(const QString & message, int timeout)
{
    statusBar()->showMessage(message, timeout);
}

void MainWindow::saveFile()
{
    if(m_memberModel->writeToXml()) {
	showMessage(tr("File saved!"));
    }else {
	showMessage(tr("Save File Error!"));
    }
}

void MainWindow::submittedAndSave()
{
    if(m_memberModel->writeToXml()) {
	showMessage(tr("Submitted, and file saved!"));
    }else {
	showMessage(tr("Submitted, but can't save file!"));
    }
}

void MainWindow::addMember()
{
    if(m_memberView->model()) {
	m_memberModel->appendMember();
	updateAmount();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    adjustHeaderWidth();
}

void MainWindow::updateAmount()
{
    static QString begin("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\"><p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:72pt; font-weight:600; color:#0000ff;\">");

    static QString internal("</span><span style=\" font-size:26pt; font-weight:600; color:#ff0000;\">/</span><span style=\" font-size:26pt; color:#00aa00;\">");

    static QString end("</span></p></body></html>");

    m_amountLabel->setText(begin + QString::number(m_memberModel->submittedSize()) +
			   internal + QString::number(m_memberModel->rowCount()) +
			   end);
}
