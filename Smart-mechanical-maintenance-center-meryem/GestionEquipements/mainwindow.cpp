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


//client
#include "clientc.h"
#include <QMessageBox>
#include <QDate>
#include "clientc.h"
#include <QTableView>
#include <QPrinter>
#include <QPainter>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include<QSslSocket>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QNetworkReply>
#include <QNetworkAccessManager>


#include "voiture.h"
#include <QMessageBox>
#include <QtCharts>
#include <QSqlQuery>


#include "service.h"
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QDebug>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QDialog>
#include <QVBoxLayout>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include <QDialog>
#include <QMap>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QPieSeries>

using namespace  QtCharts;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    clientc clientInstance;
    QSqlQueryModel* model = clientInstance.afficher();

        // Assuming you have a QTableView in your UI with the object name "tableView"
        ui->tableView_3->setModel(model);


         GestionEquipements E;
        ui->tableView->setModel(E.afficher());


        //voiture
        voiture v;
        ui->tableView_4->setModel(v.afficher());

        int ret=A.connect_arduino(); // lancer la connexion à arduino
           switch(ret){
           case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
               break;
           case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
              break;
           case(-1):qDebug() << "arduino is not available";
           }
            QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(arduinoo()));//automatique read mel arduino

            //service
            ui->tableView->setModel(Etmp.afficher());
            ui->tableView->setSortingEnabled(true);
            ui->tableView->horizontalHeader()->setStyleSheet(
                "QHeaderView::section {"
                "    background-color: #2c3e50;"  // Dark background color (adjust as needed)
                "    color: white;"               // Text color
                "    padding: 4px;"               // Optional: space around text
                "    font-weight: bold;"          // Optional: make text bold
                "}"
            );
            this->setStyleSheet(
                "QMainWindow {"
                "    background-color: #2c3e50;"  // Dark background color (adjust as needed)
                "    color: white;"               // Optional: makes text or icons white for contrast
                "}"
            );
            setupConsulterListe();


            ui->lineEdit_id_2->setValidator(new QIntValidator(1, 1000000, this));
            QDoubleValidator *doubleValidator = new QDoubleValidator(0, 1000000, 2, this);
            doubleValidator->setNotation(QDoubleValidator::StandardNotation);
            ui->lineEdit_prix->setValidator(doubleValidator);




            ui->gestion_voiture->hide();
            ui->gestion_equipement->hide();
            ui->gestion_service->hide();
            ui->gestion_client->hide();
            ui->menu->show();

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






//*****************client*****************


void MainWindow::on_pushButton_ajouter_clicked()
{
    {
        // Récupération des valeurs saisies dans les champs de l'interface
        QString client_id = ui->lineEdit_id->text();
        QString nom = ui->lineEdit_nom->text();
        QString email = ui->lineEdit_email->text();
        QDate dateNaiss = ui->dateEdit_2->date();
        QString tel = ui->lineEdit_tel->text();
        QString sexe = ui->lineEdit_sexe->text().toUpper(); // Convertit en majuscule pour assurer la cohérence

        // Création d'un objet client avec les données saisies
        clientc newClient(client_id, nom, email,  tel, sexe,dateNaiss);

        // Validation des données saisies
        if (client_id.isEmpty() || nom.isEmpty() || email.isEmpty() || tel.isEmpty() || sexe.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
            return;
        }
        if (!newClient.isValidClientId(client_id)) {
            QMessageBox::critical(this, "Erreur", "L'ID du client doit être un numéro de 8 chiffres.");
            return;
        }
        if (!newClient.isValidName(nom)) {
            QMessageBox::critical(this, "Erreur", "Le nom doit contenir uniquement des lettres.");
            return;
        }
        if (!newClient.validateEmail(email)) {
            QMessageBox::critical(this, "Erreur", "Adresse email invalide.");
            return;
        }
        if (!newClient.isValidPhoneNumber(tel)) {
            QMessageBox::critical(this, "Erreur", "Le numéro de téléphone doit être composé de chiffres uniquement et avoir une longueur valide.");
            return;
        }
        if (dateNaiss >= QDate::currentDate()) {
            QMessageBox::critical(this, "Erreur", "Veuillez entrer une date de naissance valide.");
            return;
        }
        if (sexe != "F" && sexe != "M") {
            QMessageBox::critical(this, "Erreur", "Le sexe doit être 'F' pour féminin ou 'M' pour masculin.");
            return;
        }

        // Appel de la méthode pour ajouter le client dans la base de données
        if (newClient.ajouter_client()) {
            QMessageBox::information(this, "Succès", "Client ajouté avec succès.");

            // Efface les champs après l'ajout
            ui->lineEdit_id->clear();
            ui->lineEdit_nom->clear();
            ui->lineEdit_email->clear();
            ui->dateEdit->setDate(QDate::currentDate());
            ui->lineEdit_tel->clear();
            ui->lineEdit_sexe->clear();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du client.");
        }
    }
}

