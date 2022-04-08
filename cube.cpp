//#include <GL/gl.h>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>

using namespace std;

struct rotate_vector{

  GLfloat angle, x, y, z;
};

GLfloat angle, aspect, cube_size;
GLint rot_x, rot_y, step_size, x1, x2, y1, y2, z1, z2, gap;
vector<rotate_vector> cube_rotations[3][3][3];

void set_camera()
{
  gluLookAt(0,80,200, 0,0,0, 0,1,0);
}

void reset_layers(){
  x1 = 0;
  x2 = 2;
  y1 = 0;
  y2 = 2;
  z1 = 0;
  z2 = 2;
}

void rotate_forward(GLfloat angle){

  vector<rotate_vector> layer[3][3];
  rotate_vector rotation;

  for(int i=0;i<3;i++)
  	for(int j=0;j<3;j++){
  	
  		if(x1 == x2){
  			rotation = {angle,1.0,0.0,0.0};
  			if(i==0){
  				layer[2-j][0] = cube_rotations[x2][i][j];
  				layer[2-j][0].push_back(rotation);
  			}
  			if(i==1){
  				layer[2-j][1] = cube_rotations[x2][i][j];
  				layer[2-j][1].push_back(rotation);
  			}
  			if(i==2){
  				layer[2-j][2] = cube_rotations[x2][i][j];
  				layer[2-j][2].push_back(rotation);
  			}	
  		}
  		
  		if(y1 == y2){
  			rotation = {angle,0.0,1.0,0.0};
  			layer[j][2-i] = cube_rotations[i][y2][j];
  			layer[j][2-i].push_back(rotation);
  		}
  		
  		if(z1 == z2){
  			rotation = {angle,0.0,0.0,1.0};
  			
  			if(j==2){
  				layer[0][i] = cube_rotations[i][j][z2];
  				layer[0][i].push_back(rotation);
  			}
  			if(j==1){
  				layer[1][i] = cube_rotations[i][j][z2];
  				layer[1][i].push_back(rotation);
  			}
  			if(j==0){
  				layer[2][i] = cube_rotations[i][j][z2];
  				layer[2][i].push_back(rotation);
  			}
  		}
  	}

   for(int i = 0; i < 3; ++i)
      for(int j = 0; j < 3; ++j) {

         if(x1 == x2)
            cube_rotations[x2][i][j] = layer[i][j];

         if(y1 == y2)
            cube_rotations[i][y2][j] = layer[i][j];

         if(z1 == z2)
            cube_rotations[i][j][z2] = layer[i][j];
      }
}

void rotate_backward(GLfloat angle){

  vector<rotate_vector> layer[3][3];
  int index;
  rotate_vector rotation;

  for(int i=0;i<3;i++)
  	for(int j=0;j<3;j++){
  	
  		if(x1 == x2){
  			rotation = {angle,1.0,0.0,0.0};
  			
  			if(j==2){
  				layer[2][2-i] = cube_rotations[x2][i][j];
  				layer[2][2-i].push_back(rotation);
  			}
  			if(j==1){
  				layer[1][2-i] = cube_rotations[x2][i][j];
  				layer[1][2-i].push_back(rotation);
  			}
  			if(j==0){
  				layer[0][2-i] = cube_rotations[x2][i][j];
  				layer[0][2-i].push_back(rotation);
  			}	
  		}
  		
  		if(y1 == y2){
  			rotation = {angle,0.0,1.0,0.0};

			if(j==2){
  				layer[0][i] = cube_rotations[i][y2][j];
  				layer[0][i].push_back(rotation);
  			}
  			if(j==1){
  				layer[1][i] = cube_rotations[i][y2][j];
  				layer[1][i].push_back(rotation);
  			}
  			if(j==0){
  				layer[2][i] = cube_rotations[i][y2][j];
  				layer[2][i].push_back(rotation);
  			}
  		}
  		
  		if(z1 == z2){
  			rotation = {angle,0.0,0.0,1.0};

  			layer[j][2-i] = cube_rotations[i][j][z2];
  			layer[j][2-i].push_back(rotation);
  		}
  	}

   for(int i = 0; i < 3; ++i)
      for(int j = 0; j < 3; ++j) {

         if(x1 == x2)
            cube_rotations[x2][i][j] = layer[i][j];

         if(y1 == y2)
            cube_rotations[i][y2][j] = layer[i][j];

         if(z1 == z2)
            cube_rotations[i][j][z2] = layer[i][j];
      }


}

