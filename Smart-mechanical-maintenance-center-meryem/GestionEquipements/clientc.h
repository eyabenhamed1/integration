#ifndef CLIENTC_H
#define CLIENTC_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QRegularExpression>
#include <QFileDialog>
#include <QDebug>

class clientc
{
private:
    QString CLIENT_ID, NAME, EMAIL, TEL, SEXE;
    QDate DATEN;

public:
    // Constructeurs
    clientc();
    clientc(QString CLIENT_ID, QString NAME, QString EMAIL, QString TEL, QString SEXE, QDate DATEN);

    // Getters
    QString getClientId()   { return CLIENT_ID; }
    QString getName()   { return NAME; }
    QString getEmail()   { return EMAIL; }
    QString getTel()   { return TEL; }
    QString getSexe()   { return SEXE; }
    QDate getDateN()   { return DATEN; }

    // Setters
    void setClientId(  QString  id) { CLIENT_ID = id; }
    void setName(  QString name) { NAME = name; }
    void setEmail(  QString  email) { EMAIL = email; }
    void setTel(  QString  tel) { TEL = tel; }
    void setSexe(  QString  sexe) { SEXE = sexe; }
    void setDateN(  QDate  dateN) { DATEN = dateN; }

    // Méthodes CRUD
    bool ajouter_client();
    QSqlQueryModel* afficher();
    bool supprimer_client(const QString &id);
    bool   modifier_client();
   QSqlQueryModel* afficher_id(const QString &id);
    bool recherche(const QString &id, QSqlQueryModel*& model);
    QSqlQueryModel*   affichage_trieID_croissant();
    void   genererStatistiquesSexe(QSqlQueryModel* model);

    // Méthodes de validation des données
    bool isValidClientId(const QString &id) const {
        return id.length() == 8 && id.toInt();
    }

    bool validateEmail(const QString &email) const {
        QRegularExpression re("^[a-zA-Z0-9+_.-]+@[a-zA-Z0-9.-]+$");
        return re.match(email).hasMatch();
    }

    bool isValidPhoneNumber(const QString &tel) const {
        if (tel.length() != 8) return false;
        for (QChar c : tel) {
            if (!c.isDigit()) return false;
        }
        return true;
    }

    bool isValidName(const QString &name) const {
        QRegularExpression regex("^[a-zA-Z ]+$");
        return regex.match(name.trimmed()).hasMatch();
    }
};

#endif // CLIENTC_H
