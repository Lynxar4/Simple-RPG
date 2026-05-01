#include <iostream>
#include <string_view>
#include <vector>
#include "Random.h"
#include <limits>

class Enemy;

class Player
{
public:
	Player() = default;

	void setName(const std::string& name) { m_name = name; }

	int getHealth() const { return m_health; }

	int getAttack() const { return m_attack; }

	void damaged(int amount) { m_health -= amount; }

	void addHealth(int amount) { m_health += amount; }

	void addAttack(int amount) { m_attack += amount; }

	void attack(Enemy& enemy);

	void printStats() const
	{
		std::cout << "max health: " << m_health << '\n';
		std::cout << "attack: " << m_attack << '\n';
		std::cout << "level: " << m_level;
	}

private:
	int m_health{ 100 };
	int m_attack{ 5 };
	int m_level{ 1 };
	std::string m_name{ "Nameless" };
};

class Enemy
{
public:
	enum class Type
	{
		skeleton,
		zombie,
		wolf,
		bandit,
		wizard,
		golem,
		dragon,
	};

	Enemy() = default;
	Enemy(Type type)
		:m_type{ type }
	{
		switch (type)
		{
		case(Type::skeleton):
			m_health = 20;
			m_attack = 10;
			m_name = "Skeleton";
			break;
		case(Type::zombie):
			m_health = 15;
			m_attack = 8;
			m_name = "Zombie";
			break;
		case(Type::wolf):
			m_health = 20;
			m_attack = 25;
			m_name = "Wolf";
			break;
		case(Type::bandit):
			m_health = 40;
			m_attack = 10;
			m_name = "Bandit";
			break;
		case(Type::wizard):
			m_health = 15;
			m_attack = 20;
			m_name = "Wizard";
			break;
		case(Type::golem):
			m_health = 50;
			m_attack = 20;
			m_name = "Golem";
			break;
		case(Type::dragon):
			m_health = 500;
			m_attack = 50;
			m_name = "Dragon";
			break;
		}
	}

	int getHealth() const { return m_health; }

	int getAttack() const { return m_attack; }

	std::string_view getName() const { return m_name; }

	void damaged(int amount) { m_health -= amount; }

	void attack(Player& p);

private:
	int m_health{ 20 };
	int m_attack{ 1 };
	std::string m_name{ "Skelly" };
	Type m_type{ Type::skeleton };
	int m_experience{ 5 };
};

void Player::attack(Enemy& enemy)
{
	enemy.damaged(m_attack);
}

void Enemy::attack(Player& p)
{
	p.damaged(m_attack);
}

struct Area
{
	std::string m_name{};
	std::vector<Enemy> enemies{};

	Enemy getRandomEnemy() const
	{
		int randomEnemy{ Random::get(0, static_cast<int>(enemies.size() - 1)) };
		return enemies[randomEnemy];
	}
};

void levelUp(Player& p)
{
	p.addHealth(5);
	p.addAttack(5);
}

void versus(Player& p, Enemy e)
{
	std::cout << "You are fighting a " << e.getName() << "!\n";
	std::cout << "Your health: " << p.getHealth() << '\n';
	std::cout << e.getName() << "'s health: " << e.getHealth() << "\n\n";
	while (p.getHealth() > 0 && e.getHealth() > 0)
	{
		p.attack(e);
		std::cout << "You hit the " << e.getName() << " for " << p.getAttack() << " damage\n";
		std::cout << e.getName() << "'s health: " << e.getHealth() << '\n';
		if (e.getHealth() <= 0)
		{
			break;
		}

		e.attack(p);
		std::cout << "The " << e.getName() << " hit you for " << e.getAttack() << " damage\n";
		std::cout << "Your health: " << p.getHealth() << '\n';
		std::cout << '\n';
	}
	if (e.getHealth() <= 0)
	{
		std::cout << "You defeated the " << e.getName() << "\n\n";
	}
	else
	{
		std::cout << "You Died.\nTrain harder.\n";
	}
}

int getInput(int lowerBound, int upperBound)
{
	int choice{};
	while (true)
	{
		std::cout << "Enter a number: ";
		std::cin >> choice;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "That's not a number.\n";
			continue;
		}

		if (choice < lowerBound || choice > upperBound)
		{
			std::cout << "Enter a valid number buddy\n";
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return choice;
	}
}

int getChoice()
{
	std::cout << "1. Fight\n2. Run away\n";
	return getInput(1, 2);
}

void handleChoice(Player& p, Enemy e, int choice)
{
	if (choice == 1)
	{
		versus(p, e);
	}
	else if (choice == 2)
	{
		std::cout << "You ran like a coward.\n";
	}
}

std::vector<Area> createWorld()
{
	std::vector<Enemy> villageEnemies{ Enemy{Enemy::Type::zombie}, Enemy{Enemy::Type::skeleton} };
	std::vector<Enemy> mountainEnemies{ Enemy{Enemy::Type::wolf}, Enemy{Enemy::Type::bandit} };
	std::vector<Enemy> ruinEnemies{ Enemy{Enemy::Type::wizard}, Enemy{Enemy::Type::golem} };
	std::vector<Area> areas{ Area{"Village", villageEnemies}, Area{"Mountain", mountainEnemies}, Area{"Ancient Ruins", ruinEnemies} };
	return areas;
}

void intro(Player& player)
{
	std::cout << "Enter your name: ";
	std::string name{};
	std::cin >> name;
	player.setName(name);
	std::cout << "Hi " << name << ", welcome to simple RPG! ";
}

void encounter(Player& p, Area& area)
{
	Enemy random{ area.getRandomEnemy() };
	std::cout << "You encountered a " << random.getName() << '\n';
	handleChoice(p, random, getChoice());
}

void game()
{
	std::vector<Area> areas{ createWorld() };
	Player player{};
	intro(player);

	while (player.getHealth() > 0)
	{
		std::cout << "Where do you want to go mate?\n";
		std::cout << "1. Village\n2. Mountains\n3. Ancient ruins\n4. Quit because you're a noob\n";
		int choice{ getInput(1, 4) };
		if (choice == 4) { return; }
		choice -= 1;
		encounter(player, areas[choice]);
	}
}


int main()
{
	game();
}

