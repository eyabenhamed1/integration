#ifndef SERVICE_H
#define SERVICE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QSqlRecord>
#include <QMap>
#include "connection.h"

class Service
{
    QString Nom, Description, Duree, Employee, Equipement;
    int IDM;
    double Prix;
public:
    Service();
    Service(int,QString,QString,QString,QString,QString,float);
    //Getters
    QString getNom(){return Nom;}
    QString getDescription(){return Description;}
    QString getDuree(){return Duree;}
    QString getEmployee(){return Employee;}
    QString getEquipement(){return Equipement;}
    int GetID(){return IDM;}
    float GetPrix(){return Prix;}
    //Setters
    void setNom(QString n){Nom=n;}
    void setDescription(QString d){Description=d;}
    void setDuree(QString du){Duree=du;}
    void setEmployee(QString em){Employee=em;}
    void setEquipement(QString eq){Equipement=eq;}
    void setID(int id){IDM=id;}
    void setPrix(float p){Prix=p;}

    bool ajouter();
    QSortFilterProxyModel * afficher();
    bool supprimer(int);
    bool update();
    QSqlQueryModel* search(const QString &searchTerm);
    QMap<QString, double> getRevenueByService();

};

#endif // SERVICE_H
