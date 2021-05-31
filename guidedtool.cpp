#include "guidedtool.h"
#include <QString>
#include <QDebug>
#include <polaristransformmatrix.h>
#include <math.h>
#include <cstdlib>

/// ------------------------------------------------------------------------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------------------------------------------------------------------------
///   GUIDED TOOL CONSTRUCTOR AND METHODS:
/// ------------------------------------------------------------------------------------------------------------------------------------------------------
/// ------------------------------------------------------------------------------------------------------------------------------------------------------

// Methods Declared before called:
void EigenToArmadillo(const chai3d::cMatrix3d& Mat, arma::mat& Matrix);
//void printMatrix3d(chai3d::cMatrix3d mat);
void printArmadilloMatrix(arma::mat matrix);

//Constructor
GuidedTool::GuidedTool(chai3d::cWorld *world)
{

    cursorBlock = new chai3d::cMultiMesh();
    cursor = new chai3d::cShapeSphere(0.05);
    cursorAxisDev = new chai3d::cShapeSphere(0.01);
    // Add children to the main object sphere
    cursor->addChild(cursorAxisDev);
    cursor->addChild(cursorBlock);
    // add the object Sphere to the world
    world->addChild(cursor);
    cursor->setUseTransparency(true, false);
    cursorAxisDev->setUseTransparency(true, false);
//    cursorBlock->loadFromFile("/home/telerobotics/src/TRAC_CI_Position/stl_devices/Omnimag_cube_stl_front.STL"); // TODO uncomment
//    cursorBlock->scale(1);
//    cursorBlock->setLocalPos(chai3d::cVector3d(0,0,0));
//    cursorBlock->setLocalRot(chai3d::cMatrix3d(1, 0, 0, 0)); // this formulation is vector for axis and radians angle.;
//    cursorBlock->setUseTransparency(true, true);

    cursor->setTransparencyLevel(0);
//    cursorBlock->setTransparencyLevel(1);
    cursorAxisDev->setTransparencyLevel(0);

//    cursor->setLocalPos(chai3d::cVector3d(0,0,0));

    arrowZ = new chai3d::cMesh();
    arrowY = new chai3d::cMesh();
    arrowX = new chai3d::cMesh();
    arrow_reverseZ = new chai3d::cMesh();
    arrow_reverseY = new chai3d::cMesh();
    arrow_reverseX = new chai3d::cMesh();

    circ_arrowZ = new chai3d::cMesh();
    circ_arrowY = new chai3d::cMesh();
    circ_arrowX = new chai3d::cMesh();
    circ_arrow_reverseZ = new chai3d::cMesh();
    circ_arrow_reverseY = new chai3d::cMesh();
    circ_arrow_reverseX = new chai3d::cMesh();

    // degree value for 1 degree
    deg_val = 0.017453292519943; // 1 degree corresponding k val


    // Initialize no arrow selected
    circ_or_straight=0; // Start with rotational arrow cues
    arrow_guidance_selected=0;

}

chai3d::cVector3d GuidedTool::getcVector3d(Json::Value val){
    double x_val = val["X"].asDouble();
    double y_val = val["Y"].asDouble();
    double z_val = val["Z"].asDouble();
    chai3d::cVector3d vec = chai3d::cVector3d(x_val, y_val, z_val);
    return vec;

}

bool GuidedTool::loadToolFile(std::string filename, int cornerViewsFlag)
{
    json_file = filename;

    // We use jsoncpp library to import JSON file for each tool
    std::ifstream ifs(filename);
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);     // Reader can also read strings

    // ---------------------------------------------------------
    //  Tool File Loading Parameters
    // ---------------------------------------------------------

