
//ECS1: Pieterjan Spoelder's take on an ECS system 
/*********************************
INSPIRATION:
Data oriented design train of thought (special mention to Mike Acton & R. Fabian's 'data-oriented design book)

*********************************/

/*********************************
GOALS:
1: speed: we'll try to accomplish this through :
- we'll allocate all memory up front, preallocating arrays or maybe use a custom iterator(s) that preallocate(s) a certain pool of memory
- cache coherency: consistent arrays, no newing or deleting after initialisation (we'll swap the 'deleted' object with the last object in the component array and decrease the array iteration size with 1 
- concurrency (we'll need to cut nr of processors/threads, cache line size etc to make this work optimally)
- using component arrays has the added benefit of existence-based processing (little or no NULL checks)
- no RTTI, use an enum and/or bitset or int or ..
- we'll try to avoid exceptions

2: ease of use (don't overdo it)
3: adaptability
*********************************/

/*********************************
ENTITIES:
**********************************
IDs:
Smallest possible: integer
we'll use a simple and quick reusability system for entity IDs that got deleted and can be reclaimed so we'll never run out

*********************************/

/*********************************
COMPONENTS
**********************************
We'll have simple components like
Position2D,3D
Velocity2D,3D
...
*********************************/

/*********************************
SYSTEMS
**********************************
We'll provide simple cache efficient functions that can easily be reused
stuff like Move2D(*fromPosArr,*fromVelocityArr,count,*toPosArr)
this is also quite simple to parallelize
We'll need to keep cache line size in mind doing so
*********************************/

/*********************************
HOW IT FITS TOGETHER
**********************************
This is where methods widely differ, 

you could have one gigantic entity list:
----------------------------------------
and have one gigantic set of systems & components
this gives some problems like extra overhead:
you have to keep track of what systems your entity has components in, 
where they live in said systems (their place in the array), ..
this'll make your Manager for inserting and removing (or changing if you want to support that) more complicated
it'll be harder to establish and reason about the size limits of your systems

you can have a lot of smaller entity lists
--------------------------------------
e.g.: 
a floor system
a wall system
a moving wall system (think wolfenstein 3D)
an animated character system
a bullet system

each consisting of their own systems & components
e.g:
walls have a position
moving walls have a position and a posisble velocity if players push them
moving characters have a position,velocity and ton of other stuffs
bullets are simpler but have a position, angle, velocity, maybe a rotation and so on

you can build systems on top of that: say that after moving everything:

we provide a hasCollision system, where we compare a number of shapes

you calculate whether the bullets hit any characters based on the approriate components of the bullets and the characters
and generate events

maybe you also want to check if bullets hit walls, a very similar approach can be used here with a minimal amount of work
you reuse the same hasColission system but slot in the bullets and the walls instead




/*********************************
HOW WE BUILD EVERYTHING ELSE ON TOP:
**********************************
We can build gameplay logic on top of this, if our entity/manager know where our elements in the array reside we can reason on them and influence them
this is ofcourse a bit more specific and generally performance really isn't that much of an issue here

**********************************/

/* TO DO stuff:
We need to measure how much memory we use, and how long a given frame takes to calculate
we also need an easy way to save and load our components so we can support save and loadgames
*/
#include "Components.cpp""
int main() {
	int x = 1,  y = 2,  z = 3;
	ECS1::ComponentContainer<ECS1::Position2D> cc(3) ;
	cc.Set(5, 6, 7);

}