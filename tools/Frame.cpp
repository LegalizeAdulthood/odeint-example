#include "Frame.h"

#include "Canvas.h"

namespace chaotic_attractor
{

Frame::Frame(const wxString &title) :
    wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),
    m_canvas(new Canvas(this, wxID_ANY, wxDefaultPosition, GetClientSize(), wxSUNKEN_BORDER))
{
    wxMenu *file = new wxMenu;
    file->Append(wxID_EXIT, "&Quit\tAlt-F4", "Quit");
    wxMenuBar *menu_bar = new wxMenuBar;
    menu_bar->Append(file, "&File");
    wxMenu *attractor = new wxMenu;
    m_none = attractor->AppendCheckItem(wxID_ANY, "&None", "No attractor");
    Bind(wxEVT_MENU, &Frame::on_none, this, m_none->GetId());
    m_lorenz = attractor->AppendCheckItem(wxID_ANY, "&Lorenz", "Lorenz attractor");
    Bind(wxEVT_MENU, &Frame::on_lorenz, this, m_lorenz->GetId());
    m_rossler = attractor->AppendCheckItem(wxID_ANY, "&Rossler", "Rossler attractor");
    Bind(wxEVT_MENU, &Frame::on_rossler, this, m_rossler->GetId());
    menu_bar->Append(attractor, "&Attractor");
    wxMenu *iterate = new wxMenu;
    m_run = iterate->Append(wxID_ANY, "&Run", "Start iterating");
    Bind(wxEVT_MENU, &Frame::on_start, this, m_run->GetId());
    m_stop = iterate->Append(wxID_ANY, "&Stop", "Stop iterating");
    Bind(wxEVT_MENU, &Frame::on_stop, this, m_stop->GetId());
    menu_bar->Append(iterate, "&Iterate");
    wxFrameBase::SetMenuBar(menu_bar);
    Bind(wxEVT_MENU, &Frame::on_exit, this, wxID_EXIT);
    Bind(wxEVT_IDLE, &Frame::on_idle, this);

    set_system(dynamical_system::System::NONE);
    set_iterating(false);
}

void Frame::on_exit(wxCommandEvent &event)
{
    Close(true);
}

void Frame::on_idle(wxIdleEvent &event)
{
    if (m_iterating)
    {
        dynamical_system::Orbit orbit{dynamical_system::iterate(m_system, {0.1, 0.0, 0.0}, 0.01, 10)};
        m_canvas->Refresh(false);
    }
    event.RequestMore();
}

void Frame::on_none(wxCommandEvent &event)
{
    set_system(dynamical_system::System::NONE);
}

void Frame::on_lorenz(wxCommandEvent &event)
{
    set_system(dynamical_system::System::LORENZ);
}

void Frame::on_rossler(wxCommandEvent &event)
{
    set_system(dynamical_system::System::ROSSLER);
}

void Frame::on_start(wxCommandEvent &event)
{
    set_iterating(true);
}

void Frame::on_stop(wxCommandEvent &event)
{
    set_iterating(false);
}

void Frame::set_system( dynamical_system::System system )
{
    m_system = system;
    switch (m_system)
    {
    case dynamical_system::System::NONE:
        m_none->Check(true);
        m_lorenz->Check(false);
        m_rossler->Check(false);
        break;
    case dynamical_system::System::LORENZ:
        m_none->Check(false);
        m_lorenz->Check(true);
        m_rossler->Check(false);
        break;
    case dynamical_system::System::ROSSLER:
        m_none->Check(false);
        m_lorenz->Check(false);
        m_rossler->Check(true);
        break;
    }
}

void Frame::set_iterating(bool iterating)
{
    m_iterating = iterating;
    m_run->Enable(!m_iterating);
    m_stop->Enable(m_iterating);
}

} // namespace chaotic_attractor
