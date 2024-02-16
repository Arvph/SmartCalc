#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "finance_window.h"

extern "C" {
#include "../modules/smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow* ui;

  // added by me
 private slots:
  void digits_numbers();
  void on_pushButton_point_clicked();
  bool isPointAllowed(const QString& text);
  void on_pushButton_AC_clicked();
  void on_pushButton_equal_clicked();
  bool br_check(QString ch);
  bool oprt_check(QChar ch);
  bool is_digit(QChar ch);
  void on_pushButton_C_clicked();
  void on_pushButton_unar_clicked();
  // bool isUnarAllowed(const QString& text);
  bool count_closed_br(const QString& str);
  void on_pushButton_FIN_clicked();
};

#endif  // MAINWINDOW_H