void MainWindow::on_pushButton_update_clicked()
{
    // Collect data from UI elements
    QString clientId = ui->lineEdit_id->text();
    QString name = ui->lineEdit_nom->text();
    QString email = ui->lineEdit_email->text();
    QString tel = ui->lineEdit_tel->text();
    QString sexe = ui->lineEdit_sexe->text();

    // Collect the date from the QDateEdit widget
    QDate daten = ui->dateEdit_2->date();  // Get the QDate from the QDateEdit

    // Check if the clientId field is not empty
    if (clientId.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "L'ID du client ne peut pas être vide.");
        return;
    }

    // Create an instance of the clientc class and set the collected data
    clientc clientToUpdate(clientId, name, email, tel, sexe, daten);

    // Call the modifier_client method to update the client in the database
    if (clientToUpdate.modifier_client()) {
        QMessageBox::information(this, "Succès", "Les informations du client ont été mises à jour avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la mise à jour des informations.");
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    // Get the client ID from the QLineEdit (assumes ui->lineEdit_id_delete is the QLineEdit for the client ID)
    QString clientId = ui->lineEdit_id_delete->text();

    // Call the supprimer_client method to attempt deleting the client
    clientc clientInstance;
    bool success = clientInstance.supprimer_client(clientId);

    // Inform the user whether the operation succeeded or failed
    if (success) {
        QMessageBox::information(nullptr, "Succès", "Client supprimé avec succès.");
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Échec de la suppression du client.");
    }
}

void MainWindow::on_pushButton_afficher_clicked()
{

    clientc clientInstance;
    QSqlQueryModel* model = clientInstance.afficher();

        // Assuming you have a QTableView in your UI with the object name "tableView"
        ui->tableView_3->setModel(model);

}

void MainWindow::on_pushButton_extract_2_clicked()
{
    clientc c;
    QSqlQueryModel *model = c.affichage_trieID_croissant();

        // Check if the model is nullptr (if query failed)
        if (model == nullptr) {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'affichage des clients triés.");
            return;
        }

        // Set the model to the table view (assuming ui->tableView exists)
        ui->tableView_3->setModel(model);
}

void MainWindow::on_pushButton_extract_clicked()
{
    exportClientListToPDF();  // Call export function

}
void MainWindow::exportClientListToPDF()
{
    // Demander à l'utilisateur le nom du fichier pour sauvegarder le PDF
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        return; // L'utilisateur a annulé la boîte de dialogue
    }

    // Créer un QSqlQueryModel pour contenir les données des clients
    QSqlQueryModel* model = new QSqlQueryModel();

    // Créer une requête pour récupérer les données des clients
    QSqlQuery query;
    query.prepare("SELECT CLIENT_ID, NAME, EMAIL, TEL, SEXE, DATEN FROM CLIENT");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        delete model;  // Si la requête a échoué, supprimer le modèle
        QMessageBox::warning(this, "Error", "Failed to retrieve client data.");
        return;
    }

    if (model == nullptr || model->rowCount() == 0) {
        QMessageBox::warning(this, "No Data", "Aucun client à exporter.");
        return;
    }

    // Préparer l'imprimante PDF et les paramètres
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Portrait); // Vous pouvez changer en Paysage si nécessaire
    printer.setOutputFileName(fileName);

    // Configurer le QPainter pour dessiner sur le PDF
    QPainter painter(&printer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Error", "Unable to start the painter.");
        return;
    }

    // Définir la police et la couleur pour le dessin
    painter.setFont(QFont("Arial", 10));
    QColor headerColor(49, 164, 180);  // Couleur pour les en-têtes des colonnes
    QColor cellColor(230, 244, 241);   // Couleur pour les cellules du tableau

    // Positionnement du tableau et tailles
    int x = 10;
    int y = 40;
    int rowHeight = 20;
    int colWidth = 90;

    // Dessiner le titre du document
    painter.setFont(QFont("Arial", 15, QFont::Bold));
    painter.setPen(QPen(headerColor));
    painter.drawText(x, y, "Client List");
    y += 30;

    // Dessiner les en-têtes des colonnes
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.setBrush(QBrush(headerColor));
    painter.setPen(QPen(Qt::black));

    // Dessiner les en-têtes pour chaque colonne
    painter.drawRect(x, y, colWidth, rowHeight);
    painter.drawText(x + 5, y + 15, "Client ID");

    painter.drawRect(x + colWidth, y, colWidth, rowHeight);
    painter.drawText(x + colWidth + 5, y + 15, "Name");

    painter.drawRect(x + 2 * colWidth, y, colWidth, rowHeight);
    painter.drawText(x + 2 * colWidth + 5, y + 15, "Email");

    painter.drawRect(x + 3 * colWidth, y, colWidth, rowHeight);
    painter.drawText(x + 3 * colWidth + 5, y + 15, "Phone");

    painter.drawRect(x + 4 * colWidth, y, colWidth, rowHeight);
    painter.drawText(x + 4 * colWidth + 5, y + 15, "Sexe");

    painter.drawRect(x + 5 * colWidth, y, colWidth, rowHeight);
    painter.drawText(x + 5 * colWidth + 5, y + 15, "Birth Date");

    y += rowHeight;

    // Dessiner les lignes du tableau avec les données
    painter.setFont(QFont("Arial", 7));
    painter.setBrush(QBrush(cellColor));

    for (int row = 0; row < model->rowCount(); ++row) {
        // Dessiner chaque cellule de la ligne
        for (int col = 0; col < model->columnCount(); ++col) {
            painter.setPen(QPen(Qt::black));
            painter.drawRect(x + col * colWidth, y, colWidth, rowHeight);
            QString data = model->data(model->index(row, col)).toString();

            // Formater la date de naissance
            if (col == 5) {  // Supposons que DATEN soit la 6e colonne (index 5)
                QDate birthDate = QDate::fromString(data, "yyyy-MM-dd");
                if (birthDate.isValid()) {
                    data = birthDate.toString("dd/MM/yyyy");  // Formater comme jour/mois/année
                }
            }

            painter.drawText(x + col * colWidth + 5, y + 15, data);
        }
        y += rowHeight;  // Passer à la ligne suivante
    }

    // Terminer le processus de peinture
    painter.end();

    // Nettoyage
    delete model;

    QMessageBox::information(this, "Export Successful", "Le fichier PDF a été exporté avec succès.");
}

