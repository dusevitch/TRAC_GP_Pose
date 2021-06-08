//==============================================================================
/*
    \author    David Usevitch
*/
//==============================================================================

#pragma once
//------------------------------------------------------------------------------
#include "Application.h"
//#include "toolarrows.cpp"
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
#include "functions.cpp"

double PI = 3.1415926;

//------------------------------------------------------------------------------
using namespace chai3d;
using namespace std;
using namespace Eigen;
using namespace arma;
//------------------------------------------------------------------------------

IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");


ApplicationWidget::ApplicationWidget (QWidget *parent)
{

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
    polaris->nGetTXTransforms(0);
    updateStaticMarkers();
    qDebug()<< "global base pos: "<< global_base_pose->pos.x() << ", " << global_base_pose->pos.y() << ", "<< global_base_pose->pos.z() ;

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
//    m_camera->set(global_base_pose->pos + global_base_pose->inv_rot_mat*cVector3d(0.0, 0.0, 1000.0),    // camera position (eye)
//                cVector3d(0.0, 0.0, 0.0),    // lookat position (target)
//                cVector3d(global_base_pose->pos.x(), 0.0, 0.0));   // direction of the (up) vector
    m_camera->set(global_base_pose->pos +global_base_pose->inv_rot_mat*cVector3d(250,100,1000), // camera position (eye)
                 global_base_pose->pos,    // lookat position (target)
                 global_base_pose->rot_mat.getCol0());   // direction of the (up) vector

    printVector3d(global_base_pose->rot_mat.getCol0(),"first column of vector3d matrix");

    // Get and print camera matrix in the polaris frame
    Eigen::Matrix4d camera_trans = buildTransMatrix(m_camera->getLocalRot(), m_camera->getLocalPos());
    //camera_trans_mat = buildStructfromTransMatrix(camera_trans); // Camera Struct
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
    // OBJECTS
    //--------------------------------------------------------------------------

//    // OMNIMAGNET BASE
    gpBlock_base = new chai3d::cMultiMesh();
    gp_base = new chai3d::cShapeSphere(0.05);
    gpAxisDev_base = new chai3d::cShapeSphere(0.01);
    // Add children to the main object sphere
    gp_base->addChild(gpAxisDev_base);
    gp_base->addChild(gpBlock_base);
    // add the object Sphere to the world
    m_world->addChild(gp_base);
    gp_base->setUseTransparency(true, false);
    gp_base->setTransparencyLevel(1);
    gp_base->setLocalPos(chai3d::cVector3d(0,0,0));
    gpAxisDev_base->setUseTransparency(true, false);
    gpAxisDev_base->setTransparencyLevel(1);
    gpBlock_base->loadFromFile("/home/telerobotics/src/TRAC_CI_Position/stl_devices/Omnimag_cube_stl_front.STL"); // TODO uncomment
    gpBlock_base->scale(1);
    gpBlock_base->setLocalPos(chai3d::cVector3d(0,0,0));
    gpBlock_base->setLocalRot(chai3d::cMatrix3d(1, 0, 0, 0)); // this formulation is vector for axis and radians angle.;
    gpBlock_base->setUseTransparency(true, true);
    gpBlock_base->setTransparencyLevel(.3);


//    //    // OMNIMAGNET
//    omniToolBlock = new chai3d::cMultiMesh();
//    omniTool = new chai3d::cShapeSphere(0.05);
//    omniToolAxisDev = new chai3d::cShapeSphere(0.01);
//    // Add children to the main object sphere
//    omniTool->addChild(omniToolAxisDev);
//    omniTool->addChild(omniToolBlock);
//    // add the object Sphere to the world
//    m_world->addChild(omniTool);
//    omniTool->setUseTransparency(true, false);
//    omniToolAxisDev->setUseTransparency(true, false);
//    omniToolBlock->loadFromFile("/home/telerobotics/src/TRAC_CI_Position/stl_devices/Omnimag_cube_stl_front.STL"); // TODO uncomment
//    omniToolBlock->scale(1);
//    omniToolBlock->setLocalPos(chai3d::cVector3d(0,0,0));
//    omniToolBlock->setLocalRot(chai3d::cMatrix3d(1, 0, 0, 0)); // this formulation is vector for axis and radians angle.;
//    omniToolBlock->setUseTransparency(true, true);

//    omniTool->setTransparencyLevel(0);
//    omniToolBlock->setTransparencyLevel(1);
//    omniToolAxisDev->setTransparencyLevel(0);


    // GUIDED OMNIMAGNET TOOL
    omniTool = new GuidedTool(m_world);
    omniTool->loadToolFile("/home/telerobotics/src/TRAC_CI_Position/json_files/omnimag_settings.json",0); // TODO Uncomment


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

    updateStaticMarkers();

    gp_base->setLocalPos(cVector3d(1000,1000,1000));


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
            //printVector3d(omnimag_pose->pos, "omnimag pos");
            //printVector3d(global_base_pose->pos, "global pos");

            if(base_flag==1){ // flag for phantom
                omniTool->updatePoseAlignment(gp_phantom_pose, omnimag_pose->pos, omnimag_pose->rot_mat, gpBlock_base, global_base_pose->rot_mat*mag_offset);
//                omniTool->updatePoseAlignment(gp_phantom_pose, omnimag_pose->pos, omnimag_pose->rot_mat, gpBlock_base, mag_offset);
            }else if (base_flag==2){ // Flag for actual cochlea
                omniTool->updatePoseAlignment(cochleaPose, omnimag_pose->pos, omnimag_pose->rot_mat, gpBlock_base, global_base_pose->rot_mat*mag_offset);
//                omniTool->updatePoseAlignment(cochleaPose, omnimag_pose->pos, omnimag_pose->rot_mat, gpBlock_base, mag_offset);
            }else{ // Neither phantom data or cochlea data loaded
                omniTool->setPosition(omnimag_pose->pos);
                omniTool->setOrientation(omnimag_pose->rot_mat);
            }

            // Update the positon/orientation of the cochlea path and field arrows
            if (base_flag!=0){
                cochlea_path->updateFieldPath(omnimag_pose);
            }

            // Get the pose data for the wand
            wand_pose = getPoseData(4);

            updateLCD(m_parent->ui.wand_x, m_parent->ui.wand_y, m_parent->ui.wand_z, wand_pose);
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


// TODO: camera pos -> back into the polaris frame, update the pos alignment back into the polaris frame -> any kind of sending of data, put into the polaris frame
// for updating!!!!!!


// CHANGE THE CAMERA ANGLE --> connect button to do this:
void ApplicationWidget::updateCamera_to_base(){
    if (base_flag==0){
        qDebug() << "ERROR: COULDN'T FIND LOADED BASE POSITION!!";
    }else{
        if (base_flag==1){ // the phantom position
            m_camera->set(gp_phantom_pose->pos +global_base_pose->rot_mat*cVector3d(0,0,1000), // camera position (eye)
                     gp_phantom_pose->pos,    // look at position (target)
                     global_base_pose->rot_mat.getCol0());   // direction of the (up) vector
        }else{ // the loaded gp file position
            m_camera->set(cochleaPose->pos +global_base_pose->rot_mat*cVector3d(0,0,1000), // camera position (eye)
                     cochleaPose->pos,    // look at position (target)
                     global_base_pose->rot_mat.getCol0());   // direction of the (up) vector
        }

//        // CAMERA SET FUNCTION
//        chai3d::cVector3d camera_position = chai3d::cVector3d(global_base_pose->pos.x(),global_base_pose->pos.y(),global_base_pose->pos.z()) +global_base_pose->inv_rot_mat*cVector3d(0,0,1000);
//        chai3d::cVector3d look_at_position = global_base_pose->pos;
//        chai3d::cVector3d direction_up = global_base_pose->rot_mat.getCol0();

//        m_camera->set(camera_position, look_at_position, direction_up);
    }
}


void ApplicationWidget::load_gp_file(){
    // File Dialog
    base_flag=2;

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

    cochleaPose->rot_mat = mat;
    cochleaPose->pos = Eigen::Vector3d(cochlea_pos[0], cochlea_pos[1], cochlea_pos[2]);

    m_parent->ui.co_pos_x->display( cochleaPose->pos.x());
    m_parent->ui.co_pos_y->display( cochleaPose->pos.y());
    m_parent->ui.co_pos_z->display( cochleaPose->pos.z());

    gp_base->setLocalPos(cochleaPose->pos + global_base_pose->rot_mat*mag_offset);
//    gp_base->setLocalPos(cochleaPose->pos +mag_offset);
    gp_base->setLocalRot(cochleaPose->rot_mat);

    loaded_file = fileNames[0];
}

void ApplicationWidget::load_gp_phantom(){
    gp_phantom_pose = getPoseData(3);
    base_flag=1;

    cMatrix3d mat = gp_phantom_pose->rot_mat;

    m_parent->ui.co_pos_x->display( gp_phantom_pose->pos.x());
    m_parent->ui.co_pos_y->display( gp_phantom_pose->pos.y());
    m_parent->ui.co_pos_z->display( gp_phantom_pose->pos.z());

    gp_base->setLocalPos(gp_phantom_pose->pos + global_base_pose->rot_mat*mag_offset);
    //gp_base->setLocalPos(gp_phantom_pose->pos + mag_offset);
    gp_base->setLocalRot(mat);

    //cochlea_path = new CochleaPath("phantom_b_vectors_normalized_left.csv", gp_phantom_pose->pos, m_world, omnimag_pose->rot_mat,global_base_pose->rot_mat);
    cochlea_path = new CochleaPath("FIELDS/phantom_scaled_values.csv", gp_phantom_pose->pos, m_world, omnimag_pose, mag_offset);

}


void ApplicationWidget::updateStaticMarkers(){
    global_base_pose = getPoseData(2, true);
}

// Gets raw Polaris Data
polarisTransformMatrix* ApplicationWidget::getPoseData(int polaris_num, bool global_flag){
    polarisTransformMatrix* pose_struct = new polarisTransformMatrix(); // output struct

    if (polaris->m_dtHandleInformation[polaris_num].Xfrms.ulFlags == TRANSFORM_VALID ) {
        // Get the position and rotation values from the polaris and store
        Position3d pos_t = polaris->m_dtHandleInformation[polaris_num].Xfrms.translation;
        QuatRotation quatRot = polaris->m_dtHandleInformation[polaris_num].Xfrms.rotation;
        RotationMatrix rot;
        CvtQuatToRotationMatrix(&quatRot, rot);
        Eigen::Matrix4d curr_trans;

//        // Change all coordinates into the given frame, except if you are getting the global coordinates
//        if (!global_flag){

//            // Rebuild the transformation matrix using a rotation into the base frame
//            Eigen::Matrix3d curr_rot;
//            curr_rot << rot[0][0], rot[0][1], rot[0][2],
//                        rot[1][0], rot[1][1], rot[1][2],
//                        rot[2][0], rot[2][1], rot[2][2];
//            Eigen::Vector3d curr_pos = Eigen::Vector3d(pos_t.x,pos_t.y,pos_t.z);


//            Eigen::Matrix3d global_ROT_mat = chai3dToMatrix3d(global_base_pose->rot_mat);

//            // Transform into the global frame
//            Eigen::Matrix3d rot_adjusted = global_ROT_mat*curr_rot;
//            Eigen::Vector3d pos_adjusted = global_ROT_mat*curr_pos;

//            // Generate the transformation matrix
//            curr_trans << rot_adjusted(0,0), rot_adjusted(0,1), rot_adjusted(0,2), pos_adjusted.x(),
//                        rot_adjusted(1,0), rot_adjusted(1,1), rot_adjusted(1,2), pos_adjusted.y(),
//                        rot_adjusted(2,0), rot_adjusted(2,1), rot_adjusted(2,2), pos_adjusted.z(),
//                        0.0      , 0.0      , 0.0      , 1.0;
//        }else{


            curr_trans << rot[0][0], rot[0][1], rot[0][2], pos_t.x,
                          rot[1][0], rot[1][1], rot[1][2], pos_t.y,
                          rot[2][0], rot[2][1], rot[2][2], pos_t.z,
                          0.0      , 0.0      , 0.0      , 1.0;
//        }

        pose_struct = buildStructfromTransMatrix(curr_trans, polaris_num);
    }else{
        //qDebug() << "TRACKER NOT IN RANGE";
    }
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


void ApplicationWidget::updateLCD(QLCDNumber* x_val, QLCDNumber* y_val, QLCDNumber* z_val, polarisTransformMatrix* pose){
    if (polaris->m_dtHandleInformation[pose->polaris_num].Xfrms.ulFlags == TRANSFORM_VALID ) {
        x_val->display(pose->pos.x());
        y_val->display(pose->pos.y());
        z_val->display(pose->pos.z());
    }else{
        x_val->display(-1000);
        y_val->display(-1000);
        z_val->display(-1000);
    }
}



//multiply above by global inv rot mat
