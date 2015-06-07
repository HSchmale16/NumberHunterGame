/** LaserHandler Implementation
 * @author Henry Schmale
 * @date October 14, 2014
 * @file src/LaserHandler.cpp
 */

#include "../include/LaserHandler.h"
#include "../FilePaths.h"

// declare globals used for scoring
extern int PTS_GOOD_SALVAGE;      //!< pts given for collecting good salvage
extern int PTS_BAD_SALVAGE;       //!< pts lost for collecting bad salvage
extern int PTS_DESTROY_SALVAGE;   //!< pts lost for destroying salvage(any)
extern int PTS_HIT_ASTEROID;      //!< pts lost for hitting an asteroid
extern int PTS_DESTROY_ASTEROID;  //!< pts gained for destroying an asteroid by shooting it
extern sf::SoundBuffer explosionSND; //!< Buff for explosion sound

LaserHandler::LaserHandler() {
    //ctor
    m_MaxLasers = 5;
    m_salvageDest = 0;
    m_asteroidDest = 0;
    for(int index = 0; index < 10; index++)	// populate vector
        m_vecLaser.push_back(new Laser());

    // Sound
    if(!m_sLaserSndBuff.loadFromFile(LASER_SOUND)) {
        hjs::logToConsole("Couldn't Load Laser Sound");
    }
    // create a sound buffer for each laser
    m_LaserSnds = new sf::Sound[m_MaxLasers];
    for(int i = 0; i < m_MaxLasers; i++) {
        m_LaserSnds[i].setBuffer(m_sLaserSndBuff);
        m_LaserSnds[i].setVolume(50.0);
    }
    m_blewUpAster.setBuffer(explosionSND);
    m_blewUpSalv.setBuffer(explosionSND);
}

LaserHandler::~LaserHandler() {
    //dtor
    delete[] m_LaserSnds;
}

int LaserHandler::handleEvents(Player *p, Salvage *s, Asteroids *a, Enemy *e) {
    int nPoints = 0;
    m_salvageDest = 0;
    m_asteroidDest = 0;
    // Check if a laser should be activated
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (m_LaserLimiter > 80)) {	// check if shoot key is down to add another Laser Instance
        // find an inactive index of laser
        for(unsigned int index = 0; index < m_vecLaser.size(); index++) {
            if(!m_vecLaser[index]->getActive()) {
                m_LaserSnds[index].play();
                m_vecLaser[index]->Activate(p->getXCoord() + (p->getSideLength() / 2.0),
                                            p->getYCoord());
                m_LaserLimiter = 0;
                break;
            }
        }
    } else {
        m_LaserLimiter++;
    }

    // move the lasers
    for(unsigned int index = 0; index < m_vecLaser.size(); index++) {
        m_vecLaser[index]->Move();
    }

    // handle HitTests for salvage
    for(int sI = 0; sI < s->getCount(); sI++) {
        for(int lasI = 0; lasI < m_MaxLasers; lasI++) {
            if((m_vecLaser[lasI]->getActive())
                    && (s->hitTestShot(sI, *m_vecLaser[lasI]))) {
                m_blewUpSalv.play();            // Play blew up salvage sound
                s->ReInit(sI);                  // ReInit that instance of salvage
                m_vecLaser[lasI]->DeActivate(); // hide the laser index
                nPoints += PTS_BAD_SALVAGE;	    // That's bad lose points for destroying salvage
                m_salvageDest++;                // salvage killed so increment the count for that
                break;	// break out of hitTests for that particular instance of salvage, because that instance is gone
            }
        }
    }

    // handle HitTests for Asteroids
    for(int aI = 0; aI < a->getCount(); aI++) {
        for(int lasI = 0; lasI < m_MaxLasers; lasI++) {
            if((m_vecLaser[lasI]->getActive())
                    &&(a->hitTestLaser(aI, *m_vecLaser[lasI]))) {
                m_blewUpAster.play();
                nPoints += PTS_DESTROY_ASTEROID; // destroying asteroids is good so give points
                m_asteroidDest++;                // increment asteroids killed
                a->ReInit(aI);
                m_vecLaser[lasI]->DeActivate();
                break;
            }
        }
    }

    // hittest enemies
    for(uint64_t eI = 0; eI < e->getEnemyCount(); eI++) {
        for(size_t lasI = 0; lasI < m_vecLaser.size(); lasI++) {
            if(m_vecLaser[lasI]->getActive()
                && (e->hitTestLaser((uint64_t)eI, *m_vecLaser[lasI]))){
                //!\todo Finish Enemy hitting player laser logic
                e->ReInit(eI);
                m_vecLaser[lasI]->DeActivate();
            }
        }
    }
    // return points gained
    return nPoints;
}

int LaserHandler::getAsteroidsDestroyedThisIter() {
    return m_asteroidDest;
}

int LaserHandler::getSalvageDestroyedThisIter() {
    return m_salvageDest;
}

void LaserHandler::draw(sf::RenderTarget &target, sf::RenderStates states)const {
    for(unsigned int index = 0; index < m_vecLaser.size(); index++) {
        target.draw(*m_vecLaser[index]);
    }
}
