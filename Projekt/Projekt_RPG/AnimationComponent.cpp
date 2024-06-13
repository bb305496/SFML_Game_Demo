#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

const bool& AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

void AnimationComponent::addAnimation(const std::string key, 
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer,
		start_frame_x, start_frame_y, frames_x, start_frame_y, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float& dtime, const bool priority)
{

	if (this->priorityAnimation)
	{
		if (this->priorityAnimation = this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == nullptr)
					this->animations[key]->play(dtime);
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			if (this->animations[key]->play(dtime))
			{
				this->priorityAnimation = nullptr;
			}
		}
	}
	else
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}
	{
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == nullptr)
				this->animations[key]->play(dtime);
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dtime);
	}

	return this->animations[key]->isDone();
	
}

const bool& AnimationComponent::play(const std::string key, const float& dtime, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation = this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == nullptr)
					this->animations[key]->play(dtime);
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			if (this->animations[key]->play(dtime, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = nullptr;
			}
			
		}
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == nullptr)
				this->animations[key]->play(dtime);
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dtime, abs(modifier / modifier_max));
	}

	return this->animations[key]->isDone();
}
