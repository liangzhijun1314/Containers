#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QListView>

class infoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit infoDialog(QWidget *parent = 0);
    ~infoDialog();

private:
    QListView * m_listView;
};

#endif // INFODIALOG_H
