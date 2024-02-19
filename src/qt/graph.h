#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QWidget>

#include "qcustomplot.h"

extern "C" {
#include "../modules/smart_calc.h"
}

namespace Ui {
class graph;
}

class graph : public QDialog {
  Q_OBJECT

 public:
  explicit graph(QWidget *parent = nullptr, const QString &currentText = "");
  ~graph();

 public slots:
  void plot(double x_min, double x_max, double y_min, double y_max);
  void on_newTextAvailable(const QString &text);

 private slots:
  void updatePlot();
  void on_default_value_clicked();

 private:
  Ui::graph *ui;
  QCustomPlot *customPlot;
  QString m_currentText;
};

#endif  // GRAPH_H