void keyboard_func(unsigned char key, int x, int y)
{
  switch(key) {
    case '+':
      gap += 3;
      break;

    case '-':
      gap -= 3;
      break;

    //ROTATE THE WHOLE CUBE
    case 'L': // see right
    case 'l':
      rot_y = (rot_y - step_size) % 360;
      break;

    case 'J': // see left
    case 'j':
      rot_y = (rot_y + step_size) % 360;
      break;

    case 'I': // see top
    case 'i':
      rot_x = (rot_x + step_size) % 360;
      break;

    case 'K': // see down
    case 'k':
      rot_x = (rot_x - step_size) % 360;
      break;

    // SELECT LAYER
    // X-axis layers
    case 'Q':
    case 'q':
      reset_layers();
      x1 = 0;
      x2 = 0;
      break;

    case 'W':
    case 'w':
      reset_layers();
      x1 = 1;
      x2 = 1;
      break;

    case 'E':
    case 'e':
      reset_layers();
      x1 = 2;
      x2 = 2;
      break;

    // Y-axis layers
    case 'A':
    case 'a':
      reset_layers();
      y1 = 0;
      y2 = 0;
      break;

    case 'S':
    case 's':
      reset_layers();
      y1 = 1;
      y2 = 1;
      break;

    case 'D':
    case 'd':
      reset_layers();
      y1 = 2;
      y2 = 2;
      break;

    // Z-axis layers
    case 'Z':
    case 'z':
      reset_layers();
      z1 = 0;
      z2 = 0;
      break;

    case 'X':
    case 'x':
      reset_layers();
      z1 = 1;
      z2 = 1;
      break;

    case 'C':
    case 'c':
      reset_layers();
      z1 = 2;
      z2 = 2;
      break;

    //MOVE SELECTED LAYER
    case 'U':
    case 'u':
      rotate_backward(-90);
      break;

    case 'O':
    case 'o':
      rotate_forward(90);
      break;

    default:
      break;
  }
  glutPostRedisplay();
}

void draw_cube(int x, int y, int z)
{

  vector<rotate_vector> cur_rot = cube_rotations[x][y][z];
  
  glPushMatrix();//translations and rotations are different for each cube

  // translating cube to correct location
  glTranslatef((x - 1) * (cube_size+gap), (y - 1) * (cube_size +gap), (z - 1) * (cube_size+gap));
  
  
  //rotating cube to correct position
  for(int i = cur_rot.size() - 1; i >= 0; --i)
    glRotatef(cur_rot[i].angle, cur_rot[i].x, cur_rot[i].y, cur_rot[i].z);
   
  //drawing a cube
  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);  // front
    glNormal3f(0.0, 0.0, 1.0);  // layer normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
  glEnd();

  glColor3f(1.0f, 0.35f, 0.0f);
  glBegin(GL_QUADS);  // back
    glNormal3f(0.0, 0.0, -1.0);  // layer normal
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);  // left
    glNormal3f(-1.0, 0.0, 0.0);  // layer normal
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();
  
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);  // right
    glNormal3f(1.0, 0.0, 0.0);  // layer normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);  // top
    glNormal3f(0.0, 1.0, 0.0);  // layer normal
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);  // bottom
    glNormal3f(0.0, -1.0, 0.0);  // layer normal
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();

  glPopMatrix();
} 

void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();// reset transformations

  set_camera();

  glRotatef(rot_x, 1.0, 0.0, 0.0); 
  glRotatef(rot_y, 0.0, 1.0, 0.0);

  for(int i = 0; i < 3; ++i) //x axis
    for(int j = 0; j < 3; ++j) //y axis
      for(int k = 0; k < 3; ++k) { //z axis
		  //if(k==2)
	      draw_cube(i, j, k);
      }
  glutSwapBuffers(); // flush opengl commands
}

void load_parameters(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();//reset Transformations

  //defining the angle of view
  gluPerspective(angle,aspect,0.4,500);

  //model coordinate system
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // specify observer and target positions
  set_camera();
}

void reshape_func(GLsizei w, GLsizei h)
{
  glViewport(0, 0, w, h);
  aspect = (GLfloat)w/(GLfloat)h;
  load_parameters();
} 

void init_func (void)
{ 
  cube_size = 30.0; 
  rot_x = 0.0; // view rotation x
  rot_y = 0.0; // view rotation y
  step_size = 5; // rotation step_size
  gap = 2;
  
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  
  glEnable(GL_DEPTH_TEST);
  angle=45;
  
  reset_layers();
  x1=0,x2=0;
}
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,350);
  glutCreateWindow("CED18I050 RUBIK'S CUBE");
  
  init_func();
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape_func);
  glutKeyboardFunc(keyboard_func);

  glutMainLoop();
}
