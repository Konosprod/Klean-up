#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"


preferencesDialog::preferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preferencesDialog)
{
    ui->setupUi(this);
    setWindowTitle("Editer les préférences");
    setWindowIcon(QIcon(":/ressources/rIcon"));

    load();

    connect(ui->tableConfig, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editLine(QModelIndex)));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addLine()));
    connect(this, SIGNAL(accepted()), this, SLOT(saveConfig()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteEntry()));
}

preferencesDialog::~preferencesDialog()
{
    delete ui;
}

void preferencesDialog::addLine()
{
    editDialog* ed = new editDialog(this, "", "");

    if(ed->exec() == QDialog::Accepted)
    {
        QTableWidgetItem* mime = new QTableWidgetItem;
        QTableWidgetItem* dir = new QTableWidgetItem;

        if(!listType.contains(ed->mimeType()))
        {
            ui->tableConfig->setRowCount(ui->tableConfig->rowCount()+1);

            mime->setText(ed->mimeType());
            dir->setText(ed->directory());

            ui->tableConfig->setItem(ui->tableConfig->rowCount()-1, 0, mime);
            ui->tableConfig->setItem(ui->tableConfig->rowCount()-1, 1, dir);
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Vous avez déjà définis ce type mime !");
        }
    }

}

void preferencesDialog::deleteEntry()
{
    if(ui->tableConfig->currentIndex().isValid())
    {
        ui->tableConfig->removeRow(ui->tableConfig->currentIndex().row());
    }
}

void preferencesDialog::load()
{
    QString mime = "";
    QString dir = "";
    QFile file("config.cfg");
    file.open(QIODevice::ReadWrite | QIODevice::Text);

    if(!file.isOpen())
    {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier config.cfg");
        return;
    }

    QTextStream stream(&file);

    while(!stream.atEnd())
    {
        stream >> mime;
        stream >> dir;

        if(mime != "")
        {
            listType.append(mime);
            ui->tableConfig->setRowCount(ui->tableConfig->rowCount()+1);

            QTableWidgetItem* mimetype = new QTableWidgetItem;
            QTableWidgetItem* directory = new QTableWidgetItem;

            mimetype->setText(mime);
            directory->setText(dir);

            ui->tableConfig->setItem(ui->tableConfig->rowCount()-1, 0, mimetype);
            ui->tableConfig->setItem(ui->tableConfig->rowCount()-1, 1, directory);
        }
    }

    file.close();
}

void preferencesDialog::saveConfig()
{
    QString mime = "";
    QString dir = "";
    QString line = "";
    QFile file("config.cfg");

    file.open(QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly);

    for(int i = 0; i < ui->tableConfig->rowCount(); i++)
    {
        mime = ui->tableConfig->model()->data(ui->tableConfig->model()->index(i, 0)).toString();
        dir = ui->tableConfig->model()->data(ui->tableConfig->model()->index(i, 1)).toString();

        line = mime + " " + dir + "\n";

        file.write(line.toUtf8(), line.size());
    }

    file.close();
}

void preferencesDialog::editLine(QModelIndex index)
{
    (void)index;
    QString mime = ui->tableConfig->model()->data(ui->tableConfig->model()->index(ui->tableConfig->currentIndex().row(), 0)).toString();
    QString dir = ui->tableConfig->model()->data(ui->tableConfig->model()->index(ui->tableConfig->currentIndex().row(), 1)).toString();

    editDialog* ed = new editDialog(this, mime, dir);

    if(ed->exec() == QDialog::Accepted)
    {
        QTableWidgetItem* mimetype = new QTableWidgetItem;
        QTableWidgetItem* directory = new QTableWidgetItem;

        mimetype->setText(ed->mimeType());
        directory->setText(ed->directory());

        ui->tableConfig->setItem(ui->tableConfig->currentIndex().row(), 0, mimetype);
        ui->tableConfig->setItem(ui->tableConfig->currentIndex().row(), 1, directory);
    }
}
