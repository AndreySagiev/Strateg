#ifndef FUNC
#define FUNC

#include <SFML/Config.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>


/*!
 * \brief  A class representing a circle on the game board.
 */
class Circle {
public:
  /*!
   * \brief Default constructor for Circle.
   */
  Circle()
      : circle(40.f), fillColor(sf::Color::Red), outlineColor(sf::Color::Green),
        outlineThickness(2.f), occupied(false), tall(false) {
    circle.setFillColor(fillColor);
    circle.setOutlineThickness(outlineThickness);
    circle.setOutlineColor(outlineColor);
  }

  /*!
   * \brief Constructor for Circle with specified parameters.
   * \param radius The radius of the circle.
   * \param fillColor The fill color of the circle.
   * \param outlineColor The outline color of the circle.
   * \param outlineThickness The outline thickness of the circle.
   * \param pointsCount The number of points for the circle shape.
   */
  Circle(float radius, const sf::Color &fillColor,
         const sf::Color &outlineColor, float outlineThickness,
         int pointsCount = 6)
      : circle(radius, pointsCount), fillColor(fillColor),
        outlineColor(outlineColor), outlineThickness(outlineThickness),
        occupied(false), tall(false) {
    circle.setFillColor(fillColor);
    circle.setOutlineThickness(outlineThickness);
    circle.setOutlineColor(outlineColor);
  }

  /*!
   * \brief Draws the circle to the window.
   * \param window The window to draw the circle on.
   */
  void draw(sf::RenderWindow &window) {
    if (tall) {
      circle.setFillColor(sf::Color(255, 165, 0));
    } else {
      circle.setFillColor(fillColor);
    }

    window.draw(circle);
  }

  /*!
   * \brief Sets the position of the circle.
   * \param x The x-coordinate of the circle's position.
   * \param y The y-coordinate of the circle's position.
   */
  void setPosition(float x, float y) { circle.setPosition(x, y); }

  /*!
   * \brief Checks if the mouse position is clicked within the circle.
   * \param mousePosition The mouse position in screen coordinates.
   * \param r The radius of the circle.
   * \return True if the mouse position is clicked within the circle, false
   * otherwise.
   */
  bool isClicked(const sf::Vector2i &mousePosition, float r) {
    sf::Vector2f center = circle.getPosition() +
                          sf::Vector2f(circle.getRadius(), circle.getRadius());

    float distance = sqrt(pow(mousePosition.x - center.x, 2) +
                          pow(mousePosition.y - center.y, 2));

    return distance <= r;
  }

  /*!
   * \brief Gets the coordinates of the circle's center.
   * \return The coordinates of the circle's center.
   */
  sf::Vector2f getCenter() const {
    return circle.getPosition() +
           sf::Vector2f(circle.getRadius(), circle.getRadius());
  }

  /*!
   * \brief Checks if the circle is occupied.
   * \return True if the circle is occupied, false otherwise.
   */
  bool isOccupied() const { return occupied; }

  /*!
   * \brief Sets the occupied status of the circle.
   * \param value The new occupied status of the circle.
   */
  void setOccupied(bool value) { occupied = value; }

  /*!
   * \brief Checks if the circle is tall.
   * \return True if the circle is tall, false otherwise.
   */
  bool isTall() const { return tall; }

  /*!
   * \brief Sets the tall status of the circle.
   * \param value The new tall status of the circle.
   */
  void setTall(bool value) { tall = value; }

private:
  sf::CircleShape circle;
  sf::Color fillColor;
  sf::Color outlineColor;
  float outlineThickness;
  bool occupied; //  ������ �� ������
  bool tall; //  �������� �� ������ "�������"
};

/*!
 * \brief A class representing a non-player character (NPC) in the game.
 */
class NPC {
public:
  /*!
   * \brief Constructor for NPC with specified parameters.
   * \param size The size of the NPC.
   * \param fillColor The fill color of the NPC.
   * \param HP The hit points (health) of the NPC.
   * \param attack_diapason The attack range of the NPC.
   * \param attack The attack power of the NPC.
   * \param pointsCount The number of points for the NPC shape.
   */
  NPC(float size, const sf::Color &fillColor, int HP, int attack_diapason,
      int attack, int pointsCount)
      : npc(size, pointsCount), fillColor(fillColor),
        outlineColor(sf::Color::Black), outlineThickness(2.f), HP(HP),
        attack_diapason(attack_diapason), attack(attack) {
    npc.setFillColor(fillColor);
    npc.setOutlineThickness(outlineThickness);
    npc.setOutlineColor(outlineColor);
  }

