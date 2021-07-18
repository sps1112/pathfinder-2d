# pathfinder-2d
A 2D Pathfinder using the A* algorithm along with Map visualization. 

## Map Details
--- 
The algorithm finds the path between the Blue node to the Red node. The Black nodes are walls with the White nodes being walkable.
<p align="center">
<img width="450" src="screenshots/a1.png" >
</p>

The path is generated and shown as Green Nodes in:-
<p align="center">
<img width="300" src="screenshots/a1.png" >
<img width="300" src="screenshots/a2.png" >
</p>

--- 
## Extra Maps with Path Generation
--- 
- The Path taken changes if target is moved.
<p align="center">
<img width="300" src="screenshots/b1.png" >
<img width="300" src="screenshots/b2.png" >
</p>

- Another case with the target far away from the origin
<p align="center">
<img width="300" src="screenshots/c1.png" >
<img width="300" src="screenshots/c2.png" >
</p>

---
## Options for the Visualisation
--- 
The user can tweak Grid Coloring options for better visualisation of the Pathfinding algo.
For a given map such as:-
<p align="center">
<img width="300" src="screenshots/0.png" >
<img width="300" src="screenshots/1.png" >
</p>

- The user can choose to toggle all the nodes which were called to find the path.
<p align="center">
<img width="300" src="screenshots/1.png" >
<img width="300" src="screenshots/2.png" >
</p>

- The user can also toggle all the neighbour nodes of these nodes.
<p align="center">
<img width="300" src="screenshots/2.png" >
<img width="300" src="screenshots/3.png" >
</p>

## Options for the Pathfinding
--- 
The pathfinding algo can also be tweaked by providing various constraints.
For the previous map:-
<p align="center">
<img width="300" src="screenshots/0.png" >
<img width="300" src="screenshots/1.png" >
</p>

- The user can ban Diagonal movement on the Grid leading to a different path
<p align="center">
<img width="300" src="screenshots/1.png" >
<img width="300" src="screenshots/4.png" >
</p>

--- 
## Extra Features that can be later added

- Add Other Algos such as:-
  - [ ] BFS
  - [ ] Dijkstra
  - [ ] GBFS
- [ ] Add Path weights
- [ ] Elevated Points
- [ ] 3D Map