//    std::cout << "NAME: " << obj["NAME"].asString() << std::endl;

    stl_file = obj["stl_file"].asString();
    stl_scale_value = obj["scale_factor"].asDouble();


    if (cornerViewsFlag ==0){

        // Get Threshold values
        trans_epsilon = obj["trans_epsilon"].asDouble();
        rot_epsilon = obj["rot_epsilon"].asDouble()*deg_val;
        std::cout << "rot epsilon: " << rot_epsilon << std::endl;
        // Straight Arrow Local Positions
        x_forward_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["X_Forward"]["localPosition"]);
        x_forward_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["X_Forward"]["scale"]);
        x_reverse_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["X_Reverse"]["localPosition"]);
        x_reverse_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["X_Reverse"]["scale"]);
        y_forward_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["Y_Forward"]["localPosition"]);
        y_forward_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["Y_Forward"]["scale"]);
        y_reverse_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["Y_Reverse"]["localPosition"]);
        y_reverse_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["Y_Reverse"]["scale"]);
        z_forward_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["Z_Forward"]["localPosition"]);
        z_forward_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["Z_Forward"]["scale"]);
        z_reverse_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["Z_Reverse"]["localPosition"]);
        z_reverse_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["Z_Reverse"]["scale"]);

        // Circular Arrow Local Positions
        x_forward_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["X_Forward"]["localPosition"]);
        x_forward_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["X_Forward"]["scale"]);
        x_reverse_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["X_Reverse"]["localPosition"]);
        x_reverse_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["X_Reverse"]["scale"]);
        y_forward_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["Y_Forward"]["localPosition"]);
        y_forward_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["Y_Forward"]["scale"]);
        y_reverse_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["Y_Reverse"]["localPosition"]);
        y_reverse_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["Y_Reverse"]["scale"]);
        z_forward_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["Z_Forward"]["localPosition"]);
        z_forward_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["Z_Forward"]["scale"]);
        z_reverse_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["Z_Reverse"]["localPosition"]);
        z_reverse_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["Z_Reverse"]["scale"]);

    }else {
        // CORNER VIEWS UPDATE

        // Get Corner positions/scale/rotations
        corner_views_scale = obj["Corner_Views_Config"]["scale"].asDouble();
        views_rot_deg = obj["Corner_Views_Config"]["rot_deg"].asDouble();
        top_left_position = getcVector3d(obj["Corner_Views_Config"]["Top_Left"]["localPosition"]);
        top_left_rot = getcVector3d(obj["Corner_Views_Config"]["Top_Left"]["rot"]);
        top_right_position = getcVector3d(obj["Corner_Views_Config"]["Top_Right"]["localPosition"]);
        top_right_rot = getcVector3d(obj["Corner_Views_Config"]["Top_Right"]["rot"]);
        bottom_left_position = getcVector3d(obj["Corner_Views_Config"]["Bottom_Left"]["localPosition"]);
        bottom_left_rot = getcVector3d(obj["Corner_Views_Config"]["Bottom_Left"]["rot"]);
        bottom_right_position = getcVector3d(obj["Corner_Views_Config"]["Bottom_Right"]["localPosition"]);
        bottom_right_rot = getcVector3d(obj["Corner_Views_Config"]["Bottom_Right"]["rot"]);

        // Straight Arrow Local Positions
        x_forward_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["X_Forward"]["localPosition"]);
        x_forward_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["X_Forward"]["scale"])*arrow_scale;
        x_reverse_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["X_Reverse"]["localPosition"]);
        x_reverse_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["X_Reverse"]["scale"])*arrow_scale;
        y_forward_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["Y_Forward"]["localPosition"]);
        y_forward_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["Y_Forward"]["scale"])*arrow_scale;
        y_reverse_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["Y_Reverse"]["localPosition"]);
        y_reverse_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["Y_Reverse"]["scale"])*arrow_scale;
        z_forward_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["Z_Forward"]["localPosition"]);
        z_forward_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["Z_Forward"]["scale"])*arrow_scale;
        z_reverse_s_pos = getcVector3d(obj["Straight_Arrows_Config"]["Z_Reverse"]["localPosition"]);
        z_reverse_s_scale = getcVector3d(obj["Straight_Arrows_Config"]["Z_Reverse"]["scale"])*arrow_scale;


        // Circular Arrow Local Positions
        x_forward_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["X_Forward"]["localPosition"]);
        x_forward_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["X_Forward"]["scale"])*arrow_scale;
        x_reverse_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["X_Reverse"]["localPosition"]);
        x_reverse_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["X_Reverse"]["scale"])*arrow_scale;
        y_forward_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["Y_Forward"]["localPosition"]);
        y_forward_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["Y_Forward"]["scale"])*arrow_scale;
        y_reverse_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["Y_Reverse"]["localPosition"]);
        y_reverse_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["Y_Reverse"]["scale"])*arrow_scale;
        z_forward_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["Z_Forward"]["localPosition"]);
        z_forward_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["Z_Forward"]["scale"])*arrow_scale;
        z_reverse_c_pos = getcVector3d(obj["Circular_Arrows_Config"]["Z_Reverse"]["localPosition"]);
        z_reverse_c_scale = getcVector3d(obj["Circular_Arrows_Config"]["Z_Reverse"]["scale"])*arrow_scale;

    }

    // Colors for Arrows
    chai3d::cColorf color1, color2, color3;
    color1.setWhiteColorblind();
    color2.setGreenColorblind();
    color3.setPurpleColorblind();

    createTool();

    // Rotate about the initial offset;
    //cursorBlock->setLocalRot(chai3d::cRotEulerDeg(init_offset_rot.x(),init_offset_rot.y(),init_offset_rot.z(), chai3d::C_EULER_ORDER_XYZ));

}

void GuidedTool::setColor(std::string color)
{
    chai3d::cColorf gray, green, red;
    gray.setGray();
    green.setGreen();
    red.setRed();

    if (color == "gray"){
        cursorBlock->getMesh(0)->m_material->setColor(gray);
    }else if (color == "green"){
        cursorBlock->getMesh(0)->m_material->setColor(green);
    }else if (color == "red"){
        cursorBlock->getMesh(0)->m_material->setColor(red);
    }

}

