#ifndef MENU_HPP
#define MENU_HPP

#include "config.hpp"
#include "font.h"

#include <list>
#include <string>

class MenuNode {
public:
  MenuNode(std::string label);
  virtual ~MenuNode();
  virtual void execute();
  MenuNode *getParent() const;
  std::string_view getLabel() const;
  std::list<MenuNode> *getChildNodes();
  void addNode(MenuNode node);
protected:
  MenuNode *parentNode;
  std::list<MenuNode> childNodes;
  std::string label;
};

class Menu {
public:
  Menu(const Config &config, Renderer &renderer);
  void render(Font &font);
protected:
  Renderer &renderer;
  MenuNode rootNode;
  MenuNode *currentMenu;
};

#endif
