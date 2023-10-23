#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* = nullptr);
    ~MainWindow();

private slots:
/*

These mathods will be called after clicking buttons.

*/
    void on_openFileButton1_clicked(void);
    void on_openFileButton2_clicked(void);
    void on_actionLight_Libra_2_triggered(void);
    void on_actionDark_Sepia_2_triggered(void);
    void on_actionLight_Lagoona_2_triggered(void);
    void on_actionWally_triggered(void);
    void on_actionCucumber_triggered(void);
    void on_actionMemory_triggered(void);

private:
    Ui::MainWindow *ui;
    void setFirstTheme(void);
    void setSecondTheme(void);
    void setThirdTheme(void);
    void setFirstFont(void);
    void setSecondFont(void);
    void setThirdFont(void);
    void processFiles(void);
    void readFile(std::vector<std::string> &, QLabel *, QPlainTextEdit *);
    void saveTheme(void);
    void loadTheme(void);
    void reloadTheme(void);

    QString getActiveFont(void);

    std::vector<std::string> file1Content, file2Content;
    Qt::GlobalColor redColor, yellowColor, greenColor;
    int activeTheme, activeFont;
};
#endif // MAINWINDOW_H
