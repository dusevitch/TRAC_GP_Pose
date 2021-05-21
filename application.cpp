//==============================================================================
/*
    \author    David Usevitch
*/
//==============================================================================

//------------------------------------------------------------------------------
#include "Application.h"
//------------------------------------------------------------------------------
#include <QFile>

#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
#include "Eigen/Dense"
#include <unsupported/Eigen/MatrixFunctions>
#include <math.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <QFileDialog>

double PI = 3.1415926;

//------------------------------------------------------------------------------
using namespace chai3d;
using namespace std;
using namespace Eigen;
using namespace arma;
//------------------------------------------------------------------------------

IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
// Local Functions used by the Class
void printMatrix3d(chai3d::cMatrix3d matrix, std::string name);
void printVector3d(chai3d::cVector3d vec, QString name);
Eigen::Matrix4d inverseTransformationMatrix(const Eigen::Matrix4d &trans_mat);
polarisTransformMatrix* buildStructfromTransMatrix(Eigen::Matrix4d &trans_mat);
void breakTransMat(Eigen::Matrix4d &trans_mat, chai3d::cMatrix3d &rot, chai3d::cVector3d &pos);
Eigen::Matrix4d buildTransMatrix(chai3d::cMatrix3d rot, chai3d::cVector3d pos);


