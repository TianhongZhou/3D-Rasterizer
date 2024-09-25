CIS 560 Homework - 3D Rasterizer

# 3D Rasterizer

This project is a C++ implementation of a 3D Rasterizer that renders 3D scenes from geometric data and object files using various shading techniques. It provides support for multiple rendering styles including Lambertian, Blinn-Phong, Toon, and Iridescent shading to create visually appealing and realistic images.

## Features

- **Rendering of 3D Models**: Supports rendering of complex geometric shapes such as cubes, dodecahedrons, and custom OBJ files, and colors them with corresponding texture.
- **Perspective Camera**: Using perspective camera for rendering 3D objects, which involves the correctness of perspect.
  
  ![3D wahoo](3d_rasterizer_results/3D_wahoo%20(no%20Lambertian%20shading).bmp)
  
- **Z-buffering**: Implement Z-buffering instead of Painter's Algorithm.

  ![Z-buffering](3d_rasterizer_results/3D_twoTri.bmp)
 
- **Multiple Shading Techniques**:
  - **Lambertian Shading**: For realistic diffuse reflection.
    
    ![Lambertian](3d_rasterizer_results/3D_wahoo%20(with%20Lambertian%20shading).bmp)
  
  - **Blinn-Phong Shading**: For specular highlights and shininess effects.
      
    ![blinn-phong](3d_rasterizer_results/3D_wahoo%20(with%20Blinn-Phong%20shading).bmp)
  
  - **Toon Shading**: For stylized, cartoon-like rendering.

    ![Toon](3d_rasterizer_results/3D_wahoo%20(with%20Toon2%20shading).bmp)

  - **Iridescent Shading**: For unique color-changing effects based on the viewing angle.
 
    ![Iridescent](3d_rasterizer_results/3D_wahoo%20(with%20Iridescent%20shading).bmp)

  - **Line Rendering Style**: Only render the lines of triangles in the object.
 
    ![Line](3d_rasterizer_results/3D_wahoo%20(line%20render).bmp)

- **Anti-Aliasing**: Implements Nx Anti-Aliasing (AA) to smooth jagged edges.

  <p align="center">
    <img src="3d_rasterizer_results/3D_wahoo%20(no%20Lambertian%20shading).bmp" alt="3D Wahoo without AA" width="30%" />
    <img src="3d_rasterizer_results/3D_wahoo%20(4x%20AA).bmp" alt="3D Wahoo with 4x AA" width="30%" />
    <img src="3d_rasterizer_results/3D_wahoo%20(16x%20AA).bmp" alt="3D Wahoo with 16x AA" width="30%" />
  </p>

- **Scene File Support**: Loads scenes from JSON files that define geometric shapes and their properties.
- **Interactive User Interface**: Built with Qt, allowing dynamic scene manipulation, camera control, and real-time adjustment of rendering parameters.
