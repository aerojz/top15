#include <QVector>
#include <QDebug>

#include "calc_freq.h"

CalcFreqWord::CalcFreqWord(QObject *parent) : QObject(parent)
{

}


void CalcFreqWord::process(const QString &str)
{
    QStringList strList{str.split(" ")};

    for (auto &nextWord : strList) {
        if (nextWord.isNull()
                || nextWord.isEmpty()) {
            continue;
        }

        freq[nextWord]++;
    }
}

void CalcFreqWord::result(AllRatingWord &res)
{
    res.clear();

    QHash<QString, int>::const_iterator i = freq.constBegin();
    RAITING_WORD resWord;

    while (i != freq.constEnd()) {
        resWord.word = i.key();
        resWord.rating = i.value();

        res.append(resWord);

        ++i;
    }

    std::stable_sort(res.begin()
                     , res.end()
                     , [](const RAITING_WORD &pair1, const RAITING_WORD &pair2){ return pair1.rating > pair2.rating;});

    if (res.size() > kMaxRes) {
        res.resize(kMaxRes);
    }
}
