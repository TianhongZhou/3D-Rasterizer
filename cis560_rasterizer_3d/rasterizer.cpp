#include "rasterizer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "camera.h"

Rasterizer::Rasterizer(const std::vector<Polygon>& polygons)
    : m_polygons(polygons),
    z_buffer(std::vector<float>()),
    camera(), size()
{}

QImage Rasterizer::RenderScene(const string mode, const int AA)
{
    this->size = AA * 512;
    QImage large = render(mode);
    QImage result(512, 512, QImage::Format_RGB32);

    // Scaling down
    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 512; j++) {
            // Calculate the average color
            float r = 0.f;
            float g = 0.f;
            float b = 0.f;

            for(int m = 0; m < AA; m++) {
                for (int n = 0; n < AA; n++) {
                    QRgb cLarge = large.pixel(i * AA + m, j * AA + n);
                    QColor color(cLarge);
                    r += color.red();
                    g += color.green();
                    b += color.blue();
                }
            }

            QRgb c = qRgb(r / AA / AA, g / AA / AA, b / AA / AA);
            result.setPixel(i, j, c);
        }
    }
    return result;
}

QImage Rasterizer::render(const string mode) {
    this->z_buffer = std::vector<float>(this->size * this->size, 1000.f);

    QImage result(this->size, this->size, QImage::Format_RGB32);
    // Fill the image with black pixels
    result.fill(qRgb(0.f, 0.f, 0.f));

    glm::mat4 viewM = this->camera.viewMatrix();
    glm::mat4 projM = this->camera.projMatrix();

    // Iterate over pixel row
    for (int i = 0; i < this->size; i++) {
        float current_y = (float) i;

        // Iterate over every polygon
        for (unsigned long long j = 0; j < this->m_polygons.size(); j++) {
            Polygon p = this->m_polygons[j];

            // Convert pos for every vertex from world space to pixel space
            for (unsigned long long m = 0; m < p.m_verts.size(); m++) {
                Vertex* v = &p.m_verts[m];
                v->c_pos = viewM * v->m_pos;
                converWCStoDCS(viewM, projM, v->m_pos);
            }

            // Iterator over every triangle
            for (unsigned long long m = 0; m < p.m_tris.size(); m++) {
                float x_left = (float) this->size - 1.f;
                float x_right = 0.f;

                Triangle t = p.m_tris[m];
                updateBoundingBox(p, t);
                // Row pixel out of bounding box case
                if (current_y > t.y_max || current_y < t.y_min) {
                    continue;
                }

                // Create three line segments for the trianlge
                std::array<Segment, 3> seg = getSegments(p, t);

                if (mode == "Line") {
                    renderLine(seg, result);
                    continue;
                }

                // Find x_left and x_right for current row pixel
                getLeftAndRight(seg, x_left, x_right, i);

                // Store color of pixels between x_left and x_right into frags
                storeColor(x_left, x_right, i, p, t, result, mode);
            }
        }
    }

    return result;
}

// Update the bouding box of triangle
void Rasterizer::updateBoundingBox(const Polygon& p, Triangle &t) const {
    for (int j = 0; j < 3; j++) {
        float x = p.m_verts[t.m_indices[j]].m_pos.x;
        float y = p.m_verts[t.m_indices[j]].m_pos.y;
        t.x_min = std::min(t.x_min, x);
        t.x_max = std::max(t.x_max, x);
        t.y_min = std::min(t.y_min, y);
        t.y_max = std::max(t.y_max, y);
    }

    t.x_min = std::max(t.x_min, 0.f);
    t.x_max = std::min(t.x_max, (float) this->size - 1.f);
    t.y_min = std::max(t.y_min, 0.f);
    t.y_max = std::min(t.y_max, (float) this->size - 1.f);
}

// Draw the lines only
void Rasterizer::renderLine(const std::array<Segment, 3> &seg, QImage &result) const {
    for (int i = 0; i < 3; i++) {
        std::vector<float> end1 = seg[i].endpoint1;
        std::vector<float> end2 = seg[i].endpoint2;

        glm::vec2 e1(end1[0], end1[1]);
        glm::vec2 e2(end2[0], end2[1]);

        QRgb c = qRgb(255.f, 255.f, 255.f);

        float u = 0.f;
        while (u <= 1.f) {
            glm::vec2 point = glm::mix(e1, e2, u);
            if ((int) point.x >= 0 && (int) point.x <= (this->size - 1) && (int) point.y >= 0 && (int) point.y <= (this->size - 1)) {
                result.setPixel((int) point.x, (int) point.y, c);
            }
            u += 0.001f;
        }
    }
}

// Convert vertex position and normal from WCS to DCS
void Rasterizer::converWCStoDCS(const glm::mat4 viewM, const glm::mat4 projM, glm::vec4 &v) const {
    glm::vec4 wcs = v;
    glm::vec4 vcs = viewM * wcs;
    glm::vec4 ccs = projM * vcs;
    glm::vec4 ndcs = ccs;
    ndcs = ccs / ccs.w;
    glm::vec4 dcs = ndcs;
    dcs.x = (ndcs.x + 1.f) * (float) this->size / 2.f;
    dcs.y = (1.f - ndcs.y) * (float) this->size / 2.f;
    v = dcs;
}

