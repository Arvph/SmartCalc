#include "graph.h"

#include "ui_graph.h"

graph::graph(QWidget *parent, const QString &currentText)
    : QDialog(parent), ui(new Ui::graph) {
  ui->setupUi(this);

  m_currentText = currentText;

  setWindowTitle("Function graph");
  setFixedSize(width(), height());

  customPlot = new QCustomPlot(ui->frame);
  customPlot->resize(ui->frame->size());

  connect(ui->x_min, &QLineEdit::textChanged, this, &graph::updatePlot);
  connect(ui->x_max, &QLineEdit::textChanged, this, &graph::updatePlot);
  connect(ui->y_min, &QLineEdit::textChanged, this, &graph::updatePlot);
  connect(ui->y_max, &QLineEdit::textChanged, this, &graph::updatePlot);

  updatePlot();
}

graph::~graph() {
  delete ui;
  delete customPlot;
}

void graph::updatePlot() {
  bool xMinOk, xMaxOk, yMinOk, yMaxOk;
  double x_min = ui->x_min->text().toDouble(&xMinOk);
  double x_max = ui->x_max->text().toDouble(&xMaxOk);
  double y_min = ui->y_min->text().toDouble(&yMinOk);
  double y_max = ui->y_max->text().toDouble(&yMaxOk);

  plot(x_min, x_max, y_min, y_max);
}

void graph::plot(double x_min, double x_max, double y_min, double y_max) {
  customPlot->xAxis->setLabel("X Axis");
  customPlot->yAxis->setLabel("Y Axis");
  customPlot->xAxis->setRange(x_min, x_max);
  customPlot->yAxis->setRange(y_min, y_max);

  std::string tempStr = m_currentText.toStdString();
  const char *cstr = tempStr.c_str();
  char postfix[256];
  char result[256];

  to_postfix(cstr, postfix);

  QVector<double> x(101), y(101);  // 101 точка
  for (int i = 0; i < 101; ++i) {
    x[i] = x_min + (x_max - x_min) * i / 100.0;
    calculation(postfix, x[i], result);
    y[i] = atof(result);
  }

  customPlot->clearGraphs();
  customPlot->addGraph();
  customPlot->graph(0)->setData(x, y);

  customPlot->replot();
}

void graph::on_newTextAvailable(const QString &text) {
  m_currentText = text;
  updatePlot();
}

void graph::on_default_value_clicked() {
  ui->x_min->setText("-20");
  ui->x_max->setText("20");
  ui->y_min->setText("-20");
  ui->y_max->setText("20");
}
