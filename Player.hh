#ifndef Player_hh
#define Player_hh


#include "Info.hh"
#include "Action.hh"
#include "Random.hh"
#include "Registry.hh"
#include <iostream>

/***
 * Abstract base class for players.
 * *
 * This class uses multiple inheritance from Info and Action,
 * so that their public operations can been used from within Player.
 *
 * In order to create new players, inherit from this class and register them.
 * See for example AINull.cc and AIDemo.cc.
 */
class Player : public Info, public Random_generator, public Action {

public:

  /**
   * Identifier of my player.
   */
  int me () const;
  
  //////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////  

  /**
   * Play intelligence. Will be overwritten, thus declared virtual.
   */
  virtual void play () {
  };
  
  /**
   * Empty constructor.
   */
  Player () { }
  
private: 

  friend class Game;
  friend class SecGame;

  int me_;

  inline void reset (const Info& info) {
    *static_cast<Action*>(this) = Action();
    *static_cast<State*>(this) = (State) info;
    //    forget();
  }

  void reset (ifstream& is);
};


inline int Player::me () const {
  return me_;
};

#endif
