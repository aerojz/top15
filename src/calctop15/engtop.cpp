#include <QDebug>
#include <QThread>

#include "engtop.h"

EngTop::EngTop(QObject *parent)
    : QObject(parent)
{
}

EngTop::~EngTop()
{

    thread.quit();
    thread.wait();
}

bool EngTop::start(const QString &nameFile)
{
    session = new (std::nothrow) Session;
    if (nullptr == session) {
        return false;
    }
    session->setFileName(nameFile);
    session->moveToThread(&thread);

    connect(&thread, &QThread::finished, session, &Session::deleteLater);

    connect(&thread, &QThread::started, session, &Session::startProcess);
    connect(session, &Session::finished, &thread, &QThread::quit);

    connect(session, &Session::progress, this, &EngTop::progressProcess);
    connect(session, &Session::stop, this, &EngTop::stopProcess);
    connect(session, &Session::start, this, &EngTop::startProcess);

    thread.start();

    return true;
}

void EngTop::stopProcess(Session::RESULT res)
{
    flStart = false;
    emit stop(res);
}

void EngTop::progressProcess(qreal percent, CalcFreqWord::AllRatingWord tops)
{
    QVariantList listVarRes;

    for (const auto &el : tops) {
        QVariant tmpVar;
        tmpVar.setValue(el);
        listVarRes.append(tmpVar);
    }
    emit progress(percent, listVarRes);
}

void EngTop::startProcess()
{
    flStart = true;
}
