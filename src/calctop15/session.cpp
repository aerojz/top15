#include <QThread>

#include <QDir>
#include <QFile>
#include <QString>
#include <QUrl>
#include <QDebug>

#include "session.h"

Session::Session(QObject *parent) : QObject(parent)
{

}


void Session::startProcess()
{   
    emit start();

    QUrl url(fileName_m);
    QString fileName = QDir::toNativeSeparators(url.toLocalFile());
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit stop(Session::RESULT::ERR);
        emit finished();
        return;
    }

    CalcFreqWord::AllRatingWord result;
    CalcFreqWord calcFreq;

    auto sizeFile{file.size()};
    auto numberByteProcess{0};
    while (!file.atEnd()) {
        QByteArray buffer = file.read(kSizeParth);

        if (!file.atEnd()) {
            auto lastPos = buffer.lastIndexOf(" ");

            if ((-1) != lastPos) {
                auto numbChop{buffer.size() - lastPos - 1};

                buffer.chop(numbChop);
                file.seek(file.pos() - numbChop);
            }
        }

        calcFreq.process(buffer);
        calcFreq.result(result);

        numberByteProcess += buffer.size();
        qreal percent{numberByteProcess / (sizeFile / 100.0)};
        emit progress(percent, result);
#ifdef DELAY_PROGRESS
        QThread::msleep(DELAY_PROGRESS);
#endif
    }

    emit stop(Session::RESULT::OK);
    emit finished();
}
