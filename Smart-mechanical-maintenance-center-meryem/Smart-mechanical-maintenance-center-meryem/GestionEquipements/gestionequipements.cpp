#include "gestionequipements.h"

GestionEquipements::GestionEquipements()
{

}
GestionEquipements::GestionEquipements(QString ID_equipements,QString Nom,QString Type,QString Etat,QString Date_acquisition,QString EMPLACEMENT,QString Prix)
{
    this->ID_equipements=ID_equipements;
    this->Nom=Nom;
    this->Etat=Etat;
    this->Type=Type;
    this->EMPLACEMENT=EMPLACEMENT;
    this->Date_acquisition=Date_acquisition;
    this->Prix=Prix;
}
GestionEquipements::GestionEquipements(QString Nom,QString Type,QString Etat,QString Date_acquisition,QString EMPLACEMENT,QString Prix)
{
    this->Nom=Nom;
    this->Etat=Etat;
    this->Type=Type;
    this->EMPLACEMENT=EMPLACEMENT;
    this->Date_acquisition=Date_acquisition;
    this->Prix=Prix;
}
void GestionEquipements::Ajouter()
{
    QSqlQuery query;
    query.prepare("insert into EQUIPEMENTS (ID_EQUIPEMENT,NOM,TYPE,ETAT,EMPLACEMENT,Date_acquisition,Prix) values (:ID_EQUIPEMENT,:Nom,:Etat,:Type,:EMPLACEMENT,:Date_acquisition,:Prix)");//requete bch najouti lel base les attributs
    query.bindValue(":ID_EQUIPEMENT", ID_equipements);
    query.bindValue(":Nom", Nom);
    query.bindValue(":Etat", Etat);
    query.bindValue(":Type", Type);
    query.bindValue(":EMPLACEMENT", EMPLACEMENT);
    query.bindValue(":Date_acquisition", Date_acquisition);
    query.bindValue(":Prix", Prix);
    query.exec();
}
QSqlQueryModel * GestionEquipements::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from EQUIPEMENTS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_equipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_acquisition"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Prix"));
    return model;
}
void GestionEquipements::supprimer(QString id)
{
        QSqlQuery query;
        query.prepare("delete from EQUIPEMENTS where ID_EQUIPEMENT = :ID_EQUIPEMENT");
        query.bindValue(":ID_EQUIPEMENT", id);
        query.exec();
}
void GestionEquipements::modifier()
{
    QSqlQuery query;
          query.prepare("update  EQUIPEMENTS set  Nom=:Nom, Etat=:Etat,Type=:Type,EMPLACEMENT=:EMPLACEMENT,Date_acquisition=:Date_acquisition,Prix=:Prix where(ID_equipement=:ID_equipement)");
          query.bindValue(":ID_equipement",ID_equipements);
          query.bindValue(":Nom", Nom);
          query.bindValue(":Etat", Etat);
          query.bindValue(":Type", Type);
          query.bindValue(":EMPLACEMENT", EMPLACEMENT);
          query.bindValue(":Date_acquisition", Date_acquisition);
          query.bindValue(":Prix", Prix);
          query.exec();
}
QSqlQueryModel* GestionEquipements::tri()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENTS ORDER BY PRIX ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_equipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_acquisition"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Prix"));

    return model;
}

QSqlQueryModel* GestionEquipements::rechercher(QString NOM) {
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM EQUIPEMENTS WHERE Nom like '%"+NOM+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_equipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_acquisition"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Prix"));
    return model;
}
