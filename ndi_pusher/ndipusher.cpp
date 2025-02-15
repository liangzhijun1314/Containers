#include <QVBoxLayout>
#include <QPixmap>
#include <QIcon>
#include <QTableWidget>
#include <QPushButton>
#include <QPainter>

#include "ndipusher.h"
#include "infodialog.h"
#include "titlebar.h"
#include "centerwidget.h"

NdiPusher::NdiPusher(QWidget *parent) :
    QWidget(parent)
{
    this->setObjectName("mainWidget");
    InitCenterWidget();
    InitTitleBar();
    setNdiLayout();
}

NdiPusher::~NdiPusher()
{
}

void NdiPusher::InitTitleBar()
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    m_titleBar = new TitleBar(this);
    installEventFilter(m_titleBar);

    resize(720, 680);
    setWindowTitle("Ndi pusher");
    setWindowIcon(QIcon(":/images/logo"));
}

void NdiPusher::InitCenterWidget()
{
    m_centerWidget = new CenterWidget(this);

    connect(m_centerWidget,SIGNAL(signal_exit()),this,SLOT(close()));
    connect(m_centerWidget,SIGNAL(signal_info_show()),this,SLOT(slot_info_show()));
}

void NdiPusher::setNdiLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(m_titleBar);
    pLayout->addWidget(m_centerWidget);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(2, 2, 2, 2);

    setLayout(pLayout);
}

void NdiPusher::paintEvent(QPaintEvent *e)
{

}

void NdiPusher::slot_info_show()
{
    m_infoDlg = new infoDialog(this);
    m_infoDlg->setModal(false);
    m_infoDlg->show();
}

