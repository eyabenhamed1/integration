#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include "service.h"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include <QDebug>



Service::Service()
    : IDM(0), Prix(0.0) // Initialize numeric fields to 0 or default values
{
    // Optionally, initialize strings to empty if needed
    Nom = "";
    Description = "";
    Duree = "";
    Employee = "";
    Equipement = "";
}

Service::Service(int IDM,QString Nom,QString Description,QString Duree,QString Employee,QString Equipement,float Prix)
{
    this->IDM=IDM;
    this->Nom=Nom;
    this->Description=Description;
    this->Duree=Duree;
    this->Employee=Employee;
    this->Equipement=Equipement;
    this->Prix=Prix;

}

bool Service::ajouter()
{
    QSqlQuery checkQuery;
        QString res = QString::number(IDM);

        // Check if the ID already exists
        checkQuery.prepare("SELECT COUNT(*) FROM SERVICE WHERE IDM = :IDM");
        checkQuery.bindValue(":IDM", res);
        if (!checkQuery.exec() || !checkQuery.next()) {
            return false; // Query failed or no result, return false
        }

        if (checkQuery.value(0).toInt() > 0) {
            return false; // ID already exists, so return false
        }

    QSqlQuery query;
    query.prepare("INSERT INTO SERVICE (IDM, NAME, DESCRIPTION, PRICE, DURATION, EMPLOYEE, EQUIPEMENT)"
                  "VALUES (:IDM, :NAME, :DESCRIPTION, :PRICE, :DURATION, :EMPLOYEE, :EQUIPEMENT)");
    query.bindValue(":IDM", res);
    query.bindValue(":NAME", Nom);
    query.bindValue(":DESCRIPTION", Description);
    query.bindValue(":PRICE", QString::number(Prix));
    query.bindValue(":DURATION", Duree);
    query.bindValue(":EMPLOYEE", Employee);
    query.bindValue(":EQUIPEMENT", Equipement);
    return query.exec();
}
QSortFilterProxyModel *Service::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM SERVICE");
    //Headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRICE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DURATION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMPLOYEE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("EQUIPEMENT"));

    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);

    return proxyModel;
}
bool Service::supprimer(int IDM)
{
    QSqlQuery query;
    QString res = QString::number(IDM);
    query.prepare("DELETE FROM SERVICE WHERE IDM = :IDM");
    query.bindValue(":IDM", IDM);

    if (!query.exec()) {
        qDebug() << "Delete query failed: " << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}
bool Service::update()
{
    QSqlQuery query;

    // Prepare the SQL update statement
    query.prepare("UPDATE SERVICE SET NAME = :NAME, DESCRIPTION = :DESCRIPTION, PRICE = :PRICE, "
                  "DURATION = :DURATION, EMPLOYEE = :EMPLOYEE, EQUIPEMENT = :EQUIPEMENT "
                  "WHERE IDM = :IDM");

    // Bind values to the query
    query.bindValue(":IDM", IDM);             // ID is an int, corresponds to NUMBER
    query.bindValue(":NAME", Nom);            // QString, corresponds to VARCHAR2
    query.bindValue(":DESCRIPTION", Description); // QString, corresponds to VARCHAR2
    query.bindValue(":PRICE", Prix);          // float, corresponds to FLOAT
    query.bindValue(":DURATION", Duree);      // QString, corresponds to VARCHAR2
    query.bindValue(":EMPLOYEE", Employee);    // QString, corresponds to VARCHAR2
    query.bindValue(":EQUIPEMENT", Equipement); // QString, corresponds to VARCHAR2

    // Debugging output to check bound values
    qDebug() << "IDM:" << IDM;
    qDebug() << "NAME:" << Nom;
    qDebug() << "DESCRIPTION:" << Description;
    qDebug() << "PRICE:" << Prix;
    qDebug() << "DURATION:" << Duree;
    qDebug() << "EMPLOYEE:" << Employee;
    qDebug() << "EQUIPEMENT:" << Equipement;

    // Execute the query and handle errors
    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text(); // Log the error if it fails
        return false; // Indicate failure
    }

    return true; // Indicate success
}

QSqlQueryModel* Service::search(const QString &searchTerm) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = QString("SELECT * FROM SERVICE WHERE NAME LIKE '%%1%'").arg(searchTerm);
    model->setQuery(queryStr);

    // Optionally, set header data
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRICE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DURATION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMPLOYEE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("EQUIPEMENT"));

    return model;
}

QMap<QString, double> Service::getRevenueByService() {
    QMap<QString, double> revenueData;

    // Create and set up the model using the existing database connection
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT NAME, PRICE FROM SERVICE");

    // Check for query errors
    if (model->lastError().isValid()) {
        qDebug() << "Query failed:" << model->lastError().text();
        delete model; // Clean up if the query fails
        return revenueData; // Return empty map on failure
    }

    // Iterate through the rows of the model
    for (int i = 0; i < model->rowCount(); ++i) {
        QString serviceName = model->record(i).value("NAME").toString();
        double revenue = model->record(i).value("PRICE").toDouble();

        // Debug output to verify the retrieved values
        qDebug() << "Service:" << serviceName << "Revenue:" << revenue;

        // Add the service and its revenue to the map
        revenueData[serviceName] = revenue;
    }

    delete model; // Clean up the model after use

    return revenueData;
}