void MainWindow::on_pushButton_search_2_clicked()
{
    clientc clientc;
        QSqlQueryModel* model = clientc.afficher();
        clientc.genererStatistiquesSexe(model);
}

void MainWindow::on_pushButton_search_clicked()
{
    // Retrieve the client ID from the search line edit
    QString clientId = ui->lineEdit_search->text().trimmed();

    // Check if the input is empty
    if (clientId.isEmpty()) {
        QMessageBox::information(this, "Information", "Veuillez entrer un ID de client.");
        return;
    }

    // Use the afficher_id function to get the client data for the specified ID
   clientc c;
    QSqlQueryModel *model = c.afficher_id(clientId);

    // If the model is nullptr, the search failed or no data was found
    if (model == nullptr || model->rowCount() == 0) {
        QMessageBox::information(this, "Information", "Aucun client trouvé avec cet ID.");
        return;
    }

    // Display the result in a QTableView (assuming you have a QTableView in the UI)
    ui->tableView_3->setModel(model);
}

void MainWindow::on_SMS_clicked()
{
    QString destinataire = "+21629347440";
    QString message = ui->smscontenu->toPlainText();

    envoyerSMS(destinataire, message);

}
void MainWindow::envoyerSMS(const QString &destinataire, const QString &message)
{
    // SID et auth token de Twilio
    QString sid = "ACe0cb8d2e606dec4ec8b9db103ab149fc";
    QString authToken = "2308698b07c83b6e2237f937ce269cc6";

    // Construire l'URL de l'API Twilio
    QString url = "https://api.twilio.com/2010-04-01/Accounts/" + sid + "/Messages.json";

    // Créer le gestionnaire de réseau
    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager(this);
   // networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible); // Définir l'accessibilité du réseau
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    // Construire les données de la requête
    QByteArray postData;
    postData.append("To=" + destinataire.toUtf8());
    postData.append("&From=+13214201568");
    postData.append("&Body=" + message.toUtf8());

    // Créer la requête HTTP
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + QByteArray(QString("%1:%2").arg(sid).arg(authToken).toUtf8()).toBase64());


    // Envoyer la requête
    networkAccessManager->post(request, postData);

    // Afficher un message de succès
    QMessageBox::information(this, "Envoi SMS", "Le SMS a été envoyé avec succès.");
}

