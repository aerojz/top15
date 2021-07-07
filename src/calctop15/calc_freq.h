#ifndef CALCFREQ_H
#define CALCFREQ_H

#include <QObject>
#include <QHash>
#include <QVector>

struct RAITING_WORD {
    Q_GADGET

    Q_PROPERTY(int rating MEMBER rating)
    Q_PROPERTY(QString word MEMBER word)

public:
    int rating;
    QString word;
};

class CalcFreqWord : public QObject
{   
    Q_OBJECT
public:
    using RatingWord = RAITING_WORD;
    using AllRatingWord = QVector<RatingWord>;

    explicit CalcFreqWord(QObject *parent = nullptr);

    void clearResult() { freq.clear(); }
    void process(const QString &str);
    void result(AllRatingWord &res);

private:
    QHash<QString, int> freq;

private:
    static constexpr int kMaxRes{15};
};

Q_DECLARE_METATYPE(CalcFreqWord::RatingWord)
Q_DECLARE_METATYPE(CalcFreqWord::AllRatingWord)

#endif // CALCTOP15_H
