#include "ScenePlay.h"
#include <fstream>
#include <sstream>

void ScenePlay::update(sf::Time elapsedTime)
{
	//std::cout << "CALLS UPDATE FROM SCENE PLAY" << std::endl;
	m_entities.update();
	sAnimation();
	m_player->getComponent<CAnimation>().animation.update();
	auto& enemies = m_entities.getEntities("enemy");
	for (auto& e : enemies)
	{
		e->getComponent<CAnimation>().animation.update();
	}
	//sCollision();
	sMovement(elapsedTime);
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
		else if(action.name() == "GRID")
		{
			m_showGrid = !m_showGrid;
		}
		else if (action.name() == "BOUNDINGBOX") {
			m_showBoundingBox = !m_showBoundingBox;
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

	//bounding box
	if (m_showBoundingBox) {
		for (auto e : m_entities.getEntities())
		{
			if (e->hasComponent<CBoundingBox>())
			{
				auto& box = e->getComponent<CBoundingBox>();
				auto& transform = e->getComponent<CTransform>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x, box.size.y));
				rect.setOrigin(sf::Vector2f(box.size.x / 2, box.size.y / 2));
				rect.setPosition(transform.pos.x, transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color(255, 255, 255, 255));
				rect.setOutlineThickness(1);
				window.draw(rect);
			}
		}
	}

	//draw grid
	if (m_showGrid) {
		for (auto& g : m_grid) {
			window.draw(g);
		}
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
	this->registerAction(sf::Keyboard::G, "GRID");
	this->registerAction(sf::Keyboard::B, "BOUNDINGBOX");


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
			s >> m_playerConfig.ACC;
			s >> m_playerConfig.SPEED >> m_playerConfig.JUMP;
			s >> m_playerConfig.MAXSPEED;
			s >> m_playerConfig.GRAVITY;
			s >> m_playerConfig.WEAPON;
			std::cout << line << std::endl;
			std::cout << "player acc -> " << m_playerConfig.ACC << " x,y vel -> " << m_playerConfig.SPEED << "," << m_playerConfig.JUMP << std::endl;
		}
		else if (type == "Tile") {
			//create tile entity
			std::string name;
			float x, y;
			s >> name >> x >> y;

			auto& animation = m_game->getAssets().getAnimation(name);
			sf::Vector2f pos((m_sceneConfig.pixelSize * x) - animation.getSize().x / 2, (m_sceneConfig.pixelSize * y) - animation.getSize().y / 2);
			auto tile = m_entities.addEntity("tile");
			tile->addComponent<CTransform>(Vec2(pos.x, pos.y), Vec2(0, 0), Vec2(1, 1), 0);
			tile->addComponent<CAnimation>(animation, false);
			tile->getComponent<CAnimation>().animation.getSprite().setPosition(pos);
			tile->addComponent<CBoundingBox>(animation.getSize());
			std::cout << name << " " << animation.getSize().x << "," << animation.getSize().y << std::endl;
		}
		else if (type == "Dec") {
			//create dec entity
		}
		else if (type == "Scene") {
			s >> m_sceneConfig.levelWidth >> m_sceneConfig.levelHeight >> m_sceneConfig.pixelSize;
		}
	}
	fileStream.close();
}

void ScenePlay::sSpawnPlayer()
{
	int pixelSize = m_sceneConfig.pixelSize;
	m_player = m_entities.addEntity("player");

	Vec2 pos = {	//normalize character position so that it's at the middle of grid;
					(m_playerConfig.X * pixelSize) - pixelSize / 2,				//x
					(m_playerConfig.Y * pixelSize) - m_playerConfig.CH / 2		//y
			   };	

	Vec2 vel = { m_playerConfig.SPEED, m_playerConfig.JUMP };

	auto& t = m_player->addComponent<CTransform>(pos, vel, Vec2(1.0f, 1.0f), 0);

	auto& animation = m_game->getAssets().getAnimation("playerIdle");
	animation.getSprite().setPosition(t.pos.x, t.pos.y);
	m_player->addComponent<CAnimation>(animation, false);
	m_player->addComponent<CBoundingBox>(animation.getSize());
	m_player->addComponent<CState>("idleRight");
	m_player->addComponent<CGravity>(m_playerConfig.GRAVITY);
	m_player->addComponent<CInput>();

	std::cout << "Player -> " << m_player->getId() << std::endl;
}

