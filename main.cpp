/*!
 * \file main.cpp
 * \brief Main file
 * \author Sagiev Vanillov
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>


 /*!
   * \brief  A class representing a circle on the game board.
   */
class Circle {
public:
    /*!
     * \brief Default constructor for Circle.
     */
    Circle() : circle(40.f), fillColor(sf::Color::Red), outlineColor(sf::Color::Green), outlineThickness(2.f), occupied(false), tall(false) {
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
    Circle(float radius, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness, int pointsCount = 6) :
        circle(radius, pointsCount), fillColor(fillColor), outlineColor(outlineColor), outlineThickness(outlineThickness), occupied(false), tall(false) {
        circle.setFillColor(fillColor);
        circle.setOutlineThickness(outlineThickness);
        circle.setOutlineColor(outlineColor);
    }

    /*!
     * \brief Draws the circle to the window.
     * \param window The window to draw the circle on.
     */
    void draw(sf::RenderWindow& window) {
        // Изменяем цвет круга, если он высокий
        if (tall) {
            circle.setFillColor(sf::Color(255, 165, 0)); // Оранжевый
        }
        else {
            circle.setFillColor(fillColor); // Базовый цвет
        }

        window.draw(circle);
    }

    /*!
     * \brief Sets the position of the circle.
     * \param x The x-coordinate of the circle's position.
     * \param y The y-coordinate of the circle's position.
     */
    void setPosition(float x, float y) {
        circle.setPosition(x, y);
    }

    /*!
     * \brief Checks if the mouse position is clicked within the circle.
     * \param mousePosition The mouse position in screen coordinates.
     * \param r The radius of the circle.
     * \return True if the mouse position is clicked within the circle, false otherwise.
     */
    bool isClicked(const sf::Vector2i& mousePosition, float r) {
        // Получаем центр круга
        sf::Vector2f center = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());

        // Вычисляем расстояние от курсора до центра круга
        float distance = sqrt(pow(mousePosition.x - center.x, 2) + pow(mousePosition.y - center.y, 2));

        // Проверяем, находится ли курсор внутри круга
        return distance <= r;
    }

    /*!
     * \brief Gets the coordinates of the circle's center.
     * \return The coordinates of the circle's center.
     */
    sf::Vector2f getCenter() const {
        return circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    }

    /*!
     * \brief Checks if the circle is occupied.
     * \return True if the circle is occupied, false otherwise.
     */
    bool isOccupied() const {
        return occupied;
    }

    /*!
     * \brief Sets the occupied status of the circle.
     * \param value The new occupied status of the circle.
     */
    void setOccupied(bool value) {
        occupied = value;
    }

    /*!
     * \brief Checks if the circle is tall.
     * \return True if the circle is tall, false otherwise.
     */
    bool isTall() const {
        return tall;
    }

    /*!
     * \brief Sets the tall status of the circle.
     * \param value The new tall status of the circle.
     */
    void setTall(bool value) {
        tall = value;
    }

private:
    sf::CircleShape circle;
    sf::Color fillColor;
    sf::Color outlineColor;
    float outlineThickness;
    bool occupied; //  Занято ли клетка
    bool tall; //  Является ли клетка "высокой"
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
    NPC(float size, const sf::Color& fillColor, int HP, int attack_diapason, int attack, int pointsCount) :
        npc(size, pointsCount), fillColor(fillColor), outlineColor(sf::Color::Black), outlineThickness(2.f),
        HP(HP), attack_diapason(attack_diapason), attack(attack) {
        npc.setFillColor(fillColor);
        npc.setOutlineThickness(outlineThickness);
        npc.setOutlineColor(outlineColor);
    }

    /*!
     * \brief Draws the NPC to the window.
     * \param window The window to draw the NPC on.
     */
    void draw(sf::RenderWindow& window) const {
        window.draw(npc);
    }

    /*!
     * \brief Sets the position of the NPC.
     * \param x The x-coordinate of the NPC's position.
     * \param y The y-coordinate of the NPC's position.
     */
    void setPosition(float x, float y) {
        npc.setPosition(x, y);
    }

