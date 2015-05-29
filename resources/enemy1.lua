-- enemy.lua
-- Henry J Schmale
-- May 29, 2015
-- Determines the behavior for enemies in Number Hunter Game
-- This script makes the enemy enter the stage, and come down about
-- halfway, and move back and forth shooting at the player. Each enemy has
-- it's own Lua VM.

shotLimiter = 45
shotTimer   =  0
xPos        =  0
yPos        =  0
xSpeed      =  1
ySpeed      =  1

-- This function is called once on the loading of the enemy. This
-- function should determine where to place the enemy. It should
-- also set your globals to their initial values. Returns 0 on
-- success.
init = function()
    math.randomseed(os.time())
    xPos = math.random() * 325 + 25
    yPos = -20
    return 0
end

-- This function determines if this enemy can shoot or not.
-- It returns true if it should shoot this iteration. It is called at the
-- same rate that moveEnemy is called.
shoot = function()
    shotTimer = shotTimer + 1
    if shotTimer > shotLimiter then
        shotTimer = 0
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
    if yPos < 200 then
        yPos = yPos + 1
        return 0
    end
    if xPos < 50 or xPos > 350 then
        xSpeed = xSpeed * -1  -- invert travel direction
    end
    xPos = xPos + xSpeed;
    return 0
end