/*!
 * \file main.cpp
 * \brief Main file
 * \author Sagiev Vanillov
 */

#include "func.h"

int main() {
  srand(time(0));

  int block = 40;
  sf::RenderWindow window(sf::VideoMode(30 * block, 25 * block), L"Strateg");

  float R = 50.f; 
  float r = (R * std::sqrt(3)) / 2;
  int cols = 8; 
  int rows = 8; 

  float gridWidth = cols * (R * 2);
  float gridHeight = rows * (R * 2);

  float centerX = window.getSize().x / 2.f;
  float centerY = window.getSize().y / 2.f;

  int number_of_tall{4};
  std::vector<std::vector<Circle>> circles(rows, std::vector<Circle>(cols));

  int maxNPC;
  std::cout << "MaxNpc:" << std::endl;
  std::cin >> maxNPC;

  std::vector<NPC> NPC_Player1;
  std::vector<NPC> NPC_Player2;
  int typeNPC = 0;

  Button finishButton("Finish the selection", 10.f, window.getSize().y - 50.f, 150.f,
                      30.f, sf::Color(0, 255, 0), sf::Color(0, 0, 0));

  bool selectNPC = false;
  int positionNPC = -1;
  std::pair<int, int> previousCircle{0, 0};

  bool gameStart = false;
  bool Finish = false;
  bool Player1move = true;

  bool Player1_choice = true;

  sf::Font font;
  if (!font.loadFromFile(
          "CyrilicOld.TTF")) { 
    std::cerr << "������ �������� ������!" << std::endl;
    return 1;
  }
  sf::Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setCharacterSize(90);
  gameOverText.setFillColor(sf::Color::Red);
  sf::FloatRect textRectover = gameOverText.getLocalBounds();
  gameOverText.setPosition((window.getSize().x - textRectover.width) / 4.f,
                           300.f);

  sf::Text turnText;
  turnText.setFont(font);
  turnText.setString("���: Player 1");
  turnText.setCharacterSize(50);
  turnText.setFillColor(sf::Color::Black);
  sf::FloatRect textRect = turnText.getLocalBounds();
  turnText.setPosition((window.getSize().x - textRect.width) / 2.f, 10.f);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      float x = centerX - gridWidth / 2.f + j * (r * 2);
      float y = centerY - gridHeight / 2.f + i * (R * 1.5);

      if (i % 2 == 1) {
        x += r;
      }

      circles[i][j] =
          Circle(R, sf::Color(115, 144, 46), sf::Color(0, 90, 50), 2.f);
      if (rand() % 2 == 0 && j != 0 && j != cols - 1 && i != 0 &&
          i != rows - 1 && number_of_tall != 0) {
        circles[i][j].setTall(true);
        number_of_tall -= 1;
      }
      circles[i][j].setPosition(x, y);
    }
  }

  while (window.isOpen()) {
    window.clear(sf::Color(249, 173, 170));
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed && !Finish) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (event.mouseButton.button == sf::Mouse::Left &&
            finishButton.isClicked(mousePosition)) {
          gameStart = true;
        } else if (!gameStart) {
          for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
              if (circles[i][j].isClicked(mousePosition, r)) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                  if (!circles[i][j].isOccupied()) {
                    sf::Vector2f center = circles[i][j].getCenter();
                    if ((Player1_choice && NPC_Player1.size() < maxNPC) ||
                        (!Player1_choice && NPC_Player2.size() < maxNPC)) {
                      NPC npc = createCharacter(
                          typeNPC, r,
                          Player1_choice);
                      npc.setPosition(center.x - r, center.y - r);

                      if (Player1_choice && j < 2) {
                        NPC_Player1.push_back(
                            npc); 
                        circles[i][j].setOccupied(true);
                        std::cout << "Cell: (" << center.x << ", " << center.y
                                  << ")" << std::endl;
                      } else if (!Player1_choice && j > 5) {
                        NPC_Player2.push_back(npc);
                        circles[i][j].setOccupied(true);
                        std::cout << "Cell: (" << center.x << ", " << center.y
                                  << ")" << std::endl;
                      }
                    } else {
                      std::cout << "Max NPC!" << std::endl;
                    }
                    break;
                  } else {
                    std::cout << "�ell is Occupied!" << std::endl;
                  }
                } else if (event.mouseButton.button ==
                           sf::Mouse::Right) { 
                  if (circles[i][j].isOccupied()) {
                    for (size_t k = 0;
                         k < (Player1_choice ? NPC_Player1.size()
                                             : NPC_Player2.size());
                         ++k) {
                      sf::Vector2f npcPos =
                          (Player1_choice ? NPC_Player1[k] : NPC_Player2[k])
                              .getPosition();
                      if (npcPos.x == circles[i][j].getCenter().x - r &&
                          npcPos.y == circles[i][j].getCenter().y - r) {
                        if (Player1_choice) {
                          NPC_Player1.erase(NPC_Player1.begin() + k);
                        } else {
                          NPC_Player2.erase(NPC_Player2.begin() + k);
                        }

                        circles[i][j].setOccupied(false);

                        std::cout << "NPC deleted!" << std::endl;

                        break;
                      }
                    }
                  }
                }
                break;
              }
            }
          }
        } else if (gameStart) {
          for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
              if (circles[i][j].isClicked(mousePosition, r)) {
                if (circles[i][j].isOccupied() &&
                    event.mouseButton.button == sf::Mouse::Left && !selectNPC) {
                  for (size_t k = 0; k < (Player1move ? NPC_Player1.size()
                                                      : NPC_Player2.size());
                       ++k) {
                    sf::Vector2f npcPos =
                        (Player1move ? NPC_Player1[k] : NPC_Player2[k])
                            .getPosition();
                    if (npcPos.x == circles[i][j].getCenter().x - r &&
                        npcPos.y == circles[i][j].getCenter().y - r) {
                      selectNPC = true;
                      positionNPC = k;
                      previousCircle.first = i;
                      previousCircle.second = j;
                      std::cout << "NPC choice!" << std::endl;
                      break;
                    }
                  }
                } else if (circles[i][j].isOccupied() &&
                           event.mouseButton.button == sf::Mouse::Right) {
                  if (DestinationBetweenCircle(
                          circles[i][j], circles[previousCircle.first]
                                                [previousCircle.second]) <=
                          (Player1move
                               ? NPC_Player1[positionNPC].getAttackDiapason()
                               : NPC_Player2[positionNPC].getAttackDiapason()) *
                                  r +
                              r / 10 &&
                      selectNPC) {
                    if (Player1move) {
                      for (size_t k = 0; k < NPC_Player2.size(); ++k) {
                        if (NPC_Player2[k].getPosition() ==
                            circles[i][j].getCenter() - sf::Vector2f(r, r)) {
                          NPC_Player2[k].setHP(
                              NPC_Player2[k].getHP() -
                              NPC_Player1[positionNPC].getAttack());
                          if (NPC_Player2[k].getHP() <= 0) {
                            std::cout << NPC_Player2[k].getHP() << std::endl;
                            NPC_Player2.erase(NPC_Player2.begin() + k);
                            circles[i][j].setOccupied(false);
                          }
                          std::cout << "Damage received!" << std::endl;
                          break;
                        }
                      }
                    } else {
                      for (size_t k = 0; k < NPC_Player1.size(); ++k) {
                        if (NPC_Player1[k].getPosition() ==
                            circles[i][j].getCenter() - sf::Vector2f(r, r)) {
                          NPC_Player1[k].setHP(
                              NPC_Player1[k].getHP() -
                              NPC_Player2[positionNPC].getAttack());
                          std::cout << "Damage received!" << std::endl;
                          if (NPC_Player1[k].getHP() <= 0) {
                            std::cout << NPC_Player1[k].getHP() << std::endl;
                            NPC_Player1.erase(NPC_Player1.begin() + k);
                            circles[i][j].setOccupied(false);
                          }
                          break;
                        }
                      }
                    }
                    if (NPC_Player2.size() == 0 || NPC_Player1.size() == 0) {
                      Finish = true;
                    }
                    selectNPC = false;
                    positionNPC = -1;
                    Player1move = !Player1move;
                  }
                } else if (!circles[i][j].isOccupied() &&
                           event.mouseButton.button == sf::Mouse::Right) {
                  if (DestinationBetweenCircle(
                          circles[i][j],
                          circles[previousCircle.first]
                                 [previousCircle.second]) <= 2 * r + r / 10 &&
                      positionNPC != -1) {
                    if ((circles[i][j].isTall() == false &&
                         circles[previousCircle.first][previousCircle.second]
                                 .isTall() == false) ||
                        (circles[i][j].isTall() == true &&
                         circles[previousCircle.first][previousCircle.second]
                                 .isTall() == false &&
                         !PositionBetweenTallandnotTall(
                             circles[previousCircle.first]
                                    [previousCircle.second],
                             circles[i][j])) ||
                        (circles[i][j].isTall() == false &&
                         circles[previousCircle.first][previousCircle.second]
                                 .isTall() == true) ||
                        (circles[i][j].isTall() == true &&
                         circles[previousCircle.first][previousCircle.second]
                                 .isTall() == true)) {
                      sf::Vector2f newPos =
                          circles[i][j].getCenter() - sf::Vector2f(r, r);
                      (Player1move ? NPC_Player1[positionNPC]
                                   : NPC_Player2[positionNPC])
                          .setPosition(newPos.x, newPos.y);

                      circles[previousCircle.first][previousCircle.second]
                          .setOccupied(false);
                      circles[i][j].setOccupied(true);

                      selectNPC = false;
                      positionNPC = -1;
                      Player1move = !Player1move;

                      std::cout << "NPC move!" << std::endl;
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
          Player1_choice = !Player1_choice;
          std::cout << "Player choice change!" << std::endl;
        } else if (event.key.code == sf::Keyboard::Tab) {
          typeNPC = (typeNPC + 1) % 3;
          std::cout << "Change type" << typeNPC << std::endl;
        }
      }
    }

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        circles[i][j].draw(window);
      }
    }

    for (const auto &npc : NPC_Player1) { 
      npc.draw(window);
    }

    for (const auto &npc : NPC_Player2) {
      npc.draw(window);
    }

    if (!gameStart) {
      finishButton.draw(window);
    }
    if (Player1move) {
      turnText.setString("���: Player 1");
    } else {
      turnText.setString("���: Player 2");
    }
    if (Finish) {
      if (NPC_Player2.size() == 0) {
        gameOverText.setString("�������: Player 1");
      } else if (NPC_Player1.size() == 0) {
        gameOverText.setString("�������: Player 2");
      }
      window.draw(gameOverText);
    }
    if (gameStart) {
      window.draw(turnText);
    }

    window.display();
  }

  return 0;
}