    /*!
     * \brief Gets the coordinates of the NPC's position.
     * \return The coordinates of the NPC's position.
     */
    sf::Vector2f getPosition() const {
        return npc.getPosition();
    }

    /*!
     * \brief Gets the hit points (health) of the NPC.
     * \return The hit points (health) of the NPC.
     */
    int getHP() const {
        return HP;
    }

    /*!
     * \brief Sets the hit points (health) of the NPC.
     * \param newHP The new hit points (health) of the NPC.
     */
    void setHP(int newHP) {
        HP = newHP;
    }

    /*!
     * \brief Gets the attack range of the NPC.
     * \return The attack range of the NPC.
     */
    int getAttackDiapason() const {
        return attack_diapason;
    }

    /*!
     * \brief Gets the attack power of the NPC.
     * \return The attack power of the NPC.
     */
    int getAttack() const {
        return attack;
    }

    /*!
     * \brief Checks if two NPCs are at the same position.
     * \param other The other NPC to compare with.
     * \return True if the two NPCs are at the same position, false otherwise.
     */
    bool operator==(const NPC& other) const {
        return this->getPosition() == other.getPosition();
    }


protected:
    sf::CircleShape npc;
    sf::Color fillColor;
    sf::Color outlineColor;
    float outlineThickness;
    int HP; //  Количество очков здоровья
    int attack_diapason; //  Диапазон атаки
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
    Knight(float size, const sf::Color& fillColor, int HP, int attack_diapason, int attack, int pointsCount) :
        NPC(size, fillColor, HP, attack_diapason, attack, pointsCount) {}


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
    Archer(float size, const sf::Color& fillColor, int HP, int attack_diapason, int attack, int pointsCount) :
        NPC(size, fillColor, HP, attack_diapason, attack, pointsCount) {}

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
    Cleric(float size, const sf::Color& fillColor, int HP, int attack_diapason, int attack, int healAmount, int pointsCount) :
        NPC(size, fillColor, HP, attack_diapason, attack, pointsCount), healAmount(healAmount) {}

    /*!
     * \brief Gets the amount of health the Cleric can heal.
     * \return The amount of health the Cleric can heal.
     */
    int getHealAmount() const {
        return healAmount;
    }

private:
    int healAmount; // Количество восстановленного здоровья
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
    Button(const std::string& text, float x, float y, float width, float height, const sf::Color& fillColor, const sf::Color& outlineColor) :
        text(text),
        rectangle(sf::Vector2f(width, height)),
        fillColor(fillColor),
        outlineColor(outlineColor) {
        rectangle.setFillColor(fillColor);
        rectangle.setOutlineColor(outlineColor);
        rectangle.setOutlineThickness(2.f);
        rectangle.setPosition(x, y);

        // Создаем текст для кнопки
        font.loadFromFile("CyrilicOld.ttf");
        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(18);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setPosition(x + width / 2 - buttonText.getLocalBounds().width / 2, y + height / 2 - buttonText.getLocalBounds().height / 2);
    }