void GuidedTool::initializeArrows()
{
    arrow_flag=0;
    //-----------------------------ROTATION MATRIX DEFINITIONS-------------------------------

    double angle = 90 * (PI / 180);
    chai3d::cMatrix3d x_rot = chai3d::cMatrix3d(1, 0, 0,
                                              0, cos(angle), -sin(angle),
                                              0, sin(angle), cos(angle) );
    chai3d::cMatrix3d y_rot = chai3d::cMatrix3d(cos(angle), 0, sin(angle),
                                                0, 1, 0,
                                                -sin(angle), 0, cos(angle));
    chai3d::cMatrix3d z_rot = chai3d::cMatrix3d(cos(angle), -sin(angle), 0,
                                                sin(angle), cos(angle), 0,
                                                0, 0, 1);

    //------------------------------STRAIGHT ARROWS -----------------------------------------
    // Create the Arrows
//    chai3d::cCreateArrow(arrowX);
//    chai3d::cCreateArrow(arrowY);
//    chai3d::cCreateArrow(arrowZ);
//    chai3d::cCreateArrow(arrow_reverseX);
//    chai3d::cCreateArrow(arrow_reverseY);
//    chai3d::cCreateArrow(arrow_reverseZ);

//    cMesh *a_mesh,
//            const double &a_length=0.4,
//            const double &a_radiusShaft=0.01,
//            const double &a_lengthTip=0.1,
//            const double &a_radiusTip=0.03,
//            const bool a_includeTipsAtBothExtremities=false,
//            const unsigned int a_numSides=32,
//            const cVector3d &a_direction=cVector3d(0, 0, 1),
//            const cVector3d &a_pos=cVector3d(0, 0, 0),;
//            const cColorf &a_color=cColorf(1.0, 1.0, 1.0, 1.0)

        chai3d::cCreateArrow(       arrowX, 0.55, 0.05, 0.2, 0.12, false, 32, chai3d::cVector3d(-1,0.001,0), x_forward_s_pos);
        chai3d::cCreateArrow(       arrowY, 0.55, 0.05, 0.2, 0.12, false, 32, chai3d::cVector3d(0.001,-1,0), y_forward_s_pos);
        chai3d::cCreateArrow(       arrowZ, 0.55, 0.05, 0.2, 0.12, false, 32, chai3d::cVector3d(0,0.001,1), z_forward_s_pos);
        chai3d::cCreateArrow(arrow_reverseX, 0.55, 0.05, 0.2, 0.12, false, 32, chai3d::cVector3d(1, 0.001, 0), x_reverse_s_pos);
        chai3d::cCreateArrow(arrow_reverseY, 0.55, 0.05, 0.2, 0.12, false, 32, chai3d::cVector3d(0.001,1,0), y_reverse_s_pos);
        chai3d::cCreateArrow(arrow_reverseZ, 0.55, 0.05, 0.2, 0.12, false, 32, chai3d::cVector3d(0,0,-1), z_reverse_s_pos);

    //Add arrows to the axis Dev
        cursorAxisDev->addChild(arrowX);
        cursorAxisDev->addChild(arrowY);
        cursorAxisDev->addChild(arrowZ);
        cursorAxisDev->addChild(arrow_reverseY);
        cursorAxisDev->addChild(arrow_reverseZ);
        cursorAxisDev->addChild(arrow_reverseX);

//        cursorBlock->addChild(arrowX);
//        cursorBlock->addChild(arrowY);
//        cursorBlock->addChild(arrowZ);
//        cursorBlock->addChild(arrow_reverseY);
//        cursorBlock->addChild(arrow_reverseZ);
//        cursorBlock->addChild(arrow_reverseX);

    //Scale Arrows appropriately
    arrowX->scaleXYZ(x_forward_s_scale.x(), x_forward_s_scale.y(), x_forward_s_scale.z());
    arrowY->scaleXYZ(y_forward_s_scale.x(), y_forward_s_scale.y(), y_forward_s_scale.z());
    arrowZ->scaleXYZ(z_forward_s_scale.x(), z_forward_s_scale.y(), z_forward_s_scale.z());
    arrow_reverseX->scaleXYZ(x_reverse_s_scale.x(), x_reverse_s_scale.y(), x_reverse_s_scale.z());
    arrow_reverseY->scaleXYZ(y_reverse_s_scale.x(), y_reverse_s_scale.y(), y_reverse_s_scale.z());
    arrow_reverseZ->scaleXYZ(z_reverse_s_scale.x(), z_reverse_s_scale.y(), z_reverse_s_scale.z());

//    Set Relative Arrow Positions/Rotations
//    arrowX->setLocalPos(x_forward_s_pos);
//    arrow_reverseX->setLocalPos(x_reverse_s_pos);
//    arrowY->setLocalPos(z_forward_s_pos);
//    arrow_reverseY->setLocalPos(y_reverse_s_pos);
//    arrowZ->setLocalPos(z_forward_s_pos);
//    arrow_reverseZ->setLocalPos(z_reverse_s_pos);

//    arrowX->setLocalRot(z_rot);
//    arrow_reverseX->setLocalRot(y_rot*x_rot);
//    arrowY->setLocalRot(x_rot);
//    arrow_reverseY->setLocalRot(x_rot*y_rot);
//    arrowZ->setLocalRot(z_rot);
//    arrow_reverseZ->setLocalRot(z_rot*y_rot);

    //Set Straight Arrow colors
    setArrowColorblindColor(arrowX, "purple");
    setArrowColorblindColor(arrowY, "white");
    setArrowColorblindColor(arrowZ, "green");
    setArrowColorblindColor(arrow_reverseX, "purple");
    setArrowColorblindColor(arrow_reverseY, "white");
    setArrowColorblindColor(arrow_reverseZ, "green");

    // Set Arrays
    arrow_array[0] = arrowX; arrow_array[1] = arrowY; arrow_array[2] = arrowZ; arrow_array[3] = arrow_reverseX; arrow_array[4] = arrow_reverseY; arrow_array[5] = arrow_reverseZ;


    setArrowTransparency(0, 0, 0, 0, 0, 0, arrow_array);
    //setArrowTransparency(0, 0, 0, 1, 1, 1, arrow_array);

    //        // Circular Arrow Sizes
    //        circ_innerRad0=0.05;
    //        circ_innerRad1=0.05;
    //        circ_outerRad=0.3;
    //        circ_lengthTip=0.2;
    //        circ_radiusTip=0.1;
    //        circ_coverageAngleDEG=270;
    //        circ_includeTipsAtBothExtremities=false;
    //        circ_numSides=32;
    //        circ_numRings=32;
    //        circ_direction=cVector3d(0, 0, 1);
    //        circ_pos=cVector3d(0, 0, 0);
    //        circ_color=cColorf(1.0, 1.0, 1.0, 1.0);

    //------------------------------CIRCULAR ARROWS -----------------------------------------
    chai3d::cCreateCircularArrow(circ_arrowX, 0.05, 0.05, 0.3, 0.2, 0.1, 270, false, 32U, 32U, chai3d::cVector3d(1, 0.001, 0), x_forward_c_pos); //create a circular arrow in X axis
    chai3d::cCreateCircularArrow(circ_arrowY, 0.05, 0.05, 0.3, 0.2, 0.1, 270, false, 32U, 32U, chai3d::cVector3d(0.001, 1, 0), y_forward_c_pos); //create a circular arrow in Y axis
    chai3d::cCreateCircularArrow(circ_arrowZ, 0.05, 0.05, 0.3, 0.2, 0.1, 270, false, 32U, 32U, chai3d::cVector3d(0, 0, -1), z_forward_c_pos); //create a circular arrow in Z axis
    chai3d::cCreateCircularArrow(circ_arrow_reverseX, 0.05, 0.05, 0.3, 0.2, 0.1, 270, false, 32U, 32U, chai3d::cVector3d(-1, 0.001, 0), x_reverse_c_pos); //create a circular arrow in X axis
    chai3d::cCreateCircularArrow(circ_arrow_reverseY, 0.05, 0.05, 0.3, 0.2, 0.1, 270, false, 32U, 32U, chai3d::cVector3d(0.001, -1, 0), y_reverse_c_pos); //create a circular arrow in X axis
    chai3d::cCreateCircularArrow(circ_arrow_reverseZ, 0.05, 0.05, 0.3, 0.2, 0.1, 270, false, 32U, 32U, chai3d::cVector3d(0, 0, 1), z_reverse_c_pos); //create a circular arrow in X axis

    //Add arrows to the axis Dev
    cursorAxisDev->addChild(circ_arrowX);
    cursorAxisDev->addChild(circ_arrowY);
    cursorAxisDev->addChild(circ_arrowZ);
    cursorAxisDev->addChild(circ_arrow_reverseY);
    cursorAxisDev->addChild(circ_arrow_reverseZ);
    cursorAxisDev->addChild(circ_arrow_reverseX);

    //Scale Circular Arrows appropriately
    circ_arrowX->scaleXYZ(x_forward_c_scale.x(), x_forward_c_scale.y(), x_forward_c_scale.z());
    circ_arrowY->scaleXYZ(y_forward_c_scale.x(), y_forward_c_scale.y(), y_forward_c_scale.z());
    circ_arrowZ->scaleXYZ(z_forward_c_scale.x(), z_forward_c_scale.y(), z_forward_c_scale.z());
    circ_arrow_reverseX->scaleXYZ(x_reverse_c_scale.x(), x_reverse_c_scale.y(), x_reverse_c_scale.z());
    circ_arrow_reverseY->scaleXYZ(y_reverse_c_scale.x(), y_reverse_c_scale.y(), y_reverse_c_scale.z());
    circ_arrow_reverseZ->scaleXYZ(z_reverse_c_scale.x(), z_reverse_c_scale.y(), z_reverse_c_scale.z());

    //Set Circular Arrow colors
    setArrowColorblindColor(circ_arrowX, "purple");
    setArrowColorblindColor(circ_arrowY, "white");
    setArrowColorblindColor(circ_arrowZ, "green");
    setArrowColorblindColor(circ_arrow_reverseX, "purple");
    setArrowColorblindColor(circ_arrow_reverseY, "white");
    setArrowColorblindColor(circ_arrow_reverseZ, "green");

    circ_arrow_array[0] = circ_arrowX; circ_arrow_array[1] = circ_arrowY; circ_arrow_array[2] = circ_arrowZ; circ_arrow_array[3] = circ_arrow_reverseX; circ_arrow_array[4] = circ_arrow_reverseY; circ_arrow_array[5] = circ_arrow_reverseZ;

    setArrowTransparency(0, 0, 0, 0, 0, 0, circ_arrow_array);
//    setArrowTransparency(1, 1, 1, 1, 1, 1, circ_arrow_array);
}