  /*!
   * \brief Draws the NPC to the window.
   * \param window The window to draw the NPC on.
   */
  void draw(sf::RenderWindow &window) const { window.draw(npc); }

  /*!
   * \brief Sets the position of the NPC.
   * \param x The x-coordinate of the NPC's position.
   * \param y The y-coordinate of the NPC's position.
   */
  void setPosition(float x, float y) { npc.setPosition(x, y); }

  /*!
   * \brief Gets the coordinates of the NPC's position.
   * \return The coordinates of the NPC's position.
   */
  sf::Vector2f getPosition() const { return npc.getPosition(); }

  /*!
   * \brief Gets the hit points (health) of the NPC.
   * \return The hit points (health) of the NPC.
   */
  int getHP() const { return HP; }

  /*!
   * \brief Sets the hit points (health) of the NPC.
   * \param newHP The new hit points (health) of the NPC.
   */
  void setHP(int newHP) { HP = newHP; }

  /*!
   * \brief Gets the attack range of the NPC.
   * \return The attack range of the NPC.
   */
  int getAttackDiapason() const { return attack_diapason; }

  /*!
   * \brief Gets the attack power of the NPC.
   * \return The attack power of the NPC.
   */
  int getAttack() const { return attack; }

  /*!
   * \brief Checks if two NPCs are at the same position.
   * \param other The other NPC to compare with.
   * \return True if the two NPCs are at the same position, false otherwise.
   */
  bool operator==(const NPC &other) const {
    return this->getPosition() == other.getPosition();
  }

protected:
  sf::CircleShape npc;
  sf::Color fillColor;
  sf::Color outlineColor;
  float outlineThickness;
  int HP;
  int attack_diapason;
  int attack;
};

/*!
 * \brief A class representing a Knight NPC.
 */
class Knight : public NPC {
public:
  /*!
   * \brief Constructor for Knight with specified parameters.
   * \param size The size of the Knight.
   * \param fillColor The fill color of the Knight.
   * \param HP The hit points (health) of the Knight.
   * \param attack_diapason The attack range of the Knight.
   * \param attack The attack power of the Knight.
   * \param pointsCount The number of points for the Knight shape.
   */
  Knight(float size, const sf::Color &fillColor, int HP, int attack_diapason,
         int attack, int pointsCount)
      : NPC(size, fillColor, HP, attack_diapason, attack, pointsCount) {}
};

/*!
 * \brief A class representing an Archer NPC.
 */
class Archer : public NPC {
public:
  /*!
   * \brief Constructor for Archer with specified parameters.
   * \param size The size of the Archer.
   * \param fillColor The fill color of the Archer.
   * \param HP The hit points (health) of the Archer.
   * \param attack_diapason The attack range of the Archer.
   * \param attack The attack power of the Archer.
   * \param pointsCount The number of points for the Archer shape.
   */
  Archer(float size, const sf::Color &fillColor, int HP, int attack_diapason,
         int attack, int pointsCount)
      : NPC(size, fillColor, HP, attack_diapason, attack, pointsCount) {}
};

/*!
 * \brief A class representing a Cleric NPC.
 */
class Cleric : public NPC {
public:
  /*!
   * \brief Constructor for Cleric with specified parameters.
   * \param size The size of the Cleric.
   * \param fillColor The fill color of the Cleric.
   * \param HP The hit points (health) of the Cleric.
   * \param attack_diapason The attack range of the Cleric.
   * \param attack The attack power of the Cleric.
   * \param healAmount The amount of health the Cleric can heal.
   * \param pointsCount The number of points for the Cleric shape.
   */
  Cleric(float size, const sf::Color &fillColor, int HP, int attack_diapason,
         int attack, int healAmount, int pointsCount)
      : NPC(size, fillColor, HP, attack_diapason, attack, pointsCount),
        healAmount(healAmount) {}

  /*!
   * \brief Gets the amount of health the Cleric can heal.
   * \return The amount of health the Cleric can heal.
   */
  int getHealAmount() const { return healAmount; }

private:
  int healAmount;
};

/*!
 * \brief A class representing a button in the game.
 */
