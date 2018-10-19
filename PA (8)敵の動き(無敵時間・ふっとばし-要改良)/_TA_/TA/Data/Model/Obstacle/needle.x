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
 130;
 0.00000;-1.05339;-0.51500;,
 0.00000;0.02361;0.00000;,
 0.36416;-1.05339;-0.36416;,
 0.00000;0.02361;0.00000;,
 0.51500;-1.05339;0.00000;,
 0.00000;0.02361;0.00000;,
 0.36416;-1.05339;0.36416;,
 0.00000;0.02361;0.00000;,
 -0.00000;-1.05339;0.51500;,
 0.00000;0.02361;0.00000;,
 -0.36416;-1.05339;0.36416;,
 0.00000;0.02361;0.00000;,
 -0.51500;-1.05339;-0.00000;,
 0.00000;0.02361;0.00000;,
 -0.36416;-1.05339;-0.36416;,
 0.00000;0.02361;0.00000;,
 0.00000;-1.05339;-0.51500;,
 0.00000;-1.05339;-0.00000;,
 0.00000;-1.05339;-0.51500;,
 0.36416;-1.05339;-0.36416;,
 0.51500;-1.05339;0.00000;,
 0.36416;-1.05339;0.36416;,
 -0.00000;-1.05339;0.51500;,
 -0.36416;-1.05339;0.36416;,
 -0.51500;-1.05339;-0.00000;,
 -0.36416;-1.05339;-0.36416;,
 1.04610;-1.05339;-0.51500;,
 1.04610;0.02361;0.00000;,
 1.41026;-1.05339;-0.36416;,
 1.04610;0.02361;0.00000;,
 1.56110;-1.05339;0.00000;,
 1.04610;0.02361;0.00000;,
 1.41026;-1.05339;0.36416;,
 1.04610;0.02361;0.00000;,
 1.04610;-1.05339;0.51500;,
 1.04610;0.02361;0.00000;,
 0.68194;-1.05339;0.36416;,
 1.04610;0.02361;0.00000;,
 0.53110;-1.05339;-0.00000;,
 1.04610;0.02361;0.00000;,
 0.68194;-1.05339;-0.36416;,
 1.04610;0.02361;0.00000;,
 1.04610;-1.05339;-0.51500;,
 1.04610;-1.05339;-0.00000;,
 1.04610;-1.05339;-0.51500;,
 1.41026;-1.05339;-0.36416;,
 1.56110;-1.05339;0.00000;,
 1.41026;-1.05339;0.36416;,
 1.04610;-1.05339;0.51500;,
 0.68194;-1.05339;0.36416;,
 0.53110;-1.05339;-0.00000;,
 0.68194;-1.05339;-0.36416;,
 -1.03514;-1.05339;-0.51500;,
 -1.03514;0.02361;0.00000;,
 -0.67098;-1.05339;-0.36416;,
 -1.03514;0.02361;0.00000;,
 -0.52014;-1.05339;0.00000;,
 -1.03514;0.02361;0.00000;,
 -0.67098;-1.05339;0.36416;,
 -1.03514;0.02361;0.00000;,
 -1.03514;-1.05339;0.51500;,
 -1.03514;0.02361;0.00000;,
 -1.39930;-1.05339;0.36416;,
 -1.03514;0.02361;0.00000;,
 -1.55014;-1.05339;-0.00000;,
 -1.03514;0.02361;0.00000;,
 -1.39930;-1.05339;-0.36416;,
 -1.03514;0.02361;0.00000;,
 -1.03514;-1.05339;-0.51500;,
 -1.03514;-1.05339;0.00000;,
 -1.03514;-1.05339;-0.51500;,
 -0.67098;-1.05339;-0.36416;,
 -0.52014;-1.05339;0.00000;,
 -0.67098;-1.05339;0.36416;,
 -1.03514;-1.05339;0.51500;,
 -1.39930;-1.05339;0.36416;,
 -1.55014;-1.05339;-0.00000;,
 -1.39930;-1.05339;-0.36416;,
 2.07704;-1.05339;-0.51500;,
 2.07704;0.02361;0.00000;,
 2.44120;-1.05339;-0.36416;,
 2.07704;0.02361;0.00000;,
 2.59204;-1.05339;0.00000;,
 2.07704;0.02361;0.00000;,
 2.44120;-1.05339;0.36416;,
 2.07704;0.02361;0.00000;,
 2.07704;-1.05339;0.51500;,
 2.07704;0.02361;0.00000;,
 1.71288;-1.05339;0.36416;,
 2.07704;0.02361;0.00000;,
 1.56204;-1.05339;-0.00000;,
 2.07704;0.02361;0.00000;,
 1.71288;-1.05339;-0.36416;,
 2.07704;0.02361;0.00000;,
 2.07704;-1.05339;-0.51500;,
 2.07704;-1.05339;-0.00000;,
 2.07704;-1.05339;-0.51500;,
 2.44120;-1.05339;-0.36416;,
 2.59204;-1.05339;0.00000;,
 2.44120;-1.05339;0.36416;,
 2.07704;-1.05339;0.51500;,
 1.71288;-1.05339;0.36416;,
 1.56204;-1.05339;-0.00000;,
 1.71288;-1.05339;-0.36416;,
 -2.08573;-1.05339;-0.51500;,
 -2.08573;0.02361;0.00000;,
 -1.72157;-1.05339;-0.36416;,
 -2.08573;0.02361;0.00000;,
 -1.57073;-1.05339;0.00000;,
 -2.08573;0.02361;0.00000;,
 -1.72157;-1.05339;0.36416;,
 -2.08573;0.02361;0.00000;,
 -2.08573;-1.05339;0.51500;,
 -2.08573;0.02361;0.00000;,
 -2.44989;-1.05339;0.36416;,
 -2.08573;0.02361;0.00000;,
 -2.60073;-1.05339;-0.00000;,
 -2.08573;0.02361;0.00000;,
 -2.44989;-1.05339;-0.36416;,
 -2.08573;0.02361;0.00000;,
 -2.08573;-1.05339;-0.51500;,
 -2.08573;-1.05339;0.00000;,
 -2.08573;-1.05339;-0.51500;,
 -1.72157;-1.05339;-0.36416;,
 -1.57073;-1.05339;0.00000;,
 -1.72157;-1.05339;0.36416;,
 -2.08573;-1.05339;0.51500;,
 -2.44989;-1.05339;0.36416;,
 -2.60073;-1.05339;-0.00000;,
 -2.44989;-1.05339;-0.36416;;
 
 80;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;8,9,10;,
 3;10,11,12;,
 3;12,13,14;,
 3;14,15,16;,
 3;17,18,19;,
 3;17,19,20;,
 3;17,20,21;,
 3;17,21,22;,
 3;17,22,23;,
 3;17,23,24;,
 3;17,24,25;,
 3;17,25,18;,
 3;26,27,28;,
 3;28,29,30;,
 3;30,31,32;,
 3;32,33,34;,
 3;34,35,36;,
 3;36,37,38;,
 3;38,39,40;,
 3;40,41,42;,
 3;43,44,45;,
 3;43,45,46;,
 3;43,46,47;,
 3;43,47,48;,
 3;43,48,49;,
 3;43,49,50;,
 3;43,50,51;,
 3;43,51,44;,
 3;52,53,54;,
 3;54,55,56;,
 3;56,57,58;,
 3;58,59,60;,
 3;60,61,62;,
 3;62,63,64;,
 3;64,65,66;,
 3;66,67,68;,
 3;69,70,71;,
 3;69,71,72;,
 3;69,72,73;,
 3;69,73,74;,
 3;69,74,75;,
 3;69,75,76;,
 3;69,76,77;,
 3;69,77,70;,
 3;78,79,80;,
 3;80,81,82;,
 3;82,83,84;,
 3;84,85,86;,
 3;86,87,88;,
 3;88,89,90;,
 3;90,91,92;,
 3;92,93,94;,
 3;95,96,97;,
 3;95,97,98;,
 3;95,98,99;,
 3;95,99,100;,
 3;95,100,101;,
 3;95,101,102;,
 3;95,102,103;,
 3;95,103,96;,
 3;104,105,106;,
 3;106,107,108;,
 3;108,109,110;,
 3;110,111,112;,
 3;112,113,114;,
 3;114,115,116;,
 3;116,117,118;,
 3;118,119,120;,
 3;121,122,123;,
 3;121,123,124;,
 3;121,124,125;,
 3;121,125,126;,
 3;121,126,127;,
 3;121,127,128;,
 3;121,128,129;,
 3;121,129,122;;
 
 MeshMaterialList {
  1;
  80;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  -0.000000;0.431396;-0.902163;,
  0.637925;0.431396;-0.637925;,
  0.902163;0.431396;0.000000;,
  0.637925;0.431396;0.637925;,
  -0.000000;0.431396;0.902163;,
  -0.637925;0.431396;0.637925;,
  -0.902163;0.431396;-0.000000;,
  -0.637925;0.431396;-0.637925;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.431396;-0.902163;,
  0.637925;0.431396;-0.637925;,
  0.902163;0.431396;0.000000;,
  0.637925;0.431396;0.637925;,
  -0.000000;0.431396;0.902163;,
  -0.637925;0.431396;0.637925;,
  -0.902163;0.431396;0.000000;,
  -0.000000;0.431396;-0.902163;,
  -0.000000;0.431396;0.902163;,
  -0.637925;0.431396;0.637925;,
  -0.902163;0.431396;0.000000;,
  -0.637925;0.431396;-0.637925;,
  0.637925;0.431396;-0.637925;,
  0.902163;0.431396;0.000000;,
  0.637925;0.431396;0.637925;,
  -0.000000;0.431396;0.902163;,
  -0.637925;0.431396;0.637925;,
  -0.902163;0.431396;0.000000;,
  -0.637925;0.431396;-0.637925;;
  80;
  3;0,1,1;,
  3;1,1,2;,
  3;2,3,3;,
  3;3,3,4;,
  3;4,5,5;,
  3;5,5,6;,
  3;6,7,7;,
  3;7,7,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;9,10,10;,
  3;10,10,11;,
  3;11,12,12;,
  3;12,12,13;,
  3;13,14,14;,
  3;14,14,15;,
  3;15,7,7;,
  3;7,7,9;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;16,1,1;,
  3;1,1,2;,
  3;2,3,3;,
  3;3,3,17;,
  3;17,18,18;,
  3;18,18,19;,
  3;19,20,20;,
  3;20,20,16;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;16,21,21;,
  3;21,21,22;,
  3;22,23,23;,
  3;23,23,24;,
  3;24,18,18;,
  3;18,18,19;,
  3;19,20,20;,
  3;20,20,16;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;16,1,1;,
  3;1,1,2;,
  3;2,3,3;,
  3;3,3,24;,
  3;24,25,25;,
  3;25,25,26;,
  3;26,27,27;,
  3;27,27,16;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;;
 }
 MeshTextureCoords {
  130;
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
