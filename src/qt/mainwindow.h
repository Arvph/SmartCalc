#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QWidget>

#include "finance_window.h"
#include "graph.h"

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
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 signals:
  void newTextAvailable(const QString &text);

 private slots:
  void digits_numbers();
  void operators();
  void on_pushButton_point_clicked();
  void on_pushButton_AC_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_C_clicked();
  void on_pushButton_unar_clicked();
  void on_pushButton_FIN_clicked();
  void on_pushButton_close_br_clicked();
  void on_pushButton_open_br_clicked();
  void on_pushButton_GRAPH_clicked();
  void on_pushButton_X_clicked();

 private:
  Ui::MainWindow *ui;
  graph *graphWindow = nullptr;
  bool isPointAllowed(const QString &text);
  bool br_check(const QString ch);
  bool oprt_check(QChar ch);
  bool is_digit(QChar ch);
  bool count_closed_br(const QString &str);
};

#endif  // MAINWINDOW_H
