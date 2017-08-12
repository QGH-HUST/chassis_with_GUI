#ifndef CHASSIS_DISPLAY_H
#define CHASSIS_DISPLAY_H

#include <QDialog>
#include "QTimer"

extern QString str_FLCPOS;
extern QString str_BLCPOS;
extern QString str_FLTPOS;
extern QString str_BLTPOS;

extern QString str_FLCVEL;
extern QString str_BLCVEL;
extern QString str_FLTVEL;
extern QString str_BLTVEL;

extern QString str_FLPVEL;
extern QString str_BLPVEL;
extern QString str_FLEVEL;
extern QString str_BLEVEL;

extern QString str_FLPACC;
extern QString str_BLPACC;
extern QString str_FLPDEC;
extern QString str_BLPDEC;

extern QString str_CURRENTX;
extern QString str_CURRENTY;
extern QString str_CURRENTS;

extern QString str_TRACKX;
extern QString str_TRACKY;
extern QString str_TRACKS;

extern QString str_DESTX;
extern QString str_DESTY;
extern QString str_DESTS;

extern QString str_CPPNUM;
extern QString str_AIMNUM;


namespace Ui {
class chassis_display;
}

class chassis_display : public QDialog
{
    Q_OBJECT
    
public:
    explicit chassis_display(QWidget *parent = 0);
    ~chassis_display();
private slots:
    void on_OPENButton_clicked();
    void timerupdate();
    void on_AIMNUM_editingFinished();

    void on_STARTButton_clicked();

    void on_CLOSEButton_clicked();

    void on_PLANButton_clicked();

    void on_TRACKButton_clicked();

    void on_STOPButton_clicked();

private:
    Ui::chassis_display *ui;
};

#endif // CHASSIS_DISPLAY_H
