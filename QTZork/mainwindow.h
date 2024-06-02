#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string> // Include string header for std::string

// Forward declaration of ZorkUL class
class ZorkUL;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setOutputText(const std::string &text); // Change QString to std::string
    void appendOutputText(const std::string &text); // Change QString to std::string
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    //void handleRoomChange(const std::string &description);

    //3pm
    void handleRoomChangeImage(const std::string &imgName);
    void handleDirectionButton();

private slots:
    void on_lineEdit_returnPressed();
    void toggleMenuVisibility();

private:
    Ui::MainWindow *ui;
    ZorkUL *zorkUL; // Declare a pointer to ZorkUL
};

#endif // MAINWINDOW_H
