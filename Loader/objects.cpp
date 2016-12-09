#include "objects.h"

TRect::TRect() : Objects() {
    sSprite         = nullptr;
    tTexture        = nullptr;
    vData           = nullptr;
    iID             = 0;
}

TRect::TRect(const TRect &object){
    iID             = object.iID;
    sName           = object.sName;
    sType           = object.sType;
    sObjectGroupName      = object.sObjectGroupName;

    fRect           = object.fRect;

    sSprite         = object.sSprite;
    tTexture        = object.tTexture;
    vData           = object.vData;
}

TShape::TShape(){
    tTexture        = nullptr;
    vData           = nullptr;
}

TShape::TShape(const TShape &obj){
    sName           = obj.sName;
    sType           = obj.sType;
    sObjectGroupName     = obj.sObjectGroupName;

    tTexture        = obj.tTexture;
    fRect           = obj.fRect;

    iID             = obj.iID;

    vData           = obj.vData;
}

Polygon::Polygon() : Objects(){
    iCountShapePoints = 0;
}

Polygon::Polygon(const Polygon &obj){
    iID               = obj.iID;
    iCountShapePoints = obj.iCountShapePoints;
    sName             = obj.sName;
    sType             = obj.sType;
    sObjectGroupName  = obj.sObjectGroupName;
    vData             = obj.vData;
    lShapePoints      = obj.lShapePoints;
    vPosition         = obj.vPosition;
    cShape            = obj.cShape;
}

Polyline::Polyline(){
    iCountShapePoints = 0;
}

Polyline::Polyline(const Polyline &obj){
    cShape            = obj.cShape;
    iCountShapePoints = obj.iCountShapePoints;
    iID               = obj.iID;
    sName             = obj.sName;
    sObjectGroupName  = obj.sObjectGroupName;
    sType             = obj.sType;
    lShapePoints      = obj.lShapePoints;
    vData             = obj.vData;
}
