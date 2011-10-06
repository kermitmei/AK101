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
protected:
    virtual void resizeEvent(QResizeEvent * event);

    MemberModel  *m_memberModel;
};

extern MainWindow *g_MainWindow;

#endif//_MAINWINDOW_H_
