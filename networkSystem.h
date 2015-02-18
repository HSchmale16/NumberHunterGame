/** networkSystem.h
* Contains the sf::Packet overloads and struct prototypes for connecting to the
*  game server.
* @author Henry Schmale
* @date November 21, 2014
*/

#ifndef NETWORKSYSTEM_H_INCLUDED
#define NETWORKSYSTEM_H_INCLUDED

#include <string>
#include <SFML/Network.hpp>

namespace network
{
const int SERVER_PORT = 53000;
const sf::IpAddress SERVER_ADDRESS("127.0.0.1");

enum RequestType
{
    NEW_SCORE_RECORD,
    FETCH_HIGHSCORES,
    VERIFY_CLIENT
};

/** \brief struct that contains the highscore list strings that are recieved from server/db
 *	\param tbHeading The heading the table should have
 *	\param names A list of 10 player names delimited by newlines
 *	\param scores A list of 10 player scores delimited by newlines in the same order as the player who got it
 * This struct will hold the data to create a high score table.
 * It is what should be streamed into a packet on a request for highscores for a set level
 */
struct HiScoreList
{
    std::string tbHeading;
    std::string names;
    std::string scores;
};

struct ScoreRecord
{
    RequestType request = NEW_SCORE_RECORD;
    std::string name;
    sf::Int32 level;
    sf::Int32 score;
    sf::Int32 salvage;
    sf::Int32 ast_destroyed;
};


// Overloads for working with the structs
/**< Load the ScoreRecord into sf::Packet For Sending */
sf::Packet &operator <<(sf::Packet& packet, const ScoreRecord& rec)
{
    return packet << static_cast<sf::Int16>(rec.request) << rec.name << rec.level << rec.score
           << rec.salvage << rec.ast_destroyed;
}

/**< Unload Packet containing ScoreRecord into a struct */
sf::Packet &operator >>(sf::Packet &p, ScoreRecord &rec)
{
    return p >> rec.request >> rec.name >> rec.level >> rec.score >> rec.salvage >> rec.ast_destroyed;
}

/**< Loads the hiScoreList into packet for sending */
sf::Packet &operator <<(sf::Packet &p, const HiScoreList &hs)
{
    return p << hs.tbHeading << hs.names << hs.scores;
}

/**< Unloads the hiScoreList from packet */
sf::Packet &operator >>(sf::Packet &p, HiScoreList &hs)
{
    return p >> hs.tbHeading >> hs.names >> hs.scores;
}
}
#endif // NETWORKSYSTEM_H_INCLUDED
