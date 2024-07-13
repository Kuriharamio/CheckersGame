#include "user.h"

User::User(int num , const QString &username, int rank, bool isTurn, int operated, const QString &color,const QString &type,int stamina,bool regretted)
    : Num(num),Username(username), Rank(rank), IsTurn(isTurn), Operated(operated), Color(color), Type(type), Stamina(stamina), Regretted(regretted) {


}

bool User::operator==(const User& other) const {
    return Username == other.Username &&
           Rank == other.Rank &&
           IsTurn == other.IsTurn &&
           Operated == other.Operated &&
           Num == other.Num &&
           Color == other.Color &&
           Type == other.Type &&
           Stamina == other.Stamina;
}

QDataStream& operator<<(QDataStream& out, const User& user) {
    out << user.getUsername() << user.getRank() << user.getIsTurn() << user.getOperated()
        << user.getNum() << user.getColor() << user.getType() << user.getStamina();
    return out;
}

QDataStream& operator>>(QDataStream& in, User& user) {
    QString tempUsername;
    int tempRank;
    bool tempIsTurn;
    int tempOperated;
    int tempNum;
    QString tempColor;
    QString tempType;
    int tempStamina;
    in >> tempUsername >> tempRank >> tempIsTurn >> tempOperated
        >> tempNum >> tempColor >> tempType >> tempStamina;
    user.setUsername(tempUsername);
    user.setRank(tempRank);
    user.setIsTurn(tempIsTurn);
    user.setOperated(tempOperated);
    user.setNum(tempNum);
    user.setColor(tempColor);
    user.setType(tempType);
    user.setStamina(tempStamina);
    return in;
}

int User::getNum() const {
    return Num;
}

void User::setNum(int num) {
    Num = num;
}

QString User::getUsername() const {
    return Username;
}

void User::setUsername(const QString &username) {
    Username = username;
}

int User::getRank() const {
    return Rank;
}

void User::setRank(int rank) {
    Rank = rank;
}

bool User::getIsTurn() const {
    return IsTurn;
}

void User::setIsTurn(bool isTurn) {
    IsTurn = isTurn;
}

bool User::getRegretted() const {
    return Regretted;
}

void User::setRegretted(bool regretted) {
    Regretted = regretted;
}

int User::getOperated() const {
    return Operated;
}

void User::setOperated(int operated) {
    Operated = operated;
}

QString User::getColor() const {
    return Color;
}

void User::setColor(const QString &color) {
    Color = color;
}

QString User::getType() const{
    return Type;

}
void User::setType(const QString &type){
    Type = type;
}

void User::setStamina(int stamina) {
    Stamina = stamina;
}

int User::getStamina() const {
    return Stamina;
}
