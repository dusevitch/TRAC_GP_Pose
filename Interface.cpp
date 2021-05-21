//==============================================================================
/*
    \author    David Usevitch (CI INSERTION AND OMNIMAGNET POSITIONING CODE)
*/
//==============================================================================

//------------------------------------------------------------------------------
#include <QTextStream>
#include "Interface.h"
#include "Application.h"
//------------------------------------------------------------------------------
using std::string;
//------------------------------------------------------------------------------

Interface::Interface (QWidget        *parent,
                      Qt::WindowFlags flags) : QMainWindow (parent, flags)
{
    // setup ui
    ui.setupUi(this);

    // setup keyboard shortcuts
    EscKey   = new QShortcut (Qt::Key_Escape, this, SLOT(ExitFullScreen()));
    FKey     = new QShortcut (Qt::Key_F,      this, SLOT(ToggleFullScreen()));
    SKey     = new QShortcut (Qt::Key_S,      this, SLOT(ToggleSettings()));
    QKey     = new QShortcut (Qt::Key_Q,      this, SLOT(close()));

    // sync settings state
    connect (ui.actionShow_Settings, SIGNAL(triggered(bool)), this, SLOT(ShowSettings(bool)));
    connect (ui.actionFull_Screen,   SIGNAL(triggered(bool)), this, SLOT(SetFullScreen(bool)));


    // create CHAI3D application widget
    Application = new ApplicationWidget (this);
    if (Application) 
    {
        //Application->updateCamera_to_base(); // TODO: fix where this should be...??
        Application->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        centralWidget()->layout()->addWidget (Application);


    }
    else 
    {
        QMessageBox::information (this, "Application", "Cannot start application.", QMessageBox::Ok);
        close();
    }

    // configure timers
    StatusTimer = new QTimer (this);
    connect(StatusTimer, SIGNAL(timeout()), this, SLOT(UpdateStatus()));
    StatusTimer->start (1000);

    // set numeric label fonts
    QFont font("Monospace", 8);
    font.setStyleHint(QFont::TypeWriter);
    //ui.labelZoom->setFont (font);

    // initialize status bar
    GraphicRate.setFrameStyle(QFrame::Panel | QFrame::Sunken);
    ui.statusBar->addPermanentWidget (&GraphicRate);
    HapticRate.setFrameStyle(QFrame::Panel | QFrame::Sunken);
    ui.statusBar->addPermanentWidget (&HapticRate);

    // set default widget configuration
//    ui.sliderZoom->setValue ((int)(100.0*0.6));

    // show settings by default
    ShowSettings(true);

}

//------------------------------------------------------------------------------

int Interface::Start()
{
    // start haptic thread
    if (Application->start () < 0)
    {
        QMessageBox::warning (this, "CHAI3D", "No device found.", QMessageBox::Ok);
        return (-1);
    }

    // synchronize setting widgets with simulation initial state
    SyncUI ();

    return (0);
}

//------------------------------------------------------------------------------

void Interface::Stop()
{
    Application->stop();
}

//------------------------------------------------------------------------------

Interface::~Interface()
{
    Stop();
}

//------------------------------------------------------------------------------

void Interface::SyncUI()
{
//    ui.sliderZoom->setValue ((int)(10.0*Application->m_camera->getSphericalRadius()));
}

//------------------------------------------------------------------------------

void Interface::EnterFullScreen()
{
    showFullScreen ();
    ui.actionFull_Screen->setChecked (true);
}

//------------------------------------------------------------------------------

void Interface::ExitFullScreen()
{
    showNormal ();
    ui.actionFull_Screen->setChecked (false);
}

//------------------------------------------------------------------------------

void Interface::ToggleFullScreen()
{
    if (isFullScreen())
    {
        ExitFullScreen();
    }
    else
    {
        EnterFullScreen();
    }
}

//------------------------------------------------------------------------------

void Interface::SetFullScreen(bool fs)
{
    if( fs && !isFullScreen())
    {
        EnterFullScreen();
    }
    else if (!fs &&  isFullScreen())
    {
        ExitFullScreen();
    }
}

//------------------------------------------------------------------------------

void Interface::ToggleSettings()
{
      bool show = !ui.Settings->isVisible();
      ui.Settings->setVisible (show);
      ui.actionShow_Settings->setChecked (show);
}

