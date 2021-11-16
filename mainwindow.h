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

private slots:
    void on_QFile_open_clicked();

    void on_quit_clicked();

    void on_QFile_save_clicked();

    void on_QTextStream_open_clicked();

    void on_QTextStream_save_clicked();

private:
    Ui::MainWindow *ui;
    int openTextByIODevice(const QString fileName);
    int saveByIODevice(const QString filename);

    int openTextByTextStream(const QString &filename);
    int saveByTextStream(const QString filename);
};
#endif // MAINWINDOW_H
