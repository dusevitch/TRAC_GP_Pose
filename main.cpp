//==============================================================================
/*
    \author    Your Name
*/
//==============================================================================

//#include <QSerialPortInfo>
#include<QDebug>
//------------------------------------------------------------------------------
#include "Interface.h"
//------------------------------------------------------------------------------

int main (int argc, char *argv[])
{
//  TO TEST INPUT COM PORT:
//    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
//        {
//        qDebug() << serialPortInfo.portName();
//        }

    QApplication a (argc, argv);
    Interface    w;

    w.show ();
    w.Start ();

    return a.exec ();
}

//------------------------------------------------------------------------------