void MainWindow::on_pushButton_search_4_clicked()
{
    QString serveur = "smtp.gmail.com";
           int port = 587; // Port pour SMTP avec STARTTLS

           // Informations de l'expéditeur et du destinataire
           QString expediteur = "hedichaibi76@gmail.com";
           QString destinataire = ui->lineEdit_search_2->text();

           QString subject = "Cher notre fidele client";

           // Détails du message
            QString corps = ui->plainTextEdit->toPlainText();

           // Connexion au serveur SMTP
           QSslSocket socket;
           socket.connectToHost(serveur, port);
           if (!socket.waitForConnected()) {
               qDebug() << "Échec de connexion au serveur SMTP:" << socket.errorString();
               return;
           }

           // Attente de la réponse du serveur
           if (!socket.waitForReadyRead()) {
               qDebug() << "Délai d'attente de réponse du serveur SMTP:" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse initiale du serveur

           // Envoi de la commande EHLO
           socket.write("EHLO localhost\r\n");
           if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
               qDebug() << "Délai d'attente de réponse du serveur SMTP (EHLO):" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse après EHLO

           // Envoi de la commande STARTTLS
           socket.write("STARTTLS\r\n");
           if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
               qDebug() << "Délai d'attente de réponse du serveur SMTP (STARTTLS):" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse après STARTTLS

           // Démarrer le chiffrement
           socket.startClientEncryption();
           if (!socket.waitForEncrypted()) {
               qDebug() << "Échec du chiffrement:" << socket.errorString();
               return;
           }

           // Envoi de la commande AUTH LOGIN
           socket.write("AUTH LOGIN\r\n");
           if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
               qDebug() << "Délai d'attente de réponse du serveur SMTP (AUTH LOGIN):" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse après AUTH LOGIN

           // Envoi du nom d'utilisateur encodé en Base64
           socket.write(QByteArray().append(expediteur.toUtf8()).toBase64() + "\r\n");
           if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
               qDebug() << "Délai d'attente de réponse du serveur SMTP (Nom d'utilisateur):" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du nom d'utilisateur

           // Envoi du mot de passe encodé en Base64
           socket.write(QByteArray().append("lzmt nqzv zavf fmic").toBase64() + "\r\n");
           if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
               qDebug() << "Échec de l'authentification SMTP (Mot de passe):" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du mot de passe

           // Envoi de la commande MAIL FROM
           socket.write("MAIL FROM:<" + expediteur.toUtf8() + ">\r\n");
           if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
               qDebug() << "Délai d'attente de réponse du serveur SMTP (MAIL FROM):" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse après MAIL FROM

           // Envoi de la commande RCPT TO
           socket.write("RCPT TO:<" + destinataire.toUtf8() + ">\r\n");
           if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
               qDebug() << "Délai d'attente de réponse du serveur SMTP (RCPT TO):" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse après RCPT TO

           // Envoi de la commande DATA
           socket.write("DATA\r\n");
           if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
               qDebug() << "Délai d'attente de réponse du serveur SMTP (DATA):" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse après DATA

           // Envoi des en-têtes et du corps du message
           socket.write("From: " + expediteur.toUtf8() + "\r\n");
           socket.write("To: " + destinataire.toUtf8() + "\r\n");
           socket.write("Subject: " + subject.toUtf8() + "\r\n");
           socket.write("\r\n");
           socket.write(corps.toUtf8() + "\r\n");
           socket.write(".\r\n");
           if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
               qDebug() << "Échec d'envoi des données du mail:" << socket.errorString();
               return;
           }
           qDebug() << socket.readAll(); // Afficher la réponse après l'envoi des données du mail

           // Envoi de la commande QUIT
           socket.write("QUIT\r\n");
           if (!socket.waitForBytesWritten()) {
               qDebug() << "Échec d'envoi de la commande QUIT:" << socket.errorString();
               return;
           }

           // Fermeture de la connexion
           socket.close();
           QMessageBox::information(this, "Succès", "L'email a été envoyé avec succès à " + destinataire);




}





//*****************voiture****************
void MainWindow::alerte()
{
     QDate currentDate = QDate::currentDate();
     QSqlQuery query;
        query.prepare("SELECT matricule, date_sortie FROM voiture WHERE date_sortie BETWEEN :currentDate AND :Date");
        query.bindValue(":currentDate", currentDate);
        query.bindValue(":Date", currentDate.addDays(3));

        if (!query.exec()) {
            qDebug() << "Error executing query:";
            return;
        }
        QString warningMessage;
           while (query.next()) {
               QString matricule = query.value("matricule").toString();
               QDate dateSortie = query.value("date_sortie").toDate();
               warningMessage += QString("Car with matricule '%1' has a sortie date on %2\n")
                                     .arg(matricule, dateSortie.toString());
           }

           // Display warning if there are cars meeting the condition
           if (!warningMessage.isEmpty()) {
               QMessageBox::warning(nullptr, "Upcoming Date Sortie Warnings", warningMessage);
           } else {
               QMessageBox::information(nullptr, "No Warnings", "No cars have a sortie date within 3 days.");
           }

}


void MainWindow::arduinoo() {
    //eya
        QString data = A.read_from_arduino();
        if (!data.isEmpty()) {
            bool isValidCode = verifyCode(data);
            if (isValidCode) {
                qDebug() << "Code valide : " << data;
                //aymen
                A.write_to_arduino("0");
                 QMessageBox::information(this, "reussie ", "matricule : "+data+" existe dans la  base");

            } else {

                qDebug() << "Code invalide : " << data;
                QMessageBox::warning(this, "reussie ", "matricule : "+data+" n'existe pas dans la  base");
            }
        }

}
//eya
bool MainWindow::verifyCode(QString data)
{
    QSqlQuery query;

    qDebug() << "Preparing query to verify code:" << data; // Debug input data
    query.prepare("SELECT * FROM VOITURE WHERE matricule = :code");
    query.bindValue(":code", data);

    if (query.exec()) {
        qDebug() << "Query executed successfully.";
        if (query.next()) {
            qDebug() << "Code found in database:" << data;
            return true; // Code exists in the database
        } else {
            qDebug() << "Code not found in database:" << data;
        }
    } else {
        qDebug() << "Query execution error:" ;
    }

    return false; // Code not found or query execution failed
}