ApplicationWidget::ApplicationWidget (QWidget *parent)
{
    //--------------------------------------------------------------------------
    // INITIALIZATION
    //--------------------------------------------------------------------------


    // initialize variables
    m_parent  = (Interface*)(void*)parent;
    m_running = false;
    m_timerID = 0;
    m_mouseMoveCamera = false;

    // reset frequency counters
    m_graphicRate.reset();
    m_hapticRate.reset();


    //--------------------------------------------------------------------------
    // WORLD - CAMERA - LIGHTING
     // create a new world.
    m_world = new cWorld();

    // set the background color of the environment
    m_world->m_backgroundColor.setBlack();

    // create a camera and insert it into the virtual world
    m_camera = new cCamera(m_world);
    m_world->addChild(m_camera);
    m_camera->set(cVector3d(0.0, 0.0, 1000.0),    // camera position (eye)
                cVector3d(0.0, 0.0, 0.0),    // lookat position (target)
                cVector3d(1.0, 0.0, 0.0));   // direction of the (up) vector

    // Get and print camera matrix in the polaris frame
    Eigen::Matrix4d camera_trans = buildTransMatrix(m_camera->getLocalRot(), m_camera->getLocalPos());
    camera_trans_mat = buildStructfromTransMatrix(camera_trans); // Camera Struct
//    qDebug() << "Camera 3d matrix: ";
//    printMatrix3d(m_camera->getLocalRot(), "Camera");
//    printVector3d(m_camera->getLocalPos(), "CAMERA");


    // set the near and far clipping planes of the camera
    m_camera->setClippingPlanes (0.01, 10000.0);

    // create a light source
    m_light = new cDirectionalLight (m_world);

    // add light to camera
    m_camera->addChild(m_light);

    // enable light source
    m_light->setEnabled(true);

    // define the direction of the light beam
    m_light->setDir(-1.0,-1.0,-0.5);

    //--------------- TEST TEST TESTSTESTSTESTE --------------------------

    //--------------------------------------------------------------------------
    // HAPTIC DEVICES / TOOLS
    //--------------------------------------------------------------------------


    //--------------------------------------------------------------------------
    // WIDGETS
    //--------------------------------------------------------------------------


    //--------------------------------------------------------------------------
    // Polaris Spectra Device
    //--------------------------------------------------------------------------

    // create a haptic device handler
    polaris = new PolarisSpectra();

    if (polaris_on){


        // initialize the polaris system
        polaris->Initialize();

        // activate all the ports
        if (polaris->nActivateAllPorts())
            std::cout << "Tools have been activated!" << endl;

        // Start the Polaris system tracking
        if (polaris->nStartTracking() == REPLY_OKAY){
            std::cout << "Tracking has started!" << endl;}
        else{std::cout << "Device could not start tracking!" << endl;}
    }

    //--------------------------------------------------------------------------
    // OBJECTS
    //--------------------------------------------------------------------------

//    // OMNIMAGNET BASE
    cursorBlock_base = new chai3d::cMultiMesh();
    cursor_base = new chai3d::cShapeSphere(0.05);
    cursorAxisDev_base = new chai3d::cShapeSphere(0.01);
    // Add children to the main object sphere
    cursor_base->addChild(cursorAxisDev_base);
    cursor_base->addChild(cursorBlock_base);
    // add the object Sphere to the world
    m_world->addChild(cursor_base);
    cursor_base->setUseTransparency(true, false);
    cursor_base->setTransparencyLevel(1);
    cursor_base->setLocalPos(chai3d::cVector3d(0,0,0));
    cursorAxisDev_base->setUseTransparency(true, false);
    cursorAxisDev_base->setTransparencyLevel(1);
    cursorBlock_base->loadFromFile("/home/telerobotics/src/TRAC_CI_Position/stl_devices/OmniMag_ROM_STL_TXT/Omnimag_stl_cube_core.STL"); // TODO uncomment
    cursorBlock_base->scale(1);
    cursorBlock_base->setLocalPos(chai3d::cVector3d(0,0,0));
    cursorBlock_base->setLocalRot(chai3d::cMatrix3d(1, 0, 0, 0)); // this formulation is vector for axis and radians angle.;
    cursorBlock_base->setUseTransparency(true, true);
    cursorBlock_base->setTransparencyLevel(.3);

    cursor_base_matrix = new polarisTransformMatrix();
    cursor_base_matrix->pos= chai3d::cVector3d(0,0,0);// TODO FINISH THIS!



    //    // OMNIMAGNET TOOL
//        cursorBlock_tool = new chai3d::cMultiMesh();
//        cursor_tool = new chai3d::cShapeSphere(0.05);
//        cursorAxisDev_tool = new chai3d::cShapeSphere(0.01);
//        // Add children to the main object sphere
//        cursor_tool->addChild(cursorAxisDev_tool);
//        cursor_tool->addChild(cursorBlock_tool);
//        // add the object Sphere to the world
//        m_world->addChild(cursor_tool);
//        cursor_tool->setUseTransparency(true, false);
//        cursor_tool->setTransparencyLevel(1);
//        cursor_tool->setLocalPos(chai3d::cVector3d(0,0,0));
//        cursorAxisDev_tool->setUseTransparency(true, false);
//        cursorAxisDev_tool->setTransparencyLevel(1);
//        cursorBlock_tool->loadFromFile("/home/telerobotics/src/TRAC_CI_Position/stl_devices/OmniMag_ROM_STL_TXT/Omnimag_stl_cube_core.STL");
//        cursorBlock_tool->scale(1);
//        cursorBlock_tool->setLocalPos(chai3d::cVector3d(0,0,0));
//        cursorBlock_tool->setLocalRot(chai3d::cMatrix3d(1, 0, 0, 0)); // this formulation is vector for axis and radians angle.;
//        cursorBlock_tool->setUseTransparency(true, false);
//        cursorBlock_tool->setTransparencyLevel(1);

//        omnimagBase = new GuidedTool(m_world);
//    omnimagBase->loadToolFile("/home/telerobotics/src/TRAC_CI_Position/json_files/omnimag_settings.json",0);
//    printVector3d(omnimagBase->cursor->getLocalPos(), "Omnimag Base");

    // GUIDED OMNIMAGNET TOOL
    omniTool = new GuidedTool(m_world);
    omniTool->loadToolFile("/home/telerobotics/src/TRAC_CI_Position/json_files/omnimag_settings.json",0); // TODO Uncomment

    //cornerViews = new CornerViews(omniTool, m_world, m_camera);
    //printVector3d(omniTool->cursor->getLocalPos(), "Omnimag Tool");

    //printMatrix3d(m_camera->getLocalRot(), "Camera");


    // Set the initial pos of the magnets
    int init_pos_flag = 0;
//    omniTool->cursor->setLocalPos(cVector3d(0.0, 0.0, 0.0));
//    omniTool->cursor->setLocalRot(cMatrix3d(1, 0, 0, 0 ));
//    omnimagBase->cursor->setLocalPos(cube_pose->pos);
//    omnimagBase->cursor->setLocalRot(cube_pose->rot_mat);
}

//------------------------------------------------------------------------------

ApplicationWidget::~ApplicationWidget ()
{
    delete m_world;
}

//------------------------------------------------------------------------------

