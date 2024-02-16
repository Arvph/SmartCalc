#ifndef FINANCE_WINDOW_H
#define FINANCE_WINDOW_H

#include <QDialog>
#include <QMessageBox>

extern "C" {
#include "../modules/smart_calc.h"
}

namespace Ui {
class Finance_window;
}

class Finance_window : public QDialog
{
    Q_OBJECT

public:
    explicit Finance_window(QWidget *parent = nullptr);
    ~Finance_window();

private:
    Ui::Finance_window *ui;

    QWidget *creditWidgetGroup;
    QWidget *debitWidgetGroup;

private slots:
    void on_creditButton_clicked();
    void on_debitButton_clicked();
    void onButton1Clicked();
    void onButton2Clicked();

    void on_calculate_credit_clicked();
    void on_calculate_clear_clicked();
};


#endif // FINANCE_WINDOW_H
