/*=========================================================================

  Program:   Visualization Toolkit
  Module:    SpecularSpheres.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This examples demonstrates the effect of specular lighting.
//
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

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>

#include <vector>
#include "DrawObject.h"


class vtk441Mapper : public vtkOpenGLPolyDataMapper
{
  protected:
   GLuint displayList;
   bool   initialized;

  public:
   vtk441Mapper()
   {
     initialized = false;
   }
    
   void
   RemoveVTKOpenGLStateSideEffects()
   {
     float Info[4] = { 0, 0, 0, 1 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Info);
     float ambient[4] = { 1,1, 1, 1.0 };
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
     float diffuse[4] = { 1, 1, 1, 1.0 };
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
     float specular[4] = { 1, 1, 1, 1.0 };
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   }


   void SetupLight(void)
   {
       glEnable(GL_LIGHTING);
       glEnable(GL_LIGHT0);
       GLfloat diffuse0[4] = { 0.6, 0.6, 0.6, 1 };
       GLfloat ambient0[4] = { 0.2, 0.2, 0.2, 1 };
       GLfloat specular0[4] = { 0.0, 0.0, 0.0, 1 };
       GLfloat pos0[4] = { 0, .707, 0.707, 0 };
       glLightfv(GL_LIGHT0, GL_POSITION, pos0);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
       glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
       glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
       glEnable(GL_LIGHT1);
       GLfloat pos1[4] = { .707, -.707, 0 };
       glLightfv(GL_LIGHT1, GL_POSITION, pos1);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
       glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
       glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);
       glDisable(GL_LIGHT2);
       glDisable(GL_LIGHT3);
       glDisable(GL_LIGHT5);
       glDisable(GL_LIGHT6);
       glDisable(GL_LIGHT7);
   }
};

class vtk441MapperPart3 : public vtk441Mapper
{
 public:
   static vtk441MapperPart3 *New();
   
   GLuint displayList;
   bool   initialized;
   double headSize; // absolute terms
   double eyeballSize; // as proportion of headSize
   double eyeHeight; // as proportion of radius above center of sphere
   double pupilSize; // as proportion of eyeballSize
   double eyeAngle; // from center-line, in degrees.  

   vtk441MapperPart3()
   {
     initialized = false;
     headSize = 4;
     eyeballSize = 0.2;
     eyeHeight = 0.25;
     pupilSize = 0.25;
     eyeAngle = 22;
   }


   void Brown(void) { glColor3ub(205, 133, 63); };
   void LightBrown(void) { glColor3ub(245, 222, 179); };
   void DarkBrown(void) { glColor3ub(162, 82, 45); };
   void Pink(void) { glColor3ub(250, 128, 114); };
   void White(void) { glColor3ub(255, 255, 255); };
   void Black(void) { glColor3ub(0, 0, 0); };


   virtual void RenderPiece(vtkRenderer *ren, vtkActor *act)
   {
       RemoveVTKOpenGLStateSideEffects();
       SetupLight();
       glEnable(GL_COLOR_MATERIAL);
    
       glMatrixMode(GL_MODELVIEW);

       // draw a cube
       //Brown();
       glPushMatrix();
       //glTranslatef(2,2,0);
       //glScalef(4,4,4);
       ThreeD_Object threeD;
       //threeD.DrawCube();
       //threeD.DrawWall(2,2,0.2);
       //threeD.DrawTable();
       //threeD.DrawDoor();
       //threeD.DrawWindow();
       //threeD.DrawBlackBoard();  
       //threeD.DrawStage();
       //threeD.DrawChair();
       //threeD.DrawSymposium();
       // length, width, height
       //threeD.DrawPlainClassroom(30,20,10);
       // length, width, height, capacity
       threeD.DrawClassroom(30,20,10,10);
       glPopMatrix();
   }
};

vtkStandardNewMacro(vtk441MapperPart3);


int main()
{
  // Dummy input so VTK pipeline mojo is happy.
  //
  

  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetThetaResolution(100);
  sphere->SetPhiResolution(50);

  vtkSmartPointer<vtk441MapperPart3> win3Mapper =
    vtkSmartPointer<vtk441MapperPart3>::New();
  win3Mapper->SetInputConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> win3Actor =
    vtkSmartPointer<vtkActor>::New();
  win3Actor->SetMapper(win3Mapper);

  // now add read obj
  // finally shows together~~~!! 
  //ThreeD_Object threeD;
  //vtkActor * actor = threeD.ReadOBJ("tinker.obj");
  // but, how to cooperate/put "tinker" in a certain location is still not solved

  vtkSmartPointer<vtkRenderer> ren3 =
    vtkSmartPointer<vtkRenderer>::New();
    //ren3 -> AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren3);
  ren3->SetViewport(0, 0, 1, 1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size.
  //
  bool doWindow3 = true;
  if (doWindow3)
      ren3->AddActor(win3Actor);
  ren3->SetBackground(0.3, 0.3, 0.3);
  renWin->SetSize(1000, 1000);

  // Set up the lighting.
  //
  vtkSmartPointer<vtkLight> light =
    vtkSmartPointer<vtkLight>::New();
  light->SetFocalPoint(1.875,0.6125,0);
  light->SetPosition(0.875,1.6125,1);
  ren3->AddLight(light);


  ren3->GetActiveCamera()->SetFocalPoint(7,0,-5); //(x,y,z),x+: move to right
  ren3->GetActiveCamera()->SetPosition(0,0,-70); //10,2,-40
  ren3->GetActiveCamera()->SetViewUp(0,1,0);
  ren3->GetActiveCamera()->SetClippingRange(10, 200);
  ren3->GetActiveCamera()->SetDistance(70);
  
  // This starts the event loop and invokes an initial render.
  //
  ((vtkInteractorStyle *)iren->GetInteractorStyle())->SetAutoAdjustCameraClippingRange(0);
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}




