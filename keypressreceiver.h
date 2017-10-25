#ifndef KEYPRESSRECEIVER_H
#define KEYPRESSRECEIVER_H

#include <QObject>



class keyPressReceiver : public QObject
{
    Q_OBJECT
protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // KEYPRESSRECEIVER_H
