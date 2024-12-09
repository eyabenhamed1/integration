#include "clientc.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QTableView>
#include <QPrinter>
#include <QPainter>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
using namespace  QtCharts;
 // Constructeur par défaut
clientc::clientc() {
    CLIENT_ID = "";
    NAME = "";
    EMAIL = "";
    TEL = "";
    SEXE = "";
    DATEN = QDate::currentDate();
}

// Constructeur avec paramètres
clientc::clientc(QString CLIENT_ID, QString NAME, QString EMAIL, QString TEL, QString SEXE, QDate DATEN) {
    this->CLIENT_ID = CLIENT_ID;
    this->NAME = NAME;
    this->EMAIL = EMAIL;
    this->TEL = TEL;
    this->SEXE = SEXE;
    this->DATEN = DATEN;
}

bool clientc::ajouter_client()
{
    // Vérification des champs obligatoires
    if (CLIENT_ID.isEmpty() || NAME.isEmpty() || EMAIL.isEmpty() || TEL.isEmpty() || SEXE.isEmpty()) {
        QMessageBox::critical(nullptr, "Information", "Veuillez remplir tous les champs requis.");
        return false;
    }

    // Validation de l'ID du client
    if (!isValidClientId(CLIENT_ID)) {
        QMessageBox::critical(nullptr, "Information", "L'ID du client doit être un numéro de 8 chiffres.");
        return false;
    }

    // Vérification de l'existence de l'ID du client dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM CLIENT WHERE CLIENT_ID = :CLIENT_ID");
    checkQuery.bindValue(":CLIENT_ID", CLIENT_ID);
    if (!checkQuery.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la vérification de l'existence de l'ID dans la base de données.");
        return false;
    }
    checkQuery.next();
    int count = checkQuery.value(0).toInt();
    if (count > 0) {
        QMessageBox::critical(nullptr, "Information", "L'ID du client spécifié existe déjà dans la base de données.");
        return false;
    }

    // Validation du nom
    if (!isValidName(NAME)) {
        QMessageBox::critical(nullptr, "Information", "Le nom doit être composé uniquement de lettres.");
        return false;
    }

    // Validation du numéro de téléphone
    if (!isValidPhoneNumber(TEL)) {
        QMessageBox::critical(nullptr, "Information", "Le numéro de téléphone doit être composé de chiffres uniquement et avoir une longueur valide.");
        return false;
    }

    // Validation de l'email
    if (!validateEmail(EMAIL)) {
        QMessageBox::critical(nullptr, "Information", "Veuillez vérifier votre adresse e-mail.");
        return false;
    }

    // Validation de la date de naissance
    if (DATEN.isValid() && DATEN == QDate::currentDate()) {
        QMessageBox::critical(nullptr, "Information", "Veuillez vérifier la date de naissance.");
        return false;
    }

    // Insertion dans la base de données
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (CLIENT_ID, NAME, EMAIL, TEL, SEXE, DATEN) "
                  "VALUES (:CLIENT_ID, :NAME, :EMAIL, :TEL, :SEXE, :DATEN)");
    query.bindValue(":CLIENT_ID", CLIENT_ID);
    query.bindValue(":NAME", NAME);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":TEL", TEL);
    query.bindValue(":SEXE", SEXE);
    query.bindValue(":DATEN", DATEN);

    // Exécution de la requête
    return query.exec();
}
QSqlQueryModel* clientc::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT CLIENT_ID, NAME, EMAIL, TEL, SEXE, DATEN FROM CLIENT");

    // Formatage de la date de naissance (si nécessaire)
    for (int i = 0; i < model->rowCount(); ++i) {
        QModelIndex dateIndex = model->index(i, 5);  // Colonne de la date
        QString dateString = dateIndex.data().toDate().toString("yyyy-MM-dd");
        model->setData(dateIndex, dateString);
    }

    // Configuration des en-têtes de colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CLIENT_ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATEN"));

    return model;
}
bool clientc::supprimer_client(const QString &id)
{
    // Vérification de la validité de l'ID du client
    if (!isValidClientId(id)) {
        QMessageBox::critical(nullptr, "Information", "L'ID du client doit être un numéro de 8 chiffres.");
        return false;
    }

    // Vérification de l'existence de l'ID du client dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM CLIENT WHERE CLIENT_ID = :CLIENT_ID");
    checkQuery.bindValue(":CLIENT_ID", id);
    if (!checkQuery.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la vérification de l'ID du client.");
        return false;
    }
    checkQuery.next();
    int count = checkQuery.value(0).toInt();
    if (count == 0) {
        QMessageBox::information(nullptr, "Information", "L'ID du client spécifié n'existe pas dans la base de données.");
        return false;
    }


    // Suppression du client
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE CLIENT_ID = :CLIENT_ID");
    query.bindValue(":CLIENT_ID", id);

    return query.exec();
}
bool clientc::modifier_client()
{
    // Vérification des champs obligatoires
    if (CLIENT_ID.isEmpty()) {
        QMessageBox::information(nullptr, "Information", "Le champ CLIENT_ID est vide.");
        return false;
    }

    // Validation de l'ID du client
    if (!isValidClientId(CLIENT_ID)) {
        QMessageBox::information(nullptr, "Information", "L'ID du client doit être un numéro de 8 chiffres.");
        return false;
    }

    // Vérification de l'existence de l'ID du client dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM CLIENT WHERE CLIENT_ID = :CLIENT_ID");
    checkQuery.bindValue(":CLIENT_ID", CLIENT_ID);
    if (!checkQuery.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la vérification de l'ID dans la base de données.");
        return false;
    }
    checkQuery.next();
    int count = checkQuery.value(0).toInt();
    if (count == 0) {
        QMessageBox::information(nullptr, "Information", "L'ID du client spécifié n'existe pas dans la base de données.");
        return false;
    }

    // Validation du numéro de téléphone
    if (!TEL.isEmpty() && !isValidPhoneNumber(TEL)) {
        QMessageBox::information(nullptr, "Information", "Le numéro de téléphone doit être composé de chiffres uniquement et avoir une longueur valide.");
        return false;
    }

    // Validation de l'email
    if (!EMAIL.isEmpty() && !validateEmail(EMAIL)) {
        QMessageBox::information(nullptr, "Information", "Veuillez vérifier votre adresse e-mail.");
        return false;
    }

    // Validation de la date de naissance
    if (DATEN.isValid() && DATEN == QDate::currentDate()) {
        QMessageBox::critical(nullptr, "Information", "Veuillez vérifier la date de naissance.");
        return false;
    }

    // Préparation de la requête de mise à jour
    QSqlQuery query;
    QString queryString = "UPDATE CLIENT SET ";
    if (!NAME.isEmpty()) queryString += "NAME = :NAME, ";
    if (!EMAIL.isEmpty()) queryString += "EMAIL = :EMAIL, ";
    if (!TEL.isEmpty()) queryString += "TEL = :TEL, ";
    if (!SEXE.isEmpty()) queryString += "SEXE = :SEXE, ";
    if (DATEN.isValid()) queryString += "DATEN = :DATEN, ";
    queryString.chop(2); // Supprime la dernière virgule
    queryString += " WHERE CLIENT_ID = :CLIENT_ID";

    query.prepare(queryString);

    if (!NAME.isEmpty()) query.bindValue(":NAME", NAME);
    if (!EMAIL.isEmpty()) query.bindValue(":EMAIL", EMAIL);
    if (!TEL.isEmpty()) query.bindValue(":TEL", TEL);
    if (!SEXE.isEmpty()) query.bindValue(":SEXE", SEXE);
    if (DATEN.isValid()) query.bindValue(":DATEN", DATEN);
    query.bindValue(":CLIENT_ID", CLIENT_ID);

    return query.exec();
}
QSqlQueryModel* clientc::afficher_id(const QString &id)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Prepare the SQL query to select the client with the given CLIENT_ID
    QSqlQuery query;
    query.prepare("SELECT CLIENT_ID, NAME, EMAIL, TEL, SEXE, DATEN FROM CLIENT WHERE CLIENT_ID = :CLIENT_ID");
    query.bindValue(":CLIENT_ID", id);

    // Execute the query
    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la récupération des informations du client.");
        return nullptr; // Return nullptr if query fails
    }

    // Set the result of the query to the model
    model->setQuery(query);

    // Format the date (if necessary)
    for (int i = 0; i < model->rowCount(); ++i) {
        QModelIndex dateIndex = model->index(i, 5);  // Column for DATEN (date of birth)
        QString dateString = dateIndex.data().toDate().toString("yyyy-MM-dd");
        model->setData(dateIndex, dateString);
    }

    // Set column headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CLIENT_ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATEN"));

    return model;
}
QSqlQueryModel* clientc::affichage_trieID_croissant()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // SQL query to select client data sorted by CLIENT_ID in ascending order
    QSqlQuery query;
    query.prepare("SELECT CLIENT_ID, NAME, EMAIL, TEL, SEXE, DATEN FROM CLIENT ORDER BY CLIENT_ID ASC");

    // Execute the query
    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la récupération des clients triés par ID.");
        return nullptr; // Return nullptr if query fails
    }

    // Set the result of the query to the model
    model->setQuery(query);

    // Format the date (if necessary)
    for (int i = 0; i < model->rowCount(); ++i) {
        QModelIndex dateIndex = model->index(i, 5);  // Column for DATEN (date of birth)
        QString dateString = dateIndex.data().toDate().toString("yyyy-MM-dd");
        model->setData(dateIndex, dateString);
    }

    // Set column headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CLIENT_ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATEN"));

    return model;
}