void* ApplicationWidget::hapticThread ()
{
    polaris->nGetTXTransforms(0); // Get the current transformation information from the Polaris system
    // acquire run lock
    m_runLock.acquire();

    // update state
    m_running = true;

    int counter = 0;



    polaris->nGetTXTransforms(0);
    updateStaticMarkers();



    printVector3d(cube_pose->pos, "Cube Position");
    cursor_base->setLocalPos(cube_pose->pos + (cube_pose->inv_rot_mat*cVector3d(0,0,-200)));
//    cursor_base->setLocalPos(cube_pose->pos + (cube_pose->inv_rot_mat*cVector3d(0,200,0)));
    cursor_base_matrix->pos=cube_pose->pos + (cube_pose->inv_rot_mat*cVector3d(0,0,-200));
    cursor_base->setLocalRot(cube_pose->rot_mat); // this formulation is vector for axis and radians angle.;

    while (m_running)
    {

        // compute global reference frames for each object
        m_world->computeGlobalPositions(true);

        // update frequency counter
        m_hapticRate.signal(1);

        //----------------------------------------------------------------
        // READ POLARIS DEVICE
        //----------------------------------------------------------------

        if (polaris_on){ // If tracker is off
            polaris->nGetTXTransforms(0); // Get the current transformation information from the Polaris system


            // omni_pose update position
            omnimag_pose = getPoseData(1);


            omniTool->cursor->setLocalPos(omnimag_pose->pos);
            omniTool->cursor->setLocalRot(omnimag_pose->rot_mat);
//            omniTool->updatePoseAlignment(cursor_base_matrix, cursor_base->getLocalPos(), cursor_base->getLocalRot(), omnimag_pose->pos, omnimag_pose->rot_mat);
            omniTool->updatePoseAlignment(cursor_base_matrix, omnimag_pose->pos, omnimag_pose->rot_mat, cursorBlock_base);
//            printMatrix3d(omnimag_pose->rot_mat, "cursorMat");
//            printMatrix3d(cursor_base_matrix->rot_mat, "baseomnimag");
        }

//        printVector3d(omnimag_pose->pos, "Omnimag cur_Position");

        m_parent->updateLCDpos();

    }

    // update state
    m_running = false;

    // release run lock
    m_runLock.release();

    // exit thread
    return (NULL);
}


// CHANGE THE CAMERA ANGLE --> connect button to do this:
void ApplicationWidget::updateCamera_to_base(){

//        chai3d::cMatrix3d b_R_v = global_base_pose->inv_rot_mat*camera_trans_mat->rot_mat; // The rotation matrix of the camera view in the base frame
//        m_camera->setLocalRot(b_R_v); // align the camera with the base frame
//        m_camera->setLocalPos(chai3d::cVector3d(cube_tool_position.x(),cube_tool_position.y(),cube_tool_position.z()) + chai3d::cVector3d(0,-70,700));


        // CAMERA SET FUNCTION
        chai3d::cVector3d camera_position = chai3d::cVector3d(cube_pose->pos.x(),cube_pose->pos.y(),cube_pose->pos.z()) + 600*(global_base_pose->rot_mat.getCol2());
        chai3d::cVector3d look_at_position = chai3d::cVector3d(cube_pose->pos.x(),cube_pose->pos.y(),cube_pose->pos.z());
        chai3d::cVector3d direction_up = cube_pose->rot_mat.getCol0();

        m_camera->set(camera_position, look_at_position, direction_up);


//        //------------------ DEBUG ---------------------
//        qDebug()<< "TEST DEBUG";
//        printVector3d(camera_position, "camera_position");
//        printVector3d( (100*(global_base_pose->rot_mat.getCol2())), "camera_position added vector");
//        printVector3d(look_at_position, "look_at_position");
//        printVector3d(direction_up, "direction_up");

//        printMatrix3d(m_camera->getLocalRot(), "Camera Rot");
//        printVector3d(m_camera->getLocalPos(), "Camera POS");
//        printVector3d(cube_pose->pos, "Base");

}


