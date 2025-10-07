#include <dynamical-system/dynamical-system.h>

#include <wx/wx.h>

#include <memory>

#include "Canvas.h"
#include "Frame.h"

namespace chaotic_attractor
{

class App : public wxApp
{
public:
    ~App() override = default;

    bool OnInit() override;
};

bool App::OnInit()
{
    Frame *frame = new Frame("Chaotic Attractor");
    frame->Show(true);
    return true;
}

} // namespace chaotic_attractor

wxIMPLEMENT_APP(chaotic_attractor::App);
