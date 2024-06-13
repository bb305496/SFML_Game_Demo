#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
    this->skills.push_back(Skill(SKILLS::HEALTH));
    this->skills.push_back(Skill(SKILLS::ATTACK));
    this->skills.push_back(Skill(SKILLS::ACCURACY));
    this->skills.push_back(Skill(SKILLS::ENDURANCE));
}

SkillComponent::~SkillComponent()
{

}

const int SkillComponent::getSkill(const int skill) const
{
    if (skills.empty() || skill < 0 || skill >= this->skills.size())
        throw("ERROR::SKILLCOMPONENT:: key is not exisiting");
    else
        return this->skills[skill].getLevel();
}

const void SkillComponent::gainExp(const int skill, const int exp)
{
    if (skills.empty() || skill < 0 || skill >= this->skills.size())
        throw("ERROR::SKILLCOMPONENT:: key is not exisiting");
    else
    {
        this->skills[skill].gainExp(exp);
    }
}


