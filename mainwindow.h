#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "preferencesdialog.h"
#include <QListView>
#include <QTreeView>
#include <QMessageBox>
#include <QFileDialog>
#include <QMimeType>
#include <QTextStream>
#include <QMimeDatabase>
#include <QFileInfo>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void load();

public slots:
    void browseDir();
    void editPreferences();
    void submit();
    void saveLog();

protected:
    void rangeDir(QString dir);
    void moveFile(QFileInfo fpath);

private:
    Ui::MainWindow *ui;
    QStringList listDir;
    QStringList listDirRange;
    QStringList listType;

};

#endif // MAINWINDOW_H
