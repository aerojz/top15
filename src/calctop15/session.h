#ifndef SESSION_H
#define SESSION_H

#include <QObject>

#include "calc_freq.h"

class Session : public QObject
{
    Q_OBJECT
public:
    enum class RESULT {
        OK
        , ERR
    };

    explicit Session(QObject *parent = nullptr);

    void setFileName(const QString &fileName) {fileName_m = fileName;}

signals:
    void start();
    void progress(qreal percent, CalcFreqWord::AllRatingWord tops);
    void stop(Session::RESULT res);
    void finished();

public slots:
    void startProcess();

private:
    QString fileName_m;
    static constexpr int kSizeParth{1024};
};

#endif // CALCTOP_H
