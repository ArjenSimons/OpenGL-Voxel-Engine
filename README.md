# OpenGL-Voxel-Engine

This voxel engine is created using modern OpenGL. Features like world to screen space projection have been made from the ground up. To keep the scope of the project at a reasonable size libraries where used for time consuming trivial tasks like creating a window on windows or other platforms. To get started on the voxel part of the project a graphics engine was made. This graphics engine only exists out of features necessary to create the voxel engine. (e.g. world to screen space projection, basic lighting and camera movement). 
The main features from the voxel engine it self are the generation of a chunk that’s build out of voxels. Only the faces that don’t touch another voxel are used to create a mesh that’s rendered. The other big features are chunk loading, multi threading and texturing.
