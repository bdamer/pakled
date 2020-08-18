# pakled
An easy-to-use texture atlas generator.

# Installation

## Compile-time Dependencies
* LibPNG 1.6.16
* SDL2 2.0.8
* SDL2_image 2.0.3
* Dukat (https://github.com/bdamer/dukat)

# Usage

## Command line

pakled.exe &lt;size&gt; &lt;input directory&gt; &lt;output file&gt;

Example:

pakled.exe 512 .\images .\textures\atlas

Will generate a 512x512 pixel image under .\textures\atlas.png as well as an index file .\textures\atlas.map

