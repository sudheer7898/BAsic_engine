# BAsic_engine
RobustEngine-C++
A high-performance, modular 2D/3D Game Engine built from scratch using C++17 and OpenGL 4.x. This project was engineered to explore low-level system architecture, memory management, and GPU pipeline optimization.
<p>
  
🚀 Architectural Highlights
1. High-Performance Rendering Pipeline
Interleaved Vertex Buffers: Implemented a custom data-packing strategy (Position, Color, UV) to minimize GPU bus traffic and maximize cache locality.

   Shader-Driven Architecture: Decoupled rendering logic from object data, allowing for dynamic shader swapping and real-time uniform updates (Model-View-Projection).
   
   Automated Texture Mapping: Integrated stb_image with a custom RAII-compliant Texture_2D class, supporting mipmapping, anisotropic filtering, and multiple wrap modes.
</p>


2. Modern C++ Memory Management
RAII & Smart Pointers: Zero-leak memory architecture using std::shared_ptr and std::unique_ptr for lifetime management of GPU resources (VAOs, VBOs, Textures).

    Scene Graph System: A robust hierarchy-based scene management system that allows for efficient object querying via custom Tagging and MetaData systems.

3. Advanced 3D Camera System
Basis Vector Navigation: Built a custom 3D Camera using Gram-Schmidt Orthonormalization to manage local coordinate systems (Right, Up, Front).

Real-time Interaction: Integrated a decoupled Input System with std::function callbacks to allow smooth 3D navigation and user interaction.

🛠️ Tech Stack
Language: C++17

Graphics API: OpenGL 4.3 (Core Profile)

Windowing/Input: GLFW, GLAD

Math: GLM (OpenGL Mathematics)

Image Loading: stb_image

🏗️ Phase 1 Milestone Reached
[x] Engine Bone Structure & Main Loop

[x] Interleaved Buffer Logic (8-stride UV support)

[x] Perspective & Orthographic Projection

[x] RAII Texture Wrapper

[x] Decoupled Renderer Pipeline
