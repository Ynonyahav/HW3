#include "HealthPoints.h"

using namespace std;

// C'tor of HealthPoints class
HealthPoints::HealthPoints(int healthPoints)
{
    if(healthPoints <= 0)
    {
        throw InvalidArgument();
    }
    m_HP = healthPoints;
    m_maxHP = healthPoints;
}

//---------------------------------Member Functions---------------------------------

// operator+=: (hp += 50)
HealthPoints& HealthPoints::operator+=(int addition)
{
    if(m_HP + addition >= m_maxHP)
    {
        m_HP = m_maxHP;
    }
    else if(m_HP + addition <= 0)
    {
        m_HP = 0;
    }
    else
    {
        m_HP += addition;
    }
    return *this;
}
// operator-=: (hp -= 50)
HealthPoints& HealthPoints::operator-=(int subtraction)
{
    *this += (-subtraction);
    return *this;
}
// getHealthPoints: (hp + 50)
HealthPoints HealthPoints::operator+(int addition) const
{
    HealthPoints newHP(*this);
    newHP += addition;
    return newHP;
}
// getHealthPoints: (hp - 50)
HealthPoints HealthPoints::operator-(int subtraction) const
{
    HealthPoints newHP(*this);
    newHP -= subtraction;
    return newHP;
}

//---------------------------------Friend Member Functions---------------------------------

// operator<<: (std::cout << hp)
std::ostream& operator<<(std::ostream& os, const HealthPoints& hp)
{
    os << hp.m_HP << "(" << hp.m_maxHP << ")";
    return os;
}
// operator<=: (hp1 <= hp2)
bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return hp1.m_HP <= hp2.m_HP;
}

//---------------------------Non-Friend Non-Member Functions--------------------------------

// operator>=: (hp1 >= hp2)
bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return (hp2 <= hp1) ;
}
// operator==: (hp1 == hp2) || (50 == hp2) || (hp1 == 50)
bool operator==(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return (hp1 <= hp2 && hp1 >= hp2);
}
// operator!=: (hp1 != hp2) || (50 != hp2) || (hp1 != 50)
bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return !(hp1 == hp2);
}

bool operator>(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return !(hp1 <= hp2);
}
bool operator<(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return (hp1 <= hp2 && hp1 != hp2);
}

HealthPoints operator+(int addition, const HealthPoints& hp2)
{
    HealthPoints newHp(hp2);
    newHp += addition;
    return newHp;
}





