#ifndef EX3_HEALTH_POINTS_H
#define EX3_HEALTH_POINTS_H 

#include <iostream>
using std::ostream;

/*
 *  HealthPoints:
 *  This class represents the health points object belonging to a player in the game
*/
struct HealthPoints {

public:
    //--------------------------Static Mweber Variable--------------------------------
    static const int DEFAULT_HP = 100;
    //----------------------------------Methods---------------------------------------
    /**
    * C'tor of HealthPoints class
    * @param healthPoints - the health points of the player
    * @throw InvalidArgument - if the health points are not positive
    * if healthPoints is not given, the default health points will be 100
    * @return
    *     - a new HealthPoints object 
    */
    HealthPoints(int healthPoints = DEFAULT_HP);
    /*
    *  copy c'tor && assignment operator && d'tor - use the default implementation
    */
    ~HealthPoints() = default;
    HealthPoints(const HealthPoints&) = default;
    HealthPoints& operator=(const HealthPoints&) = default;

    //---------------------------------Member Functions---------------------------------
    /**
     * operator+=: (hp1 += 50)
     * @param healthPoints - the number of points to add.
     * @return  
    *       a reference to the current updated HealthPoints object.
    */
    HealthPoints& operator+=(int addition);
    /**
     * operator-=: (hp1 -= 50)
     * @param subtraction - the number of points to reduced.
     * @return  
    *       a reference to the current updated HealthPoints object.
    */
    HealthPoints& operator-=(int subtraction);

    //---------------------------------friend functions---------------------------------

    /**
     * operator<=: (hp1 <= hp2)
     * @param hp1 - the first HealthPoints object
     * @param hp2 - the second HealthPoints object
     * @return
     *     true if hp1 is less then or equal to hp2, false otherwise
     */
    friend bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2);
    /**
     * operator<<: (std::cout << hp)
     * @param os - the output stream
     * @param hp - the HealthPoints object
     * @return
     *     the output stream
     */
    friend ostream& operator<<(ostream& os, const HealthPoints& hp);

    //----------------------------------Exception Class---------------------------------
    /**
     *  InvalidArgument:
     *  This class represents an exception that is thrown when the health points are not positive
     */ 
    class InvalidArgument {};

private:
    // The health points of the player and the maximum health points
    int m_HP;
    int m_maxHP;
};

//---------------------------Non-Friend Non-Member Functions-----------------------------
/**
 * operator==: (hp1 == hp2) || (50 == hp2) || (hp1 == 50)
 * @param hp1 - the first HealthPoints object
 * @param hp2 - the second HealthPoints object
 * @return
 *     true if hp1 is equal to hp2, false otherwise
 */
bool operator==(const HealthPoints& hp1, const HealthPoints& hp2);
/**
 * operator!=: (hp1 != hp2)
 * @param hp1 - the first HealthPoints object
 * @param hp2 - the second HealthPoints object
 * @return
 *     true if hp1 is not equal to hp2, false otherwise
 */
bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2);
/**
 * operator>=: (hp1 >= hp2)
 * @param hp1 - the first HealthPoints object
 * @param hp2 - the second HealthPoints object
 * @return
 *     true if hp1 is greater than or equal to hp2, false otherwise
 */
bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);
/**
 * operator<: (hp1 < hp2)
 * @param hp1 - the first HealthPoints object
 * @param hp2 - the second HealthPoints object
 * @return
 *     true if hp1 is less than hp2, false otherwise
 */
bool operator<(const HealthPoints& hp1, const HealthPoints& hp2);
/**
 * operator>: (hp1 > hp2)
 * @param hp1 - the first HealthPoints object
 * @param hp2 - the second HealthPoints object
 * @return
 *     true if hp1 is greater than hp2, false otherwise
 */
bool operator>(const HealthPoints& hp1, const HealthPoints& hp2);

/**
 * operator+: (hp1 + hp2)
 * @param hp1 - the first HealthPoints object
 * @param hp2 - the second HealthPoints object
 * @return
 *     a new HealthPoints object with the sum of hp1 and hp2
 */
HealthPoints operator+(const HealthPoints& hp1, const HealthPoints& hp2);
/**
 * operator-: (hp1 - hp2)
 * @param hp1 - the first HealthPoints object
 * @param hp2 - the second HealthPoints object
 * @return
 *     a new HealthPoints object with the subtraction of hp2 from hp1
 */
HealthPoints operator-(const HealthPoints& hp1, const HealthPoints& hp2);

#endif /* EX3_HEALTH_POINTS_H */ 