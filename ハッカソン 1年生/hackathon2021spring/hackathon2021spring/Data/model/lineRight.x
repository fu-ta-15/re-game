xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 132;
 -10.65418;2.54779;-24.38000;,
 -17.50018;2.54779;-24.38000;,
 -17.50018;7.02779;-24.38000;,
 -10.65418;7.02779;-24.38000;,
 24.38000;2.54778;17.42810;,
 24.38000;2.54778;10.58212;,
 24.38000;7.02778;10.58212;,
 24.38000;7.02778;17.42810;,
 -2.07287;2.54779;16.94913;,
 -12.12149;2.63292;11.81710;,
 -7.17515;2.63292;6.92026;,
 -0.07663;2.54779;9.98173;,
 24.38000;2.54778;10.58212;,
 24.38000;2.54778;17.42810;,
 -2.07287;2.54779;16.94913;,
 24.38000;7.02778;17.42810;,
 -2.07287;7.02779;16.94913;,
 -12.12149;7.11292;11.81710;,
 -12.12149;2.63292;11.81710;,
 -0.07663;2.54779;9.98173;,
 -7.17515;2.63292;6.92026;,
 -7.17515;7.11292;6.92026;,
 -0.07663;7.02779;9.98173;,
 24.38000;7.02778;10.58212;,
 -2.07287;7.02779;16.94913;,
 -0.07663;7.02779;9.98173;,
 -7.17515;7.11292;6.92026;,
 -12.12149;7.11292;11.81710;,
 -16.99133;2.41747;2.00204;,
 -17.50018;2.54779;-24.38000;,
 -10.65418;2.54779;-24.38000;,
 -10.08789;2.41746;0.00846;,
 -16.99133;2.41747;2.00204;,
 -16.99133;6.89746;2.00204;,
 -17.50018;7.02779;-24.38000;,
 -17.50018;2.54779;-24.38000;,
 -10.08789;2.41746;0.00846;,
 -10.65418;2.54779;-24.38000;,
 -10.65418;7.02779;-24.38000;,
 -10.08789;6.89746;0.00846;,
 -16.99133;6.89746;2.00204;,
 -10.08789;6.89746;0.00846;,
 -10.65418;7.02779;-24.38000;,
 -17.50018;7.02779;-24.38000;,
 23.94341;0.14610;-24.38000;,
 19.05341;0.14610;-24.38000;,
 19.05341;4.62610;-24.38000;,
 23.94341;4.62610;-24.38000;,
 19.05341;0.14610;-24.38000;,
 10.03282;0.14610;24.38000;,
 10.03282;4.62610;24.38000;,
 19.05341;4.62610;-24.38000;,
 10.03282;0.14610;24.38000;,
 19.81282;0.14610;24.38000;,
 19.81282;4.62610;24.38000;,
 10.03282;4.62610;24.38000;,
 19.81282;0.14610;24.38000;,
 23.94341;0.14610;-24.38000;,
 23.94341;4.62610;-24.38000;,
 19.81282;4.62610;24.38000;,
 19.05341;0.14610;-24.38000;,
 23.94341;0.14610;-24.38000;,
 23.94341;4.62610;-24.38000;,
 19.05341;4.62610;-24.38000;,
 24.30282;0.14610;-19.04349;,
 24.30282;0.14610;-23.93349;,
 24.30282;4.62610;-23.93349;,
 24.30282;4.62610;-19.04349;,
 24.30282;0.14610;-23.93349;,
 -24.45718;0.14610;-19.89000;,
 -24.45718;4.62610;-19.89000;,
 24.30282;4.62610;-23.93349;,
 -24.45718;0.14610;-19.89000;,
 -24.45718;0.14610;-10.11000;,
 -24.45718;4.62610;-10.11000;,
 -24.45718;4.62610;-19.89000;,
 -24.45718;0.14610;-10.11000;,
 24.30282;0.14610;-19.04349;,
 24.30282;4.62610;-19.04349;,
 -24.45718;4.62610;-10.11000;,
 24.30282;0.14610;-23.93349;,
 24.30282;0.14610;-19.04349;,
 24.30282;4.62610;-19.04349;,
 24.30282;4.62610;-23.93349;,
 24.00049;0.14610;-20.57299;,
 20.54273;0.14610;-24.03074;,
 20.54273;4.62610;-24.03074;,
 24.00049;4.62610;-20.57299;,
 20.54273;0.14610;-24.03074;,
 -20.77419;0.14610;13.78151;,
 -20.77419;4.62610;13.78151;,
 20.54273;4.62610;-24.03074;,
 -20.77419;0.14610;13.78151;,
 -13.85869;0.14610;20.69701;,
 -13.85869;4.62610;20.69701;,
 -20.77419;4.62610;13.78151;,
 -13.85869;0.14610;20.69701;,
 24.00049;0.14610;-20.57299;,
 24.00049;4.62610;-20.57299;,
 -13.85869;4.62610;20.69701;,
 20.54273;0.14610;-24.03074;,
 24.00049;0.14610;-20.57299;,
 24.00049;4.62610;-20.57299;,
 20.54273;4.62610;-24.03074;,
 24.30282;2.54778;-10.57700;,
 24.30282;2.54778;-17.42300;,
 24.30282;7.02778;-17.42300;,
 24.30282;7.02778;-10.57700;,
 17.35718;2.54778;-24.21892;,
 10.51116;2.54779;-24.21892;,
 10.51116;7.02778;-24.21892;,
 17.35718;7.02778;-24.21892;,
 15.34286;2.60429;-15.54174;,
 10.51116;2.54779;-24.21892;,
 17.35718;2.54778;-24.21892;,
 18.77857;2.60429;-18.95204;,
 24.30282;2.54778;-17.42300;,
 24.30282;2.54778;-10.57700;,
 15.34286;2.60429;-15.54174;,
 24.30282;2.54778;-10.57700;,
 24.30282;7.02778;-10.57700;,
 15.34286;7.08429;-15.54174;,
 10.51116;7.02778;-24.21892;,
 18.77857;2.60429;-18.95204;,
 17.35718;7.02778;-24.21892;,
 18.77857;7.08429;-18.95204;,
 24.30282;7.02778;-17.42300;,
 24.30282;2.54778;-17.42300;,
 15.34286;7.08429;-15.54174;,
 24.30282;7.02778;-10.57700;,
 24.30282;7.02778;-17.42300;,
 18.77857;7.08429;-18.95204;;
 
 92;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,13,15,16;,
 4;14,16,17,18;,
 4;19,20,21,22;,
 4;19,22,23,12;,
 4;24,15,23,25;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;28,31,10,9;,
 4;32,18,17,33;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;36,39,21,20;,
 4;40,27,26,41;,
 4;40,41,42,43;,
 4;3,2,1,0;,
 4;7,6,5,4;,
 4;11,10,9,8;,
 4;13,12,11,8;,
 4;16,15,13,14;,
 4;18,17,16,14;,
 4;22,21,20,19;,
 4;12,23,22,19;,
 4;25,23,15,24;,
 4;27,26,25,24;,
 4;31,30,29,28;,
 4;9,10,31,28;,
 4;33,17,18,32;,
 4;35,34,33,32;,
 4;39,38,37,36;,
 4;20,21,39,36;,
 4;41,26,27,40;,
 4;43,42,41,40;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;56,49,60,61;,
 4;62,63,50,59;,
 4;47,46,45,44;,
 4;51,50,49,48;,
 4;55,54,53,52;,
 4;59,58,57,56;,
 4;61,60,49,56;,
 4;59,50,63,62;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;76,69,80,81;,
 4;82,83,70,79;,
 4;67,66,65,64;,
 4;71,70,69,68;,
 4;75,74,73,72;,
 4;79,78,77,76;,
 4;81,80,69,76;,
 4;79,70,83,82;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;96,89,100,101;,
 4;102,103,90,99;,
 4;87,86,85,84;,
 4;91,90,89,88;,
 4;95,94,93,92;,
 4;99,98,97,96;,
 4;101,100,89,96;,
 4;99,90,103,102;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,115,116,117;,
 4;118,119,120,121;,
 4;118,121,122,113;,
 4;123,114,124,125;,
 4;123,125,126,127;,
 4;128,129,130,131;,
 4;128,131,124,122;,
 4;107,106,105,104;,
 4;111,110,109,108;,
 4;115,114,113,112;,
 4;117,116,115,112;,
 4;121,120,119,118;,
 4;113,122,121,118;,
 4;125,124,114,123;,
 4;127,126,125,123;,
 4;131,130,129,128;,
 4;122,124,131,128;;
 
 MeshMaterialList {
  2;
  92;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.279200;0.279200;0.279200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.668000;0.470400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  96;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.001583;-0.999963;0.008450;,
  0.710053;0.000000;-0.704149;,
  -0.711202;0.000000;0.702988;,
  -0.004066;-0.999989;-0.002176;,
  -0.242698;0.000000;0.970102;,
  0.214190;0.000000;-0.976792;,
  0.005293;-0.999954;0.008061;,
  -0.971355;0.000000;0.237633;,
  0.977817;0.000000;-0.209460;,
  -0.000000;-1.000000;-0.000000;,
  -0.018104;0.000000;0.999836;,
  0.024542;0.000000;-0.999699;,
  0.004066;0.999989;0.002176;,
  0.000000;1.000000;0.000000;,
  -0.001583;0.999963;-0.008450;,
  -0.000710;-0.999987;-0.005128;,
  -0.999814;0.000000;0.019284;,
  0.999731;0.000000;-0.023213;,
  -0.005294;0.999954;-0.008061;,
  0.000709;0.999987;0.005128;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.004066;0.999989;0.002176;,
  -0.001583;0.999963;-0.008450;,
  0.242698;0.000000;-0.970102;,
  0.018104;0.000000;-0.999836;,
  0.711202;0.000000;-0.702988;,
  -0.214190;0.000000;0.976792;,
  -0.710053;0.000000;0.704149;,
  -0.024542;0.000000;0.999699;,
  -0.004066;-0.999989;-0.002176;,
  0.001583;-0.999963;0.008450;,
  -0.005293;0.999954;-0.008061;,
  0.000710;0.999987;0.005128;,
  0.971355;0.000000;-0.237633;,
  0.999814;0.000000;-0.019284;,
  -0.977817;0.000000;0.209460;,
  -0.999731;0.000000;0.023213;,
  0.005294;-0.999954;0.008061;,
  -0.000709;-0.999987;-0.005128;,
  0.000000;0.000000;-1.000000;,
  -0.983315;0.000000;-0.181913;,
  0.000000;0.000000;1.000000;,
  0.996431;0.000000;0.084410;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.983315;0.000000;0.181913;,
  -0.996431;0.000000;-0.084410;,
  1.000000;0.000000;0.000000;,
  -0.082643;0.000000;-0.996579;,
  -1.000000;0.000000;0.000000;,
  0.180214;0.000000;0.983627;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.082643;0.000000;0.996579;,
  -0.180214;0.000000;-0.983627;,
  0.707106;0.000000;-0.707108;,
  -0.675127;0.000000;-0.737702;,
  -0.707107;0.000000;0.707107;,
  0.736902;0.000000;0.676000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.707106;0.000000;0.707108;,
  0.675127;0.000000;0.737702;,
  0.707107;0.000000;-0.707107;,
  -0.736902;0.000000;-0.676000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.002529;-0.999993;0.002711;,
  -0.706370;0.000000;0.707843;,
  0.709377;0.000000;-0.704829;,
  0.002081;-0.999970;0.007461;,
  -0.007138;-0.999972;-0.002039;,
  -0.484672;0.000000;0.874696;,
  -0.873685;0.000000;0.486493;,
  0.965460;0.000000;-0.260552;,
  0.266757;0.000000;-0.963764;,
  0.002528;0.999993;-0.002711;,
  0.007138;0.999972;0.002039;,
  -0.002082;0.999970;-0.007462;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.002529;0.999993;-0.002711;,
  -0.002081;0.999970;-0.007461;,
  0.007138;0.999972;0.002039;,
  0.706370;0.000000;-0.707843;,
  0.484672;0.000000;-0.874696;,
  0.873685;0.000000;-0.486493;,
  -0.709377;0.000000;0.704829;,
  -0.965460;0.000000;0.260552;,
  -0.266757;0.000000;0.963764;,
  -0.002528;-0.999993;0.002711;,
  -0.007138;-0.999972;-0.002039;,
  0.002082;-0.999970;0.007462;;
  92;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;5,2,2,5;,
  4;5,5,11,11;,
  4;6,12,12,6;,
  4;6,6,4,4;,
  4;7,3,3,7;,
  4;7,7,13,13;,
  4;14,15,15,14;,
  4;14,14,16,16;,
  4;8,17,17,8;,
  4;8,8,2,2;,
  4;9,4,4,9;,
  4;9,9,18,18;,
  4;10,19,19,10;,
  4;10,10,3,3;,
  4;20,16,16,20;,
  4;20,20,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,25,25,24;,
  4;15,15,24,24;,
  4;26,27,27,26;,
  4;28,28,26,26;,
  4;29,30,30,29;,
  4;31,31,29,29;,
  4;32,11,11,32;,
  4;33,33,32,32;,
  4;34,35,35,34;,
  4;25,25,34,34;,
  4;36,28,28,36;,
  4;37,37,36,36;,
  4;38,39,39,38;,
  4;30,30,38,38;,
  4;40,33,33,40;,
  4;41,41,40,40;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;44,44,44,44;,
  4;48,48,48,48;,
  4;42,42,42,42;,
  4;49,49,49,49;,
  4;47,47,47,47;,
  4;46,46,46,46;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;52,52,52,52;,
  4;56,56,56,56;,
  4;50,50,50,50;,
  4;57,57,57,57;,
  4;55,55,55,55;,
  4;54,54,54,54;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;63,63,63,63;,
  4;62,62,62,62;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,73,73,70;,
  4;70,70,74,74;,
  4;71,75,75,71;,
  4;71,71,76,76;,
  4;72,77,77,72;,
  4;72,72,78,78;,
  4;79,80,80,79;,
  4;79,79,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;84,85,85,84;,
  4;86,86,84,84;,
  4;87,88,88,87;,
  4;89,89,87,87;,
  4;90,91,91,90;,
  4;92,92,90,90;,
  4;93,94,94,93;,
  4;95,95,93,93;;
 }
 MeshTextureCoords {
  132;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.338080;,
  1.000000;0.500140;,
  0.000000;0.500140;,
  0.000000;0.338080;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.661920;0.000000;,
  1.000000;1.000000;,
  0.661920;1.000000;,
  0.499860;1.000000;,
  0.499860;0.000000;,
  0.338080;0.000000;,
  0.500140;0.000000;,
  0.500140;1.000000;,
  0.338080;1.000000;,
  0.000000;1.000000;,
  1.000000;0.661920;,
  0.000000;0.661920;,
  0.000000;0.499860;,
  1.000000;0.499860;,
  1.000000;0.713870;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.713870;,
  0.286130;0.000000;,
  0.286130;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.713870;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.713870;1.000000;,
  1.000000;0.286130;,
  0.000000;0.286130;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.498140;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.498140;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.498140;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.498140;1.000000;,
  0.000000;1.000000;,
  0.501860;0.000000;,
  1.000000;1.000000;,
  0.501860;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.501860;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.501860;;
 }
}