void ScenePlay::sPlayerMovement(sf::Time elapsedTime)
{
	auto& transform = this->m_player->getComponent<CTransform>();
	auto& input = this->m_player->getComponent<CInput>();
	auto& boundingBox = this->m_player->getComponent<CBoundingBox>();
	auto& gravity = m_player->getComponent<CGravity>();

	Vec2 acceleration = { 0,  0};

	if (!gravity.isOnGround) acceleration.y = gravity.gravity;

	if (input.up && gravity.isOnGround) acceleration.y -= m_playerConfig.JUMP;
	if (input.left && transform.pos.x - (boundingBox.size.x/2)  > 0) acceleration.x += m_playerConfig.ACC * (-1);
	if (input.right) acceleration.x += m_playerConfig.ACC;

	acceleration.x += transform.velocity.x * -0.3f; //friction has to be minus
	transform.velocity += acceleration + (acceleration * 0.5f);
	
	gravity.isOnGround = false;

	//test param
	Vec2 contactPoint = { 0,0 };
	Vec2 contactNormal = { 0,0 };
	float contactTime = 0;
	std::vector<std::pair<std::shared_ptr<Entity>,float>> collideOrder;
	for (auto& e : m_entities.getEntities()) {
		if (!e->hasComponent<CBoundingBox>())
			continue;
		if (e->getId() == m_player->getId())
			continue;
		if (m_collisionManager.dynamicRectVsRect(m_player, e, contactPoint, contactNormal, contactTime, elapsedTime.asSeconds())) {
			collideOrder.push_back({ e, contactTime });
		}
	}

	//Sort collided objects
	std::sort(collideOrder.begin(), collideOrder.end(), [](const std::pair<std::shared_ptr<Entity>,float>& a, const std::pair<std::shared_ptr<Entity>,float>& b)
	{
		return a.second < b.second;
	});

	for (auto& e : collideOrder) {
		if (m_collisionManager.resolveDynamicRectVsRect(m_player, e.first, elapsedTime.asSeconds())){
			//std::cout << "setelah: " << gravity.isOnGround << " vel -> " << transform.velocity.print() << " cp -> " << contactNormal.print() << std::endl;
		}
	}

	Vec2 predictedPos = transform.pos + transform.velocity * elapsedTime.asSeconds();

	transform.pos = predictedPos;

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

void ScenePlay::sMovement(sf::Time elapsedTime)
{
	sPlayerMovement(elapsedTime);
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

const bool ScenePlay::sCheckCollision(std::shared_ptr<Entity> actor, std::shared_ptr<Entity> other, Vec2& predictedPos, Vec2& _overlap) const
{
	auto& aB = actor->getComponent<CBoundingBox>();

	auto& bT = other->getComponent<CTransform>();
	auto& bB = other->getComponent<CBoundingBox>();

	Vec2 distance = { abs(predictedPos.x - bT.pos.x), abs(predictedPos.y - bT.pos.y) };
	float oX = (aB.size.x / 2) + (bB.size.x / 2) - distance.x; //overlap if oX > 0
	float oY = (aB.size.y / 2) + (bB.size.y / 2) - distance.y;
	_overlap = { oX, oY };

	return _overlap.x > 0 && _overlap.y > 0;
}

void ScenePlay::sCollision()
{
	auto& entities = m_entities.getEntities();
	for (auto& a : entities) {
		if (a->getTag() == "tile")
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
			if (overlap.x > 0 && overlap.y > 0)
				break;
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
	int levelWidth = m_sceneConfig.levelWidth; //read from levelConfig
	int levelHeight = m_sceneConfig.levelHeight; //read from levelConfig, but for now we can just use window size
	int pixelSize = m_sceneConfig.pixelSize;

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
	: Scene(gameEngine)
{
	init(levelPath);
}
