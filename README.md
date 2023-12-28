![PraiseTheSunFormation](https://github.com/Liech/RTSPathingLib/assets/16963076/5b1392a0-4c31-4a86-92d2-4cba4fa75c40)# RTSPathingLib

Library that tries to provide tools tackling the fundamental problem of the RTS genre:

* How should this unit individually move

Tackling Formation, guide units to formation places, navigation and moving in a formation along the planned path.

# Recreational Goals

* Get more confidence with testing
  * Try TDD
  * Use SVG for Visual Testing and Documentation
* Get more versatile with cmake and vcpkg 
* Build Mechanic before Graphic
* Build a giant RTS, in small deliverable pieces

# Todo

* Formation
  * Unit Placement Behavior Property
    * Center First
    * Distribute Evenly
    * Outer First
  * Hollow Property (e.g. for Hollow Circles)
  * Convex Polygon Shape
  * Extrusion Based Shape (like line formations in BAR)
* Project
  * Github Documentation
  * Release / Setting Public
* Flow Field Pathfinding
* Flocking & Unit Movement

# Formation Generation and showing units to their place

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
Units are Green Dots.
Places are Gray.
The Tickets are Yellow.
![image](https://github.com/Liech/RTSPathingLib/assets/16963076/9f426be9-84a7-4326-a5d6-c471aa4996e8)

# Complex Formation Generation

An Complex Example for a Formation with different Unit Sizes.

Here is an example that may justify this Formation:
 * Red Units are in the center to be protected from aggressive Forces. Archers and a few Big Catapults.
 * Green Units are the Protectors. Heavy armored Paladins.
 * Blue Units are Horsemen / Zerglings. Melee units that are fast. They swarm out protected by the heavy fire of the archers.

![image](https://github.com/Liech/RTSPathingLib/assets/16963076/95d2e214-1b93-44c1-b1ed-4106aa1c310f)
See "Formation/PraiseTheSun" Test if you are interested how its done.

# Build

* Use VCPKG and CMAKE
* Dependencies
  * Boost.Geometry
  * Boost.Graph
  * nlohmann::json
  * glm
  * catch2
