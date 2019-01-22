#include "View.h"
#include "Card.h"
#include <string>
View::View(const Glib::RefPtr<Gtk::Application>& app,
        Model* model, Controller* con) : app_(app),
model_(model),
controller_(con),
frame1_(true, 60),    
toolBar_(Gtk::Orientation::ORIENTATION_VERTICAL)
{
    set_title( "Straights UI" );
    set_default_size( 900, 600 );
   
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 13; ++j){
            std::string k;
            if(j <= 9){
                k = "_" + std::to_string(j);
            }

            else if(j == 10){
                k = "_j";
            }

            else if(j == 11){
                k = "_q";
            }

            else{
                k = "_k";
            }
            cards.push_back(Gdk::Pixbuf::create_from_file("img/" + std::to_string(i) + k + ".png"));            

        }
    }

    cards.push_back(Gdk::Pixbuf::create_from_file("img/nothing.png"));
    
    for(size_t i = 0; i < cards.size(); ++i){
        images_.push_back(Gtk::Image());
        images_.at(i).set(cards.at(i));
    }
    
    for(size_t i = 0; i < cards.size(); ++i){
        deckimages_.push_back(Gtk::Image());
        deckimages_.at(i).set(cards[cards.size() - 1]);
    }

    for(size_t i = 0; i < 13; ++i){
        handbuttons_.push_back(Gtk::Button());
        handbuttons_.at(i).set_image(images_[52]);
        handbuttons_.at(i).set_always_show_image(true);
        handbuttons_.at(i).signal_clicked().connect(sigc::bind(
                                                          sigc::mem_fun(*this, &View::card_selected),
                                                          i));
    }

    deck_.set_row_spacing(10);
    deck_.set_column_spacing(24);
    hand_.set_column_spacing(5);
    for(int i = 0; i < 13; ++i){
        deck_.attach(deckimages_[i], i, 1, 1, 1);
        hand_.attach(handbuttons_[i], i, 1, 1, 1);
    }

    for(int i = 13; i < 26; ++i){
        deck_.attach(deckimages_[i], i%13, 2, 1, 1);
    }

    for(int i = 26; i < 39; ++i){
        deck_.attach(deckimages_[i], i%26, 3, 1, 1);
    }

    for(int i = 39; i < 52; ++i){
        deck_.attach(deckimages_[i], i%39, 4, 1, 1);
    }

    actionGroup_ = Gio::SimpleActionGroup::create();
    builder_ = Gtk::Builder::create_from_file("toolbar.glade");
    insert_action_group("straights", actionGroup_);

    actionGroup_->add_action("newgame", sigc::mem_fun(*this, &View::newGame) );
    actionGroup_->add_action("endgame", sigc::mem_fun(*this, &View::endGame) );

    Gtk::Toolbar *toolbar = nullptr;
    builder_->get_widget("toolbar", toolbar);
    if(!toolbar){
        g_warning("toolbar not found");
    }
    else{
        toolBar_.pack_start(*toolbar, Gtk::PACK_SHRINK);
    }

    for(int i = 1; i < 5; ++i){
        players_.push_back(Gtk::Frame());
        players_.at(i-1).set_label("Player " + std::to_string(i));
        if(i == 1){
            b1_.set_label("Rage!");
            b1_.set_sensitive(false);
            l1_.set_text("0 points");
            l5_.set_text("0 discards");
            p1_.add(b1_);
            p1_.add(l1_);
            p1_.add(l5_);
            players_.at(0).add(p1_);
            b1_.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &View::ragequit), 0));
        }
        else if(i == 2){
            b2_.set_label("Rage!");
            b2_.set_sensitive(false);
            l2_.set_text("0 points");
            l6_.set_text("0 discards");
            p2_.add(b2_);
            p2_.add(l2_);
            p2_.add(l6_);
            players_.at(1).add(p2_);
            b2_.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &View::ragequit), 1));
        }

        else if(i == 3){
            b3_.set_label("Rage!");
            b3_.set_sensitive(false);
            l3_.set_text("0 points");
            l7_.set_text("0 discards");
            p3_.add(b3_);
            p3_.add(l3_);
            p3_.add(l7_);
            players_.at(2).add(p3_);
            b3_.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &View::ragequit), 2));
        }

        else{
            b4_.set_label("Rage!");
            b4_.set_sensitive(false);
            l4_.set_text("0 points");
            l8_.set_text("0 discards");
            p4_.add(b4_);
            p4_.add(l4_);
            p4_.add(l8_);
            players_.at(3).add(p4_);
            b4_.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &View::ragequit), 3));
        }

        playerGrid_.attach(players_.at(i-1), i, 1, 1, 1); 
    }

    playerGrid_.set_column_homogeneous(true);
    hand_.set_column_homogeneous(true);
    frame1_.add(toolBar_);
    points_.set_text("Seed for Current Game: ");
    typeTurn_.set_text("Turn: ");
    pointsBox_.add(points_);
    pointsBox_.add(typeTurn_);
    pointsBox_.set_spacing(100);
    frame1_.add(pointsBox_);

    frame1_.set_border_width(5);
    topLevel_.attach(frame1_, 1, 1, 1, 1);

    frame2_.add(deck_);
    frame2_.set_label("Cards on table");
    frame2_.set_border_width(5);
    topLevel_.set_row_spacing(2);
    topLevel_.attach(frame2_, 1, 2, 1, 1);

    frame3_.add(playerGrid_);
    topLevel_.attach(frame3_, 1, 3, 1, 1);

    frame4_.set_label("Your Hand:");
    frame4_.set_border_width(5);
    frame4_.add(hand_);
    topLevel_.attach(frame4_, 1, 4, 1, 1);

    add(topLevel_);
    show_all_children();
}

