#pragma once

#include <dynamical-system/dynamical-system.h>

#include <wx/glcanvas.h>
#include <wx/wx.h>

#include <memory>

namespace chaotic_attractor
{

class Canvas : public wxGLCanvas
{
public:
    explicit Canvas(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize, long style = 0, const wxString &name = "Canvas");
    Canvas(const Canvas &rhs) = delete;
    Canvas(Canvas &&rhs) = delete;
    Canvas &operator=(const Canvas &rhs) = delete;
    Canvas &operator=(Canvas &&rhs) = delete;
    ~Canvas() override = default;

    void set_orbit(const dynamical_system::Orbit &orbit);

private:
    void on_size(wxEvent &event);
    void on_paint(wxEvent &event);
    void on_erase_background(wxEvent &event);
    void on_mouse_move(wxEvent &event);
    void init_gl();
    void reset_view();
    void render();

    bool m_initialized{};
    std::shared_ptr<wxGLContext> m_context{std::make_shared<wxGLContext>(this)};
    dynamical_system::Orbit m_orbit;
    dynamical_system::Point3f m_min{};
    dynamical_system::Point3f m_max{};
};

} // namespace chaotic_attractor
