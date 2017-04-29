#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QTextCodec>
#include <QLabel>
#include <QImage>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Shell");
    ui->pushButton_2->setText("打开电路");
    ui->pushButton_4->setText("一键运算");
    ui->pushButton_5->setText("真值显示");
    ui->pushButton_6->setText("基本电路显示");
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QProcess::startDetached(QCoreApplication::applicationDirPath() + "\\QCSShell.exe", QStringList());

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    QString c = QFileDialog::getOpenFileName(this, tr("Open File"),".",tr("file(*.real)"));
    if (c.isEmpty())
        return;

    QFile file(c);
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        return;

    QTextStream read(&file);
    while(read.atEnd() == 0)
    {
        ui->textEdit->append(read.readLine());
    }

    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
    QTextCodec* codec = QTextCodec::codecForName("gb18030");
    QTextCodec::setCodecForLocale(codec);
    configIniWrite->setValue("/FilePath/Circuit", c);
    delete configIniWrite;

    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_4->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString c = QFileDialog::getExistingDirectory (this, tr("QFileDialog::getExistingDirectory()"));
    if (c.isEmpty())
        return;

    ui->lineEdit->setText(c);

    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
    QTextCodec* codec = QTextCodec::codecForName("gb18030");
    QTextCodec::setCodecForLocale(codec);
    configIniWrite->setValue("/FilePath/GateLib", c);
    delete configIniWrite;
}

void MainWindow::on_pushButton_4_clicked()
{
    QProcess::startDetached(QCoreApplication::applicationDirPath() + "\\AutoGo.exe", QStringList());
    ui->pushButton_5->show();
    ui->pushButton_6->show();
    ui->pushButton_4->hide();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->textEdit->clear();

    QString c = QCoreApplication::applicationDirPath() + "\\~temp.truth";
    QFile file(c);
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        return;

    QTextStream read(&file);
    while(read.atEnd() == 0)
    {
        ui->textEdit->append(read.readLine());
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->textEdit->clear();
    QString c = QCoreApplication::applicationDirPath() + "\\~temp.real";
    QFile file(c);
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        return;

    QTextStream read(&file);
    while(read.atEnd() == 0)
    {
        ui->textEdit->append(read.readLine());
    }
}
