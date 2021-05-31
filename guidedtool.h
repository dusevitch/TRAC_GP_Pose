#ifndef GUIDEDTOOL_H
#define GUIDEDTOOL_H
#pragma once

#include "chai3d.h"
#include <iostream>
#include <string>
#include "Eigen/Dense"
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <armadillo>
#include <json/json.h>
#include <json/value.h>
#include <polaristransformmatrix.h>

extern double PI;

class GuidedTool
{
public:
    ///----------------------------------------
    ///   Methods
    /// ---------------------------------------

    GuidedTool(chai3d::cWorld* world);
    void generateArrows();
    chai3d::cVector3d getcVector3d(Json::Value val);
    bool loadToolFile(std::string filename, int cornerViewsFlag = 0);
    void setColor(std::string color);
    void initializeArrows();
    void createTool();
    void setArrowColorblindColor(chai3d::cMesh* arrow, std::string color);
    void allArrowsTransparent(chai3d::cMesh* arrow_type_array[6]);
    void setArrowTransparency(int x, int y, int z, int xr, int yr, int zr, chai3d::cMesh* arrow_array[6]);
    void setPosition(chai3d::cVector3d new_pos);
    void setOrientation(chai3d::cMatrix3d new_rot);
    void getKValues(const chai3d::cMatrix3d tool_base_rot_matrix);
    void updateCircularArrows(int dof);
    void updateStraightArrows();
    //void updatePoseAlignment(GuidedTool* base_tool, chai3d::cVector3d tool_position, chai3d::cMatrix3d tool_rotation);
    //void updatePoseAlignment(polarisTransformMatrix* base_pose, chai3d::cVector3d tool_position, chai3d::cMatrix3d tool_rotation, chai3d::cMultiMesh* base_tool);
    void updatePoseAlignment(polarisTransformMatrix* base_pose, chai3d::cVector3d tool_position, chai3d::cMatrix3d tool_rotation, chai3d::cMultiMesh* base_tool, chai3d::cVector3d mag_offset=chai3d::cVector3d(0,0,0));

    int* getArrowTransparency(chai3d::cMesh* arrow_array[6]);
    //void updatePoseAlignment(chai3d::cMultiMesh* cursorblockbase, chai3d::cVector3d base_loc_position, chai3d::cMatrix3d base_loc_rotation, chai3d::cVector3d tool_position, chai3d::cMatrix3d tool_rotation);

    ///----------------------------------------
    ///   Variables/Properties
    /// ---------------------------------------

    // Main Object
    chai3d::cMultiMesh* cursorBlock;
    chai3d::cShapeSphere* cursor;
    chai3d::cShapeSphere* cursorAxisDev;

    // STL FILE Parameters
    std::string stl_file;
    double stl_scale_value;
    chai3d::cVector3d posZeroingVector; // Offset vector to position tool on screen


    // For Storing the current position and orientation of the object
    chai3d::cVector3d pos;

    chai3d::cVector3d rot_vec;
    double rot_rad;
    chai3d::cMatrix3d rot;
    chai3d::cVector3d k; // Sparse params

    std::string track_file;

    chai3d::cVector3d ObjScale;
    chai3d::cVector3d TransOffset;
    chai3d::cVector3d RotOffset;

    chai3d::cVector3d ScreenViewPos;
    chai3d::cVector3d ScreenViewRot;

    chai3d::cVector3d CornerViewShift;

    ///----------------------------------------
    ///   Variables
    /// ---------------------------------------

    // Thresholds
    double trans_epsilon;
    double rot_epsilon;
    double deg_val;

    double main_stl_scale_value; // For scaling when using the cornerViews, this keeps track of main object size while stl_scale_value is replaced by the cornerview size

    // Initial offset tool vector (Orient coordinate frame to align with the tool frame
    chai3d::cVector3d init_offset_rot;
    chai3d::cMatrix3d init_offset_mat;

    // Arrow Selection Tools
    int circ_or_straight; // 0 for circ, 1 for straight
    int arrow_guidance_selected; // If arrow is occupied
    double cur_pos_x_offset;
    double cur_pos_y_offset;
    double cur_pos_z_offset;

