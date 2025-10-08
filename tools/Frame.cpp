#include "Frame.h"

#include "Canvas.h"

#include <algorithm>
#include <iterator>

namespace chaotic_attractor
{

void DynamicalSystem::reset(dynamical_system::Attractor value)
{
    attractor = value;
    orbit.clear();
    state = {0.1f, 0.0f, 0.0f};
    begin = 0.0f;
    end = 10.0f;
    dt = 0.1f;
}

void DynamicalSystem::iterate()
{
    const dynamical_system::Orbit chunk{dynamical_system::iterate(attractor, state, begin, end, dt)};
    if (orbit.size() > 10'000)
    {
        orbit.erase(orbit.begin(), orbit.begin() + chunk.size());
    }
    std::copy(chunk.begin(), chunk.end(), std::back_inserter(orbit));
    state = orbit.back();
    begin = end;
    end += 10.0f;
}

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

    set_system(dynamical_system::Attractor::NONE);
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
        m_sys.iterate();
        m_canvas->set_orbit(m_sys.orbit);
        m_canvas->Refresh(false);
    }
    event.RequestMore();
}

void Frame::on_none(wxCommandEvent &event)
{
    set_system(dynamical_system::Attractor::NONE);
}

void Frame::on_lorenz(wxCommandEvent &event)
{
    set_system(dynamical_system::Attractor::LORENZ);
}

void Frame::on_rossler(wxCommandEvent &event)
{
    set_system(dynamical_system::Attractor::ROSSLER);
}

void Frame::on_start(wxCommandEvent &event)
{
    set_iterating(true);
}

void Frame::on_stop(wxCommandEvent &event)
{
    set_iterating(false);
}

void Frame::set_system(dynamical_system::Attractor attractor)
{
    m_sys.reset(attractor);
    switch (attractor)
    {
    case dynamical_system::Attractor::NONE:
        m_none->Check(true);
        m_lorenz->Check(false);
        m_rossler->Check(false);
        break;
    case dynamical_system::Attractor::LORENZ:
        m_none->Check(false);
        m_lorenz->Check(true);
        m_rossler->Check(false);
        break;
    case dynamical_system::Attractor::ROSSLER:
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
