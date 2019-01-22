#include "Model.h"
#include "Controller.h"
#include "View.h"
#include <gtkmm/application.h>

int main(int argc, char* argv[]){

    auto app = Gtk::Application::create(argc, argv, "GTKmm.Straights.Game");

    Model model(0);
    Controller controller(&model);
    View view(app, &model, &controller);

    model.subscribe(&view);

    return app->run(view);
}
