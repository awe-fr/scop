# Scop

### Overview

This project is a simple 3D object viewer built using ```C++``` and ```OpenGL```. The main goal is to display a 3D model from an ```.obj``` file, rendered with perspective, and to implement various interactions such as rotating around the object, moving along different axes, and applying a texture.

### Features

   - **3D Object Rendering :** The program loads and parses ```.obj``` files to render 3D objects in a window.
   - **Perspective View :** Objects are displayed with proper perspective, where distant elements appear smaller.
   - **Object Rotation :** The 3D object rotates around its main axis of symmetry, creating a dynamic visual effect.
   - **Facet Coloring :** Different facets of the object are distinguishable by varying colors.
   - **Translation :** Users can move along all three axes (```X, Y, Z```) in both directions.
   - **Texture Application :** A basic texture can be applied to the object using a dedicated key. The texture is smoothly transitioned with a corresponding color display.
   - **42 Logo Support :** The program includes a special feature to display the 42 logo rotating with grayscale facet colors and a fun texture (unicorns).

### Technical Details

   - **Language :** ```C++```
   - **Graphics Library :** ```OpenGL```
   - **External Libraries :** ```GLFW``` only for window management and event handling.
   - **Makefile :** A standard Makefile is provided to build the project.

### How to Run

   - 1 . Clone the repository :

	git clone https://github.com/awe-fr/scop.git

   - 2 . Build the project :

	cd scop
 	make

   - 3 . Run the executable :

	./scop [.obj file]

#### Controls

   - **WASD :** Move forward, backward, left, and right.
   - **CTL / SPACE :** Move upward, downward.
   - **T :** Swap mode (colors to texture).
   - **Esc :** Exit the program
