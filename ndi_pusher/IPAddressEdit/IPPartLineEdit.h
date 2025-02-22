#ifndef IPPartLineEdit_H
#define IPPartLineEdit_H

#include <QLineEdit> 

class QWidget; 
class QFocusEvent; 
class QKeyEvent; 

class IPPartLineEdit : public QLineEdit 
{ 
    Q_OBJECT 
public: 
    IPPartLineEdit(QWidget *parent = 0,int index = 0);
    ~IPPartLineEdit(void); 

    void set_nexttab_edit(QLineEdit *nexttab) { next_tab_ = nexttab; } 
    void set_pritab_edit(QLineEdit *pritab) {pri_tab_ = pritab;}

protected: 
    //virtual void focusInEvent(QFocusEvent *e);
    virtual void keyPressEvent(QKeyEvent *event);   

private slots: 
    void text_edited(const QString& text); 

private: 
    QLineEdit *next_tab_; 
    QLineEdit *pri_tab_;
}; 

#endif //IPPartLineEdit_H