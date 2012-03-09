#include "testApp.h"

#include "QuadMesh.h"

bool select_point(ofVec2f f, ofVec2f t, float r)
{
	if ( f.distance(t) < r ) return true;
	else					 return false;
}

GLuint genTex(int w, int h, unsigned char* pixels)
{
	GLuint tid;
	glGenTextures(1, &tid);
	glBindTexture(GL_TEXTURE_2D, tid);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	return tid;
}

int id = -1;

QuadMesh quadmesh;

ofImage quadimage;

GLuint quadtexture;

//--------------------------------------------------------------
void testApp::setup(){

	quadmesh.create(150, 50, 400, 300, 8);

	quadimage.loadImage("1.jpg");
	quadtexture = genTex(quadimage.getWidth(), quadimage.getHeight(), quadimage.getPixels());
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(0);
	quadmesh.renderMesh(quadtexture);
	quadmesh.renderWirframes();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if ( key == 's' )
	{
		quadmesh.save("quad.xml");
	}
	if ( key == 'l' )
	{
		quadmesh.load("quad.xml");
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	if ( id > -1 )
	{
		quadmesh.setPos(id, ofVec2f(x, y));
	}

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	for ( int i = 0; i < 4; i++ )
	{
		if ( select_point(ofVec2f(x, y), quadmesh.getPos(i), 10) ){	id = i;	return;	}
	}

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	id = -1;

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
