<h1 align="center" id="title">miniRT</h1>

<p id="description">Mini raytracer written in c.</p>

<h2> Screenshot</h2>

![Screenshot 1](/img/screenshot1.png)

<h2>🧐 Features</h2>

Here're some of the project's best features:

*   Rendering basic shapes (plane rectangle sphere cylinder and cone)
*   Rendering from a scene file (custom configuration files some examples found in ./scenes)
*   Multiple colored point lights
*   Shadows
*   Reflections
*   Texture uv mapping
*   Normal maps.

<h2>🕹️ controls</h2>

*   ```Mouse click to select an object.```
*   ```Hold ctrl to control the camera instead.```
*   wasd: move around.
*   NUMPAD_8 / NUMPAD_2 : move up / move down
*   up / down arrow     : rotate along x axis.
*   left / right arrow  : rotate along y axis (z for camera).
*   NUMPAD_6 / NUMPAD_4 : rotate along z axis (not implemented for camera for obvious reason (dizziness)).
*   NUMPAD_+ / NUMPAD_- : control object's radius.
*   KEYPAD_+ / KEYPAD_- : control object's height.
*   KEYPAD_( / KEYPAD_) : control object's width.
*   KEYPAD_H            : hide/unhide object.
*   KEYPAD_G            : generate a .rt file for the current scene (extra).

<h2>🛠️ Installation Steps:</h2>

<p>1. install 42 mlx.</p>

<p>2. Compile.</p>

for compiling mandatory part:
```
make
```
for compiling bonus part (recommended):
```
make bonus
```
for compiling extra part (contains some additional features):
```
make extra
```
<p>3. Run</p>

Mandatory:
```
./miniRT [path to a scene file containing only mandatory params]
```

Bonus:
```
./miniRT_bonus [path to a scene file with full features]
```
Extra:
```
./miniRT_extra [path to a scene file with full features]
```
