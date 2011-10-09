#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include "ui_MainWindow.h"

class MemberModel;
class QResizeEvent;

class MainWindow : public QMainWindow,
		   public Ui::MainWindow
{
    Q_OBJECT;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openFile();
    void saveFile();
    void addMember();
    void adjustHeaderWidth();
    void updateAmount();
    void showMessage(const QString & message, int timeout = 0);
    void submittedAndSave();
    void setShowMode(bool isFullScreen);
protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    void updateDateTime();

    MemberModel  *m_memberModel;
    int           m_mainTimerId;
};

extern MainWindow *g_MainWindow;

#endif//_MAINWINDOW_H_
