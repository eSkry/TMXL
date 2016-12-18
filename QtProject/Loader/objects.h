#ifndef OBJECTS_H
#define OBJECTS_H

/////////// SFML ///////////
#include <SFML/Graphics.hpp>
using namespace sf;


/////////// STL ///////////
#include <string>
#include <list>
using namespace std;

/////////////////////////// OBJECTS ///////////////////////////
struct Objects_ML{
    string              sObjectGroupName;
    string              sName;
    string              sType;

    int                 iID;

    void*               vData;
};

struct Shape_ML : public Objects_ML{
    Shape_ML();
    Shape_ML(const Shape_ML &obj);

    FloatRect           fRect;

    Texture*            tTexture;
};

struct Rect_ML : public Objects_ML{
    Rect_ML();
    Rect_ML(const Rect_ML &object);

    FloatRect           fRect;

    Texture*            tTexture;
    Sprite*             sSprite;
};

struct Polygon_ML : public Objects_ML{
    Polygon_ML();
    Polygon_ML(const Polygon_ML &obj);

    Vector2f            vPosition;

    ConvexShape         cShape;

    list<Vector2f>      lShapePoints;
    int                 iCountShapePoints;
};

struct Polyline_ML : public Objects_ML{
    Polyline_ML();
    Polyline_ML(const Polyline_ML &obj);

    ConvexShape         cShape;

    list<Vector2f>      lShapePoints;
    int                 iCountShapePoints;
};

typedef list<Objects_ML*>  LObjects;
typedef list<Shape_ML*>    LElipse;
typedef list<Rect_ML*>     LRect;
typedef list<Polygon_ML*>  LPolygon;
typedef list<Polyline_ML*> LPolyline;

/////////////////////////// OBJECTS ///////////////////////////

#endif // OBJECTS_H
