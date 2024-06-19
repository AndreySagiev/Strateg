#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "main.cpp"
#include <stdexcept>

using namespace sf;


TEST_CASE("Circle Class: Constructors and Initial State") {
    // Тестируем конструкторы
    Circle circle1;
    CHECK(circle1.getCenter() == Vector2f(40, 40));
    CHECK(!circle1.isOccupied());
    CHECK(!circle1.isTall());

    Circle circle2(50, Color::Blue, Color::Yellow, 3, 8);
    CHECK(circle2.getCenter() == Vector2f(50, 50));
    CHECK(!circle2.isOccupied());
    CHECK(!circle2.isTall());
}

TEST_CASE("Circle Class: Set Position and Center") {
    Circle circle2(50, Color::Blue, Color::Yellow, 3, 8);
    circle2.setPosition(100, 150);
    CHECK(circle2.getCenter() == Vector2f(150, 200));
}

TEST_CASE("Circle Class: IsClicked Method") {
    Circle circle2(50, Color::Blue, Color::Yellow, 3, 8);
    circle2.setPosition(100, 150);

    CHECK(circle2.isClicked(Vector2i(140, 190), 50)); // Внутри круга
    CHECK(!circle2.isClicked(Vector2i(200, 200), 50)); // Вне круга
}

TEST_CASE("Circle Class: Occupied and Tall Properties") {
    Circle circle2(50, Color::Blue, Color::Yellow, 3, 8);

    // Occupied 
    circle2.setOccupied(true);
    REQUIRE(circle2.isOccupied());
    circle2.setOccupied(false);
    REQUIRE(!circle2.isOccupied());

    // Tall
    circle2.setTall(true);
    REQUIRE(circle2.isTall());
    circle2.setTall(false);
    REQUIRE(!circle2.isTall());
}

TEST_CASE("NPC Class: Constructor and Initial State") {
    NPC npc1(40, Color::Magenta, 100, 5, 10, 6);
    REQUIRE(npc1.getHP() == 100);
    REQUIRE(npc1.getAttackDiapason() == 5);
    REQUIRE(npc1.getAttack() == 10);
}

TEST_CASE("NPC Class: Set Position and Get Position") {
    NPC npc1(40, Color::Magenta, 100, 5, 10, 6);
    npc1.setPosition(200, 250);
    REQUIRE(npc1.getPosition() == Vector2f(200, 250));
}

TEST_CASE("NPC Class: Set HP") {
    NPC npc1(40, Color::Magenta, 100, 5, 10, 6);
    npc1.setHP(75);
    REQUIRE(npc1.getHP() == 75);
}

TEST_CASE("NPC Class: Equality Operator") {
    NPC npc1(40, Color::Magenta, 100, 5, 10, 6);
    npc1.setPosition(200, 250);
    NPC npc2(40, Color::Magenta, 100, 5, 10, 6);

    npc2.setPosition(200, 250);
    REQUIRE(npc1 == npc2);

    npc2.setPosition(250, 250);
    REQUIRE_FALSE(npc1 == npc2);
}

TEST_CASE("Knight Class: Constructor") {
    Knight knight1(40, Color::Blue, 120, 3, 25, 8);
    REQUIRE(knight1.getHP() == 120);
    REQUIRE(knight1.getAttackDiapason() == 3);
    REQUIRE(knight1.getAttack() == 25);
}

TEST_CASE("Archer Class: Constructor") {
    Archer archer1(30, Color::Green, 80, 7, 18, 5);
    REQUIRE(archer1.getHP() == 80);
    REQUIRE(archer1.getAttackDiapason() == 7);
    REQUIRE(archer1.getAttack() == 18);
}

TEST_CASE("Cleric Class: Constructor") {
    Cleric cleric1(40, Color::Yellow, 60, 4, 12, 15, 6);
    REQUIRE(cleric1.getHP() == 60);
    REQUIRE(cleric1.getAttackDiapason() == 4);
    REQUIRE(cleric1.getAttack() == 12);
    REQUIRE(cleric1.getHealAmount() == 15);
}

TEST_CASE("Button Class: Constructor and Initial State") {
    Button button1("Start", 100, 100, 100, 50, Color::Cyan, Color::Black);
    REQUIRE(button1.text == "Start");
    REQUIRE(button1.rectangle.getPosition() == Vector2f(100, 100));
    REQUIRE(button1.rectangle.getSize() == Vector2f(100, 50));
    REQUIRE(button1.fillColor == Color::Cyan);
    REQUIRE(button1.outlineColor == Color::Black);
}

TEST_CASE("Button Class: IsClicked Method") {
    Button button1("Start", 100, 100, 100, 50, Color::Cyan, Color::Black);
    REQUIRE(button1.isClicked(Vector2i(120, 120))); // Внутри кнопки
    REQUIRE_FALSE(button1.isClicked(Vector2i(50, 50))); // Вне кнопки
}

TEST_CASE("DestinationBetweenCircle Function: Calculate Distance") {
    Circle circle1(40, Color::Red, Color::Green, 2, 6);
    circle1.setPosition(100, 100);
    Circle circle2(40, Color::Blue, Color::Yellow, 3, 8);
    circle2.setPosition(200, 200);

    float distance = DestinationBetweenCircle(circle1, circle2);
    CHECK(distance == Approx(141.421356));
}

TEST_CASE("PositionBetweenTallandnotTall Function: Valid Healing Position") {
    Circle circle1(40, Color::Red, Color::Green, 2, 6);
    circle1.setPosition(150, 100);
    Circle circle2(40, Color::Blue, Color::Yellow, 3, 8);
    circle2.setPosition(100, 100);

    REQUIRE(PositionBetweenTallandnotTall(circle1, circle2) == true);

    circle2.setPosition(200, 100);

    REQUIRE(PositionBetweenTallandnotTall(circle1, circle2) == false);
}

TEST_CASE("createCharacter Function: Create Knight") {
    NPC knight = createCharacter(0, 40, true);
    REQUIRE(knight.getHP() == 50);
    REQUIRE(knight.getAttackDiapason() == 2);
    REQUIRE(knight.getAttack() == 20);
    REQUIRE(knight.fillColor == Color::Blue);
}

TEST_CASE("createCharacter Function: Create Archer") {
    NPC archer = createCharacter(1, 30, false);
    REQUIRE(archer.getHP() == 30);
    REQUIRE(archer.getAttackDiapason() == 10);
    REQUIRE(archer.getAttack() == 15);
    REQUIRE(archer.fillColor == Color::Red);
}

TEST_CASE("createCharacter Function: Create Cleric") {
    NPC cleric = createCharacter(2, 40, true);
    REQUIRE(cleric.getHP() == 40);
    REQUIRE(cleric.getAttackDiapason() == 8);
    REQUIRE(cleric.getAttack() == 10);
    REQUIRE(cleric.fillColor == Color::Blue);
}

TEST_CASE("ChangePlayermove Function: Toggle Player Turn") {
    REQUIRE(ChangePlayermove(true) == false);
    REQUIRE(ChangePlayermove(false) == true);
}