#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "Huffman.hpp"
#include "LZW.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize progress bar
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);

    // Connect buttons to slots
    connect(ui->btnCompress, &QPushButton::clicked, this, &MainWindow::onCompressClicked);
    connect(ui->btnDecompress, &QPushButton::clicked, this, &MainWindow::onDecompressClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCompressClicked(){
    QString file = QFileDialog::getOpenFileName(this, "Select file to Compress");
    if(file.isEmpty()) return;

    ui->txtFilePath->setText(file);
    ui->textLog->append("Compressing...");
    ui->progressBar->setValue(0);

    QString algo = ui->comboAlgorithm->currentText();

    try{
        ui->progressBar->setValue(10);

        if(algo == "Huffman"){
            Huffman h;
            h.compress(file.toStdString(), file.toStdString() + ".huff");
        }
        else if(algo == "LZW"){
            LZW l;
            l.compress(file.toStdString(), file.toStdString() + ".lzw");
        }

        ui->progressBar->setValue(100);
        ui->textLog->append("✅ Compression complete!");
    }
    catch(const std::exception &e){
        QMessageBox::warning(this, "Error", QString("Compression failed:\n%1").arg(e.what()));
        ui->progressBar->setValue(0);
    }
}

void MainWindow::onDecompressClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Select File to Decompress");
    if(file.isEmpty()) return;

    ui->txtFilePath->setText(file);
    ui->textLog->append("Decompressing...");
    ui->progressBar->setValue(0);

    QString algo = ui->comboAlgorithm->currentText();

    try
    {
        ui->progressBar->setValue(10);

        if (algo == "Huffman") {
            Huffman h;
            h.decompress(file.toStdString(), file.toStdString() + ".restored");
        }
        else if (algo == "LZW") {
            LZW l;
            l.decompress(file.toStdString(), file.toStdString() + ".restored");
        }

        ui->progressBar->setValue(100);
        ui->textLog->append("✅ Decompression complete!");
    }
    catch(const std::exception &e)
    {
        QMessageBox::warning(this, "Error", QString("Decompression failed:\n%1").arg(e.what()));
        ui->progressBar->setValue(0);
    }
}
