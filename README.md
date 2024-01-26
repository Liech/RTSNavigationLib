# RTSNavigationLib

Library that tries to provide tools tackling the fundamental problem of the RTS genre:

* How should this unit individually move

Tackling Formation, guide units to formation places, navigation and moving in a formation along the planned path.

# Implementation State

- [x] Formation Shape Creation
- [x] Usher
- [x] Flocking
- [ ] Pathfinding
  - [x] Distance Grid (Dijkstra & Eikonal)
  - [ ] Flow Field
  - [ ] Portals
  - [ ] Inter Portal Navigation
  - [ ] Line Of Sight
  - [ ] Continous Crowd

# Formation Forming

In this example a simple Rectangle Formation is created and used for some units. The places are the untransformed location where the units should be.

The [Usher](https://en.wikipedia.org/wiki/Usher_(occupation)) generates tickets assigning each unit a location.

In a real scenario the places are transformed after generation to the real location.

```
    std::string formationDescription = R"""(
      {
        "OwnInterfacePoint"                : 0,  
        "ParentInterfacePoint"             : 0, 
        "OverwriteWidthWithInterfaceWidth" : false, 
        "RotateWithInterface"              : false, 
        "Rotation"                         : 0, 
        "UnitCategory"                     : 0, 
        "UnitDistributionWeight"           : 1,
        "Children"                         : {},

        "Shape" : {
          "Type" : "Rectangle",
          "Size" : [1,1],
          "Scaling" : "Isotropic"
        }
      }
    )""";
    auto formation = RTSPathingLib::Formation();
    formation.fromJson(nlohmann::json::parse(formationDescription));

    std::vector<RTSPathingLib::Body> units;

    units.push_back(RTSPathingLib::Body(glm::dvec2(4, 6), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(-3, 5), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(3, 2), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(5, 3), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(3, 5), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(2, 3), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(0, 1), 0, 1));

    units.push_back(RTSPathingLib::Body(glm::dvec2(-3, -2), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(-2, 4), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(2, -5), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(-3, -5), 0, 1));

    auto places = RTSPathingLib::FormationCalculator(formation, units).calculate();

    std::vector<size_t> tickets = RTSPathingLib::Usher::assignPlaces(units, places);
```

* Units are Green Dots.
* Places are Gray.
* The Tickets are Yellow.

![image](https://github.com/Liech/RTSPathingLib/blob/main/Documentation/Usher.png)

# Complex Formation Generation

A Complex Example for a Formation with different Unit Sizes.

Here is an example that may justify this Formation:
 * Red Units are in the center to be protected from aggressive Forces. Archers and a few Big Catapults.
 * Green Units are the Protectors. Heavy armored Paladins.
 * Blue Units are Horsemen / Zerglings. Melee units that are fast. They swarm out protected by the heavy fire of the archers.

![image](https://github.com/Liech/RTSPathingLib/blob/main/Documentation/PraiseTheSunFormation.png)

See "Formation/PraiseTheSun" Test if you are interested how its done.

# Recreational Goals

* Get more confidence with testing
  * Try TDD
  * Use SVG for Visual Testing and Documentation
  * try out Github CI features
* Get more versatile with cmake and vcpkg 
* Build Mechanic before Graphic
* Build a giant RTS, in small deliverable pieces

# Links

Here some links which maybe helpful to understand the tech behind it:

* Usher
  * https://en.wikipedia.org/wiki/Hungarian_algorithm
  * https://stackoverflow.com/questions/76444431/faster-alternatives-to-the-hungarian-algorithm
* Pathfinding
  * https://www.jdxdev.com/blog/2020/05/03/flowfields/
  * https://www.gameaipro.com/GameAIPro/GameAIPro_Chapter23_Crowd_Pathfinding_and_Steering_Using_Flow_Field_Tiles.pdf
  * https://www.sanctuaryshatteredsun.com/post/pathfinding-1
  * https://github.com/bjkarasek/flowfield-unity
  * https://gamedev.stackexchange.com/questions/387/how-does-flow-field-pathfinding-work
* Flocking
  * https://ap011y0n.github.io/Group-Movement/ 
* Multiple Topics
  * https://howtorts.github.io/
  * https://www.youtube.com/watch?v=a4yXJ-9H4pY
  * http://youtu.be/5Qyl7h7D1Q8?t=24m24s

# Build

* Use VCPKG and CMAKE
* Dependencies
  * Boost.Geometry
  * Boost.Graph
  * nlohmann::json
  * glm
  * catch2