void GuidedTool::createTool()
{
    // Load STL File, scale and set rotation and position on screen
    cursorBlock->loadFromFile(stl_file);
    cursorBlock->scale(stl_scale_value);
    cursorBlock->setLocalPos(chai3d::cVector3d(0,0,0));
    cursorBlock->setLocalRot(chai3d::cMatrix3d(1, 0, 0, 0)); // this formulation is vector for axis and radians angle.;
    cursorBlock->setUseTransparency(true, true);
    cursorBlock->setTransparencyLevel(1); //(Transparency level 1 is fully Transparent)

    initializeArrows();
}


void GuidedTool::setArrowColorblindColor(chai3d::cMesh* arrow, std::string color)
{
    // For setting Arrow Colors to the safe colorblind colors
    if (color == "white"){
        arrow->m_material->setWhiteColorblind();
    }else if (color =="green"){
        arrow->m_material->setGreenColorblind();
    }else if (color =="purple"){
        arrow->m_material->setPurpleColorblind();
    }
}

void GuidedTool::allArrowsTransparent(chai3d::cMesh* arrow_type_array[6])
{
    // Set transparent_arrow_array as the circular or straight array
    int *transparent_arrow_array;
    if (arrow_type_array == circ_arrow_array)
    {
        transparent_arrow_array = circular_arrow_transparency_levels;

    }else{
        transparent_arrow_array = straight_arrow_transparency_levels;
    }

    for (int j = 0; j < 6; j++) // Set at 6 for all 6 arrows in the array
    {
        arrow_type_array[j]->setTransparencyLevel(0);
        *(transparent_arrow_array + j) = 0;

    }
}

