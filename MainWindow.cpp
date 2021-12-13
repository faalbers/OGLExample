#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

MainWindow::MainWindow()
    : ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
}

MainWindow::~MainWindow()
{
}
