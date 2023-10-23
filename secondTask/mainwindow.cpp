#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include "StringTools.h"

void printLine(QPlainTextEdit *resultWindow, std::string S) {
    resultWindow->appendPlainText(QString::fromStdString(S));
}

QString MainWindow::getActiveFont(void) {
    switch(activeFont) {
    case 1:
        return "\
               font-family: roboto;\
            font-size: 16px;\
            font-weight: 800;\
            line-height: 16px;\
               ";
    case 2:
        return "\
               font-family: Times New Roman;\
            font-size: 12px;\
            font-weight: bold;\
            line-height: 18px;\
               ";
    case 3:
        return "\
               font-family: Calibri;\
            font-size: 19px;\
            font-weight: bold;\
            line-height: 24px;\
               ";
    }
    return "";
}

void MainWindow::saveTheme(void) {
    std::ofstream out;
    out.open("theme.conf");
    out << activeTheme << ' ' << activeFont;
    out.close();
}

void MainWindow::loadTheme(void) {
    std::ifstream in;
    in.open("theme.conf");
    in >> activeTheme >> activeFont;
    in.close();
    switch(activeTheme) {
    case 1:
        setFirstTheme();
        break;
    case 2:
        setSecondTheme();
        break;
    case 3:
        setThirdTheme();
        break;
    }
}

void MainWindow::reloadTheme(void) {
    switch(activeTheme) {
    case 1:
        setFirstTheme();
        break;
    case 2:
        setSecondTheme();
        break;
    case 3:
        setThirdTheme();
        break;
    }
}

void MainWindow::setFirstFont(void) {
    activeFont = 1;
    this->setStyleSheet("\
        font-family: roboto;\
        font-size: 16px;\
        font-weight: 800;\
        line-height: 16px;\
        ");
    reloadTheme();
    saveTheme();
}

void MainWindow::setSecondFont(void) {
    activeFont = 2;
    this->setStyleSheet("\
        font-family: Times New Roman;\
        font-size: 12px;\
        font-weight: bold;\
        line-height: 18px;\
        ");
    reloadTheme();
    saveTheme();
}

void MainWindow::setThirdFont(void) {
    activeFont = 3;
    this->setStyleSheet("\
        font-family: Calibri;\
        font-size: 19px;\
        font-weight: bold;\
        line-height: 24px;\
        ");
    reloadTheme();
    saveTheme();
}

void MainWindow::on_actionCucumber_triggered(void) {
    setFirstFont();
    processFiles();
}

void MainWindow::on_actionWally_triggered(void) {
    setSecondFont();
    processFiles();
}

void MainWindow::on_actionMemory_triggered(void) {
    setThirdFont();
    processFiles();
}

void MainWindow::setFirstTheme(void) {
    activeTheme = 1;
    saveTheme();
    redColor = Qt::red;
    yellowColor = Qt::yellow;
    greenColor = Qt::green;
    this->setStyleSheet(getActiveFont() + "background-color: white; color: black;");
    ui->fileText1->setStyleSheet(getActiveFont() + "background-color: white; color: black;");
    ui->fileText2->setStyleSheet(getActiveFont() + "background-color: white; color: black;");
//    ui->resultWindow->setStyleSheet(getActiveFont() + "background-color: white; color: black;");
    ui->openFileButton1->
            setStyleSheet(getActiveFont() + "\
          background: #FF4742;\
          border: 1px solid #FF4742;\
          border-radius: 6px;\
          box-shadow: rgba(0, 0, 0, 0.1) 1px 2px 4px;\
          box-sizing: border-box;\
          color: #FFFFFF;\
          cursor: pointer;\
          display: inline-block;\
    ");
    ui->openFileButton2->
            setStyleSheet(getActiveFont() + "\
          background: #FF4742;\
          border: 1px solid #FF4742;\
          border-radius: 6px;\
          box-shadow: rgba(0, 0, 0, 0.1) 1px 2px 4px;\
          box-sizing: border-box;\
          color: #FFFFFF;\
          cursor: pointer;\
          display: inline-block;\
          text-rendering: geometricprecision;\
          text-transform: none;\
    ");
}