    double arrow_scale;

    int arrow_flag; // Determine which arrow x,y, or z is currently being computed, determined by the largest rotational dist from goal (x=1, y=2, z=3)
    std::string json_file; // json load file associated with this tool

    // Update to see the transparency levels of all arrows
    int straight_arrow_transparency_levels[6];
    int circular_arrow_transparency_levels[6];

    // STRAIGHT ARROWS --------------------------------------------------------------------

    // Staright Arrow Meshes
    chai3d::cMesh* arrowZ;
    chai3d::cMesh* arrowY;
    chai3d::cMesh* arrowX;
    chai3d::cMesh* arrow_reverseZ;
    chai3d::cMesh* arrow_reverseY;
    chai3d::cMesh* arrow_reverseX;

    chai3d::cMesh* arrow_array[6];

    // Straight Arrow Position
    chai3d::cVector3d x_forward_s_pos; // X forward straight arrow local position
    chai3d::cVector3d x_reverse_s_pos;
    chai3d::cVector3d y_forward_s_pos;
    chai3d::cVector3d y_reverse_s_pos;
    chai3d::cVector3d z_forward_s_pos;
    chai3d::cVector3d z_reverse_s_pos;

    // Straight Arrow Scale
    chai3d::cVector3d x_forward_s_scale; // X forward straight arrow local scale
    chai3d::cVector3d x_reverse_s_scale;
    chai3d::cVector3d y_forward_s_scale;
    chai3d::cVector3d y_reverse_s_scale;
    chai3d::cVector3d z_forward_s_scale;
    chai3d::cVector3d z_reverse_s_scale;

    // Straight Arrow Parameters
    double arrow_len;
    double arrow_hw; // Arrow width and height (we keep equally proportional for aesthetics)

    // CIRCULAR ARROWS --------------------------------------------------------------------
    // Circle Arrow Meshes
    chai3d::cMesh* circ_arrowZ;
    chai3d::cMesh* circ_arrowY;
    chai3d::cMesh* circ_arrowX;
    chai3d::cMesh* circ_arrow_reverseZ;
    chai3d::cMesh* circ_arrow_reverseY;
    chai3d::cMesh* circ_arrow_reverseX;

    chai3d::cMesh* circ_arrow_array[6];

    // Circular Arrow Position
    chai3d::cVector3d x_forward_c_pos; // X forward circular arrow local position
    chai3d::cVector3d x_reverse_c_pos;
    chai3d::cVector3d y_forward_c_pos;
    chai3d::cVector3d y_reverse_c_pos;
    chai3d::cVector3d z_forward_c_pos;
    chai3d::cVector3d z_reverse_c_pos;

    // Circular Arrow Scale
    chai3d::cVector3d x_forward_c_scale; // X forward circular arrow local scale
    chai3d::cVector3d x_reverse_c_scale;
    chai3d::cVector3d y_forward_c_scale;
    chai3d::cVector3d y_reverse_c_scale;
    chai3d::cVector3d z_forward_c_scale;
    chai3d::cVector3d z_reverse_c_scale;

    // Circular Arrow Parameters
    double circ_arrow_depth; // thickness in z direction
    double circ_arrow_hw; // Arrow width and height (diameter of circle)

    chai3d::cMesh* arrowStraightArray[6];
    chai3d::cMesh* arrowCircArray[6];
    chai3d::cMesh* arrowCurrArray[6];

    // Corner  View Parameters -------------------------------------------------------------------
    double corner_views_scale;
    double views_rot_deg;
    chai3d::cVector3d top_left_position;
    chai3d::cVector3d top_left_rot;
    chai3d::cVector3d top_right_position;
    chai3d::cVector3d top_right_rot;
    chai3d::cVector3d bottom_left_position;
    chai3d::cVector3d bottom_left_rot;
    chai3d::cVector3d bottom_right_position;
    chai3d::cVector3d bottom_right_rot;

};


#endif // GUIDEDTOOL_H
