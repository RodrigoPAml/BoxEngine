// Shader basico para ray tracing com 1 bounce
#version 330 core

out vec4 FragColor;

<<SQUARES>>
#define PI 3.14159265359
#define INF 999999999.0

// Define a qualidade da luz indireta
// Número de raios castados para determinar a luz indireta
// (para qualidade maxima por no minimo 360)
#define DIR <<RAYS>> 

struct Square
{
    vec2 position;
    vec2 size;
    vec3 color;
};

// Quadrados do cenario
uniform Square squares[MAX_SQUARES];
uniform vec2 mouse;
uniform float closeLightStr;
uniform float distLightStr;
uniform float linearStr;
uniform float ambientLight;

// Intersection between lines detection
bool LineLineIntersect(vec2 l1p1, vec2 l1p2, vec2 l2p1, vec2 l2p2) 
{
    float ua = ((l2p2.x - l2p1.x) * (l1p1.y - l2p1.y) - (l2p2.y - l2p1.y) * (l1p1.x - l2p1.x)) / ((l2p2.y - l2p1.y) * (l1p2.x - l1p1.x) - (l2p2.x - l2p1.x) * (l1p2.y - l1p1.y));
    float ub = ((l1p2.x - l1p1.x) * (l1p1.y - l2p1.y) - (l1p2.y - l1p1.y) * (l1p1.x - l2p1.x)) / ((l2p2.y - l2p1.y) * (l1p2.x - l1p1.x) - (l2p2.x - l2p1.x) * (l1p2.y - l1p1.y));
  
    return (ua >= 0.0 && ua <= 1.0 && ub >= 0.0 && ub <= 1.0);
}

// Intersection between line and rect detection
bool LineRectIntersect(vec2 lineStart, vec2 lineEnd, vec2 rectCenter, vec2 rectSize)
{
    vec2 rectHalfSize = rectSize * 0.5;
    vec2 rectMin = rectCenter - rectHalfSize;
    vec2 rectMax = rectCenter + rectHalfSize;
  
    return (LineLineIntersect(lineStart, lineEnd, rectMin, vec2(rectMin.x, rectMax.y)) || LineLineIntersect(lineStart, lineEnd, vec2(rectMin.x, rectMax.y), rectMax) || LineLineIntersect(lineStart, lineEnd, rectMax, vec2(rectMax.x, rectMin.y)) || LineLineIntersect(lineStart, lineEnd, vec2(rectMax.x, rectMin.y), rectMin));
}

// Find the point of intersection between a ray and rect
vec2 RayRectangleIntersection(vec2 rayOrigin, vec2 rayDirection, vec2 rectCenter, vec2 rectSize)
{
    vec2 halfSize = rectSize * 0.5;
    vec2 rectPosition = rectCenter - halfSize;

    vec2 t1 = (rectPosition - rayOrigin) / rayDirection;
    vec2 t2 = (rectPosition + rectSize - rayOrigin) / rayDirection;

    vec2 tMin = min(t1, t2);
    vec2 tMax = max(t1, t2);

    float tEnter = max(tMin.x, tMin.y);
    float tExit = min(tMax.x, tMax.y);

    if (tEnter > tExit || tExit < 0.0) 
        return vec2(-1.0, -1.0);
    
    vec2 intersectionPoint = rayOrigin + tEnter * rayDirection;

    return intersectionPoint;
}

// Get a normalized direction between two points
vec2 GetNormalizedDirection(vec2 fromPoint, vec2 toPoint)
{
    return normalize(toPoint - fromPoint);
}

// Draw a rect
bool IsRect(vec2 pos, vec2 size, vec2 currFrag) 
{
    return (currFrag.x >= pos.x - size.x / 2.0 && currFrag.x <= pos.x + size.x / 2.0 && currFrag.y >= pos.y - size.y / 2.0 && currFrag.y <= pos.y + size.y / 2.0) ;
}

// Get normalized vector to an angle
vec2 GetDirection(int angle) 
{
    float r = (2.0 * PI * float(angle)) / float(DIR);
    return normalize(vec2(cos(r), sin(r)));
}

// Return if reached by light
bool ReachLight(vec2 fragPos, vec2 lightPos, int reduce)
{
    for (int i = 0; i < MAX_SQUARES; ++i) 
    {
        vec2 size = squares[i].size;
      
        if(reduce == i)
        {
            size.x = size.x - 1.0;
            size.y = size.y - 1.0;
        }
      
        bool intersect = LineRectIntersect(lightPos, fragPos, squares[i].position, size);

        if (intersect)
            return false;
    }
    
    return true;
}

