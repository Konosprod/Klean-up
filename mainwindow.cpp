#include "mainwindow.h"
#include "ui_mainwindow.h"


/*

 Demo of Qt 5 QMimeType and QMimeDatabase classes. Displays MIME information for a file.

*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Klean up");
    ui->actionPr_f_rences->setIconVisibleInMenu(true);
    ui->actionPr_f_rences->setIcon(QIcon(":/ressources/rPref"));

    load();

    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browseDir()));
    connect(ui->actionPr_f_rences, SIGNAL(triggered()), this, SLOT(editPreferences()));
    connect(ui->rangeButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(ui->saveLogButton, SIGNAL(clicked()), this, SLOT(saveLog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::submit()
{
    foreach(QString dir, listDir)
    {
        ui->logText->appendHtml("<font color=\"green\"> Rangement de : <b>" + dir + "</b></font>");
        rangeDir(dir);
        ui->logText->appendHtml("<font color=\"green\">----------------------------------</font>");
    }
}

void MainWindow::load()
{
    QString mime = "";
    QString dir = "";
    QFile file("config.cfg");
    file.open(QIODevice::ReadWrite | QIODevice::Text);

    if(!file.isOpen())
    {
        QMessageBox::warning(this, "Erreur", "Impossible de créer/ouvrir le fichier config.cfg");
        return;
    }

    QTextStream stream(&file);

    while(!stream.atEnd())
    {
        stream >> mime;
        stream >> dir;

        listType.append(mime);
        listDirRange.append(dir);
    }

    file.close();
}

void MainWindow::moveFile(QFileInfo fpath)
{
    QMimeDatabase db;
    QMimeType mimetype;
    mimetype = db.mimeTypeForFile(fpath.absoluteFilePath());

    if(listType.contains(mimetype.name()))
    {
        int index = listType.indexOf(mimetype.name());
        QString text = "[%4] Déplacement de <b>%1</b> depuis <font color=\"red\">%2</font> vers <font color=\"blue\">%3</font>";
        ui->logText->appendHtml(text.arg(fpath.baseName() + "." + fpath.completeSuffix(), fpath.absolutePath(),
                                         listDirRange.at(index), QTime::currentTime().toString("HH:mm:ss")));
        QFile::copy(fpath.absoluteFilePath(), listDirRange.at(index) + "/" + fpath.baseName() + "." + fpath.completeSuffix());
        QFile::remove(fpath.absoluteFilePath());
    }
}

void MainWindow::saveLog()
{
    QString filename = QFileDialog::getSaveFileName(this, "Enregistrer le log", QDir::homePath(), "HTML (*.html *.htm)");

    if(!filename.isEmpty())
    {
        QFile f(filename);
        f.open(QIODevice::ReadWrite | QIODevice::Text);

        if(!f.isOpen())
        {
            QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier : " + filename);
        }
        else
        {
            QString content = ui->logText->document()->toHtml();

            f.write(content.toUtf8(), content.size());
            f.close();
        }
    }
}

void MainWindow::editPreferences()
{
    preferencesDialog pd;

    pd.exec();
}

void MainWindow::rangeDir(QString dir)
{
    QDir directory(dir);

    foreach(QFileInfo s, directory.entryInfoList(QDir::Files))
    {
        moveFile(s);
    }
}

void MainWindow::browseDir()
{
    QFileDialog w;
    w.setWindowTitle("Sélectionnez un ou des dossiers");
    w.setFileMode(QFileDialog::DirectoryOnly);
    w.setDirectory(QDir::home());
    w.setOption(QFileDialog::DontUseNativeDialog,true);
    QListView *l = w.findChild<QListView*>("listView");
    if (l)
    {
        l->setSelectionMode(QAbstractItemView::MultiSelection);
    }
    QTreeView *t = w.findChild<QTreeView*>();
    if (t)
    {
        t->setSelectionMode(QAbstractItemView::MultiSelection);
    }
    if(w.exec() == QDialog::Accepted)
    {
        listDir = w.selectedFiles();
    }

    ui->entryDir->setText(listDir.join(' '));
}
