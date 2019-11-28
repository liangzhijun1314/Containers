#include "centerwidget.h"
//#include "ui_centerwidget.h"
#include <QLabel>
#include "IPAddressEdit.h"
#include <QLayout>
#include <QLineEdit>
#include <QListView>

CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent)/*,
    ui(new Ui::CenterWidget)*/
{
    //ui->setupUi(this);
    InitUi();
}

CenterWidget::~CenterWidget()
{
    //delete ui;
}

void CenterWidget::InitUi()
{
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    m_lb_ip_addr = new QLabel(this);
    m_lb_ip_addr->setText("IP 地址");
    m_lb_ip_addr->setFont(font);
    //m_lb_play_buffers->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

//    m_ip_addr = new IPAddressEdit(this);
//    m_ip_addr->setIP("233.1.0.1");

    m_lb_play_buffers = new QLabel(this);
    m_lb_play_buffers->setText("播放缓冲");
    m_lb_play_buffers->setFont(font);
    m_lb_play_buffers->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    m_line_play_buffer = new QLineEdit(this);

    m_lb_mesc = new QLabel(this);
    m_lb_mesc->setText("毫秒");

    QHBoxLayout * play_layout = new QHBoxLayout();
    play_layout->addWidget(m_lb_play_buffers);
    play_layout->addWidget(m_lb_mesc);

    QHBoxLayout * hLayout = new QHBoxLayout();
    hLayout->addWidget(m_lb_ip_addr);
    //hLayout->addWidget(m_ip_addr);
    hLayout->addLayout(play_layout);

    m_list_view = new QListView(this);


    QVBoxLayout * vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout);
    vLayout->addWidget(m_list_view);
    vLayout->setStretch(0, 2);
    vLayout->setStretch(1, 8);
    vLayout->setMargin(0);
    setLayout(vLayout);

}

//void CenterWidget::on_bt_start_push_clicked()
//{

//}

//void CenterWidget::on_bt_end_push_clicked()
//{

//}

//void CenterWidget::on_bt_info_clicked()
//{
//    emit signal_info_show();
//}

//void CenterWidget::on_bt_exit_clicked()
//{
//    emit signal_exit();
//}
