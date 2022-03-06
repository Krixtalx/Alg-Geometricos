
/* 
 * File:   DrawVect3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 14:45
 */

#ifndef DRAWVECT3D_H
#define DRAWVECT3D_H

#include "../Scene.h"
#include "Vect3d.h"
#include "../Draw.h"

class DrawVect3d: public Draw {
    Vect3d dp;
public:
    
    DrawVect3d(Vect3d &p);
    DrawVect3d (DrawVect3d &ddp): dp (ddp.dp) , Draw() {}
    void drawIt ();
    void drawIt (TypeColor c);
    virtual ~DrawVect3d(){};

};

#endif /* DRAWVECT3D_H */

