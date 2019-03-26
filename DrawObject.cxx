# include "DrawObject.h"


void ThreeD_Object::DrawCube () {
    double edge = 1;
     glBegin(GL_QUAD_STRIP);
     glNormal3f(0,0,edge);
     glVertex3f(0,0,0);
     glVertex3f(0,edge,0);
     glVertex3f(edge,0,0);
     glVertex3f(edge,edge,0); //first front face
     glNormal3f(edge,0,0);
     glVertex3f(edge,0,-edge);
     glVertex3f(edge,edge,-edge); // right side face
     glNormal3f(edge,0,-edge);
     glVertex3f(0,0,-edge);
     glVertex3f(0,edge,-edge); // face on the back
     glNormal3f(-edge,0,0);
     glVertex3f(0,0,0);
     glVertex3f(0,edge,0); // face on the left
     glEnd();  
     glBegin(GL_QUADS);
     glNormal3f(0,edge+1,0);
     glVertex3f(0,edge,0);
     glVertex3f(edge,edge,0);
     glVertex3f(edge,edge,-edge);
     glVertex3f(0,edge,-edge);
     glNormal3f(0,-1,0);
     glVertex3f(0,0,0);
     glVertex3f(edge,0,0);
     glVertex3f(edge,0,-edge);
     glVertex3f(0,0,-edge);
     glEnd();  
}

std::vector<Triangle> 
ThreeD_Object::SplitTriangle(std::vector<Triangle> &list)
   {
       std::vector<Triangle> output(4*list.size());
       for (unsigned int i = 0 ; i < list.size() ; i++)
       {
           double mid1[3], mid2[3], mid3[3];
           mid1[0] = (list[i].X[0]+list[i].X[1])/2;
           mid1[1] = (list[i].Y[0]+list[i].Y[1])/2;
           mid1[2] = (list[i].Z[0]+list[i].Z[1])/2;
           mid2[0] = (list[i].X[1]+list[i].X[2])/2;
           mid2[1] = (list[i].Y[1]+list[i].Y[2])/2;
           mid2[2] = (list[i].Z[1]+list[i].Z[2])/2;
           mid3[0] = (list[i].X[0]+list[i].X[2])/2;
           mid3[1] = (list[i].Y[0]+list[i].Y[2])/2;
           mid3[2] = (list[i].Z[0]+list[i].Z[2])/2;
           output[4*i+0].X[0] = list[i].X[0];
           output[4*i+0].Y[0] = list[i].Y[0];
           output[4*i+0].Z[0] = list[i].Z[0];
           output[4*i+0].X[1] = mid1[0];
           output[4*i+0].Y[1] = mid1[1];
           output[4*i+0].Z[1] = mid1[2];
           output[4*i+0].X[2] = mid3[0];
           output[4*i+0].Y[2] = mid3[1];
           output[4*i+0].Z[2] = mid3[2];
           output[4*i+1].X[0] = list[i].X[1];
           output[4*i+1].Y[0] = list[i].Y[1];
           output[4*i+1].Z[0] = list[i].Z[1];
           output[4*i+1].X[1] = mid2[0];
           output[4*i+1].Y[1] = mid2[1];
           output[4*i+1].Z[1] = mid2[2];
           output[4*i+1].X[2] = mid1[0];
           output[4*i+1].Y[2] = mid1[1];
           output[4*i+1].Z[2] = mid1[2];
           output[4*i+2].X[0] = list[i].X[2];
           output[4*i+2].Y[0] = list[i].Y[2];
           output[4*i+2].Z[0] = list[i].Z[2];
           output[4*i+2].X[1] = mid3[0];
           output[4*i+2].Y[1] = mid3[1];
           output[4*i+2].Z[1] = mid3[2];
           output[4*i+2].X[2] = mid2[0];
           output[4*i+2].Y[2] = mid2[1];
           output[4*i+2].Z[2] = mid2[2];
           output[4*i+3].X[0] = mid1[0];
           output[4*i+3].Y[0] = mid1[1];
           output[4*i+3].Z[0] = mid1[2];
           output[4*i+3].X[1] = mid2[0];
           output[4*i+3].Y[1] = mid2[1];
           output[4*i+3].Z[1] = mid2[2];
           output[4*i+3].X[2] = mid3[0];
           output[4*i+3].Y[2] = mid3[1];
           output[4*i+3].Z[2] = mid3[2];
       }
       return output;
   }

