/*
* Prácticas de IG
* Copyright Domingo Martín Perandrés 2014-218
* dmartin@ugr.es
*
* GPL 3
*/

#include "glwidget.h"
#include "window.h"

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;

/**
* Constructor
*
*@param
*@returns
*/

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}

/**
* Evento tecla pulsada
*
*@param
*@returns
*/


void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){
  case Qt::Key_1:Object=OBJECT_TETRAHEDRON;break;
  case Qt::Key_2:break;
  case Qt::Key_3:break;
  case Qt::Key_4:break;
  case Qt::Key_5:break;
  case Qt::Key_6:break;
  case Qt::Key_7:break;
  case Qt::Key_8:break;

  case Qt::Key_P:Draw_point=!Draw_point;break;
  case Qt::Key_L:Draw_line=!Draw_line;break;
  case Qt::Key_F:Draw_fill=!Draw_fill;break;

  case Qt::Key_F1:Mode_rendering=MODE_RENDERING_SOLID;break;
  case Qt::Key_F2:break;
  case Qt::Key_F3:break;
  case Qt::Key_F4:break;
  case Qt::Key_F5:break;

  case Qt::Key_A:
    Animation=!Animation;
    set_animation();
    break;

  case Qt::Key_J:break;
  case Qt::Key_K:break;

  case Qt::Key_M:break;
  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP_KEY;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP_KEY;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP_KEY;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP_KEY;break;

  /*************************/
  case Qt::Key_PageUp:
    if (Projection_type==PERSPECTIVE_PROJECTION) Observer_distance*=DISTANCE_FACTOR;
    else{
      /*************************/

      /*************************/
    }
    break;
  case Qt::Key_PageDown:
    if (Projection_type==PERSPECTIVE_PROJECTION) Observer_distance/=DISTANCE_FACTOR;
    else{
      /*************************/

      /*************************/
    }
    break;
  /*************************/

  case Qt::Key_Q:break;
  case Qt::Key_W:break;
  case Qt::Key_S:break;
  case Qt::Key_D:break;
  case Qt::Key_Z:break;
  case Qt::Key_X:break;

  case Qt::Key_E:break;
  case Qt::Key_R:break;
  case Qt::Key_T:break;
  case Qt::Key_Y:break;
  case Qt::Key_U:break;
  case Qt::Key_I:break;

  case Qt::Key_C:Projection_type=PERSPECTIVE_PROJECTION;break;
  case Qt::Key_V:Projection_type=PARALLEL_PROJECTION;break;
  }

  update();
}

/**
*
*@param
*@returns
*/

void _gl_widget::mousePressEvent(QMouseEvent *Event)
{
  /*************************/

  /*************************/
}

/**
*
*@param
*@returns
*/

void _gl_widget::mouseReleaseEvent(QMouseEvent *Event)
{
  /*************************/

  /*************************/
}


/**
*
*@param
*@returns
*/

void _gl_widget::mouseMoveEvent(QMouseEvent *Event)
{
  /*************************/

  /*************************/
}

/**
*
*@param
*@returns
*/

void _gl_widget::wheelEvent(QWheelEvent *Event)
{
  int Step=Event->delta()/120;
  
  /*************************/

  /*************************/
}

/**
* Limpiar ventana
*
*@param
*@returns
*/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


/**
* Funcion para definir la transformación de proyeccion
*
*@param
*@returns
*/


void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float Aspect=(float)Window_height/(float)Window_width;

  if (Projection_type==PERSPECTIVE_PROJECTION){
    glFrustum(-Camera_width,Camera_width,-Camera_width*Aspect, Camera_width*Aspect,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
  }
  else{
  /*************************/

  /*************************/
  }
}


/**
* Funcion para definir la transformación de vista (posicionar la camara)
*
*@param
*@returns
*/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}


/**
* Funcion que dibuja los objetos
*
*@param
*@returns
*/

void _gl_widget::draw_objects()
{
  Axis.draw_line();

  if (Draw_point){
    glPointSize(5);
    glColor3fv((GLfloat *) &BLACK);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;
    default:break;
    }
  }

  if (Draw_line){
    glLineWidth(1);
    glColor3fv((GLfloat *) &MAGENTA);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;
    default:break;
    }
  }

  if (Draw_fill){
    switch (Mode_rendering){
    case MODE_RENDERING_SOLID:
      glColor3fv((GLfloat *) &BLUE);
      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;
      default:break;
      }
      break;
    default:break;
    }
  }
}


/**
* Evento de dibujado
*
*@param
*@returns
*/


void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_objects();
}


/**
* Evento de cambio de tamaño de la ventana
*@param
*@returns
*/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  Window_width=Width1;
  Window_height=Height1;

  glViewport(0,0,Width1,Height1);
}


/**
* Inicialización de OpenGL
*@param
*@returns
*/

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (GLEW_OK != err){
    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    exit (-1);
  }

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Window_width=width();
  Window_height=height();

  Change_camera=true;
  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;
  Show_selection=false;
  Selected_triangle=-1;

  Camera_width=X_MAX;

  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;

  Animation=false;


  Timer = new QTimer(this);
  Timer->setInterval(0);
  connect(Timer, SIGNAL(timeout()), this, SLOT(tick()));


  Object=OBJECT_TETRAHEDRON;
  Mode_rendering=MODE_RENDERING_SOLID;

  /*************************/


  /*************************/
}

/**
*
*@param
*@returns
*/

void _gl_widget::set_animation()
{
  if (Animation) Timer->start();
  else Timer->stop();
}

/**
*
*@param
*@returns
*/

void _gl_widget::tick()
{
  cout << "Tic" << endl;

  update();
}


/**
*
*@param
*@returns
*/

void _gl_widget::pick()
{
  makeCurrent();

  // Frame Buffer Object to do the off-screen rendering
  glGenFramebuffers(1,&FBO);
  glBindFramebuffer(GL_FRAMEBUFFER,FBO);

  // Texture for drawing
  glGenTextures(1,&Color_texture);
  glBindTexture(GL_TEXTURE_2D,Color_texture);
  // RGBA8
  glTexStorage2D(GL_TEXTURE_2D,1,GL_RGBA8, Window_width,Window_height);
  // this implies that there is not mip mapping
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

  // Texure for computing the depth
  glGenTextures(1,&Depth_texture);
  glBindTexture(GL_TEXTURE_2D,Depth_texture);
  // Float
  glTexStorage2D(GL_TEXTURE_2D,1,GL_DEPTH_COMPONENT24, Window_width,Window_height);

  // Attatchment of the textures to the FBO
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,Color_texture,0);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,Depth_texture,0);

  // OpenGL will draw to these buffers (only one in this case)
  static const GLenum Draw_buffers[]={GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1,Draw_buffers);

  /*************************/

  // dibujar para seleccion

  /*************************/

  // get the pixel
  int Color;
  glReadBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT,1);
  glReadPixels(Selection_position_x,Selection_position_y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,&Color);

  /*************************/

  // convertir de RGB a identificador

  // actualizar el identificador en el objeto

  /*************************/

  glDeleteTextures(1,&Color_texture);
  glDeleteTextures(1,&Depth_texture);
  glDeleteFramebuffers(1,&FBO);
  // the normal framebuffer takes the control of drawing
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,defaultFramebufferObject());
}
