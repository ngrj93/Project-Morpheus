#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    //Load application
    QApplication a(argc, argv);

    //Splash screen
    QSplashScreen *spl=new QSplashScreen();
    spl->setPixmap(QPixmap("/home/nagaraj/Morpheus/morph.jpg"));
    spl->show();
    MainWindow w;
    w.setFixedSize(w.width(),w.height());
    w.setWindowIcon(QIcon("/home/nagaraj/Morpheus/firewire.png"));
    QTimer::singleShot(2500,spl,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));

    //Credits page
    w.write("<h3>Thank you for using MorphSim ver 2.0! </h3> This simulator models load distribution activities in a wireless ad hoc high performance cluster and evaluates performance in a dynamic fashion.");
    w.write("-------------------------------------------------------------------------");
    w.write("Performance Parameters:<br>");
    w.write("<font color='maroon'>[1] Hit/miss ratio</font> ");
    w.write("<font color='maroon'>[2] Average resource utilization</font>");
    w.write("<font color='maroon'>[3] Response time</font>");
    w.write("<font color='maroon'>[4] Starvation deadline</font><br>");
    w.write("These parameters can be utilised as benchmarks for further analysis and comparison with other resource allocation and scheduling strategies.");
    w.write("-------------------------------------------------------------------------");
    w.write("The log file contains execution runtime statistics and other log events.<br>");
    w.write("© 2016 by Nagaraj Poti & Prasobh P.S");

    return a.exec();
}
