#include "ScenePlay.h"
#include <fstream>
#include <sstream>

void ScenePlay::update()
{
	//std::cout << "CALLS UPDATE FROM SCENE PLAY" << std::endl;
	m_entities.update();
	/*sAnimation();
	m_player->getComponent<CAnimation>().animation.update();
	auto& enemies = m_entities.getEntities("enemy");
	for (auto& e : enemies)
	{
		e->getComponent<CAnimation>().animation.update();
	}
	sCollision();
	sGravity();
	sMovement();*/
	sRender();
}

void ScenePlay::sDoAction(const Action& action)
{
	if (action.type() == "START") 
	{
		if (action.name() == "JUMP")
		{
			m_player->getComponent<CInput>().up = true;
			m_player->getComponent<CState>().state = "jump";
		}
		else if (action.name() == "LEFT")
		{
			m_player->getComponent<CInput>().left = true;
			m_player->getComponent<CState>().state = "runLeft";
		}
		else if (action.name() == "RIGHT")
		{
			m_player->getComponent<CInput>().right = true;
			m_player->getComponent<CState>().state = "runRight";
		}
		else if (action.name() == "EXIT")
		{
			onEnd();
		}
		else if (action.name() == "PAUSE")
		{
			setPaused(!m_paused);
		}
		
		//toggle_grid
		//toggle_texture
		//toggle_collision
	} 
	else if (action.type() == "END")
	{
		if (action.name() == "JUMP")
		{
			auto& t = m_player->getComponent<CTransform>();
			m_player->getComponent<CInput>().up = false;
			//m_player->getComponent<CState>().state = t.pos.x > t.prevPos.x ? "idleRight" : "idleLeft";
		}
		else if (action.name() == "LEFT")
		{
			m_player->getComponent<CInput>().left = false;
			m_player->getComponent<CState>().state = "idleLeft";
		}
		else if (action.name() == "RIGHT")
		{
			m_player->getComponent<CInput>().right = false;
			m_player->getComponent<CState>().state = "idleRight";
		}
		
	}
}

void ScenePlay::sRender()
{	
	//TODO: Implement this
	auto& window = m_game->window();

	window.clear();

	for (auto& t : m_entities.getEntities("tile")) {
		//std::cout << "test" << std::endl;
		window.draw(t->getComponent<CAnimation>().animation.getSprite());
	}

	window.draw(m_player->getComponent<CAnimation>().animation.getSprite());
	auto& enemies = m_entities.getEntities("enemy");

	for (auto& e : enemies) {
		window.draw(e->getComponent<CAnimation>().animation.getSprite());
	}

	//draw grid
	for (auto& g : m_grid) {
		window.draw(g);
	}

	for (auto& c : m_coordiates) {
		window.draw(c);
	}

	window.display();
}

void ScenePlay::onEnd()
{
	//TODO: Implement this
	m_game->quit();
}

void ScenePlay::init(const std::string& levelPath)
{
	this->registerAction(sf::Keyboard::W, "JUMP");
	this->registerAction(sf::Keyboard::A, "LEFT");
	this->registerAction(sf::Keyboard::D, "RIGHT");
	this->registerAction(sf::Keyboard::Escape, "EXIT");
	this->registerAction(sf::Keyboard::P, "PAUSE");

	readConfig(levelPath);

	sSpawnPlayer();
	sEnemySpawner();
	sCreatePixelGrid();
}

void ScenePlay::readConfig(const std::string& levelPath)
{
	std::ifstream fileStream(levelPath);
	if (!fileStream.is_open())
		std::cout << "Failed to open level file!!! path: " << levelPath << std::endl;
	std::string line;
	while (std::getline(fileStream, line)) {
		std::istringstream s(line);
		std::string type;
		s >> type;
		if (type == "Player") {
			s >> m_playerConfig.X >> m_playerConfig.Y;
			s >> m_playerConfig.CW >> m_playerConfig.CH;
			s >> m_playerConfig.SPEED >> m_playerConfig.JUMP;
			s >> m_playerConfig.MAXSPEED;
			s >> m_playerConfig.GRAVITY;
			s >> m_playerConfig.WEAPON;
			std::cout << line << std::endl;
		}
		else if (type == "Tile") {
			//create tile entity
			std::string name;
			float x, y;
			s >> name >> x >> y;

			sf::Vector2f pos((32 * x) - 32, (32 * y) - 32);
			auto tile = m_entities.addEntity("tile");
			auto& animation = m_game->getAssets().getAnimation(name);
			tile->addComponent<CAnimation>(animation, false);
			tile->getComponent<CAnimation>().animation.getSprite().setPosition(pos);
			std::cout << name << " " << pos.x << "," << pos.y << std::endl;
		}
		else if (type == "Dec") {
			//create dec entity
		}
	}
	fileStream.close();
}