void ApplicationWidget::load_gp_file(){
    // File Dialog

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    QFile file(fileNames[0]);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       return;

    // Load and read the file
    QTextStream in(&file);
    int counter =0;

    std::vector<Eigen::Vector3d> input_trans_mat;
    std::vector<double> cochlea_pos;

    while (!in.atEnd()) {

        QString full_line = in.readLine();
        QStringList line = full_line.split(',');
        if (counter < 4){
            input_trans_mat.push_back(Eigen::Vector3d(line[0].toDouble(),line[1].toDouble(),line[2].toDouble()));
            cochlea_pos.push_back(line[3].toDouble());
        }else{
            Eigen::Vector3d pos = Eigen::Vector3d(line[0].toDouble(),line[1].toDouble(),line[2].toDouble());
            Eigen::Vector3d field = Eigen::Vector3d(line[3].toDouble(),line[4].toDouble(),line[5].toDouble());

            cochlea_path_pos_points.push_back(pos);
            cochlea_path_field_points.push_back(field);
        }
        counter++;
    }

    // Create the cochleaPos matrix
    Eigen::Matrix3d mat;
    mat << input_trans_mat[0][0],input_trans_mat[0][1],input_trans_mat[0][2],
            input_trans_mat[1][0],input_trans_mat[1][1],input_trans_mat[1][2],
            input_trans_mat[2][0],input_trans_mat[2][1],input_trans_mat[2][2];

    cochleaPose.rot_mat = mat;
    cochleaPose.pos = Eigen::Vector3d(cochlea_pos[0], cochlea_pos[1], cochlea_pos[2]);

    loaded_file = fileNames[0];

}


void ApplicationWidget::updateStaticMarkers(){
    global_base_pose = getPoseData(2);
    cube_pose = getPoseData(3);

    // Copy the cube_pose rotation data
    chai3d::cMatrix3d rot_mat_temp;
    rot_mat_temp.copyfrom(cube_pose->rot_mat);
    cursor_base_matrix->rot_mat=rot_mat_temp;
//    printMatrix3d(cube_pose->rot_mat, "cube_pose rot mat");
//    printMatrix3d(rot_mat_temp, "rot mat temp");
//    printMatrix3d(cursor_base_matrix->rot_mat, "cursor_base_matrix");


}

polarisTransformMatrix* ApplicationWidget::getPoseData(int polaris_num){
    polarisTransformMatrix* pose_struct = new polarisTransformMatrix(); // output struct

    if (polaris->m_dtHandleInformation[polaris_num].Xfrms.ulFlags == TRANSFORM_VALID ) {
        // Get the position and rotation values from the polaris and store
        Position3d pos_t = polaris->m_dtHandleInformation[polaris_num].Xfrms.translation;
        QuatRotation quatRot = polaris->m_dtHandleInformation[polaris_num].Xfrms.rotation;
        RotationMatrix rot;
        CvtQuatToRotationMatrix(&quatRot, rot);
        Eigen::Matrix4d curr_trans;
        curr_trans << rot[0][0], rot[0][1], rot[0][2], pos_t.x,
                      rot[1][0], rot[1][1], rot[1][2], pos_t.y,
                      rot[2][0], rot[2][1], rot[2][2], pos_t.z,
                      0.0      , 0.0      , 0.0      , 1.0;
        pose_struct = buildStructfromTransMatrix(curr_trans);
    }else{
        //qDebug() << "TRACKER NOT IN RANGE";
    }
    return pose_struct;
    delete pose_struct;
}

Eigen::Matrix4d inverseTransformationMatrix(const Eigen::Matrix4d &trans_mat){
    // Remove the rotation and position matrices
    Eigen::Matrix3d rot = trans_mat.topLeftCorner(3,3);
    Eigen::Vector4d pos = trans_mat.col(3);

    // transpose of the rotation
    Eigen::Matrix3d rot_t = rot.transpose();

    // Generate inverse transformation matrix and return
    Eigen::Vector3d inv_pos = -rot_t*pos.head(3);
    Eigen::Matrix4d inv_trans_mat;
    inv_trans_mat << rot_t(0,0), rot_t(0,1), rot_t(0,2), inv_pos(0),
                     rot_t(1,0), rot_t(1,1), rot_t(1,2), inv_pos(1),
                     rot_t(2,0), rot_t(2,1), rot_t(2,2), inv_pos(2),
                     0,           0,           0,           1;

    return inv_trans_mat;
}

