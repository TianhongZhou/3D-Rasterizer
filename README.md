CIS 560 Homework - 3D Rasterizer

# 3D Rasterizer

This project is a C++ implementation of a 3D Rasterizer that renders 3D scenes from geometric data and object files using various shading techniques. It provides support for multiple rendering styles including Lambertian, Blinn-Phong, Toon, and Iridescent shading to create visually appealing and realistic images.

## Features

- **Rendering of 3D Models**: Supports rendering of complex geometric shapes such as cubes, dodecahedrons, and custom OBJ files, and colors them with corresponding texture.
  
  ![3D wahoo](3d_rasterizer_results/3D_wahoo%20(no%20Lambertian%20shading).bmp)
  
- **Perspective Camera**: Using perspective camera for rendering 3D objects, which involves the correctness of perspect.
- **Z-buffering**: Implement Z-buffering instead of Painter's Algorithm.
- **Multiple Shading Techniques**:
  - **Lambertian Shading**: For realistic diffuse reflection.
  - **Blinn-Phong Shading**: For specular highlights and shininess effects.
  - **Toon Shading**: For stylized, cartoon-like rendering.
  - **Iridescent Shading**: For unique color-changing effects based on the viewing angle.
  - **Line Rendering Style**: Only render the lines of triangles in the object.
- **Anti-Aliasing**: Implements 4x Anti-Aliasing (AA) to smooth jagged edges.
- **Scene File Support**: Loads scenes from JSON files that define geometric shapes and their properties.
- **Interactive User Interface**: Built with Qt, allowing dynamic scene manipulation, camera control, and real-time adjustment of rendering parameters.