void ThreeD_Object::DrawSphere()
   {
       int recursionLevel = 3;
       Triangle t;
       t.X[0] = 1;
       t.Y[0] = 0;
       t.Z[0] = 0;
       t.X[1] = 0;
       t.Y[1] = 1;
       t.Z[1] = 0;
       t.X[2] = 0;
       t.Y[2] = 0;
       t.Z[2] = 1;
       std::vector<Triangle> list;
       list.push_back(t);
       for (int r = 0 ; r < recursionLevel ; r++)
       {
           list = SplitTriangle(list);
       }

       // really draw `
       for (int octent = 0 ; octent < 8 ; octent++)
       {
           glPushMatrix();
           glRotatef(90*(octent%4), 1, 0, 0);
           if (octent >= 4)
               glRotatef(180, 0, 0, 1);
           glBegin(GL_TRIANGLES);
           for (unsigned int i = 0 ; i < list.size() ; i++)
           {
               for (int j = 0 ; j < 3 ; j++)
               {
                   double ptMag = sqrt(list[i].X[j]*list[i].X[j]+
                                       list[i].Y[j]*list[i].Y[j]+
                                       list[i].Z[j]*list[i].Z[j]);
                   glNormal3f(list[i].X[j]/ptMag, list[i].Y[j]/ptMag, list[i].Z[j]/ptMag);
                   glVertex3f(list[i].X[j]/ptMag, list[i].Y[j]/ptMag, list[i].Z[j]/ptMag);
               }
           }
           glEnd();
           glPopMatrix();
       }
   }


   void ThreeD_Object::DrawCylinder()
   {
       int nfacets = 30;
       glBegin(GL_TRIANGLES);
       for (int i = 0 ; i < nfacets ; i++)
       {
           double angle = 3.14159*2.0*i/nfacets;
           double nextAngle = (i == nfacets-1 ? 0 : 3.14159*2.0*(i+1)/nfacets);
           glNormal3f(0,0,1);
           glVertex3f(0, 0, 1);
           glVertex3f(cos(angle), sin(angle), 1);
           glVertex3f(cos(nextAngle), sin(nextAngle), 1);
           glNormal3f(0,0,-1);
           glVertex3f(0, 0, 0);
           glVertex3f(cos(angle), sin(angle), 0);
           glVertex3f(cos(nextAngle), sin(nextAngle), 0);
       }
       glEnd();
       glBegin(GL_QUADS);
       for (int i = 0 ; i < nfacets ; i++)
       {
           double angle = 3.14159*2.0*i/nfacets;
           double nextAngle = (i == nfacets-1 ? 0 : 3.14159*2.0*(i+1)/nfacets);
           glNormal3f(cos(angle), sin(angle), 0);
           glVertex3f(cos(angle), sin(angle), 1);
           glVertex3f(cos(angle), sin(angle), 0);
           glNormal3f(cos(nextAngle), sin(nextAngle), 0);
           glVertex3f(cos(nextAngle), sin(nextAngle), 0);
           glVertex3f(cos(nextAngle), sin(nextAngle), 1);
       }
       glEnd();
   }

// ----------------- End of Phase 1: Basic Shapes

void ThreeD_Object::DrawWall(double width, double thickness, double height) {
  /*
    vtkJPEGReader *rdr = vtkJPEGReader::New();
    rdr -> SetFileName("fish.jpg");
    rdr -> Update();
    vtkImageData * img = rdr-> GetOutput();
    int dims[3];
    img->GetDimensions(dims);
    unsigned char *buffer = (unsigned char *)img -> GetScalarPointer(0,0,0);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,dims[0],dims[1],0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
    glEnable(GL_COLOR_MATERIAL);
    
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glEnable(GL_TEXTURE_2D);
    float ambient[3] = {1,1,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,ambient);
    */
    // draw wall
    LightYellow();
    glPushMatrix();
    glScalef(width,height,thickness);
    DrawCube();
    glPopMatrix();
  }



void ThreeD_Object::DrawTable() {
  /*
    vtkJPEGReader *rdr = vtkJPEGReader::New();
    rdr -> SetFileName("Texture_white_coffee.jpg");
    rdr -> Update();
    vtkImageData * img = rdr-> GetOutput();
    int dims[3];
    img->GetDimensions(dims);
    unsigned char *buffer = (unsigned char *)img -> GetScalarPointer(0,0,0);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,dims[0],dims[1],0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
    glEnable(GL_COLOR_MATERIAL);
    
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glEnable(GL_TEXTURE_2D);
    float ambient[3] = {1,1,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,ambient);
    */
    double table_width = 4;
    double table_length = 3;
    double table_height = 2;
    // draw table
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(table_length,0.5,table_width);
    DrawCube();
    glPopMatrix();
    // draw 4 legs
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.4,-0.4,0);
    glScalef(0.2,0.2,3);
    DrawCylinder();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.4,-table_width+0.4,0);
    glScalef(0.2,0.2,3);
    DrawCylinder();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(table_length-0.4,-0.4,0);
    glScalef(0.2,0.2,3);
    DrawCylinder();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(table_length-0.4,-table_width+0.4,0);
    glScalef(0.2,0.2,3);
    DrawCylinder();
    glPopMatrix();

}

