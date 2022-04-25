
/*
 * File:   PontCloud3d.h
 * Author: lidia
 *
 * Created on 26 de enero de 2021, 17:36
 */

#ifndef PONTCLOUD3D_H
#define PONTCLOUD3D_H


#include <string>
#include "AABB.h"
 //#include "TriangleMesh.h"
#include "Vect3d.h"
#include "../Draw.h"
#include <GLFW/glfw3.h>

/**
*	@brief This class represents a set of points distributed in the space.
*	@author Lidia Mª Ortega Alvarado.
*/
class PointCloud3d {
protected:
	std::vector<Vect3d> _points;
	Vect3d _maxPoint, _minPoint;						// AABB.
	Vect3d _maxPointIndex, _minPointIndex;				// Indices of those vertices which have the boundary coordinates of the mesh.


protected:
	/**
	*	@brief Updates the new maximum and minimum points taking into account a new point.
	*/
	void updateMaxMin(int index);

public:
	/**
	*	@brief Default constructor.
	*/
	PointCloud3d();

	/**
	*	@brief Loads the point cloud from a file.
	*/
	PointCloud3d(const std::string& filename);

	/**
*	@brief Construct the point cloud from a vector of points
*/
	PointCloud3d(std::vector<Vect3d>& pointCloud);

	/**
	*	@brief Constructor.
	*/
	PointCloud3d(int size, float max_x, float max_y, float max_z);

	/**
	*	@brief Constructor.
	*/
	PointCloud3d(int size, Vect3d min, Vect3d max);

	/**
	*	@brief Alternative constructor with an uniform sphere distribution.
	*/
	PointCloud3d(int size, float radius);

	/**
	*	@brief Copy constructor.
	*/
	PointCloud3d(const PointCloud3d& pointCloud);

	/**
	*	@brief Destructor.
	*/
	virtual ~PointCloud3d();

	/**
	*	@brief Adds a new point to the cloud.
	*/
	void addPoint(Vect3d& p);

	/**
	*	@brief Removes all the points.
	*/
	void clear() {
		_points.clear();
	}

	/**
	*	@brief Deletes the data saved from the convex hull step by step process.
	*/
	//void forgetConvexHullData() { delete _convexHullData; _convexHullData = nullptr; }

	/**
	*	@brief Returns the bounding box that delimites the point cloud space.
	*/
	AABB getAABB();

	/**
	*	@brief Generates a complete convex hull.
	*/
	//TriangleMesh* getConvexHull();

	/**
	*	@brief Generates the next triangle from the current convex hull.
	*/
	//TriangleMesh* getConvexHullNextTriangle();

	/**
	*	@brief Returns a certain point.
	*/
	Vect3d getPoint(int pos);

	/**
	*	@brief Returns all the cloud points.
	*/
	std::vector<Vect3d> getPoints() {
		return _points;
	}

	/**
	*	@brief Assigment operator.
	*/
	virtual PointCloud3d& operator=(const PointCloud3d& pointCloud);

	/**
	*	@brief Saves the cloud points in a file.
	*/
	void save(const std::string& filename);

	/**
	*	@brief Returns the number of points that this cloud contains.
	*/
	int size() {
		return _points.size();
	}

	/**
	*    @brief get the index of the most distanced points in the cloud.
	*/

	void getMostDistanced(int& a, int& b);

	/**
	 * Elige k puntos de forma aleatoria considerándolos potenciales centroides de las k clusters y que itera hasta encontrar los centroides adecuados.
	 *
	 * \param k nº de clusters
	 * \return Vector donde cada posicion es uno de los clusters
	 */
	std::vector<std::vector<Vect3d>> kmeans_naive(const int k, const int maxIterations);

	void kmeans_naive_auto_update(const int k, const int maxIterations, GLFWwindow* ventana);

	std::vector<std::vector<Vect3d>> kmeans_grid(const int k, const int maxIterations);

	void kmeans_grid_auto_update(const int k, const int maxIterations, GLFWwindow* ventana);

	static TypeColor getClusterColor(int index, int k);
};



#endif /* PONTCLOUD3D_H */

