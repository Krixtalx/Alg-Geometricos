
/* 
 * File:   DrawLine3d3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 17:41
 */

#ifndef DRAWLINE3D_H
#define DRAWLINE3D_H

#include "../Scene.h"
#include "Line3d.h"
#include "../Draw.h"

class DrawLine3d: public Draw {
    
    Line3d dt;
    
    public:
        
    DrawLine3d (Line3d &t); 
    
    DrawLine3d (DrawLine3d &ddt): dt (ddt.dt) , Draw() {}
    
    void drawIt ();
    void drawIt (TypeColor c);
    
    virtual ~DrawLine3d(){};
};



#endif /* DRAWLINE3D_H */