//------------------------------------------------------------------------------
void Interface::ShowSettings(bool show)
{
      ui.Settings->setVisible (show);
      ui.actionShow_Settings->setChecked (show);
}

//------------------------------------------------------------------------------

//void Interface::on_sliderZoom_valueChanged(int val)
//{
//      //ui.labelZoom->setText (QString("%1").arg(val, 3));

//      double sph_rad = Application->m_camera->getSphericalRadius();
//      Application->m_camera->setSphericalRadius(sph_rad + (double)val/10.0);
//     // Application->m_camera->rotateAboutLocalAxisDeg( chai3d::cVector3d(0,1,0), (val-50)/10);
//}

//------------------------------------------------------------------------------

void Interface::UpdateStatus()
{
    if (Application)
    {
        GraphicRate.setText(QString("graphic: %1 Hz").arg((int)(Application->getGraphicRate()), 3));
        HapticRate.setText(QString("haptic: %1 Hz").arg((int)(Application->getHapticRate()), 4));
    }
    else 
    {
        GraphicRate.setText(QString("graphic: --- Hz"));
        HapticRate.setText(QString("haptic: ---- Hz"));
    }
}

//------------------------------------------------------------------------------


void Interface::on_alignCamera_clicked()
{
    if (Application)
    {
        Application->updateCamera_to_base();
    }else{
        qDebug() << "Application Not Running Error";
    }
}

void Interface::on_updateStaticMarkers_clicked()
{
    if (Application)
    {
        Application->updateStaticMarkers();
    }else{
        qDebug() << "Application Not Running Error";
    }
}

void Interface::on_hide_show_base_toggled(bool checked)
{
    if (checked){
        Application->gpBlock_base->setTransparencyLevel(0);
        ui.hide_show_base->setText("Show Base");

    }else{
        Application->gpBlock_base->setTransparencyLevel(1);
        ui.hide_show_base->setText("Hide Base");
    }
}

void Interface::on_hide_show_tool_toggled(bool checked)
{
    if (checked){
        Application->omniTool->cursorBlock->setTransparencyLevel(0);
        ui.hide_show_tool->setText("Show Tool");

    }else{
        Application->omniTool->cursorBlock->setTransparencyLevel(1);
        ui.hide_show_tool->setText("Hide Tool");
    }
}

void Interface::updateLCDpos(){

    // For calib cube calibration
//    QLCDNumber *bframe_x_val = ui.bframe_x;
//    QLCDNumber *bframe_y_val = MainWindow::findChild<QLCDNumber *>("bframe_y");
//    QLCDNumber *bframe_z_val = MainWindow::findChild<QLCDNumber *>("bframe_z");

//    QLCDNumber *tool_x_val = MainWindow::findChild<QLCDNumber *>("tool_x");
//    QLCDNumber *tool_y_val = MainWindow::findChild<QLCDNumber *>("tool_y");
//    QLCDNumber *tool_z_val = MainWindow::findChild<QLCDNumber *>("tool_z");

//    QLCDNumber *btool_x_val = MainWindow::findChild<QLCDNumber *>("btool_x");
//    QLCDNumber *btool_y_val = MainWindow::findChild<QLCDNumber *>("btool_y");
//    QLCDNumber *btool_z_val = MainWindow::findChild<QLCDNumber *>("btool_z");


//    ui.bframe_x->display(QString::number(Application->global_base_pose->pos.x()));
//    ui.bframe_y->display(QString::number(Application->global_base_pose->pos.y()));
//    ui.bframe_z->display(QString::number(Application->global_base_pose->pos.z()));

    ui.objframe_x->display(QString::number(Application->omnimag_pose->pos.x()));
    ui.objframe_y->display(QString::number(Application->omnimag_pose->pos.y()));
    ui.objframe_z->display(QString::number(Application->omnimag_pose->pos.z()));

    ui.base_x->display(QString::number(Application->cube_pose->pos.x()));
    ui.base_y->display(QString::number(Application->cube_pose->pos.y()));
    ui.base_z->display(QString::number(Application->cube_pose->pos.z()));

}


void Interface::on_zoom_out_clicked()
{
    Application->m_camera->setLocalPos(Application->m_camera->getLocalPos() + chai3d::cVector3d(0,0,100));
}