void MainWindow::setSecondTheme(void) {
    activeTheme = 2;
    saveTheme();
    redColor = Qt::darkRed;
    yellowColor = Qt::darkYellow;
    greenColor = Qt::darkGreen;
    this->setStyleSheet(getActiveFont() + "background-color: #948B89; color: black;");
    ui->fileText1->setStyleSheet(getActiveFont() + "background-color: #948B89; color: black;");
    ui->fileText2->setStyleSheet(getActiveFont() + "background-color: #948B89; color: black;");
//    ui->resultWindow->setStyleSheet(getActiveFont() + "background-color: #948B89; color: black;");
    ui->openFileButton1->
        setStyleSheet(getActiveFont() + "\
          color: #fff\
          padding: 0;\
          border-radius: 5px;\
          background-color: #4C43CD;\
          background-image: radial-gradient(93% 87% at 87% 89%, rgba(0, 0, 0, 0.23) 0%, transparent 86.18%), radial-gradient(66% 87% at 26% 20%, rgba(255, 255, 255, 0.41) 0%, rgba(255, 255, 255, 0) 69.79%, rgba(255, 255, 255, 0) 100%);\
        ");
    ui->openFileButton2->
        setStyleSheet(getActiveFont() + "\
          color: #fff\
          padding: 0;\
          border-radius: 5px;\
          background-color: #4C43CD;\
          background-image: radial-gradient(93% 87% at 87% 89%, rgba(0, 0, 0, 0.23) 0%, transparent 86.18%), radial-gradient(66% 87% at 26% 20%, rgba(255, 255, 255, 0.41) 0%, rgba(255, 255, 255, 0) 69.79%, rgba(255, 255, 255, 0) 100%);\
        ");
}

void MainWindow::setThirdTheme(void) {
    activeTheme = 3;
    saveTheme();
    redColor = Qt::red;
    yellowColor = Qt::yellow;
    greenColor = Qt::green;
    this->setStyleSheet(getActiveFont() + "background-color: white; color: black;");
    ui->fileText1->setStyleSheet(getActiveFont() + "background-color: #bbd1ea; color: black;");
    ui->fileText2->setStyleSheet(getActiveFont() + "background-color: #bbd1ea; color: black;");
//    ui->resultWindow->setStyleSheet(getActiveFont() + "background-color: #bbd1ea; color: black;");
    ui->openFileButton1->
          setStyleSheet(getActiveFont() + "\
            background: blue;\
            border: 1px solid #FF4742;\
            border-radius: 6px;\
            box-shadow: rgba(0, 0, 0, 0.1) 1px 2px 4px;\
            box-sizing: border-box;\
            color: #FFFFFF;\
            cursor: pointer;\
            display: inline-block;\
            text-rendering: geometricprecision;\
            text-transform: none;\
        ");
    ui->openFileButton2->
          setStyleSheet(getActiveFont() + "\
            background: blue;\
            border: 1px solid #FF4742;\
            border-radius: 6px;\
            box-shadow: rgba(0, 0, 0, 0.1) 1px 2px 4px;\
            box-sizing: border-box;\
            color: #FFFFFF;\
            cursor: pointer;\
            display: inline-block;\
            text-rendering: geometricprecision;\
            text-transform: none;\
        ");
}

void MainWindow::on_actionLight_Libra_2_triggered(void) {
    setFirstTheme();
    processFiles();
}

void MainWindow::on_actionDark_Sepia_2_triggered(void) {
    setSecondTheme();
    processFiles();
}

