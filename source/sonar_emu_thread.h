#ifndef __SONAR_EMU_THREAD_H__
#define __SONAR_EMU_THREAD_H__
#include <QtGui>
#include <QThread>

class SonarEmuSts {
 protected:;
   QString _fullname_tmp_tiff;
   QVector<unsigned int> _acoustic_channel_ids;
   int _project_id;
   double _time_delay;
   /* Map, {time, id} */
   QMap<long int, unsigned int> _map_acoustic_data_ch_ids;
 public:;
   void set_fullname_tmp_tiff (QString n) {_fullname_tmp_tiff = n;};
   void set_acoustic_channel_ids (QVector<unsigned int> ids) {_acoustic_channel_ids = ids;}; // deprecated
   void set_project_id (int id) {_project_id = id;};
   void set_time_delay (double td){_time_delay = td;};
   void set_map_acoustic_data_ch_ids (QMap<long int, unsigned int> ids_map) {_map_acoustic_data_ch_ids = ids_map;};
   SonarEmuSts () ;
};

class SonarEmuThread : public QThread , public SonarEmuSts {
    Q_OBJECT
public:;
    QProgressBar *progressbar;
public:;
    SonarEmuThread (QObject *parent = NULL) ;
    virtual ~SonarEmuThread () {;} ;

protected: ;
    virtual void run () { start_write_full_tiff_all_tracks (); };
    // virtual void run () { start_sonar_emu_view (); };
    void start_sonar_emu_view ();
    void start_write_tiff ();
    void start_write_full_tiff ();
    void start_write_full_tiff_all_tracks ();
signals:;
    void number_worked_lines (int nl);
};

#endif