void clientc::genererStatistiquesSexe(QSqlQueryModel* model)
{
    QPieSeries *series = new QPieSeries();

    int countHomme = 0;
    int countFemme = 0;

    // Vérification que le modèle a suffisamment de colonnes
    if (model->columnCount() > 4) { // SEXE est à l'index 4
        for (int row = 0; row < model->rowCount(); ++row) {
            QString sexe = model->data(model->index(row, 4)).toString(); // Colonne 4 pour SEXE
            if (sexe.toLower() == "m") {
                countHomme++;
            } else if (sexe.toLower() == "f") {
                countFemme++;
            }
        }
    }

    int totalCount = countHomme + countFemme;
    if (totalCount == 0) {
        // Eviter la division par zéro
        totalCount = 1;
    }

    // Calculer les pourcentages
    qreal percentHomme = (static_cast<qreal>(countHomme) / totalCount) * 100.0;
    qreal percentFemme = (static_cast<qreal>(countFemme) / totalCount) * 100.0;

    // Ajouter les segments au graphique
    series->append("Hommes (" + QString::number(percentHomme, 'm', 1) + "%)", countHomme);
    series->append("Femmes (" + QString::number(percentFemme, 'f', 1) + "%)", countFemme);

    // Créer un graphique et ajouter la série
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par sexe");

    // Personnaliser les polices pour le titre et la légende
    QFont font;
    font.setPixelSize(16);
    chart->setTitleFont(font);
    chart->legend()->setFont(font);
    chart->legend()->setAlignment(Qt::AlignRight);

    // Afficher le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(800, 600); // Ajuster la taille du graphique
    chartView->show();
}

