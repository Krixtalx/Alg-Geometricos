
/* 
 * File:   DrawTriangleModel.h
 * Author: lidia
 *
 * Created on 21 de febrero de 2021, 11:35
 */

#ifndef DRAWTRIANGLEMODEL_H
#define DRAWTRIANGLEMODEL_H

#include "../Scene.h"
#include "../Draw.h"
#include "TriangleModel.h"

class DrawTriangleModel: public Draw {
    
    TriangleModel dt;
    
    public:
        
   
    DrawTriangleModel (const TriangleModel &t); 
   
    DrawTriangleModel (const DrawTriangleModel &ddt): dt (ddt.dt) , Draw() {}
    
    
    void drawItPlain ();
    void drawIt ();
    void drawIt (TypeColor c);
    
    virtual ~DrawTriangleModel(){};
};


#endif /* DRAWTRIANGLEMODEL_H */