void Interface::on_zoom_in_clicked()
{
    Application->m_camera->setLocalPos(Application->m_camera->getLocalPos() + chai3d::cVector3d(0,0,-100));
}





// Test the position of the x, y, and z arrows appearing-----------------------
void Interface::on_x_pos_toggled(bool checked)
{
    if (checked){
        Application->omniTool->setArrowTransparency(1, 0, 0, 0, 0, 0, Application->omniTool->arrow_array);
        Application->omniTool->setArrowTransparency(1, 0, 0, 0, 0, 0, Application->omniTool->circ_arrow_array);
        ui.x_pos->setStyleSheet("background-color: green");
    }else{
        Application->omniTool->allArrowsTransparent(Application->omniTool->arrow_array);
        Application->omniTool->allArrowsTransparent(Application->omniTool->circ_arrow_array);
        ui.x_pos->setStyleSheet("background-color: gray");
    }
}

void Interface::on_x_neg_toggled(bool checked)
{
    if (checked){
        Application->omniTool->setArrowTransparency(0, 0, 0, 1, 0, 0, Application->omniTool->arrow_array);
        Application->omniTool->setArrowTransparency(0, 0, 0, 1, 0, 0, Application->omniTool->circ_arrow_array);
        ui.x_neg->setStyleSheet("background-color: green");
    }else{
        Application->omniTool->allArrowsTransparent(Application->omniTool->arrow_array);
        Application->omniTool->allArrowsTransparent(Application->omniTool->circ_arrow_array);
        ui.x_neg->setStyleSheet("background-color: gray");
    }
}

void Interface::on_y_pos_toggled(bool checked)
{
    if (checked){
        Application->omniTool->setArrowTransparency(0, 1, 0, 0, 0, 0, Application->omniTool->arrow_array);
        Application->omniTool->setArrowTransparency(0, 1, 0, 0, 0, 0, Application->omniTool->circ_arrow_array);
        ui.y_pos->setStyleSheet("background-color: green");
    }else{
        Application->omniTool->allArrowsTransparent(Application->omniTool->arrow_array);
        Application->omniTool->allArrowsTransparent(Application->omniTool->circ_arrow_array);
        ui.y_pos->setStyleSheet("background-color: gray");
    }
}

void Interface::on_y_neg_toggled(bool checked)
{
    if (checked){
        Application->omniTool->setArrowTransparency(0, 0, 0, 0, 1, 0, Application->omniTool->arrow_array);
        Application->omniTool->setArrowTransparency(0, 0, 0, 0, 1, 0, Application->omniTool->circ_arrow_array);
        ui.y_neg->setStyleSheet("background-color: green");
    }else{
        Application->omniTool->allArrowsTransparent(Application->omniTool->arrow_array);
        Application->omniTool->allArrowsTransparent(Application->omniTool->circ_arrow_array);
        ui.y_neg->setStyleSheet("background-color: gray");
    }
}

void Interface::on_z_pos_toggled(bool checked)
{
    if (checked){
        Application->omniTool->setArrowTransparency(0, 0, 1, 0, 0, 0, Application->omniTool->arrow_array);
        Application->omniTool->setArrowTransparency(0, 0, 1, 0, 0, 0, Application->omniTool->circ_arrow_array);
        ui.z_pos->setStyleSheet("background-color: green");
    }else{
        Application->omniTool->allArrowsTransparent(Application->omniTool->arrow_array);
        Application->omniTool->allArrowsTransparent(Application->omniTool->circ_arrow_array);
        ui.z_pos->setStyleSheet("background-color: gray");
    }
}

void Interface::on_z_neg_toggled(bool checked)
{
    if (checked){
        Application->omniTool->setArrowTransparency(0, 0, 0, 0, 0, 1, Application->omniTool->arrow_array);
        Application->omniTool->setArrowTransparency(0, 0, 0, 0, 0, 1, Application->omniTool->circ_arrow_array);
        ui.z_neg->setStyleSheet("background-color: green");
    }else{
        Application->omniTool->allArrowsTransparent(Application->omniTool->arrow_array);
        Application->omniTool->allArrowsTransparent(Application->omniTool->circ_arrow_array);
        ui.z_neg->setStyleSheet("background-color: gray");
    }
}

void Interface::on_pushButton_clicked()
{
    Application->load_gp_file();
    ui.gp_file_label->setText(Application->loaded_file);
}