void ScenePlay::sSpawnPlayer()
{
	m_player = m_entities.addEntity("player");
	auto& t = m_player->addComponent<CTransform>(Vec2(100, 150), Vec2(5.0f, 5.0f), Vec2(1.0f, 1.0f), 0);

	auto& animation = m_game->getAssets().getAnimation("playerIdle");
	animation.getSprite().setPosition(t.pos.x, t.pos.y);
	m_player->addComponent<CAnimation>(animation, false);
	m_player->addComponent<CBoundingBox>(animation.getSize());
	m_player->addComponent<CState>("idleRight");
	m_player->addComponent<CGravity>(5.8f);
	m_player->addComponent<CInput>();

	std::cout << "Player -> " << m_player->getId() << std::endl;
}

void ScenePlay::sPlayerMovement()
{
	auto& transform = this->m_player->getComponent<CTransform>();
	auto& input = this->m_player->getComponent<CInput>();
	auto& boundingBox = this->m_player->getComponent<CBoundingBox>();

	transform.prevPos = transform.pos;

	bool isOverlapped = boundingBox.preOverlap.x > 0 && boundingBox.preOverlap.y > 0;

	if (input.up) transform.pos.y -= transform.velocity.y;
	//if (input.down) transform.pos.y += transform.velocity.y;
	if (input.left && transform.pos.x - (boundingBox.size.x /2)  > 0) transform.pos.x -= transform.velocity.x;
	if (input.right) transform.pos.x += transform.velocity.x;
	
	std::cout << "overlap -> " << boundingBox.preOverlap.x << std::endl;
	
	float xDirection = transform.pos.x - transform.prevPos.x;
	float yDirection = transform.pos.y - transform.prevPos.y;

	if (isOverlapped) {
		if (xDirection != 0) {
			float xPush = transform.velocity.x + boundingBox.preOverlap.x;
			transform.pos.x += xDirection > 0 ? (-1) * xPush : xPush;
		}
		if (yDirection != 0) {
			float yPush = transform.velocity.y + boundingBox.preOverlap.y;
			transform.pos.y += yDirection > 0 ? (-1) * yPush : yPush;
		}
	}


	auto& sprite = this->m_player->getComponent<CAnimation>().animation.getSprite();
	sprite.setPosition(transform.pos.x, transform.pos.y);
}

void ScenePlay::setAnimation(std::shared_ptr<Entity> entity, const std::string& animationName, bool repeat)
{
	if (entity->getComponent<CAnimation>().animation.getName() == animationName)
		return;
	entity->getComponent<CAnimation>() = CAnimation(m_game->getAssets().getAnimation(animationName), repeat);
}

void ScenePlay::sAnimation()
{
	auto& state = m_player->getComponent<CState>().state;
	auto& animation = m_player->getComponent<CAnimation>();

	if (state == "idleRight") {
		setAnimation(m_player, "playerIdle", true);
		animation.animation.getSprite().setScale(1, 1);
	}
	else if (state == "idleLeft") {
		setAnimation(m_player, "playerIdle", true);
		animation.animation.getSprite().setScale(-1, 1);
	}
	else if (state == "runRight") {
		setAnimation(m_player, "playerRun", true);
		animation.animation.getSprite().setScale(1, 1);
	}
	else if (state == "runLeft") {
		setAnimation(m_player, "playerRun", true);
		animation.animation.getSprite().setScale(-1, 1);
	}
	else if (state == "jump") {
		setAnimation(m_player, "playerJump", true);
	}
}

void ScenePlay::sMovement()
{
	sPlayerMovement();
	//sEnemyMovement();
}

