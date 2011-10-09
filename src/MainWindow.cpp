#include "MainWindow.h"
#include "MemberModel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDateTime>

#define  QSS_FILE  "./style.qss"

MainWindow *g_MainWindow(0);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
      m_memberModel(new MemberModel(this)),
      m_mainTimerId(0)
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

    connect(m_fullScreenAction, SIGNAL(triggered(bool)),
	    this,               SLOT(setShowMode(bool )));

    m_memberView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    m_memberModel->readFromXml();
    m_memberView->setModel(m_memberModel);

    updateAmount();
    updateDateTime();
    m_mainTimerId = startTimer(1000);  //1s
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
    int width = (m_memberView->width() - 18) / m_memberModel->columnCount();
    for(int i = 0; i < m_memberModel->columnCount(); ++i) {
	m_memberView->setColumnWidth(i,width);
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
    m_submitLcdNumber->display(m_memberModel->submittedSize());
    m_amountLcdNumber->display(m_memberModel->rowCount());
}

void MainWindow::setShowMode(bool isFullScreen)
{
    if(isFullScreen)
	showFullScreen();
    else
	showNormal();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    updateAmount();
    if(event->timerId() == m_mainTimerId) {
	updateDateTime();
    }else {
	QMainWindow::timerEvent(event);
    }
}

void MainWindow::updateDateTime()
{
    static bool tmpFlag = true;
    QDateTime dateTime = QDateTime::currentDateTime();

    m_dateLabel->setText(dateTime.toString("yyyy-MM-dd"));
    if(tmpFlag)
	m_timeDayLabel->setText(dateTime.toString("hh:mm   ddd"));
    else
	m_timeDayLabel->setText(dateTime.toString("hh mm   ddd"));
    tmpFlag = !tmpFlag;
}
