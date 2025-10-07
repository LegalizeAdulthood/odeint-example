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
    m_lorenz = attractor->AppendCheckItem(wxID_ANY, "&Lorenz", "Lorenz attractor");
    Bind(wxEVT_MENU, &Frame::on_lorenz, this, m_lorenz->GetId());
    m_rossler = attractor->AppendCheckItem(wxID_ANY, "&Rossler", "Rossler attractor");
    Bind(wxEVT_MENU, &Frame::on_rossler, this, m_rossler->GetId());
    menu_bar->Append(attractor, "&Attractor");
    wxFrameBase::SetMenuBar(menu_bar);
    Bind(wxEVT_MENU, &Frame::on_exit, this, wxID_EXIT);
}

void Frame::on_exit(wxCommandEvent &event)
{
    Close(true);
}

void Frame::on_lorenz(wxCommandEvent &event)
{
    m_rossler->Check(false);
    m_lorenz->Check(true);
    m_system = System::LORENZ;
}

void Frame::on_rossler(wxCommandEvent &event)
{
    m_lorenz->Check(false);
    m_rossler->Check(true);
    m_system = System::ROSSLER;
}

} // namespace chaotic_attractor