void ThreeD_Object::DrawSymposium() {
  /*
    vtkJPEGReader *rdr = vtkJPEGReader::New();
    rdr -> SetFileName("Texture_dark_wood.jpg");
    rdr -> Update();
    vtkImageData * img = rdr-> GetOutput();
    int dims[3];
    img->GetDimensions(dims);
    unsigned char *buffer = (unsigned char *)img -> GetScalarPointer(0,0,0);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,dims[0],dims[1],0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
    glEnable(GL_COLOR_MATERIAL);
    
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glEnable(GL_TEXTURE_2D);
    float ambient[3] = {1,1,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,ambient);
    */
    double sym_height = 2;
    
    // draw base
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(1,sym_height,1);
    DrawCube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(30,0,0,1);
    glTranslatef(0.8*sym_height,0.6*sym_height,-0.15);
    glScalef(0.9,0.1,0.7);
    DrawCube();
    glPopMatrix();
}


void ThreeD_Object::DrawStage() {
  double stage_l = 6;
  double stage_w = 3;
  double stage_h = 0.5;

  // draw base
  Orange();
  glPushMatrix();
  glTranslatef(0,0,0);
  glScalef(stage_l,stage_h,stage_w);
  DrawCube();
  glPopMatrix();
}

void ThreeD_Object::DrawDoor() {
  double objThickness =1;
  // 6ft 8 inches (203.2cm), by 2ft(60.96) around 3:1

  // top frame
  glPushMatrix();
  White();
  glTranslatef(0,objThickness*17,0);
  glScalef(objThickness*10,objThickness,objThickness);
  DrawCube();
  glPopMatrix();

  // two side frame
  glPushMatrix();
  glTranslatef(-0.8,0,0);
  glScalef(objThickness,objThickness*18,objThickness);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(objThickness*10,0,0);
  glScalef(objThickness,objThickness*18,objThickness);
  DrawCube();
  glPopMatrix();

  // Door
  glPushMatrix();
  Orange();
  glTranslatef(0,0,0),
  glScalef(objThickness*10,objThickness*17,0.5*objThickness);
  DrawCube();
  glPopMatrix();

  // door handle
  glPushMatrix();
  Silver();
  glTranslatef(objThickness*2,objThickness*8,-objThickness);
  glScalef(objThickness*0.3,objThickness*0.3,objThickness*0.3);
  DrawCylinder();
  glPopMatrix();

  glPushMatrix();
  Silver();
  glTranslatef(objThickness*2,objThickness*8,-objThickness*1.2);
  glScalef(objThickness*0.5,objThickness*0.5,objThickness*0.3);
  DrawSphere();
  glPopMatrix();
}

void ThreeD_Object::DrawWindow() {
  double frameThickness=0.5;
  double frameHeight = 8;

  // frames: 3 horizontle
  White();
  glPushMatrix();
  glTranslatef(0,0,0);
  glScalef(frameThickness*5,frameThickness,frameThickness/2);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,frameHeight/2,0);
  glScalef(frameThickness*5,frameThickness,frameThickness/2);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,frameHeight,0);
  glScalef(frameThickness*5,frameThickness,frameThickness/2);
  DrawCube();
  glPopMatrix();

  // frame: 2 side
  glPushMatrix();
  glTranslatef(0,0,0);
  glScalef(frameThickness,frameHeight,frameThickness/2);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(frameThickness*5,0,0);
  glScalef(frameThickness,frameHeight+frameThickness,frameThickness/2);
  DrawCube();
  glPopMatrix();

  // glass of window
  glPushMatrix();
  Glass();
  glTranslatef(frameThickness,frameThickness,0);
  glScalef(frameThickness*4,frameHeight-frameThickness,frameThickness/4);
  DrawCube();
  glPopMatrix();
}

