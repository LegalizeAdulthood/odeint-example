#include "Canvas.h"

#include <gl/glu.h>

#include <algorithm>

using namespace dynamical_system;

namespace chaotic_attractor
{

Canvas::Canvas(
    wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name) :
    wxGLCanvas(parent, id, nullptr, pos, size, style | wxFULL_REPAINT_ON_RESIZE, name)
{
    // Create the context immediately after construction
    m_context = std::make_shared<wxGLContext>(this);
    
    Bind(wxEVT_SIZE, &Canvas::on_size, this, wxID_ANY);
    Bind(wxEVT_PAINT, &Canvas::on_paint, this, wxID_ANY);
    Bind(wxEVT_ERASE_BACKGROUND, &Canvas::on_erase_background, this, wxID_ANY);
    Bind(wxEVT_MOTION, &Canvas::on_mouse_move, this, wxID_ANY);
}

void Canvas::set_orbit(const Orbit &orbit)
{
    m_orbit = orbit;
    if (!m_orbit.empty())
    {
        Point3f min{m_orbit[0]};
        Point3f max{m_orbit[0]};
        for (const auto &p : m_orbit)
        {
            for (int i = 0; i < 3; ++i)
            {
                min[i] = std::min(p[i], min[i]);
                max[i] = std::max(p[i], max[i]);
            }
        }
        m_min = min;
        m_max = max;
        
        // Force immediate refresh
        Refresh(false);
        Update();
    }
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
    // only doing line drawing, not triangles
    glDisable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(0.5f);
    glDepthMask(GL_FALSE);
}

void Canvas::reset_view()
{
    if (!IsShownOnScreen())
    {
        return;
    }

    // This is normally only necessary if there is more than one wxGLCanvas
    // or more than one wxGLContext in the application.
    SetCurrent(*m_context);

    const wxSize client_size = GetClientSize() * GetContentScaleFactor();

    // It's up to the application code to update the OpenGL viewport settings.
    // In order to avoid extensive context switching, consider doing this in
    // OnPaint() rather than here, though.
    glViewport(0, 0, client_size.x, client_size.y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double width;
    double height;
    if (client_size.x > client_size.y)
    {
        height = 1.0;
        width = height * client_size.x / client_size.y;
    }
    else
    {
        width = 1.0;
        height = width * client_size.y / client_size.x;
    }
    glFrustum(-width, width, -height, height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Canvas::render()
{
    if (m_orbit.empty())
    {
        return;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    const auto length = [&](int index)
    {
        return m_max[index] - m_min[index];
    };
    const auto center = [&](int index)
    {
        return m_min[index] + length(index) / 2.0f;
    };
    
    gluLookAt(0.0, 0.0, 3.0, // Eye position
        0.0, 0.0, 0.0,       // Look-at point
        0.0, 1.0, 0.0);      // Up direction
    const float max_length = std::max({length(0), length(1), length(2)});
    if (max_length > 0.0f)  // Avoid division by zero
    {
        const float factor{4.0f / max_length};
        glScalef(factor, factor, factor);
    }
    glTranslatef(-center(0), -center(1), -center(2));

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (const auto &p : m_orbit)
    {
        glVertex3f(p[0], p[1], p[2]);
    }
    glEnd();
}

} // namespace chaotic_attractor
