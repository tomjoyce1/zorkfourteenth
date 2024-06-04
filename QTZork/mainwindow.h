#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

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
    void setOutputText(const std::string &text);
    void appendOutputText(const std::string &text);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:

    void handleRoomChangeImage(const std::string &imgName);
    void handleDirectionButton();

private slots:
    void on_lineEdit_returnPressed();
    void toggleMenuVisibility();

private:
    Ui::MainWindow *ui;
    ZorkUL *zorkUL;
};

#endif // MAINWINDOW_H
