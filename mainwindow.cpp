#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//QIODevice形式打开
void MainWindow::on_QFile_open_clicked()
{
    QString path = QDir::currentPath();
    QString title = "打开一个文件";
    QString filter = "程序文件(*.h *.cpp *.txt);;文本文件(*.txt);;所有文件(*.*)";
    QString afile = QFileDialog::getOpenFileName(this, title, path, filter);
    if(afile.isEmpty()){
        return;
    }
    openTextByIODevice(afile);
}

int MainWindow::openTextByIODevice(const QString fileName)
{
    QFile file(fileName);
    if(!file.exists()){
        return false;
    }
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }
    ui->plainTextEdit->setPlainText(file.readAll());
    file.close();
}

//QTextStream形式打开
void MainWindow::on_QTextStream_open_clicked()
{
    QString path = QDir::currentPath();
    QString title = "打开一个文件";
    QString filter = "程序文件(*.h *.cpp *.txt);;文本文件(*.txt);;所有文件(*.*)";
    QString afile = QFileDialog::getOpenFileName(this, title, path, filter);
    if(afile.isEmpty()){
        return;
    }
    openTextByTextStream(afile);
}


int MainWindow::openTextByTextStream(const QString &filename)
{
    QFile file(filename);
    if(!file.exists()){
        return false;
    }
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }
    QTextStream stream(&file);
    stream.setAutoDetectUnicode(true);
    ui->plainTextEdit->setPlainText(stream.readAll());
    file.close();
    return true;
}


//QIODevice另存
void MainWindow::on_QFile_save_clicked()
{
    if(ui->plainTextEdit->document()->isEmpty()){
        QMessageBox::warning(this, "警告", "存储内容为空，请先打开一个文件！", QMessageBox::Ok);
        return;
    }

    QString path = QDir::currentPath();
    QString title = "另存一个文件";
    QString filter = "h文件(*.h);;c++文件(*.cpp);;所有文件(*.*)";
    QString afile = QFileDialog::getSaveFileName(this, title, path, filter);
    if(afile.isEmpty()){
        return;
    }
    saveByIODevice(afile);
}

int MainWindow::saveByIODevice(const QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }
    QString str = ui->plainTextEdit->toPlainText();
    QByteArray array = str.toUtf8();
    file.write(array);
    file.close();
    return true;
}

//TextStream保存
void MainWindow::on_QTextStream_save_clicked()
{
    if(ui->plainTextEdit->document()->isEmpty()){
        QMessageBox::warning(this, "警告", "存储内容为空，请先打开一个文件！", QMessageBox::Ok);
        return;
    }
    QString path = QDir::currentPath();
    QString titlt = "TextStream保存";
    QString filter = "h文件(*.h);;c++文件(*.cpp);;txt(*.txt);;所有文件(*.*)";
    QString afile = QFileDialog::getSaveFileName(this, titlt, path, filter);
    if(afile.isEmpty()){
        return;
    }
    saveByTextStream(afile);
}


int MainWindow::saveByTextStream(const QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::Text | QIODevice::WriteOnly)){
        return false;
    }
    QTextStream stream(&file);
    stream.setAutoDetectUnicode(true);
    QString str = ui->plainTextEdit->toPlainText();
    stream<<str;
    file.close();
    return true;
}

//退出
void MainWindow::on_quit_clicked()
{
    this->close();
}