polarisTransformMatrix* buildStructfromTransMatrix(Eigen::Matrix4d &trans_mat){
    polarisTransformMatrix* pose_struct = new polarisTransformMatrix();

    // Rotation
    Eigen::Matrix3d rot_eig = trans_mat.topLeftCorner(3,3);
    pose_struct->rot_mat = chai3d::cMatrix3d(rot_eig(0,0), rot_eig(0,1),rot_eig(0,2),rot_eig(1,0),rot_eig(1,1),rot_eig(1,2),rot_eig(2,0),rot_eig(2,1),rot_eig(2,2));

    // Inverse Rotation
    chai3d::cMatrix3d inv_rot_mat;
    inv_rot_mat.copyfrom(pose_struct->rot_mat); //copy
    inv_rot_mat.trans();
    pose_struct->inv_rot_mat = inv_rot_mat;

    //Position
    Eigen::Vector4d pos_vec = trans_mat.col(3);
    pose_struct->pos = cVector3d(pos_vec(0), pos_vec(1), pos_vec(2));

    // Transformation matrix and Inverse Transformation matrix
    pose_struct->trans_mat = trans_mat;
    pose_struct->inv_trans_mat = inverseTransformationMatrix(trans_mat);

    // Return and delete
    return pose_struct;
    delete pose_struct;
}

//------------------------------------------------------------------------------

void ApplicationWidget::initializeGL ()
{
#ifdef GLEW_VERSION
    glewInit ();
#endif
}

//------------------------------------------------------------------------------

void ApplicationWidget::paintGL ()
{
    if (!m_running) return;

    m_worldLock.acquire();

    // render world
    m_camera->renderView(m_width, m_height);

    // wait until all GL commands are completed
    glFinish();

    m_graphicRate.signal(1);

    m_worldLock.release();
}

//------------------------------------------------------------------------------

void ApplicationWidget::resizeGL (int a_width,  int a_height)
{
    m_worldLock.acquire ();

    m_width = a_width;
    m_height = a_height;

    m_worldLock.release ();
}

//------------------------------------------------------------------------------

int ApplicationWidget::start ()
{
    // start graphic rendering
    m_timerID = startTimer(20);

    // start haptic thread
    m_thread.start (_hapticThread, CTHREAD_PRIORITY_HAPTICS, this);

    return(0);
}

//------------------------------------------------------------------------------

int ApplicationWidget::stop ()
{
    // stop the simulation thread and wait it to join
    m_running = false;
    m_runLock.acquire();
    m_runLock.release();

    // close polaris device
    polaris->close();
    if (polaris)
        delete polaris;

    killTimer (m_timerID);

    return 0;
}


//------------------------------------------------------------------------------

void _hapticThread (void *arg)
{
    ((ApplicationWidget*)arg)->hapticThread();
}

//------------------------------------------------------------------------------


void printMatrix3d(chai3d::cMatrix3d matrix, std::string name)
{
    std::cout << "-------MATRIX: "<< name << " :---- " << std::endl;
    std::cout << matrix.getCol0().x() << ", " << matrix.getCol1().x() << ", " << matrix.getCol2().x() << std::endl;
    std::cout << matrix.getCol0().y() << ", " << matrix.getCol1().y() << ", " << matrix.getCol2().y() << std::endl;
    std::cout << matrix.getCol0().z() << ", " << matrix.getCol1().z() << ", " << matrix.getCol2().z() << std::endl;
    std::cout << "----------------" << std::endl;
}

void printVector3d(chai3d::cVector3d vec, QString name)
{
    //qDebug() << "Pos of " <<  name <<  " X: " << vec.x() << " Y: " << vec.y() << " Z: " << vec.z();
    std::cout << "Pos of " <<  name.toStdString() <<  " X: " << vec.x() << " Y: " << vec.y() << " Z: " << vec.z() << std::endl;;
}

Eigen::Matrix4d buildTransMatrix(chai3d::cMatrix3d rot, chai3d::cVector3d pos){
    Eigen::Matrix4d trans_mat;

    trans_mat << rot(0,0), rot(0,1), rot(0,2), pos(0),
                 rot(1,0), rot(1,1), rot(1,2), pos(1),
                 rot(2,0), rot(2,1), rot(2,2), pos(2),
                 0,           0,           0,      1;
    return trans_mat;
}

void breakTransMat(Eigen::Matrix4d &trans_mat, chai3d::cMatrix3d rot, chai3d::cVector3d pos){
    // Rotation Matrix
    Eigen::Matrix3d rot_eig = trans_mat.topLeftCorner(3,3);
    rot = chai3d::cMatrix3d(rot_eig(0,0), rot_eig(0,1),rot_eig(0,2),rot_eig(1,0),rot_eig(1,1),rot_eig(1,2),rot_eig(2,0),rot_eig(2,1),rot_eig(2,2));

    // Position Vector
    pos = chai3d::cVector3d(rot_eig(3,0), rot_eig(3,1), rot_eig(3,2));
}