View::~View(){}

void View::update(){
    if(model_->getTurn() == Model::PLAY){
        Card *c = model_->currentPlayer()->getLastPlayed();
        int suit = (int)c->getSuit() * 13;
        int rank = (int)c->getRank();
        deckimages_[suit + rank].set(cards[suit + rank]);
        
        }

    else if(model_->getTurn() == Model::DISCARD){
        int num = model_->currentPlayer()->discardedCardsSize();
        switch(model_->getCurrentPlayerNumber()){
                case 0: l5_.set_text(std::to_string(num) + " discards");
                        break;
                case 1: l6_.set_text(std::to_string(num) + " discards");
                        break;
                case 2: l7_.set_text(std::to_string(num) + " discards");
                        break;
                case 3: l8_.set_text(std::to_string(num) + " discards");
                        break;
        }
    }

    if(model_->getState() == Model::ROUND_ENDED){
        Gtk::MessageDialog dialog(*this, "Current Round Ended", false, Gtk::MESSAGE_OTHER, Gtk::BUTTONS_OK);
        dialog.set_secondary_text("Points at the end of the round are following");

        Gtk::Label p1("Player 1: " + std::to_string(model_->getPlayer(0)->totalScore()));
        Gtk::Label p2("Player 2: " + std::to_string(model_->getPlayer(1)->totalScore()));
        Gtk::Label p3("Player 3: " + std::to_string(model_->getPlayer(2)->totalScore()));
        Gtk::Label p4("Player 4: " + std::to_string(model_->getPlayer(3)->totalScore()));


        Gtk::Box *b = dialog.get_message_area();
        b->pack_start(p1);
        b->pack_start(p2);
        b->pack_start(p3);
        b->pack_start(p4);

        dialog.show_all_children();
        dialog.run();

        render();

        l1_.set_text(std::to_string(model_->getPlayer(0)->totalScore()) + " Points");
        l2_.set_text(std::to_string(model_->getPlayer(1)->totalScore()) + " Points");
        l3_.set_text(std::to_string(model_->getPlayer(2)->totalScore()) + " Points");
        l4_.set_text(std::to_string(model_->getPlayer(3)->totalScore()) + " Points");
        l5_.set_text("0 discards");
        l6_.set_text("0 discards");
        l7_.set_text("0 discards");
        l8_.set_text("0 discards");
        typeTurn_.set_text("Turn: ");


        for(size_t i = 0; i < 52; ++i){
            deckimages_.at(i).set(cards[52]);
        }

        if(model_->checkIfGameEnded()){
            l1_.set_text(std::to_string(model_->getPlayer(0)->totalScore()) + " Points");
            l2_.set_text(std::to_string(model_->getPlayer(1)->totalScore()) + " Points");
            l3_.set_text(std::to_string(model_->getPlayer(2)->totalScore()) + " Points");
            l4_.set_text(std::to_string(model_->getPlayer(3)->totalScore()) + " Points");
            l5_.set_text(std::to_string(model_->getPlayer(0)->discardedCardsSize()) + " discards");
            l6_.set_text(std::to_string(model_->getPlayer(1)->discardedCardsSize()) + " discards");
            l7_.set_text(std::to_string(model_->getPlayer(2)->discardedCardsSize()) + " discards");
            l8_.set_text(std::to_string(model_->getPlayer(3)->discardedCardsSize()) + " discards");
            points_.set_text("Seed for Current Game: ");
            typeTurn_.set_text("Turn: ");

            b1_.set_sensitive(false);
            b2_.set_sensitive(false);
            b3_.set_sensitive(false);
            b4_.set_sensitive(false);

        Gtk::MessageDialog dialog(*this, "Game Ended", false, Gtk::MESSAGE_OTHER, Gtk::BUTTONS_OK);
        dialog.set_secondary_text("Winners are following");

        std::vector<int> winners = model_->winners();
        std::string listwinners = "";
        for(size_t i = 0; i < winners.size(); ++i){
            listwinners = listwinners + " Player " + std::to_string(winners[i]) + "\n";
        }

        Gtk::Label p1("Winners are: " + listwinners);
        Gtk::Box *b = dialog.get_message_area();
        b->pack_start(p1);
        dialog.show_all_children();
        dialog.run();
        l1_.set_text("0 Points");
        l2_.set_text("0 Points");
        l3_.set_text("0 Points");
        l4_.set_text("0 Points");
        l5_.set_text("0 discards");
        l6_.set_text("0 discards");
        l7_.set_text("0 discards");
        l8_.set_text("0 discards");
        points_.set_text("Seed for Current Game: ");
        typeTurn_.set_text("Turn: ");

        //controller_->endGame();
        for(size_t i = 0; i < 13; ++i){
            handbuttons_.at(i).set_image(images_[52]);
        }
            return;
        } else {
            controller_->startNewRound();
        }
    }

}