void ScenePlay::sEnemySpawner()
{
	auto koopa = m_entities.addEntity("enemy");
	auto& transform = koopa->addComponent<CTransform>(Vec2(200, 150), Vec2(5.0f, 5.0f), Vec2(0, 0), 0);
	koopa->addComponent<CState>("walk");
	auto& animation = m_game->getAssets().getAnimation("redWalkKoopa");
	auto& cAnimation = koopa->addComponent<CAnimation>(animation, true);
	koopa->addComponent<CBoundingBox>(Vec2(16, 15)); //temporary
	cAnimation.animation.getSprite().setPosition(transform.pos.x, transform.pos.y);	
	transform.prevPos = transform.pos;
	koopa->addComponent<CGravity>(5.8);

}

void ScenePlay::sEnemyMovement()
{
	auto& entities = m_entities.getEntities("enemy");
	for (auto& e : entities) {
		auto& transform = e->getComponent<CTransform>();
		auto& boundingBox = e->getComponent<CBoundingBox>();
		if (transform.pos.x - (boundingBox.size.x / 2) > 0) transform.pos.x -= transform.velocity.x;

		auto& sprite = e->getComponent<CAnimation>().animation.getSprite();
		sprite.setPosition(transform.pos.x, transform.pos.y);
		transform.prevPos = transform.pos;
	}
}

void ScenePlay::sCollision()
{
	auto& entities = m_entities.getEntities();
	for (auto& a : entities) {
		if (a->getTag() == "object")
			continue;
		auto& aT = a->getComponent<CTransform>();
		auto& aB = a->getComponent<CBoundingBox>();
		for (auto& b : entities) {
			if (a->getId() == b->getId())
				continue;
			auto& bT = b->getComponent<CTransform>();
			auto& bB = b->getComponent<CBoundingBox>();
			
			Vec2 distance = { abs(aT.pos.x - bT.pos.x), abs(aT.pos.y - bT.pos.y) };
			float oX = (aB.size.x / 2) + (bB.size.x / 2) - distance.x; //overlap if oX > 0
			float oY = (aB.size.y / 2) + (bB.size.y / 2) - distance.y;
			Vec2 overlap(oX, oY);
			aB.preOverlap = overlap;
		}
	}

}

void ScenePlay::sGravity()
{
	auto& entities = m_entities.getEntities();
	for (auto& e : entities)
	{
		if (!e->hasComponent<CTransform>() || !e->hasComponent<CGravity>())
			continue;
		auto& transform = e->getComponent<CTransform>();
		auto& gravity = e->getComponent<CGravity>();
		transform.pos.y += gravity.gravity;
	}
}

void ScenePlay::sCreatePixelGrid()
{
	int levelWidth = 3584; //read from levelConfig
	int levelHeight = 480; //read from levelConfig, but for now we can just use window size
	int pixelSize = 32;

	for (int x = pixelSize; x <= levelWidth; x += pixelSize) {
		sf::RectangleShape line(sf::Vector2f(1, levelHeight));
		line.setOrigin(sf::Vector2f(0.5f, levelHeight / 2));
		line.setPosition(x, m_game->window().getSize().y / 2);
		line.setFillColor(sf::Color::White);
		m_grid.push_back(line);
	}
	
	for (int y = pixelSize; y <= levelHeight; y += pixelSize) {
		sf::RectangleShape line(sf::Vector2f(levelWidth, 1));
		line.setOrigin(sf::Vector2f(levelWidth/2, 0.5f));
		line.setPosition(levelWidth/2, y);
		line.setFillColor(sf::Color::White);
		m_grid.push_back(line);
	}

	int r = pixelSize / 2;
	for (int y = pixelSize; y <= levelHeight; y += pixelSize) {
		int cY = y / pixelSize;
		for (int x = pixelSize; x <= levelWidth; x += pixelSize) {
			int cX = x / pixelSize;
			sf::Text coordinate;
			coordinate.setFont(m_game->getAssets().getFont("robotRebels"));
			coordinate.setString("(" + std::to_string(cX) + "," + std::to_string(cY) + ")");
			coordinate.setCharacterSize(8);
			sf::FloatRect localBound = coordinate.getLocalBounds();
			coordinate.setOrigin(localBound.width / 2, localBound.height / 2);
			coordinate.setFillColor(sf::Color::White);
			coordinate.setPosition(x - r, y - r);
			m_coordiates.push_back(coordinate);
		}
	}
}

ScenePlay::ScenePlay(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine), m_levelPath(levelPath)
{
	init(levelPath);
}