class Button {
public:
  /*!
   * \brief Constructor for Button with specified parameters.
   * \param text The text to display on the button.
   * \param x The x-coordinate of the button's position.
   * \param y The y-coordinate of the button's position.
   * \param width The width of the button.
   * \param height The height of the button.
   * \param fillColor The fill color of the button.
   * \param outlineColor The outline color of the button.
   */
  Button(const std::string &text, float x, float y, float width, float height,
         const sf::Color &fillColor, const sf::Color &outlineColor)
      : text(text), rectangle(sf::Vector2f(width, height)),
        fillColor(fillColor), outlineColor(outlineColor) {
    rectangle.setFillColor(fillColor);
    rectangle.setOutlineColor(outlineColor);
    rectangle.setOutlineThickness(2.f);
    rectangle.setPosition(x, y);

    font.loadFromFile("CyrilicOld.TTF");
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(18);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(
        x + width / 2 - buttonText.getLocalBounds().width / 2,
        y + height / 2 - buttonText.getLocalBounds().height / 2);
  }

  /*!
   * \brief Draws the button to the window.
   * \param window The window to draw the button on.
   */
  void draw(sf::RenderWindow &window) {
    window.draw(rectangle);
    window.draw(buttonText);
  }

  /*!
   * \brief Checks if the mouse position is clicked within the button.
   * \param mousePosition The mouse position in screen coordinates.
   * \return True if the mouse position is clicked within the button, false
   * otherwise.
   */
  bool isClicked(const sf::Vector2i &mousePosition) {
    return mousePosition.x >= rectangle.getPosition().x &&
           mousePosition.x <=
               rectangle.getPosition().x + rectangle.getSize().x &&
           mousePosition.y >= rectangle.getPosition().y &&
           mousePosition.y <= rectangle.getPosition().y + rectangle.getSize().y;
  }

private:
  std::string text;
  sf::RectangleShape rectangle;
  sf::Color fillColor;
  sf::Color outlineColor;
  sf::Font font;
  sf::Text buttonText;
};

/*!
 * \brief Calculates the distance between the centers of two circles.
 * \param circle1 The first circle.
 * \param circle2 The second circle.
 * \return The distance between the centers of the two circles.
 */
float DestinationBetweenCircle(const Circle &circle1, const Circle &circle2) {
  sf::Vector2f center1 = circle1.getCenter();
  sf::Vector2f center2 = circle2.getCenter();
  return sqrt(pow(center1.x - center2.x, 2) + pow(center1.y - center2.y, 2));
}

/*!
 * \brief Checks if the previous circle position is valid for healing.
 * \param circle1 The previous circle.
 * \param circle2 The current circle.
 * \return True if the previous circle position is valid for healing, false
 * otherwise.
 */
bool PositionBetweenTallandnotTall(const Circle &circle1,
                                   const Circle &circle2) {
  sf::Vector2f previouscenter1 = circle1.getCenter();
  sf::Vector2f center2 = circle2.getCenter();
  if (previouscenter1.y == center2.y && previouscenter1.x >= center2.x) {
    return true;
  } else if (previouscenter1.y == center2.y && previouscenter1.x < center2.x) {
    return false;
  }
  return true;
}

/*!
 * \brief Creates a new NPC character based on the specified type.
 * \param type The type of character to create (0: Knight, 1: Archer, 2:
 * Cleric). \param R The radius of the character's circle. \param Player
 * Indicates whether the character belongs to the player or the opponent.
 * \return The newly created NPC character.
 */
NPC createCharacter(int type, float R, bool Player) {
  NPC character(R, Player ? sf::Color::Blue : sf::Color::Red, 50, 2, 1, 4);
  if (type == 0) {
    Knight character(R, Player ? sf::Color::Blue : sf::Color::Red, 50, 2, 20,
                     4);
    return character;
  } else if (type == 1) {
    Archer character(R, Player ? sf::Color::Blue : sf::Color::Red, 30, 10, 15,
                     3);
    return character;
  } else if (type == 2) {
    Cleric character(R, Player ? sf::Color::Blue : sf::Color::Red, 40, 8, 10,
                     15, 100);
    return character;
  }
  return character;
}

/*!
 * \brief Changes the player's turn.
 * \param choice The current player's turn.
 * \return The next player's turn.
 */
bool ChangePlayermove(bool choice) {
  if (choice) {
    return false;
  } else {
    return true;
  }
}


#endif