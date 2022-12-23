#ifndef FORMD_H
#define FORMD_H

#include <QWidget>

namespace Ui {
class Formd;
}

class Formd : public QWidget
{
    Q_OBJECT

public:
    explicit Formd(QWidget *parent = 0);
    ~Formd();

private:
    Ui::Formd *ui;
};

#endif // FORMD_H
