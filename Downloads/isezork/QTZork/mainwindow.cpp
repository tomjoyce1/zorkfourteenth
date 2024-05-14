#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ZorkUL.h" // Include ZorkUL.h here

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: gray;");
    ui->lineEdit->setStyleSheet("background-color: white;");
    ui->outputLineEdit->setStyleSheet("background-color: white;");

    // Initialize zorkUL and pass a reference to this MainWindow
    zorkUL = new ZorkUL(*this);

    connect(zorkUL, &ZorkUL::roomChanged, this, &MainWindow::handleRoomChange);
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

void MainWindow::handleRoomChange(const std::string &description) {
    qDebug() << "Image is changing";
    // Update the image here based on the room description
    // For example:
    QPixmap image("C:\\Users\\Thoma\\Downloads\\aaa.png");
    ui->imageHolder->setPixmap(image);
    ui->imageHolder->setScaledContents(true);
}

void MainWindow::on_lineEdit_returnPressed()
{
    appendOutputText("works up to here");
    ui->outputLineEdit->clear();

    std::string text = ui->lineEdit->text().toStdString();

    if (!text.empty()) {
        qDebug() << "Text not empty, calling update with text: " << QString::fromStdString(text);

        bool finished = zorkUL->update(text);

        if (finished) {
            setOutputText("The game is finished");
            QCoreApplication::quit();
        }
    } else {
        qDebug() << "Text is empty";
        // Handle empty buffer here, such as displaying a message to the user
    }

    ui->lineEdit->clear();
}