void ThreeD_Object::DrawBlackBoard() {
  // frames: 3 horizontle
  double board_w = 10;
  double board_h = 2;
  double board_thick = 0.4;

  // frame top and bottom
  White();
  glPushMatrix();
  glTranslatef(0,2,0);
  glScalef(board_w,board_thick,board_thick/2);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,2+board_thick+board_h,0);
  glScalef(board_w,board_thick,board_thick/2);
  DrawCube();
  glPopMatrix();

  // frame: 2 side
  glPushMatrix();
  glTranslatef(0,2+board_thick,0);
  glScalef(board_thick,board_h+board_thick,board_thick/2);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(board_w,2,0);
  glScalef(board_thick,board_h+2*board_thick,board_thick/2);
  DrawCube();
  glPopMatrix();

  // board
  glPushMatrix();
  BlackBoard();
  glTranslatef(board_thick,board_thick+2,0);
  glScalef(board_w-board_thick,board_h,0.1);
  DrawCube();
  glPopMatrix();
}

void ThreeD_Object::DrawChair() {
  

  // back frame
  glPushMatrix();
  Brown();
  glTranslatef(0,chair_side+1.3,0);
  glScalef(0.3,1.5,chair_side);
  DrawCube();
  glPopMatrix();

  // 3 columns at back
  glPushMatrix();
  DarkBrown();
  glTranslatef(0,chair_side,0);
  glScalef(0.3,1.3,0.3);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  DarkBrown();
  glTranslatef(0,chair_side,-chair_side/2);
  glScalef(0.3,1.3,0.3);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  DarkBrown();
  glTranslatef(0,chair_side,-chair_side+0.3);
  glScalef(0.3,1.3,0.3);
  DrawCube();
  glPopMatrix();

  // support for table panel
  glPushMatrix();
  DarkBrown();
  glTranslatef(0.4*chair_side,chair_side+0.1,0);
  glRotatef(-20,0,0,1);
  glScalef(0.2,1.65,0.2);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  DarkBrown();
  glTranslatef(0.7*chair_side,chair_side,0);
  glScalef(0.2,1.5,0.2);
  DrawCube();
  glPopMatrix();

  // table panel
  glPushMatrix();
  LightBrown();
  glTranslatef(0.4*chair_side,chair_side+1.5,0);
  glScalef(0.5*chair_side,0.2,0.8*chair_side);
  DrawCube();
  glPopMatrix();
  

  // base
  glPushMatrix();
  Brown();
  glTranslatef(0,chair_side,0);
  glScalef(chair_side,0.15,chair_side);
  DrawCube();
  glPopMatrix();

  // draw legs
  glPushMatrix();
  DarkBrown();
  glTranslatef(0.8*chair_side,0,-0.1*chair_side);
  glScalef(0.5,chair_side,0.5);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  DarkBrown();
  glTranslatef(0.1*chair_side,0,-0.1*chair_side);
  glScalef(0.5,chair_side,0.5);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  DarkBrown();
  glTranslatef(0.1*chair_side,0,-0.8*chair_side);
  glScalef(0.5,chair_side,0.5);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  DarkBrown();
  glTranslatef(0.8*chair_side,0,-0.8*chair_side);
  glScalef(0.5,chair_side,0.5);
  DrawCube();
  glPopMatrix();
}

// ----------------- End of Phase 2: Objects develop from basic shapes


void ThreeD_Object::DrawPlainClassroom(double length, double width,double height) {
  // draw floor
  glPushMatrix();
  glTranslatef(0,0,0);
  glScalef(length,0.1,width);
  DrawCube();
  glPopMatrix();

  // draw back wall
  glPushMatrix();
  glTranslatef(0,0,0);
  DrawWall(length,wall_thickness,height);
  glPopMatrix();

  // black board
  glPushMatrix();
  glTranslatef(0.08*length,-2.5,-wall_thickness);
  glScalef(2.5,2,0);
  DrawBlackBoard();
  glPopMatrix();

  // stage
  glPushMatrix();
  glTranslatef(0.15*length,0,0);
  glScalef(3.5,1,1);
  DrawStage();
  glPopMatrix();

  
  // table on left side
  glPushMatrix();
  glTranslatef(0.85*length,3,-0.5);
  glScalef(1,1,1);
  DrawTable();
  glPopMatrix();


  // Symposium
  glPushMatrix();
  glTranslatef(0.15*length,0,-3);
  glRotatef(90,0,1,0);
  glScalef(1,2,1);
  DrawSymposium();
  glPopMatrix();

  // left wall + windows
  glPushMatrix();
  glTranslatef(length,0,0);
  DrawWall(wall_thickness,width,height);
  glPopMatrix();

  
  double interval = width/3;
  double start_pos = 0.1*width;
  glPushMatrix();
  glRotatef(90,0,1,0);
  glTranslatef(start_pos,0.3*height,length);
  glScalef(0.8,0.5,0.5);
  DrawWindow();
  glPopMatrix();

  start_pos += interval;

  glPushMatrix();
  glRotatef(90,0,1,0);
  glTranslatef(start_pos,0.3*height,length);
  glScalef(0.8,0.5,0.5);
  DrawWindow();
  glPopMatrix();

  start_pos += interval;

  glPushMatrix();
  glRotatef(90,0,1,0);
  glTranslatef(start_pos,0.3*height,length);
  glScalef(0.8,0.5,0.5);
  DrawWindow();
  glPopMatrix();

  // right wall + door
  glPushMatrix();
  glTranslatef(0,0,0);
  DrawWall(wall_thickness,width,height);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90,0,1,0);
  glTranslatef(0.2*width,0,wall_thickness/2);
  glScalef(0.3,0.4,1);
  DrawDoor();
  glPopMatrix();

  // wall at back
  
  glPushMatrix();
  glTranslatef(0,0,-width);
  DrawWall(length+wall_thickness,wall_thickness,height);
  glPopMatrix();
  
}

