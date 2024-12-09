#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
/*db.setDatabaseName("SourceProjet");//nom de la base
db.setUserName("ahmed");//inserer nom de l'utilisateur
db.setPassword("esprit18");//inserer mot de passe de cet utilisateur*/
db.setDatabaseName("CPP_project");//inserer le nom de la source de données
db.setUserName("aymen");//inserer nom de l'utilisateur
db.setPassword("xiozzahs");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}
