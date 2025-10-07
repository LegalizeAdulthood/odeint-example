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
    wxFrameBase::SetMenuBar(menu_bar);
    Bind(wxEVT_MENU, &Frame::on_exit, this, wxID_EXIT);
    set_system(System::NONE);
}

void Frame::on_exit(wxCommandEvent &event)
{
    Close(true);
}

void Frame::set_system(System system)
{
    m_system = system;
    switch (m_system)
    {
    case System::NONE:
        m_none->Check(true);
        m_lorenz->Check(false);
        m_rossler->Check(false);
        break;
    case System::LORENZ:
        m_none->Check(false);
        m_lorenz->Check(true);
        m_rossler->Check(false);
        break;
    case System::ROSSLER:
        m_none->Check(false);
        m_lorenz->Check(false);
        m_rossler->Check(true);
        break;
    }
}

void Frame::on_none(wxCommandEvent &event)
{
    set_system(System::NONE);
}

void Frame::on_lorenz(wxCommandEvent &event)
{
    set_system(System::LORENZ);
}

void Frame::on_rossler(wxCommandEvent &event)
{
    set_system(System::ROSSLER);
}

} // namespace chaotic_attractor
