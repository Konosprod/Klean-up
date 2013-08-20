#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QModelIndex>
#include <QTextStream>
#include "editdialog.h"

namespace Ui {
class preferencesDialog;
}

class preferencesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit preferencesDialog(QWidget *parent = 0);
    ~preferencesDialog();

protected:
    void load();

public slots:
    void editLine(QModelIndex index);
    void addLine();
    void saveConfig();
    void deleteEntry();

private:
    Ui::preferencesDialog *ui;
    QStringList listType;
};

#endif // PREFERENCESDIALOG_H