void GuidedTool::setArrowTransparency(int x, int y, int z, int xr, int yr, int zr, chai3d::cMesh* arrow_array[6])
{
        // Set all Arrows as Transparent
        allArrowsTransparent(arrow_array);


        int *transparent_arrow_array;
        if (arrow_array == circ_arrow_array)
        {
            transparent_arrow_array = circular_arrow_transparency_levels;

        }else{
            transparent_arrow_array = straight_arrow_transparency_levels;
        }

        // Set codes:
        //      0: Make Arrows Disappear (Fully Transparent)
        //      1: Make Arrow Appear

        //FORWARD
        if (x == 1)
        {
            arrow_array[0]->setTransparencyLevel(1);
            arrow_array[3]->setTransparencyLevel(0);
            *(transparent_arrow_array + 0) = 1;
            *(transparent_arrow_array + 3) = 0;
        }
        else if (x == 0)
        {
            arrow_array[0]->setTransparencyLevel(0);
            *(transparent_arrow_array + 0) = 0;
        }
        if (y == 1)
        {
            arrow_array[1]->setTransparencyLevel(1);
            arrow_array[4]->setTransparencyLevel(0);
            *(transparent_arrow_array + 1) = 1;
            *(transparent_arrow_array + 4) = 0;
        }
        else if (y == 0)
        {
            arrow_array[1]->setTransparencyLevel(0);
            *(transparent_arrow_array + 1) = 0;
        }
        if (z == 1)
        {
            arrow_array[2]->setTransparencyLevel(1);
            arrow_array[5]->setTransparencyLevel(0);
            *(transparent_arrow_array + 2) = 1;
            *(transparent_arrow_array + 5) = 0;
        }
        else if (z == 0)
        {
            arrow_array[2]->setTransparencyLevel(0);
            *(transparent_arrow_array + 2) = 0;
        }


        //REVERSE
        if (xr == 1)
        {
            arrow_array[3]->setTransparencyLevel(1);
            arrow_array[0]->setTransparencyLevel(0);
            *(transparent_arrow_array + 3) = 1;
            *(transparent_arrow_array + 0) = 0;
        }
        else if (xr == 0)
        {
            arrow_array[3]->setTransparencyLevel(0);
            *(transparent_arrow_array + 3) = 0;
        }
        if (yr == 1)
        {
            arrow_array[4]->setTransparencyLevel(1);
            arrow_array[1]->setTransparencyLevel(0);
            *(transparent_arrow_array + 4) = 1;
            *(transparent_arrow_array + 1) = 0;
        }
        else if (yr == 0)
        {
            arrow_array[4]->setTransparencyLevel(0);
            *(transparent_arrow_array + 4) = 0;
        }
        if (zr == 1)
        {
            arrow_array[5]->setTransparencyLevel(1);
            arrow_array[2]->setTransparencyLevel(0);
            *(transparent_arrow_array + 5) = 1;
            *(transparent_arrow_array + 2) = 0;
        }
        else if (zr == 0) {
            arrow_array[5]->setTransparencyLevel(0);
            *(transparent_arrow_array + 5) = 0;
        }
}

void GuidedTool::setPosition(chai3d::cVector3d new_pos)
{
    pos = new_pos;
    cursor->setLocalPos(pos);
}

void GuidedTool::setOrientation(chai3d::cMatrix3d new_rot)
{
    rot = new_rot;
//    rot.identity(); // TODO: REMOVE THIS, JUST A TEST
    cursor->setLocalRot(rot);
    //cursorBlock->setLocalRot(new_rot); // TODO: UNCOMMENT
    //cursorBlock->setLocalRot(chai3d::cMatrix3d(1, 0, 0, 0));
}



