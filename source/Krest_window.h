#ifndef __KREST_WINDOW_H__
#define __KREST_WINDOW_H__

#include <QWidget>
#include <QObject>
#include <QGraphicsScene>
//#include <QGraphicsPixmapItem>
#include <QMainWindow>
#include <QGraphicsView>
#include <QAction>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QInputDialog>
#include <iostream>
#include <QVector3D>
#include <stdio.h>
#include <iostream>
// #include "hyscan-acoustic-data.h"
// #include "hyscan-db.h"

#include "RubberRect.h"
//#include <QMutex>
//#include <QMutexLocker>

#include "ui_form_mainwindow.h"
#include "../graphic_item_image/graphic_item_image.h"
#include "krest.h"
#include "krestview.h"
//#include "cgdalraster.h"
//#include "moiGdal.h"
#include "Krest_scene.h"
#include "cthread.h"
#include "sonar_emu_thread.h"

class QAction;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsView;
class KrestView;

double MathRound(double num, int precision);

// Creates temporal tiff file. Takes path. Returns path + filename.
QString create_tmp_tiff (QString fullfilename, int w, int h);
void remove_tmp_tiff (QString fullfilename);

// QSize estimate_tmp_tiff_size (QString project_dir_name, int project_id);
QMap<long int, unsigned int> estimate_tmp_tiff_size (QSize & out_size, QString project_dir_name, int project_id);

//! Класс, описывающий окно отображения кадра
class KrestWindow : public QMainWindow , public Ui::MainWindow {
	  Q_OBJECT
private:;
	KrestScene *scene;
	QGraphicsItem_Image *QGI_Image;
	bool is_move;//!< флаг режима перемещени¤
	double c,r;//!< положение курсора
	QAction *pushButtonFit;
	CThread*pThread ;
	SonarEmuThread *pThread_sound_gen;
	QPointF startPos,endPos; //начальная/конечноя позиции курсора при зуммировании
	Krest KrestXL,KrestXR,KrestYU,KrestYD;
	// HyScanDB *DB;
//public:;
    double PixelSize;//размер пикселя в мм
    double FrameSizeMm;//размер рамки в мм
    int FrameSizePx;//размер рамки в пикселях
    double time_delay;
    bool useSizeMm; //использовать задание рамки в мм
    QInputDialog *QIDSFSMm; //немодальные диалоги задания размера рамки в мм
    QInputDialog *QIDSFSPx; //в пикселях
    QInputDialog *QIDSTDSec; // задание временной задержки в секундах
    QPointF Center;
    RubberRect *RR;
    bool cutting;
    bool iscutting;
    int cut_count;
    QString nameIn ; //image path+name
    QString nameOut ;//image name
    QString pathOut ;//image path
    QString pathPoint ;//points path
    QString tmp_tiff_path;
    QString tmp_tiff_full_name;
    QString bd_path;
    QString project_dir_name;
    int project_id;
    QVector<unsigned int> acoustic_data_ch_ids;
    // time, id
    QMap<long int, unsigned int> map_acoustic_data_ch_ids;
    // GDALDataset *ptmp_tiff;
    // GDALDriver *pdriver_tmp_tiff;
public:;
  	//! конструктор
    KrestWindow();
    ~KrestWindow();
    QPointF XL,XR,YU,YD;
    //enum numbKrst{movekursor,krestXL,krestYU,krestXR,krestYD};
    Krest*selectedKrest();
    void calculCoordKrest();
    //bool openImage(const QString &fileName);
    //bool saveImage(const QString &fileName, const char *fileFormat);
    //void setImage(const QImage &image);

private slots:;
   void openProject();
   void set_tmp_tiff_path();
   void start_sound_gen();
   void stop_sound_gen();
   void openImageDialog ();
   void openPoints();
   void savePoints();
   void savePointsAs(); 

   void addKrestRX( QPointF F = QPointF(-1,-1) );  //! добавление крестов
   void addKrestLX( QPointF F = QPointF(-1,-1) );
   void addKrestUY( QPointF F = QPointF(-1,-1) );
   void addKrestDY( QPointF F = QPointF(-1,-1) );
   void changeCoord(double x,double y);
   void changeFrameSize(int); //задание размера рамки в пикселх
   void changeFrameSize(double); 
   void changeTimeDelay(double val);
   void cursorCross();
   void cursorHand ();
   void cursorRubber();   
   //void cutImage();
   //void cutImage2();
   //void cutImage3();
   void cutRect();
   void endCut ();
   //void ctrlZ_Cut();
   //void ctrlZ_All_Cut();   
   //void updateCoord(QPointF,QPointF);
   void del();   //! удаление
   //void show_position_on_shot(double c,double r); //! отображение координат курсора
   void updateActions(); //! обновление действий
   void pickAllKrest( );   //catch all krest
   //!слот запуска рассчета
   //void pressed_button_run ();
   //void pressed_button_run2();
   void run_process();
   void ShowPixel   (QPointF const&Pixel) ;
   void SetPixelSize();  //задание размера пикселя в мм
   void SetFrameSizeMm();//задание размера рамки в мм
   void SetFrameSizePx();//задание размера рамки в пикселях
   void setTimeDelay();
   void SaveTrAs();
   void SaveTr();
   void ScaleFit(){graphicsView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);} ;
   void ScaleRubberFit(QRect);
   void StopProcess();
   // May receive number of worked lines
   void update_scene (int nwl=0);
private:;
    void createActions();
    void createMenus();
    void setupKrest(Krest *krest,QPointF F );
    void openImage (QString fullfilename);

    //void setupKrest(Krest *krest);
protected:;
    //void updateRubberBandRegion();
    //void wheelEvent(QWheelEvent *event);
   	//! отработка нажати¤ на кнопку мыши
    virtual void	mousePressEvent ( QGraphicsSceneMouseEvent * event );
    //virtual void	mousePressEvent ( QMouseEvent * event );
  	//! отработка отпускани¤ на кнопки мыши
    virtual void	mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    //virtual void	mouseReleaseEvent ( QMouseEvent * event );
   	//! отработка сигнала перемещени¤ мыши
    //virtual void	mouseMoveEvent ( QMouseEvent * event );   
   	//virtual void	mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
   	//! отработка нажати¤ на кнопки
    //virtual void keyPressEvent ( QKeyEvent * event );
signals:;
    //! сигнал о положении курсора на снимке
    //void position_on_shot(double c,double r);
};



/*class Block_transform {//: public QVector3D {
public:
  Block_transform(QPoint,QPoint,QPoint,QPoint,int BlockSizeX_OUT,int BlockSizeY_OUT);  
//private:
  QVector3D ro_block[4];
  QVector3D e1_block,e2_block,b_block,rc_block;
  int  r_block,c_block;
  double c0b_OUT,r0b_OUT;//, r0_block,c0_block;
  double e11_block,e12_block,e22_block,e1b_block,e2b_block;
  double D_block,D1_block,t1_block;      
};*/

#endif
