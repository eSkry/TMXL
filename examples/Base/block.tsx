<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.2" tiledversion="1.2.4" name="block" tilewidth="32" tileheight="32" tilecount="448" columns="28">
 <image source="block.png" width="896" height="512"/>
 <terraintypes>
  <terrain name="Новый участок местности" tile="0"/>
 </terraintypes>
 <tile id="0" terrain="0,,,"/>
 <tile id="1" terrain=",0,,"/>
 <tile id="2" terrain=",,,0">
  <objectgroup draworder="index">
   <object id="1" x="0" y="-1" width="32" height="35"/>
  </objectgroup>
 </tile>
 <tile id="3" terrain=",,0,"/>
 <tile id="4" terrain="0,0,,"/>
 <tile id="5" terrain=",0,,0"/>
 <tile id="6" terrain=",,0,0"/>
 <tile id="7" terrain="0,,0,"/>
 <tile id="8" terrain="0,,,0"/>
 <tile id="9" terrain=",0,0,"/>
 <tile id="99" terrain="0,0,0,0"/>
 <tile id="127" terrain="0,0,0,0"/>
 <tile id="155" terrain="0,0,0,0"/>
 <tile id="181">
  <objectgroup draworder="index">
   <object id="1" x="4" y="5">
    <polygon points="0,0 6,23 23,7"/>
   </object>
  </objectgroup>
 </tile>
 <tile id="204">
  <objectgroup draworder="index">
   <object id="1" x="17" y="30">
    <point/>
   </object>
  </objectgroup>
 </tile>
 <tile id="230" terrain=",0,0,0"/>
 <tile id="231" terrain="0,0,0,0"/>
 <tile id="232" terrain="0,0,0,0"/>
 <tile id="233" terrain="0,0,0,0"/>
 <tile id="238">
  <animation>
   <frame tileid="59" duration="200"/>
   <frame tileid="64" duration="200"/>
   <frame tileid="224" duration="200"/>
   <frame tileid="232" duration="200"/>
  </animation>
 </tile>
 <tile id="258" terrain="0,0,0,0"/>
 <tile id="259" terrain="0,0,0,0"/>
 <tile id="260" terrain=",,0,"/>
 <tile id="283" terrain="0,,,"/>
 <tile id="292">
  <objectgroup draworder="index">
   <object id="1" x="16" y="18">
    <ellipse/>
   </object>
  </objectgroup>
 </tile>
 <tile id="312" terrain="0,,,"/>
 <wangsets>
  <wangset name="Новый набор плиток Вана" tile="181">
   <wangedgecolor name="w" color="#ff0000" tile="-1" probability="1"/>
   <wangedgecolor name="" color="#00ff00" tile="-1" probability="1"/>
   <wangtile tileid="0" wangid="0x1000000"/>
   <wangtile tileid="1" wangid="0x1"/>
   <wangtile tileid="2" wangid="0x100"/>
   <wangtile tileid="3" wangid="0x10000"/>
   <wangtile tileid="5" wangid="0x1000001"/>
   <wangtile tileid="6" wangid="0x1000100"/>
   <wangtile tileid="8" wangid="0x1000101"/>
   <wangtile tileid="10" wangid="0x1010101"/>
   <wangtile tileid="12" wangid="0x2020202"/>
   <wangtile tileid="178" wangid="0x1010101"/>
  </wangset>
 </wangsets>
</tileset>
