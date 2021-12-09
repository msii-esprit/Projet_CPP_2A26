
#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>
Notification::Notification()
{

}

void Notification::notification_ajoutterrain()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    //notifyIcon->setIcon(QIcon("C:/Users/asus/Desktop/pdf/logo_projet"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des TERRAINS ","nouveau TERRAIN est ajouté ",QSystemTrayIcon::Information,15000);
}



void Notification::notification_supprimerterrain(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des TERRAINS ","Un TERRAIN est supprimé",QSystemTrayIcon::Information,15000);
}





void Notification::notification_modifierterrain(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des TERRAINS ","UN TERRAINS est modifié",QSystemTrayIcon::Information,15000);

}



































