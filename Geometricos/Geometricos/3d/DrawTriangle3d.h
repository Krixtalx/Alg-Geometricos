
/* 
 * File:   DrawTriangle3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 17:28
 */

#ifndef DRAWTRIANGLE3D_H
#define DRAWTRIANGLE3D_H

#include "../Scene.h"
#include "Triangle3d.h"
#include "../Draw.h"


class DrawTriangle3d: public Draw {
    
    Triangle3d dt;
    
    public:
        
    DrawTriangle3d (Triangle3d &t); 
    
    DrawTriangle3d (DrawTriangle3d &ddt): dt (ddt.dt) , Draw() {}
    
    void drawIt ();
    void drawIt (TypeColor c);
    
    virtual ~DrawTriangle3d(){};
};


#endif /* DRAWTRIANGLE3D_H */

