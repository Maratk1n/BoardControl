#include "mathbutton.h"
#include <QtScript/QScriptEngine>

MathButton::MathButton(const QString &text, QWidget *parent):
    QPushButton(text, parent)
{

}

void MathButton::setCoefficient(float coeff)
{
    _formula.clear();
    _coeff = coeff;
    setBorder();
}

void MathButton::setFormula(const QString &formula)
{
    _coeff = 1.0;
    _formula = formula;
    setBorder();
}

float MathButton::calc(float data)
{
    float val = 0.0;
    if (_formula.isEmpty()) {
        val = _coeff * data;
    }
    else {
        QString expression_string(QString(_formula).arg(data));
        QScriptEngine expression;
        val = expression.evaluate(expression_string).toNumber();
    }
    return val;
}

void MathButton::setBorder()
{
    QColor color(Qt::darkCyan);
    setStyleSheet(QString("border:3px solid rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));
}

void MathButton::resetExpr()
{
    _coeff = 1.0;
    _formula.clear();
    setStyleSheet("");
    return;
}
