#include "userinterface.h"
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserInterface w; //All code manage in 'w'
    w.show();

    return a.exec();
}
