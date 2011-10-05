#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include "ui_MainWindow.h"

class MemberModel;

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

protected:
    MemberModel  *m_memberModel;
    QString       m_fileName;
};


#endif//_MAINWINDOW_H_
