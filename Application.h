//==============================================================================
/*
    \author    Your Name
*/
//==============================================================================


//------------------------------------------------------------------------------
#ifndef APPLICATION_H
#define APPLICATION_H
//------------------------------------------------------------------------------
#if defined(WIN32) | defined(WIN64)
#pragma warning(disable: 4100)
#endif
//------------------------------------------------------------------------------
#include "chai3d.h"
//------------------------------------------------------------------------------
#include "Interface.h"
//------------------------------------------------------------------------------
#include <QWheelEvent>
//------------------------------------------------------------------------------
#include "PolarisSpectra.h"
#include <armadillo>
#include <QDebug>

#include "guidedtool.h"

#include "json/json.h"
#include "polaristransformmatrix.h"
#include <eigen3/Eigen/Dense>

void _hapticThread (void *arg);

//------------------------------------------------------------------------------

class ApplicationWidget : public QGLWidget
{

    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    ApplicationWidget (QWidget *parent);
    virtual ~ApplicationWidget ();


    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    int start();
    int stop();
    void waitForStop();
    void* hapticThread();
    bool isRunning() { return m_running; }

    double getGraphicRate() { return (m_graphicRate.getFrequency()); }
    double getHapticRate() { return  (m_hapticRate.getFrequency()); }

    //--------------------------------------------------------------------------
    // PROTECTED METHODS:
    //--------------------------------------------------------------------------

protected:

    void initializeGL();
    void resizeGL(int a_width, int a_height);
    void paintGL();
//    void wheelEvent(QWheelEvent *event);
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event) { updateGL(); }


    //--------------------------------------------------------------------------
    // PUBLIC MEMBERS:
    //--------------------------------------------------------------------------

public:

    // application control
    Interface* m_parent;
    chai3d::cMutex m_worldLock;
    chai3d::cMutex m_runLock;
    chai3d::cThread m_thread;
    chai3d::cFrequencyCounter m_graphicRate;
    chai3d::cFrequencyCounter m_hapticRate;

    int m_timerID;
    bool m_running;
    int m_width;
    int m_height;
    int m_mouseX;
    int m_mouseY;
    bool m_mouseMoveCamera;

    // CHAI3D world
    chai3d::cWorld* m_world;
    chai3d::cCamera* m_camera;
    chai3d::cDirectionalLight* m_light;
    chai3d::cMultiMesh* m_object;

    // TRAC WORLD TOOL:
    chai3d::cMultiMesh* cursorBlock;
    chai3d::cShapeSphere* cursor;
    chai3d::cShapeSphere* cursorAxisDev;

    // Polaris Tracker
    PolarisSpectra* polaris;


    //------------FOR CURRENT SETUP-----------------
    // Tool Variables
    chai3d::cVector3d tool_position;
    chai3d::cMatrix3d tool_rotation;

    //Reference tool Variables
    chai3d::cVector3d reference_position;
    chai3d::cMatrix3d reference_rotation;

    // Tools
    GuidedTool* omnimagBase;
    GuidedTool* omniTool;

    double x_omnimag_pos;
    double y_omnimag_pos;
    double z_omnimag_pos;

    double x_base_pos;
    double y_base_pos;
    double z_base_pos;

    double x_cube_pos;
    double y_cube_pos;
    double z_cube_pos;

    QString loaded_file = "NO FILE LOADED";

    polarisTransformMatrix cochleaPose;

    std::vector<Eigen::Vector3d> cochlea_path_field_points;
    std::vector<Eigen::Vector3d> cochlea_path_pos_points;



//    Eigen::Matrix3d get_pos_rot(const Eigen::Matrix4d& trans_base, int polaris_tool_num, double &global_x, double &global_y, double &global_z);
//    void transformVector(const Eigen::Matrix4d& transformation_matrix, Eigen::Vector4d vector, double& toolPos_x, double& toolPos_y, double& toolPos_z, int inv);
    void updateCamera_to_base();

    Eigen::Matrix4d transf_base = Eigen::MatrixXd::Identity(4,4);
    polarisTransformMatrix *global_base_pose;
    polarisTransformMatrix *omnimag_pose;
    polarisTransformMatrix *cube_pose;

    polarisTransformMatrix* getPoseData(int polaris_num);
    polarisTransformMatrix *temp_pose = NULL;

    polarisTransformMatrix *camera_trans_mat; // Camera view matrix in polaris frame (p^T_v)

    polarisTransformMatrix* cursor_base_matrix;

    void updateStaticMarkers();
    void load_gp_file();

    bool polaris_on = true; // turn on/off polaris

    // TEST VARIABLES:
    chai3d::cMultiMesh* cursorBlock_base;
    chai3d::cShapeSphere* cursor_base;
    chai3d::cShapeSphere* cursorAxisDev_base;

    chai3d::cMultiMesh* cursorBlock_tool;
    chai3d::cShapeSphere* cursor_tool;
    chai3d::cShapeSphere* cursorAxisDev_tool;


};

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
