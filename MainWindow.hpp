#ifndef OGLEXAMPLE_MAINWINDOW
#define OGLEXAMPLE_MAINWINDOW

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    
private:    
    Ui::MainWindow* ui_;
};

#endif