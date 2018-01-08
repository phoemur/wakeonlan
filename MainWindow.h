#ifndef WAKEONLAN_MAINWINDOW
#define WAKEONLAN_MAINWINDOW

#include <QDialog>
#include <QString>
#include <QKeyEvent>
#include <memory>

#include "ui_MainWindow.h"

namespace Ui {
    class MainWindow; // forward declaration
}

class MainWindow : public QDialog {
    Q_OBJECT
    std::unique_ptr<Ui::MainWindow> ui;
    
public:
    MainWindow(QDialog* parent = nullptr);
    
private slots:
    void wake();
    
protected:
    void keyPressEvent(QKeyEvent*);
    
}; // class MainWindow


#endif // WAKEONLAN_MAINWINDOW