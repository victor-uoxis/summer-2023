#pragma once
class Player
{
public:
	Player();
	virtual ~Player();

	// Functions

	void moveVector(const float x, const float y);
	void update();
	void move();
	void updateAnimations();
	void updatePhysics();
	void render(sf::RenderTarget& target);

private:
	// Visual
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect frame;
	sf::Clock animationTimer;

	short animState;

	sf::Vector2f velocity;
	float maxVelocity;
	float minVelocity;
	float accel;
	float drag;

	void initVar();
	void initSprite();
	void initTexture();
	void initAnimations();
	void initPhysics();
};

