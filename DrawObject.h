#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkInteractorStyle.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkLight.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkJPEGReader.h"
#include "vtkImageData.h"
#include <vtkOBJReader.h>
#include <vtkDataObjectAlgorithm.h>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>

#include <vector>
#include <string>
#include <math.h>

using namespace std;

class Triangle
{
  public:
      double         X[3];
      double         Y[3];
      double         Z[3];
};

class ThreeD_Object {
    public:
        
        Triangle triangle;
        double wall_thickness = 0.5;
        double chair_side = 3;
        
        void DrawCube();
        std::vector<Triangle> SplitTriangle(std::vector<Triangle> &list);
        void DrawSphere();
        void DrawCylinder();
        void DrawWall(double width, double thickness, double height);
        void DrawTable();
        void DrawSymposium();
        void DrawDoor();
        void DrawWindow();
        void DrawBlackBoard();
        void DrawStage();
        void DrawChair();
        void DrawPlainClassroom(double length, double width,double height);
        void DrawClassroom(double length, double width,double height,int capacity);
        

        void Brown(void) { glColor3ub(205, 133, 63); };
        void LightBrown(void) { glColor3ub(245, 222, 179); };
        void DarkBrown(void) { glColor3ub(162, 82, 45); };
        void Pink(void) { glColor3ub(250, 128, 114); };
        void White(void) { glColor3ub(255, 255, 255); };
        void Black(void) { glColor3ub(0, 0, 0); };
        void Orange(void) {glColor3ub(244, 143, 66); };
        void Silver(void) {glColor3ub(192,192,192);};
        void Glass(void) {glColor3ub(194, 247, 255); };
        void BlackBoard(void) {glColor3ub(49,52,58); };
        void LightYellow(void) {glColor3ub(255,250,205); };

        vtkActor * ReadOBJ(string fileName);
};