#ifndef character_hpp_
#define character_hpp_

class Character {
public:
    virtual void act() = 0;
    virtual bool is_alive() = 0;
    virtual ~Character() { };
};

#endif