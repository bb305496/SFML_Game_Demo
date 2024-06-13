#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
    this->initAttack = false;
	this->attacking = false;
    this->weapon = new Sword(1, 3, 6, 180, 20, "Resources/Images/Sprites/Weapons/W1.png");
    //this->weapon->generate(1, 1);

    this->keyTime = 0.f;
    this->keyTimeMax = 2.f;

    this->damageTimerMax = 500;
}

void Player::initComponents()
{

}

void Player::initAnimations()
{

    this->animationComponent->addAnimation("IDLE", 18.f, 0, 0, 15, 0, 150, 150);
    this->animationComponent->addAnimation("WALK_RIGHT", 18.f, 0, 1, 8, 1, 150, 150);
    this->animationComponent->addAnimation("WALK_LEFT", 18.f, 0, 2, 8, 2, 150, 150);
    this->animationComponent->addAnimation("WALK_UP", 70.f, 0, 3, 5, 3, 150, 150);
    //this->animationComponent->addAnimation("ATTACK", 10.f, 0, 4, 0, 4, 300, 150);
}

void Player::initInventory()
{
    this->inventory = new Inventory(100);
}


Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 50.f, 50.f, 50.f, 100.f);
	//Changing speed/acceleration/deceleration
	this->createMovementComponent(150.f, 1300.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent(1);
    this->createSkillComponent();

    this->setPosition(x, y);
    this->initAnimations();

    this->initInventory();
}

Player::~Player()
{
    delete this->inventory;
    delete this->weapon;
}

AttributeComponent* Player::getAttributeComponent()
{
    return this->attributeComponent;;
}

Weapon* Player::getWeapon() const
{
    return this->weapon;
}

const bool Player::canTakeDamage()
{
    if (this->keyTime >= this->keyTimeMax)
    {
        this->keyTime = 0.f;
        return true;
    }
    return false;
}

void Player::updateKeyTime(const float& dtime)
{
    if (this->keyTime < this->keyTimeMax)
    {
        this->keyTime += 10.f * dtime;
    }
}

const std::string Player::toStringCharacterTab() const
{
    std::stringstream ss;

    ss << "   Player \n    stats: \n"
        << "Level: " << this->attributeComponent->level << "\n"
        << "HP: " << this->attributeComponent->hpMax << "\n"
        << "Dmg: " << this->attributeComponent->damageMax << "\n"
        << "Accuracy " << this->attributeComponent->accuracy << "\n"
        << "Defence: " << this->attributeComponent->defence << "\n"
        << "Lucky: " << this->attributeComponent->luck << "\n\n"

        << "  Weapon \n    stats: \n"
        << "Level: " << this->weapon->getLevel() << "\n"
        << "Type: " << this->weapon->getType() << "\n"
        << "Value: " << this->weapon->getValue() << "\n"
        << "Range: " << this->weapon->getRanged() << "\n"
        << "Dmg: " <<  this->weapon->getDamageMin()
        << "~" << this->weapon->getDamageMax();


    return ss.str();
}

const bool& Player::getInitAttack() const
{
    return this->initAttack;
}

const bool Player::getDamageTimer()
{
    if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
    {
        this->damageTimer.restart();
        return true;
    }

    return false;
}

const unsigned Player::getDamage() const
{
    return rand() % ((this->attributeComponent->damageMax + this->weapon->getDamageMax())
        - (this->attributeComponent->damageMin + this->weapon->getDamageMin()) + 1)
        + (this->attributeComponent->damageMin + this->weapon->getDamageMin());
}

bool Player::isDead() const
{
    return this->attributeComponent->hp <= 0;
}

void Player::resetHealth()
{
    this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::setInitAttack(const bool initAttack)
{
    this->initAttack = initAttack;
}


void Player::loseHP(const int hp)
{
    this->attributeComponent->loseHP(hp);

}

void Player::gainHP(const int hp)
{
    this->attributeComponent->gainHP(hp);

}

void Player::loseEXP(const int exp)
{
    this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
{
    this->attributeComponent->gainExp(exp);
}

void Player::updateAnimation(const float& dtime)
{
	if (this->attacking)
	{

	}
	if (this->movementComponent->getState(IDLE))
	{
		//It will help later to center attack texture
		//this->sprite.setOrigin(0.f,0.f);
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("IDLE", dtime);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("WALK_RIGHT", dtime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocuty());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("WALK_LEFT", dtime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocuty());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("WALK_RIGHT", dtime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocuty());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("WALK_RIGHT", dtime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocuty());
	}
}

void Player::setPosition(const float x, const float y)
{
    if (this->hitboxComponent)
        this->hitboxComponent->setPosition(x, y);
    else
        this->sprite.setPosition(x, y);
}

void Player::move(const float dir_x, const float dir_y, const float& dtime)
{
    if (this->movementComponent)
        this->movementComponent->move(dir_x, dir_y, dtime);  //Sets velocity

    if (this->skillComponent)
    {
        this->skillComponent->gainExp(SKILLS::ENDURANCE, 10);
    }
}

void Player::stopVelocity()
{
    if (this->movementComponent)
        this->movementComponent->stopVelocity();
}

void Player::stopVelocityX()
{
    if (this->movementComponent)
        this->movementComponent->stopVelocityX();
}

void Player::stopVelocityY()
{
    if (this->movementComponent)
        this->movementComponent->stopVelocityY();
}

void Player::update(const float& dtime, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
    //std::cout << this->attributeComponent->debugPrint() << "\n";
    this->updateKeyTime(dtime);

	this->movementComponent->update(dtime);

	this->updateAnimation(dtime);

	this->hitboxComponent->update();

    this->weapon->update(mouse_pos_view, this->getCenter());

}

void Player::render(sf::RenderTarget& target,sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_position);

        target.draw(this->sprite, shader);

        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_position);
        this->weapon->render(target, shader);
        
    }
    else
    {
        target.draw(this->sprite);
        this->weapon->render(target);
    }

    if(show_hitbox)
        this->hitboxComponent->render(target);
}
