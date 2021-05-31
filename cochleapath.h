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
    CochleaPath(QString file_path_name, chai3d::cVector3d &pos, chai3d::cWorld *world, chai3d::cMatrix3d &global_frame);
    ~CochleaPath();

    void readPathFile();
    void createPathFieldArrow(chai3d::cVector3d point_loc, chai3d::cVector3d field);
    void buildPath();
    void scaleSize(double scale_factor);
    void scaleOriginal();

    double last_scale_factor = 1;

private:
    chai3d::cVector3d center;
    chai3d::cShapeSphere *path;
    std::vector<chai3d::cVector3d> point_locs;
    std::vector<chai3d::cVector3d> field;
    QString filename;

    chai3d::cMatrix3d global_base_frame_rot_mat;



};



#endif // COCHLEAPATH_H
