/*
 *	@author:geistyp
 */
#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "MeshIndexCreator.h"

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
	 *	tid : render texture - GL_TEXTURE_2D
	 */
	void renderMesh(GLuint tid)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tid);

		mesh_.drawFaces();

		glDisable(GL_TEXTURE_2D);
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

};