void MainWindow::on_actionLight_Lagoona_2_triggered(void) {
    setThirdTheme();
    processFiles();
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    this->setFixedSize(914, 615);
    ui->setupUi(this);
    ui->openFileButton1->resize(
        QSize(100, 35)
        );
    ui->openFileButton2->resize(
        QSize(100, 35)
        );
    loadTheme();
    ui->fileText1->setReadOnly(true);
    ui->fileText2->setReadOnly(true);
//    ui->resultWindow->setReadOnly(true);
}

void MainWindow::readFile(std::vector<std::string> &dest, QLabel *label, QPlainTextEdit *textEdit) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select file"), "C://");
    if (fileName == "") {
        return;
    }
    dest.clear();
    label->setText(StringTools::extractFileName(fileName));
    std::ifstream inputFile(fileName.toStdString());
    std::string content, fileContent = "";
    getline(inputFile, fileContent);
    dest.push_back(fileContent);
    while (getline(inputFile, content)) {
        fileContent += "\n" + content;
        dest.push_back(content);
    }
    textEdit->setPlainText(tr(fileContent.c_str()));
}

void MainWindow::on_openFileButton1_clicked(void) {
    readFile(file1Content, ui->fileName1, ui->fileText1);
    processFiles();
}

void MainWindow::on_openFileButton2_clicked(void) {
    readFile(file2Content, ui->fileName2, ui->fileText2);
    processFiles();
}

#define END_OF_PLAIN_TEXT ui->fileText1->toPlainText().size()

void MainWindow::processFiles(void) {
    if (ui->fileName1->text() == "" || ui->fileName2->text() == "") {
        return;
    }
    ui->fileText1->setPlainText("");
    std::vector < int > whiteRows1, whiteRows2, yellowRows1, yellowRows2;
    StringTools::findLCS(file1Content, file2Content, &whiteRows1, &whiteRows2);
    int white = 0, i = 0, j = 0;
    while(i < file1Content.size() && j < file2Content.size()) {
        i = whiteRows1[white] + 1;
        j = whiteRows2[white] + 1;
        for (; i < whiteRows1[white+1]; ++ i) {
            if (yellowRows2.size()) {
                j = std::max(yellowRows2.back(), whiteRows2[white]) + 1;
            } else {
                j = whiteRows2[white] + 1;
            }
            for(; j < whiteRows2[white+1]; ++ j) {
                if (StringTools::coefficient(file1Content[i], file2Content[j]) > MINIMUM_COEFFICIENT) {
                    yellowRows1.push_back(i);
                    yellowRows2.push_back(j);
                    break;
                }
            }
        }
        ++ white;
    }
    yellowRows1.push_back(file1Content.size());
    yellowRows2.push_back(file2Content.size());
    white = 1, j = 0, i = 0;
    int yellow = 0;
    int position = 0;
    while(i < file1Content.size()) {
        position = END_OF_PLAIN_TEXT;
        if (i == whiteRows1[white] && j == whiteRows2[white]) {
            printLine(ui->fileText1, file1Content[i]);
            ++ white;
            ++ j;
            ++ i;
        } else {
            if (i == yellowRows1[yellow] && j == yellowRows2[yellow]) {
                printLine(ui->fileText1, file1Content[i]);
                StringTools::formatText(yellowColor, ui->fileText1, position, END_OF_PLAIN_TEXT);
                ++ yellow;
                ++ j;
                ++ i;
            } else {
                if (i != yellowRows1[yellow] && i != whiteRows1[white]) {
                    printLine(ui->fileText1, file1Content[i]);
                    StringTools::formatText(redColor, ui->fileText1, position, END_OF_PLAIN_TEXT);
                    ++ i;
                } else {
                    if (j != yellowRows2[yellow] && j != whiteRows2[white]) {
                        printLine(ui->fileText1, file2Content[j]);
                        StringTools::formatText(greenColor, ui->fileText1, position, END_OF_PLAIN_TEXT);
                        ++ j;
                    }
                }
            }
        }
    }
}

MainWindow::~MainWindow(void) {
    delete ui;
}