    /*!
     * \brief Draws the button to the window.
     * \param window The window to draw the button on.
     */
    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);
        window.draw(buttonText);
    }

    /*!
     * \brief Checks if the mouse position is clicked within the button.
     * \param mousePosition The mouse position in screen coordinates.
     * \return True if the mouse position is clicked within the button, false otherwise.
     */
    bool isClicked(const sf::Vector2i& mousePosition) {
        return mousePosition.x >= rectangle.getPosition().x &&
            mousePosition.x <= rectangle.getPosition().x + rectangle.getSize().x &&
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
float DestinationBetweenCircle(const Circle& circle1, const Circle& circle2) {
    sf::Vector2f center1 = circle1.getCenter();
    sf::Vector2f center2 = circle2.getCenter();
    return sqrt(pow(center1.x - center2.x, 2) + pow(center1.y - center2.y, 2));
}

/*!
 * \brief Checks if the previous circle position is valid for healing.
 * \param circle1 The previous circle.
 * \param circle2 The current circle.
 * \return True if the previous circle position is valid for healing, false otherwise.
 */
bool PositionBetweenTallandnotTall(const Circle& circle1, const Circle& circle2) {
    sf::Vector2f previouscenter1 = circle1.getCenter();
    sf::Vector2f center2 = circle2.getCenter();
    if (previouscenter1.y == center2.y && previouscenter1.x >= center2.x) {
        return true;
    }
    else if (previouscenter1.y == center2.y && previouscenter1.x < center2.x) {
        return false;
    }
    return true;
}

/*!
 * \brief Creates a new NPC character based on the specified type.
 * \param type The type of character to create (0: Knight, 1: Archer, 2: Cleric).
 * \param R The radius of the character's circle.
 * \param Player Indicates whether the character belongs to the player or the opponent.
 * \return The newly created NPC character.
 */
NPC createCharacter(int type, float R, bool Player) {
    NPC character(R, Player ? sf::Color::Blue : sf::Color::Red, 50, 2, 1, 4);
    if (type == 0) {
        Knight character(R, Player ? sf::Color::Blue : sf::Color::Red, 50, 2, 20, 4);
        return character;
    }
    else if (type == 1) {
        Archer character(R, Player ? sf::Color::Blue : sf::Color::Red, 30, 10, 15, 3);
        return character;
    }
    else if (type == 2) {
        Cleric character(R, Player ? sf::Color::Blue : sf::Color::Red, 40, 8, 10, 15, 100);
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
    }
    else {
        return true;
    }
}

int main() {
    srand(time(0));

    int block = 40;
    sf::RenderWindow window(sf::VideoMode(30 * block, 25 * block), L"Strateg");

    float R = 50.f; // Радиус круга
    float r = (R * std::sqrt(3)) / 2;
    int cols = 8; // Количество столбцов
    int rows = 8; // Количество строк

    // Вычисляем размер сетки в пикселях
    float gridWidth = cols * (R * 2);
    float gridHeight = rows * (R * 2);

    // Вычисляем координаты центра экрана
    float centerX = window.getSize().x / 2.f;
    float centerY = window.getSize().y / 2.f;

    int number_of_tall{ 4 };
    // Создаем вектор векторов для хранения кругов
    std::vector<std::vector<Circle>> circles(rows, std::vector<Circle>(cols));

    int maxNPC;
    std::cout << "MaxNpc:" << std::endl;
    std::cin >> maxNPC;
    
    // Создаем векторы для хранения рыцарей
    std::vector<NPC> NPC_Player1;
    std::vector<NPC> NPC_Player2;
    int typeNPC = 0;

    Button finishButton("Закончить выбор", 10.f, window.getSize().y - 50.f, 150.f, 30.f, sf::Color(0, 255, 0), sf::Color(0, 0, 0));

    bool selectNPC = false;
    int positionNPC = -1;
    std::pair <int, int> previousCircle{ 0, 0 };

    bool gameStart = false;
    bool Finish = false;
    bool Player1move = true;

    // Переменная для выбора цвета рыцаря
    bool Player1_choice = true;


    sf::Font font;
    if (!font.loadFromFile("CyrilicOld.ttf")) { // Замените путь на ваш файл шрифта
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
        return 1;
    }
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(90);
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect textRectover = gameOverText.getLocalBounds();
    gameOverText.setPosition((window.getSize().x - textRectover.width) / 4.f, 300.f);

    sf::Text turnText;
    turnText.setFont(font);
    turnText.setString("Ход: Player 1");
    turnText.setCharacterSize(50);
    turnText.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = turnText.getLocalBounds();
    turnText.setPosition((window.getSize().x - textRect.width) / 2.f, 10.f);

    // Заполняем вектор векторов кругами
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Позиция круга с учетом центра сетки
            float x = centerX - gridWidth / 2.f + j * (r * 2);
            float y = centerY - gridHeight / 2.f + i * (R * 1.5);

            // Смещение для четных строк
            if (i % 2 == 1) {
                x += r; // Смещаем круг влево на половину расстояния между центрами
            }

            // Создание круга и добавление его в вектор
            circles[i][j] = Circle(R, sf::Color(115, 144, 46), sf::Color(0, 90, 50), 2.f);
            if (rand() % 2 == 0 && j != 0 && j != cols - 1 && i != 0 && i != rows - 1 && number_of_tall != 0) {
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
                if (event.mouseButton.button == sf::Mouse::Left && finishButton.isClicked(mousePosition)) {
                    gameStart = true;
                }
                else if (!gameStart) {
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (circles[i][j].isClicked(mousePosition, r)) {
                                // Получаем координаты центра кликнутого круга
                                if (event.mouseButton.button == sf::Mouse::Left) {
                                    // Проверяем, не занята ли клетка
                                    if (!circles[i][j].isOccupied()) {
                                        sf::Vector2f center = circles[i][j].getCenter();
                                        if ((Player1_choice && NPC_Player1.size() < maxNPC) || (!Player1_choice && NPC_Player2.size() < maxNPC)) {
                                            // Создаем рыцаря
                                            NPC npc = createCharacter(typeNPC, r, Player1_choice); // Задаем начальные характеристики
                                            npc.setPosition(center.x - r , center.y - r);

                                            if (Player1_choice && j < 2) {
                                                NPC_Player1.push_back(npc);// Помечаем клетку как занятую
                                                circles[i][j].setOccupied(true);
                                                std::cout << "Cell: (" << center.x << ", " << center.y << ")" << std::endl;
                                            }
                                            else if (!Player1_choice && j > 5) {
                                                NPC_Player2.push_back(npc);
                                                circles[i][j].setOccupied(true);
                                                std::cout << "Cell: (" << center.x << ", " << center.y << ")" << std::endl;
                                            }
                                        }
                                        else {
                                            // Выводим сообщение, что рыцарей уже достаточно
                                            std::cout << "Max NPC!" << std::endl;
                                        }
                                        break;
                                    }
                                    else {
                                        // Выводим сообщение о том, что клетка занята
                                        std::cout << "Сell is Occupied!" << std::endl;
                                    }
                                }
                                else if (event.mouseButton.button == sf::Mouse::Right) { // Обрабатываем правый клик
                                    // Проверяем, есть ли рыцарь на этой клетке
                                    if (circles[i][j].isOccupied()) {
                                        // Находим рыцаря в списке knights
                                        for (size_t k = 0; k < (Player1_choice ? NPC_Player1.size() : NPC_Player2.size()); ++k) {
                                            // Получаем позицию рыцаря
                                            sf::Vector2f npcPos = (Player1_choice ? NPC_Player1[k] : NPC_Player2[k]).getPosition();
                                            // Сравниваем позицию рыцаря с позицией клетки
                                            if (npcPos.x == circles[i][j].getCenter().x - r  &&
                                                npcPos.y == circles[i][j].getCenter().y - r ) {
                                                // Удаляем рыцаря из вектора
                                                if (Player1_choice) {
                                                    NPC_Player1.erase(NPC_Player1.begin() + k);
                                                }
                                                else {
                                                    NPC_Player2.erase(NPC_Player2.begin() + k);
                                                }

                                                // Помечаем клетку как свободную
                                                circles[i][j].setOccupied(false);

                                                std::cout << "NPC deleted!" << std::endl;

                                                break; // Выходим из цикла, когда нашли нужного рыцаря
                                            }
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
                else if (gameStart) {
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (circles[i][j].isClicked(mousePosition, r)) {
                                if (circles[i][j].isOccupied() && event.mouseButton.button == sf::Mouse::Left && !selectNPC) {
                                    for (size_t k = 0; k < (Player1move ? NPC_Player1.size() : NPC_Player2.size()); ++k) {
                                        sf::Vector2f npcPos = (Player1move ? NPC_Player1[k] : NPC_Player2[k]).getPosition();
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
                                }
                                else if (circles[i][j].isOccupied() && event.mouseButton.button == sf::Mouse::Right) {
                                    if (DestinationBetweenCircle(circles[i][j], circles[previousCircle.first][previousCircle.second]) <=
                                        (Player1move ? NPC_Player1[positionNPC].getAttackDiapason() : NPC_Player2[positionNPC].getAttackDiapason()) * r + r / 10 &&
                                        selectNPC) {
                                        // Нанесение урона
                                        if (Player1move) {
                                            for (size_t k = 0; k < NPC_Player2.size(); ++k) {
                                                if (NPC_Player2[k].getPosition() == circles[i][j].getCenter() - sf::Vector2f(r, r)) {
                                                    NPC_Player2[k].setHP(NPC_Player2[k].getHP() - NPC_Player1[positionNPC].getAttack());
                                                    if (NPC_Player2[k].getHP() <= 0) {
                                                        std::cout << NPC_Player2[k].getHP() << std::endl;
                                                        NPC_Player2.erase(NPC_Player2.begin() + k);
                                                        circles[i][j].setOccupied(false);
                                                    }
                                                    std::cout << "Damage received!" << std::endl;
                                                    // ... (Проверка на уничтожение, ...) ...
                                                    break;
                                                }
                                            }
                                        }
                                        else {
                                            for (size_t k = 0; k < NPC_Player1.size(); ++k) {
                                                if (NPC_Player1[k].getPosition() == circles[i][j].getCenter() - sf::Vector2f(r, r)) {
                                                    NPC_Player1[k].setHP(NPC_Player1[k].getHP() - NPC_Player2[positionNPC].getAttack());
                                                    std::cout << "Damage received!" << std::endl;
                                                    if (NPC_Player1[k].getHP() <= 0) {
                                                        std::cout << NPC_Player1[k].getHP() << std::endl;
                                                        NPC_Player1.erase(NPC_Player1.begin() + k);
                                                        circles[i][j].setOccupied(false);
                                                    }
                                                    // ... (Проверка на уничтожение, ...) ...
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
                                }
                                else if (!circles[i][j].isOccupied() && event.mouseButton.button == sf::Mouse::Right) {
                                    if (DestinationBetweenCircle(circles[i][j], circles[previousCircle.first][previousCircle.second]) <= 2 * r + r / 10 && positionNPC != -1) {
                                        if ((circles[i][j].isTall() == false && circles[previousCircle.first][previousCircle.second].isTall() == false) ||
                                            (circles[i][j].isTall() == true && circles[previousCircle.first][previousCircle.second].isTall() == false && !PositionBetweenTallandnotTall(circles[previousCircle.first][previousCircle.second], circles[i][j])) || 
                                            (circles[i][j].isTall() == false && circles[previousCircle.first][previousCircle.second].isTall() == true) || 
                                            (circles[i][j].isTall() == true && circles[previousCircle.first][previousCircle.second].isTall() == true)) {
                                            sf::Vector2f newPos = circles[i][j].getCenter() - sf::Vector2f(r, r);
                                            (Player1move ? NPC_Player1[positionNPC] : NPC_Player2[positionNPC]).setPosition(newPos.x, newPos.y);

                                            // Обновление состояния занятости клеток
                                            circles[previousCircle.first][previousCircle.second].setOccupied(false);
                                            circles[i][j].setOccupied(true);

                                            // Сброс выбора рыцаря
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
            if (event.type == sf::Event::KeyPressed) { // Обрабатываем нажатие клавиш
                if (event.key.code == sf::Keyboard::Space) {
                    Player1_choice = !Player1_choice;
                    std::cout << "Player choice change!" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Tab) {
                    typeNPC = (typeNPC + 1) % 3;
                    std::cout << "Change type" << typeNPC << std::endl;
                }
            }
        }

        // Отрисовка всех кругов
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                circles[i][j].draw(window);
            }
        }

        // Отрисовка всех рыцарей
        for (const auto& npc : NPC_Player1) { // Используем const-ссылку
            npc.draw(window);
        }

        for (const auto& npc : NPC_Player2) { // Используем const-ссылку
            npc.draw(window);
        }

        if (!gameStart) {
            finishButton.draw(window);
        }
        if (Player1move) {
            turnText.setString("Ход: Player 1");
        }
        else {
            turnText.setString("Ход: Player 2");
        }
        if (Finish) {
            if (NPC_Player2.size() == 0) {
                gameOverText.setString("Выиграл: Player 1");
            }
            else if (NPC_Player1.size() == 0) {
                gameOverText.setString("Выиграл: Player 2");
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
