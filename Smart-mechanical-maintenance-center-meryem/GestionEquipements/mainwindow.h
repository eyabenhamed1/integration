#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arduino.h"
#include "service.h"
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>
#include <QSqlTableModel>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void alerte();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();



    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();


    //************client************
    void on_pushButton_ajouter_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_afficher_clicked();

    void on_pushButton_extract_2_clicked();

    void on_pushButton_extract_clicked();

    void exportClientListToPDF();


    void on_pushButton_search_2_clicked();

    void on_pushButton_search_clicked();

    void on_SMS_clicked();

    void envoyerSMS(const QString &destinataire, const QString &message);

    void on_pushButton_search_4_clicked();


    //*****************voiture***************
    void arduinoo() ;
    bool verifyCode(QString data);


    void on_ajouterButton_clicked();

    void on_supprimerButton_clicked();

    void on_modifierButton_clicked();

    void on_pushButton_7_clicked();

    void on_matriculeInput_3_textChanged(const QString &arg1);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_10_clicked();

    //***********service*******
    void on_pushButton_ajouter_2_clicked();
    void addToHistory(const QString &action, const QString &serviceName);
    void saveHistoryToFile();
    void setupConsulterListe();
    void setupRevenueChart() ;


    void on_pushButton_update_2_clicked();

    void on_pushButton_search_6_clicked();
    void extractToPdf() ;

    void on_pushButton_refresh_clicked();

    void on_pushButton_search_7_clicked();

    void on_pushButton_search_3_clicked();

    void on_pushButton_extract_3_clicked();

    void on_pushButton_search_5_clicked();

    void on_pushButton_supprimer_2_clicked();

    void on_menu_client_clicked();

    void on_menu_equipement_clicked();

    void on_menu_service_clicked();

    void on_menu_voiture_clicked();

    void on_voiture_menu_clicked();

    void on_client_menu_clicked();

    void on_equipement_menu_clicked();

    void on_service_menu_clicked();

private:
    Ui::MainWindow *ui;
    QTableView *tableView;
   Service Etmp;
        arduino A;
};
#endif // MAINWINDOW_H
