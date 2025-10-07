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

    Canvas *m_canvas;
};

} // namespace chaotic_attractor
