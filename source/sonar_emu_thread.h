#ifndef __SONAR_EMU_THREAD_H__
#define __SONAR_EMU_THREAD_H__
#include <QtGui>
#include <QThread>

class settings {
 protected:;
   QString name_in ;
   QString name_out;
   QSize q_out_size;
   QVector<QPointF> qvqp_x; //-x+y+x-y
 public:
   //settings(QString i,QString o, QVector<QPoint> x) {name_in=i;name_out=o;qvqp_x=x;};
   void set_in_name (QString n) {name_in =n;};
   void set_out_name(QString n) {name_out=n;};
   void set_point   (QVector<QPointF> x) {qvqp_x=x;};
   void set_size_out(QSize s) {q_out_size=s;};
   settings( ) ;
};


class SonarEmuThread : public QThread { //, public settings {
    Q_OBJECT
public: ;
    QProgressBar *progressbar;
public:;
    SonarEmuThread (QObject *parent = NULL) ;
    virtual ~SonarEmuThread () {;} ;

protected: ;
    virtual void run ();
signals:;
    void number_worked_lines (int nl);
};

#endif
