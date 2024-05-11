#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ZorkUL.h" // Include ZorkUL.h here

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: grey;");
    ui->lineEdit->setStyleSheet("background-color: white;");
    ui->outputLineEdit->setStyleSheet("background-color: white;");

    // Initialize zorkUL and pass a reference to this MainWindow
    zorkUL = new ZorkUL(*this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setOutputText(const std::string &text) {
    if (ui->outputLineEdit) { // Check if ui->outputLineEdit is not null
        QString qText = QString::fromStdString(text);
        ui->outputLineEdit->setText(qText);
    } else {
        // Handle the case where ui->outputLineEdit is null
        qDebug() << "Error: ui->outputLineEdit is null";
    }
}

void MainWindow::appendOutputText(const std::string &text) {
    if (ui->outputLineEdit) { // Check if ui->outputLineEdit is not null
        std::string currentText = ui->outputLineEdit->text().toStdString();
        ui->outputLineEdit->setText(QString::fromStdString(currentText + text));
    } else {
        // Handle the case where ui->outputLineEdit is null
        qDebug() << "Error: ui->outputLineEdit is null";
    }
}


void MainWindow::on_lineEdit_returnPressed()
{
    ui->outputLineEdit->clear();
    bool finished = zorkUL->update(ui->lineEdit->text().toStdString());

    if (finished)
        QCoreApplication::quit();

    ui->lineEdit->clear();
}