void ThreeD_Object::DrawClassroom(double length,double width, double height,int capacity) {
  glPushMatrix();
  glTranslatef(0,0,0);
  DrawPlainClassroom(length,width,height);
  glPopMatrix();

  double rescale = 0.7;
  double rowStart = -0.6*width;
  double columnStart = -0.05*length;

  double max_width = 0.8*width;
  double max_length = length;
  /*
  To calculate the number of chair in a row (a), and column(b), use function
  a = floor ( (C(capacity) * max_length / max_width) / 2.7) // 2.7 = chair_side * rescale
  b = floor (C / a)
  */
  double raw_a = pow(capacity*max_length/max_width,0.5);
  int a = floor (raw_a / (chair_side*rescale));
  int b = floor (capacity/a);

  double interval_between_row = max_width / (a-1);
  double interval_between_column = max_length / (b-1);

  cout <<"a is: "<<a<<". b is: "<<b<<endl;

  cout<<"interval_between_row is: "<<interval_between_row<<", interval_beteen_column is: "<<interval_between_row<<endl;

  
  glRotatef(-90,0,1,0);
  glScalef(rescale,rescale,rescale);
  // Translatef: (x,y,z): -z: Left +z: right; +y:Up, -y:Down; +x: behind board, -x:in room
  
  
/*
  for (int row=0; row<a; a++) {
    for (int column=0; column<b; b++) {
      glPushMatrix();
      glTranslatef(rowStart-row*interval_between_row,0,columnStart-column*interval_between_column);       
      DrawChair();
      glPopMatrix();
    }
  }
*/

  // first row
  glPushMatrix();
  glTranslatef(rowStart-0*interval_between_row,0,columnStart-0*interval_between_column); 
  DrawChair();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(rowStart-0*interval_between_row,0,columnStart-1*interval_between_column); 
  DrawChair();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(rowStart-0*interval_between_row,0,columnStart-2*interval_between_column); 
  DrawChair();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(rowStart-0*interval_between_row,0,columnStart-3*interval_between_column); 
  DrawChair();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(rowStart-0*interval_between_row,0,columnStart-4*interval_between_column); 
  DrawChair();
  glPopMatrix();

  // second row
  glPushMatrix();
  glTranslatef(rowStart-0.5*interval_between_row,0,columnStart-0*interval_between_column); 
  DrawChair();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(rowStart-0.5*interval_between_row,0,columnStart-1*interval_between_column); 
  DrawChair();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(rowStart-0.5*interval_between_row,0,columnStart-2*interval_between_column); 
  DrawChair();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(rowStart-0.5*interval_between_row,0,columnStart-3*interval_between_column); 
  DrawChair();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(rowStart-0.5*interval_between_row,0,columnStart-4*interval_between_column); 
  DrawChair();
  glPopMatrix();
  
}


vtkActor *
ThreeD_Object::ReadOBJ(string fileName) {
    vtkOBJReader *objReader = vtkOBJReader::New();
    objReader -> SetFileName(fileName.c_str());

    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(0.1,0.5,0.5);
    glPopMatrix();
    objReader -> Update();

    vtkPolyDataMapper * mapper = vtkPolyDataMapper::New();
    mapper -> SetInputConnection(objReader -> GetOutputPort());

    vtkActor * actor = vtkActor::New();
    actor->SetMapper(mapper);

    return actor;

    /*
    vtkRenderer * renderer = vtkRenderer::New();
    renderer -> AddActor(actor);

    vtkRenderWindow * renderWindow = vtkRenderWindow::New();
    renderWindow -> AddRenderer(renderer);

    vtkRenderWindowInteractor * renderWindowInteractor = vtkRenderWindowInteractor::New();
    renderWindowInteractor -> SetRenderWindow(renderWindow);

    renderWindowInteractor -> Start();
    */
    
}