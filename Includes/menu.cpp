#include "menu.hpp"

#include <iostream>

MenuNode::MenuNode(std::string label) : label(label) {

}

MenuNode::~MenuNode() {

}

void MenuNode::execute() {

}

std::string_view MenuNode::getLabel() const {
  return this->label;
}

std::list<MenuNode> *MenuNode::getChildNodes() {
  return &this->childNodes;
}

// TODO: Split up into Subclass SubmenuNode?


void MenuNode::addNode(MenuNode node) {
  this->childNodes.push_back(node);
}

Menu::Menu(const Config &config, Renderer &renderer) : rootNode("root"), renderer(renderer) {
  for (auto &e : config.json["menu"]) {
    MenuNode newNode(e["label"]);
    //newNode.label = e["label"];
    this->rootNode.addNode(newNode);
    //std::cout << e << std::endl;
    //std::cout << e["label"] << std::endl;
  }
}

void Menu::render(Font &font) {
  std::pair<float, float> coordinates(100, 100);
  std::string menutext;
  int i = 0;
  for (MenuNode &menuNode : *this->rootNode.getChildNodes()) {
    //menutext += std::string(menuNode.getLabel()) + "\n";
    menutext = std::string(menuNode.getLabel());
    std::pair<float, float> dimensions;
    dimensions = font.draw(menutext, coordinates);

    if (i == 1) {
      SDL_Rect rect;
      rect.w = std::get<0>(dimensions) + 20;
      rect.h = std::get<1>(dimensions);
      rect.x = std::get<0>(coordinates) - 10;
      rect.y = std::get<1>(coordinates);
      renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderDrawRect(renderer.getRenderer(), &rect);
    }

    coordinates = std::pair<float, float>(std::get<0>(coordinates), std::get<1>(coordinates) + std::get<1>(dimensions));

    i++;
  }
//  font.draw(menutext);
}
