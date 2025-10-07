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
    wxFrameBase::SetMenuBar(menu_bar);
    Bind(wxEVT_MENU, &Frame::on_exit, this, wxID_EXIT);
}

void Frame::on_exit(wxCommandEvent &event)
{
    Close(true);
}

} // namespace chaotic_attractor
