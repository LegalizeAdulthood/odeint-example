#include <wx/wx.h>

#include <memory>

namespace chaotic_attractor
{

class Canvas;

enum class System
{
    NONE = 0,
    LORENZ = 1,
    ROSSLER = 2
};

class Frame : public wxFrame
{
public:
    explicit Frame(const wxString &title);

private:
    void on_exit(wxCommandEvent &event);
    void on_lorenz(wxCommandEvent &event);
    void on_rossler(wxCommandEvent &event);

    wxMenuItem *m_lorenz;
    wxMenuItem *m_rossler;
    Canvas *m_canvas;
    System m_system{System::NONE};
};

} // namespace chaotic_attractor
