#ifndef COCHLEAPATH_H
#define COCHLEAPATH_H

#include "chai3d.h"
#include <iostream>
#include <string>
#include "Eigen/Dense"
#include <QString>
#include "polaristransformmatrix.h"

class CochleaPath
{
public:
    CochleaPath(QString file_path_name, chai3d::cVector3d &pos, chai3d::cWorld *world, polarisTransformMatrix *input_mag_frame, chai3d::cVector3d mag_offset);
    CochleaPath(QString file_path_name);
    ~CochleaPath();


    void readPathFile();
    void createPathFieldArrow(chai3d::cVector3d point_loc, chai3d::cVector3d field);
    void buildPath();
    void scaleSize(double scale_factor);
    void scaleOriginal();
    void exportFieldArrowCSV(QString textFileOutput);
    void updateFieldPath(polarisTransformMatrix *mag_frame);

    double last_scale_factor = 1;

private:
    chai3d::cVector3d center;
    chai3d::cShapeSphere *path;
    std::vector<Eigen::Vector3d> init_point_locs;
    std::vector<Eigen::Vector3d> init_field;
    std::vector<Eigen::Vector3d> current_field;
    std::vector<Eigen::Vector3d> current_point_locs;
    QString filename;

    polarisTransformMatrix *mag_frame;
    chai3d::cVector3d mag_offset_vec;
    chai3d::cMatrix3d mag_frame_rot_mat;
    chai3d::cMatrix3d global_frame_rot_mat;

    // Vector record all arrow Fields and points created from path
    std::vector<chai3d::cMesh*> arrow_vector;
    std::vector<chai3d::cShapeSphere*> arrow_point;



};



#endif // COCHLEAPATH_H
