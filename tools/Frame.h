#pragma once

#include <dynamical-system/dynamical-system.h>

#include <wx/wx.h>

#include <memory>

namespace chaotic_attractor
{

class Canvas;

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
    void set_system(dynamical_system::System system);
    void set_iterating(bool iterating);

    wxMenuItem *m_none;
    wxMenuItem *m_lorenz;
    wxMenuItem *m_rossler;
    wxMenuItem *m_run;
    wxMenuItem *m_stop;
    Canvas *m_canvas;
    dynamical_system::System m_system{dynamical_system::System::NONE};
    bool m_iterating{};
};

} // namespace chaotic_attractor
