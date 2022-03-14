/**
 * @file main.cpp
 *
 * @author lidia
 *
 * @brief Función main y callbacks
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "windows.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
 //#include <glm/gtx/transform.hpp>
#include "Scene.h"

#include "InclGeom2D.h"
#include "InclDraw2D.h"
#include "Bezier.h"
#include "DrawBezier.h"
#include "3d/Plane.h"
#include "3d/DrawPlane.h"
#include "3d/DrawLine3d.h"
#include "3d/DrawVect3d.h"
#include "3d/PointCloud3d.h"
#include "3d/DrawSegment3d.h"
#include "3d/DrawCloud3d.h"
#include "3d/DrawAABB.h"
#include "3d/TriangleModel.h"
#include "3d/DrawTriangleModel.h"
#include "3d/DrawTriangle3d.h"


Movements movimientoActivo = Movements::NONE;
bool botonPulsado = false;
double ratonX = 0;
double ratonY = 0;
int modeloActivo = -1;


void mostrarAyuda() {
	std::cout << "Ayuda" << std::endl
		<< "================" << std::endl
		<< "s -> Apartado a" << std::endl
		<< "l -> Apartado b" << std::endl
		<< "y -> Apartado c" << std::endl
		<< "r -> Resetea la escena" << std::endl
		<< "Cursores y rueda ratón -> Rotación" << std::endl
		<< "h -> Muestra esta ayuda" << std::endl
		<< "q -> Cierra la aplicación" << std::endl;
}


void refresWindow(GLFWwindow* ventana) {
	try {
		Scene::getInstance()->refresh();
	} catch (std::runtime_error& e) {
		std::cout << "Exception on refeshWindow"
			<< std::endl
			<< "=============================================="
			<< std::endl
			<< e.what() << std::endl;
	}

	glfwSwapBuffers(ventana);
}


void callbackTamFB(GLFWwindow* ventana, int ancho, int alto) {
	Scene::getInstance()->changeTamViewport(ancho, alto);
}


// Implementado después de la función main
void callbackKey(GLFWwindow* ventana, int tecla, int scancode, int accion,
	int modificadores);


void callbackMouseButton(GLFWwindow* ventana, int boton, int accion,
	int modificadores) {
	if (boton == 0) {
		if (accion == GLFW_PRESS) {
			botonPulsado = true;
			glfwGetCursorPos(ventana, &ratonX, &ratonY);
		}

		if (accion == GLFW_RELEASE) {
			botonPulsado = false;
			ratonX = 0;
			ratonY = 0;
		}
	}
}


void callbackMouseMovevent(GLFWwindow* ventana, double posX, double posY) {
	static clock_t ultimaEjecucion = clock();   // Se inicializa una única vez

	movimientoActivo = Movements::ORBIT;

	if (botonPulsado)
		if ((clock() - ultimaEjecucion) > 10) {
			double incX = posX - ratonX;
			double incY = posY - ratonY;

			Scene::getInstance()->moveCamera(movimientoActivo, incY, incX);

			ratonX = posX;
			ratonY = posY;
			refresWindow(ventana);
			ultimaEjecucion = clock();
			movimientoActivo = Movements::NONE;
		}
}


void callbackMouseWheel(GLFWwindow* ventana, double incX, double incY) {
	movimientoActivo = Movements::ZOOM;
	Scene::getInstance()->moveCamera(movimientoActivo, -incY);
	refresWindow(ventana);
	movimientoActivo = Movements::NONE;
}


int main(int argc, char** argv) {
	std::cout << "Prácticas de algoritmos Geométricos" << std::endl;

	if (glfwInit() != GLFW_TRUE) {
		std::cout << "Fallo al inicializar GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	GLFWwindow* miVentana;
	miVentana = glfwCreateWindow(1024, 576, "Algoritmos Geométricos", nullptr, nullptr);

	if (miVentana == nullptr) {
		std::cout << "Fail wheb initializing GLFW" << std::endl;
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(miVentana);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Fail wheb initializing GLEW" << std::endl;
		glfwDestroyWindow(miVentana);
		glfwTerminate();
		return -3;
	}

	std::cout << glGetString(GL_RENDERER) << std::endl
		<< glGetString(GL_VENDOR) << std::endl
		<< glGetString(GL_VERSION) << std::endl
		<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glfwSetWindowRefreshCallback(miVentana, refresWindow);
	glfwSetFramebufferSizeCallback(miVentana, callbackTamFB);
	glfwSetKeyCallback(miVentana, callbackKey);
	glfwSetMouseButtonCallback(miVentana, callbackMouseButton);
	glfwSetScrollCallback(miVentana, callbackMouseWheel);
	glfwSetCursorPosCallback(miVentana, callbackMouseMovevent);

	mostrarAyuda();

	try {
		Scene::getInstance()->setScene(1024, 576);


		while (!glfwWindowShouldClose(miVentana)) {
			glfwPollEvents();
		}
	} catch (std::runtime_error& e) {
		std::cout << "Excepction captured: " << e.what() << std::endl;
		glfwWindowShouldClose(miVentana);
	}

	std::cout << "End of application" << std::endl;
	glfwDestroyWindow(miVentana);
	miVentana = nullptr;
	glfwTerminate();
}


void callbackKey(GLFWwindow* ventana, int tecla, int scancode, int accion,
	int modificadores) {
	GLfloat f = 0;

	switch (tecla) {
	case GLFW_KEY_Q:
		if (accion == GLFW_PRESS) {
			glfwSetWindowShouldClose(ventana, GLFW_TRUE);
		}
		break;

	case GLFW_KEY_M:
		if (accion == GLFW_PRESS) {
			try {
				Vect2d a(3.0, 2.0);
				Vect2d b(0.0, 0.0);
				Vect2d c(-2.0, 1.0);

				Triangle t1(a, b, c);
				DrawTriangle* dt1 = new DrawTriangle(t1);
				TypeColor magenta(1.0, 0.0, 1.0);
				dt1->drawIt(magenta);
				dt1 = nullptr;
			} catch (std::exception& e) {
				std::cout << "Exception captured in callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refresWindow(ventana);
		}
		break;

	case GLFW_KEY_S:
		if (accion == GLFW_PRESS) {
			try {
				//Crear una nube de puntos aleatoria de tamaño 50
				PointCloud3d cloud(50, 5.0f, 5.0f, 5.0f);
				DrawCloud3d* drawCloud = new DrawCloud3d(cloud);
				drawCloud->drawIt({ 0, 1, 0 });

				//Encontrar los puntos más alejados (getMostDistanced), crear el segmento asociado y pintarlo.
				int a, b;
				cloud.getMostDistanced(a, b);
				Segment3d segment(cloud.getPoint(a), cloud.getPoint(b));
				DrawSegment3d* drawSegment = new DrawSegment3d(segment);
				drawSegment->drawIt({ 1, 0, 0 });

				//Calcular el punto más distanciado a la recta que contiene al segmento anterior y pintarla.
				Line3d line(segment.getOrigin(), segment.getDestination());
				auto points = cloud.getPoints();
				float maxDist = -FLT_MAX;
				Vect3d p;
				for (auto point : points) {
					float dist = line.distance(point);
					if (dist > maxDist) {
						maxDist = dist;
						p = point;
					}
				}
				line = line.normalLine(p);
				DrawLine3d* drawLine = new DrawLine3d(line);
				drawLine->drawIt({ 1, 0, 1 });

				//Calcular y dibujar la caja envolvente de la nube de puntos.
				AABB aabb(cloud.getAABB());
				DrawAABB* drawAABB = new DrawAABB(aabb);
				drawAABB->drawIt({ 0, 0, 1 });
				Vect3d v1(aabb.getMin().getX(), aabb.getMin().getY(), aabb.getMin().getZ());
				Vect3d v2(aabb.getMax().getX(), aabb.getMin().getY(), aabb.getMin().getZ());
				Vect3d v3(aabb.getMin().getX(), aabb.getMin().getY(), aabb.getMax().getZ());
				Plane plano(v1, v2, v3, true);
				DrawPlane* drawPlane = new DrawPlane(plano);
				drawPlane->drawIt({ 1, 1, 0 , 0.2 });

				bool found = false;
				while (!found) {
					int a = rand() % points.size();
					int b = rand() % points.size();
					Line3d l(points[a], points[b]);
					found = plano.intersect(l, p);
					if (found) {
						drawLine = new DrawLine3d(l);
						drawLine->drawIt({ 1, 0, 0 });
					}

				}
				DrawVect3d* drawPoint = new DrawVect3d(p);
				drawPoint->drawIt({ 1, 0, 0 });

			} catch (std::exception& e) {
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refresWindow(ventana);
		}
		break;


	case GLFW_KEY_P:
		if (accion == GLFW_PRESS) {
			try {
				Point a(0.0, 0.0);
				DrawPoint* da = new DrawPoint(a);
				da->drawIt();
				da = nullptr;
			} catch (std::exception& e) {
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refresWindow(ventana);
		}
		break;

	case GLFW_KEY_L:
		if (accion == GLFW_PRESS) {
			try {
				Vect3d a, b, c, d, e, f, g;
				a = { 0, 0, 0 };
				b = { 1, 0, 0 };
				c = { 0, 1, 0 };
				d = { 0, 1, 0 };
				e = { 0, 0, 1 };
				f = { 1, 0, 0 };
				g = { 0, 0, 1 };
				Plane planoA(a, b, c, true);
				Plane planoB(a, d, e, true);
				Plane planoC(a, f, g, true);
				DrawPlane* draw;
				draw = new DrawPlane(planoA);
				draw->drawIt({ 1, 0, 0, 0.5 });
				draw = new DrawPlane(planoB);
				draw->drawIt({ 0, 1, 0, 0.5 });
				draw = new DrawPlane(planoC);
				draw->drawIt({ 0, 0, 1, 0.5 });

				Line3d line3d;
				if (planoA.intersect(planoB, line3d)) {
					DrawLine3d* drawLine = new DrawLine3d(line3d);
					drawLine->drawIt();
				}

				Vect3d point;
				if (planoA.intersect(planoB, planoC, point)) {
					DrawVect3d* dVect = new DrawVect3d(point);
					dVect->drawIt({ 1, 0, 1 });
				}


			} catch (std::exception& e) {
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refresWindow(ventana);
		}
		break;

	case GLFW_KEY_Y:
		if (accion == GLFW_PRESS) {
			try {
				TriangleModel model("vacaSinNormales.obj");
				DrawTriangleModel* drawModel = new DrawTriangleModel(model);
				drawModel->drawIt();

				AABB aabb(model.getAABB());
				DrawAABB* drawAABB = new DrawAABB(aabb);
				drawAABB->drawIt({ 0, 0, 1 });
				DrawTriangle3d* drawTriangle;
				auto triangles(model.getFaces());
				for (auto& triangle : triangles) {
					for (size_t i = 0; i < 3; i++) {
						if (BasicGeometry::anyEqual(triangle[i], aabb.getMin()) || BasicGeometry::anyEqual(triangle[i], aabb.getMax())) {
							i = 3;
							drawTriangle = new DrawTriangle3d(triangle);
							drawTriangle->drawIt({ 1, 0, 0 });
						}
					}
				}

			} catch (std::exception& e) {
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refresWindow(ventana);
		}
		break;

	case GLFW_KEY_R:
		Scene::getInstance()->clearScene();
		refresWindow(ventana);
		break;

	case GLFW_KEY_1:
		if (accion == GLFW_PRESS) {
			Scene::getInstance()->setView(TypeView::PLANT);

			refresWindow(ventana);
		}
		break;
	case GLFW_KEY_2:
		if (accion == GLFW_PRESS) {
			Scene::getInstance()->setView(TypeView::ELEVATION);

			refresWindow(ventana);
		}
		break;
	case GLFW_KEY_3:
		if (accion == GLFW_PRESS) {
			Scene::getInstance()->setView(TypeView::PROFILE);

			refresWindow(ventana);
		}
		break;
	case GLFW_KEY_4:
		if (accion == GLFW_PRESS) {
			Scene::getInstance()->setView(TypeView::ISOMETRIC);

			refresWindow(ventana);
		}
		break;
	case GLFW_KEY_H:
		if (accion == GLFW_PRESS) {
			mostrarAyuda();
		}
		break;

	case GLFW_KEY_LEFT:
		f = -1;
	case GLFW_KEY_RIGHT:
		f = (f != -1) ? 1 : f;
		if (accion == GLFW_PRESS) {
			switch (movimientoActivo) {
			case Movements::DOLLY:
				Scene::getInstance()->moveCamera(movimientoActivo, f, 0);
				break;
			case Movements::ORBIT:
				Scene::getInstance()->moveCamera(movimientoActivo, 0, 10 * f);
				break;
			case Movements::PAN:
				Scene::getInstance()->moveCamera(movimientoActivo, f);
				break;
			case Movements::ZOOM:
			case Movements::CRANE:
			case Movements::TILT:
			default:
				break;
			}
		}

		refresWindow(ventana);
		break;
	case GLFW_KEY_UP:
		f = 1;
	case GLFW_KEY_DOWN:
		f = (f != 1) ? -1 : f;
		if (accion == GLFW_PRESS) {
			switch (movimientoActivo) {
			case Movements::TILT:
			case Movements::ZOOM:
				Scene::getInstance()->moveCamera(movimientoActivo, -f);
				break;
			case Movements::CRANE:
				Scene::getInstance()->moveCamera(movimientoActivo, f);
				break;
			case Movements::DOLLY:
				Scene::getInstance()->moveCamera(movimientoActivo, 0, -f);
				break;
			case Movements::ORBIT:
				Scene::getInstance()->moveCamera(movimientoActivo, -10 * f, 0);
				break;
			default:
				break;
			}
		}
		refresWindow(ventana);
		break;


	}

	//std::cout << "The End" << std::endl;
}