// Calculate light based on distance
float GetLight(float baseValue, float distanceToLight)
{
    return baseValue / (linearStr + closeLightStr * distanceToLight + distLightStr * distanceToLight * distanceToLight);
}

// Calculate light for an point in shadow (used in indirect light calculation only)
float CalculateLightPixelIndirect(vec2 fragPos, vec2 lightPos, int ignore)
{
    if (!ReachLight(fragPos, lightPos, ignore)) 
      return ambientLight;
  
    float distanceToLight = distance(fragPos, lightPos);
    float attenuation = GetLight(1.0, distanceToLight);
  
    return max(ambientLight, attenuation);
}

vec2 CalculateSquareNormal(vec2 fragPos, Square square)
{
    vec2 halfSize = square.size * 0.5;
    float epsilon = 0.1;
    
    if(fragPos.y - epsilon < square.position.y - halfSize.y)
        return vec2(0, -1);
    if(fragPos.y + epsilon > square.position.y + halfSize.y)
        return vec2(0, 1);
    if(fragPos.x - epsilon < square.position.x - halfSize.x)
        return vec2(-1, 0);
    if(fragPos.x + epsilon > square.position.x + halfSize.x)
        return vec2(1, 0);
   
    return vec2(0.0);
}

// Calculate indirect light by casting rays around the pixel
// If a ray hits a particular quad that have light in it, it will be take into account
// Only take into account the nearest hit for each direction
float CalculateIndirectLight(vec2 fragPos, vec2 lightPos, int idx) 
{
    float result = 0.0;
    float hits = 0.0;
  
    // Cast rays around the dark pixel
    for (int j = 0; j < DIR; ++j) 
    {
        vec2 dir = GetDirection(j);
    
        float nearestDistance = INF;
        float dirResult = 0.0;

        // Test foreach quad
        for (int i = 0; i < MAX_SQUARES; ++i)
        {
            // Where the ray hit the quad
            vec2 interP = RayRectangleIntersection(fragPos, dir, squares[i].position, squares[i].size);
        
            if (interP == vec2(-1, -1) || idx == i) 
                continue;
            
            float distIntersect = distance(interP, fragPos);
        
            // We only want the more closest hit
            if(distIntersect >= nearestDistance && nearestDistance != INF)
                continue;
              
            // Calculate the light intensity in the point hitted
            float lightInIntersection = CalculateLightPixelIndirect(interP, lightPos, i);

            // Attenuate until it get in fragPos
            float correctedLight = GetLight(lightInIntersection, distIntersect);
            vec2 normal = CalculateSquareNormal(interP, squares[i]);
            
            // Calculate vectors from the intersected point to (light and pixel)
            vec2 dirToLight = normalize(interP - lightPos);
            vec2 dirReflected = normalize(reflect(dirToLight, normal));
            vec2 dirToPoint = GetNormalizedDirection(interP, fragPos);   

            // Get the angle
            float dotProduct = dot(dirReflected, dirToPoint);
            float angleCloseness = 0.5 * (dotProduct + 1.0);
            
            dirResult = correctedLight * angleCloseness;
            nearestDistance = distIntersect;
        }
    
        if(nearestDistance != INF)
        {
            result += dirResult;
            hits = hits + 1.0;
        }
    }
    
    return (result)/DIR;
}

// Main function that calculates light for each pixel
float CalculateLightPixel(vec2 fragPos, vec2 lightPos, int i) 
{ 
    // Here its for indirect light
    if (!ReachLight(fragPos, lightPos, -1)) 
        return CalculateIndirectLight(fragPos, lightPos, i);
  
    // Direct light
    float distanceToLight = distance(fragPos, lightPos);
    float attenuation = GetLight(1.0f, distanceToLight);
  
    return attenuation;
}

void main() 
{
  vec3 color = vec3(1.0);
  vec2 lightPosition = mouse;

  int index = -1;
  for (int i = 0; i < MAX_SQUARES; ++i) 
  {
    if(IsRect(squares[i].position, squares[i].size, gl_FragCoord.xy))
    {
        index = i;
        color *= squares[i].color * 2;
    }
  }
  
  color *= CalculateLightPixel(gl_FragCoord.xy, lightPosition, index);

  FragColor = vec4(color, 1.0);
}