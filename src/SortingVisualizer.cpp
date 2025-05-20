#include "SortingVisualizer.hpp"
#include <iostream>

namespace {
    const sf::Color bg(40,40,55);
    constexpr float WIN_SCALE = 0.8f;
}

namespace SortingVisualizer {
void StartApp(){
    sf::Font font;
    if(!font.loadFromFile("assets/font.ttf")){
        std::cerr<<"Cannot load font\n"; return;
    }
    auto dm = sf::VideoMode::getDesktopMode();
    sf::RenderWindow win(
        {unsigned(dm.width*WIN_SCALE), unsigned(dm.height*WIN_SCALE)},
        "Sorting Visualizer", sf::Style::Close|sf::Style::Resize
    );
    win.setFramerateLimit(60);

    AppState st;
    st.visH = win.getSize().y * 0.8f;
    st.model = ArrayModel(100);
    st.model.generateRandom();

    ArrayVisualizer av(win, st.visH);
    av.setArray(st.model.getData());

    std::vector<Button::Button<Screen>> btns;
    btns.emplace_back(
        win.getSize().x/2.f-100, win.getSize().y/2.f-20,
        200,40, font, "Bubble Sort",
        sf::Color(80,120,200), sf::Color(100,150,250),
        sf::Color::White, sf::Color(100,100,100),
        Screen::Bubble
    );
    Button::Button<Screen> back(20,20,80,30,font,"Back",
        sf::Color(200,80,80),sf::Color(220,100,100),
        sf::Color::White, sf::Color(150,150,150),
        Screen::Main
    );
    Button::Button<bool> start(
        win.getSize().x/2.f-50, win.getSize().y*0.7f,
        100,40,font,"Start",
        sf::Color(80,200,120),sf::Color(100,220,140),
        sf::Color::White, sf::Color(150,150,150),
        true
    );

    Screen screen = Screen::Main;
    while(win.isOpen()){
        float dt = st.clock.restart().asSeconds();
        sf::Event e;
        while(win.pollEvent(e)){
            if(e.type==sf::Event::Closed) win.close();
            if(e.type==sf::Event::Resized){
                win.setView({{0,0}, {float(e.size.width),float(e.size.height)}});
                av.updateWindowSize();
            }
        }
        win.clear(bg);

        switch(screen){
        case Screen::Main:
            for(auto& b: btns){
                b.update(sf::Mouse::getPosition(win));
                b.render(win);
                if(b.isClicked){
                    screen = b.getMessage();
                    st.model.generateRandom();
                    st.done = st.active = false;
                    av.setArray(st.model.getData());
                }
            }
            break;
        case Screen::Bubble:
            back.update(sf::Mouse::getPosition(win));
            back.render(win);
            start.update(sf::Mouse::getPosition(win));
            start.render(win);

            if(back.isClicked){
                screen = Screen::Main;
            }
            if(start.isClicked){
                st.active = true;
                st.done = false;
            }
            if(st.active && !st.done){
                st.model.step(dt);
                av.setArray(st.model.getData());
            }
            av.draw(st.model.isSwapping(),
                    st.model.getSwapIndices(),
                    st.model.getSwapProgress());
            break;
        }

        win.display();
    }
}
}
