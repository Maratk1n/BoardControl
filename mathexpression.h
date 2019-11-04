#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H

#include <QDialog>
#include "mathbutton.h"

namespace Ui {
class MathExpression;
}

class MathExpression : public QDialog
{
    Q_OBJECT

public:
    MathExpression(MathButton *button, QWidget *parent = 0);
    ~MathExpression();
    void setCoefficient(float coeff);
    void setFormula(const QString &formula);

private slots:
    void on_apply_clicked();

    void on_reset_clicked();

private:
    float _coeff = 1.0;
    QString _formula;
    Ui::MathExpression *ui;
    void init();
    MathButton *_button = nullptr;
    const int kCoefficient = 0;
    const int kFormula = 1;
};

#endif // MATHEXPRESSION_H
