-- basic datas
w,h = __getMapSize();
x,y = __getPosition();
angle = __getAngle();
if x == -1 and y == -1 then return 1 end

-- if we're in danger, moving out is a priority
b = __amExposed()
if b == 1 then
   safe_x,safe_y = __safePosition()

   if safe_x ~= -1 and safe_y ~= -1 then
      __simpleMoveTo(safe_x, safe_y)
      return 0
   else
      -- let's die with class
      __setDirection(0, 0)
      __putBomb()
      return 0
   end
end

b = __brickAround()
if b == 1 then
   -- destroy brick
   __putBomb()
   __setDirection(0, 0)
   return 0
else
   -- go to a brick (Safe is optional)
   to_x,to_y = __toBrickSafe()
   if to_x ~= -1 and to_y ~= -1 then
      __simpleMoveTo(to_x, to_y)
      return 0
   end
end

-- if everything goes wrong, we stop the boat
-- but since we don't know what to do else, let's put a bomb
__putBomb()
__setDirection(0, 0)
