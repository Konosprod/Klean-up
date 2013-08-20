#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QMimeDatabase>
#include <QMimeType>
#include <QFileDialog>

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit editDialog(QWidget *parent = 0, QString mime = "", QString path = "");
    ~editDialog();
    QString directory();
    QString mimeType();

public slots:
    void refFile();
    void browseDir();

private:
    Ui::editDialog *ui;
};

#endif // EDITDIALOG_H
