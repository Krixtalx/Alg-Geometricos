
/*
 * File:   Line3d.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:55
 */

#ifndef LINE3D_H
#define LINE3D_H

#include "Edge3d.h"
#include "Line3d.h"


class Line3d : public Edge3d {
public:
	enum classifyLines { NON_INTERSECT, PARALLEL, INTERSECT, THESAME };

protected:
	/**
	*	@brief Checks if the parametric value t is valid. Any value is valid for a line.
	*/
	virtual bool isTvalid(double t) { return true; }

public:
	/**
	*	@brief Default constructor.
	*/
	Line3d();

	/**
	*	@brief Constructor.
	*/
	Line3d(const Vect3d& orig, const Vect3d& dest);

	/**
	*	@brief Copy constructor.
	*/
	Line3d(const Line3d& line);

	/**
	*	@brief Destructor.
	*/
	virtual ~Line3d();

	/**
	*	@brief Distance between two lines.
	*/
	double distance(Line3d& line);


	/**
	*    @brief Distance between point p and this.
	*/
	double distance(Vect3d& p);

	/**
	*	@brief Returns the normal to this line that passes through p.
	*/
	Line3d normalLine(Vect3d& p);

	/**
	*	@brief Assignment operator.
	*/
	virtual Line3d& operator=(const Line3d& line);

	/**
	*	@brief Shows line data at the debug window.
	*/
	virtual void out();


};




#endif /* LINE3D_H */

