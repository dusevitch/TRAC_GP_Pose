#include "cornerviews.h"

CornerViews::CornerViews()
{

}

CornerViews::CornerViews(GuidedTool* tool, chai3d::cWorld* m_world, chai3d::cCamera* m_camera)
{
    // Generate all Views
    toolView_TL = new GuidedTool(m_world);
    toolView_TR = new GuidedTool(m_world);
    toolView_BL = new GuidedTool(m_world);
    toolView_BR = new GuidedTool(m_world);

    updateView(toolView_TL, tool, m_camera, 0);
    updateView(toolView_TR, tool, m_camera, 1);
    updateView(toolView_BL, tool, m_camera, 2);
    updateView(toolView_BR, tool, m_camera, 3);

}

void CornerViews::updateView(GuidedTool* toolView, GuidedTool* tool, chai3d::cCamera* m_camera, int corner_pos)
{

    // Load tool properties from json file
    toolView->loadToolFile(tool->json_file, 1);

    // Get camera position
    chai3d::cVector3d camera_pos = m_camera->getLocalPos();

    // Change position based on which corner view it is
    if (corner_pos==0){
        toolView->pos = camera_pos + toolView->top_left_position;
    }else if (corner_pos==1){
        toolView->pos = camera_pos + toolView->top_right_position;
    }else if (corner_pos==2){
        toolView->pos = camera_pos + toolView->bottom_left_position;
    }else if (corner_pos==3){
        toolView->pos = camera_pos + toolView->bottom_right_position;
    }

    // Set position
    toolView->setPosition(toolView->pos);




    //UPDATE ORIENTATION OF OBJECTS IN APPLICATION.CPP CODE

}

void CornerViews::orientationUpdate(GuidedTool* tool, chai3d::cMatrix3d new_rot,  chai3d::cVector3d new_pos)
{
    // Change orientation
//    toolView_TL->setOrientation(new_rot * chai3d::cMatrix3d(tool->top_left_rot, tool->views_rot_deg));
//    toolView_TR->setOrientation(new_rot * chai3d::cMatrix3d(tool->top_right_rot, tool->views_rot_deg));
//    toolView_BL->setOrientation(new_rot * chai3d::cMatrix3d(tool->bottom_left_rot, tool->views_rot_deg));
//    toolView_BR->setOrientation(new_rot * chai3d::cMatrix3d(tool->bottom_right_rot, tool->views_rot_deg));

    toolView_TL->setOrientation(new_rot );
    toolView_TR->setOrientation(new_rot);
    toolView_BL->setOrientation(new_rot);
    toolView_BR->setOrientation(new_rot);


//    // Set the correct arrows Visible
    setCornerViewTransparency(toolView_TL, tool);
    setCornerViewTransparency(toolView_TR, tool);
    setCornerViewTransparency(toolView_BL, tool);
    setCornerViewTransparency(toolView_BR, tool);

    //std::cout << "PARENT: " << toolView_TL->arrow_array[4]->getParent() << std::endl;
}

void CornerViews::setCornerViewTransparency(GuidedTool* toolView, GuidedTool* tool)
{
    // Set Arrow Views for straight arrows based on main tool
    toolView->setArrowTransparency(tool->straight_arrow_transparency_levels[0], tool->straight_arrow_transparency_levels[1], tool->straight_arrow_transparency_levels[2], tool->straight_arrow_transparency_levels[3], tool->straight_arrow_transparency_levels[4], tool->straight_arrow_transparency_levels[5], toolView->arrow_array);

    // Set Arrow Views for circular arrows based on main tool
    toolView->setArrowTransparency(tool->circular_arrow_transparency_levels[0], tool->circular_arrow_transparency_levels[1], tool->circular_arrow_transparency_levels[2], tool->circular_arrow_transparency_levels[3], tool->circular_arrow_transparency_levels[4], tool->circular_arrow_transparency_levels[5], toolView->circ_arrow_array);

}

//void CornerViews::setAllViewsTransparent()
//{
//    toolView_TL->allArrowsTransparent(toolView_TL->arrow_array);
//    toolView_TL->allArrowsTransparent(toolView_TL->circ_arrow_array);
//    toolView_TL->cursor->setTransparencyLevel(0);

//    toolView_TR->allArrowsTransparent(toolView_TR->arrow_array);
//    toolView_TR->allArrowsTransparent(toolView_TR->circ_arrow_array);
//    toolView_TR->cursor->setTransparencyLevel(0);

//    toolView_BL->allArrowsTransparent(toolView_BL->arrow_array);
//    toolView_BL->allArrowsTransparent(toolView_BL->circ_arrow_array);
//    toolView_BL->cursor->setTransparencyLevel(0);

//    toolView_BR->allArrowsTransparent(toolView_BR->arrow_array);
//    toolView_BR->allArrowsTransparent(toolView_BR->circ_arrow_array);
//    toolView_BR->cursor->setTransparencyLevel(0);

//}
