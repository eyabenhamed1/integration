#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionequipements.h"
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Add equipment
void MainWindow::on_pushButton_clicked()
{
    QString ID_EQUIPEMENT = ui->lineEdit_6->text();
    QString NOM = ui->lineEdit->text();
    QString TYPE = ui->lineEdit_2->text();
    QString ETAT = ui->lineEdit_3->text();
    QString DATE_ACQUISITION = ui->dateEdit->date().toString();
    QString EMPLACEMENT = ui->lineEdit_4->text();
    QString PRIX = ui->lineEdit_5->text();

    QDate DATE_ACQUISITIONN = ui->dateEdit->date();
    QDate dateActuelle = QDate::currentDate();

    GestionEquipements E(ID_EQUIPEMENT, NOM, TYPE, ETAT, DATE_ACQUISITION, EMPLACEMENT, PRIX);
    if (ID_EQUIPEMENT.isEmpty() || NOM.isEmpty() || TYPE.isEmpty() || ETAT.isEmpty() || EMPLACEMENT.isEmpty() || PRIX.isEmpty() || DATE_ACQUISITION.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs");
    } else {
        if (PRIX.toInt() <= 0 || PRIX.toInt() >= 1000000) {
            QMessageBox::warning(this, "Erreur", "Veuillez introduire un Prix >= 0 et <=1000000 ");
        } else if (DATE_ACQUISITIONN < dateActuelle) {
            QMessageBox::warning(this, "Erreur", "Veuillez saisir une date valide");
        } else {
            E.Ajouter();
            ui->lineEdit_6->clear();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
            ui->tableView->setModel(E.afficher());
        }
    }
}

// Update equipment
void MainWindow::on_pushButton_2_clicked()
{
    QString ID_EQUIPEMENT = ui->lineEdit_6->text();
    QString NOM = ui->lineEdit->text();
    QString TYPE = ui->lineEdit_2->text();
    QString ETAT = ui->lineEdit_3->text();
    QString DATE_ACQUISITION = ui->dateEdit->date().toString();
    QString EMPLACEMENT = ui->lineEdit_4->text();
    QString PRIX = ui->lineEdit_5->text();
    GestionEquipements E(ID_EQUIPEMENT, NOM, TYPE, ETAT, DATE_ACQUISITION, EMPLACEMENT, PRIX);
    if (ID_EQUIPEMENT.isEmpty() || NOM.isEmpty() || TYPE.isEmpty() || ETAT.isEmpty() || EMPLACEMENT.isEmpty() || PRIX.isEmpty() || DATE_ACQUISITION.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
    } else {
        if (PRIX.toInt() <= 0 || PRIX.toInt() >= 1000000) {
            QMessageBox::warning(this, "Erreur", "Veuillez introduire un Prix >= 0 et <=1000000 ");
        } else {
            E.modifier();
            ui->lineEdit_6->clear();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
            ui->tableView->setModel(E.afficher());
        }
    }
}

// Delete equipment
void MainWindow::on_pushButton_3_clicked()
{
    QString ID = ui->lineEdit_6->text();
    GestionEquipements E;
    E.supprimer(ID);
    ui->lineEdit_6->clear();
    ui->tableView->setModel(E.afficher());
}

// Sort equipment
void MainWindow::on_pushButton_4_clicked()
{
    GestionEquipements E;
    ui->tableView->setModel(E.tri());
}

// Search equipment
void MainWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
    GestionEquipements E;
    ui->tableView->setModel(E.rechercher(arg1));
}

// Show pie chart
void MainWindow::on_pushButton_5_clicked()
{
    QSqlQuery query;
    query.exec("SELECT Etat, COUNT(*) FROM EQUIPEMENTS GROUP BY Etat");

    QPieSeries *series = new QPieSeries();
    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        QPieSlice *slice = new QPieSlice(type, count);
        series->append(slice);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistics based on EQUIPEMENTS Etat");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->tableView_2);
    chartView->resize(ui->tableView_2->size());
    chartView->show();
}

// Generate PDF
void MainWindow::on_pushButton_6_clicked()
{
    QPdfWriter pdf("c:/Users/ayadi/Desktop/GestionEquipements/equipement.pdf");
    QPainter painter(&pdf);
    int i = 4100;

    QColor dateColor(0x4a5bcf);
    painter.setPen(dateColor);
    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();
    painter.drawText(7700, 250, cd.toString("Ariana, El Ghazela"));
    painter.drawText(8100, 500, cd.toString("dd/MM/yyyy"));

    QColor titleColor(0x341763);
    painter.setPen(titleColor);
    painter.setFont(QFont("Montserrat SemiBold", 25));
    painter.drawText(3000, 2700, "Liste des equipements");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    painter.drawRect(100, 3300, 9400, 500);

    painter.setFont(QFont("Montserrat SemiBold", 10));
    painter.drawText(300, 3600, "ID_equipements");
    painter.drawText(2000, 3600, "nom");
    painter.drawText(3000, 3600, "etat");
    painter.drawText(4000, 3600, "type");
    painter.drawText(5000, 3600, "emplacement");
    painter.drawText(6000, 3600, "Date_acquisition");
    painter.drawText(8000, 3600, "prix");

    painter.setFont(QFont("Montserrat", 10));
    painter.drawRect(100, 3300, 9400, 9000);

    QSqlQuery query;
    query.prepare("select * from EQUIPEMENTS");
    query.exec();
    int y = 4300;
    while (query.next()) {
        painter.drawLine(100, y, 9490, y);
        y += 500;
        painter.drawText(300, i, query.value(0).toString());
        painter.drawText(2000, i, query.value(1).toString());
        painter.drawText(3000, i, query.value(2).toString());
        painter.drawText(4000, i, query.value(3).toString());
        painter.drawText(5000, i, query.value(4).toString());
        painter.drawText(6000, i, query.value(5).toString());
        painter.drawText(8000, i, query.value(6).toString());
        i += 500;
    }

    int response = QMessageBox::question(this, "Générer PDF", "PDF Enregistré.\nVous voulez l'afficher ?", QMessageBox::Yes | QMessageBox::No);
    if (response == QMessageBox::Yes) {
        QDesktopServices::openUrl(QUrl::fromLocalFile("c:/Users/ayadi/Desktop/GestionEquipements/equipement.pdf"));
        painter.end();
    } else {
        painter;}}
