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
struct Objects{
    string              sObjectGroupName;
    string              sName;
    string              sType;

    int                 iID;

    void*               vData;
};

struct TShape : public Objects{
    TShape();
    TShape(const TShape &obj);

    FloatRect           fRect;

    Texture*            tTexture;
};

struct TRect : public Objects{
    TRect();
    TRect(const TRect &object);

    FloatRect           fRect;

    Texture*            tTexture;
    Sprite*             sSprite;
};

struct Polygon : public Objects{
    Polygon();
    Polygon(const Polygon &obj);

    Vector2f            vPosition;

    ConvexShape         cShape;

    list<Vector2f>      lShapePoints;
    int                 iCountShapePoints;
};

struct Polyline : public Objects{
    Polyline();
    Polyline(const Polyline &obj);

    ConvexShape         cShape;

    list<Vector2f>      lShapePoints;
    int                 iCountShapePoints;
};

typedef list<Objects*>  LObjects;
typedef list<TRect*>    LRect;
typedef list<TShape*>   LElipse;
typedef list<Polygon*>  LPolygon;
typedef list<Polyline*> LPolyline;

/////////////////////////// OBJECTS ///////////////////////////

#endif // OBJECTS_H
