#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCurrent();


private slots:
    void on_actionminimum_size_triggered();

    void on_actionmaximum_size_triggered();

    void on_action500x500_triggered();

    void on_action400x400_triggered();

    void on_action300x300_triggered();

    void on_s200_triggered();

private:
    Ui::MainWindow *ui;
    void resizeEvent( QResizeEvent *e );
};
#endif // MAINWINDOW_H
