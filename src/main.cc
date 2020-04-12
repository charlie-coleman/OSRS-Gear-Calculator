#include "CalculatorWindow.h"

int main(int argc, char **argv)
{
  auto app = Gtk::Application::create(argc, argv, "com.charlie-coleman.osrsgearcal");

  CalculatorWindow window;

  return app->run(window);
}