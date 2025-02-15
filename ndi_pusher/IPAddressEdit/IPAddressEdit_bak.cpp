#include "IPAddressEdit.h" 
#include <QRegExpValidator> 
#include <QLabel> 
#include "IPPartLineEdit.h"
#include <QHBoxLayout>
#include <QClipboard>
#include <QApplication>

IPAddressEdit::IPAddressEdit(QWidget* pParent /* = 0 */)
: QWidget(pParent)
{ 
    this->setObjectName("IPAddressEdit");
    ip_part1_ = new IPPartLineEdit(this, 1);
    ip_part2_ = new IPPartLineEdit(this, 2);
    ip_part3_ = new IPPartLineEdit(this, 3);
    ip_part4_ = new IPPartLineEdit(this, 4);

    labeldot1_ = new QLabel(this); 
    labeldot2_ = new QLabel(this); 
    labeldot3_ = new QLabel(this);
    labeldot1_->setStyleSheet("QLabel{background-color: rgb(255, 255, 255);}");
    labeldot2_->setStyleSheet("QLabel{background-color: rgb(255, 255, 255);}");
    labeldot3_->setStyleSheet("QLabel{background-color: rgb(255, 255, 255);}");

    setStyleSheet("background-color: rgb(255, 255, 255);");
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(1);
    //hlayout->setContentsMargins(1,0,0,0);

    hlayout->setSpacing(0);
    hlayout->addWidget(ip_part1_);
    hlayout->addWidget(labeldot1_);
    hlayout->addWidget(ip_part2_);
    hlayout->addWidget(labeldot2_);
    hlayout->addWidget(ip_part3_);
    hlayout->addWidget(labeldot3_);
    hlayout->addWidget(ip_part4_);
    this->setLayout(hlayout);

    labeldot1_->setText(".");

    labeldot1_->setAlignment(Qt::AlignCenter);

    labeldot2_->setText(".");

    labeldot2_->setAlignment(Qt::AlignCenter);

    labeldot3_->setText(".");

    labeldot3_->setAlignment(Qt::AlignCenter);

    QWidget::setTabOrder(ip_part1_, ip_part2_); 
    QWidget::setTabOrder(ip_part2_, ip_part3_); 
    QWidget::setTabOrder(ip_part3_, ip_part4_); 
    ip_part1_->set_nexttab_edit(ip_part2_);
    ip_part2_->set_nexttab_edit(ip_part3_); 
    ip_part3_->set_nexttab_edit(ip_part4_);

    ip_part2_->set_pritab_edit(ip_part1_);
    ip_part3_->set_pritab_edit(ip_part2_);
    ip_part4_->set_pritab_edit(ip_part3_);


    connect(ip_part1_, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&))); 
    connect(ip_part2_, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&))); 
    connect(ip_part3_, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&))); 
    connect(ip_part4_, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&))); 

    connect(ip_part1_, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&))); 
    connect(ip_part2_, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&))); 
    connect(ip_part3_, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&))); 
    connect(ip_part4_, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&))); 
    ip_part1_->installEventFilter(this);
    ip_part2_->installEventFilter(this);
    ip_part3_->installEventFilter(this);
    ip_part4_->installEventFilter(this);
     
} 

IPAddressEdit::~IPAddressEdit() 
{ 

} 

void IPAddressEdit::textchangedslot(const QString& /*text*/) 
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    ippart1 = ip_part1_->text(); 
    ippart2 = ip_part2_->text(); 
    ippart3 = ip_part3_->text(); 
    ippart4 = ip_part4_->text(); 

    QString ipaddr = QString("%1.%2.%3.%4") 
                     .arg(ippart1) 
                     .arg(ippart2) 
                     .arg(ippart3) 
                     .arg(ippart4); 

    emit textchanged(ipaddr);
} 

void IPAddressEdit::texteditedslot(const QString &/*text*/) 
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    ippart1 = ip_part1_->text(); 
    ippart2 = ip_part2_->text(); 
    ippart3 = ip_part3_->text(); 
    ippart4 = ip_part4_->text(); 

    QString ipaddr = QString("%1.%2.%3.%4") 
        .arg(ippart1) 
        .arg(ippart2) 
        .arg(ippart3) 
        .arg(ippart4); 

    emit textedited(ipaddr); 
} 

void IPAddressEdit::setText(const QString &text)
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    QString qstring_validate = text; 

    // IP地址验证 
    QRegExp regexp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)"); 
    QRegExpValidator regexp_validator(regexp, this); 
    int nPos = 0; 
    QValidator::State state = regexp_validator.validate(qstring_validate, nPos); 
    // IP合法 
    if (state == QValidator::Acceptable) 
    { 
        QStringList ippartlist = text.split("."); 
     
        int strcount = ippartlist.size(); 
        int index = 0; 
        if (index < strcount) 
        { 
            ippart1 = ippartlist.at(index); 
        } 
        if (++index < strcount) 
        { 
            ippart2 = ippartlist.at(index); 
        } 
        if (++index < strcount) 
        { 
            ippart3 = ippartlist.at(index); 
        } 
        if (++index < strcount) 
        { 
            ippart4 = ippartlist.at(index); 
        } 
    } 

    ip_part1_->setText(ippart1); 
    ip_part2_->setText(ippart2); 
    ip_part3_->setText(ippart3); 
    ip_part4_->setText(ippart4); 
} 

QString IPAddressEdit::text() 
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    ippart1 = ip_part1_->text(); 
    ippart2 = ip_part2_->text(); 
    ippart3 = ip_part3_->text(); 
    ippart4 = ip_part4_->text(); 
    if(!this->checkInlegal()) return "";

    return QString("%1.%2.%3.%4") 
        .arg(ippart1) 
        .arg(ippart2) 
        .arg(ippart3) 
            .arg(ippart4);
}

void IPAddressEdit::setHight(int hight)
{
    ip_part1_->setFixedHeight(hight);
    ip_part2_->setFixedHeight(hight);
    ip_part3_->setFixedHeight(hight);
    ip_part4_->setFixedHeight(hight);
    labeldot1_->setFixedHeight(hight);
    labeldot2_->setFixedHeight(hight);
    labeldot3_->setFixedHeight(hight);
}

void IPAddressEdit::clear()
{
    ip_part1_->clear();
    ip_part2_->clear();
    ip_part3_->clear();
    ip_part4_->clear();
}

bool IPAddressEdit::checkInlegal()
{
    return !(ip_part1_->text().isEmpty() || ip_part2_->text().isEmpty() || ip_part3_->text().isEmpty() || ip_part4_->text().isEmpty());
}

bool IPAddressEdit::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ip_part1_ || watched == ip_part2_ || watched == ip_part3_ || watched == ip_part4_)
    {
         if (event->type() == QEvent::KeyPress)
         {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->matches(QKeySequence::Paste))
            {
                if(keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_V)
                {
                    QClipboard *clipboard = QApplication::clipboard(); //获取系统剪贴板指针
                    QString originalText = clipboard->text();
                    setText(originalText);
                }
            }
         }
    }
    return true;
}
