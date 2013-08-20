#include "editdialog.h"
#include "ui_editdialog.h"

editDialog::editDialog(QWidget *parent, QString mime, QString path) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
    ui->dirLine->setText(path);
    ui->lineMIME->setText(mime);

    setWindowIcon(QIcon(":/ressources/rIcon"));

    connect(ui->browseFileButton, SIGNAL(clicked()), this, SLOT(refFile()));
    connect(ui->browseDirButton, SIGNAL(clicked()), this, SLOT(browseDir()));
}

editDialog::~editDialog()
{
    delete ui;
}

void editDialog::refFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choisissez le fichier de référence");

    if(!filename.isEmpty())
    {
        QMimeDatabase db;
        QMimeType mimeType;

        ui->pathLine->setText(filename);
        mimeType = db.mimeTypeForFile(filename);
        ui->lineMIME->setText(mimeType.name());
    }
}

void editDialog::browseDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Sélectionnez le dossier où ranger", QDir::homePath());

    if(!dir.isEmpty())
    {
        ui->dirLine->setText(dir);
    }
}

QString editDialog::directory()
{
    return ui->dirLine->text();
}

QString editDialog::mimeType()
{
    return ui->lineMIME->text();
}
