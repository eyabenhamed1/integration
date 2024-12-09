#ifndef GESTIONEQUIPEMENTS_H
#define GESTIONEQUIPEMENTS_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
class GestionEquipements
{
        QString ID_equipements;
        QString Nom;
        QString Type;
        QString Etat;
        QString Date_acquisition;
        QString EMPLACEMENT;
        QString Prix;
public:
    GestionEquipements();
    GestionEquipements(QString Nom,QString Type,QString Etat,QString Date_acquisition,QString Emplacment,QString Prix);
    GestionEquipements(QString ID_equipements,QString Nom,QString Type,QString Etat,QString Date_acquisition,QString Emplacment,QString Prix);
    void Ajouter();
    QSqlQueryModel *afficher();
    void supprimer(QString ID_equipements);
    void modifier();
    QSqlQueryModel* tri();
    QSqlQueryModel* rechercher(QString TYPE);
};

#endif // GESTIONEQUIPEMENTS_H
