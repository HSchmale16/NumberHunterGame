-- enemy.lua
-- Henry J Schmale
-- May 29, 2015
-- Determines the behavior for enemies in Number Hunter Game
-- This script makes the enemy enter the stage, and come down about
-- halfway, and move back and forth shooting at the player. Each enemy has
-- it's own Lua VM.

-- Set up random number generator. This is a nasty hack that abuses
-- the random number generator and time to get a pseudo random number
-- for multiple lua instances at the same time.
math.randomseed(math.random(os.time()) * os.time())

-- Do any initial setup here
shotLimiter = 45
shotTimer   = 0
xSpeed      = 1
ySpeed      = 1
yBound      = 300 * math.random()
bspeed      = 0
-- Variables that the host program accesses
xPos        = 0   -- current x position of this enemy
yPos        = 0   -- current y position of this enemy
bullet_dx   = 0   -- bullet x speed
bullet_dy   = 0   -- bullet y speed. positive goes down on screen
-- Variables that the host program gives this script
player_x    = 0   -- player x position last iteration
player_y    = 0   -- player y position last iteration

-- This function is called once on the loading of the enemy. This
-- function should determine where to place the enemy. It should
-- also set your globals to their initial values. Returns 0 on
-- success.
init = function()
    xPos   = math.random() * 325 + 25
    yPos   = -1 * math.floor(math.random() * 100)
    xSpeed = math.random() * 2 + .02
    ySpeed = math.random() + .25
    bspeed = 2
    return 0
end

-- This function determines if this enemy can shoot or not.
-- It returns true if it should shoot this iteration. It is called at the
-- same rate that moveEnemy is called. It also needs to set bullet_dx and
-- bullet_dy if it returns true
shoot = function()
    if shotTimer > shotLimiter then
        shotTimer = 0 -- reset shot timer
        angle = math.atan(player_y - yPos, player_x - xPos)
        bullet_dx = math.cos(angle) * bspeed
        bullet_dy = math.sin(angle) * bspeed
        return true;
    end
    return false
end

-- This function represents one movement iteration. It manipulates global
-- variables to determine the current position of the enemy. It is called
-- about 30 times per second roughly. It should update xPos and yPos to the
-- new position and return 0 to the caller on success, returning any other
-- value indicates failure.
function moveEnemy()
    if yPos < yBound then
        yPos = yPos + 1
        return 0
    end
    shotTimer = shotTimer + 1
    if xPos < 20 or xPos > 350 then
        xSpeed = xSpeed * -1
    end
    xPos = xPos + xSpeed
    return 0
end