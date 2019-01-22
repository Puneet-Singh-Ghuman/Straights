#ifndef VIEW_H
#define VIEW_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <gtkmm.h>
#include "Observer.h"
#include "Model.h"
#include "Controller.h"
#include <vector>

class View : public Gtk::Window, public Observer{
    private:
        std::vector<Glib::RefPtr< Gdk::Pixbuf > > cards;
        std::vector<Gtk::Image> images_;
        Gtk::Grid topLevel_;

        const Glib::RefPtr<Gtk::Application>& app_;
        Model* model_;
        Controller* controller_;
        
        Glib::RefPtr<Gtk::Builder> builder_;
        Glib::RefPtr<Gio::SimpleActionGroup> actionGroup_;
        Gtk::HBox frame1_;
        Gtk::Box toolBar_;
        Gtk::Box pointsBox_;
        Gtk::Label points_;
        Gtk::Label typeTurn_;
        void newGame();
        void endGame();

        Gtk::Frame frame2_;
        Gtk::Grid deck_;
        std::vector<Gtk::Image> deckimages_;


        Gtk::Frame frame3_;
        Gtk::Grid playerGrid_;
        Gtk::Button b1_;
        Gtk::Button b2_;
        Gtk::Button b3_;
        Gtk::Button b4_;
        Gtk::Label l1_;
        Gtk::Label l2_;
        Gtk::Label l3_;
        Gtk::Label l4_;
        Gtk::Label l5_;
        Gtk::Label l6_;
        Gtk::Label l7_;
        Gtk::Label l8_;
        Gtk::VBox p1_;
        Gtk::VBox p2_;
        Gtk::VBox p3_;
        Gtk::VBox p4_;
        std::vector<Gtk::Frame> players_;


        Gtk::Frame frame4_;
        Gtk::Grid hand_;
        std::vector<Gtk::Button> handbuttons_;

        void render();
        void card_selected(int);
        void ragequit(int);
    public:
        View(const Glib::RefPtr<Gtk::Application>&, Model*, Controller*);

        ~View();

        void update() override;
};

#endif
