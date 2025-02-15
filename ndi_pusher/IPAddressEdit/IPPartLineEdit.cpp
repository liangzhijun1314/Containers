#include "IPPartLineEdit.h" 
#include <QIntValidator> 
#include <QKeyEvent> 

IPPartLineEdit::IPPartLineEdit(QWidget *parent/* = 0*/,int index)
: QLineEdit(parent) 
{ 
    next_tab_ = NULL; 
    pri_tab_ = NULL;

    this->setFrame(false);
    this->setAlignment(Qt::AlignHCenter);

    QRegExp regexp;
    if(index == 1)
    {
        regexp.setPattern("(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|[1-9])");
    }else{
        regexp.setPattern("(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)|(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)\\.");
    }

    QRegExpValidator *regexp_validator = new QRegExpValidator(regexp, this);
    this->setValidator(regexp_validator);

    connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(text_edited(const QString&))); 
} 

IPPartLineEdit::~IPPartLineEdit(void) 
{ 
} 


void IPPartLineEdit::keyPressEvent(QKeyEvent *event) 
{ 
    if(event->key() == Qt::Key_Backspace)
    {
        if(pri_tab_ != NULL && this->text().isEmpty())
       {
            pri_tab_->setFocus();
            pri_tab_->selectAll();
        }
    }else if(event->key() == Qt::Key_Left){
        if(pri_tab_ != NULL && cursorPosition() == 0){
            pri_tab_->setFocus();
            pri_tab_->setCursorPosition(pri_tab_->text().size());
        }
    }else if(event->key() == Qt::Key_Right){
        if(next_tab_ != NULL & cursorPosition() == this->text().size()){
            next_tab_->setFocus();
            next_tab_->setCursorPosition(0);
        }
    }
    QLineEdit::keyPressEvent(event); 
} 

void IPPartLineEdit::text_edited(const QString& text) 
{ 
    QString chanText = text;
    int index = chanText.indexOf(".");
    if(index >= 0)
    {
        chanText.remove(index,1);
        this->setText(chanText);
        if (next_tab_)
        {
            next_tab_->setFocus();
        }
        return ;
    }
    QIntValidator v(0, 255, this); 
    QString ipaddr = text; 
    int pos = 0; 
    QValidator::State state = v.validate(ipaddr, pos);  
    if (state == QValidator::Acceptable) 
    { 
        if (ipaddr.size() > 1) 
        { 
            if (ipaddr.size() == 2) 
            { 
                int ipnum = ipaddr.toInt(); 
                 
                if (ipnum > 25) 
                { 
                    if (next_tab_) 
                    { 
                        next_tab_->setFocus(); 
                        next_tab_->selectAll(); 
                    }     
                } 
            } 
            else 
            { 
                if (next_tab_) 
                { 
                    next_tab_->setFocus(); 
                    next_tab_->selectAll(); 
                }     
            } 
        } 
    } 
}
