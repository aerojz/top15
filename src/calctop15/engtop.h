#ifndef ENGTOP_H
#define ENGTOP_H

#include <QObject>
#include <QVariantList>
#include <QThread>
#include "session.h"

class EngTop : public QObject
{
    friend Session;

    Q_OBJECT

public:
    explicit EngTop(QObject *parent = nullptr);
    ~EngTop();

    Q_INVOKABLE bool start(const QString &nameFile);
    Q_INVOKABLE bool isStart() { return flStart; }

signals:
    void stop(Session::RESULT res);
    void progress(qreal percent, QVariantList tops);

private slots:
    void stopProcess(Session::RESULT res);
    void progressProcess(qreal percent, CalcFreqWord::AllRatingWord tops);
    void startProcess();

private:
    QThread thread;
    Session *session{nullptr};

    bool flStart{false};
};

#endif // ENGTOP_H
