#ifndef MATHBUTTON_H
#define MATHBUTTON_H

#include <QPushButton>
#include "protocol.h"

class MathExpression;

class MathButton : public QPushButton
{
    Q_OBJECT

    friend class MathExpression;
public:
    MathButton(const QString &text, QWidget *parent = 0);
    void setCoefficient(float coeff);
    void setFormula(const QString &formula);
    float calc(float data);
    void resetExpr();
private:
    void setBorder();
    float _coeff = 1.0;
    QString _formula;
};

#endif // MATHBUTTON_H
