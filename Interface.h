//==============================================================================
/*
    \author    Your Name
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifndef INTERFACE_H
#define INTERFACE_H
//------------------------------------------------------------------------------
#if defined(WIN32) | defined(WIN64)
#pragma warning(disable: 4100)
#endif
//------------------------------------------------------------------------------
#include "ui_Interface.h"
//------------------------------------------------------------------------------
#include "chai3d.h"
//------------------------------------------------------------------------------
#include <QGLWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QShortcut>
//------------------------------------------------------------------------------
class ApplicationWidget;
//------------------------------------------------------------------------------

namespace Ui
{
    class InterfaceClass;
}

//------------------------------------------------------------------------------

class Interface : public QMainWindow
{
    Q_OBJECT

    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    Interface (QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~Interface ();
    Ui::InterfaceClass ui;


    //--------------------------------------------------------------------------
    // PRIVATE MEMBERS - UI:
    //--------------------------------------------------------------------------

private:


    QShortcut *EscKey;
    QShortcut *FKey;
    QShortcut *SKey;
    QShortcut *QKey;
    QTimer *StatusTimer;
    ApplicationWidget *Application;
    QLabel GraphicRate;
    QLabel HapticRate;

    //--------------------------------------------------------------------------
    // PRIVATE MEMBERS:
    //--------------------------------------------------------------------------

private:

    int AbortRequest;

    //--------------------------------------------------------------------------
    // PRIVATE SLOTS:
    //--------------------------------------------------------------------------

private slots:

    //void on_sliderZoom_valueChanged(int val);
    void EnterFullScreen();
    void ExitFullScreen();
    void ToggleFullScreen();
    void SetFullScreen(bool fs);
    void ToggleSettings();
    void ShowSettings(bool show);
    void UpdateStatus();

    void on_alignCamera_clicked();
    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------



    void on_updateStaticMarkers_clicked();

    void on_hide_show_base_toggled(bool checked);

//    void on_hide_show_tool_toggled(bool checked);

    void on_zoom_out_clicked();

    void on_zoom_in_clicked();

//    void on_x_pos_toggled(bool checked);

//    void on_x_neg_toggled(bool checked);

//    void on_y_pos_toggled(bool checked);

//    void on_y_neg_toggled(bool checked);

//    void on_z_pos_toggled(bool checked);

//    void on_z_neg_toggled(bool checked);

    void on_pushButton_clicked();

    void on_load_gp_phantom_clicked();

    void on_scale_button_toggled(bool checked);

    void on_export_path_file_clicked();

public:

    int  Start();
    void Stop();
    void SyncUI();
    void updateLCDpos();
};


//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
