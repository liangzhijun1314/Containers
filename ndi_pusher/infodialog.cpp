#include "infodialog.h"
#include <QLayout>

infoDialog::infoDialog(QWidget *parent) :
    QDialog(parent)
{
    m_listView = new QListView(this);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(m_listView);
    layout->setMargin(0);
    setLayout(layout);
}

infoDialog::~infoDialog()
{
}
