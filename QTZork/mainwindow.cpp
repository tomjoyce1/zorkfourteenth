#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ZorkUL.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: black;");
    ui->lineEdit->setStyleSheet("background-color: white;");
    ui->outputLineEdit->setStyleSheet("background-color: white;");

    connect(ui->showMenu, &QPushButton::clicked, this, &MainWindow::toggleMenuVisibility);

QString buttonStyleSheet = "background-color: rgba(0,0,0,0); color: white;"; // Transparent background and white font color
    ui->showMenu->setStyleSheet(buttonStyleSheet);

QString compassButtons = "background-color: gray; color: black;";

    ui->North->setStyleSheet(compassButtons);
    ui->East->setStyleSheet(compassButtons);
    ui->West->setStyleSheet(compassButtons);
    ui->South->setStyleSheet(compassButtons);

    connect(ui->North, &QPushButton::clicked, this, &MainWindow::handleDirectionButton);
    connect(ui->East, &QPushButton::clicked, this, &MainWindow::handleDirectionButton);
    connect(ui->South, &QPushButton::clicked, this, &MainWindow::handleDirectionButton);
    connect(ui->West, &QPushButton::clicked, this, &MainWindow::handleDirectionButton);


    // Initialize zorkUL and pass a reference to this MainWindow
    zorkUL = new ZorkUL(*this);

    QPixmap image("C:\\Users\\Thoma\\OneDrive\\Documents\\fourteenth\\qtzork\\Downloads\\isezork\\QTZork\\WallImages\\Antartica.png");
    ui->imageHolder->setPixmap(image);
    ui->imageHolder->setScaledContents(true);

    //3pm
    //connect(zorkUL, &ZorkUL::roomChanged, this, &MainWindow::handleRoomChange);

    //3pm
    connect(zorkUL, &ZorkUL::roomChangedImage, this, &MainWindow::handleRoomChangeImage);


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

// In MainWindow.cpp
void MainWindow::toggleMenuVisibility() {
    bool isVisible = ui->North->isVisible(); // Check if buttons are currently visible

    // Toggle the visibility of the buttons
    ui->North->setVisible(!isVisible);
    ui->East->setVisible(!isVisible);
    ui->West->setVisible(!isVisible);
    ui->South->setVisible(!isVisible);
}


void MainWindow::handleRoomChangeImage(const std::string &imgName) {


    qDebug() << "Image is changing";
    qDebug() << "Image is changing for room:" << QString::fromStdString(imgName);


    // Update the image here based on the room description
    // For example:


    QPixmap image("C:\\Users\\Thoma\\OneDrive\\Documents\\fourteenth\\qtzork\\Downloads\\isezork\\QTZork\\WallImages\\" + QString::fromStdString(imgName));
    ui->imageHolder->setPixmap(image);
    ui->imageHolder->setScaledContents(true);
}

void MainWindow::on_lineEdit_returnPressed()
{

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

//north south buttons
void MainWindow::handleDirectionButton() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString direction;
    if (button == ui->North) {
        direction = "north";
    } else if (button == ui->East) {
        direction = "east";
    } else if (button == ui->South) {
        direction = "south";
    } else if (button == ui->West) {
        direction = "west";
    }

    if (!direction.isEmpty()) {
        std::string command = "go " + direction.toStdString();
        bool finished = zorkUL->update(command);

        if (finished) {
            setOutputText("The game is finished");
            QCoreApplication::quit();
        }
    }
}
