#include "stdafx.h"
#include "Rat1.h"

void Rat1::initVariables()
{

}

void Rat1::initAnimations()
{

    this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 3, 0, 200, 200);
    this->animationComponent->addAnimation("WALK_LEFT", 18.f, 0, 1, 3, 1, 200, 200);
    this->animationComponent->addAnimation("WALK_RIGHT", 18.f, 0, 2, 3, 2, 200, 200);
    //this->animationComponent->addAnimation("WALK_UP", 70.f, 0, 4, 3, 4, 75, 75);
    //this->animationComponent->addAnimation("ATTACK", 10.f, 0, 4, 0, 4, 300, 150);
}

void Rat1::initAI()
{

}

void Rat1::initGUI()
{
    this->hpBar.setFillColor(sf::Color::Red);
    this->hpBar.setSize(sf::Vector2f(10.f, 7.f));
    this->hpBar.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 10.f);
}


Rat1::Rat1(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player)
    : Enemy(enemy_spawner_tile)
{
    this->initVariables();
    this->initGUI();

    this->createHitboxComponent(this->sprite, 10.f, 5.f, 70.f, 100.f);
    //Changing speed/acceleration/deceleration
    this->createMovementComponent(100.f, 1600.f, 1000.f);
    this->createAnimationComponent(texture_sheet);
    //Gain exp change
    this->createAttributeComponent(100);

    //Optimize
    this->attributeComponent->vitality = 10;
    this->attributeComponent->strength = 5;

    this->generateAttributes(this->attributeComponent->level);
    this->attributeComponent->updateStats(true);

    this->setPosition(x, y);
    this->initAnimations();

    this->follow = new AIFollow(*this, player);
}

Rat1::~Rat1()
{
    delete this->follow;
}

void Rat1::updateAnimation(const float& dtime)
{
    if (this->movementComponent->getState(IDLE))
    {
        //It will help later to center attack texture
        //this->sprite.setOrigin(0.f,0.f);
        this->sprite.setScale(0.5f, 0.5f);
        this->animationComponent->play("IDLE", dtime);
    }
    else if (this->movementComponent->getState(MOVING_RIGHT))
    {
        this->sprite.setScale(0.5f, 0.5f);
        this->animationComponent->play("WALK_RIGHT", dtime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocuty());
    }
    else if (this->movementComponent->getState(MOVING_LEFT))
    {
        this->sprite.setScale(0.5f, 0.5f);
        this->animationComponent->play("WALK_LEFT", dtime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocuty());
    }
    else if (this->movementComponent->getState(MOVING_UP))
    {
        this->sprite.setScale(0.5f, 0.5f);
        this->animationComponent->play("WALK_RIGHT", dtime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocuty());
    }
    else if (this->movementComponent->getState(MOVING_DOWN))
    {
        this->sprite.setScale(0.5f, 0.5f);
        this->animationComponent->play("WALK_RIGHT", dtime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocuty());
    }

    if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
    {
        this->sprite.setColor(sf::Color::Red);
    }
    else
        this->sprite.setColor(sf::Color::White);
}

void Rat1::update(const float& dtime, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
    Enemy::update(dtime, mouse_pos_view, view);

    this->movementComponent->update(dtime);

    this->hpBar.setSize(sf::Vector2f(100.f * (static_cast<float>(this->attributeComponent->hp) / static_cast<float>(this->attributeComponent->hpMax)) / 1.4f, 10.f));
    this->hpBar.setPosition(this->sprite.getPosition().x + 4.f, this->sprite.getPosition().y - 3.f);

    //this->updateAttack();

    this->updateAnimation(dtime);

    this->hitboxComponent->update();

    this->follow->update(dtime);
}

void Rat1::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_position);

        target.draw(this->sprite, shader);
    }
    else
    {
        target.draw(this->sprite);
    }

    target.draw(this->hpBar);

    if (show_hitbox)
        this->hitboxComponent->render(target);
}