#include <dynamical-system/dynamical-system.h>

#include <wx/wx.h>

namespace chaotic_attractor
{

class Frame : public wxFrame
{
public:
    explicit Frame(const wxString &title);

private:
    void on_exit(wxCommandEvent &event);
};

class App : public wxApp
{
public:
    ~App() override = default;

    bool OnInit() override;
};

Frame::Frame(const wxString &title): wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
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

bool App::OnInit()
{
    Frame *frame = new Frame("Chaotic Attractor");
    frame->Show(true);
    return true;
}

} // namespace chaotic_attractor

wxIMPLEMENT_APP(chaotic_attractor::App);
