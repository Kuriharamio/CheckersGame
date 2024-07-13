#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>
#include <QDataStream>

class User {
public:
    User(int num = 0, const QString &username = "user", int rank = 0, bool isTurn = false, int operated = 0,const QString &Color = "NONE",const QString &Type = "NONE",int stamina = 0,bool regretted = 0 );


    int getNum() const;
    void setNum(int num);

    QString getUsername() const;
    void setUsername(const QString &username);

    int getRank() const;
    void setRank(int rank);

    bool getIsTurn() const;
    void setIsTurn(bool regretted);

    bool getRegretted() const;
    void setRegretted(bool regretted);

    int getOperated() const;
    void setOperated(int operated);

    QString getColor() const;
    void setColor(const QString &color);

    QString getType() const;
    void setType(const QString &type);


    int getStamina() const;
    void setStamina(int stamina);

    friend QDataStream& operator<<(QDataStream& out, const User& user);
    friend QDataStream& operator>>(QDataStream& in, User& user);
    bool operator==(const User& other) const ;

private:

    QString Username;
    int Rank;
    bool IsTurn;
    int Operated;
    int Num;
    QString Color;
    QString Type;
    int Stamina;
    bool Regretted;

};

#endif // USER_H
