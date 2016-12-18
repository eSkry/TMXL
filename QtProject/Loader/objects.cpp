#include "objects.h"

Rect_ML::Rect_ML() : Objects_ML() {
    sSprite         = nullptr;
    tTexture        = nullptr;
    vData           = nullptr;
    iID             = 0;
}

Rect_ML::Rect_ML(const Rect_ML &object){
    iID             = object.iID;
    sName           = object.sName;
    sType           = object.sType;
    sObjectGroupName      = object.sObjectGroupName;

    fRect           = object.fRect;

    sSprite         = object.sSprite;
    tTexture        = object.tTexture;
    vData           = object.vData;
}

Shape_ML::Shape_ML(){
    tTexture        = nullptr;
    vData           = nullptr;
}

Shape_ML::Shape_ML(const Shape_ML &obj){
    sName           = obj.sName;
    sType           = obj.sType;
    sObjectGroupName     = obj.sObjectGroupName;

    tTexture        = obj.tTexture;
    fRect           = obj.fRect;

    iID             = obj.iID;

    vData           = obj.vData;
}

Polygon_ML::Polygon_ML() : Objects_ML(){
    iCountShapePoints = 0;
}

Polygon_ML::Polygon_ML(const Polygon_ML &obj){
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

Polyline_ML::Polyline_ML(){
    iCountShapePoints = 0;
}

Polyline_ML::Polyline_ML(const Polyline_ML &obj){
    cShape            = obj.cShape;
    iCountShapePoints = obj.iCountShapePoints;
    iID               = obj.iID;
    sName             = obj.sName;
    sObjectGroupName  = obj.sObjectGroupName;
    sType             = obj.sType;
    lShapePoints      = obj.lShapePoints;
    vData             = obj.vData;
}