void GuidedTool::getKValues(const chai3d::cMatrix3d tool_base_rot_matrix)
{
    // Initialize Armadillo Matrices
    arma::mat base_matrix(3, 3);
    arma::mat rotated_tool_matrix(3, 3);

    // Change Eigen Matrices to Armadillo Matrices (for log matrix function)
    EigenToArmadillo(tool_base_rot_matrix, base_matrix);
    EigenToArmadillo(rot, rotated_tool_matrix);

//    std::cout << "MATRICES PRINTED" << std::endl;
//    base_matrix.print();
//    rotated_tool_matrix.print();

    if ((rotated_tool_matrix[0]!=rotated_tool_matrix[0]) || (base_matrix[0]!=base_matrix[0])){
        std::cout<<"NO TOOL FOUND"<< std::endl;
        k.x(-1000);
        k.y(-1000);
        k.z(-1000);

    }else{
        // Find Rotation matrix bewteen the base and the rotated tool frame
        arma::mat R_oper = base_matrix*(rotated_tool_matrix.t());  // BUG: WHY ISN't THIS WORKING

        // Compute the log matrix and get the skew symmetric matrix
        arma::cx_mat skew = arma::logmat(R_oper);
        arma::mat skew2 = arma::conv_to<arma::mat>::from(skew);

         // Extract K values from skew symmetric matrix
        double k1, k2, k3;
        k1 = skew2(2, 1);
        k2 = skew2(0, 2);
        k3 = skew2(1, 0);

        // Set input k cVector3d vector with the newly computed k values
        k.x(k1);
        k.y(k2);
        k.z(k3);
    }
}



void GuidedTool::updateCircularArrows(int dof=6)
{

    //-----------------------------SET OCCUPIED ARROW ----------------------------
    // Detect occupied portion and see if a circular arrow is being computed currently for 5 or 6 dof (6 dof is default)
    if (!arrow_guidance_selected) {
        if (dof==6){
            std::cout << " DOF 6 ----------------------"<< std::endl;
            if (fabs(k.x()) > rot_epsilon && fabs(k.x()) > fabs(k.y()) && fabs(k.x()) > fabs(k.z()) ) {
                arrow_flag = 1;
                arrow_guidance_selected = 1;
            }
            else if (fabs(k.y()) > rot_epsilon && fabs(k.y()) > fabs(k.z()) && fabs(k.y()) > fabs(k.x()) ) {
                arrow_flag = 2;
                arrow_guidance_selected = 1;
            }
            else if (fabs(k.z()) > rot_epsilon && fabs(k.z()) > fabs(k.y()) && fabs(k.z()) > fabs(k.x()) ) {
                arrow_flag = 3;
                arrow_guidance_selected = 1;
            }
            else
            {
                // Clear All Arrows
                allArrowsTransparent(circ_arrow_array);
                allArrowsTransparent(arrow_array);
                arrow_guidance_selected = 0;
                arrow_flag = 0;
                circ_or_straight = 1;

            }
        }else if (dof==5){
           std::cout << " DOF 5 ----------------------"<< std::endl;
            // TODO: FILL in 5 dof tool info

        }else if (dof==4){ // This is the system we are using for the omni arm ( we can't control the 2 dofs that it is already fixed on, only rotation around arm (we assume arm remains stiff and perpendicular to ground normal plane)

//            std::cout << "K X: " << k.x() << " K Y: " << k.y() << " K Z: " << k.z() << " rot_eps: " << rot_epsilon << std::endl;
//             std::cout << "if fabs(k.x()): " << fabs(k.x()) << " is > rot_epsilon: " << rot_epsilon << std::endl;

            if (fabs(k.x()) > rot_epsilon) {
                arrow_flag = 1;
                arrow_guidance_selected = 1;
            }else{
                // Clear All Arrows
                allArrowsTransparent(circ_arrow_array);
                allArrowsTransparent(arrow_array);
                arrow_guidance_selected = 0;
                arrow_flag = 0;
                circ_or_straight = 1;
            }
        }else{
            std::cout << " NO DOF??????????? ----------------------"<< std::endl;
        }
    }

    //std::cout << "ARROW FLAG: " << arrow_flag << std::endl;

    //-----------------------------SET VISIBLE ARROW ----------------------------
    if (arrow_flag == 1) {   // X Axis Arrow
        if (fabs(k.x()) < rot_epsilon) {
            arrow_guidance_selected = 0; // Release occupied to check for next largest rotation value
        }
        else if (k.x() >= 0) {
            setArrowTransparency(0, 0, 0, 1, 0, 0, circ_arrow_array);
        }
        else{
            setArrowTransparency(1, 0, 0, 0, 0, 0, circ_arrow_array);
        }
    }
    else if (arrow_flag == 2) { // Y Axis Arrow
        if (fabs(k.y()) < rot_epsilon) {
            arrow_guidance_selected = 0;
        }
        else if (k.y() >= 0) {
            setArrowTransparency(0, 1, 0, 0, 0, 0, circ_arrow_array);
        }
        else{
            setArrowTransparency(0, 0, 0, 0, 1, 0, circ_arrow_array);
        }
    }
    else if (arrow_flag == 3) {
        if (fabs(k.z()) < rot_epsilon) {
            arrow_guidance_selected = 0;
        }
        else if (k.z() >= 0) {
            setArrowTransparency(0, 0, 1, 0, 0, 0, circ_arrow_array);
        }
        else{
            setArrowTransparency(0, 0, 0, 0, 0, 1, circ_arrow_array);
        }
    }
    else{ // Set all Transparent
        //std::cout << "SET ALL TRANSPARENT ARROWS" << std::endl;
        allArrowsTransparent(circ_arrow_array);
        arrow_guidance_selected = 0;
    }
}

