#pragma once
#include <polygon.h>
#include <QImage>
#include <camera.h>

using namespace std;

class Rasterizer
{
private:
    //This is the set of Polygons loaded from a JSON scene file
    std::vector<Polygon> m_polygons;
    std::vector<float> z_buffer;
public:
    Camera camera;
    int size;

    Rasterizer(const std::vector<Polygon>& polygons);
    QImage RenderScene(const string mode, const int AA);
    QImage render(const string mode);
    void ClearScene();
    // Helper functions for rasterizer
    std::array<Segment, 3> getSegments(const Polygon &p,  const Triangle &t) const;
    void getLeftAndRight(const std::array<Segment, 3> &seg, float &x_left, float &x_right, const int i) const;
    void storeColor(const float x_left, const float x_right, const int i, const Polygon &p, const Triangle &t, QImage &result, const string &mode);
    float area(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3) const;
    glm::vec3 barycentricInterpolation(const std::array<glm::vec3, 3> &pos, const glm::vec3 &current_point) const;
    void converWCStoDCS(const glm::mat4 viewM, const glm::mat4 projM, glm::vec4 &v) const;
    template <typename T>
    T perspectiveInterpolation(const std::array<T, 3> &t, const glm::vec3 coeff, const float z) const;
    float lambertianReflection(const glm::vec4 N, const glm::vec4 L) const;
    float toonShading(const glm::vec4 N, const glm::vec4 L) const;
    glm::vec3 blinnPhongReflection(const glm::vec4 N, const glm::vec4 L, const glm::vec3 base_color) const;
    glm::vec3 iridescentReflection(const glm::vec4 N, const glm::vec4 L) const;
    float litSphere(const glm::vec4 N, const glm::vec4 L) const;
    void renderLine(const std::array<Segment, 3> &seg, QImage &result) const;
    void updateBoundingBox(const Polygon& p, Triangle &t) const;
};