void MainWindow::on_ajouterButton_clicked()
{

    QString MATRICULE=ui->matriculeInput->text();
    QString MARQUE=ui->marqueInput->text();
    QString MODELE=ui->modeleInput->text();
    QString KILOMETRAGE=ui->kilometrageInput->text();
    QString DATE_ARRIVAGE=ui->dateArrivageInput->date().toString();
    QDate DATE_SORTIE=ui->dateSortieInput->date();
    QString TYPE_DE_PANNE=ui->comboBox->currentText();
    QRegularExpression matriculeRegex(R"(^\d{4} [A-Z]{3} \d{3}$)");

    voiture v(MATRICULE,MARQUE,MODELE,KILOMETRAGE,DATE_ARRIVAGE,DATE_SORTIE,TYPE_DE_PANNE);
    if(MATRICULE =="" || MARQUE =="" || MODELE =="" || KILOMETRAGE =="" || DATE_ARRIVAGE =="" || TYPE_DE_PANNE =="" )
    {
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr("veuillez remplir les champs\n"), QMessageBox::Cancel);
    }
    else{
        if(TYPE_DE_PANNE!="mecanique" && TYPE_DE_PANNE!="electrique" && TYPE_DE_PANNE!="vidange" && TYPE_DE_PANNE!="autre" ){
            QMessageBox::critical(nullptr, QObject::tr("erreur"),
                        QObject::tr("le type doit etre mecanique ou electrique ou vidange ou autre"), QMessageBox::Cancel);
        }
        else{
            if(!matriculeRegex.match(MATRICULE).hasMatch())
            {
                QMessageBox::critical(nullptr, QObject::tr("erreur"),
                            QObject::tr("la matricule doit etre comme ca xxxx TUN xxx"), QMessageBox::Cancel);
            }
            else{
                if(KILOMETRAGE.contains(QRegExp("[^0-9]")))
                {
                    QMessageBox::critical(nullptr, QObject::tr("erreur"),
                                QObject::tr("le kilometrage doit contient que de nombre"), QMessageBox::Cancel);
                }
                else{
        v.ajouter();
        ui->tableView_4->setModel(v.afficher());
                }
            }
        }
    }
}

void MainWindow::on_supprimerButton_clicked()
{
    QString MATRICULE=ui->matriculeInput->text();
    voiture v;
    v.supprimer(MATRICULE);
    ui->tableView_4->setModel(v.afficher());
}

void MainWindow::on_modifierButton_clicked()
{
    QString MATRICULE=ui->matriculeInput->text();
    QString MARQUE=ui->marqueInput->text();
    QString MODELE=ui->modeleInput->text();
    QString KILOMETRAGE=ui->kilometrageInput->text();
    QString DATE_ARRIVAGE=ui->dateArrivageInput->date().toString();
    QDate DATE_SORTIE=ui->dateSortieInput->date();
    QString TYPE_DE_PANNE=ui->comboBox->currentText();
    voiture v(MATRICULE,MARQUE,MODELE,KILOMETRAGE,DATE_ARRIVAGE,DATE_SORTIE,TYPE_DE_PANNE);
    v.modifier();
    ui->tableView_4->setModel(v.afficher());
}

void MainWindow::on_pushButton_7_clicked()
{
    voiture v;
   ui->tableView_4->setModel(v.tri());
}

void MainWindow::on_matriculeInput_3_textChanged(const QString &arg1)
{
    voiture v;
    ui->tableView_4->setModel(v.rechercher(arg1));
}

void MainWindow::on_pushButton_8_clicked()
{

    QSqlQuery query;
    query.exec("SELECT TYPE_DE_PANNE, COUNT(*) FROM VOITURE GROUP BY TYPE_DE_PANNE");

    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        QtCharts::QPieSlice *slice = new QtCharts::QPieSlice(type, count);
        series->append(slice);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistics based on VOITURE type_de_panne");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->tableView_5);
    chartView->resize(ui->tableView_5->size());
    chartView->show();
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->gestion_voiture->hide();
    ui->calendrier->show();
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->calendrier->hide();
    ui->gestion_voiture->show();
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QSqlQuery query;
    query.prepare("SELECT matricule FROM voiture WHERE date_sortie = :date");
       query.bindValue(":date", date);

       if (!query.exec()) {
           QMessageBox::critical(this, "Query Error", "error");
           return;
       }
       ui->listWidget->clear();

          // Populate the list with results
          while (query.next()) {
              ui->listWidget->addItem(query.value("matricule").toString());
          }
}