// Calculating area of triangle
float Rasterizer::area(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3) const {
    glm::vec3 c = glm::cross(p1 - p2, p3 - p2);
    float l = glm::length(c);
    return 0.5f * l;
}

// Calculate the color using Barycentric interpolation
glm::vec3 Rasterizer::barycentricInterpolation(const std::array<glm::vec3, 3> &pos, const glm::vec3 &current_point) const {
    float s = area(pos[0], pos[1], pos[2]);
    float s1 = area(current_point, pos[1], pos[2]);
    float s2 = area(current_point, pos[2], pos[0]);
    float s3 = area(current_point, pos[0], pos[1]);

    return {s1 / s, s2 / s, s3 / s};
}

// Template function for Perspective-correct interpolation
template <typename T>
T Rasterizer::perspectiveInterpolation(const std::array<T, 3> &t, const glm::vec3 coeff, const float z) const {
    T result = T(0.f);
    for (int i = 0; i < 3; i++) {
        result += t[i] * coeff[i];
    }
    return z * result;
}

// Store color of pixels between x_left and x_right into frags
void Rasterizer::storeColor(const float x_left, const float x_right, const int i, const Polygon &p, const Triangle &t, QImage &result, const string &mode) {
    float f = x_left - (int) x_left;
    for (int n = x_left; n + f <= x_right; n++) {
        float current_x = n + f;
        float current_y = (float) i;
        glm::vec3 current_point = {current_x, current_y, 0.f};

        // 3D rasterizer
        // Store info of vertices to a list for every triangle
        std::array<glm::vec2, 3> uvs;
        std::array<glm::vec4, 3> normals;
        std::array<glm::vec3, 3> pos;
        std::array<float, 3> zs;

        for (int n = 0; n < 3; n++) {
            glm::vec4 vertex_pos = p.m_verts[t.m_indices[n]].m_pos;
            pos[n] = {vertex_pos.x, vertex_pos.y, 0.f};
            uvs[n] = p.m_verts[t.m_indices[n]].m_uv;
            normals[n] = p.m_verts[t.m_indices[n]].m_normal;
            zs[n] = p.m_verts[t.m_indices[n]].c_pos.z;
        }

        // Use perspective-correct interpolation to calculate current z
        glm::vec3 coeff = barycentricInterpolation(pos, current_point);
        float sum = 0.f;
        for (int n = 0; n < 3; n++) {
            coeff[n] /= zs[n];
            sum += coeff[n];
        }

        // Compare current z with z buffer
        float current_z = 1.f / sum;
        if (z_buffer[n + this->size * i] <= current_z) {
            continue;
        }
        z_buffer[n + this->size * i] = current_z;

        // Use current z and coefficients to find color, normal, uv for current frag
        glm::vec2 current_uv = perspectiveInterpolation(uvs, coeff, current_z);
        glm::vec4 current_normal = perspectiveInterpolation(normals, coeff, current_z);

        // Read colors from texture
        glm::vec3 current_color = GetImageColor(current_uv, p.mp_texture);

        /* 2D rasterizer
        std::array<glm::vec3, 3> colors;
        std::array<glm::vec3, 3> pos;
        float current_z = 0.f;
        for (int n = 0; n < 3; n++) {
            glm::vec4 vertex_pos = p.m_verts[t.m_indices[n]].m_pos;
            pos[n] = {vertex_pos.x, vertex_pos.y, 0.f};
            colors[n] = p.m_verts[t.m_indices[n]].m_color;
            current_z = vertex_pos.z;
        }

        // Calculate colors using barycentric interpolation
        glm::vec3 coeff = barycentricInterpolation(pos, current_point);
        glm::vec3 current_color;
        for (int n = 0; n < 3; n++) {
            current_color += coeff[n] * colors[n];
        }
        */

        // Conver position of current fragment back to wcs
        float ndcs_x = current_x / (float) this->size * 2.f - 1.f;
        float ndcs_y = 1.f - current_y / (float) this->size * 2.f;
        glm::vec4 ndcs(ndcs_x, ndcs_y, current_z, 1.0f);
        glm::vec4 vcs = glm::inverse(this->camera.projMatrix()) * ndcs;
        glm::vec4 wcs = glm::inverse(this->camera.viewMatrix()) * vcs;
        glm::vec4 L = this->camera.getPos() - wcs;

        glm::vec3 final_color;

        // Apply shading
        if (mode == "None") {
            final_color = current_color;
        } else if (mode == "Lambertian") {
            final_color = lambertianReflection(current_normal, L) * current_color;
        } else if (mode == "Toon1") {
            final_color = glm::mix(glm::vec3(255.f, 0.f, 0.f), glm::vec3(255.f, 255.f, 0.f), toonShading(current_normal, L));
        } else if (mode == "Toon2") {
            final_color = glm::mix(glm::vec3(0.f, 0.f, 0.f), current_color, toonShading(current_normal, L));
        } else if (mode == "Blinn-Phong") {
            final_color = blinnPhongReflection(current_normal, L, current_color);
        } else if (mode == "Iridescent") {
            final_color = iridescentReflection(current_normal, L);
        }

        QRgb c = qRgb(glm::clamp(final_color.x, 0.f, 255.f), glm::clamp(final_color.y, 0.f, 255.f), glm::clamp(final_color.z, 0.f, 255.f));
        result.setPixel(n, i, c);
    }
}