void GuidedTool::updateStraightArrows()
{
    //-----------------------------SET OCCUPIED ARROW ----------------------------
    // Detect occupied portion and see if a straight arrow is being computed
    if (!arrow_guidance_selected) {
        if (fabs(cur_pos_x_offset) >= trans_epsilon && fabs(cur_pos_x_offset) > fabs(cur_pos_y_offset) && fabs(cur_pos_x_offset) > fabs(cur_pos_z_offset) )
        {
            arrow_flag = 1;
            arrow_guidance_selected = 1;
        }
        else if (fabs(cur_pos_y_offset) >= trans_epsilon && fabs(cur_pos_y_offset) > fabs(cur_pos_x_offset) && fabs(cur_pos_y_offset) > fabs(cur_pos_z_offset) )
        {
            arrow_flag = 2;
            arrow_guidance_selected = 1;
        }
        else if (fabs(cur_pos_z_offset) >= trans_epsilon && fabs(cur_pos_z_offset) > fabs(cur_pos_x_offset) && fabs(cur_pos_z_offset) > fabs(cur_pos_y_offset) )
        {
            arrow_flag = 3;
            arrow_guidance_selected = 1;
        }
        else{
            // Clear All Arrows
            allArrowsTransparent(arrow_array);
            arrow_flag = 0;
            circ_or_straight=0;
            arrow_guidance_selected = 0;
        }
    }


    //std::cout << "arrow flag: " << arrow_flag << std::endl;


    //-----------------------------SET VISIBLE ARROW ----------------------------
    if (arrow_flag == 1) {   // X Axis Arrow
        if (fabs(cur_pos_x_offset) < trans_epsilon) {
            arrow_guidance_selected = 0; // Release occupied to check for next largest rotation value
        }
        else if ((cur_pos_x_offset) >= 0) {
            setArrowTransparency(1, 0, 0, 0, 0, 0, arrow_array);
        }
        else{
            setArrowTransparency(0, 0, 0, 1, 0, 0, arrow_array);
        }
    }
    else if (arrow_flag == 2) { // Y Axis Arrow
        if (fabs(cur_pos_y_offset) < trans_epsilon) {
            arrow_guidance_selected = 0;
        }
        else if ((cur_pos_y_offset) >= 0) {
            setArrowTransparency(0, 1, 0, 0, 0, 0, arrow_array);
        }
        else{
            setArrowTransparency(0, 0, 0, 0, 1, 0, arrow_array);
        }
    }
    else if (arrow_flag == 3) {
        if (fabs(cur_pos_z_offset) < trans_epsilon) {
            arrow_guidance_selected = 0;
        }
        else if ((cur_pos_z_offset) >= 0) {
            setArrowTransparency(0, 0, 1, 0, 0, 0, arrow_array);
            //arrow_guidance_selected = 0;
        }
        else{
            setArrowTransparency(0, 0, 0, 0, 0, 1, arrow_array);
        }
    }
}



//void GuidedTool::updatePoseAlignment(chai3d::cMultiMesh* cursorblockbase, chai3d::cVector3d base_loc_position, chai3d::cMatrix3d base_loc_rotation, chai3d::cVector3d tool_position, chai3d::cMatrix3d tool_rotation)
//{
//    // Set Guided tool position and rotation
////    setPosition(tool_position);
////    setOrientation(tool_rotation);

//    //TODO: add updates to tool rotation here for CornerViews?

//    //Get the rotation values
//    getKValues(base_loc_rotation);

//    //Get the position values
//    cur_pos_x_offset = base_loc_position.x() - pos.x();
//    cur_pos_y_offset = base_loc_position.y() - pos.y();
//    cur_pos_z_offset = base_loc_position.z() - pos.z();

////    std::cout << "-----K values------------" << std::endl;
////    std::cout << "base LOC X: " << base_loc_position.x() << " Y: "<< base_loc_position.y() << " Z: " << base_loc_position.z() << std::endl;
////    std::cout << "pos X: " << pos.x() << " Y: "<< pos.y() << " Z: " << pos.z() << std::endl;
////    std::cout << "cur_pos_offset X: " << cur_pos_x_offset << " Y: "<< cur_pos_y_offset << " Z: " << cur_pos_z_offset << std::endl;


//    // Clear All Arrows
//    allArrowsTransparent(circ_arrow_array);
//    allArrowsTransparent(arrow_array);

//    //std::cout << "K vals:  X: " << k.x() << " Y: " << k.y() << " Z: " << k.z() << "  rot_epsilon: " << rot_epsilon <<" arrow_guidance_selected: " << arrow_guidance_selected << " circ_or_straight: "<< circ_or_straight << std::endl;
//    // circ_or_straight 0 -> for updating Circular Arrows, 1 -> for updating straight arrows

//    if (!circ_or_straight) {
//        updateCircularArrows();
//    }
//    else{
//        updateStraightArrows();
//    }

////    updateStraightArrows();


//    // CHECK FOR MATCH
//    // full match
//    if (fabs(cur_pos_x_offset) < trans_epsilon && fabs(cur_pos_y_offset) < trans_epsilon && fabs(cur_pos_z_offset) < trans_epsilon && fabs(k.x())<rot_epsilon && fabs(k.y())<rot_epsilon && fabs(k.z())<rot_epsilon){
//        //TODO change this
//        this->setColor("green");
//        cursorblockbase->getMesh(0)->m_material->setGreen();
//    }else{
//        this->setColor("gray");
//        cursorblockbase->getMesh(0)->m_material->setGray();
//    }
//}

