#include <QVBoxLayout>
#include <QPixmap>
#include <QIcon>
#include <QTableWidget>
#include <QPushButton>

#include "ndipusher.h"
#include "infodialog.h"
#include "titlebar.h"
#include "centerwidget.h"

NdiPusher::NdiPusher(QWidget *parent) :
    QWidget(parent)
{

    InitCenterWidget();
    InitTitleBar();

    connect(m_centerWidget,SIGNAL(signal_exit()),this,SLOT(close()));
    connect(m_centerWidget,SIGNAL(signal_info_show()),this,SLOT(slot_info_show()));

}

NdiPusher::~NdiPusher()
{
}

void NdiPusher::InitTitleBar()
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    TitleBar *pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);

    resize(720, 680);
    setWindowTitle("Ndi pusher");
    setWindowIcon(QIcon(":/images/ndi"));

//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, QColor(0,191,255));
//    setAutoFillBackground(true);
//    setPalette(pal);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    //pLayout->addStretch();
    pLayout->addWidget(m_centerWidget);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(pLayout);

}

void NdiPusher::InitCenterWidget()
{
    m_centerWidget = new CenterWidget(this);
}

void NdiPusher::slot_info_show()
{
    m_infoDlg = new infoDialog(this);
    m_infoDlg->setModal(false);
    m_infoDlg->show();
}

