#include "Canvas.h"

namespace chaotic_attractor
{

Canvas::Canvas(
    wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name) :
    wxGLCanvas(parent, id, nullptr, pos, size, style | wxFULL_REPAINT_ON_RESIZE, name)
{
    Bind(wxEVT_SIZE, &Canvas::on_size, this, wxID_ANY);
    Bind(wxEVT_PAINT, &Canvas::on_paint, this, wxID_ANY);
    Bind(wxEVT_ERASE_BACKGROUND, &Canvas::on_erase_background, this, wxID_ANY);
    Bind(wxEVT_MOTION, &Canvas::on_mouse_move, this, wxID_ANY);
}

void Canvas::on_size(wxEvent &event)
{
    reset_view();
}

void Canvas::on_paint(wxEvent &event)
{
    wxPaintDC dc(this);

    SetCurrent(*m_context);
    if (!m_initialized)
    {
        init_gl();
        reset_view();
        m_initialized = true;
    }

    glClearColor(0.0f, 0.8f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: set attractor modelview matrix
    // Transformations
    glLoadIdentity();
    //glTranslatef(0.0f, 0.0f, -20.0f);
    //GLfloat m[4][4];
    //build_rotmatrix(m, m_gldata.quat);
    //glMultMatrixf(&m[0][0]);

    render();

    glFlush();
    SwapBuffers();
}

void Canvas::on_erase_background(wxEvent &event)
{
    // intentionally do nothing to avoid flashing
}

void Canvas::on_mouse_move(wxEvent &event)
{
    // TODO: handle arcball
}

void Canvas::init_gl()
{
    static const GLfloat light0_pos[4] = {-50.0f, 50.0f, 0.0f, 0.0f};

    // white light
    static const GLfloat light0_color[4] = {0.6f, 0.6f, 0.6f, 1.0f};

    static const GLfloat light1_pos[4] = {50.0f, 50.0f, 0.0f, 0.0f};

    // cold blue light
    static const GLfloat light1_color[4] = {0.4f, 0.4f, 1.0f, 1.0f};

    /* remove back faces */
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    /* speedups */
    glEnable(GL_DITHER);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

    /* light */
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_color);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_color);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void Canvas::reset_view()
{
    if (!IsShownOnScreen())
        return;

    // This is normally only necessary if there is more than one wxGLCanvas
    // or more than one wxGLContext in the application.
    SetCurrent(*m_context);

    const wxSize ClientSize = GetClientSize() * GetContentScaleFactor();

    // It's up to the application code to update the OpenGL viewport settings.
    // In order to avoid extensive context switching, consider doing this in
    // OnPaint() rather than here, though.
    glViewport(0, 0, ClientSize.x, ClientSize.y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double fH = tan(M_PI / 8);
    double fW = fH * ClientSize.x / ClientSize.y;
    glFrustum(-fW, fW, -fH, fH, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Canvas::render()
{
    // TODO: render attractor
}

} // namespace chaotic_attractor