void GuidedTool::updatePoseAlignment(polarisTransformMatrix* base_pose, chai3d::cVector3d tool_position, chai3d::cMatrix3d tool_rotation, chai3d::cMultiMesh* base_tool, chai3d::cVector3d mag_offset)
{
    // Set Guided tool position and rotation
    setPosition(tool_position);
    setOrientation(tool_rotation);

    //TODO: add updates to tool rotation here for CornerViews?

    //Get the rotation values
    getKValues(base_pose->rot_mat);

    //Get the position values
    cur_pos_x_offset = (base_pose->pos.x() + mag_offset.x()) - pos.x();
    cur_pos_y_offset = (base_pose->pos.y() + mag_offset.y()) - pos.y();
    cur_pos_z_offset = (base_pose->pos.z() + mag_offset.z()) - pos.z();

    // Clear All Arrows
    allArrowsTransparent(circ_arrow_array);
    allArrowsTransparent(arrow_array);

    //std::cout << "K vals:  X: " << k.x() << " Y: " << k.y() << " Z: " << k.z() << "  rot_epsilon: " << rot_epsilon <<" arrow_guidance_selected: " << arrow_guidance_selected << " circ_or_straight: "<< circ_or_straight << std::endl;
    qDebug() << "Pos of k" <<  " X: " << k.x() << " Y: " << k.y() << " Z: " << k.z();


    //TODO: uncomment this for the future when you want to
    // circ_or_straight 0 -> for updating Circular Arrows, 1 -> for updating straight arrows
    if (!circ_or_straight) {
        updateCircularArrows(4);
    }
    else{
        updateStraightArrows();
    }

//    updateCircularArrows(4);

    int dof = 4;

    if (dof==6){
        // CHECK FOR MATCH (6dof)
        // full match
        if (fabs(cur_pos_x_offset) < trans_epsilon && fabs(cur_pos_y_offset) < trans_epsilon && fabs(cur_pos_z_offset) < trans_epsilon && fabs(k.x())<rot_epsilon && fabs(k.y())<rot_epsilon && fabs(k.z())<rot_epsilon){
            //TODO change this
            this->setColor("green");
            //base_tool->setColor("green");
        }else{
            this->setColor("gray");
            //base_tool->setColor("red");
        }

    }else if(dof==4){
        // CHECK FOR MATCH (6dof)
        // full match
        if (fabs(cur_pos_x_offset) < trans_epsilon && fabs(cur_pos_y_offset) < trans_epsilon && fabs(cur_pos_z_offset) < trans_epsilon && fabs(k.x())<rot_epsilon){
            //TODO change this
            this->setColor("green");
            base_tool->getMesh(0)->m_material->setGreenLight();
        }else{
            this->setColor("gray");
            base_tool->getMesh(0)->m_material->setRedCrimson();
        }
    }

}

int* GuidedTool::getArrowTransparency(chai3d::cMesh*  arrow_array[6])
{
    int output_array[6];
    // Check to see which of the arrows is Transparent
    for(int i=0;i<6;i++){
        if (arrow_array[i]->m_material->isTransparent()){
            output_array[i] = 0;
        }
        else {
            output_array[i] = 1;
        }
    }
    return output_array;
}


// ----------------------------------------- EXTRA FUNCTIONS -----------------------------------------
void EigenToArmadillo(const chai3d::cMatrix3d& Mat, arma::mat& Matrix)
{
    chai3d::cVector3d col0, col1, col2;

    col0 = Mat.getCol0();
    col1 = Mat.getCol1();
    col2 = Mat.getCol2();

    Matrix(0, 0) = col0.x();
    Matrix(0, 1) = col1.x();
    Matrix(0, 2) = col2.x();
    Matrix(1, 0) = col0.y();
    Matrix(1, 1) = col1.y();
    Matrix(1, 2) = col2.y();
    Matrix(2, 0) = col0.z();
    Matrix(2, 1) = col1.z();
    Matrix(2, 2) = col2.z();
}

//void printMatrix3d(chai3d::cMatrix3d matrix)
//{
//    std::cout << "-------MATRIX: PRINTED:---- " << std::endl;
//    std::cout << matrix.getCol0().x() << ", " << matrix.getCol1().x() << ", " << matrix.getCol2().x() << std::endl;
//    std::cout << matrix.getCol0().y() << ", " << matrix.getCol1().y() << ", " << matrix.getCol2().y() << std::endl;
//    std::cout << matrix.getCol0().z() << ", " << matrix.getCol1().z() << ", " << matrix.getCol2().z() << std::endl;
//    std::cout << "----------------" << std::endl;
//}


void printArmadilloMatrix(arma::mat matrix)
{
    std::cout << "-------MATRIX: PRINTED:---- " << std::endl;
    std::cout << matrix[0] << ", " << matrix[3] << ", " << matrix[6] << std::endl;
    std::cout << matrix[1] << ", " << matrix[4] << ", " << matrix[7] << std::endl;
    std::cout << matrix[2] << ", " << matrix[5] << ", " << matrix[8] << std::endl;
    std::cout << "----------------" << std::endl;
}

