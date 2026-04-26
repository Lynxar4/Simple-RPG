#include <iostream>
#include <string_view>

class Enemy;

class Player
{
	int m_health{ 100 };
	int m_attack{ 5 };
	std::string m_name{ "Nameless" };

public:
	Player() = default;

	void setName(const std::string& name)
	{
		m_name = name;
	}

	int getHealth() const
	{
		return m_health;
	}

	int getAttack() const
	{
		return m_attack;
	}

	void attack(Enemy& enemy);

	void damaged(int amount)
	{
		m_health -= amount;
	}

};

enum class EnemyType
{
	skeleton,
	zombie,
	dragon,
	wizard,
};

class Enemy
{
	int m_health{ 20 };
	int m_attack{ 1 };
	std::string m_name{ "Skelly" };
	EnemyType m_type{ EnemyType::skeleton };

public:
	Enemy() = default;
	Enemy(EnemyType type)
		:m_type{ type }
	{
		switch (type)
		{
		case(EnemyType::skeleton):
			m_health = 20;
			m_attack = 10;
			m_name = "Skeleton";
			break;
		case(EnemyType::zombie):
			m_health = 15;
			m_attack = 8;
			m_name = "Zombie";
			break;
		case(EnemyType::dragon):
			m_health = 500;
			m_attack = 50;
			m_name = "Dragon";
			break;
		case(EnemyType::wizard):
			m_health = 15;
			m_attack = 20;
			m_name = "Wizard";
			break;
		}

	}

	int getHealth() const
	{
		return m_health;
	}

	int getAttack() const
	{
		return m_attack;
	}

	std::string_view getName() const
	{
		return m_name;
	}

	void attack(Player& p);

	void damaged(int amount)
	{
		m_health -= amount;
	}

};

void Player::attack(Enemy& enemy)
{
	enemy.damaged(m_attack);
}

void Enemy::attack(Player& p)
{
	p.damaged(m_attack);
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

int getChoice()
{
	std::cout << "1. Fight\n2. Run away\n";
	int choice{};
	std::cin >> choice;
	return choice;
}

void handleChoice(Player& p, Enemy& e, int choice)
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

void game()
{
	Player player{};
	Enemy zombie{ EnemyType::zombie };
	Enemy skeleton{ EnemyType::skeleton };
	Enemy dragon{ EnemyType::dragon };
	Enemy wizard{ EnemyType::wizard };

	std::cout << "Enter your name: ";
	std::string name{};
	std::cin >> name;
	player.setName(name);
	std::cout << "Hi " << name << " welcome to simple RPG!\n";
	std::cout << "What do you want to do mate?\n";
	std::cout << "1. Go to the village, 2. Go to the cemetary, 3. Go to the mountains, 4. Go to the ancient ruins\n";
	int choice{};
	std::cin >> choice;
	switch (choice)
	{
	case(1):
		std::cout << "omg you encountered a ZOMBIE\n";
		handleChoice(player, zombie, getChoice());
		std::cout << "Another zombie attacks you from behind, you thought there would only be one?\n";
		handleChoice(player, zombie, getChoice());
		break;
	case(2):
		std::cout << "A spooky skeleton appears out of nowhere\n";
		handleChoice(player, skeleton, getChoice());
		break;

	case(3):
		std::cout << "You didn't even climb the mountain yet but a dragon flies towards you\n";
		handleChoice(player, dragon, getChoice());
		break;

	case(4):
		std::cout << "You reach the ruins and then get jumped by a wizard\n";
		handleChoice(player, wizard, getChoice());
		break;
	}
}


int main()
{
	game();
}