void View::newGame(){
    Gtk::MessageDialog dialog(*this, "Welcome to Straights!", false, Gtk::MESSAGE_OTHER, Gtk::BUTTONS_OK);
    dialog.set_secondary_text("Choose Player types!");

    Gtk::Grid data;
    Gtk::Label p1("Player 1");
    Gtk::Label p2("Player 2");
    Gtk::Label p3("Player 3");
    Gtk::Label p4("Player 4");
    Gtk::Label seed("Seed");
    Gtk::Entry p1_data;
    Gtk::Entry p2_data;
    Gtk::Entry p3_data;
    Gtk::Entry p4_data;
    Gtk::Entry seed_data;

    data.attach(p1, 1, 1, 1, 1);
    data.attach(p2, 1, 2, 1, 1);
    data.attach(p3, 1, 3, 1, 1);
    data.attach(p4, 1, 4, 1, 1);
    data.attach(seed, 1, 5, 1, 1);
    data.attach(p1_data, 2, 1, 1, 1);
    data.attach(p2_data, 2, 2, 1, 1);
    data.attach(p3_data, 2, 3, 1, 1);
    data.attach(p4_data, 2, 4, 1, 1);
    data.attach(seed_data, 2, 5, 1, 1);

    data.set_column_homogeneous(true);
    data.set_row_spacing(5);
    Gtk::Box *b = dialog.get_message_area();
    b->pack_start(data);
    dialog.show_all_children();
    dialog.run();

    std::vector<std::string> input;
    input.push_back(p1_data.get_text());
    input.push_back(p2_data.get_text());
    input.push_back(p3_data.get_text());
    input.push_back(p4_data.get_text());
    input.push_back(seed_data.get_text());
    points_.set_text("Seed for Current Game: " + seed_data.get_text());
    controller_->endGame();
    controller_->setupGame(input);
    render();
}