void MainWindow::on_pushButton_10_clicked()
{
    QPdfWriter pdf("C:/Users/benhamed eya/Documents/pi/voiture.pdf");

           QPainter painter(&pdf);
           int i = 4100;

                  QColor dateColor(0x4a5bcf);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(7700,250,cd.toString("Ariana, El Ghazela"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,2700,"Liste des voiture");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));
                              painter.drawText(300,3600,"matricule");
                              painter.drawText(1500,3600,"marque");
                              painter.drawText(2500,3600,"modele");
                              painter.drawText(3500,3600,"kilometrage");
                              painter.drawText(4500,3600,"date_arrivage");
                              painter.drawText(6500,3600,"date_sortie");
                              painter.drawText(8500,3600,"type_de_panne");

                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from voiture");
                  query.exec();
                  int y=4300;
                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);
                      y+=500;
                      painter.drawText(300,i,query.value(0).toString());
                          painter.drawText(1500,i,query.value(1).toString());
                          painter.drawText(2500,i,query.value(2).toString());
                          painter.drawText(3500,i,query.value(3).toString());
                          painter.drawText(4500,i,query.value(4).toString());
                          painter.drawText(6500,i,query.value(5).toString());
                          painter.drawText(8500,i,query.value(6).toString());
                     i = i + 500;
                  }

                  int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré.\nVous voulez l'affichez ?", QMessageBox::Yes |  QMessageBox::No);
                  if (reponse == QMessageBox::Yes)
                  {
                      QDesktopServices::openUrl( QUrl::fromLocalFile("C:/Users/benhamed eya/Documents/pi/voiture.pdf"));
                      painter.end();
                  }
                  else
                  {
                      painter.end();
                  }
}


//service

void MainWindow::on_pushButton_ajouter_2_clicked()
{
    int IDM = ui->lineEdit_id_2->text().toInt();
    QString NAME = ui->lineEdit_nom_2->text();
    QString DESCRIPTION = ui->lineEdit_description->text();
    float PRICE = ui->lineEdit_prix->text().toFloat();
    QString DURATION = ui->lineEdit_duree->text();
    QString EQUIPEMENT = ui->lineEdit_equipement->text();
    QString EMPLOYEE = ui->lineEdit_employee->text();

    if(IDM <= 0 || NAME.isEmpty() || PRICE < 0.0f || DURATION.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    Service S(IDM, NAME, DESCRIPTION, DURATION, EMPLOYEE, EQUIPEMENT, PRICE);

    bool test = S.ajouter(); // Appel de la fonction d'ajout

    if(test)
    {
        ui->tableView_6->setModel(Etmp.afficher()); // Actualiser la vue de la table
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\nClick cancel to exit."),
                                 QMessageBox::Cancel);

        // Enregistrer l'ajout dans l'historique
        addToHistory("Ajout du service", QString::number(IDM));
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué\nClick cancel to exit."),
                              QMessageBox::Cancel);
    }
}
void MainWindow::addToHistory(const QString &action, const QString &serviceName)
{
    // Chemin du fichier historique
    QString filePath = ":/images/image/historique_services.txt";
    QFile file(filePath);

    // Ouvrir le fichier en mode ajout
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique.";
        return;
    }

    // Créer un flux texte pour écrire dans le fichier
    QTextStream out(&file);

    // Obtenir la date et l'heure actuelles
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Écrire l'action dans le fichier historique avec la date et l'heure
    out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " - " << action;
    if (!serviceName.isEmpty()) {
        out << " pour le service : " << serviceName;
    }
    out << "\n";

    // Fermer le fichier
    file.close();
}

void MainWindow::saveHistoryToFile()
{
    // Chemin du fichier historique
    QString filePath = ":/images/image/historique_services.txt";// :/images/image/pexels-dmitry-demidov-515774-678.jpg
    QFile file(filePath);

    // Ouvrir le fichier en mode lecture
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique pour lecture.";
        return;
    }

    // Lire le contenu du fichier historique
    QTextStream in(&file);
    QString content = in.readAll();

    // Afficher le contenu de l'historique dans la console ou l'UI
    qDebug() << content;

    // Fermer le fichier
    file.close();
}
void MainWindow::setupConsulterListe()
{
    // Create and set the SQL model
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("SERVICE");  // Replace "SERVICE" with your actual table name
    model->select();  // Load data

    // Enable sorting for the model
    model->setSort(0, Qt::AscendingOrder);  // Sort by the first column by default

    // Set the model to the tableView
    ui->tableView_6->setModel(model);
    ui->tableView_6->setSortingEnabled(true);  // Enable sorting in the UI
}

