#include "polygon.h"
#include <glm/gtx/transform.hpp>

void Polygon::Triangulate()
{
    //TODO: Populate list of triangles
    int n_triangles = this->m_verts.size() - 2;

    for (int i = 1; i <= n_triangles; i++) {
        // Create triangle for every 2 vertices
        Triangle t;
        t.m_indices[0] = 0;
        t.m_indices[1] = i;
        t.m_indices[2] = i + 1;

        // Push the new triangle back to the list of triangles
        this->m_tris.push_back(t);
    }
}

glm::vec3 GetImageColor(const glm::vec2 &uv_coord, const QImage* const image)
{
    if(image)
    {
        int X = glm::min(image->width() * uv_coord.x, image->width() - 1.0f);
        int Y = glm::min(image->height() * (1.0f - uv_coord.y), image->height() - 1.0f);
        QColor color = image->pixel(X, Y);
        return glm::vec3(color.red(), color.green(), color.blue());
    }
    return glm::vec3(255.f, 255.f, 255.f);
}


// Creates a polygon from the input list of vertex positions and colors
Polygon::Polygon(const QString& name, const std::vector<glm::vec4>& pos, const std::vector<glm::vec3>& col)
    : m_tris(), m_verts(), m_name(name), mp_texture(nullptr), mp_normalMap(nullptr)
{
    for(unsigned int i = 0; i < pos.size(); i++)
    {
        m_verts.push_back(Vertex(pos[i], col[i], glm::vec4(), glm::vec2()));
    }
    Triangulate();
}

// Creates a regular polygon with a number of sides indicated by the "sides" input integer.
// All of its vertices are of color "color", and the polygon is centered at "pos".
// It is rotated about its center by "rot" degrees, and is scaled from its center by "scale" units
Polygon::Polygon(const QString& name, int sides, glm::vec3 color, glm::vec4 pos, float rot, glm::vec4 scale)
    : m_tris(), m_verts(), m_name(name), mp_texture(nullptr), mp_normalMap(nullptr)
{
    glm::vec4 v(0.f, 1.f, 0.f, 1.f);
    float angle = 360.f / sides;
    for(int i = 0; i < sides; i++)
    {
        glm::vec4 vert_pos = glm::translate(glm::vec3(pos.x, pos.y, pos.z))
        * glm::rotate(rot, glm::vec3(0.f, 0.f, 1.f))
            * glm::scale(glm::vec3(scale.x, scale.y, scale.z))
            * glm::rotate(i * angle, glm::vec3(0.f, 0.f, 1.f))
            * v;
        m_verts.push_back(Vertex(vert_pos, color, glm::vec4(), glm::vec2()));
    }

    Triangulate();
}

Polygon::Polygon(const QString &name)
    : m_tris(), m_verts(), m_name(name), mp_texture(nullptr), mp_normalMap(nullptr)
{}

Polygon::Polygon()
    : m_tris(), m_verts(), m_name("Polygon"), mp_texture(nullptr), mp_normalMap(nullptr)
{}

Polygon::Polygon(const Polygon& p)
    : m_tris(p.m_tris), m_verts(p.m_verts), m_name(p.m_name), mp_texture(nullptr), mp_normalMap(nullptr)
{
    if(p.mp_texture != nullptr)
    {
        mp_texture = new QImage(*p.mp_texture);
    }
    if(p.mp_normalMap != nullptr)
    {
        mp_normalMap = new QImage(*p.mp_normalMap);
    }
}

Polygon::~Polygon()
{
    delete mp_texture;
}

void Polygon::SetTexture(QImage* i)
{
    mp_texture = i;
}

void Polygon::SetNormalMap(QImage* i)
{
    mp_normalMap = i;
}

void Polygon::AddTriangle(const Triangle& t)
{
    m_tris.push_back(t);
}

void Polygon::AddVertex(const Vertex& v)
{
    m_verts.push_back(v);
}

void Polygon::ClearTriangles()
{
    m_tris.clear();
}

Triangle& Polygon::TriAt(unsigned int i)
{
    return m_tris[i];
}

Triangle Polygon::TriAt(unsigned int i) const
{
    return m_tris[i];
}

Vertex &Polygon::VertAt(unsigned int i)
{
    return m_verts[i];
}

Vertex Polygon::VertAt(unsigned int i) const
{
    return m_verts[i];
}

Segment::Segment()
    : endpoint1({0.f, 0.f}), endpoint2({0.f, 0.f}), slope(0)
{}

Segment::Segment(const std::vector<float> &e1, const std::vector<float> &e2)
    : endpoint1(e1), endpoint2(e2), slope((endpoint2[1] - endpoint1[1]) / (endpoint2[0] - endpoint1[0]))
{}

bool Segment::getIntersection(int y, float &x) const {
    // Both vertices are above row pixel
    if (this->endpoint1[1] > y && this->endpoint2[1] > y) {
        return false;
    }
    // Both vertices are below row pixel
    if (this->endpoint1[1] < y && this->endpoint2[1] < y) {
        return false;
    }
    // Vertical line segment
    if (this->endpoint1[0] == this->endpoint2[0]) {
        x = endpoint1[0];
        return true;
    }
    // Both vertices are on row pixel
    if (this->slope == 0) {
        return false;
    }
    // General case
    float b = this->endpoint1[1] - this->slope * this->endpoint1[0];
    x = (y - b) / slope;
    return true;
}