void View::endGame(){
    //call controller cleanup
    controller_->endGame();
    for(size_t i = 0; i < 52; ++i){
       deckimages_.at(i).set(cards[52]);
    }

    for(size_t i = 0; i < handbuttons_.size(); ++i){
        handbuttons_.at(i).set_image(images_[52]);
    }

    l1_.set_text("0 Points");
    l2_.set_text("0 Points");
    l3_.set_text("0 Points");
    l4_.set_text("0 Points");
    l5_.set_text("0 discards");
    l6_.set_text("0 discards");
    l7_.set_text("0 discards");
    l8_.set_text("0 discards");
}

void View::render(){
    if(model_->getState() == Model::ROUND_IN_PROGRESS){
        if(model_->currentPlayer()->isHuman() == false){
            for(size_t i = 0; i < 13; ++i){
                  handbuttons_.at(i).set_image(images_[52]);
                }
            return;
        }
    }

    for(size_t i = 0; i < handbuttons_.size(); ++i){
        handbuttons_.at(i).set_image(images_[52]);
    }
        if(model_->getState() == Model::ROUND_IN_PROGRESS){
            std::vector<Card *> hand = model_->currentPlayer()->hand();
            std::vector<Card *> legalPlays = model_->getLegalPlays();
            if(legalPlays.size() == 0){
                typeTurn_.set_text("Turn: DISCARD");
            } else {
                typeTurn_.set_text("Turn: PLAY");
            }
            for(size_t i = 0; i < hand.size(); ++i){
              handbuttons_.at(i).set_image(images_[13*(int)hand[i]->getSuit() + (int)hand[i]->getRank()]);
              Card c(hand[i]->getSuit(), hand[i]->getRank());
            
              bool flag = false;
              if(legalPlays.size() == 0) flag = true;
              for(size_t i = 0; i < legalPlays.size(); ++i){
                if( c == *legalPlays[i] ){
                    flag = true;
                    break;
                }
              }
              handbuttons_.at(i).set_sensitive(flag);
            }

            for(size_t i = hand.size(); i < 13; ++i){
              handbuttons_.at(i).set_sensitive(false);
            }

            switch(model_->getCurrentPlayerNumber()){
                case 0: b1_.set_sensitive(true);
                        break;
                case 1: b2_.set_sensitive(true);
                        break;
                case 2: b3_.set_sensitive(true);
                        break;
                case 3: b4_.set_sensitive(true);
                        break;
            }
        }
        else if(model_->isRoundFinished() == true){

        for(size_t i = 0; i < 52; ++i){
            deckimages_.at(i).set(cards[52]);
        }
    }
}
void View::card_selected(int i){
     switch(model_->getCurrentPlayerNumber()){
        case 0: b1_.set_sensitive(false);
                break;
        case 1: b2_.set_sensitive(false);
                break;
        case 2: b3_.set_sensitive(false);
                break;
        case 3: b4_.set_sensitive(false);
                break;

    }
    std::vector<Card *> hand = model_->currentPlayer()->hand();
    controller_->playTurn(hand[i]);
    handbuttons_.at(i).set_sensitive(false);
    render();
}

void View::ragequit(int i){
    switch(model_->getCurrentPlayerNumber()){
        case 0: b1_.set_sensitive(false);
                break;
        case 1: b2_.set_sensitive(false);
                break;
        case 2: b3_.set_sensitive(false);
                break;
        case 3: b4_.set_sensitive(false);
                break;

    }
   controller_->rageQuit();
   render();
}
