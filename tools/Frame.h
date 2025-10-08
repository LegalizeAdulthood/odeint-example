#pragma once

#include <dynamical-system/dynamical-system.h>

#include <wx/wx.h>

#include <memory>

namespace chaotic_attractor
{

class Canvas;

struct DynamicalSystem
{
    void reset(dynamical_system::Attractor value);
    void iterate();

    dynamical_system::Attractor attractor{dynamical_system::Attractor::NONE};
    dynamical_system::Point3f state{0.1f, 0.0f, 0.0f};
    float begin{0.0f};
    float end{10.0f};
    float dt{0.1f};
    dynamical_system::Orbit orbit;
};

class Frame : public wxFrame
{
public:
    explicit Frame(const wxString &title);

private:
    void on_exit(wxCommandEvent &event);
    void on_idle(wxIdleEvent &event);
    void on_none(wxCommandEvent &event);
    void on_lorenz(wxCommandEvent &event);
    void on_rossler(wxCommandEvent &event);
    void on_start(wxCommandEvent &event);
    void on_stop(wxCommandEvent &event);
    void set_system( dynamical_system::Attractor attractor );
    void set_iterating(bool iterating);

    wxMenuItem *m_none;
    wxMenuItem *m_lorenz;
    wxMenuItem *m_rossler;
    wxMenuItem *m_run;
    wxMenuItem *m_stop;
    Canvas *m_canvas;
    bool m_iterating{};
    DynamicalSystem m_sys;
};

} // namespace chaotic_attractor
