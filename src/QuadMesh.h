/*
 *	@author:geistyp
 */
#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

/*
 *	Quad mesh creator
 */
class QuadMesh
{
public:
	QuadMesh(void);
	~QuadMesh(void);

	/*
	 *	create base quad mesh
	 *	x/y : initial offset
	 *	w/h : quad size
	 *	res	: mesh resolution
	 */
	void create(int x, int y, int w, int h, int res);

	ofVec2f getPos(int i)
	{
		return vertex_[i];
	}

	/*
	 *	set vertex position
	 *	: if vertex change , use this, updateMesh will recalculate Mesh 
	 */
	void setPos(int i, ofVec2f p)
	{
		vertex_[i] = p;
		updateMesh();
	}

	/*
	 *	Reset texture coordinate
	 *	eg. GL_TEXTURE_2D (1,1) 
	 *		GL_TEXTURE_RECTANGLE (texture_width,texture_height)
	 */
	void ResetTextureCoords(float w, float h);
	//////////////////////////////////////////////////////////////////////////
	/*
	 *	create mesh & indices
	 */
	void createMesh();
	/*
	 *	update mesh, recalculate
	 */
	void updateMesh();

	/*
	 *	render mesh texture
	 *	type: texture type (eg.GL_TEXTURE_2D)
	 *	tid : render texture
	 */
	void renderMesh(GLenum type, GLuint tid)
	{
		glEnable(type);
		glBindTexture(type, tid);

		mesh_.drawFaces();

		glDisable(type);
	}
	/*
	 *	render wirframes (white)
	 */
	void renderWirframes()
	{
		mesh_.drawWireframe();
		ofNoFill();
		for ( int i = 0; i < 4; i++ ) ofCircle(vertex_[i], 10);
	}
	//////////////////////////////////////////////////////////////////////////
	void load(string xmlpath)
	{
		ofxXmlSettings xml;
		if ( !xml.loadFile(xmlpath) ) return;

		resolution_ = xml.getValue("resolution", 1);
		texture_width = xml.getValue("texture_width", 1.0);
		texture_height = xml.getValue("texture_height", 1.0);

		for ( int i = 0; i < 4; i++ )
		{
			string s = xml.getValue("p", "0,0", i);
			sscanf(s.c_str(), "%f,%f", &vertex_[i].x, &vertex_[i].y);
		}

		createMesh();
	}

	void save(string xmlpath)
	{
		ofxXmlSettings xml;

		xml.setValue("resolution", resolution_);

		xml.setValue("texture_width", texture_width);
		xml.setValue("texture_height", texture_height);

		for ( int i = 0; i < 4; i ++ )
		{
			xml.setValue("p", ofToString(vertex_[i].x, 0)+","+ofToString(vertex_[i].y, 0), i);
		}

		xml.saveFile(xmlpath);
	}
	
	void incrResolution()
	{
		resolution_++;
		createMesh();
	}

	void decrResolution()
	{
		if ( resolution_ <= 1 ) return;

		resolution_--;
		createMesh();
	}

	ofVec2f vertex_[4];

	int resolution_;

	ofMesh mesh_;

	ofxXmlSettings xml_;

	float texture_width, texture_height;
};

