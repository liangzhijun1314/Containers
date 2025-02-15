#ifndef MYIPADDREDIT_H
#define MYIPADDREDIT_H

#include <QFrame>
#include <QMouseEvent>
#include <QKeyEvent>

class QLineEdit; 
class QLabel; 
class IPPartLineEdit;

class IPAddressEdit : public QWidget
{ 
    Q_OBJECT 
public: 
    IPAddressEdit(QWidget* pParent = 0);
    ~IPAddressEdit();

    void setText(const QString &text);
    QString text();  
    void setHight(int hight);
    void clear();
    bool checkInlegal();
protected:
    bool eventFilter(QObject *watched, QEvent *event);

signals: 
    void textchanged(const QString& text); 
    void textedited(const QString &text); 

private slots: 
    void textchangedslot(const QString& text); 
    void texteditedslot(const QString &text); 

private: 
    IPPartLineEdit *ip_part1_; //ip的四段
    IPPartLineEdit *ip_part2_;
    IPPartLineEdit *ip_part3_;
    IPPartLineEdit *ip_part4_;

    QLabel *labeldot1_; //'.'号
    QLabel *labeldot2_;     
    QLabel *labeldot3_; 
};
#endif //MYIPADDREDIT_H
