# Architect-Engine
This engine is aiming to contain a rich architect object library. User/Designer can directly use these objects by calling the function. Meanwhile, besides the individual object such as chair, the engine also aiming to build the building by calling the function. For example, DrawClassroom(double width, double length, double height, int capacity)


# How to run engine
clone repo  <br/>
cmake .    // don't forget "dot ( . ) "  <br/>
make   <br/>
./MainEngine  <br/>

* Note: <br/>
(1) only call "cmake ." after first time clone. After any modification of the code and want to run the program. do: "
make <br/>
./MainEngine"   <br/> 

(2) If want to use different function, call specific function in Render_Piect() in "MainEngine.cxx"


# Things need to improve
(1) DrawClassroom is not fully work, the function to calculate the interval would cause drawing of chair with wrong position <br/>
(2) ReadOBJ is tricky, the farest that I made is to make both read obj file and my own object shown in the same screen. However, I still don't figure our how to modify, resize, and re-locate read obj <br/>
(3) The more object the better