glm::vec3 Rasterizer::iridescentReflection(const glm::vec4 N, const glm::vec4 L) const {
    glm::vec3 normalized_N = glm::normalize(glm::vec3(N));
    glm::vec3 normalized_L = glm::normalize(glm::vec3(L));

    float diffuse = glm::dot(normalized_N, normalized_L);
    diffuse = glm::clamp(diffuse, 0.f, 1.f);

    if (diffuse < 0.2f) {
        return glm::mix(glm::vec3(255.f, 0.f, 0.f), glm::vec3(255.f, 255.f, 0.f), diffuse * 5.f);
    } else if (diffuse < 0.4f) {
        return glm::mix(glm::vec3(255.f, 255.f, 0.f), glm::vec3(0.f, 255.f, 0.f), (diffuse - 0.2f) * 5.f);
    } else if (diffuse < 0.6f) {
        return glm::mix(glm::vec3(0.f, 255.f, 0.f), glm::vec3(0.f, 0.f, 255.f), (diffuse - 0.4f) * 5.f);
    } else if (diffuse < 0.8f) {
        return glm::mix(glm::vec3(0.f, 0.f, 255.f), glm::vec3(255.f, 0.f, 255.f), (diffuse - 0.6f) * 5.f);
    }
    return glm::mix(glm::vec3(255.f, 0.f, 255.f), glm::vec3(255.f, 0.f, 0.f), (diffuse - 0.8f) * 5.f);
}

glm::vec3 Rasterizer::blinnPhongReflection(const glm::vec4 N, const glm::vec4 L, const glm::vec3 base_color) const {
    float ka = 0.1f;
    glm::vec3 ambient_color = ka * base_color;

    float kd = 1.f;
    float diffuse_intensity = lambertianReflection(N, L);
    glm::vec3 diffuse_color = kd * diffuse_intensity * base_color;

    float ks = 0.2f;
    float shinningness = 32.f;
    // L = V in our case since light is at camera pos
    glm::vec3 H = glm::vec3(L) + glm::vec3(L);
    glm::vec3 normalized_N = glm::normalize(glm::vec3(N));
    glm::vec3 normalized_H = glm::normalize(glm::vec3(H));
    float specular_intensity = glm::clamp(glm::dot(normalized_H, normalized_N), 0.f, 1.f);
    glm::vec3 specular_base_color(255.f);
    glm::vec3 specular_color = ks * glm::pow(specular_intensity, shinningness) * specular_base_color;

    glm::vec3 final_color = ambient_color + diffuse_color + specular_color;
    return final_color;
}

float Rasterizer::toonShading(const glm::vec4 N, const glm::vec4 L) const {
    glm::vec3 normalized_N = glm::normalize(glm::vec3(N));
    glm::vec3 normalized_L = glm::normalize(glm::vec3(L));

    float diffuse = glm::dot(normalized_N, normalized_L);

    // Make diffuse a step function
    diffuse = floor(diffuse * 5.f) / 5.f;

    return glm::clamp(diffuse, 0.f, 1.f);
}

float Rasterizer::lambertianReflection(const glm::vec4 N, const glm::vec4 L) const {
    glm::vec3 normalized_N = glm::normalize(glm::vec3(N));
    glm::vec3 normalized_L = glm::normalize(glm::vec3(L));

    float diffuse = glm::dot(normalized_N, normalized_L);

    return glm::clamp(diffuse, 0.f, 1.f);
}

// Find x_left and x_right for current row pixel
void Rasterizer::getLeftAndRight(const std::array<Segment, 3> &seg, float &x_left, float &x_right, const int i) const {
    for (int n = 0; n < 3; n++) {
        float x = 0.f;
        if (!seg[n].getIntersection(i, x)) {
            continue;
        }
        x_left = std::min(x_left, x);
        x_right = std::max(x_right, x);
        x_left = std::max(x_left, 0.f);
        x_right = std::min(x_right, (float) this->size - 1.f);
    }
}

// Create three line segments for the trianlge
std::array<Segment, 3> Rasterizer::getSegments(const Polygon &p,  const Triangle &t) const {
    std::array<std::vector<float>, 3> pos;
    std::array<Segment, 3> seg;
    for (int n = 0; n < 3; n++) {
        glm::vec4 vertex_pos = p.m_verts[t.m_indices[n]].m_pos;
        pos[n] = {vertex_pos.x, vertex_pos.y, vertex_pos.z};
    }
    seg[0] = Segment(pos[0], pos[1]);
    seg[1] = Segment(pos[0], pos[2]);
    seg[2] = Segment(pos[1], pos[2]);
    return seg;
}

void Rasterizer::ClearScene()
{
    m_polygons.clear();
}