void MainWindow::setupRevenueChart() {

    QMap<QString, double> revenueData = Etmp.getRevenueByService();

    // Effacer tous les widgets dans le layout avant d'ajouter le nouveau graphique
    QLayoutItem* item;
    while ((item = ui->horizontalLayout_charts->takeAt(0)) != nullptr) {
        delete item->widget();  // Supprimer le widget du layout
        delete item;  // Supprimer l'élément du layout
    }

    // Vérifier si les données sont vides
    if (revenueData.isEmpty()) {
        // Si aucune donnée, afficher un message seulement une fois
        QMessageBox::information(this, "Aucune donnée", "Aucune donnée de revenu disponible pour le graphique.");
        return;  // Retourner sans essayer d'afficher un graphique
    }

    // Créer un QBarSet pour les valeurs des revenus
    QtCharts::QBarSet *revenueSet = new QtCharts::QBarSet("Revenu");

    // Remplir QBarSet avec les données et les noms des services
    QStringList categories;
    for (auto it = revenueData.constBegin(); it != revenueData.constEnd(); ++it) {
        categories << it.key();  // Nom du service
        *revenueSet << it.value();  // Revenu
    }

    // Créer une série QBarSeries et y ajouter le QBarSet
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(revenueSet);

    // Créer le graphique et y ajouter la série
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Revenu par service");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Configurer les axes X et Y
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Revenu ($)");
    axisY->setLabelFormat("%.2f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Afficher le graphique dans un QChartView
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Ajouter le nouveau chartView au layout
    ui->horizontalLayout_charts->addWidget(chartView);
}
void MainWindow::on_pushButton_update_2_clicked()
{
    int IDM = ui->lineEdit_id_2->text().toInt();
    QString NAME = ui->lineEdit_nom_2->text();
    QString DESCRIPTION = ui->lineEdit_description->text();
    float PRICE = ui->lineEdit_prix->text().toFloat();
    QString DURATION = ui->lineEdit_duree->text();
    QString EQUIPEMENT = ui->lineEdit_equipement->text();
    QString EMPLOYEE = ui->lineEdit_employee->text();

    if(IDM <= 0 || NAME.isEmpty() || PRICE < 0.0f || DURATION.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    Service S(IDM, NAME, DESCRIPTION, DURATION, EMPLOYEE, EQUIPEMENT, PRICE);

    bool test = S.update(); // Appel de la fonction de mise à jour

    if (test)
    {
        ui->tableView_6->setModel(Etmp.afficher()); // Actualiser la vue de la table
        QMessageBox::information(nullptr, QObject::tr("Update Successful"),
                                 QObject::tr("The record has been updated successfully.\n"
                                             "Click OK to continue."),
                                 QMessageBox::Ok);

        // Enregistrer l'opération d'update dans l'historique
        addToHistory("Mise à jour du service", QString::number(IDM));
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Update Failed"),
                              QObject::tr("The update operation failed.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_search_6_clicked()
{
    QString searchTerm = ui->lineEdit_search_4->text();
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a search term.");
        return;
    }

    // Mettre à jour le modèle affiché dans la vue table
    ui->tableView_6->setModel(Etmp.search(searchTerm));

    // Appeler addToHistory depuis MainWindow
    addToHistory("Recherche du service", searchTerm);
}
void MainWindow::extractToPdf() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");
    if (filePath.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter(&printer);

    int rowHeight = 500;
    int xOffset = 50;
    int yOffset = 100;
    int pageWidth = printer.pageRect().width();

    // Assuming you want to print all columns in the table
    int numColumns = ui->tableView->model()->columnCount();
    int numRows = ui->tableView->model()->rowCount();
    int columnWidth = pageWidth / numColumns;

    // Print headers
    for (int col = 0; col < numColumns; ++col) {
        QString header = ui->tableView->model()->headerData(col, Qt::Horizontal).toString();
        painter.drawText(xOffset + col * columnWidth, yOffset, header);
    }

    // Print data rows
    yOffset += rowHeight;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numColumns; ++col) {
            QModelIndex index = ui->tableView->model()->index(row, col);
            QString data = index.data().toString();
            painter.drawText(xOffset + col * columnWidth, yOffset + row * rowHeight, data);
        }
    }

    painter.end();
    QMessageBox::information(this, "Export to PDF", "The list has been successfully exported as a PDF.");
}

void MainWindow::on_pushButton_refresh_clicked()
{
    ui->tableView_6->setModel(Etmp.afficher());

}

void MainWindow::on_pushButton_search_7_clicked()
{
    QString filePath = ":/images/image/historique_services.txt"; //C:/Users/hp/Downloads/Atelier_Connexion/Atelier_Connexion/historique_services.txt
    QFile file(filePath);

    // Vérifier si le fichier peut être ouvert en mode lecture
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier d'historique.");
        return;
    }

    // Lire tout le contenu du fichier historique
    QTextStream in(&file);
    QString historyContent = in.readAll();

    // Afficher le contenu dans une boîte de dialogue ou une zone de texte
    QMessageBox::information(this, "Historique des actions", historyContent);

    // Fermer le fichier
    file.close();
}

void MainWindow::on_pushButton_search_3_clicked()
{
    setupRevenueChart();  // Appel de la méthode setupRevenueChart pour afficher ou rafraîchir le graphique

}

void MainWindow::on_pushButton_extract_3_clicked()
{
    extractToPdf();
}

void MainWindow::on_pushButton_search_5_clicked()
{
    QString serveur = "smtp.gmail.com";
        int port = 587; // Port pour SMTP avec STARTTLS

        // Informations de l'expéditeur et du destinataire
        QString expediteur = "aymenraddedi96325@gmail.com";
        QString destinataire = ui->lineEdit_search_3->text();

        QString subject = "[URG] A propos le nouveau service associé";

        // Détails du message
         QString corps = ui->plainTextEdit_2->toPlainText();

        // Connexion au serveur SMTP
        QSslSocket socket;
        socket.connectToHost(serveur, port);
        if (!socket.waitForConnected()) {
            qDebug() << "Échec de connexion au serveur SMTP:" << socket.errorString();
            return;
        }

        // Attente de la réponse du serveur
        if (!socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP:" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse initiale du serveur

        // Envoi de la commande EHLO
        socket.write("EHLO localhost\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (EHLO):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après EHLO

        // Envoi de la commande STARTTLS
        socket.write("STARTTLS\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (STARTTLS):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après STARTTLS

        // Démarrer le chiffrement
        socket.startClientEncryption();
        if (!socket.waitForEncrypted()) {
            qDebug() << "Échec du chiffrement:" << socket.errorString();
            return;
        }

        // Envoi de la commande AUTH LOGIN
        socket.write("AUTH LOGIN\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (AUTH LOGIN):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après AUTH LOGIN

        // Envoi du nom d'utilisateur encodé en Base64
        socket.write(QByteArray().append(expediteur.toUtf8()).toBase64() + "\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (Nom d'utilisateur):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du nom d'utilisateur

        // Envoi du mot de passe encodé en Base64
        socket.write(QByteArray().append("flxe mzjz hirc ctdo").toBase64() + "\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Échec de l'authentification SMTP (Mot de passe):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du mot de passe

        // Envoi de la commande MAIL FROM
        socket.write("MAIL FROM:<" + expediteur.toUtf8() + ">\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (MAIL FROM):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après MAIL FROM

        // Envoi de la commande RCPT TO
        socket.write("RCPT TO:<" + destinataire.toUtf8() + ">\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (RCPT TO):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après RCPT TO

        // Envoi de la commande DATA
        socket.write("DATA\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (DATA):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après DATA

        // Envoi des en-têtes et du corps du message
        socket.write("From: " + expediteur.toUtf8() + "\r\n");
        socket.write("To: " + destinataire.toUtf8() + "\r\n");
        socket.write("Subject: " + subject.toUtf8() + "\r\n");
        socket.write("\r\n");
        socket.write(corps.toUtf8() + "\r\n");
        socket.write(".\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Échec d'envoi des données du mail:" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après l'envoi des données du mail

        // Envoi de la commande QUIT
        socket.write("QUIT\r\n");
        if (!socket.waitForBytesWritten()) {
            qDebug() << "Échec d'envoi de la commande QUIT:" << socket.errorString();
            return;
        }

        // Fermeture de la connexion
        socket.close();
        QMessageBox::information(this, "Succès", "L'email a été envoyé avec succès à " + destinataire);



}

void MainWindow::on_pushButton_supprimer_2_clicked()
{
    QString idText = ui->lineEdit_id_delete_2->text().trimmed(); // Correct the name to lineEdit_id_delete
    qDebug() << "Input from lineEdit_id_delete:" << idText; // Print the input for debugging

    // Check if the input is empty
    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter an ID to delete.");
        return; // Exit if the input is empty
    }

    bool ok; // Variable to check if conversion was successful
    int ID = idText.toInt(&ok); // Convert to integer

    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Invalid ID input.");
        return; // Exit if the input is invalid
    }

    qDebug() << "Attempting to delete IDM:" << ID;

    bool test = Etmp.supprimer(ID);

    if (test) {
        ui->tableView_6->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée\nClick cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectuée\nClick cancel to exit."), QMessageBox::Cancel);
    }
    addToHistory("Suppression du service", QString::number(ID));
}

void MainWindow::on_menu_client_clicked()
{
    ui->menu->hide();
    ui->gestion_service->hide();
    ui->gestion_voiture->hide();
    ui->gestion_equipement->hide();
    ui->gestion_client->show();

}

void MainWindow::on_menu_equipement_clicked()
{
    ui->menu->hide();
    ui->gestion_service->hide();
    ui->gestion_voiture->hide();
    ui->gestion_client->hide();
    ui->gestion_equipement->show();
}

void MainWindow::on_menu_service_clicked()
{
    ui->menu->hide();
    ui->gestion_equipement->hide();
    ui->gestion_voiture->hide();
    ui->gestion_client->hide();
    ui->gestion_service->show();
}

void MainWindow::on_menu_voiture_clicked()
{
    ui->menu->hide();
    ui->gestion_equipement->hide();
    ui->gestion_service->hide();
    ui->gestion_client->hide();
    ui->gestion_voiture->show();

}

void MainWindow::on_voiture_menu_clicked()
{
    ui->gestion_voiture->hide();
    ui->gestion_equipement->hide();
    ui->gestion_service->hide();
    ui->gestion_client->hide();
    ui->menu->show();
}

void MainWindow::on_client_menu_clicked()
{
    ui->gestion_voiture->hide();
    ui->gestion_equipement->hide();
    ui->gestion_service->hide();
    ui->gestion_client->hide();
    ui->menu->show();
}

void MainWindow::on_equipement_menu_clicked()
{
    ui->gestion_voiture->hide();
    ui->gestion_equipement->hide();
    ui->gestion_service->hide();
    ui->gestion_client->hide();
    ui->menu->show();
}

void MainWindow::on_service_menu_clicked()
{
    ui->gestion_voiture->hide();
    ui->gestion_equipement->hide();
    ui->gestion_service->hide();
    ui->gestion_client->hide();
    ui->menu->show();
}
